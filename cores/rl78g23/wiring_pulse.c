/*
  wiring_pulse.c - pulseIn() function
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

  $Id: wiring.c 248 2007-02-03 15:36:30Z mellis $
*/
/*
 * Modified  5 Mar  2017 by Yuuki Okamiya for RL78/G13
　* Modified 18 Mar  2017 by Nozomu Fujita for pulseInWait, pulseInCount
*/

#include "wiring_private.h"
#include "pins_arduino.h"
#include "pintable.h"
/* 1112 nhu add */
#include "r_smc_entry.h"
/* 1112 nhu add */
#ifdef __RL78__
/* 1112 nhu add */
extern volatile uint8_t g_tau0_ch0_interrupt_flag;
extern volatile uint8_t g_tau0_ch1_interrupt_flag;
extern volatile uint8_t g_tau0_ch2_interrupt_flag;
extern volatile uint8_t g_tau0_ch3_interrupt_flag;
extern volatile uint8_t g_tau0_ch4_interrupt_flag;
extern volatile uint8_t g_tau0_ch5_interrupt_flag;
extern volatile uint8_t g_tau0_ch6_interrupt_flag;
extern volatile uint8_t g_tau0_ch7_interrupt_flag;

extern uint32_t R_BSP_GetFclkFreqHz(void);


volatile uint32_t g_pulse_enable_interrupt_flag = 0;
volatile unsigned short *g_timer_pulse_mode_reg[PULSE_IN_CH_NUM] = {&TMR01,&TMR02,&TMR03,&TMR04,&TMR05,&TMR06,&TMR07};
volatile unsigned short *g_timer_pulse_clock_select_reg = &TPS0;
volatile unsigned short *g_timer_timeout_data_reg = &TDR00;
volatile unsigned short *g_timer_timeout_mode_reg = &TMR00;
const uint8_t  pulse_in_channel_table[PULSE_IN_CH_NUM]  = {PWM_PIN_32,PWM_PIN_31,PWM_PIN_6,PWM_PIN_3,PWM_PIN_10,PWM_PIN_9,PWM_PIN_5};
pulse_in_func pulse_in_ch[PULSE_IN_CH_NUM] =
{
	{
		.open  = (void*)R_Config_TAU0_0_1_Mesure_Signal_Create,
		.start = (void*)R_Config_TAU0_0_1_Mesure_Signal_Start,
		.stop = (void*)R_Config_TAU0_0_1_Mesure_Signal_Stop,
		.get_width = (void*)R_Config_TAU0_1_Mesure_Signal_Get_PulseWidth,
	},
	{
		.open  = (void*)R_Config_TAU0_0_2_Mesure_Signal_Create,
		.start = (void*)R_Config_TAU0_0_2_Mesure_Signal_Start,
		.stop = (void*)R_Config_TAU0_0_2_Mesure_Signal_Stop,
		.get_width = (void*)R_Config_TAU0_2_Mesure_Signal_Get_PulseWidth,
	},
	{
		.open  = (void*)R_Config_TAU0_0_3_Mesure_Signal_Create,
		.start = (void*)R_Config_TAU0_0_3_Mesure_Signal_Start,
		.stop = (void*)R_Config_TAU0_0_3_Mesure_Signal_Stop,
		.get_width = (void*)R_Config_TAU0_3_Mesure_Signal_Get_PulseWidth,
	},
	{
		.open  = (void*)R_Config_TAU0_0_4_Mesure_Signal_Create,
		.start = (void*)R_Config_TAU0_0_4_Mesure_Signal_Start,
		.stop = (void*)R_Config_TAU0_0_4_Mesure_Signal_Stop,
		.get_width = (void*)R_Config_TAU0_4_Mesure_Signal_Get_PulseWidth,
	},
	{
		.open  = (void*)R_Config_TAU0_0_5_Mesure_Signal_Create,
		.start = (void*)R_Config_TAU0_0_5_Mesure_Signal_Start,
		.stop = (void*)R_Config_TAU0_0_5_Mesure_Signal_Stop,
		.get_width = (void*)R_Config_TAU0_5_Mesure_Signal_Get_PulseWidth,
	},
	{
		.open  = (void*)R_Config_TAU0_0_6_Mesure_Signal_Create,
		.start = (void*)R_Config_TAU0_0_6_Mesure_Signal_Start,
		.stop = (void*)R_Config_TAU0_0_6_Mesure_Signal_Stop,
		.get_width = (void*)R_Config_TAU0_6_Mesure_Signal_Get_PulseWidth,
	},
	{
		.open  = (void*)R_Config_TAU0_0_7_Mesure_Signal_Create,
		.start = (void*)R_Config_TAU0_0_7_Mesure_Signal_Start,
		.stop = (void*)R_Config_TAU0_0_7_Mesure_Signal_Stop,
		.get_width = (void*)R_Config_TAU0_7_Mesure_Signal_Get_PulseWidth,
	}
};

