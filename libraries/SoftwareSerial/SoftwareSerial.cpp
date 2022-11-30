/*
SoftwareSerial.cpp (formerly NewSoftSerial.cpp) - 
Multi-instance software serial library for Arduino/Wiring
-- Interrupt-driven receive and other improvements by ladyada
   (http://ladyada.net)
-- Tuning, circular buffer, derivation from class Print/Stream,
   multi-instance support, porting to 8MHz processors,
   various optimizations, PROGMEM delay tables, inverse logic and 
   direct port writing by Mikal Hart (http://www.arduiniana.org)
-- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
-- 20MHz processor support by Garrett Mace (http://www.macetech.com)
-- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at
http://arduiniana.org.
*/
/* Aug 25th 2017: Modified by Yuuki Okamiya for RL78 */

// When set, _DEBUG co-opts pins 11 and 13 for debugging with an
// oscilloscope or logic analyzer.  Beware: it also slightly modifies
// the bit times, so don't rely on it too much at high baud rates
#define _DEBUG 0
#define _DEBUG_PIN1 11
#define _DEBUG_PIN2 13
// 
// Includes
// 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#ifndef __RL78__
#include <util/delay_basic.h>
#else
// 2022/10/15 no use now
#define digitalPinToInt(p) (((p) == 2) ? 0 : ((p) == 3) ? 1 : -1 )

// 2022/10/13 removed by KAD
/*
void _delay_loop_2(uint16_t __count)
{
    __asm __volatile(
        "    movw    ax, %0  \n"
        "    cmpw    ax, #0  \n"
        "    bz      $9f     \n"
        "1:                  \n"
        "    subw    ax, #1  \n"
        "    bnz     $1b     \n"
        "9:                  \n"
        :
        : "r"(__count)
        : "ax"
    );
}
*/

#endif
// 2022/10/13 add by KAD
extern "C" {
    #include "pintable.h"
    extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];
}

// mod KAD(Aono) 2022/10/14
volatile int tempAXvalue=0;
// 2022/10/14 need to move somewhere
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) )
const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
        DIGITAL_PIN_MASK_0,
        DIGITAL_PIN_MASK_1,
        DIGITAL_PIN_MASK_2,
        DIGITAL_PIN_MASK_3,
        DIGITAL_PIN_MASK_4,
        DIGITAL_PIN_MASK_5,
        DIGITAL_PIN_MASK_6,
        DIGITAL_PIN_MASK_7,
        DIGITAL_PIN_MASK_8,
        DIGITAL_PIN_MASK_9,
        DIGITAL_PIN_MASK_10,
        DIGITAL_PIN_MASK_11,
        DIGITAL_PIN_MASK_12,
        DIGITAL_PIN_MASK_13,
        DIGITAL_PIN_MASK_14,
        DIGITAL_PIN_MASK_15,
        DIGITAL_PIN_MASK_16,
        DIGITAL_PIN_MASK_17,
        DIGITAL_PIN_MASK_18,
        DIGITAL_PIN_MASK_19,
        DIGITAL_PIN_MASK_20,
        DIGITAL_PIN_MASK_21,
        DIGITAL_PIN_MASK_22,
        DIGITAL_PIN_MASK_23,
        DIGITAL_PIN_MASK_24,
        DIGITAL_PIN_MASK_25,
        DIGITAL_PIN_MASK_26,
        DIGITAL_PIN_MASK_27,
        DIGITAL_PIN_MASK_28,
        DIGITAL_PIN_MASK_29,
        DIGITAL_PIN_MASK_30
};
//
// Statics
//
SoftwareSerial *SoftwareSerial::active_object = 0;
uint8_t SoftwareSerial::_receive_buffer[_SS_MAX_RX_BUFF]; 
volatile uint8_t SoftwareSerial::_receive_buffer_tail = 0;
volatile uint8_t SoftwareSerial::_receive_buffer_head = 0;

