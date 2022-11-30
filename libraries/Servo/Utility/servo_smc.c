#include "servo_smc.h"

extern uint32_t R_BSP_GetFclkFreqHz(void);

/* servo pin set */
volatile uint16_t tdr;
volatile uint8_t  g_servo_timer_count[SERVO_CH_NUM] = {0,0,0,0,0,0,0};
extern volatile uint8_t g_servo_enable_interrupt_flag[SERVO_CH_NUM] ;
volatile unsigned short *g_servo_period_reg[SERVO_CH_NUM] = {&TDR01,&TDR02,&TDR03,&TDR04,&TDR05,&TDR06,&TDR07};
volatile unsigned short *g_timer_servo_mode_reg[SERVO_CH_NUM] = {&TMR01,&TMR02,&TMR03,&TMR04,&TMR05,&TMR06,&TMR07};
volatile unsigned short *g_timer_servo_clock_select_reg = &TPS0;
volatile unsigned short *g_timer_status_reg[SERVO_CH_NUM] = {&TSR01,&TSR02,&TSR03,&TSR04,&TSR05,&TSR06,&TSR07};
const uint8_t  servo_channel_table[SERVO_CH_NUM]  = {PWM_PIN_32,PWM_PIN_31,PWM_PIN_6,PWM_PIN_3,PWM_PIN_10,PWM_PIN_9,PWM_PIN_5};

uint8_t g_servo_flg[SERVO_CH_NUM] = {0,0,0,0,0,0,0};
servo_func servo_ch[SERVO_CH_NUM] =
{
	{
		.open  = (void*)R_Config_TAU0_1_Servo_Create,
		.start = (void*)R_Config_TAU0_1_Servo_Start,
		.stop = (void*)R_Config_TAU0_1_Servo_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_2_Servo_Create,
		.start = (void*)R_Config_TAU0_2_Servo_Start,
		.stop = (void*)R_Config_TAU0_2_Servo_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_3_Servo_Create,
		.start = (void*)R_Config_TAU0_3_Servo_Start,
		.stop = (void*)R_Config_TAU0_3_Servo_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_4_Servo_Create,
		.start = (void*)R_Config_TAU0_4_Servo_Start,
		.stop = (void*)R_Config_TAU0_4_Servo_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_5_Servo_Create,
		.start = (void*)R_Config_TAU0_5_Servo_Start,
		.stop = (void*)R_Config_TAU0_5_Servo_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_6_Servo_Create,
		.start = (void*)R_Config_TAU0_6_Servo_Start,
		.stop = (void*)R_Config_TAU0_6_Servo_Stop
	},
	{
		.open  = (void*)R_Config_TAU0_7_Servo_Create,
		.start = (void*)R_Config_TAU0_7_Servo_Start,
		.stop = (void*)R_Config_TAU0_7_Servo_Stop
	}
};

int8_t get_servo_channel(uint8_t servo_num)
{
	uint8_t servo_cnt;

	for(servo_cnt=0;servo_cnt<SERVO_CH_NUM;servo_cnt++)
	{
		if (servo_num == servo_channel_table[servo_cnt])
		{
			return servo_cnt;
		}
	}
	return -1;
}

void smc_attach_servo_channel(uint8_t pin)
{
	int8_t servo_channel = get_servo_channel(pin);
	/* Initializes the servo channel */
	servo_ch[servo_channel].open();
}

void smc_ServoWrite(uint8_t pin, unsigned int microseconds)
{
	uint8_t i;
	uint8_t servo_pin_flg = 0;
	int8_t servo_channel = get_servo_channel(pin);
	uint32_t fclk_frequency = 0;
	uint32_t timer_frequency = 0;
	uint32_t timer_clock_mode = 0;
	uint32_t operating_clock_select = 0;


	if (-1 == (*(int8_t*)get_servo_channel))
	{
		NOP();
	}

	/* If it is not a servo output pin, do nothing and exit */
	for(i = 0; i < SERVO_CH_NUM; i ++)
	{
		if(pin == servo_channel_table[i])
		{
			servo_pin_flg = 1;
			i = SERVO_CH_NUM;
		}
		else
		{
			servo_pin_flg = 0;
		}
	}

	if(servo_pin_flg == 1)
	{
		while (1UL==g_servo_enable_interrupt_flag[servo_channel]) {
			NOP();
			NOP();
			NOP();
		}

		/* Frequency Set
		 * Frequency of square wave output from TOmn = Frequency of count clock/{(Set value of TDRmn + 1) × 2}
		 * Set value of TDRmn = (Frequency of count clock / 2 x Frequency of square wave output from TOmn) - 1
		 */
		fclk_frequency = R_BSP_GetFclkFreqHz();

		/* Get timer frequency */
		timer_clock_mode = *((uint32_t*)g_timer_servo_mode_reg[servo_channel]) & TAU_OPERATION_CLOCK;

		if (timer_clock_mode == _4000_TAU_CLOCK_SELECT_CKM2)
		{
			operating_clock_select = *((uint32_t*)g_timer_servo_clock_select_reg) & CK02_OPERATION;			
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
			operating_clock_select = *((uint32_t*)g_timer_servo_clock_select_reg) & CK03_OPERATION;
			operating_clock_select = operating_clock_select >> 12;
			timer_frequency = fclk_frequency/( pow(2,(2 * operating_clock_select +8)));	/* fclk/2^8 ~ 2^14 */
		}
		else /* CK00, CK01 Clock Select */
		{
			operating_clock_select = *((uint32_t*)g_timer_servo_clock_select_reg) & CK00_CK01_OPERATION;
			timer_frequency = fclk_frequency/( pow(2,operating_clock_select));	/* ckm00, ckm01 - fclk/2^0 ~ 2^15 */
		}

//		/* Initializes the servo channel */
//		servo_ch[servo_channel].stop();
		servo_ch[servo_channel].open();

		/* Set TDR　Reg　*/
//		DI();
		tdr = (uint16_t)(microseconds * (uint16_t)(timer_frequency/1000000) - 1 ) ;
		*((uint32_t*)g_servo_period_reg[servo_channel]) = tdr;
//		EI();

		/* Servo Timer Flag set */
		g_servo_enable_interrupt_flag[servo_channel] = 1UL;
		/* Start　Timer for Servo */
		servo_ch[servo_channel].start();
//		while (1==g_servo_enable_interrupt_flag[servo_channel])
//		{
//			NOP();
//		}
//		servo_ch[servo_channel].stop();
	}
}
