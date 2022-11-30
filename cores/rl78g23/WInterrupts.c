/* -*- mode: jde; c-basic-offset: 2; indent-tabs-mode: nil -*- */

/*
  Part of the Wiring project - http://wiring.uniandes.edu.co

  Copyright (c) 2004-05 Hernando Barragan

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
  
  Modified 24 November 2006 by David A. Mellis
  Modified 1 August 2010 by Mark Sproul
*/
/*
 * Mar 1st 2017 : Modified for RL78/G13 by Yuuki Okamiya.
 */

#include <inttypes.h>
#ifndef __RL78__
#include <avr/io.h>
#include <avr/interrupt.h>
#endif /*__RL78__*/
#include <avr/pgmspace.h>
#include <stdio.h>

#include "wiring_private.h"

/* 1108 Ueeda add */
#include "r_smc_entry.h"
//#include "iodefine.h"
#include "platform.h"
/* 1108 Ueeda add */

#ifndef __RL78__
static volatile voidFuncPtr intFunc[EXTERNAL_NUM_INTERRUPTS];
// volatile static voidFuncPtr twiIntFunc;
#endif

#ifdef __RL78__


/* 1108 Ueeda add */

typedef struct {
    void (*begin)();
    void (*mode)(uint8_t interruptNum, int mode);
    void (*start)();
    void (*stop)(uint8_t interruptNum);
} Interrupts_func;

Interrupts_func Int_func =
{
    .begin  = (void*)R_Config_INTC_Create,
    .mode = (void*)R_Config_INTC_Create_Mode,
    .start = (void*)R_Config_INTC_INTP_Start,
    .stop = (void*)R_Config_INTC_INTP_Stop
};

static bool IsFirst = true;

/* 1108 Ueeda add */

#endif

void attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode) {
#ifndef __RL78__
    if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {
        intFunc[interruptNum] = userFunc;

        // Configure the interrupt mode (trigger on low input, any change, rising
        // edge, or falling edge).  The mode constants were chosen to correspond
        // to the configuration bits in the hardware register, so we simply shift
        // the mode into place.

        // Enable the interrupt.

        switch (interruptNum) {
    #if defined(__AVR_ATmega32U4__)
        // I hate doing this, but the register assignment differs between the 1280/2560
        // and the 32U4.  Since avrlib defines registers PCMSK1 and PCMSK2 that aren't
        // even present on the 32U4 this is the only way to distinguish between them.
        case 0:
            EICRA = (EICRA & ~((1<<ISC00) | (1<<ISC01))) | (mode << ISC00);
            EIMSK |= (1<<INT0);
            break;
        case 1:
            EICRA = (EICRA & ~((1<<ISC10) | (1<<ISC11))) | (mode << ISC10);
            EIMSK |= (1<<INT1);
            break;
        case 2:
            EICRA = (EICRA & ~((1<<ISC20) | (1<<ISC21))) | (mode << ISC20);
            EIMSK |= (1<<INT2);
            break;
        case 3:
            EICRA = (EICRA & ~((1<<ISC30) | (1<<ISC31))) | (mode << ISC30);
            EIMSK |= (1<<INT3);
            break;
        case 4:
            EICRB = (EICRB & ~((1<<ISC60) | (1<<ISC61))) | (mode << ISC60);
            EIMSK |= (1<<INT6);
            break;
    #elif defined(EICRA) && defined(EICRB) && defined(EIMSK)
        case 2:
            EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
            EIMSK |= (1 << INT0);
            break;
        case 3:
            EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
            EIMSK |= (1 << INT1);
            break;
        case 4:
            EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
            EIMSK |= (1 << INT2);
            break;
        case 5:
            EICRA = (EICRA & ~((1 << ISC30) | (1 << ISC31))) | (mode << ISC30);
            EIMSK |= (1 << INT3);
            break;
        case 0:
            EICRB = (EICRB & ~((1 << ISC40) | (1 << ISC41))) | (mode << ISC40);
            EIMSK |= (1 << INT4);
            break;
        case 1:
            EICRB = (EICRB & ~((1 << ISC50) | (1 << ISC51))) | (mode << ISC50);
            EIMSK |= (1 << INT5);
            break;
        case 6:
            EICRB = (EICRB & ~((1 << ISC60) | (1 << ISC61))) | (mode << ISC60);
            EIMSK |= (1 << INT6);
            break;
        case 7:
            EICRB = (EICRB & ~((1 << ISC70) | (1 << ISC71))) | (mode << ISC70);
            EIMSK |= (1 << INT7);
            break;
    #else
        case 0:
        #if defined(EICRA) && defined(ISC00) && defined(EIMSK)
            EICRA = (EICRA & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
            EIMSK |= (1 << INT0);
        #elif defined(MCUCR) && defined(ISC00) && defined(GICR)
            MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
            GICR |= (1 << INT0);
        #elif defined(MCUCR) && defined(ISC00) && defined(GIMSK)
            MCUCR = (MCUCR & ~((1 << ISC00) | (1 << ISC01))) | (mode << ISC00);
            GIMSK |= (1 << INT0);
        #else
          #error attachInterrupt not finished for this CPU (case 0)
        #endif
            break;

        case 1:
        #if defined(EICRA) && defined(ISC10) && defined(ISC11) && defined(EIMSK)
            EICRA = (EICRA & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
            EIMSK |= (1 << INT1);
        #elif defined(MCUCR) && defined(ISC10) && defined(ISC11) && defined(GICR)
            MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
            GICR |= (1 << INT1);
        #elif defined(MCUCR) && defined(ISC10) && defined(GIMSK) && defined(GIMSK)
            MCUCR = (MCUCR & ~((1 << ISC10) | (1 << ISC11))) | (mode << ISC10);
            GIMSK |= (1 << INT1);
        #else
          #warning attachInterrupt may need some more work for this cpu (case 1)
        #endif
            break;

        case 2:
        #if defined(EICRA) && defined(ISC20) && defined(ISC21) && defined(EIMSK)
            EICRA = (EICRA & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
            EIMSK |= (1 << INT2);
        #elif defined(MCUCR) && defined(ISC20) && defined(ISC21) && defined(GICR)
            MCUCR = (MCUCR & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
            GICR |= (1 << INT2);
        #elif defined(MCUCR) && defined(ISC20) && defined(GIMSK) && defined(GIMSK)
            MCUCR = (MCUCR & ~((1 << ISC20) | (1 << ISC21))) | (mode << ISC20);
            GIMSK |= (1 << INT2);
        #endif
            break;
    #endif
        }
    }

#else

    if (interruptNum < EXTERNAL_NUM_INTERRUPTS) {
        /* ユーザー定義割り込みハンドラの登録 */
        g_afInterruptFuncTable[interruptNum] = userFunc;
        /* 1108 Ueeda add */
        if(IsFirst){
            Int_func.begin();
            IsFirst = false;
        }
        Int_func.mode(interruptNum, mode);
            /* 1108 Ueeda add */
                /* 割り込み要因のクリア＆割り込みマスクを許可 */
    #ifdef WORKAROUND_READ_MODIFY_WRITE
    #if EXTERNAL_INTERRUPT_0 == 0
        SBI(SFR_PR00L, 2);
        SBI(SFR_PR10L, 2);
        CBI(SFR_IF0L,  2);
        CBI(SFR_MK0L,  2);
    #elif EXTERNAL_INTERRUPT_0 == 1
        SBI(SFR_PR00L, 3);
        SBI(SFR_PR10L, 3);
        CBI(SFR_IF0L,  3);
        CBI(SFR_MK0L,  3);
    #elif EXTERNAL_INTERRUPT_0 == 2
        SBI(SFR_PR00L, 4);
        SBI(SFR_PR10L, 4);
        CBI(SFR_IF0L,  4);
        CBI(SFR_MK0L,  4);
    #elif EXTERNAL_INTERRUPT_0 == 3
        SBI(SFR_PR00L, 5);
        SBI(SFR_PR10L, 5);
        CBI(SFR_IF0L,  5);
        CBI(SFR_MK0L,  5);
    #elif EXTERNAL_INTERRUPT_0 == 4
        SBI(SFR_PR00L, 6);
        SBI(SFR_PR10L, 6);
        CBI(SFR_IF0L,  6);
        CBI(SFR_MK0L,  6);
        PIF4 = 0;    PMK4 = 0;
    #elif EXTERNAL_INTERRUPT_0 == 5
        SBI(SFR_PR00L, 7);
        SBI(SFR_PR10L, 7);
        CBI(SFR_IF0L,  7);
        CBI(SFR_MK0L,  7);
    #endif
    #else    /* WORKAROUND_READ_MODIFY_WRITE */
        /* 1108 Ueeda add */
        Int_func.start();
        /* 1108 Ueeda add */
    #endif

    }
#endif //__RL78__
}

void detachInterrupt(uint8_t interruptNum) {
#ifndef __RL78__
      if(interruptNum < EXTERNAL_NUM_INTERRUPTS) {
        // Disable the interrupt.  (We can't assume that interruptNum is equal
        // to the number of the EIMSK bit to clear, as this isn't true on the
        // ATmega8.  There, INT0 is 6 and INT1 is 7.)
        switch (interruptNum) {
    #if defined(__AVR_ATmega32U4__)
        case 0:
            EIMSK &= ~(1<<INT0);
            break;
        case 1:
            EIMSK &= ~(1<<INT1);
            break;
        case 2:
            EIMSK &= ~(1<<INT2);
            break;
        case 3:
            EIMSK &= ~(1<<INT3);
            break;
        case 4:
            EIMSK &= ~(1<<INT6);
            break;
    #elif defined(EICRA) && defined(EICRB) && defined(EIMSK)
        case 2:
          EIMSK &= ~(1 << INT0);
          break;
        case 3:
          EIMSK &= ~(1 << INT1);
          break;
        case 4:
          EIMSK &= ~(1 << INT2);
          break;
        case 5:
          EIMSK &= ~(1 << INT3);
          break;
        case 0:
          EIMSK &= ~(1 << INT4);
          break;
        case 1:
          EIMSK &= ~(1 << INT5);
          break;
        case 6:
          EIMSK &= ~(1 << INT6);
          break;
        case 7:
          EIMSK &= ~(1 << INT7);
          break;
    #else
        case 0:
        #if defined(EIMSK) && defined(INT0)
          EIMSK &= ~(1 << INT0);
        #elif defined(GICR) && defined(ISC00)
          GICR &= ~(1 << INT0); // atmega32
        #elif defined(GIMSK) && defined(INT0)
          GIMSK &= ~(1 << INT0);
        #else
          #error detachInterrupt not finished for this cpu
        #endif
          break;

        case 1:
        #if defined(EIMSK) && defined(INT1)
          EIMSK &= ~(1 << INT1);
        #elif defined(GICR) && defined(INT1)
          GICR &= ~(1 << INT1); // atmega32
        #elif defined(GIMSK) && defined(INT1)
          GIMSK &= ~(1 << INT1);
        #else
          #warning detachInterrupt may need some more work for this cpu (case 1)
        #endif
          break;

        case 2:
        #if defined(EIMSK) && defined(INT2)
          EIMSK &= ~(1 << INT2);
        #elif defined(GICR) && defined(INT2)
          GICR &= ~(1 << INT2); // atmega32
        #elif defined(GIMSK) && defined(INT2)
          GIMSK &= ~(1 << INT2);
        #elif defined(INT2)
          #warning detachInterrupt may need some more work for this cpu (case 2)
        #endif
          break;
    #endif
        }

        intFunc[interruptNum] = nothing;
      }
    #else
        if (interruptNum < EXTERNAL_NUM_INTERRUPTS) {
            /* 1108 Ueeda add */
            Int_func.stop(interruptNum);
            /* 1108 Ueeda add */
            /* ユーザー定義割り込みハンドラの登録解除 */
            g_afInterruptFuncTable[interruptNum] = NULL;
    #endif
    }
}
/*
void attachInterruptTwi(void (*userFunc)(void) ) {
  twiIntFunc = userFunc;
}
*/

#if defined(__AVR_ATmega32U4__)
ISR(INT0_vect) {
    if(intFunc[EXTERNAL_INT_0])
        intFunc[EXTERNAL_INT_0]();
}

ISR(INT1_vect) {
    if(intFunc[EXTERNAL_INT_1])
        intFunc[EXTERNAL_INT_1]();
}

ISR(INT2_vect) {
    if(intFunc[EXTERNAL_INT_2])
        intFunc[EXTERNAL_INT_2]();
}

ISR(INT3_vect) {
    if(intFunc[EXTERNAL_INT_3])
        intFunc[EXTERNAL_INT_3]();
}

ISR(INT6_vect) {
    if(intFunc[EXTERNAL_INT_4])
        intFunc[EXTERNAL_INT_4]();
}

#elif defined(EICRA) && defined(EICRB)

ISR(INT0_vect) {
  if(intFunc[EXTERNAL_INT_2])
    intFunc[EXTERNAL_INT_2]();
}

ISR(INT1_vect) {
  if(intFunc[EXTERNAL_INT_3])
    intFunc[EXTERNAL_INT_3]();
}

ISR(INT2_vect) {
  if(intFunc[EXTERNAL_INT_4])
    intFunc[EXTERNAL_INT_4]();
}

ISR(INT3_vect) {
  if(intFunc[EXTERNAL_INT_5])
    intFunc[EXTERNAL_INT_5]();
}

ISR(INT4_vect) {
  if(intFunc[EXTERNAL_INT_0])
    intFunc[EXTERNAL_INT_0]();
}

ISR(INT5_vect) {
  if(intFunc[EXTERNAL_INT_1])
    intFunc[EXTERNAL_INT_1]();
}

ISR(INT6_vect) {
  if(intFunc[EXTERNAL_INT_6])
    intFunc[EXTERNAL_INT_6]();
}

ISR(INT7_vect) {
  if(intFunc[EXTERNAL_INT_7])
    intFunc[EXTERNAL_INT_7]();
}

#else
#endif

#ifndef __RL78__
ISR(INT0_vect) {
  if(intFunc[EXTERNAL_INT_0])
    intFunc[EXTERNAL_INT_0]();
}

ISR(INT1_vect) {
  if(intFunc[EXTERNAL_INT_1])
    intFunc[EXTERNAL_INT_1]();
}
#else

 //__RL78__
// INTERRUPT HANDLERS *********************************************************/
// NMI and IRQ interrupt handlers. Note that all of these are declared in
// interrupts_handlers.h but defined here for clarity.
/**
 * 外部割込みハンドラ0
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
INTERRUPT void external_interrupt_0(void)
{
    if (g_afInterruptFuncTable[0] != NULL) {
        (*g_afInterruptFuncTable[0])();
    }
}

/**
 * 外部割込みハンドラ1
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
INTERRUPT void external_interrupt_1(void)
{
    if (g_afInterruptFuncTable[1] != NULL) {
        (*g_afInterruptFuncTable[1])();
    }
}

/**
 * 外部割込みハンドラ2
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
INTERRUPT void external_interrupt_2(void)
{
    if (g_afInterruptFuncTable[2] != NULL) {
        (*g_afInterruptFuncTable[2])();
    }
}

#endif

/*
ISR(TWI_vect) {
  if(twiIntFunc)
    twiIntFunc();
}
*/

