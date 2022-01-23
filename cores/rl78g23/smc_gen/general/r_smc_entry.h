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
* File Name    : r_smc_entry.h
* Version      : 1.0.1
* Device(s)    : R7F100GLGxFB
* Description  : SMC platform header file..
* Creation Date: 2021-05-14
***********************************************************************************************************************/

#ifndef SMC_ENTRY_H
#define SMC_ENTRY_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_ADC.h"
#include "Config_IICA0.h"
#include "Config_IICA1.h"
#include "Config_WDT.h"
#include "Config_IICA01.h"
#include "Config_IICA11.h"
#include "Config_RTC.h"
#include "Config_ITL000.h"
#include "Config_ITL001.h"
#include "Config_ITL012.h"
#include "Config_UART0.h"
#include "Config_UART1.h"
#include "Config_UART2.h"
#include "Config_CSI11.h"
#include "r_cg_sau_common.h"
#include "r_cg_tau_common.h"
#include "r_cg_itl_common.h"
#include "r_cg_iica_common.h"
#include "r_cg_ad_common.h"
#include "r_cg_rtc_common.h"
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */
/* 1006 Nhu add */
#include "Config_TAU0_01_PWM.h"
#include "Config_TAU0_23_PWM.h"
#include "Config_TAU0_45_PWM.h"
#include "Config_TAU0_67_PWM.h"
/* 1006 Nhu add */

/* 1108 Ueeda add */
#include "Config_INTC.h"
/* 1108 Ueeda add */

/* 1112 nhu add */
#include "Config_TAU0_1_Square_Wave.h"
#include "Config_TAU0_2_Square_Wave.h"
#include "Config_TAU0_3_Square_Wave.h"
#include "Config_TAU0_4_Square_Wave.h"
#include "Config_TAU0_5_Square_Wave.h"
#include "Config_TAU0_6_Square_Wave.h"
#include "Config_TAU0_7_Square_Wave.h"

#include "Config_TAU0_0_Mesure_Signal.h"
#include "Config_TAU0_1_Mesure_Signal.h"
#include "Config_TAU0_2_Mesure_Signal.h"
#include "Config_TAU0_3_Mesure_Signal.h"
#include "Config_TAU0_4_Mesure_Signal.h"
#include "Config_TAU0_5_Mesure_Signal.h"
#include "Config_TAU0_6_Mesure_Signal.h"
#include "Config_TAU0_7_Mesure_Signal.h"
/* 1112 nhu add */
/* End user code. Do not edit comment generated here */
#endif

