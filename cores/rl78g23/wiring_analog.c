/*
 wiring_analog.c - analog input and output
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
#include "wiring_private.h"
#include "pins_arduino.h"

#ifdef __RL78__
#include "pintable.h"
#include "r_smc_entry.h"


extern const PinTableType * pinTablelist[NUM_DIGITAL_PINS];

extern uint8_t g_adc_int_flg;
static uint8_t g_u8AnalogReference = DEFAULT;
// static uint8_t g_u8SwPwmTicksCount = 0;
//uint8_t g_u8ADUL = 0xFF;
//uint8_t g_u8ADLL = 0x00;
boolean g_bAdcInterruptFlag = false;

uint16_t g_u16ADUL;
uint16_t g_u16ADLL;

/* 1027 Nhu add */
extern uint32_t R_BSP_GetFclkFreqHz(void);
/* 1027 Nhu add */

/* 1008 Mitsugi add */
/* Match to the value of PWM_PIN */
volatile unsigned short *g_timer_period_reg[PWM_CH_NUM] = {&TDR00,&TDR02,&TDR04,&TDR06};
volatile unsigned short *g_timer_duty_reg[PWM_CH_NUM]   = {&TDR01,&TDR03,&TDR05,&TDR07};
volatile unsigned short *g_timer_analog_mode_reg[PWM_CH_NUM] = {&TMR01,&TMR03,&TMR05,&TMR07};
volatile unsigned short *g_timer_analog_clock_select_reg = &TPS0;
const uint8_t  pwm_channel_table[PWM_CH_NUM]  = {PWM_PIN_32,PWM_PIN_6,PWM_PIN_10,PWM_PIN_5};

static void _analogPinRead(uint8_t pin);
static int _analogRead(uint8_t u8ADS);
static int _analogDuty(int val, uint16_t frequency);
static uint16_t _analogFrequency (uint8_t pin, uint32_t u32Hz);

Pwm_func pwm_ch[PWM_CH_NUM] =
{
	{
		.open  = (void*)R_Config_TAU0_01_PWM_Create,
		.start = (void*)R_Config_TAU0_01_PWM_Start,
		.cycle = CYCLE_VALUE,
	},
	{
		.open  = (void*)R_Config_TAU0_23_PWM_Create,
		.start = (void*)R_Config_TAU0_23_PWM_Start,
		.cycle = CYCLE_VALUE,
	},
	{
		.open  = (void*)R_Config_TAU0_45_PWM_Create,
		.start = (void*)R_Config_TAU0_45_PWM_Start,
		.cycle = CYCLE_VALUE,
	},
	{
		.open  = (void*)R_Config_TAU0_67_PWM_Create,
		.start = (void*)R_Config_TAU0_67_PWM_Start,
		.cycle = CYCLE_VALUE,
	}
};

int8_t get_pwm_channel(uint8_t pwm_num)
{
	uint8_t pwm_cnt;

	for(pwm_cnt=0;pwm_cnt<PWM_CH_NUM;pwm_cnt++)
	{
		if (pwm_num == pwm_channel_table[pwm_cnt])
		{
			return pwm_cnt;
		}
	}
	return -1;
}
/* 1008 Mitsugi add */

#endif /*__RL78__*/

/* 1006 Nhu add */
/***********************************************************************************************************************
* Function Name: analogReference
* Description  : The reference voltage used for analog input.
* Arguments    : mode -
*                    DEFAULT: use VDD as VREF(+)
*                    INTERNAL: use internal voltage as VREF(+)
*                    EXTERNAL: use AVREFP as VREF(+)
* Return Value : None
***********************************************************************************************************************/
void analogReference(uint8_t mode) 
{
	// can't actually set the register here because the default setting
	// will connect AVCC and the AREF pin, which would cause a short if
	// there's something connected to AREF.
#ifndef __RL78__
	analog_reference = mode;
#else
	R_Config_ADC_Create();
	R_Config_ADC_Set_Reference(mode);
	g_u8AnalogReference = mode;
#endif
}
/* 1006 Nhu add */

#ifdef __RL78__

bool g_u8AnalogWriteAvailableTable[NUM_DIGITAL_PINS] = {
false, false, false, false,
false, false, false, false,
false, false, false, false,
false, false, false, false,
false, false, false, false,
false, false, false, false,
false, };
const uint8_t g_au8AnalogPinTable[NUM_ANALOG_INPUTS] = {
ANALOG_PIN_0, ANALOG_PIN_1, ANALOG_PIN_2, ANALOG_PIN_3,
ANALOG_PIN_4, ANALOG_PIN_5, ANALOG_PIN_6, ANALOG_PIN_7,
ANALOG_PIN_8, ANALOG_PIN_9};

