/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

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
*/
/*
 * Mar 1st 2017: Modified for RL78/G13 by Yuuki Okamiya.
 */

#ifndef Arduino_h
#define Arduino_h

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <avr/pgmspace.h>

#ifndef __RL78__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif

#include "binary.h"

#ifdef __RL78__
#include "platform.h"

//#include "rl78/specific_instructions.h"
#include "utilities.h"

#include "r_cg_macrodriver.h"
#endif

#ifdef __RL78__
#define RLDUINO78_VERSION 0x0203
#define INTERRUPT
#define _BV(bit) (1 << (bit))
#define _HALT()		asm("halt;");
#define _STOP()		asm("stop;");

/* Software PWM 定義 */
#define SOFTWARE_PWM		0xF0
#define SW_PWM_TIMER        6
#define SWPWM_MIN           1024

#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ 					(32000000)	//!< CPUの動作周波数（RTOS未使用時に定義）
#endif

#define clockCyclesPerMicrosecond()			(configCPU_CLOCK_HZ / 1000000)				//!< CPUの動作周波数を1000000で割ったもの
#define clockCyclesToMicroseconds(cycle)	((cycle) / clockCyclesPerMicrosecond())		//!< サイクルあたりの時間[us]
#define microsecondsToClockCycles(us)		((us) * clockCyclesPerMicrosecond())		//!< 時間当たりのサイクル数


#define ANALOG_PIN_0		2		// ANI2
#define ANALOG_PIN_1		3		// ANI3
#define ANALOG_PIN_2		4		// ANI4
#define ANALOG_PIN_3		5		// ANI5
#define ANALOG_PIN_4		6		// ANI6
#define ANALOG_PIN_5		7		// ANI7
//#define ANALOG_PIN_6		18		// ANI18
//#define ANALOG_PIN_7		19		// ANI19

#define ANALOG_ADPC_OFFSET	4

#if 0
/* Deprecated: Use macros `CSI_CHANNEL{ 0, ..., 7 }` below instead. */
#define SPI_CHANNEL 		21		// CSI21
#define SPI2_CHANNEL		1       // CSI01
#endif
#ifdef GRADZUKI
#define SERVO_CHANNEL 		3		// TM03
#else
#define SERVO_CHANNEL 		3		// TM04
//#define SERVO_CHANNEL 		4		// TM04
#endif
#if 0
/* Deprecated: Use macros `IIC_CHANNEL{ 0, 1 }` below instead. */
#define I2C_CHANNEL 		0		// IICA0
#endif
#define UART_CHANNEL 		0		// UART0(Serial0)
//#define UART1_CHANNEL       1       // UART1(Serial1)
#define UART2_CHANNEL       2       // UART2(Serial2)
//#define HOOK_TIMER_CHANNEL  1    // Original
#define HOOK_TIMER_CHANNEL  7

/* Timer clock setting. */
#define TIMER_CLOCK			(0x0050)	// CK0 = 32MHz, CK1 = 1MHz, CK2 = 16MHz, CK3 = 125kHz
#define CLK_SOURCE_XT1 1
#define CLK_SOURCE_FIL 2
#define RTC_CLK_SOURCE CLK_SOURCE_XT1
//#define RTC_CLK_SOURCE CLK_SOURCE_FIL

#if (RTC_CLK_SOURCE == CLK_SOURCE_XT1)
#define INTERVAL		(33 - 1)	//!< インターバルタイマ割り込み周期（1 / 32.768kHz x 33   =   1.0070 ms)
#elif (RTC_CLK_SOURCE == CLK_SOURCE_FIL)
#define INTERVAL		(15 - 1)	//!< インターバルタイマ割り込み周期（1 / 15kHz x 15    =   1 ms)
#endif

#define MICROSECONDS_PER_TIMER05_OVERFLOW 0xffff //1us * 2 ^ 16
#define MILLISECONDS_PER_TIMER05_OVERFLOW (MICROSECONDS_PER_TIMER05_OVERFLOW / 1000)
#define INTERVAL_MICRO_TDR	(MICROSECONDS_PER_TIMER05_OVERFLOW - 1)
#define WAIT_XT1_CLOCK	1850000
/* Interval Micro Timer setting. */
#define INTERVAL_MICRO_MODE       (0x8000)    // Select CK1, Using Interrupt Handler
#define INTERVAL_FCLK_MODE        (0x0000)    // Select CKm0, Using Interrupt Handler

