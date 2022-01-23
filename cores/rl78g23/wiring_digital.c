/*
  wiring_digital.c - digital input and output functions
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2005-2006 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  Modified 28 September 2010 by Mark Sproul

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/
/*
 * Modified  4 Mar  2017 by Yuuki Okamiya for RL78/G13
*/

#define ARDUINO_MAIN
#include "wiring_private.h"
#include "pins_arduino.h"

#define PMPUPIMPOM_CHECK_ENABLE		/* Do not change invalid bits */

#ifdef __RL78__
#include "pintable.h"
extern bool g_u8AnalogWriteAvailableTable[NUM_DIGITAL_PINS];
extern volatile SwPwm g_SwPwm[NUM_SWPWM_PINS];

/**********************************************************************************************************************
 * Function Name: pintable setting
 * Description  : Set the pintable.
 * Arguments    : pin  - pin number
 *              : pp   - pin table
 * Return Value : -
 *********************************************************************************************************************/
void getPinTable(uint8_t pin,PinTableType *pp)
{
	pp->mask                         = pin_mask[pin];
	pp->bit                          = pin_bit[pin];
	pp->pmca                         = pin_pmca[pin];
	pp->pmct                         = pin_pmct[pin];
	pp->pmce                         = pin_pmce[pin];
	pp->ccde                         = pin_ccde[pin];
	pp->pdidis                       = pin_pdidis[pin];
	pp->pm                           = pin_pm[pin];
	pp->pu                           = pin_pu[pin];
	pp->pim                          = pin_pim[pin];
	pp->pom                          = pin_pom[pin];
	pp->timer                        = 0;
	pp->portModeRegisterAddr         = getPortModeRegisterAddr(digital_pin[pin]);
	pp->portPullUpRegisterAddr       = getPortPullUpRegisterAddr(digital_pin[pin]);
	pp->portInputModeRegisterAddr    = getPortInputModeRegisterAddr(digital_pin[pin]);
	pp->portOutputModeRegisterAddr   = getPortOutputModeRegisterAddr(digital_pin[pin]);
	pp->portRegisterAddr             = getPortRegisterAddr(digital_pin[pin]);
	pp->portModeControlARegisterAddr = getPortModeControlARegisterAddr(digital_pin[pin]);
	pp->portModeControlTRegisterAddr = getPortModeControlTRegisterAddr(digital_pin[pin]);
	pp->portModeControlERegisterAddr = getPortModeControlERegisterAddr(digital_pin[pin]);
	pp->portOutCurControlRegisterAddr= getPortOutCurControlRegisterAddr();
	pp->portDigInputDisRegisterAddr  = getPortDigInputDisRegisterAddr(digital_pin[pin]);
}

/**
 * PWM STOP~
 *
 * @param[in] u8Timer Timer Number of PWM
 *
 * @return Nothing
 *
 * @attention Nothing
 ***************************************************************************/
void _turnOffPwmPin(uint8_t u8Pin)
{
	unsigned int u16TMR0x;

	uint8_t u8Timer = 0xFF;
	if (u8Pin < NUM_DIGITAL_PINS) {
//		u8Timer = getPinTable(u8Pin)->timer;
		g_u8AnalogWriteAvailableTable[u8Pin] = false;
	}
	if (u8Timer == SWPWM_PIN) {
		///////////////////////
		// Software PWM�Ή��s���̏ꍇ
		///////////////////////
#if defined(__RL78__)
		int i;

		for (i = 0; i < NUM_SWPWM_PINS; i++) {
			if (g_SwPwm[i].valid) {
				if (g_SwPwm[i].pin == u8Pin) {
					g_SwPwm[i].valid = false;
				} else {
					break;
				}
			}
		}
		if (i >= NUM_SWPWM_PINS) {			// SoftwarePWM�̐ݒ�Ȃ�
			_stopTimerChannel(SW_PWM_TIMER);
		}
#endif
	} else {
		///////////////////////
		// PWM�Ή��s���̏ꍇ
		///////////////////////
		switch (u8Timer) {
		case 1:
			u16TMR0x = TMR01;
			break;

		case 2:
			u16TMR0x = TMR02;
			break;

		case 3:
			u16TMR0x = TMR03;
			break;

		case 4:
			u16TMR0x = TMR04;
			break;

		case 5:
			u16TMR0x = TMR05;
			break;

		case 6:
			u16TMR0x = TMR06;
			break;

		case 7:
			u16TMR0x = TMR07;
			break;

		default:
			u16TMR0x = PWM_MASTER_MODE;
			break;
		}
		if (u16TMR0x == PWM_SLAVE_MODE) {
			_stopTimerChannel(u8Timer);
		}
	}
}
#endif/*__RL78__*/