volatile SwPwm g_SwPwm[NUM_SWPWM_PINS] = { { 0, 0, 0, 0, 0, 0 }, };

bool g_u8AnalogReadAvailableTable[NUM_ANALOG_INPUTS] = { 0 };

const uint8_t g_analog_pin_input[NUM_ANALOG_INPUTS] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};
int8_t get_analog_channel(uint8_t analog_num)
{
	uint8_t analog_cnt;

	for(analog_cnt=0;analog_cnt<NUM_ANALOG_INPUTS;analog_cnt++)
	{
		if (analog_num == g_analog_pin_input[analog_cnt])
		{
			return analog_cnt;
		}
	}
	return -1;
}

#endif/*__RL78__*/

/***********************************************************************************************************************
* Function Name: analogRead
* Description  : Reads the value from the specified analog pin.
* Arguments    : analog_pin - the name of the analog input pin to read from A0 to A7
* Return Value : The analog reading on the pin.
*                Although it is limited to the resolution of the analog to digital converter
*                (0-255 for 8 bits or 0-1023 for 10 bits).
***********************************************************************************************************************/
int analogRead(uint8_t analog_pin) {
#if 0
#ifndef __RL78__
	uint8_t low, high;

#if defined(analogPinToChannel)
#if defined(__AVR_ATmega32U4__)
	if (pin >= 18) pin -= 18; // allow for channel or pin numbers
#endif
	pin = analogPinToChannel(pin);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
	if (pin >= 54) pin -= 54; // allow for channel or pin numbers
#elif defined(__AVR_ATmega32U4__)
	if (pin >= 18) pin -= 18; // allow for channel or pin numbers
#elif defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
	if (pin >= 24) pin -= 24; // allow for channel or pin numbers
#else
	if (pin >= 14) pin -= 14; // allow for channel or pin numbers
#endif

#if defined(ADCSRB) && defined(MUX5)
	// the MUX5 bit of ADCSRB selects whether we're reading from channels
	// 0 to 7 (MUX5 low) or 8 to 15 (MUX5 high).
	ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
#endif

	// set the analog reference (high two bits of ADMUX) and select the
	// channel (low 4 bits).  this also sets ADLAR (left-adjust result)
	// to 0 (the default).
#if defined(ADMUX)
	ADMUX = (analog_reference << 6) | (pin & 0x07);
#endif

	// without a delay, we seem to read from the wrong channel
	//delay(1);

#if defined(ADCSRA) && defined(ADCL)
	// start the conversion
	sbi(ADCSRA, ADSC);

	// ADSC is cleared when the conversion finishes
	while (bit_is_set(ADCSRA, ADSC));

	// we have to read ADCL first; doing so locks both ADCL
	// and ADCH until ADCH is read.  reading ADCL second would
	// cause the results of each conversion to be discarded,
	// as ADCL and ADCH would be locked when it completed.
	low = ADCL;
	high = ADCH;
#else
	// we dont have an ADC, return 0
	low = 0;
	high = 0;
#endif

	// combine the two bytes
	return (high << 8) | low;
#else /*__RL78__*/
	int s16Result = 0;
	uint8_t oldadpc, newadpc;
	// ピン番号がANALOG_PIN_START_NUMBER（GR-KURUMIの場合は14）以上の場合0～に割り当てなおす。
	if (pin >= ANALOG_PIN_START_NUMBER) {
		pin -= ANALOG_PIN_START_NUMBER;
	}

	if (pin < NUM_ANALOG_INPUTS) {
		if (g_u8AnalogReadAvailableTable[pin] == false) {
			// ピンモードをAnalogモードに変更
//			PinTableType* p = &PinTable[pin];
			PinTableType* p;
			getPinTable(pin,p);
			if (0!=p->pmca)
			{
				/* アナログピンの場合PMCAをセットする */
				*p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
			}
#if 0
			switch (g_au8AnalogPinTable[pin]) {
			case 18:
				PMCA14 |= 0x80;	// P147をアナログポートに設定
				break;

			case 19:
				PMCA12 |= 0x01;	// P120をアナログポートに設定
				break;

			default:
//				oldadpc = ADPC;
//				newadpc = (pin - 14) + ANALOG_ADPC_OFFSET - 1;
//				if (newadpc > oldadpc) {
//					ADPC = newadpc;
//				}
				break;
			}
#endif
			// Specify pin number as digital port number
			pinMode(pin + ANALOG_PIN_START_NUMBER, INPUT);
			g_u8AnalogReadAvailableTable[pin] = true;

		}

	}

	// アナログ値の読み込み
	s16Result = _analogRead(g_au8AnalogPinTable[pin]);
//	s16Result = _analogRead(pin);
	return s16Result;
#endif/*__RL78__*/
#endif/* if 0 */

	int s16Result = 0;
	uint8_t analog_read_flg = 0;
	uint8_t cnt;

	//アナログ入力端子の設定
	_analogPinRead(analog_pin);

	//アナログ入力端子ではない場合、何もしない終了する
	for(cnt = 0; cnt < NUM_ANALOG_INPUTS; cnt ++)
	{
		if(analog_pin == g_analog_pin_input[cnt])
		{
			analog_read_flg = 1;
			cnt = NUM_ANALOG_INPUTS;
		}
		else
		{
		analog_read_flg = 0;
		}
	}

	if(analog_read_flg == 1)
	{
	// アナログ値の読み込み
	s16Result = _analogRead(g_au8AnalogPinTable[get_analog_channel(analog_pin)]);
	}
	return s16Result;
}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
/***********************************************************************************************************************
* Function Name: analogWrite
* Description  : Writes an analog value (PWM wave) to a pin.
* Arguments    : pin - the name of output pin (5,6,10,32)
*                value - Output PWM duty 0 ~ 255
* Return Value : None
***********************************************************************************************************************/
void analogWrite(uint8_t pin, int value) {
#ifndef __RL78__
	// We need to make sure the PWM output is enabled for those pins
	// that support it, as we turn it off when digitally reading or
	// writing with them.  Also, make sure the pin is in output mode
	// for consistenty with Wiring, which doesn't require a pinMode
	// call for the analog output pins.
	pinMode(pin, OUTPUT);
	if (val == 0)
	{
		digitalWrite(pin, LOW);
	}
	else if (val == 255)
	{
		digitalWrite(pin, HIGH);
	}
	else
	{
		switch(digitalPinToTimer(pin))
		{
			// XXX fix needed for atmega8
#if defined(TCCR0) && defined(COM00) && !defined(__AVR_ATmega8__)
			case TIMER0A:
			// connect pwm to pin on timer 0
			sbi(TCCR0, COM00);
			OCR0 = val;// set pwm duty
			break;
#endif

#if defined(TCCR0A) && defined(COM0A1)
			case TIMER0A:
			// connect pwm to pin on timer 0, channel A
			sbi(TCCR0A, COM0A1);
			OCR0A = val;// set pwm duty
			break;
#endif

#if defined(TCCR0A) && defined(COM0B1)
			case TIMER0B:
			// connect pwm to pin on timer 0, channel B
			sbi(TCCR0A, COM0B1);
			OCR0B = val;// set pwm duty
			break;
#endif

#if defined(TCCR1A) && defined(COM1A1)
			case TIMER1A:
			// connect pwm to pin on timer 1, channel A
			sbi(TCCR1A, COM1A1);
			OCR1A = val;// set pwm duty
			break;
#endif

#if defined(TCCR1A) && defined(COM1B1)
			case TIMER1B:
			// connect pwm to pin on timer 1, channel B
			sbi(TCCR1A, COM1B1);
			OCR1B = val;// set pwm duty
			break;
#endif

#if defined(TCCR2) && defined(COM21)
			case TIMER2:
			// connect pwm to pin on timer 2
			sbi(TCCR2, COM21);
			OCR2 = val;// set pwm duty
			break;
#endif

#if defined(TCCR2A) && defined(COM2A1)
			case TIMER2A:
			// connect pwm to pin on timer 2, channel A
			sbi(TCCR2A, COM2A1);
			OCR2A = val;// set pwm duty
			break;
#endif

#if defined(TCCR2A) && defined(COM2B1)
			case TIMER2B:
			// connect pwm to pin on timer 2, channel B
			sbi(TCCR2A, COM2B1);
			OCR2B = val;// set pwm duty
			break;
#endif

#if defined(TCCR3A) && defined(COM3A1)
			case TIMER3A:
			// connect pwm to pin on timer 3, channel A
			sbi(TCCR3A, COM3A1);
			OCR3A = val;// set pwm duty
			break;
#endif

#if defined(TCCR3A) && defined(COM3B1)
			case TIMER3B:
			// connect pwm to pin on timer 3, channel B
			sbi(TCCR3A, COM3B1);
			OCR3B = val;// set pwm duty
			break;
#endif

#if defined(TCCR3A) && defined(COM3C1)
			case TIMER3C:
			// connect pwm to pin on timer 3, channel C
			sbi(TCCR3A, COM3C1);
			OCR3C = val;// set pwm duty
			break;
#endif

#if defined(TCCR4A)
			case TIMER4A:
			//connect pwm to pin on timer 4, channel A
			sbi(TCCR4A, COM4A1);
#if defined(COM4A0)		// only used on 32U4
			cbi(TCCR4A, COM4A0);
#endif
			OCR4A = val;	// set pwm duty
			break;
#endif

#if defined(TCCR4A) && defined(COM4B1)
			case TIMER4B:
			// connect pwm to pin on timer 4, channel B
			sbi(TCCR4A, COM4B1);
			OCR4B = val;// set pwm duty
			break;
#endif

#if defined(TCCR4A) && defined(COM4C1)
			case TIMER4C:
			// connect pwm to pin on timer 4, channel C
			sbi(TCCR4A, COM4C1);
			OCR4C = val;// set pwm duty
			break;
#endif

#if defined(TCCR4C) && defined(COM4D1)
			case TIMER4D:
			// connect pwm to pin on timer 4, channel D
			sbi(TCCR4C, COM4D1);
#if defined(COM4D0)		// only used on 32U4
			cbi(TCCR4C, COM4D0);
#endif
			OCR4D = val;	// set pwm duty
			break;
#endif

#if defined(TCCR5A) && defined(COM5A1)
			case TIMER5A:
			// connect pwm to pin on timer 5, channel A
			sbi(TCCR5A, COM5A1);
			OCR5A = val;// set pwm duty
			break;
#endif

#if defined(TCCR5A) && defined(COM5B1)
			case TIMER5B:
			// connect pwm to pin on timer 5, channel B
			sbi(TCCR5A, COM5B1);
			OCR5B = val;// set pwm duty
			break;
#endif

#if defined(TCCR5A) && defined(COM5C1)
			case TIMER5C:
			// connect pwm to pin on timer 5, channel C
			sbi(TCCR5A, COM5C1);
			OCR5C = val;// set pwm duty
			break;
#endif

			case NOT_ON_TIMER:
			default:
			if (val < 128) {
				digitalWrite(pin, LOW);
			} else {
				digitalWrite(pin, HIGH);
			}
		}
	}
#else /*__RL78__*/
//	uint8_t u8Timer;
	if (pin < NUM_DIGITAL_PINS) {
		{
			value = min(max(value, PWM_MIN), PWM_MAX);
#if !defined(G23_FPB)
			u8Timer = getPinTable(pin)->timer;
			if (u8Timer == SWPWM_PIN) {
				/////////////////////
				 Software PWM対応ピンの場合
				/////////////////////
#if defined(__RL78__)
				_startTAU0(TIMER_CLOCK);
				if (!g_u8AnalogWriteAvailableTable[pin]) {
					pinMode(pin, OUTPUT);		// 初期時のみ出力モードを設定
					g_u8AnalogWriteAvailableTable[pin] = true;
				}
				int i;
				int j = NUM_SWPWM_PINS;
				for (i = 0; i < NUM_SWPWM_PINS; i++) {
					if (!g_SwPwm[i].valid) {
						if (j >= NUM_SWPWM_PINS) {
							j = i;
						}
					} else if (g_SwPwm[i].pin == pin) {
						break;
					}
				}
				if (i >= NUM_SWPWM_PINS) {
					i = j;
				}
				if (i < NUM_SWPWM_PINS) {
					if (g_SwPwm[i].valid && g_SwPwm[i].pin == pin) {
						g_SwPwm[i].newValue = val;
					} else {
//						const PinTableType* p = getPinTable(pin);
						PinTableType* p;
						getPinTable(pin,p);
						g_SwPwm[i].valid = false;
						g_SwPwm[i].pin = pin;
						g_SwPwm[i].value = g_SwPwm[i].newValue = val;
						g_SwPwm[i].port = p->portRegisterAddr;
						g_SwPwm[i].mask = p->mask;
						g_SwPwm[i].valid = true;
					}
					if (!(TE0 & 0x0040)) { // No pin uses Software PWM
						_startTimerChannel( SW_PWM_TIMER, 0x0001, SWPWM_MIN,
								false, true);
					}
				} else {
					digitalWrite(pin,
							val >= ((PWM_MIN + PWM_MAX + 1) / 2) ? HIGH : LOW);
				}

#endif
			} else {
				///////////////////////
				// PWM対応ピンの場合
				///////////////////////
				_startTAU0(TIMER_CLOCK);

				if (((TE0 & 0x0001) == 0) || (TDR00 != g_u16TDR00)) {
					// Masterチャネルの設定
					TT0 |= 0x0001;			// タイマ停止
					TMR00 = PWM_MASTER_MODE;	// 動作モードの設定
					TDR00 = g_u16TDR00;		// PWM出力の周期の設定
					TO0 &= ~0x0001;			// タイマ出力の設定
					TOE0 &= ~0x0001;			// タイマ出力許可の設定
					// マスタチャネルのタイマ動作許可
					TS0 |= 0x00001;
				}

				u16Duty = (unsigned short) (((unsigned long) val
						* (g_u16TDR00 + 1)) / PWM_MAX);
				if (!g_u8AnalogWriteAvailableTable[pin]) {
					pinMode(pin, OUTPUT);			// 出力モードに設定
					digitalWrite(pin, LOW);

					// Slaveチャネルの設定
					_startTimerChannel(u8Timer, PWM_SLAVE_MODE, u16Duty, true,
							false);
					g_u8AnalogWriteAvailableTable[pin] = true;

				} else {
					_modifyTimerPeriodic(u8Timer, u16Duty);
				}
			}
		}
	}
#endif
/* 1006 Nhu add */
			/* 1008 Mitsugi add */
			uint8_t cnt;
			uint8_t analog_write_flg = 0;
			int8_t pwm_channel = get_pwm_channel(pin);

			if (-1 ==(*(int8_t*)get_pwm_channel))
			{
				NOP();
			}

			/* If it is not a PWM output terminal, do nothing and exit */
			for(cnt = 0; cnt < PWM_CH_NUM; cnt ++)
			{
				if(pin == pwm_channel_table[cnt])
				{
					analog_write_flg = 1;
					cnt = PWM_CH_NUM;
				}
				else
				{
				analog_write_flg = 0;
				}
			}

			if(analog_write_flg == 1)
			{
			pwm_ch[pwm_channel].open();

			/* Frequency Set */
			if(pwm_ch[pwm_channel].cycle == CYCLE_VALUE)
			{
				pwm_ch[pwm_channel].cycle = _analogFrequency(pin,FREQUENCY_MIN_VAL);
			}
			else
			{
				*((uint32_t*)g_timer_period_reg[pwm_channel]) = pwm_ch[pwm_channel].cycle;
			}


			/* Duty set */
			*((uint32_t*)g_timer_duty_reg[pwm_channel])   = _analogDuty(value, pwm_ch[pwm_channel].cycle);

			pwm_ch[pwm_channel].start();
			}
			/* 1008 Mitsugi add */
		}
	}