/* PWM setting. */
#define PWM_MASTER_CLOCK    (32000000)
//#define PWM_MASTER_CLOCK    (1000000)
#if PWM_MASTER_CLOCK == 32000000
#define PWM_MASTER_MODE		(0x0801)    // CK0を選択
#define PWM_SLAVE_MODE		(0x0409)
#elif PWM_MASTER_CLOCK == 1000000
#define PWM_MASTER_MODE		(0x8801)    // CK1を選択
#define PWM_SLAVE_MODE		(0x8409)
#endif
#define PWM_DEFAULT_FREQ    (490)       // 490Hz
#define PWM_TDR00			(PWM_MASTER_CLOCK / PWM_DEFAULT_FREQ - 1)

/* Tone setting. */
#define TONE_TIMER			PWM_PIN_3
#define TONE_MODE			(0xC000)    // CK3を選択
#define TONE_DURATION_INFINITY	(0xFFFFFFFF)

/* Output clock setting. */
#define OUTPUT_CLOCK_CKx	(32000000)
#define OUTPUT_CLOCK_MODE 	(0x0000)    // CK0を選択
#define OUTPUT_CLOCK_MIN	(245)
#define OUTPUT_CLOCK_MAX	(16000000)

/* Serial define */
#define USE_SMART_CONFIGRATOR (1)

/* SPI register define. */
#if ( SPI_CHANNEL == 0 )
#define SPI_SAUxEN			SAU0EN
#define SPI_SPSx			SPS0
#define SPI_STx 			ST0
#define SPI_SSx 			SS0
#define SPI_CHx 			0x0001
#define SPI_CSIMKxx 		CSIMK00
#define SPI_CSIIFxx 		CSIIF00
#define SPI_CSIPR1xx		CSIPR100
#define SPI_CSIPR0xx		CSIPR000
#define SPI_SIRxx			SIR00
#define SPI_SMRxx			SMR00
#define SPI_SCRxx			SCR00
#define SPI_SDRxx			SDR00
#define SPI_SOx 			SO0
#define SPI_SOEx			SOE0
#define SPI_SIOxx			SIO00

#elif ( SPI_CHANNEL == 21 )
#define SPI_SAUxEN			SAU1EN
#define SPI_SPSx			SPS1
#define SPI_STx 			ST1
#define SPI_SSx 			SS1
#define SPI_CHx 			0x0002
#define SPI_CSIMKxx 		CSIMK21
#define SPI_CSIIFxx 		CSIIF21
#define SPI_CSIPR1xx		CSIPR121
#define SPI_CSIPR0xx		CSIPR021
#define SPI_SIRxx			SIR11
#define SPI_SMRxx			SMR11
#define SPI_SCRxx			SCR11
#define SPI_SDRxx			SDR11
#define SPI_SOx 			SO1
#define SPI_SOEx			SOE1
#define SPI_SIOxx			SIO21

#endif

#if ( SPI2_CHANNEL == 1 )
#define SPI2_SAUxEN			SAU0EN
#define SPI2_SPSx			SPS0
#define SPI2_STx 			ST0
#define SPI2_SSx 			SS0
#define SPI2_CHx 			0x0002
#define SPI2_CSIMKxx 		CSIMK01
#define SPI2_CSIIFxx 		CSIIF01
#define SPI2_CSIPR1xx		CSIPR101
#define SPI2_CSIPR0xx		CSIPR001
#define SPI2_SIRxx			SIR01
#define SPI2_SMRxx			SMR01
#define SPI2_SCRxx			SCR01
#define SPI2_SDRxx			SDR01
#define SPI2_SOx 			SO0
#define SPI2_SOEx			SOE0
#define SPI2_SIOxx			SIO01

#endif

#ifdef WORKAROUND_READ_MODIFY_WRITE

