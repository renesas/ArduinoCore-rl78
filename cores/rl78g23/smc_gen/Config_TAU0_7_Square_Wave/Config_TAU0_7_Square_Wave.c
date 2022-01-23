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
* File Name    : Config_TAU0_7_Square_Wave.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxLA
* Description  : This file implements device driver for Config_TAU0_7_Square_Wave.
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
#include "Config_TAU0_7_Square_Wave.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_7_Square_Wave_Create
* Description  : This function initializes the TAU0 channel7 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_7_Square_Wave_Create(void)
{
    TPS0 &= _FFF0_TAU_CKM0_CLEAR;
    TPS0 |= _0000_TAU_CKM0_FCLK_0;
    /* Stop channel 7 */
    TT0 |= _0080_TAU_CH7_STOP_TRG_ON;
    /* Mask channel 7 interrupt */
    TMMK07 = 1U;    /* disable INTTM07 interrupt */
    TMIF07 = 0U;    /* clear INTTM07 interrupt flag */
    /* TAU07 used as square output function */
    TMR07 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0000_TAU_TRIGGER_SOFTWARE | 
            _0000_TAU_MODE_INTERVAL_TIMER | _0001_TAU_START_INT_USED;
    TDR07 = _F9FF_TAU_TDR07_VALUE;
    TOM0 &= (uint16_t)~_0080_TAU_CH7_SLAVE_OUTPUT;
    TOL0 &= (uint16_t)~_0080_TAU_CH7_OUTPUT_LEVEL_L;
    TO0 &= (uint16_t)~_0080_TAU_CH7_OUTPUT_VALUE_1;
    TOE0 |= _0080_TAU_CH7_OUTPUT_ENABLE;
    /* Set TO07 pin */
    PFOE0 |= 0x80U;
    P4 &= 0xFDU;
    PM4 &= 0xFDU;
    
    R_Config_TAU0_7_Square_Wave_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_7_Square_Wave_Start
* Description  : This function starts the TAU0 channel7 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_7_Square_Wave_Start(void)
{
    TOE0 |= _0080_TAU_CH7_OUTPUT_ENABLE;
    TS0 |= _0080_TAU_CH7_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_7_Square_Wave_Stop
* Description  : This function stops the TAU0 channel7 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_7_Square_Wave_Stop(void)
{
    TT0 |= _0080_TAU_CH7_STOP_TRG_ON;
    TOE0 &= (uint16_t)~_0080_TAU_CH7_OUTPUT_ENABLE;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