#endif/*__RL78__*/

}

/***********************************************************************************************************************
* Function Name: analogWriteFrequency
* Description  : Sets the cycle. The default is 490Hz.
* Arguments    : Hz: cycle
* Return Value : None
***********************************************************************************************************************/
#ifdef __RL78__
void analogWriteFrequency(uint32_t Hz) {
	/* PWM output pulse cycle setting
	Pulse period = (TDR00 setting value + 1) x count clock period
	Example) When the pulse period is 2 [ms]
	2 [ms] = 1/32 [MHz] x (TDR00 setting + 1)
	TDR00 setting value = 63999 */

	pwm_ch[0].cycle = _analogFrequency(PWM_PIN_32,Hz);
	pwm_ch[1].cycle = _analogFrequency(PWM_PIN_6,Hz);
	pwm_ch[2].cycle = _analogFrequency(PWM_PIN_10,Hz);
	pwm_ch[3].cycle = _analogFrequency(PWM_PIN_5,Hz);

	/* 1008 Mitsugi add */
}

/***********************************************************************************************************************
* Function Name: analogWritePinFrequency
* Description  : Sets the cycle. The default is 490Hz.
* Arguments    : pin - the name of analog value (PWM wave) output pin (5,6,10,32)
*                Hz - cycle
* Return Value : None
***********************************************************************************************************************/
/* 1011 Nhu add */
void analogWritePinFrequency(uint8_t pin, uint32_t Hz) {
	/* PWM output pulse cycle setting
	Pulse period = (TDR00 setting value + 1) x count clock period
	Example) When the pulse period is 2 [ms]
	2 [ms] = 1/32 [MHz] x (TDR00 setting + 1)
	TDR00 setting value = 63999 */
	int8_t pwm_channel = get_pwm_channel(pin);
	pwm_ch[pwm_channel].cycle = _analogFrequency(pin, Hz);
}