/**********************************************************************************************************************
 * Function Name: pinmode setting
 * Description  : Set the port register.
 * Arguments    : -
 * Return Value : -
 *********************************************************************************************************************/
void pinMode(uint8_t pin, uint8_t u8Mode)
{
#ifndef __RL78__
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *reg, *out;

	if (port == NOT_A_PIN) return;

	/* JWS: can I let the optimizer do this? */
	reg = portModeRegister(port);
	out = portOutputRegister(port);

	if (mode == INPUT) {
		uint8_t oldSREG = SREG;
                cli();
		*reg &= ~bit;
		*out &= ~bit;
		SREG = oldSREG;
	} else if (mode == INPUT_PULLUP) {
		uint8_t oldSREG = SREG;
                cli();
		*reg &= ~bit;
		*out |= bit;
		SREG = oldSREG;
	} else {
		uint8_t oldSREG = SREG;
                cli();
		*reg |= bit;
		SREG = oldSREG;
	}
#else /*__RL78__*/
	if (pin < NUM_DIGITAL_PINS) {
		PinTableType *p;
		PinTableType pin_tbl;
		p = (PinTableType*)&pin_tbl;

		getPinTable(pin,p);

#ifdef PMPUPIMPOM_CHECK_ENABLE
		if (0 != p->pm){
#endif
			switch (u8Mode) {
				 case OUTPUT:
					*p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);
					break;
				 case INPUT:
					*p->portModeRegisterAddr |=  (unsigned long)(0x1 << p->bit);
					break;
			}
#ifdef PMPUPIMPOM_CHECK_ENABLE
		}
#endif

		/* clear pmca register when analog pin */
		if (0!=p->pmca)
		{
			*p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
		}

		/* clear pmct register when touch pin */
		if (0!=p->pmct)
		{
			*p->portModeControlTRegisterAddr &= (unsigned long)~(p->pmct);
		}

		/* clear pmce register when ELCL pin */
		if (0!=p->pmce)
		{
			*p->portModeControlERegisterAddr &= (unsigned long)~(p->pmce);
		}

		/* clear ccde register */
		if (0!=p->ccde)
		{
			*p->portOutCurControlRegisterAddr &= (unsigned long)~(p->ccde);
		}

		if (g_u8AnalogWriteAvailableTable[pin]) {
			_turnOffPwmPin(pin);	/* PWM setting cancel */
		}
		if (!(*p->portModeRegisterAddr & p->mask)) {
			if (*p->portRegisterAddr & p->mask) {
				if (u8Mode == INPUT) {
					u8Mode = INPUT_PULLUP;
				} else if (u8Mode == INPUT_TTL) {
					u8Mode = INPUT_TTL_PULLUP;
				}
			}
		}

		switch (u8Mode) {
		case INPUT:
		case INPUT_PULLUP:
		case INPUT_TTL:
		case INPUT_TTL_PULLUP:
#ifdef PMPUPIMPOM_CHECK_ENABLE
			if (0 != p->pu){
				if (u8Mode == INPUT_PULLUP || u8Mode == INPUT_TTL_PULLUP) {
					*p->portPullUpRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* Enable Pullup Reg */
				} else {
					*p->portPullUpRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* Disable Pullup Reg */
				}
			}
			if (0 != p->pim){
				if (u8Mode == INPUT_TTL || u8Mode == INPUT_TTL_PULLUP) {
					*p->portInputModeRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set TTL Input */
				} else {
					*p->portInputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set CMOS Onput */
				}
			}
			if (0 != p->pm){
				*p->portModeRegisterAddr |= (unsigned long)(1U << p->bit); 			/* set Input Mode */
			}
			if (0 != p->pom){
				*p->portOutputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);  /* set Normal Output */
			}
			if (0 != p->pdidis){
				*p->portDigInputDisRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set Input enable */
			}
#else
			if (u8Mode == INPUT_PULLUP || u8Mode == INPUT_TTL_PULLUP) {
				*p->portPullUpRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* Enable Pullup Reg */
			} else {
				*p->portPullUpRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* Disable Pullup Reg */
			}
			if (u8Mode == INPUT_TTL || u8Mode == INPUT_TTL_PULLUP) {
				*p->portInputModeRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set TTL Input */
			} else {
				*p->portInputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set CMOS Onput */
			}
			*p->portModeRegisterAddr |= (unsigned long)(1U << p->bit); 			/* set Input Mode */
			*p->portOutputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);  /* set Normal Output */
			*p->portDigInputDisRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set Input enable */
