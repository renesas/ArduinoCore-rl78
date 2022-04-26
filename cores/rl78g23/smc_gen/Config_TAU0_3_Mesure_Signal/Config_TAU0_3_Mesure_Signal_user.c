/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : Config_TAU0_3_Mesure_Signal_user.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxLA
* Description  : This file implements device driver for Config_TAU0_3_Mesure_Signal.
* Creation Date: 2021-11-12
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_TAU0_3_Mesure_Signal.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* For TAU0_ch3 pulse measurement */
volatile uint32_t g_tau0_ch3_width = 0UL;
/* Start user code for global. Do not edit comment generated here */
volatile uint8_t g_tau0_ch3_interrupt_flag = 0UL;
extern volatile uint8_t g_pulse_enable_interrupt_flag;

extern volatile uint8_t g_servo_enable_interrupt_flag[7];
void R_Config_TAU0_1_Servo_Stop(void);
void R_Config_TAU0_2_Servo_Stop(void);
void R_Config_TAU0_3_Servo_Stop(void);
void R_Config_TAU0_4_Servo_Stop(void);
void R_Config_TAU0_5_Servo_Stop(void);
void R_Config_TAU0_6_Servo_Stop(void);
void R_Config_TAU0_7_Servo_Stop(void);
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_3_Mesure_Signal_Create_UserInit
* Description  : This function adds user code after initializing the TAU0 channel3.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_3_Mesure_Signal_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_TAU0_3_Mesure_Signal_interrupt
* Description  : This function is INTTM03 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_TAU0_3_Mesure_Signal_interrupt(void)
{
	if(g_pulse_enable_interrupt_flag == 1UL)
	{
		if (1U == (TSR03 & _0001_TAU_OVERFLOW_OCCURS))    /* overflow occurs */
		{
			g_tau0_ch3_width = (uint32_t)(TDR03 + 1UL) + 0x10000UL;
		}
		else
		{
			g_tau0_ch3_width = (uint32_t)(TDR03 + 1UL);
		}
		/* Start user code for r_Config_TAU0_3_Mesure_Signal_interrupt. Do not edit comment generated here */
		g_tau0_ch3_interrupt_flag = 1UL;
	}
	else
	{
		;
	}
	if (g_servo_enable_interrupt_flag[2] == 1UL)
	{
		R_Config_TAU0_3_Servo_Stop();
		g_servo_enable_interrupt_flag[2]= 0UL;
	}
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