static uint16_t _analogFrequency (uint8_t pin, uint32_t u32Hz)
{
	uint16_t Result;
	uint32_t fclk_frequency = 0;
	uint32_t timer_frequency = 0;
	uint32_t timer_clock_mode = 0;
	uint32_t operating_clock_select = 0;
	int8_t pwm_channel = get_pwm_channel(pin);

	fclk_frequency = R_BSP_GetFclkFreqHz();

	/* Get timer frequency */
		timer_clock_mode = *((uint32_t*)g_timer_analog_mode_reg[pwm_channel]) & TAU_OPERATION_CLOCK;

		if (timer_clock_mode == _4000_TAU_CLOCK_SELECT_CKM2) /* CK02 Clock Selected */
		{
			operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK02_OPERATION;
			if(operating_clock_select == _0000_TAU_CKM2_FCLK_1)
			{
				timer_frequency = fclk_frequency/2;	/*  fclk/2 */
			}
			else
			{
				operating_clock_select = operating_clock_select >> 8;
				timer_frequency = fclk_frequency/( pow(2, 2 * operating_clock_select));	/*  fclk/2^2 ~ 2^6 */
			}
		}
		else if  (timer_clock_mode == _C000_TAU_CLOCK_SELECT_CKM3) /* CK03 Clock Selected */
		{
			operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK03_OPERATION;

			operating_clock_select = operating_clock_select >> 12;
			timer_frequency = fclk_frequency/( pow(2,(2 * operating_clock_select +8)));	/* fclk/2^8 ~ 2^14 */
		}
		else /* CK00, CK01 Clock Selected */
		{
			operating_clock_select = *((uint32_t*)g_timer_analog_clock_select_reg) & CK00_CK01_OPERATION;
			timer_frequency = fclk_frequency/( pow(2,operating_clock_select));	/* ckm00, ckm01 - fclk/2^0 ~ 2^15 */
		}

	/* 490 Hz <= frequency <= 8MHz */
	u32Hz = min(max(u32Hz, FREQUENCY_MIN_VAL), FREQUENCY_MAX_VAL);

	/* Pulse period = {Set value of TDRmn (master) + 1} × Count clock period
	   Set value of TDRmn (master) = (Pulse period / Count clock period) - 1 */
	Result = (timer_frequency / u32Hz) - 1;

	return Result;
}