#define SFR_ADM0	0xfff30
#define SFR_RTCC0	0xfff9d
#define SFR_RTCC1	0xfff9d
#define SFR_IF2		0xfffd0
#define SFR_IF2L	0xfffd0
#define SFR_IF2H	0xfffd1
#define SFR_IF3L	0xfffd2
#define SFR_MK2		0xfffd4
#define SFR_MK2L	0xfffd4
#define SFR_MK2H	0xfffd5
#define SFR_MK3L	0xfffd6
#define SFR_PR02	0xfffd8
#define SFR_PR02L	0xfffd8
#define SFR_PR02H	0xfffd9
#define SFR_PR03L	0xfffda
#define SFR_PR12	0xfffdc
#define SFR_PR12L	0xfffdd
#define SFR_PR12H	0xfffdd
#define SFR_PR13L	0xfffde
#define SFR_IF0		0xfffe0
#define SFR_IF0L	0xfffe0
#define SFR_IF0H	0xfffe1
#define SFR_IF1		0xfffe2
#define SFR_IF1L	0xfffe2
#define SFR_IF1H	0xfffe3
#define SFR_MK0		0xfffe4
#define SFR_MK0L	0xfffe4
#define SFR_MK0H    0xfffe5
#define SFR_MK1		0xfffe6
#define SFR_MK1L	0xfffe6
#define SFR_MK1H	0xfffe7
#define SFR_PR00	0xfffe8
#define SFR_PR00L	0xfffe8
#define SFR_PR00H	0xfffe9
#define SFR_PR01	0xfffea
#define SFR_PR01L	0xfffea
#define SFR_PR01H	0xfffeb
#define SFR_PR10	0xfffec
#define SFR_PR10L	0xfffec
#define SFR_PR10H	0xfffed
#define SFR_PR11	0xfffee
#define SFR_PR11L	0xfffee
#define SFR_PR11H	0xfffef

/*
#define SFR_MDAL    0xffff0
#define SFR_MDAH    0xffff2
#define SFR_MDBL    0xffff4
#define SFR_MDBH    0xffff6
#define SFR_PMC        0xffffe
*/

#define SFR2_ADM2	0xf0010

#define SFR2_PMC12	0xf006c
#define SFR2_PMC14	0xf006e

#define SFR2_PER0	0xf00f0

#define	SFR2_SS0	0xf0122
#define	SFR2_ST0	0xf0124
#define	SFR2_SO0L	0xf0128
#define	SFR2_SO0H	0xf0129
#define	SFR2_SOE0	0xf012a
#define	SFR2_SS1	0xf0162
#define	SFR2_ST1	0xf0164
#define	SFR2_SO1L	0xf0168
#define	SFR2_SO1H	0xf0169
#define	SFR2_SOE1	0xf016a

#define	SFR2_TSR02L	0xf01a4
#define	SFR2_TSR03L	0xf01a6
#define	SFR2_TSR04L	0xf01a8
#define	SFR2_TSR05L	0xf01aa
#define	SFR2_TSR06L	0xf01ac
#define	SFR2_TSR07L	0xf01ae
#define	SFR2_TE0L	0xf01b0
#define	SFR2_TS0L	0xf01b2
#define	SFR2_TT0L	0xf01b4
#define	SFR2_TPS0	0xf01b6
#define	SFR2_TO0L	0xf01b8
#define	SFR2_TOE0L	0xf01ba
#define	SFR2_TOL0L	0xf01bc
#define	SFR2_TOM0L	0xf01be

#define SFR_BIT_RTCE		7

#define SFR_BIT_ADCE		0
#define SFR_BIT_ADCS		7

#define SFR2_BIT_TAU0EN		0
#define SFR2_BIT_TAU1EN		1
#define SFR2_BIT_SAU0EN		2
#define SFR2_BIT_SAU1EN		3
#define SFR2_BIT_IICA0EN	4
#define SFR2_BIT_ADCEN		5
#define SFR2_BIT_IICA1EN	6
#define SFR2_BIT_RTCEN		7


#if ( SPI_CHANNEL == 0 )
#define	SFR2_STx 			SFR2_ST0
#define	SFR2_SSx 			SFR2_SS0
#define	SFR_MKxx 			SFR_MK0H
#define	SFR_IFxx 			SFR_IF0H
#define	SFR_PR1xx			SFR_PR10H
#define	SFR_PR0xx			SFR_PR00H
#define	SFR2_SOxL 			SFR2_SO0L
#define	SFR2_SOxH			SFR2_SO0H
#define	SFR2_SOEx			SFR2_SOE0