#endif
			break;
		case OUTPUT:
		case OUTPUT_OPENDRAIN:
#ifdef PMPUPIMPOM_CHECK_ENABLE
			if (u8Mode == OUTPUT_OPENDRAIN) {
				if (0 != p->pom){
					*p->portOutputModeRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set N-ch OpenDrain output */
				}
				if (0 != p->pdidis){
					*p->portDigInputDisRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set N-ch Input disable */
				}
			} else {
				if (0 != p->pom){
					*p->portOutputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);  /* set Normal Output */
				}
				if (0 != p->pdidis){
					*p->portDigInputDisRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set Input enable */
				}
			}
			if (0 != p->pm){
				*p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);		/* set Output Mode */
			}
			if (0 != p->pu){
				*p->portPullUpRegisterAddr &= (unsigned long)~(0x1 << p->bit);		/* Disable Pullup Reg */
			}
			if (0 != p->pim){
				*p->portInputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set CMOS Onput */
			}
			*p->portRegisterAddr &= (unsigned long)~(0x1 << p->bit);			/* clear Port */
#else
			if (u8Mode == OUTPUT_OPENDRAIN) {
				*p->portOutputModeRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set N-ch OpenDrain output */
				*p->portDigInputDisRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* set N-ch Input disable */
			} else {
				*p->portOutputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);  /* set Normal Output */
				*p->portDigInputDisRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set Input enable */
			}
			*p->portModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);		/* set Output Mode */
			*p->portPullUpRegisterAddr &= (unsigned long)~(0x1 << p->bit);		/* Disable Pullup Reg */
			*p->portInputModeRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set CMOS Onput */
			*p->portRegisterAddr &= (unsigned long)~(0x1 << p->bit);			/* clear Port */
#endif
			break;
		}
	}
#endif/*__RL78__*/
}

// Forcing this inline keeps the callers from having to push their own stuff
// on the stack. It is a good performance win and only takes 1 more byte per
// user than calling. (It will take more bytes on the 168.)
//
// But shouldn't this be moved into pinMode? Seems silly to check and do on
// each digitalread or write.
//
// Mark Sproul:
// - Removed inline. Save 170 bytes on atmega1280
// - changed to a switch statment; added 32 bytes but much easier to read and maintain.
// - Added more #ifdefs, now compiles for atmega645
//
#ifndef __RL78__
static inline void turnOffPWM(uint8_t timer) __attribute__ ((always_inline));
static inline void turnOffPWM(uint8_t timer)
static void turnOffPWM(uint8_t pin)
{
#ifndef __RL78__
	switch (timer)
	{
		#if defined(TCCR1A) && defined(COM1A1)
		case TIMER1A:   cbi(TCCR1A, COM1A1);    break;
		#endif
		#if defined(TCCR1A) && defined(COM1B1)
		case TIMER1B:   cbi(TCCR1A, COM1B1);    break;
		#endif
		
		#if defined(TCCR2) && defined(COM21)
		case  TIMER2:   cbi(TCCR2, COM21);      break;
		#endif
		
		#if defined(TCCR0A) && defined(COM0A1)
		case  TIMER0A:  cbi(TCCR0A, COM0A1);    break;
		#endif
		
		#if defined(TIMER0B) && defined(COM0B1)
		case  TIMER0B:  cbi(TCCR0A, COM0B1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2A1)
		case  TIMER2A:  cbi(TCCR2A, COM2A1);    break;
		#endif
		#if defined(TCCR2A) && defined(COM2B1)
		case  TIMER2B:  cbi(TCCR2A, COM2B1);    break;
		#endif
		
		#if defined(TCCR3A) && defined(COM3A1)
		case  TIMER3A:  cbi(TCCR3A, COM3A1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3B1)
		case  TIMER3B:  cbi(TCCR3A, COM3B1);    break;
		#endif
		#if defined(TCCR3A) && defined(COM3C1)
		case  TIMER3C:  cbi(TCCR3A, COM3C1);    break;
		#endif

		#if defined(TCCR4A) && defined(COM4A1)
		case  TIMER4A:  cbi(TCCR4A, COM4A1);    break;
		#endif					
		#if defined(TCCR4A) && defined(COM4B1)
		case  TIMER4B:  cbi(TCCR4A, COM4B1);    break;
		#endif
		#if defined(TCCR4A) && defined(COM4C1)
		case  TIMER4C:  cbi(TCCR4A, COM4C1);    break;
		#endif			
		#if defined(TCCR4C) && defined(COM4D1)
		case TIMER4D:	cbi(TCCR4C, COM4D1);	break;
		#endif			
			
		#if defined(TCCR5A)
		case  TIMER5A:  cbi(TCCR5A, COM5A1);    break;
		case  TIMER5B:  cbi(TCCR5A, COM5B1);    break;
		case  TIMER5C:  cbi(TCCR5A, COM5C1);    break;
		#endif
	}
#else /*__RL78__*/
	unsigned int u16TMR0x;

	uint8_t u8Timer = 0xFF;
	if (pin < NUM_DIGITAL_PINS) {
//		u8Timer = getPinTable(pin)->timer;
		g_u8AnalogWriteAvailableTable[pin] = false;
	}
	if (u8Timer == SWPWM_PIN) {
		///////////////////////
		// Software PWM�Ή��s���̏ꍇ
		///////////////////////
#if defined(__RL78__)
		int i;

		for (i = 0; i < NUM_SWPWM_PINS; i++) {
			if (g_SwPwm[i].valid) {
				if (g_SwPwm[i].pin == pin) {
					g_SwPwm[i].valid = false;
				} else {
					break;
				}
			}
		}
		if (i >= NUM_SWPWM_PINS) {			// SoftwarePWM�̐ݒ�Ȃ�
			_stopTimerChannel(SW_PWM_TIMER);
		}
#endif
	} else {
		///////////////////////
		// For PWM Pin
		///////////////////////
		switch (u8Timer) {
		case 1:
			u16TMR0x = TMR01;
			break;

		case 2:
			u16TMR0x = TMR02;
			break;

		case 3:
			u16TMR0x = TMR03;
			break;

		case 4:
			u16TMR0x = TMR04;
			break;

		case 5:
			u16TMR0x = TMR05;
			break;

		case 6:
			u16TMR0x = TMR06;
			break;

		case 7:
			u16TMR0x = TMR07;
			break;

		default:
			u16TMR0x = PWM_MASTER_MODE;
			break;
		}
		if (u16TMR0x == PWM_SLAVE_MODE) {
			_stopTimerChannel(u8Timer);
		}
	}
#endif/*__RL78__*/
}
#endif