static int _analogDuty(int val, uint16_t frequency)
{
/*	Duty factor [0 ~ 255] = {Set value of TDRmp (slave)}/{Set value of TDRmn (master) + 1} × 255
	{Set value of TDRmp (slave)} = Duty factor * {Set value of TDRmn (master) + 1} / 255 */

	unsigned short u16Duty = 0;

	/* Duty set */
	if(val> PWM_MAX)
	{
		val = PWM_MAX;
	}
	else
	{
		u16Duty = (unsigned short) (((unsigned long) val
				* (frequency + 1)) / PWM_MAX);
	}

	return u16Duty;
}

/* 1011 Nhu add */
static void _analogPinRead (uint8_t pin)
{
	uint8_t pin_index;
	if (pin==29)
	{
		pin_index = 8;
	}
	else if (pin==40)
	{
		pin_index = 9;
	}
	else if (pin<ANALOG_PIN_START_NUMBER && pin < 2)
	{
		pin_index = pin + 6;
	}
	else
	{
		pin_index = pin - ANALOG_PIN_START_NUMBER;
	}


	if (g_u8AnalogReadAvailableTable[pin_index] == false) {
		// ピンモードをAnalogモードに変更
		//PinTableType *p;
		//PinTableType pin_tbl;
		//p = (PinTableType*)&pin_tbl;
        //getPinTable(pin,p);

		PinTableType ** pp;
		PinTableType * p;
		pp = &pinTablelist[pin];
		p = (PinTableType *)*pp;

		if (0!=p->pmca)
		{
			pinMode(pin, INPUT);
			/* アナログピンの場合PMCAをセットする */
			*p->portModeControlARegisterAddr |= (unsigned long)(p->pmca);

//			*p->portModeControlARegisterAddr &= (unsigned long)~(p->pmca);
			g_u8AnalogReadAvailableTable[pin_index] = true;
		}
	}
}

