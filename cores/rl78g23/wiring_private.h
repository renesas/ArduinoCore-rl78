/*
  wiring_private.h - Internal header file.
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

  $Id: wiring.h 239 2007-01-12 17:58:39Z mellis $
*/
/*
  Modified 13 July 2014 by Nozomu Fujita for GR-SAKURA
  Modified 1  Mar  2017 by Yuuki Okamiya for RL78/G13
*/

#ifndef WiringPrivate_h
#define WiringPrivate_h

#ifndef __RL78__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif/*__RL78__*/
#include <stdio.h>
#include <stdarg.h>

#include "Arduino.h"

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __RL78__
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define EXTERNAL_INT_0 0
#define EXTERNAL_INT_1 1
#define EXTERNAL_INT_2 2
#define EXTERNAL_INT_3 3
#define EXTERNAL_INT_4 4
#define EXTERNAL_INT_5 5
#define EXTERNAL_INT_6 6
#define EXTERNAL_INT_7 7

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define EXTERNAL_NUM_INTERRUPTS 8
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#define EXTERNAL_NUM_INTERRUPTS 3
#elif defined(__AVR_ATmega32U4__)
#define EXTERNAL_NUM_INTERRUPTS 5
#else
#define EXTERNAL_NUM_INTERRUPTS 2
#endif
#else
#define ANALOG_ADPC_OFFSET	4
#define ANALOG_PIN_START_NUMBER	(51)
#define MAX_CYCLIC_HANDLER 		(8)

/* 1112 Ueeda add */
#define EXTERNAL_NUM_INTERRUPTS (6)
/* 1112 Ueeda add */

/* PWM defines. */
#define PWM_MIN			0
#define PWM_MAX			255

/* 1112 Ueeda add */
/* External interrupt define. */
#define EXTERNAL_INTERRUPT_0	4
#define EXTERNAL_INTERRUPT_1	6
#define EXTERNAL_INTERRUPT_2	7
#define EXTERNAL_INTERRUPT_3    11
#define EXTERNAL_INTERRUPT_4    12
#define EXTERNAL_INTERRUPT_5    13

fInterruptFunc_t g_afInterruptFuncTable[EXTERNAL_NUM_INTERRUPTS] __attribute__((weak));
/* 1112 Ueeda add */

#define CYCLE_VALUE	(0)
	
typedef struct {
    uint8_t valid:1;
    uint8_t pin:7;
    uint8_t value;
    volatile uint8_t* port;
    uint8_t mask;
    uint8_t newValue;
} SwPwm;

/* 1008 Mitsugi add */
typedef struct {
    void (*open)();
	void (*start)();
	uint16_t cycle;
} Pwm_func;

#define	PWM_CH_NUM	(4)

int8_t get_pwm_channel(uint8_t pwm_num);

int8_t get_analog_channel(uint8_t analog_num);

/* 1008 Mitsugi add */

/* 1027 Nhu add */
#define FREQUENCY_MIN_VAL	(500)
#define FREQUENCY_MAX_VAL	(8000000)
/* 1027 Nhu add */

/* 1112 Nhu add */

#define TONE_CH_NUM				(7)
#define PULSE_IN_CH_NUM			(7)
#define TAU_OPERATION_CLOCK		(0xC000U)    /* operation clock set by PRS register */
#define CK00_CK01_OPERATION		(0x000F)	/* Selection of operation clock CK00, CK01 */
#define CK02_OPERATION			(0x0300)	/* Selection of operation clock CK02 */
#define CK03_OPERATION			(0x3000)	/* Selection of operation clock CK03 */
#define TIMEOUT_MAX_VAL			(65535)
#define PULSE_INTERUPT			(1)

typedef struct {
    void (*open)();
	void (*start)();
	void (*stop)();
} tone_func;

int8_t get_tone_channel(uint8_t tone_num);

typedef struct {
    void (*open)();
	void (*start)();
	void (*stop)();
	void (*get_width)(uint32_t * const width);
} pulse_in_func;

int8_t get_pulse_in_channel(uint8_t pulse_in_num);

/* 1112 Nhu add */


#endif/*__RL78__*/

typedef void (*voidFuncPtr)(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