/**********************************************************************************************************************
 * Function Name: pin output
 * Description  : Perform port output
 * Arguments    : pin  - pin number
 *              : pp   - output value
 * Return Value : -
 *********************************************************************************************************************/
void digitalWrite(uint8_t pin, uint8_t val)
{
	PinTableType* p;
	PinTableType pin_tbl;
	p =(PinTableType*)&pin_tbl;

#ifndef __RL78__
	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *out;

	if (port == NOT_A_PIN) return;

	/* If the pin that support PWM output, we need to turn it off */
	/* before doing a digital write. */
	if (timer != NOT_ON_TIMER) turnOffPWM(timer);

	out = portOutputRegister(port);

	uint8_t oldSREG = SREG;
	cli();

	if (val == LOW) {
		*out &= ~bit;
	} else {
		*out |= bit;
	}

	SREG = oldSREG;
#else /*__RL78__*/
	if (pin < NUM_DIGITAL_PINS) {
		getPinTable(pin,p);
		if (*p->portModeRegisterAddr & p->mask) {
			/* When Input Mode */
#ifdef WORKAROUND_READ_MODIFY_WRITE
			if (val == LOW) {
				cbi(p->portPullUpRegisterAddr, p->mask);	/* Disable pull-up resistor */
				cbi(p->portRegisterAddr, p->mask);			/* Set output to LOW */
			} else {
				sbi(p->portPullUpRegisterAddr, p->mask);	/* Enable pull-up resistor */
				sbi(p->portRegisterAddr, p->mask);			/* Set output to HIGH */
			}
#else
			if (val == LOW) {
				*p->portPullUpRegisterAddr &= ~p->mask;		/* Disable Pullup Reg */
			} else {
				*p->portPullUpRegisterAddr |= p->mask;		/* Enable Pullup Reg */
			}
#endif
		}
		else
		{
			/* When Output Mode  */
#ifdef WORKAROUND_READ_MODIFY_WRITE
			if (val == LOW) {
				cbi(p->portRegisterAddr, p->mask);		/* Write "0" to Port */
			} else {
				sbi(p->portRegisterAddr, p->mask);		/* Write "1" to Port */
			}
#else
			if (val == LOW) {
				*p->portRegisterAddr &= ~p->mask;		/* Write "0" to Port */
			} else {
				*p->portRegisterAddr |= p->mask;		/* Write "1" to Port */
			}
#endif
		}
	}
#endif /*__RL78__*/
}