int8_t get_pulse_in_channel(uint8_t pulse_in_num)
{
	uint8_t pulse_in_cnt;

	for(pulse_in_cnt=0;pulse_in_cnt<PULSE_IN_CH_NUM;pulse_in_cnt++)
	{
		if (pulse_in_num == pulse_in_channel_table[pulse_in_cnt])
		{
			return pulse_in_cnt;
		}
	}
	return -1;
}

static uint32_t get_timer_frequency(uint32_t clock_mode);
/* 1112 nhu add */

static const uint16_t PulseInWaitCycles = 1 + 1 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 4;

static bool pulseInWait(
	volatile uint8_t* Px,
	uint8_t u8Bit,
	uint8_t u8StateMask,
	unsigned long* u32TimeoutCycles
) {
	bool ret;
#if 1
	const unsigned char u16PulseInWaitCycles = 30;
	while ((*Px & u8Bit) == u8StateMask) {
		if (*u32TimeoutCycles >= u16PulseInWaitCycles) {
			*u32TimeoutCycles -= u16PulseInWaitCycles;
		} else {
			ret = true;
			break;
		}
	}
	ret = false;

#else
	__asm __volatile(
		"	clrb	%0					\n"
		"	movw	de, %1					\n"
		"	mov	a, %2					\n"
		"	mov	b, a					\n"
		"	mov	a, %3					\n"
		"	mov	c, a					\n"
		"	movw	hl, %4					\n"
		"1:							\n"
		"	mov	a, [de]				;1	\n"
		"	and	a, b				;1	\n"
		"	cmp	a, c				;1	\n"
		"	bnz	$2f				;2/4	\n"
		"	movw	ax, [hl]			;1	\n"
		"	subw	ax, %5				;1	\n"
		"	movw	[hl], ax			;1	\n"
		"	movw	ax, [hl+2]			;1	\n"
		"	sknc					;1	\n"
		"	subw	ax, #1				;1	\n"
		"	movw	[hl+2], ax			;1	\n"
		"	bnc	$1b				;2/4	\n"
		"	oneb	%0					\n"
		"2:		 					\n"
		:"=&r"(ret)
		:"r"(Px), "r"(u8Bit), "r"(u8StateMask), "r"(u32TimeoutCycles), "i"(PulseInWaitCycles)
		:"ax", "bc", "de", "hl"
	);
#endif
	return ret;
}

static const uint16_t PulseInCountCycles = 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 4;

static bool pulseInCount(
	volatile uint8_t* Px,
	uint8_t u8Bit,
	uint8_t u8StateMask,
	unsigned long u32TimeoutCycles,
	unsigned long* u32PulseCycles
) {
	bool ret;
#if 1
	const unsigned long u16PulseInCountCycles = 35;
	while ((*Px & u8Bit) == u8StateMask) {
		if (u32TimeoutCycles >= u16PulseInCountCycles) {
			u32TimeoutCycles -= u16PulseInCountCycles;
		} else {
			ret = true;
			break;
		}
		*u32PulseCycles += u16PulseInCountCycles;
	}
	ret = false;
#else
	__asm __volatile(
		"	clrb	%0					\n"
		"	movw	de, %1					\n"
		"	mov	a, %2					\n"
		"	mov	b, a					\n"
		"	mov	a, %3					\n"
		"	mov	c, a					\n"
		"	movw	hl, %5					\n"
		"	br	$2f					\n"
		"1:							\n"
		"	movw	ax, [hl]			;1	\n"
		"	addw	ax, %7				;1	\n"
		"	movw	[hl], ax			;1	\n"
		"	movw	ax, [hl+2]			;1	\n"
		"	sknc					;1	\n"
		"	incw	ax				;1	\n"
		"	movw	[hl+2], ax			;1	\n"
		"2:							\n"
		"	mov	a, [de]				;1	\n"
		"	and	a, b				;1	\n"
		"	cmp	a, c				;1	\n"
		"	bnz	$3f				;2/4	\n"
		"	movw	ax, %4+0			;1	\n"
		"	subw	ax, %7				;1	\n"
		"	movw	%4+0, ax			;1	\n"
		"	movw	ax, %4+2			;1	\n"
		"	sknc					;1	\n"
		"	subw	ax, #1				;1	\n"
		"	movw	%4+2, ax			;1	\n"
		"	bnc	$1b				;2/4	\n"
		"	oneb	%0					\n"
		"3:		 					\n"
		:"=&r"(ret)
		:"r"(Px), "r"(u8Bit), "r"(u8StateMask), "r"(u32TimeoutCycles), "r"(u32PulseCycles), "i"(PulseInWaitCycles), "i"(PulseInCountCycles)
		:"ax", "bc", "de", "hl"
	);
#endif
	return ret;
}

