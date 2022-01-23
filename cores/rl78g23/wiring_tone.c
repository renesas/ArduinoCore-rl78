/*
 * writing_tone.c
 *
 *  Created on: 2021/11/02
 *      Author: hmU11983
 */

#ifndef __RL78__
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#else /*__RL78__*/
#endif/*__RL78__*/
#include "pins_arduino.h"
/* 1112 nhu add */
#include "wiring_private.h"
#include "pintable.h"
#include "r_smc_entry.h"
/* 1112 nhu add */

#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega128__)
#define TCCR2A TCCR2
#define TCCR2B TCCR2
#define COM2A1 COM21
#define COM2A0 COM20
#define OCR2A OCR2
#define TIMSK2 TIMSK
#define OCIE2A OCIE2
#define TIMER2_COMPA_vect TIMER2_COMP_vect
#define TIMSK1 TIMSK
#endif

#ifndef __RL78__
// timerx_toggle_count:
//  > 0 - duration specified
//  = 0 - stopped
//  < 0 - infinitely (until stop() method called, or new play() called)

#if !defined(__AVR_ATmega8__)
volatile long timer0_toggle_count;
volatile uint8_t *timer0_pin_port;
volatile uint8_t timer0_pin_mask;
#endif

volatile long timer1_toggle_count;
volatile uint8_t *timer1_pin_port;
volatile uint8_t timer1_pin_mask;
volatile long timer2_toggle_count;
volatile uint8_t *timer2_pin_port;
volatile uint8_t timer2_pin_mask;
#else
// Tone relation
//static uint8_t g_u8TonePin = NOT_A_PIN;
//static uint8_t g_u8ToneToggle = 0;
//static unsigned long g_u32ToneDuration = 0;
//static unsigned long g_u32ToneInterruptCount = 0;
#endif /*__RL78__*/

#if defined(TIMSK3)
volatile long timer3_toggle_count;
volatile uint8_t *timer3_pin_port;
volatile uint8_t timer3_pin_mask;
#endif

#if defined(TIMSK4)
volatile long timer4_toggle_count;
volatile uint8_t *timer4_pin_port;
volatile uint8_t timer4_pin_mask;
#endif

#if defined(TIMSK5)
volatile long timer5_toggle_count;
volatile uint8_t *timer5_pin_port;
volatile uint8_t timer5_pin_mask;
#endif


#ifndef __RL78__
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

#define AVAILABLE_TONE_PINS 1
#define USE_TIMER2

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 2 /*, 3, 4, 5, 1, 0 */ };
static uint8_t tone_pins[AVAILABLE_TONE_PINS] = { 255 /*, 255, 255, 255, 255, 255 */ };

#elif defined(__AVR_ATmega8__)

#define AVAILABLE_TONE_PINS 1
#define USE_TIMER2

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 2 /*, 1 */ };
static uint8_t tone_pins[AVAILABLE_TONE_PINS] = { 255 /*, 255 */ };

#elif defined(__AVR_ATmega32U4__)

#define AVAILABLE_TONE_PINS 1
#define USE_TIMER3

const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 3 /*, 1 */ };
static uint8_t tone_pins[AVAILABLE_TONE_PINS] = { 255 /*, 255 */ };

#else

#define AVAILABLE_TONE_PINS 1
#define USE_TIMER2

// Leave timer 0 to last.
const uint8_t PROGMEM tone_pin_to_timer_PGM[] = { 2 /*, 1, 0 */ };
static uint8_t tone_pins[AVAILABLE_TONE_PINS] = { 255 /*, 255, 255 */ };

#endif
#else /*__RL78__*/
/* 1112 nhu add */
extern uint32_t R_BSP_GetFclkFreqHz(void);