/**********************************************************************************************************************
 * Function Name: pin input
 * Description  : Perform port input
 * Arguments    : pin  - pin number
 * Return Value : input value
 *********************************************************************************************************************/
int digitalRead(uint8_t pin)
{
#ifndef __RL78__
	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);

	if (port == NOT_A_PIN) return LOW;

	/* If the pin that support PWM output, we need to turn it off */
	/* before getting a digital reading. */
	if (timer != NOT_ON_TIMER) turnOffPWM(timer);

	if (*portInputRegister(port) & bit) return HIGH;
	return LOW;
#else
#if 1
	int	s16Value;
	if (pin < NUM_DIGITAL_PINS) {
		PinTableType* p;
		PinTableType pin_tbl;
		p =(PinTableType*)&pin_tbl;
		getPinTable(pin,p);
		if (*p->portRegisterAddr & p->mask) {
#if 0
			__asm __volatile(
				"movw %0, %1 \n"
				: "=r"(s16Value)
				: "i"(HIGH)
			);
			return s16Value;
#else
			return HIGH;
#endif
		}
	}

#if 0
	__asm __volatile(
		"movw %0, %1 \n"
		: "=r"(s16Value)
		: "i"(LOW)
	);
	return s16Value;
#else
	return LOW;
#endif
#else
	int value = 0;
	__asm __volatile(
	    "\n"
	    "        /* %%0 = %0 */                 \n"
	    "        /* %%1 = %1 */                 \n"
	    "        /* %%2 = %2 */                 \n"
	    "        /* %%3 = %3 */                 \n"
	    "        /* %%4 = %4 */                 \n"
	    "        /* %%5 = %5 */                 \n"
	    "        /* %%6 = %6 */                 \n"
	    "        mov     a, %2                  \n"
	    "        cmp     a, %3                  \n"
	    "        bnc     $9f                    \n"
	    "        mov     x, %4                  \n"
	    "        mulu    x                      \n"
	    "        movw    bc, ax                 \n"
	    "        movw    ax, %u5[bc]            \n"
	    "        movw    hl, ax                 \n"
	    "        mov     a, %u6[bc]             \n"
	    "        and     a, [hl]                \n"
	    "        add     a, #0xff               \n"
	    "        mov1    %1.0, cy               \n"
	    "9:                                     \n"
	    : "=r"(value)
	    : "r"(value),
	      "m"(pin),
	      "i"(NUM_DIGITAL_PINS),
	      "i"((unsigned)&PinTable[1] - (unsigned)&PinTable[0]),
	      "i"(&PinTable->portRegisterAddr),
	      "i"(&PinTable->mask)
	    : "a", "x", "b", "c", "h", "l"
	);
	return value;
#endif



#endif /*__RL78__*/
}

#ifdef __RL78__
/**********************************************************************************************************************
 * Function Name: disable input pin
 * Description  : Prohibits the input of the specified pin.
 * Arguments    : pin   - pin number
 * Return Value : -
 *********************************************************************************************************************/
void DisableDigitalInput(uint8_t pin)
{

	if (pin < NUM_DIGITAL_PINS) {
		PinTableType *p;
		PinTableType pin_tbl;
		p = (PinTableType*)&pin_tbl;

		getPinTable(pin,p);
		if (0 != p->pdidis){	/* can be changed */
			*p->portDigInputDisRegisterAddr |= (unsigned long)(0x1 << p->bit);	/* Input disable */
		}
	}
}

/**********************************************************************************************************************
 * Function Name: enable input pin
 * Description  : Allows the input of the specified pin.
 * Arguments    : pin   - pin number
 * Return Value : -
 *********************************************************************************************************************/
void EnableDigitalInput(uint8_t pin)
{

	if (pin < NUM_DIGITAL_PINS) {
		PinTableType *p;
		PinTableType pin_tbl;
		p = (PinTableType*)&pin_tbl;

		getPinTable(pin,p);
		if (0 != p->pdidis){	/* can be changed */
			*p->portDigInputDisRegisterAddr &= (unsigned long)~(0x1 << p->bit);	/* set Input enable */
		}
	}
}
#endif /*__RL78__*/