#endif
/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
#ifndef __RL78__
	// cache the port and bit of the pin in order to speed up the
	// pulse width measuring loop and achieve finer resolution.  calling
	// digitalRead() instead yields much coarser resolution.
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	uint8_t stateMask = (state ? bit : 0);
	unsigned long width = 0; // keep initialization out of time critical area
	
	// convert the timeout from microseconds to a number of times through
	// the initial loop; it takes 16 clock cycles per iteration.
	unsigned long numloops = 0;
	unsigned long maxloops = microsecondsToClockCycles(timeout) / 16;
	
	// wait for any previous pulse to end
	while ((*portInputRegister(port) & bit) == stateMask)
		if (numloops++ == maxloops)
			return 0;
	
	// wait for the pulse to start
	while ((*portInputRegister(port) & bit) != stateMask)
		if (numloops++ == maxloops)
			return 0;
	
	// wait for the pulse to stop
	while ((*portInputRegister(port) & bit) == stateMask) {
		if (numloops++ == maxloops)
			return 0;
		width++;
	}

	// convert the reading to microseconds. The loop has been determined
	// to be 20 clock cycles long and have about 16 clocks between the edge
	// and the start of the loop. There will be some error introduced by
	// the interrupt handlers.
	return clockCyclesToMicroseconds(width * 21 + 16); 
#else
#if !defined(G23_FPB)
	/**
	 * ピンに入力されるパルスを検出します。
	 *
	 * たとえば、パルスの種類(u8Value)をHIGHに指定した場合、 pulseIn()関数は入力がHIGHに
	 * 変わると同時に時間の計測を始め、またLOWに戻ったら、そこまでの時間(つまりパルス
	 * の長さ)をマイクロ秒単位で返します。タイムアウトを指定した場合は、その時間を超
	 * えた時点で0を返します。
	 *
	 * @param[in] u8Pin      パルスを入力するピン番号を指定します。
	 * @param[in] u8Value    測定するパルスの種類（HIGHまたはLOW）を指定します。
	 * @param[in] u32Timeout タイムアウトまでの時間(単位・マイクロ秒)を指定します。
	 *
	 * @return パルスの長さ(マイクロ秒)を返却します。
	 *         パルスがスタートする前にタイムアウトとなった場合は0を返却します。
	 *
	 * @attention なし
	 ***************************************************************************/
	uint8_t u8StateMask;
	unsigned long u32TimeoutCycles;
	unsigned long u32PulseCycles = 0;
	unsigned long u32PulseLength = 0;
	const unsigned long u32AdjustCycles = 50 + PulseInWaitCycles / 2 + PulseInCountCycles / 2;
	bool timeOut;

	if (pin < NUM_DIGITAL_PINS) {
//		PinTableType* p = getPinTable(pin);
		PinTableType* p;
		getPinTable(pin,p);
		u8StateMask = (state ? p->mask : 0);
		{
			u32TimeoutCycles = microsecondsToClockCycles(timeout);
			timeOut =  pulseInWait(p->portRegisterAddr, p->mask, u8StateMask, &u32TimeoutCycles);

			if (!timeOut) {
				timeOut =  pulseInWait(p->portRegisterAddr, p->mask, u8StateMask ^ p->mask, &u32TimeoutCycles);
				if (!timeOut) {
					timeOut = pulseInCount(p->portRegisterAddr, p->mask, u8StateMask, u32TimeoutCycles, &u32PulseCycles);
				}
			}
			if (!timeOut) {
				u32PulseLength = clockCyclesToMicroseconds(u32PulseCycles + u32AdjustCycles);
			}
		}
	}

	return u32PulseLength;
