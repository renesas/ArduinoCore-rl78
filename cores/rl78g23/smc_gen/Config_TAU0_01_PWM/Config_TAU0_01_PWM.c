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
* File Name    : Config_TAU0_01_PWM.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_TAU0_01_PWM.
* Creation Date: 2021-10-07
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
#include "Config_TAU0_01_PWM.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_01_PWM_Create
* Description  : This function initializes the TAU0 channel0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_01_PWM_Create(void)
{
    TPS0 &= _FFF0_TAU_CKM0_CLEAR;
    TPS0 |= _0000_TAU_CKM0_FCLK_0;
    TT0 |= (_0002_TAU_CH1_STOP_TRG_ON | _0001_TAU_CH0_STOP_TRG_ON);
    TMMK00 = 1U;    /* disable INTTM00 interrupt */
    TMIF00 = 0U;    /* clear INTTM00 interrupt flag */
    TMMK01 = 1U;    /* disable INTTM01 interrupt */
    TMIF01 = 0U;    /* clear INTTM01 interrupt flag */
    /* Channel 0 is used as master channel for PWM output function */
    TMR00 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_TRIGGER_SOFTWARE | 
            _0001_TAU_MODE_PWM_MASTER;
    TDR00 = _F9FF_TAU_TDR00_VALUE;
    TO0 &= (uint16_t)~_0001_TAU_CH0_OUTPUT_VALUE_1;
    TOE0 &= (uint16_t)~_0001_TAU_CH0_OUTPUT_ENABLE;
    /* Channel 1 is used as slave channel for PWM output function */
    TMR01 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_COMBINATION_SLAVE | 
            _0400_TAU_TRIGGER_MASTER_INT | _0009_TAU_MODE_PWM_SLAVE;
    TDR01 = _7D00_TAU_TDR01_VALUE;
    TOM0 |= _0002_TAU_CH1_SLAVE_OUTPUT;
    TOL0 &= (uint16_t)~_0002_TAU_CH1_OUTPUT_LEVEL_L;
    TO0 &= (uint16_t)~_0002_TAU_CH1_OUTPUT_VALUE_1;
    TOE0 |= _0002_TAU_CH1_OUTPUT_ENABLE;
    /* Set TO01 pin */
    PMCE1 &= 0xBFU;
    PFOE0 |= 0x02U;
    CCDE &= 0xFEU;
    P1 &= 0xBFU;
    PM1 &= 0xBFU;

    R_Config_TAU0_01_PWM_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_01_PWM_Start
* Description  : This function starts the TAU0 channel0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_01_PWM_Start(void)
{
    TOE0 |= _0002_TAU_CH1_OUTPUT_ENABLE;
    TS0 |= (_0002_TAU_CH1_START_TRG_ON | _0001_TAU_CH0_START_TRG_ON);
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_01_PWM_Stop
* Description  : This function stops the TAU0 channel0 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_01_PWM_Stop(void)
{
    TT0 |= (_0002_TAU_CH1_STOP_TRG_ON | _0001_TAU_CH0_STOP_TRG_ON);
    TOE0 &= (uint16_t)~_0002_TAU_CH1_OUTPUT_ENABLE;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