//
// Debugging
//
// This function generates a brief pulse
// for debugging or measuring on an oscilloscope.
#if _DEBUG
inline void DebugPulse(uint8_t pin, uint8_t count)
{
    volatile uint8_t *pport = portOutputRegister(digitalPinToPort(pin));

    uint8_t val = *pport;
    while (count--)
    {
        *pport = val | digitalPinToBitMask(pin);
        *pport = val;
    }
}
#else
inline void DebugPulse(uint8_t, uint8_t) {}
#endif

//
// Private methods
//

/* static */ 
// 2022/10/13 mod by KAD
// inline void SoftwareSerial::tunedDelay(uint16_t delay) {
//  _delay_loop_2(delay);
// }
inline void SoftwareSerial::tunedDelay(uint16_t delay_cnt){
    tempAXvalue = delay_cnt;
    asm("movw bc, ax");
    asm("movw de, #0");
    asm("movw ax, bc");
    asm("cmpw ax, #0");
    asm("bz $1f");
    asm("2:");
    asm("incw de");
    asm("movw ax, de");
    asm("cmpw ax, bc");
    asm("bnz $2b");
    asm("1:");
    return;
}


// This function sets the current object as the "listening"
// one and returns true if it replaces another 
bool SoftwareSerial::listen()
{
    if (!_rx_delay_stopbit)
        return false;

    if (active_object != this)
    {
        if (active_object)
            active_object->stopListening();

        _buffer_overflow = false;
        _receive_buffer_head = _receive_buffer_tail = 0;
        active_object = this;
        setRxIntMsk(true);
        return true;
    }

  return false;
}

// Stop listening. Returns true if we were actually listening.
bool SoftwareSerial::stopListening()
{
    if (active_object == this)
    {
        setRxIntMsk(false);
        active_object = NULL;
        return true;
      }
    return false;
}

// 2022/10/19 added by KAD (only for debug use)
uint8_t tempLEDBlink = 0;

void DebugPulse2(void){
    if(tempLEDBlink == 0)
    {
        digitalWrite(BUILTIN_LED2, HIGH);
        tempLEDBlink = 1;
    }
    else
    {
        digitalWrite(BUILTIN_LED2, LOW);
        tempLEDBlink = 0;
    }
}

//
// The receive routine called by the interrupt handler
//
void SoftwareSerial::recv()
{
// 2022/10/13 removed by KAD
/*
#if GCC_VERSION < 40302
// Work-around for avr-gcc 4.3.0 OSX version bug
// Preserve the registers that the compiler misses
// (courtesy of Arduino forum user *etracer*)
  asm volatile(
    "push r18 \n\t"
    "push r19 \n\t"
    "push r20 \n\t"
    "push r21 \n\t"
    "push r22 \n\t"
    "push r23 \n\t"
    "push r26 \n\t"
    "push r27 \n\t"
    ::);
#endif  
*/
// 2022/10/19 only for debug, if this is added additional 2us delay must be compensated
//    DebugPulse2();
    uint8_t d = 0;

  // If RX line is high, then we don't see any start bit
  // so interrupt is probably not for us
    if (_inverse_logic ? rx_pin_read() : !rx_pin_read())
    {
    // Disable further interrupts during reception, this prevents
    // triggering another interrupt directly after we return, which can
    // cause problems at higher baudrates.
        setRxIntMsk(false);

    // Wait approximately 1/2 of a bit width to "center" the sample
        if(_rx_delay_centering>0) tunedDelay(_rx_delay_centering);

        if(_rx_delay_firstbit>0) tunedDelay(_rx_delay_firstbit);
    // Read each of the 8 bits
        for (uint8_t i=8; i > 0; --i)
        {
            if(i<8) tunedDelay(_rx_delay_intrabit);
            d >>= 1;
//            DebugPulse2();
            if (rx_pin_read())
                d |= 0x80;
        }

        if (_inverse_logic)
            d = ~d;

    // if buffer full, set the overflow flag and return
        uint8_t next = (_receive_buffer_tail + 1) % _SS_MAX_RX_BUFF;
        if (next != _receive_buffer_head)
        {
      // save new data in buffer: tail points to where byte goes
            _receive_buffer[_receive_buffer_tail] = d; // save new byte
            _receive_buffer_tail = next;
        }
        else 
        {
            _buffer_overflow = true;
        }

    // skip the stop bit
        tunedDelay(_rx_delay_stopbit);

    // Re-enable interrupts when we're sure to be inside the stop bit
        setRxIntMsk(true);

    }

// 2022/10/13 removed by KAD
/*
#if GCC_VERSION < 40302
// Work-around for avr-gcc 4.3.0 OSX version bug
// Restore the registers that the compiler misses
  asm volatile(
    "pop r27 \n\t"
    "pop r26 \n\t"
    "pop r23 \n\t"
    "pop r22 \n\t"
    "pop r21 \n\t"
    "pop r20 \n\t"
    "pop r19 \n\t"
    "pop r18 \n\t"
    ::);
#endif
*/
}