/* tone pin set */
volatile unsigned short *g_tone_period_reg[TONE_CH_NUM] = {&TDR01,&TDR02,&TDR03,&TDR04,&TDR05,&TDR06,&TDR07};
volatile unsigned short *g_timer_tone_mode_reg[TONE_CH_NUM] = {&TMR01,&TMR02,&TMR03,&TMR04,&TMR05,&TMR06,&TMR07};
volatile unsigned short *g_timer_tone_clock_select_reg = &TPS0;
const uint8_t  tone_channel_table[TONE_CH_NUM]  = {PWM_PIN_32,PWM_PIN_31,PWM_PIN_6,PWM_PIN_3,PWM_PIN_10,PWM_PIN_9,PWM_PIN_5};
tone_func tone_ch[TONE_CH_NUM] =
{
	{
		.open  = (void*)R_Config_TAU0_1_Square_Wave_Create,
		.start = (void*)R_Config_TAU0_1_Square_Wave_Start,
		.stop = (void*)R_Config_TAU0_1_Square_Wave_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_2_Square_Wave_Create,
		.start = (void*)R_Config_TAU0_2_Square_Wave_Start,
		.stop = (void*)R_Config_TAU0_2_Square_Wave_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_3_Square_Wave_Create,
		.start = (void*)R_Config_TAU0_3_Square_Wave_Start,
		.stop = (void*)R_Config_TAU0_3_Square_Wave_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_4_Square_Wave_Create,
		.start = (void*)R_Config_TAU0_4_Square_Wave_Start,
		.stop = (void*)R_Config_TAU0_4_Square_Wave_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_5_Square_Wave_Create,
		.start = (void*)R_Config_TAU0_5_Square_Wave_Start,
		.stop = (void*)R_Config_TAU0_5_Square_Wave_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_6_Square_Wave_Create,
		.start = (void*)R_Config_TAU0_6_Square_Wave_Start,
		.stop = (void*)R_Config_TAU0_6_Square_Wave_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_7_Square_Wave_Create,
		.start = (void*)R_Config_TAU0_7_Square_Wave_Start,
		.stop = (void*)R_Config_TAU0_7_Square_Wave_Stop
	}
};

int8_t get_tone_channel(uint8_t tone_num)
{
	uint8_t tone_cnt;

	for(tone_cnt=0;tone_cnt<TONE_CH_NUM;tone_cnt++)
	{
		if (tone_num == tone_channel_table[tone_cnt])
		{
			return tone_cnt;
		}
	}
	return -1;
}

/* 1112 nhu add */
#endif/*__RL78__*/



#ifndef __RL78__
static int8_t toneBegin(uint8_t _pin)
{
  int8_t _timer = -1;

  // if we're already using the pin, the timer should be configured.
  for (int i = 0; i < AVAILABLE_TONE_PINS; i++) {
    if (tone_pins[i] == _pin) {
      return pgm_read_byte(tone_pin_to_timer_PGM + i);
    }
  }

  // search for an unused timer.
  for (int i = 0; i < AVAILABLE_TONE_PINS; i++) {
    if (tone_pins[i] == 255) {
      tone_pins[i] = _pin;
      _timer = pgm_read_byte(tone_pin_to_timer_PGM + i);
      break;
    }
  }

  if (_timer != -1)
  {
    // Set timer specific stuff
    // All timers in CTC mode
    // 8 bit timers will require changing prescalar values,
    // whereas 16 bit timers are set to either ck/1 or ck/64 prescalar
    switch (_timer)
    {
      #if defined(TCCR0A) && defined(TCCR0B)
      case 0:
        // 8 bit timer
        TCCR0A = 0;
        TCCR0B = 0;
        bitWrite(TCCR0A, WGM01, 1);
        bitWrite(TCCR0B, CS00, 1);
        timer0_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer0_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR1A) && defined(TCCR1B) && defined(WGM12)
      case 1:
        // 16 bit timer
        TCCR1A = 0;
        TCCR1B = 0;
        bitWrite(TCCR1B, WGM12, 1);
        bitWrite(TCCR1B, CS10, 1);
        timer1_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer1_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR2A) && defined(TCCR2B)
      case 2:
        // 8 bit timer
        TCCR2A = 0;
        TCCR2B = 0;
        bitWrite(TCCR2A, WGM21, 1);
        bitWrite(TCCR2B, CS20, 1);
        timer2_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer2_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR3A) && defined(TCCR3B) &&  defined(TIMSK3)
      case 3:
        // 16 bit timer
        TCCR3A = 0;
        TCCR3B = 0;
        bitWrite(TCCR3B, WGM32, 1);
        bitWrite(TCCR3B, CS30, 1);
        timer3_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer3_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR4A) && defined(TCCR4B) &&  defined(TIMSK4)
      case 4:
        // 16 bit timer
        TCCR4A = 0;
        TCCR4B = 0;
        #if defined(WGM42)
          bitWrite(TCCR4B, WGM42, 1);
        #elif defined(CS43)
          #warning this may not be correct
          // atmega32u4
          bitWrite(TCCR4B, CS43, 1);
        #endif
        bitWrite(TCCR4B, CS40, 1);
        timer4_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer4_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif

      #if defined(TCCR5A) && defined(TCCR5B) &&  defined(TIMSK5)
      case 5:
        // 16 bit timer
        TCCR5A = 0;
        TCCR5B = 0;
        bitWrite(TCCR5B, WGM52, 1);
        bitWrite(TCCR5B, CS50, 1);
        timer5_pin_port = portOutputRegister(digitalPinToPort(_pin));
        timer5_pin_mask = digitalPinToBitMask(_pin);
        break;
      #endif
    }
  }

  return _timer;
}
#endif/*__RL78__*/



