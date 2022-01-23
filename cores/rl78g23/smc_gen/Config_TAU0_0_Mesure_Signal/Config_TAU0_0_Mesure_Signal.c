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
* File Name    : Config_TAU0_0.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxLA
* Description  : This file implements device driver for Config_TAU0_0_Mesure_Signal.
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
#include "Config_TAU0_0_Mesure_Signal.h"
/* Start user code for include. Do not edit comment generated here */
#include "Config_TAU0_1_Mesure_Signal.h"
#include "Config_TAU0_2_Mesure_Signal.h"
#include "Config_TAU0_3_Mesure_Signal.h"
#include "Config_TAU0_4_Mesure_Signal.h"
#include "Config_TAU0_5_Mesure_Signal.h"
#include "Config_TAU0_6_Mesure_Signal.h"
#include "Config_TAU0_7_Mesure_Signal.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_0_Create
* Description  : This function initializes the TAU0 channel 0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_0_Mesure_Signal_Create(void)
{
    TPS0 &= _FFF0_TAU_CKM0_CLEAR;
    TPS0 |= _0005_TAU_CKM0_FCLK_5;
    /* Stop channel 0 */
    TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    /* Set INTTM00 low priority */
    TMPR100 = 1U;
    TMPR000 = 1U;
    /* TAU00 used as interval timer */
    TMR00 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_TRIGGER_SOFTWARE | 
            _0000_TAU_MODE_INTERVAL_TIMER | _0000_TAU_START_INT_UNUSED;
    TDR00 = _0000_TAU_TDR00_VALUE;
    TO0 &= (uint16_t)~_0001_TAU_CH0_OUTPUT_VALUE_1;
    TOE0 &= (uint16_t)~_0001_TAU_CH0_OUTPUT_ENABLE;
    
    R_Config_TAU0_0_Mesure_Signal_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_0_Start
* Description  : This function starts the TAU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_0_Mesure_Signal_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TS0 |= _0001_TAU_CH0_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_0_Stop
* Description  : This function stops the TAU0 channel 0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_0_Mesure_Signal_Stop(void)
{
    TT0 |= _0001_TAU_CH0_STOP_TRG_ON;
    /* Mask channel 0 interrupt */
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */
/* 1124 nhu add */
void R_Config_TAU0_0_1_Mesure_Signal_Create(void)
{
	R_Config_TAU0_0_Mesure_Signal_Create();
	R_Config_TAU0_1_Mesure_Signal_Create();
}

void R_Config_TAU0_0_2_Mesure_Signal_Create(void)
{
	R_Config_TAU0_0_Mesure_Signal_Create();
	R_Config_TAU0_2_Mesure_Signal_Create();
}

void R_Config_TAU0_0_3_Mesure_Signal_Create(void)
{
	R_Config_TAU0_0_Mesure_Signal_Create();
	R_Config_TAU0_3_Mesure_Signal_Create();
}

void R_Config_TAU0_0_4_Mesure_Signal_Create(void)
{
	R_Config_TAU0_0_Mesure_Signal_Create();
	R_Config_TAU0_4_Mesure_Signal_Create();
}

void R_Config_TAU0_0_5_Mesure_Signal_Create(void)
{
	R_Config_TAU0_0_Mesure_Signal_Create();
	R_Config_TAU0_5_Mesure_Signal_Create();
}

void R_Config_TAU0_0_6_Mesure_Signal_Create(void)
{
	R_Config_TAU0_0_Mesure_Signal_Create();
	R_Config_TAU0_6_Mesure_Signal_Create();
}

void R_Config_TAU0_0_7_Mesure_Signal_Create(void)
{
	R_Config_TAU0_0_Mesure_Signal_Create();
	R_Config_TAU0_7_Mesure_Signal_Create();
}

void R_Config_TAU0_0_1_Mesure_Signal_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TMMK01 = 0U;    /* enable INTTM01 interrupt */
    TS0 |= (_0001_TAU_CH0_START_TRG_ON | _0002_TAU_CH1_START_TRG_ON);
}

void R_Config_TAU0_0_2_Mesure_Signal_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TMMK02 = 0U;    /* enable INTTM02 interrupt */
    TS0 |= (_0001_TAU_CH0_START_TRG_ON | _0004_TAU_CH2_START_TRG_ON);
}