uint8_t SoftwareSerial::rx_pin_read()
{
    return *_receivePortRegister & _receiveBitMask;
}

//
// Interrupt handling
//

/* static */
inline void SoftwareSerial::handle_interrupt()
{
    if (active_object)
    {
        active_object->recv();
    }
}

#if defined(PCINT0_vect)
ISR(PCINT0_vect)
{
    SoftwareSerial::handle_interrupt();
}
#endif

#if defined(PCINT1_vect)
ISR(PCINT1_vect, ISR_ALIASOF(PCINT0_vect));
#endif

#if defined(PCINT2_vect)
ISR(PCINT2_vect, ISR_ALIASOF(PCINT0_vect));
#endif

#if defined(PCINT3_vect)
ISR(PCINT3_vect, ISR_ALIASOF(PCINT0_vect));
#endif

#ifdef __RL78__
static void softwareserial_interrupt(){
      SoftwareSerial::handle_interrupt();
}
#endif

//
// Constructor
//
SoftwareSerial::SoftwareSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic /* = false */) : 
    _rx_delay_centering(0),
    _rx_delay_firstbit(0),
    _rx_delay_intrabit(0),
    _rx_delay_stopbit(0),
    _tx_delay(0),
    _buffer_overflow(false),
    _inverse_logic(inverse_logic)
{
// 2022/10/23 modified by KAD
//  setTX(transmitPin);
//  setRX(receivePin);
    _transmitPin = transmitPin;
    _receivePin = receivePin;
    _transmitBitMask = digitalPinToBitMask(transmitPin);
    _receiveBitMask = digitalPinToBitMask(receivePin);
    PinTableType* p;
    PinTableType pin_tbl;
    p =(PinTableType*)&pin_tbl;
    const PinTableType ** pp;
    pp = &pinTablelist[transmitPin];
    p = (PinTableType *)*pp;
    _transmitPortRegister = p->portRegisterAddr;
    pp = &pinTablelist[receivePin];
    p = (PinTableType *)*pp;
    _receiveBitMask = p->mask;
    _receivePortRegister = p->portRegisterAddr;
    _interrupt_num = digitalPinToInterrupt(_receivePin);
    _pcint_maskreg_p = 0;
    _pcint_maskreg_n = 0;
    _pcint_maskvalue_p = 0;
    _pcint_maskvalue_n = 0;
}

//
// Destructor
//
SoftwareSerial::~SoftwareSerial()
{
    end();
}