#define	SFR2_BIT_SAUxEN		SFR2_BIT_SAU0EN
#define	SFR_BIT_CSIMKxx		5
#define	SFR_BIT_CSIIFxx		5
#define	SFR_BIT_CSIPR1xx	5
#define	SFR_BIT_CSIPR0xx	5
#define	SFR2_BIT_STx		0
#define	SFR2_BIT_SSx		0
#define	SFR2_BIT_SOx		0
#define	SFR2_BIT_SOEx		0

#elif ( SPI_CHANNEL == 21 )
#define	SFR2_STx 			SFR2_ST1
#define	SFR2_SSx 			SFR2_SS1
#define	SFR_MKxx 			SFR_MK0H
#define	SFR_IFxx 			SFR_IF0H
#define	SFR_PR1xx			SFR_PR10H
#define	SFR_PR0xx			SFR_PR00H
#define	SFR2_SOxL 			SFR2_SO1L
#define	SFR2_SOxH			SFR2_SO1H
#define	SFR2_SOEx			SFR2_SOE1

#define	SFR2_BIT_SAUxEN		SFR2_BIT_SAU1EN
#define	SFR_BIT_CSIMKxx		1
#define	SFR_BIT_CSIIFxx		1
#define	SFR_BIT_CSIPR1xx	1
#define	SFR_BIT_CSIPR0xx	1
#define	SFR2_BIT_STx		1
#define	SFR2_BIT_SSx		1
#define	SFR2_BIT_SOx		1
#define	SFR2_BIT_SOEx		1

#endif

#if ( SPI2_CHANNEL == 1 )
#define	SFR22_STx 			SFR2_ST0
#define	SFR22_SSx 			SFR2_SS0
#define	SFR2_MKxx 			SFR_MK0H
#define	SFR2_IFxx 			SFR_IF0H
#define	SFR2_PR1xx			SFR_PR10H
#define	SFR2_PR0xx			SFR_PR00H
#define	SFR22_SOxL 			SFR2_SO0L
#define	SFR22_SOxH			SFR2_SO0H
#define	SFR22_SOEx			SFR2_SOE0

#define	SFR22_BIT_SAUxEN		SFR2_BIT_SAU0EN
#define	SFR2_BIT_CSIMKxx		6
#define	SFR2_BIT_CSIIFxx		6
#define	SFR2_BIT_CSIPR1xx	6
#define	SFR2_BIT_CSIPR0xx	6
#define	SFR22_BIT_STx		1
#define	SFR22_BIT_SSx		1
#define	SFR22_BIT_SOx		1
#define	SFR22_BIT_SOEx		1

#endif

#endif /*WORKAROUND_READ_MODIFY_WRITE*/
#endif /*__RL78__*/

#ifdef __cplusplus
extern "C"{
#endif

void yield(void);


#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2
#ifdef __RL78__
#define INPUT_TTL	0x3
#define INPUT_TTL_PULLUP	0x4
#define OUTPUT_OPENDRAIN	0x5
#endif

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  #define DEFAULT 0
  #define EXTERNAL 1
  #define INTERNAL1V1 2
  #define INTERNAL INTERNAL1V1
#elif defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  #define DEFAULT 0
  #define EXTERNAL 4
  #define INTERNAL1V1 8
  #define INTERNAL INTERNAL1V1
  #define INTERNAL2V56 9
  #define INTERNAL2V56_EXTCAP 13
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#define INTERNAL1V1 2
#define INTERNAL2V56 3
#elif defined(__RL78__)
/* Analog reference mode. */
#define DEFAULT			0x00
#define EXTERNAL		0x01
#define INTERNAL		0x02
#else
#define INTERNAL 3
#define DEFAULT 1
#define EXTERNAL 0
#endif

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) ((x)>0?(x):-(x))
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x)*(x))

//#define interrupts() sei()
//#define noInterrupts() cli()

#define interrupts()  EI()
#define noInterrupts()  DI()

