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
* File Name    : Config_TAU0_7_Mesure_Signal.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxLA
* Description  : This file implements device driver for Config_TAU0_7_Mesure_Signal.
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
#include "Config_TAU0_7_Mesure_Signal.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* For TAU0_ch7 pulse measurement */
extern volatile uint32_t g_tau0_ch7_width;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_7_Mesure_Signal_Create
* Description  : This function initializes the TAU0 channel7 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_7_Mesure_Signal_Create(void)
{
    TPS0 &= _FFF0_TAU_CKM0_CLEAR;
    TPS0 |= _0005_TAU_CKM0_FCLK_5;
    /* Stop channel 7 */
    TT0 |= _0080_TAU_CH7_STOP_TRG_ON;
    /* Mask channel 7 interrupt */
    TMMK07 = 1U;    /* disable INTTM07 interrupt */
    TMIF07 = 0U;    /* clear INTTM07 interrupt flag */
    /* Set INTTM07 low priority */
    TMPR107 = 1U;
    TMPR007 = 1U;
    /* TAU07 is used to measure input pulse low-/high-width */
    TMR07 = _0000_TAU_CLOCK_SELECT_CKM0 | _0000_TAU_CLOCK_MODE_CKS | _0200_TAU_TRIGGER_TIMN_BOTH | 
    		_0080_TAU_TIMN_EDGE_BOTH_LOW | _000C_TAU_MODE_HIGHLOW_MEASURE;
    TOM0 &= (uint16_t)~_0080_TAU_CH7_SLAVE_OUTPUT;
    TOL0 &= (uint16_t)~_0080_TAU_CH7_OUTPUT_LEVEL_L;
    TO0 &= (uint16_t)~_0080_TAU_CH7_OUTPUT_VALUE_1;
    TOE0 &= (uint16_t)~_0080_TAU_CH7_OUTPUT_ENABLE;
    /* Set TI07 pin */
    PM4 |= 0x02U;
    
    R_Config_TAU0_7_Mesure_Signal_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_7_Mesure_Signal_Start
* Description  : This function starts the TAU0 channel7 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_7_Mesure_Signal_Start(void)
{
    TMIF07 = 0U;    /* clear INTTM07 interrupt flag */
    TMMK07 = 0U;    /* enable INTTM07 interrupt */
    TS0 |= _0080_TAU_CH7_START_TRG_ON;
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_7_Mesure_Signal_Stop
* Description  : This function stops the TAU0 channel7 counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_7_Mesure_Signal_Stop(void)
{
    TT0 |= _0080_TAU_CH7_STOP_TRG_ON;
    /* Mask channel 7 interrupt */
    TMMK07 = 1U;    /* disable INTTM07 interrupt */
    TMIF07 = 0U;    /* clear INTTM07 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_TAU0_7_Mesure_Signal_Get_PulseWidth
* Description  : This function measures TAU0 channel 7 input pulse width.
* Arguments    : width -
*                    the address where to write the input pulse width
* Return Value : None
***********************************************************************************************************************/
void R_Config_TAU0_7_Mesure_Signal_Get_PulseWidth(uint32_t * const width)
{
    /* For channel 7 pulse measurement */
    *width = g_tau0_ch7_width;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