void R_Config_TAU0_0_3_Mesure_Signal_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TMMK03 = 0U;    /* enable INTTM03 interrupt */
    TS0 |= (_0001_TAU_CH0_START_TRG_ON | _0008_TAU_CH3_START_TRG_ON);
}

void R_Config_TAU0_0_4_Mesure_Signal_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF04 = 0U;    /* clear INTTM04 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TMMK04 = 0U;    /* enable INTTM04 interrupt */
    TS0 |= (_0001_TAU_CH0_START_TRG_ON | _0010_TAU_CH4_START_TRG_ON);
}

void R_Config_TAU0_0_5_Mesure_Signal_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF05 = 0U;    /* clear INTTM05 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TMMK05 = 0U;    /* enable INTTM05 interrupt */
    TS0 |= (_0001_TAU_CH0_START_TRG_ON | _0020_TAU_CH5_START_TRG_ON);
}

void R_Config_TAU0_0_6_Mesure_Signal_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF06 = 0U;    /* clear INTTM06 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TMMK06 = 0U;    /* enable INTTM06 interrupt */
    TS0 |= (_0001_TAU_CH0_START_TRG_ON | _0040_TAU_CH6_START_TRG_ON);
}

void R_Config_TAU0_0_7_Mesure_Signal_Start(void)
{
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF07 = 0U;    /* clear INTTM07 interrupt flag */
    TMMK00 = 0U;    /* enable INTTM00 interrupt */
    TMMK07 = 0U;    /* enable INTTM07 interrupt */
    TS0 |= (_0001_TAU_CH0_START_TRG_ON | _0080_TAU_CH7_START_TRG_ON);
}

void R_Config_TAU0_0_1_Mesure_Signal_Stop(void)
{
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMMK01 = 1U;    /* disable INTTM01 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
    TS0 |= (_0001_TAU_CH0_STOP_TRG_ON | _0002_TAU_CH1_STOP_TRG_ON);
}

void R_Config_TAU0_0_2_Mesure_Signal_Stop(void)
{
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMMK02 = 1U;    /* disable INTTM02 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF02 = 0U;    /* clear INTTM02 interrupt flag */
    TS0 |= (_0001_TAU_CH0_STOP_TRG_ON | _0004_TAU_CH2_STOP_TRG_ON);
}

void R_Config_TAU0_0_3_Mesure_Signal_Stop(void)
{
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMMK03 = 1U;    /* disable INTTM03 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF03 = 0U;    /* clear INTTM03 interrupt flag */
    TS0 |= (_0001_TAU_CH0_STOP_TRG_ON | _0008_TAU_CH3_STOP_TRG_ON);
}

void R_Config_TAU0_0_4_Mesure_Signal_Stop(void)
{
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMMK04 = 1U;    /* disable INTTM04 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF04 = 0U;    /* clear INTTM04 interrupt flag */
    TS0 |= (_0001_TAU_CH0_STOP_TRG_ON | _0010_TAU_CH4_STOP_TRG_ON);
}

void R_Config_TAU0_0_5_Mesure_Signal_Stop(void)
{
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMMK05 = 1U;    /* disable INTTM05 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF05 = 0U;    /* clear INTTM05 interrupt flag */
    TS0 |= (_0001_TAU_CH0_STOP_TRG_ON | _0020_TAU_CH5_STOP_TRG_ON);
}

void R_Config_TAU0_0_6_Mesure_Signal_Stop(void)
{
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMMK06 = 1U;    /* disable INTTM06 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF06 = 0U;    /* clear INTTM06 interrupt flag */
    TS0 |= (_0001_TAU_CH0_STOP_TRG_ON | _0040_TAU_CH6_STOP_TRG_ON);
}

void R_Config_TAU0_0_7_Mesure_Signal_Stop(void)
{
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMMK07 = 1U;    /* disable INTTM07 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMIF07 = 0U;    /* clear INTTM07 interrupt flag */
    TS0 |= (_0001_TAU_CH0_STOP_TRG_ON | _0080_TAU_CH7_STOP_TRG_ON);
}
/* 1124 nhu add */
/* End user code. Do not edit comment generated here */