#ifdef __RL78__
#define F_CPU (32 * 1000 * 1000L)
#endif

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) (bitvalue ? bitSet(value, bit) : bitClear(value, bit))

// avr-libc defines _NOP() since 1.6.2
#ifndef _NOP
#define _NOP() do { __asm__ volatile ("nop"); } while (0)
#endif

#ifndef __RL78__
typedef unsigned int word;
#else
typedef unsigned char	uint8_t;
typedef signed char     int8_t;
typedef unsigned short	uint16_t;
typedef signed short    int16_t;
typedef unsigned long   uint32_t;
typedef signed long     int32_t;
typedef uint8_t			byte;
typedef unsigned int	word;
typedef uint8_t			boolean;
#endif/*__RL78__*/

#define bit(b) (1UL << (b))

#ifndef __RL78__
typedef bool boolean;
typedef uint8_t byte;
#endif/*__RL78__*/

void init(void);
void initVariant(void);

int atexit(void (*func)()) __attribute__((weak));


void pinMode(uint8_t, uint8_t);
void digitalWrite(uint8_t, uint8_t);

int digitalRead(uint8_t);
#ifdef __RL78__
void DisableDigitalInput(uint8_t pin);
void EnableDigitalInput(uint8_t pin);
#endif
int analogRead(uint8_t analog_pin);

void analogReference(uint8_t mode);
void analogWrite(uint8_t pin, int value);
#ifdef __RL78__
void analogWriteFrequency(uint32_t Hz);
/* 1011 Nhu add */
void analogWritePinFrequency(uint8_t pin, uint32_t Hz);
/* 1011 Nhu add */
#endif

unsigned long millis(void);
unsigned long micros(void);
void delay(unsigned long ms);
void delayMicroseconds(unsigned long us);

#ifdef __RL78__
void set_starttime(void);
long set_endtime();
#endif/*__RL78__*/

unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);

//void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);

/* 1112 Nhu add */
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value);
void shiftOutEx(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t len, uint32_t value);
void tone(uint8_t pin, unsigned int frequency, unsigned long duration);
void noTone(uint8_t pin);
/* 1112 Nhu add */
/* 1118 nhu add */
#define TAU_FUNC_PWM	(1)
#define TAU_FUNC_MESURE_SIGNAL	(2)
#define TAU_FUNC_SQUARE_WAVE	(3)
/* 1118 nhu add */
void attachInterrupt(uint8_t, void (*)(void), int mode);
void detachInterrupt(uint8_t);

void setup();
void loop();

// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.

#define analogInPinToBit(P) (P)

// On the ATmega1280, the addresses of some of the port registers are
// greater than 255, so we can't store them in uint8_t's.
#ifndef __RL78__
extern const uint16_t PROGMEM port_to_mode_PGM[];
extern const uint16_t PROGMEM port_to_input_PGM[];
extern const uint16_t PROGMEM port_to_output_PGM[];

extern const uint8_t PROGMEM digital_pin_to_port_PGM[];
// extern const uint8_t PROGMEM digital_pin_to_bit_PGM[];
extern const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[];
extern const uint8_t PROGMEM digital_pin_to_timer_PGM[];
// Get the bit location within the hardware port of the given virtual pin.
// This comes from the pins_*.c file for the active board configuration.
//
// These perform slightly better as macros compared to inline functions
//
#define digitalPinToPort(P) ( pgm_read_byte( digital_pin_to_port_PGM + (P) ) )
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) )
#define digitalPinToTimer(P) ( pgm_read_byte( digital_pin_to_timer_PGM + (P) ) )
#define analogInPinToBit(P) (P)
#endif

#ifndef __RL78__
#ifndef __RL78__
#define portOutputRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_output_PGM + (P))) )
#define portInputRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_input_PGM + (P))) )
#else
#define portOutputRegister(P) ( (volatile uint8_t *)( 0xFFF00 + (P)) )
#define portInputRegister(P) ( (volatile uint8_t *)( 0xFFF00 + (P)) )
#endif
#define portModeRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_mode_PGM + (P))) )
#endif

#ifndef __RL78__
#define NOT_A_PIN 0
#define NOT_A_PORT 0
#else
#define NOT_A_PIN 0xff
#define NOT_A_PORT 0xff
#endif /*__RL78__*/