/* 2022/10/13 remove setTX function and setRX function by KAD
 * These functions are only used for SoftwareSerial constructor and the constructor has improved
void SoftwareSerial::setTX(uint8_t tx)
{
  // First write, then set output. If we do this the other way around,
  // the pin would be output low for a short while before switching to
  // output high. Now, it is input with pullup for a short while, which
  // is fine. With inverse logic, either order is fine.
  digitalWrite(tx, _inverse_logic ? LOW : HIGH);
  pinMode(tx, OUTPUT);
  _transmitBitMask = digitalPinToBitMask(tx);
  uint8_t port = digitalPinToPort(tx);
  _transmitPortRegister = portOutputRegister(port);
}

void SoftwareSerial::setRX(uint8_t rx)
{
  pinMode(rx, INPUT);
  if (!_inverse_logic)
    digitalWrite(rx, HIGH);  // pullup for normal logic!
  _receivePin = rx;
  _receiveBitMask = digitalPinToBitMask(rx);
  uint8_t port = digitalPinToPort(rx);
  _receivePortRegister = portInputRegister(port);
}
*/

uint16_t SoftwareSerial::subtract_cap(uint16_t num, uint16_t sub) {
    if (num > sub)
        return num - sub;
    else
        return 1;
}

//
// Public methods
//