static int _analogRead(uint8_t u8ADS) {
	int s16Result = 0;
#if !defined(G23_FPB)
	if (((0 <= u8ADS) && (u8ADS <= 14)) || ((16 <= u8ADS) && (u8ADS <= 26))) {
#ifdef WORKAROUND_READ_MODIFY_WRITE
		ADM0 = 0x00;		// A/Dコンバータの動作停止、fclk/64、ノーマル1モードに設定
		CBI(SFR_IF1H, 0);		// INTADの割り込みフラグのクリア
#else /* WORKAROUND_READ_MODIFY_WRITE */
		ADCEN = 1;			// A/Dコンバータにクロック供給開始
		NOP();
		NOP();
		NOP();
		NOP();
		ADM0 = 0x00;// A/Dコンバータの動作停止、fclk/64、ノーマル1モードに設定
		ADMK = 1;// INTADの割り込み禁止
		ADIF = 0;// INTADの割り込みフラグのクリア
		ADPR1 = 1;// INTADの割り込み優先順位の設定
		ADPR0 = 1;// INTADの割り込み優先順位の設定
#endif
		if (g_u8AnalogReference == DEFAULT) {
			ADM2 = 0x00;	// Vddリファレンスに設定
		} else if (g_u8AnalogReference == INTERNAL) {
			ADM2 = 0x80;	// 内部リファレンス(1.45V)に設定
		} else { // EXTERNAL
			ADM2 = 0x40;	// 外部リファレンスに設定
		}
		if (g_u8PowerManagementMode == PM_SNOOZE_MODE) {
			ADM1 = 0xE3;	// ハードウェア・トリガ(INTIT)・ウェイト･モード、ワンショットに設定
		} else {
			ADM1 = 0x20;	// ソフトウェア・トリガ・モード、ワンショットに設定
		}
		ADUL = g_u8ADUL;
		ADLL = g_u8ADLL;
		ADS = u8ADS;		// アナログチャンネルの設定
		delayMicroseconds(5);	// 5 us 待ち
#ifdef WORKAROUND_READ_MODIFY_WRITE
		SBI(SFR_ADM0, SFR_BIT_ADCE);	// A/Dコンパレータを有効に設定
#else /* WORKAROUND_READ_MODIFY_WRITE */
				ADCE = 1;			// A/Dコンパレータを有効に設定
#endif
		if (g_u8PowerManagementMode == PM_SNOOZE_MODE) {
#ifdef WORKAROUND_READ_MODIFY_WRITE
			CBI(SFR_MK1H, 0);	// INTADの割り込み許可
			ADM2 |= 0x04;	// SNOOZEモードの設定
#else /* WORKAROUND_READ_MODIFY_WRITE */
					ADMK = 0;			// INTADの割り込み許可
					ADM2 |= 0x04;// SNOOZEモードの設定
#endif
			while (g_bAdcInterruptFlag == false) {
				enterPowerManagementMode(0xFFFFFFFF);	// A/Dコンバート待ち
			}
			ADM2 &= ~0x04;	// SNOOZEモードの設定解除
			g_bAdcInterruptFlag = false;
//			SBI(MK1H, 0);		// INTADの割り込み禁止
			ADMK = 1U;
		} else {
			delayMicroseconds(1);	// 1 us 待ち
#ifdef WORKAROUND_READ_MODIFY_WRITE
			SBI(SFR_ADM0, SFR_BIT_ADCS);	// A/Dコンバータの開始
#else /* WORKAROUND_READ_MODIFY_WRITE */
					ADCS = 1;		// A/Dコンバータの開始
#endif
			while (ADIF == 0)
				;	// A/Dコンバート待ち
		}
		s16Result = (ADCR >> 6);	// A/Dコンバート結果の取得

#ifdef WORKAROUND_READ_MODIFY_WRITE
		CBI(SFR_IF1H, 0);		// INTADの割り込みフラグのクリア
		CBI(SFR_ADM0, SFR_BIT_ADCE);		// A/Dコンパレータを無効に設定
#else /* WORKAROUND_READ_MODIFY_WRITE */
				ADMK = 1;			// INTADの割り込み禁止
				ADIF = 0;// INTADの割り込みフラグのクリア
				ADCE = 0;// A/Dコンパレータを無効に設定
				ADCEN = 0;// A/Dコンバータのクロック供給停止
#endif
	}
#endif

#if (false)
	/* 1006 Nhu add */
	R_Config_ADC_Set_ADChannel(u8ADS);
	R_Config_ADC_Set_OperationOn();
	g_adc_int_flg=0;
	R_Config_ADC_Start();
	while(0==g_adc_int_flg)
	{
		NOP();
	}
	if(g_u8AnalogReference == INTERNAL)
	{
		R_Config_ADC_Get_Result_8bit((uint8_t*)&s16Result);
	}
	else
	{
		R_Config_ADC_Get_Result_10bit((uint16_t*)&s16Result);
	}
	R_Config_ADC_Set_OperationOff();
	R_Config_ADC_Start();
#elif 0
    // 1. AD reference setting
	R_Config_ADC_Set_Reference (g_u8AnalogReference);
    // 2. Trigger mode setting
    if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
    {
        // Hardware trigger wait mode(RTC), one-shot conversion
        ADM1 = 0xE2;
    }
    else
    {
        // Software trigger mode, one-shot conversion
        ADM1 = 0x23;
    }
    // 3. Snooze mode return upper / lower limit setting
    ADUL = g_u8ADUL;
    ADLL = g_u8ADLL;

    if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
    {
        R_Config_ITL000_Stop();
    }

    // 4. AD channel setting
    R_Config_ADC_Set_ADChannel(u8ADS);

    g_adc_int_flg=0;
    if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
    {
        // 6. Snooze mode ON (interrupt enabled)
        R_Config_ADC_Set_SnoozeOn();
        R_Config_ADC_Snooze_Start();
        // 5. AD comparator ON
        R_Config_ADC_Set_OperationOn();
    }
    else
    {
        // 5. AD comparator ON
        R_Config_ADC_Set_OperationOn();
        R_Config_ADC_Start();
    }

    // 7. After STOP mode until AD interrupt occurs (loop processing)
    while (0 == g_adc_int_flg)
    {
        if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
        {
            enterPowerManagementMode (0xFFFFFFFF);
        }
        else
        {
            NOP();
        }
    }

    // 8. Snooze mode Off (interrupt stop)
    if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
    {
        R_Config_ADC_Set_SnoozeOff();
        R_Config_ADC_Snooze_Stop();
    }
    else
    {
        R_Config_ADC_Stop();
    }
    // 9. Get AD conversion result
    if (DEFAULT == g_u8AnalogReference)
    {
        R_Config_ADC_Get_Result_10bit ((uint16_t*) &s16Result);
    }
    else if (INTERNAL == g_u8AnalogReference)
    {
        R_Config_ADC_Get_Result_8bit ((uint8_t*) &s16Result);
    }

    // 10.AD Comparator Off
    R_Config_ADC_Set_OperationOff();

    if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
    {
        R_Config_ITL000_Start();
    }
#else
    uint8_t adc_end_flg = 0;
    // 1. AD reference setting
    R_Config_ADC_Set_Reference (g_u8AnalogReference);

    // 3. Snooze mode return upper / lower limit setting
    R_Config_ADC_Set_ComparisonLimit((uint8_t)(g_u16ADUL >> 2), (uint8_t)(g_u16ADLL >> 2));
    // 4. AD channel setting
    R_Config_ADC_Set_ADChannel(u8ADS);

    while(0 == adc_end_flg)
    {
        g_adc_int_flg=0;

        // 2. Trigger mode setting
        if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
        {
            R_Config_ITL000_Stop();
            // Hardware trigger wait mode(RTC), one-shot conversion
            R_Config_ADC_Set_ModeTrigger(PM_SNOOZE_MODE);
            // 6. Snooze mode ON (interrupt enabled)
            R_Config_ADC_Set_SnoozeOn();    //AWC =1
            // 5. AD comparator ON
            R_Config_ADC_Snooze_Start();    //enable interrupt & ADCS=1

        }
        else
        {
            // Software trigger mode, one-shot conversion
            R_Config_ADC_Set_ModeTrigger(PM_NORMAL_MODE);
            // 5. AD comparator ON
            R_Config_ADC_Set_OperationOn();  //ADCE=1 & wait
            R_Config_ADC_Start();            //ADCS=1 & enable interrupt
        }

        // 7. After STOP mode until AD interrupt occurs (loop processing)
        while (0 == g_adc_int_flg)
        {
            if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
            {
                enterPowerManagementMode (0xFFFFFFFF);
            }
            else
            {
                NOP();
            }
        }

        // 8. Snooze mode Off (interrupt stop)
        if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
        {
            R_Config_ADC_Set_SnoozeOff();
            R_Config_ADC_Snooze_Stop();
            R_Config_ITL000_Start();
        }
        else
        {
            R_Config_ADC_Stop();
        }
        // 9. Get AD conversion result
        if (DEFAULT == g_u8AnalogReference)
        {
            R_Config_ADC_Get_Result_10bit ((uint16_t*) &s16Result);
        }
        else if (INTERNAL == g_u8AnalogReference)
        {
            R_Config_ADC_Get_Result_8bit ((uint8_t*) &s16Result);
        }

        if (PM_SNOOZE_MODE == g_u8PowerManagementMode)
        {
            if((g_u16ADLL <= s16Result) && (s16Result <= g_u16ADUL))
            {
                adc_end_flg = 1;
            }
        }
        else
        {
            adc_end_flg = 1;
        }
    }
    // 10.AD Comparator Off
    R_Config_ADC_Set_OperationOff();

#endif
    // 11. Return the result
    return s16Result;
}


/**
 * SoftwarePWMの次回割り込みタイミングの設定処理
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
#if !defined(G23_FPB)
void _softwarePWM(void) {
	SwPwm* p;
	for (p = (SwPwm*) &g_SwPwm[0]; p < (SwPwm*) &g_SwPwm[NUM_SWPWM_PINS]; p++) {
		if (p->valid) {
			if (g_u8SwPwmTicksCount == PWM_MIN) {
				p->value = p->newValue;
			}
			if (g_u8SwPwmTicksCount == p->value) {
				*p->port &= ~p->mask;	// 出力をLOWに設定
			} else if (g_u8SwPwmTicksCount == PWM_MIN) {
				*p->port |= p->mask;	// 出力をHIGHに設定
			}
		}
	}
	if (++g_u8SwPwmTicksCount >= PWM_MAX) {
		g_u8SwPwmTicksCount = PWM_MIN;
	};
}

INTERRUPT void adc_interrupt(void) {
	g_bAdcInterruptFlag = true;
}

INTERRUPT void tm06_interrupt(void) {
	_softwarePWM();
}
#endif
#endif/*__RL78__*/