#define NOT_AN_INTERRUPT -1

#ifdef ARDUINO_MAIN
#define PA 1
#define PB 2
#define PC 3
#define PD 4
#define PE 5
#define PF 6
#define PG 7
#define PH 8
#define PJ 10
#define PK 11
#define PL 12
#endif

#define NOT_ON_TIMER 0
#define TIMER0A 1
#define TIMER0B 2
#define TIMER1A 3
#define TIMER1B 4
#define TIMER1C 5
#define TIMER2  6
#define TIMER2A 7
#define TIMER2B 8

#define TIMER3A 9
#define TIMER3B 10
#define TIMER3C 11
#define TIMER4A 12
#define TIMER4B 13
#define TIMER4C 14
#define TIMER4D 15
#define TIMER5A 16
#define TIMER5B 17
#define TIMER5C 18

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include "WCharacter.h"
#include "WString.h"
#include "HardwareSerial.h"


#ifndef __RL78__
#include "USBAPI.h"
#endif/*__RL78__*/
#if defined(HAVE_HWSERIAL0) && defined(HAVE_CDCSERIAL)
#error "Targets with both UART0 and CDC serial not supported"
#endif

uint16_t makeWord(uint16_t w);
uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

//unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
//unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
//
//void tone(uint8_t _pin, unsigned int frequency, unsigned long duration = 0);
//void noTone(uint8_t _pin);

// WMath prototypes
long random(long);
long random(long, long);
void randomSeed(unsigned long);
long map(long, long, long, long, long);

#endif /*  __cplusplus  */

#include "pins_arduino.h"
#include "pintable.h"

/* SPI(CSI) Definition */
#define USE_CSI      (1) // Set to '1' when Use SPI Hardware.

#if defined(USE_CSI) && USE_CSI

//#define CSI_CHANNEL0 (0) // USE CSI00 for SPI
//#define CSI_CHANNEL1 (1) // USE CSI01 for SPI
//#define CSI_CHANNEL2 (2) // USE CSI10 for SPI
  #define CSI_CHANNEL3 (3) // USE CSI11 for SPI
//#define CSI_CHANNEL4 (4) // USE CSI20 for SPI
//#define CSI_CHANNEL5 (5) // USE CSI21 for SPI
//#define CSI_CHANNEL6 (6) // USE CSI30 for SPI
//#define CSI_CHANNEL7 (7) // USE CSI31 for SPI

#endif /* defined(USE_CSI) && USE_CSI */

#if 0 /* Turn off when SPI Driver was ready */
#if (defined(CSI_CHANNEL0) & (CSI_CHANNEL0==0)) | (CSI_CHANNEL1==1) | (CSI_CHANNEL2==2) | (CSI_CHANNEL3==3) | \
    (CSI_CHANNEL4==4) | (CSI_CHANNEL5==5) | (CSI_CHANNEL6==6) | (CSI_CHANNEL7==7)
		/*
		 * FIXME:
		 * If include `SPI.h` here in `Arduino.h`,
		 * it fails to compile due to C sources including `Arduino.h`,
		 * that does not support C++ syntax.
		 *
		 * Instead, include it in `main.cpp`.
		 */
		#include <SPI.h>
#endif
#endif /* SPI */

/* IIC Definition */
#define IIC_CHANNEL0 (0)
#define IIC_CHANNEL1 (1)
#if 0 /* Turn off when Wire Driver was ready */
#if (defined(IIC_CHANNEL0) & (IIC_CHANNEL0==0)) | (IIC_CHANNEL1==1)
		/*
		 * FIXME:
		 * If include `Wire.h` here in `Arduino.h`,
		 * it fails to compile due to C sources including `Arduino.h`,
		 * that does not support C++ syntax.
		 *
		 * Instead, include it in `main.cpp`.
		 */
		#include <Wire.h>
#endif
#endif /* IIC */

#ifdef __RL78__
#define ISP_LEVEL_3 (3)
#define ISP_LEVEL_2 (2)
#define ISP_LEVEL_1 (1)
#define ISP_LEVEL_0 (0)

#define GET_PSW_ISP()  (__builtin_rl78_getpswisp ())
#endif


#endif /* ARDUINO_H */