void SoftwareSerial::begin(long speed)
{
  _rx_delay_centering = _rx_delay_intrabit = _rx_delay_stopbit = _tx_delay = _rx_delay_firstbit = 0;

#ifndef __RL78__
  // Precalculate the various delays, in number of 4-cycle delays
  //  uint16_t bit_delay = (F_CPU / speed) / 4;
#else
  // Precalculate the various delays, in number of 9-cycle delays
    uint16_t bit_delay = (F_CPU / speed) / 5 - 5;
#endif

  // 12 (gcc 4.8.2) or 13 (gcc 4.3.2) cycles from start bit to first bit,
  // 15 (gcc 4.8.2) or 16 (gcc 4.3.2) cycles between bits,
  // 12 (gcc 4.8.2) or 14 (gcc 4.3.2) cycles from last bit to stop bit
  // These are all close enough to just use 15 cycles, since the inter-bit
  // timings are the most critical (deviations stack 8 times)
  _tx_delay = subtract_cap(bit_delay, 15 / 4);

#ifndef __RL78__
  // Only setup rx when we have a valid PCINT for this pin
    if (digitalPinToPCICR(_receivePin)) {
    #if GCC_VERSION > 40800
    // Timings counted from gcc 4.8.2 output. This works up to 115200 on
    // 16Mhz and 57600 on 8Mhz.
    //
    // When the start bit occurs, there are 3 or 4 cycles before the
    // interrupt flag is set, 4 cycles before the PC is set to the right
    // interrupt vector address and the old PC is pushed on the stack,
    // and then 75 cycles of instructions (including the RJMP in the
    // ISR vector table) until the first delay. After the delay, there
    // are 17 more cycles until the pin value is read (excluding the
    // delay in the loop).
    // We want to have a total delay of 1.5 bit time. Inside the loop,
    // we already wait for 1 bit time - 23 cycles, so here we wait for
    // 0.5 bit time - (71 + 18 - 22) cycles.
    _rx_delay_centering = subtract_cap(bit_delay / 2, (4 + 4 + 75 + 17 - 23) / 4);

    // There are 23 cycles in each loop iteration (excluding the delay)
    _rx_delay_intrabit = subtract_cap(bit_delay, 23 / 4);

    // There are 37 cycles from the last bit read to the start of
    // stopbit delay and 11 cycles from the delay until the interrupt
    // mask is enabled again (which _must_ happen during the stopbit).
    // This delay aims at 3/4 of a bit time, meaning the end of the
    // delay will be at 1/4th of the stopbit. This allows some extra
    // time for ISR cleanup, which makes 115200 baud at 16Mhz work more
    // reliably
    _rx_delay_stopbit = subtract_cap(bit_delay * 3 / 4, (37 + 11) / 4);
    #else // Timings counted from gcc 4.3.2 output
    // Note that this code is a _lot_ slower, mostly due to bad register
    // allocation choices of gcc. This works up to 57600 on 16Mhz and
    // 38400 on 8Mhz.
        _rx_delay_centering = subtract_cap(bit_delay / 2, (4 + 4 + 97 + 29 - 11) / 4);
        _rx_delay_intrabit = subtract_cap(bit_delay, 11 / 4);
        _rx_delay_stopbit = subtract_cap(bit_delay * 3 / 4, (44 + 17) / 4);
    #endif


    // Enable the PCINT for the entire port here, but never disable it
    // (others might also need it, so we disable the interrupt by using
    // the per-pin PCMSK register).
        *digitalPinToPCICR(_receivePin) |= _BV(digitalPinToPCICRbit(_receivePin));
    // Precalculate the pcint mask register and value, so setRxIntMask
    // can be used inside the ISR without costing too much time.
        _pcint_maskreg = digitalPinToPCMSK(_receivePin);
        _pcint_maskvalue = _BV(digitalPinToPCMSKbit(_receivePin));
        tunedDelay(_tx_delay); // if we were low this establishes the end
    }
#else

// 2022/10/14 modified by KAD
//  digitalPinToInterrupt is defined in pins_arduino.h
//  attachInterrupt(digitalPinToInterrupt(_receivePin), softwareserial_interrupt, CHANGE);
    attachInterrupt(_interrupt_num, softwareserial_interrupt, CHANGE);
    // Note that this code is a _lot_ slower, mostly due to bad register
    // allocation choices of gcc. This works up to 57600 on 16Mhz and
    // 38400 on 8Mhz.
/*
    _rx_delay_centering = subtract_cap(bit_delay / 2, (4 + 4 + 97 + 29 - 11) / 4);
    _rx_delay_intrabit = subtract_cap(bit_delay , 11 / 4);
    _rx_delay_stopbit = subtract_cap(bit_delay * 3 / 4, (44 + 17) / 4);
*/


    if (115200 == speed)
    {
        _rx_delay_centering = 0;
        _rx_delay_firstbit = 20;
        _rx_delay_intrabit = 28;
        _rx_delay_stopbit = 28;
        _tx_delay = 28;
    }
    else if (57600 == speed)
    {
        _rx_delay_centering = 25;
        _rx_delay_firstbit = 68;
        _rx_delay_intrabit = 68;
        _rx_delay_stopbit = 68;
        _tx_delay = 68;
    }
    else if (38400 == speed)
    {
        _rx_delay_centering = 45;
        _rx_delay_firstbit = 107;
        _rx_delay_intrabit = 107;
        _rx_delay_stopbit = 107;
        _tx_delay = 107;
    }
    else if (19200 == speed)
    {
        _rx_delay_centering = 110;
        _rx_delay_firstbit = 221;
        _rx_delay_intrabit = 221;
        _rx_delay_stopbit = 221;
        _tx_delay = 221;
    }
    else if (9600 == speed)
    {
        _rx_delay_centering = 227;
        _rx_delay_firstbit = 455;
        _rx_delay_intrabit = 455;
        _rx_delay_stopbit = 455;
        _tx_delay = 455;
    }
    else if (4800 == speed)
    {
        _rx_delay_centering = 467;
        _rx_delay_firstbit = 934;
        _rx_delay_intrabit = 934;
        _rx_delay_stopbit = 934;
        _tx_delay = 934;
    }

// 2022/10/14 added by KAD
    Set_SerialPort(_transmitPin,_receivePin);
#endif

#if _DEBUG
    pinMode(_DEBUG_PIN1, OUTPUT);
    pinMode(_DEBUG_PIN2, OUTPUT);
#endif

    listen();
}
// 2022/10/19 modified by KAD
// param : true means enable the interruption
void SoftwareSerial::setRxIntMsk(bool enable)
{
    if (enable)
    {
        _pcint_maskreg_p |= _pcint_maskvalue_p;
        _pcint_maskreg_n |= _pcint_maskvalue_p;
    }
    else{
        _pcint_maskreg_p &= ~_pcint_maskvalue_p;
        _pcint_maskreg_n &= ~_pcint_maskvalue_p;
    }
}

