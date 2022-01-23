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
* File Name    : Config_RTC.h
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_RTC.
* Creation Date: 2021-05-14
***********************************************************************************************************************/

#ifndef CFG_Config_RTC_H
#define CFG_Config_RTC_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_rtc.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define RTC_WAITTIME_2CYCLE                  (163U)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef struct
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t week;
    uint8_t month;
    uint8_t year;
} st_rtc_counter_value_t;
typedef struct
{
    uint8_t alarmwm;
    uint8_t alarmwh;
    uint8_t alarmww;
} st_rtc_alarm_value_t;
typedef enum
{
    HOUR12,
    HOUR24
} e_rtc_hour_system_t;
typedef enum
{
    HALFSEC = 1U,
    ONESEC,
    ONEMIN,
    ONEHOUR,
    ONEDAY,
    ONEMONTH
} e_rtc_int_period_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_RTC_Create(void);
void R_Config_RTC_Start(void);
void R_Config_RTC_Stop(void);
MD_STATUS R_Config_RTC_Set_HourSystem(e_rtc_hour_system_t hour_system);
MD_STATUS R_Config_RTC_Get_CounterValue(st_rtc_counter_value_t * const counter_read_val);
MD_STATUS R_Config_RTC_Set_CounterValue(st_rtc_counter_value_t counter_write_val);
MD_STATUS R_Config_RTC_Set_ConstPeriodInterruptOn(e_rtc_int_period_t period);
void R_Config_RTC_Set_ConstPeriodInterruptOff(void);
void R_Config_RTC_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