// frequency (in hertz) and duration (in milliseconds).

void tone(uint8_t pin, unsigned int frequency, unsigned long duration)
{
#ifndef __RL78__
  uint8_t prescalarbits = 0b001;
  long toggle_count = 0;
  uint32_t ocr = 0;
  int8_t _timer;

  _timer = toneBegin(_pin);

  if (_timer >= 0)
  {
    // Set the pinMode as OUTPUT
    pinMode(_pin, OUTPUT);

    // if we are using an 8 bit timer, scan through prescalars to find the best fit
    if (_timer == 0 || _timer == 2)
    {
      ocr = F_CPU / frequency / 2 - 1;
      prescalarbits = 0b001;  // ck/1: same for both timers
      if (ocr > 255)
      {
        ocr = F_CPU / frequency / 2 / 8 - 1;
        prescalarbits = 0b010;  // ck/8: same for both timers

        if (_timer == 2 && ocr > 255)
        {
          ocr = F_CPU / frequency / 2 / 32 - 1;
          prescalarbits = 0b011;
        }

        if (ocr > 255)
        {
          ocr = F_CPU / frequency / 2 / 64 - 1;
          prescalarbits = _timer == 0 ? 0b011 : 0b100;

          if (_timer == 2 && ocr > 255)
          {
            ocr = F_CPU / frequency / 2 / 128 - 1;
            prescalarbits = 0b101;
          }

          if (ocr > 255)
          {
            ocr = F_CPU / frequency / 2 / 256 - 1;
            prescalarbits = _timer == 0 ? 0b100 : 0b110;
            if (ocr > 255)
            {
              // can't do any better than /1024
              ocr = F_CPU / frequency / 2 / 1024 - 1;
              prescalarbits = _timer == 0 ? 0b101 : 0b111;
            }
          }
        }
      }

#if defined(TCCR0B)
      if (_timer == 0)
      {
        TCCR0B = prescalarbits;
      }
      else
#endif
#if defined(TCCR2B)
      {
        TCCR2B = prescalarbits;
      }
#else
      {
        // dummy place holder to make the above ifdefs work
      }
#endif
    }
    else
    {
      // two choices for the 16 bit timers: ck/1 or ck/64
      ocr = F_CPU / frequency / 2 - 1;

      prescalarbits = 0b001;
      if (ocr > 0xffff)
      {
        ocr = F_CPU / frequency / 2 / 64 - 1;
        prescalarbits = 0b011;
      }

      if (_timer == 1)
      {
#if defined(TCCR1B)
        TCCR1B = (TCCR1B & 0b11111000) | prescalarbits;
#endif
      }
#if defined(TCCR3B)
      else if (_timer == 3)
        TCCR3B = (TCCR3B & 0b11111000) | prescalarbits;
#endif
#if defined(TCCR4B)
      else if (_timer == 4)
        TCCR4B = (TCCR4B & 0b11111000) | prescalarbits;
#endif
#if defined(TCCR5B)
      else if (_timer == 5)
        TCCR5B = (TCCR5B & 0b11111000) | prescalarbits;
#endif

    }


    // Calculate the toggle count
    if (duration > 0)
    {
      toggle_count = 2 * frequency * duration / 1000;
    }
    else
    {
      toggle_count = -1;
    }

    // Set the OCR for the given timer,
    // set the toggle count,
    // then turn on the interrupts
    switch (_timer)
    {

#if defined(OCR0A) && defined(TIMSK0) && defined(OCIE0A)
      case 0:
        OCR0A = ocr;
        timer0_toggle_count = toggle_count;
        bitWrite(TIMSK0, OCIE0A, 1);
        break;
#endif

      case 1:
#if defined(OCR1A) && defined(TIMSK1) && defined(OCIE1A)
        OCR1A = ocr;
        timer1_toggle_count = toggle_count;
        bitWrite(TIMSK1, OCIE1A, 1);
#elif defined(OCR1A) && defined(TIMSK) && defined(OCIE1A)
        // this combination is for at least the ATmega32
        OCR1A = ocr;
        timer1_toggle_count = toggle_count;
        bitWrite(TIMSK, OCIE1A, 1);
#endif
        break;

#if defined(OCR2A) && defined(TIMSK2) && defined(OCIE2A)
      case 2:
        OCR2A = ocr;
        timer2_toggle_count = toggle_count;
        bitWrite(TIMSK2, OCIE2A, 1);
        break;
#endif

#if defined(TIMSK3)
      case 3:
        OCR3A = ocr;
        timer3_toggle_count = toggle_count;
        bitWrite(TIMSK3, OCIE3A, 1);
        break;
#endif

#if defined(TIMSK4)
      case 4:
        OCR4A = ocr;
        timer4_toggle_count = toggle_count;
        bitWrite(TIMSK4, OCIE4A, 1);
        break;
#endif

#if defined(OCR5A) && defined(TIMSK5) && defined(OCIE5A)
      case 5:
        OCR5A = ocr;
        timer5_toggle_count = toggle_count;
        bitWrite(TIMSK5, OCIE5A, 1);
        break;
#endif

    }
  }
#else /*__RL78__*/
#if !defined(G23_FPB)
	unsigned int u16TDR0x;


	if (_pin < NUM_DIGITAL_PINS) {
		//  removed from v1.05
		//		if (g_u8TonePin == _pin) {
		//			noTone(_pin);	// 既にトーンを出力中の場合、トーンを停止する。
		//		}

		// 周期の計算
		//
		// パルス周期[s] = (TDR0x設定値 + 1) *
		// TDR0x設定値 = パルス周期(1/frequency/2) * タイマ・クロック周期(125kHz) - 1
		//
		u16TDR0x = (unsigned int)(125000 / frequency / 2 - 1);

		// 出力時間の設定
		if (duration == 0) {
			// 出力時間を無限に設定
			g_u32ToneDuration = 0xFFFFFFFF;
		}
		else {
			// 出力時間[ms]から割り込み回数に変換
			//
			// 出力時間[ms] = パルス周期(1/u16Frequence/2) * 割り込み回数 * 1000
			// 割り込み回数 = 出力時間[ms] / パルス周期(1/frequency/2) / 1000
			g_u32ToneDuration = duration * frequency * 2 / 1000;
		}

		// 変数の初期化
		g_u8ToneToggle = 0;
		g_u32ToneInterruptCount = 0;

		if (g_u8TonePin == NOT_A_PIN) {
			// 出力モードに設定
			pinMode(_pin, OUTPUT);

			// トーン出力ピンの保存
			g_u8TonePin = _pin;

			_startTAU0(TIMER_CLOCK);

			// タイマーの設定
			_startTimerChannel(TONE_TIMER, TONE_MODE, u16TDR0x, false, true);
		} else {
			_modifyTimerPeriodic(TONE_TIMER, u16TDR0x);
		}
	}
#endif /* G23_FPB */
  /* 1112 Nhu add */
	uint8_t i;
	uint8_t tone_pin_flg = 0;
	unsigned long tone_interrupt_cnt;
	int8_t tone_channel = get_tone_channel(pin);
	uint32_t fclk_frequency = 0;
	uint32_t timer_frequency = 0;
	uint32_t timer_clock_mode = 0;
	uint32_t operating_clock_select = 0;

	if (-1 == (*(int8_t*)get_tone_channel))
	{
		NOP();
	}

	/* If it is not a tone output pin, do nothing and exit */
	for(i = 0; i < TONE_CH_NUM; i ++)
	{
		if(pin == tone_channel_table[i])
		{
			tone_pin_flg = 1;
			i = TONE_CH_NUM;
		}
		else
		{
			tone_pin_flg = 0;
		}
	}

	if(tone_pin_flg == 1)
	{

		/* Initializes the tone channel */
		tone_ch[tone_channel].open();

		/* Frequency Set
		 * Frequency of square wave output from TOmn = Frequency of count clock/{(Set value of TDRmn + 1) × 2}
		 * Set value of TDRmn = (Frequency of count clock / 2 x Frequency of square wave output from TOmn) - 1
		 */
		fclk_frequency = R_BSP_GetFclkFreqHz();

		/* Get timer frequency */
		timer_clock_mode = *((uint32_t*)g_timer_tone_mode_reg[tone_channel]) & TAU_OPERATION_CLOCK;

		if (timer_clock_mode == _4000_TAU_CLOCK_SELECT_CKM2)
		{
			operating_clock_select = *((uint32_t*)g_timer_tone_clock_select_reg) & CK02_OPERATION;
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
		else if  (timer_clock_mode == _C000_TAU_CLOCK_SELECT_CKM3)
		{
			operating_clock_select = *((uint32_t*)g_timer_tone_clock_select_reg) & CK03_OPERATION;

			operating_clock_select = operating_clock_select >> 12;
			timer_frequency = fclk_frequency/( pow(2,(2 * operating_clock_select +8)));	/* fclk/2^8 ~ 2^14 */
		}
		else /* CK00, CK01 Clock Select */
		{
			operating_clock_select = *((uint32_t*)g_timer_tone_clock_select_reg) & CK00_CK01_OPERATION;
			timer_frequency = fclk_frequency/( pow(2,operating_clock_select));	/* ckm00, ckm01 - fclk/2^0 ~ 2^15 */
		}

		/* 500 Hz <= frequency <= 65535Hz */
		frequency = min(max(frequency, FREQUENCY_MIN_VAL), 65535);

		*((uint32_t*)g_tone_period_reg[tone_channel]) = (timer_frequency / 2 / frequency) - 1;

		tone_ch[tone_channel].start();

		if(duration != 0)
		{
			delay(duration);
			noTone(pin);
		}
	}

#endif/*__RL78__*/

}

// XXX: this function only works properly for timer 2 (the only one we use
// currently).  for the others, it should end the tone, but won't restore
// proper PWM functionality for the timer.
void disableTimer(uint8_t _timer)
{
#ifndef __RL78__
  switch (_timer)
  {
    case 0:
      #if defined(TIMSK0)
        TIMSK0 = 0;
      #elif defined(TIMSK)
        TIMSK = 0; // atmega32
      #endif
      break;

#if defined(TIMSK1) && defined(OCIE1A)
    case 1:
      bitWrite(TIMSK1, OCIE1A, 0);
      break;
#endif

    case 2:
      #if defined(TIMSK2) && defined(OCIE2A)
        bitWrite(TIMSK2, OCIE2A, 0); // disable interrupt
      #endif
      #if defined(TCCR2A) && defined(WGM20)
        TCCR2A = (1 << WGM20);
      #endif
      #if defined(TCCR2B) && defined(CS22)
        TCCR2B = (TCCR2B & 0b11111000) | (1 << CS22);
      #endif
      #if defined(OCR2A)
        OCR2A = 0;
      #endif
      break;

#if defined(TIMSK3)
    case 3:
      TIMSK3 = 0;
      break;
#endif

#if defined(TIMSK4)
    case 4:
      TIMSK4 = 0;
      break;
#endif

#if defined(TIMSK5)
    case 5:
      TIMSK5 = 0;
      break;
#endif
  }
#else /*__RL78__*/
#endif/*__RL78__*/
}

#if !defined(G23_FPB)
void noTone(uint8_t _pin)
{
#ifndef __RL78__
  int8_t _timer = -1;

  for (int i = 0; i < AVAILABLE_TONE_PINS; i++) {
    if (tone_pins[i] == _pin) {
      _timer = pgm_read_byte(tone_pin_to_timer_PGM + i);
      tone_pins[i] = 255;
    }
  }

  disableTimer(_timer);
#else /*__RL78__*/
  _stopTimerChannel(TONE_TIMER);
  g_u8TonePin = NOT_A_PIN;
#endif/*__RL78__*/
}
#else
void noTone(uint8_t pin)
{
	int8_t tone_channel = get_tone_channel(pin);
	if (-1 == tone_channel)
	{
		;
	}
	else
	{
	tone_ch[tone_channel].stop();
	}
}
#endif /* G23_FPB */

#ifndef __RL78__
#ifdef USE_TIMER0
ISR(TIMER0_COMPA_vect)
{
  if (timer0_toggle_count != 0)
  {
    // toggle the pin
    *timer0_pin_port ^= timer0_pin_mask;

    if (timer0_toggle_count > 0)
      timer0_toggle_count--;
  }
  else
  {
    disableTimer(0);
    *timer0_pin_port &= ~(timer0_pin_mask);  // keep pin low after stop
  }
}
#endif


#ifdef USE_TIMER1
ISR(TIMER1_COMPA_vect)
{
  if (timer1_toggle_count != 0)
  {
    // toggle the pin
    *timer1_pin_port ^= timer1_pin_mask;

    if (timer1_toggle_count > 0)
      timer1_toggle_count--;
  }
  else
  {
    disableTimer(1);
    *timer1_pin_port &= ~(timer1_pin_mask);  // keep pin low after stop
  }
}
#endif


#ifdef USE_TIMER2
ISR(TIMER2_COMPA_vect)
{

  if (timer2_toggle_count != 0)
  {
    // toggle the pin
    *timer2_pin_port ^= timer2_pin_mask;

    if (timer2_toggle_count > 0)
      timer2_toggle_count--;
  }
  else
  {
    // need to call noTone() so that the tone_pins[] entry is reset, so the
    // timer gets initialized next time we call tone().
    // XXX: this assumes timer 2 is always the first one used.
    noTone(tone_pins[0]);
//    disableTimer(2);
//    *timer2_pin_port &= ~(timer2_pin_mask);  // keep pin low after stop
  }
}
#endif


#ifdef USE_TIMER3
ISR(TIMER3_COMPA_vect)
{
  if (timer3_toggle_count != 0)
  {
    // toggle the pin
    *timer3_pin_port ^= timer3_pin_mask;

    if (timer3_toggle_count > 0)
      timer3_toggle_count--;
  }
  else
  {
    disableTimer(3);
    *timer3_pin_port &= ~(timer3_pin_mask);  // keep pin low after stop
  }
}
#endif


#ifdef USE_TIMER4
ISR(TIMER4_COMPA_vect)
{
  if (timer4_toggle_count != 0)
  {
    // toggle the pin
    *timer4_pin_port ^= timer4_pin_mask;

    if (timer4_toggle_count > 0)
      timer4_toggle_count--;
  }
  else
  {
    disableTimer(4);
    *timer4_pin_port &= ~(timer4_pin_mask);  // keep pin low after stop
  }
}
#endif


#ifdef USE_TIMER5
ISR(TIMER5_COMPA_vect)
{
  if (timer5_toggle_count != 0)
  {
    // toggle the pin
    *timer5_pin_port ^= timer5_pin_mask;

    if (timer5_toggle_count > 0)
      timer5_toggle_count--;
  }
  else
  {
    disableTimer(5);
    *timer5_pin_port &= ~(timer5_pin_mask);  // keep pin low after stop
  }
}
#endif
#else /*__RL78__*/
/// @cond
/**
 * トーン生成用割り込みハンドラ1
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
#if !defined(G23_FPB)
#ifdef __cplusplus
extern "C"
#endif
INTERRUPT void tone_interrupt(void)
{
	if (g_u32ToneDuration != TONE_DURATION_INFINITY) {
		if (g_u32ToneInterruptCount >= g_u32ToneDuration) {
			noTone(g_u8TonePin);

		}
	}
	// tone()関数が呼び出されている場合、ピンの出力を反転させる。
	if (g_u8TonePin != NOT_A_PIN) {
		g_u32ToneInterruptCount++;
		// Toggle pin.
		g_u8ToneToggle ^= 1;
		digitalWrite(g_u8TonePin, g_u8ToneToggle);
	}
}
#endif /* G23_FPB */

#endif/*__RL78__*/