/*
void SoftwareSerial::setRxIntMsk(bool enable)
{
    if (enable)
      *_pcint_maskreg |= _pcint_maskvalue;
    else
      *_pcint_maskreg &= ~_pcint_maskvalue;
}
*/

// 2022/10/13 add KAD
void SoftwareSerial::tx_pin_write(uint8_t pin_state)
{
    if (pin_state == LOW)
        *_transmitPortRegister &= ~_transmitBitMask;
    else
        *_transmitPortRegister |= _transmitBitMask;
}

void SoftwareSerial::end()
{
  stopListening();
}


// Read data from buffer
int SoftwareSerial::read()
{
    if (!isListening())
        return -1;

  // Empty buffer?
    if (_receive_buffer_head == _receive_buffer_tail)
        return -1;

  // Read from "head"
    uint8_t d = _receive_buffer[_receive_buffer_head]; // grab next byte
    _receive_buffer_head = (_receive_buffer_head + 1) % _SS_MAX_RX_BUFF;
    return d;
}

int SoftwareSerial::available()
{
    if (!isListening())
        return 0;

    return (_receive_buffer_tail + _SS_MAX_RX_BUFF - _receive_buffer_head) % _SS_MAX_RX_BUFF;
}

// modified by KAD 2022/10/17 6->4
const int XMIT_START_ADJUSTMENT = 4;

// modified by KAD 2022/10/18 add interruption control
//
size_t SoftwareSerial::write(uint8_t b)
{
    uint8_t bak_ITLCTL0;
    if (_tx_delay == 0)
        return 0;

// add 2022/10/18 stop interrupt
//    bak_ITLCTL0 = ITLCTL0;
//    ITLCTL0 &= 0xF0;
    noInterrupts();

  // Write the start bit
    tempAXvalue = _inverse_logic ? HIGH : LOW;
    tx_pin_write(tempAXvalue);
    tempAXvalue = _tx_delay + XMIT_START_ADJUSTMENT;
    tunedDelay(tempAXvalue);

  // Write each of the 8 bits
    if (_inverse_logic)
    {
        for (uint8_t mask = 0x01; mask; mask <<= 1)
        {
            if (b & mask) // choose bit
            tx_pin_write(LOW); // send 1
            else
            tx_pin_write(HIGH); // send 0

            tunedDelay(_tx_delay);
        }
        tx_pin_write(LOW); // restore pin to natural state
    }
    else
    {
        for (uint8_t mask = 0x01; mask; mask <<= 1)
        {
            if (b & mask) // choose bit
                tx_pin_write(HIGH); // send 1
            else
                tx_pin_write(LOW); // send 0

            tunedDelay(_tx_delay);
        }

        tx_pin_write(HIGH); // restore pin to natural state
    }
//  SREG = oldSREG; // turn interrupts back on
    tunedDelay(_tx_delay);
// 2022/10/18 add interrupt restart
//  ITLCTL0 = bak_ITLCTL0;
    interrupts();


    return 1;
}