#endif /* G23_FPB */
  /* 1112 Nhu add */
	uint8_t i;
	uint8_t pulse_in_flg = 0;
	uint32_t Result = 0;

	uint32_t timer_clock_mode = 0;
	uint32_t pulse_frequency = 0;
	uint32_t timeout_frequency = 0;

	g_pulse_enable_interrupt_flag = 1;

	int8_t pulse_in_channel = get_pulse_in_channel(pin);
	if (-1 ==(*(int8_t*)get_pulse_in_channel))
	{
		NOP();
	}

	/* If it is not a pulse input pin, do nothing and exit */
	for(i = 0; i < PULSE_IN_CH_NUM; i ++)
	{
		if(pin == pulse_in_channel_table[i])
		{
			pulse_in_flg = 1;
			i = PULSE_IN_CH_NUM;
		}
		else
		{
			pulse_in_flg = 0;
		}
	}

	if(pulse_in_flg == 1)
	{
		/* Timer create */
		pulse_in_ch[pulse_in_channel].open();

		/* State Set */
		if(state == LOW)
		{
			*((uint32_t*)g_timer_pulse_mode_reg[pulse_in_channel]) |= _0200_TAU_TRIGGER_TIMN_BOTH | _0080_TAU_TIMN_EDGE_BOTH_LOW;
		}
		else
		{
			*((uint32_t*)g_timer_pulse_mode_reg[pulse_in_channel]) |= _00C0_TAU_TIMN_EDGE_BOTH_HIGH;
		}

		/* Get timeout frequency */
		timer_clock_mode = *((uint32_t*)g_timer_timeout_mode_reg) & TAU_OPERATION_CLOCK;
		timeout_frequency = get_timer_frequency(timer_clock_mode);

		/* Timeout Set */
		timeout = min(timeout, TIMEOUT_MAX_VAL);
		*((uint32_t*)g_timer_timeout_data_reg) = ((timeout * timeout_frequency/1000000)-1);

		/* Timer Start */
		pulse_in_ch[pulse_in_channel].start();

		/* Get width */
				switch(pin)
				{
					case PWM_PIN_32:
						while((g_tau0_ch1_interrupt_flag == 0) && (g_tau0_ch0_interrupt_flag == 0));    	/* Wait get width */
						break;
					case PWM_PIN_31:
						while((g_tau0_ch2_interrupt_flag == 0) && (g_tau0_ch0_interrupt_flag == 0));    	/* Wait get width */
						break;
					case PWM_PIN_6:
						while((g_tau0_ch3_interrupt_flag == 0) && (g_tau0_ch0_interrupt_flag == 0));    	/* Wait get width */
						break;
					case PWM_PIN_3:
						while((g_tau0_ch4_interrupt_flag == 0) && (g_tau0_ch0_interrupt_flag == 0));    	/* Wait get width */
						break;
					case PWM_PIN_10:
						while((g_tau0_ch5_interrupt_flag == 0) || (g_tau0_ch0_interrupt_flag == 0));    	/* Wait get width */
						break;
					case PWM_PIN_9:
						while((g_tau0_ch6_interrupt_flag == 0) && (g_tau0_ch0_interrupt_flag == 0));    	/* Wait get width */
						break;
					case PWM_PIN_5:
						while((g_tau0_ch7_interrupt_flag == 0) && (g_tau0_ch0_interrupt_flag == 0));    	/* Wait get width */
						break;
					default:
						break;
					}
			pulse_in_ch[pulse_in_channel].get_width(&Result);	/* Store capture value */

			/* Get pulse frequency */
			timer_clock_mode = *((uint32_t*)g_timer_pulse_mode_reg[pulse_in_channel]) & TAU_OPERATION_CLOCK;
			pulse_frequency = get_timer_frequency(timer_clock_mode);

			Result = Result * (1000000/pulse_frequency);

			/* Timer Stop */
			pulse_in_ch[pulse_in_channel].stop();
			g_tau0_ch0_interrupt_flag = 0;

	}
	/* 1012 nhu add */

	return Result;
#endif

}

static uint32_t get_timer_frequency(uint32_t clock_mode)
{
	uint32_t fclk_frequency = 0;
	uint32_t timer_frequency = 0;
	uint32_t operating_clock_select = 0;

	fclk_frequency = R_BSP_GetFclkFreqHz();

	if (clock_mode == _4000_TAU_CLOCK_SELECT_CKM2)
	{
		operating_clock_select = *((uint32_t*)g_timer_pulse_clock_select_reg) & CK02_OPERATION;
		if(operating_clock_select == _0000_TAU_CKM2_FCLK_1)
		{
			timer_frequency = fclk_frequency/2;
		}
		else
		{
			operating_clock_select = operating_clock_select >> 8;
			timer_frequency = fclk_frequency/( pow(2, 2 * operating_clock_select));	/*  fclk/2^2 ~ 2^6 */
		}
	}
	else if  (clock_mode == _C000_TAU_CLOCK_SELECT_CKM3)
	{
		operating_clock_select = *((uint32_t*)g_timer_pulse_clock_select_reg) & CK03_OPERATION;

		operating_clock_select = operating_clock_select >> 12;
		timer_frequency = fclk_frequency/( pow(2,(2 * operating_clock_select +8)));	/* fclk/2^8 ~ 2^14 */
	}
	else /* CK00, CK01 Clock Select */
	{
		operating_clock_select = *((uint32_t*)g_timer_pulse_clock_select_reg) & CK00_CK01_OPERATION;
		timer_frequency = fclk_frequency/( pow(2,operating_clock_select));	/* ckm00, ckm01 - fclk/2^0 ~ 2^15 */
	}
	return timer_frequency;
}
