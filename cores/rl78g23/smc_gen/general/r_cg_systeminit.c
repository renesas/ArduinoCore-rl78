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
* File Name    : r_cg_systeminit.c
* Version      : 1.0.1
* Device(s)    : R7F100GLGxFB
* Description  : This file implements system initializing function.
* Creation Date: 2021-05-14
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
#include "Config_ADC.h"
#include "Config_IICA0.h"
#include "Config_IICA1.h"
#include "Config_WDT.h"
#include "Config_RTC.h"
#include "r_cg_sau_common.h"
#include "r_cg_tau_common.h"
#include "r_cg_itl_common.h"
/* Start user code for include. Do not edit comment generated here */
/* 1112 Ueeda add */
#include "Config_INTC.h"
/* 1112 Ueeda add */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Systeminit
* Description  : This function initializes every macro
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Systeminit(void)
{
    PRR0 = 0x7FU;    /* reset IICA, ADC, TAU and SAU module */
    PRR1 = 0xF3U;    /* reset DAC, SMS, COMP, ITL, REMC, CTSU module */
    PRR0 = 0x00U;    /* release IICA, ADC, TAU and SAU module */
    PRR1 = 0x00U;    /* release DAC, SMS, COMP, ITL, REMC, CTSU module */
    /* Set peripheral settings */
    SAU0EN = 1U;    /* supplies input clock */    /* R_SAU0_Create(); */
    SAU1EN = 1U;    /* supplies input clock */    /* R_SAU1_Create(); */
    TAU0EN = 1U;    /* start TAU0 clock */        /* R_TAU0_Create(); */
    TML32EN = 1U;    /* start 32-bits IT clock */ /* R_ITL_Create();  */
    R_Config_ADC_Create();
    /* R_Config_IICA0_Create(); */
    /* R_Config_IICA1_Create(); */
    /* R_Config_WDT_Create(); */

    /* The RTC initializes when using the function. */
    R_Config_RTC_Create();

}