/*
size_t SoftwareSerial::write(uint8_t b)
{
  if (_tx_delay == 0) {
    setWriteError();
    return 0;
  }

  // By declaring these as local variables, the compiler will put them
  // in registers _before_ disabling interrupts and entering the
  // critical timing sections below, which makes it a lot easier to
  // verify the cycle timings
  volatile uint8_t *reg = _transmitPortRegister;
  uint8_t reg_mask = _transmitBitMask;
  uint8_t inv_mask = ~_transmitBitMask;
#ifndef __RL78__
  uint8_t oldSREG = SREG;
#else
  uint8_t oldSREG = isInterrupts();
#endif
  bool inv = _inverse_logic;
  uint16_t delay = _tx_delay;

  if (inv)
    b = ~b;

  cli();  // turn off interrupts for a clean txmit

  // Write the start bit
  if (inv)
    *reg |= reg_mask;
  else
    *reg &= inv_mask;

  tunedDelay(delay);

  // Write each of the 8 bits
  for (uint8_t i = 8; i > 0; --i)
  {
    if (b & 1) // choose bit
      *reg |= reg_mask; // send 1
    else
      *reg &= inv_mask; // send 0

    tunedDelay(delay);
    b >>= 1;
  }

  // restore pin to natural state
  if (inv)
    *reg &= inv_mask;
  else
    *reg |= reg_mask;

#ifndef __RL78__
  SREG = oldSREG; // turn interrupts back on
#else
  if(oldSREG){
      interrupts();
  } else {
      noInterrupts();
  }
#endif
  tunedDelay(_tx_delay);
  
  return 1;
}
*/

void SoftwareSerial::flush()
{
  // There is no tx buffering, simply return
}

int SoftwareSerial::peek()
{
    if (!isListening())
        return -1;

  // Empty buffer?
    if (_receive_buffer_head == _receive_buffer_tail)
        return -1;

  // Read from "head"
    return _receive_buffer[_receive_buffer_head];
}

// 2022/10/14 added by KAD
void SoftwareSerial::Set_SerialPort(uint8_t txd_pin,uint8_t rxd_pin)
{
    //PinTableType* p;
    //PinTableType pin_tbl;
    //p = (PinTableType*)&pin_tbl;


    const PinTableType ** pp;
    PinTableType * p;

    /* Set RxD pin */
    //getPinTable(rxd_pin,p);
    pp = &pinTablelist[rxd_pin];
    p = (PinTableType *)*pp;
    /* Set PM Register for Input */
    *p->portModeRegisterAddr |=  (unsigned long)(0x1 << p->bit);

    /* Set PMCA Register */
    if (0!=p->pmca){
        *p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
    }

    /* Set PMCT Register */
    if (0!=p->pmct){
        *p->portModeControlTRegisterAddr &= (unsigned long)~(p->pmct);
    }

    /* Set PMCE Register for Output */
    if (0!=p->pmce){
        *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }

    /* Set CCDE Register for Digital InOut */
    if (0!=p->ccde){
        CCDE &= (uint8_t)~(p->ccde);
    }

// 2022/10/24 modified by KAD
    if(_interrupt_num<5)
    {
        _pcint_maskreg_p = EGP0;
        _pcint_maskreg_n = EGN0;
        _pcint_maskvalue_p = bit(_interrupt_num);
        _pcint_maskvalue_n = bit(_interrupt_num);
    }
    else{
        _pcint_maskreg_p = EGP1;
        _pcint_maskreg_n = EGN1;
        _pcint_maskvalue_p = bit(_interrupt_num-5);
        _pcint_maskvalue_n = bit(_interrupt_num-5);
    }

    /* Set TxD pin */
    //getPinTable(txd_pin,p);
    pp = &pinTablelist[txd_pin];
    p = (PinTableType *)*pp;
    /* Set PMCE Register t */
    if (0!=p->pmce){
        *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }

    /* Set P Register for Set "H" Output Port*/
    *p->portRegisterAddr |= (unsigned long)(0x1 << p->bit);

    /* Set PM Register for Output */
    *p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);

    /* Set PMCA Register */
    if (0!=p->pmca){
        *p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
    }

    /* Set PMCT Register */
    if (0!=p->pmct){
        *p->portModeControlTRegisterAddr &= (unsigned long)~(p->pmct);
    }

    /* Set PMCE Register t */
    if (0!=p->pmce){
        *p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
    }

    /* Set CCDE Register for Digital InOut */
    if (0!=p->ccde){
        CCDE &= (uint8_t)~(p->ccde);
    }
}
