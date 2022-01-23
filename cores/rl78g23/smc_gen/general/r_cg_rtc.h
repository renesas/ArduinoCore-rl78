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
* File Name    : r_cg_rtc.h
* Version      : 1.0.1
* Device(s)    : R7F100GLGxFB
* Description  : General header file for RTC peripheral.
* Creation Date: 2021-05-14
***********************************************************************************************************************/

#ifndef RTC_H
#define RTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Peripheral Enable Register 0 (PER0)
*/
/* Control of real-time clock (RTC) input clock (RTCWEN) */
#define _00_RTC_CLOCK_STOP                                    (0x00U)    /* stops supply of input clock */
#define _80_RTC_CLOCK_SUPPLY                                  (0x80U)    /* supplies input clock */

/*
    Subsystem Clock Supply Mode Control Register (OSMC)
*/
/* Selection of operation clock (fRTCCK) for real-time clock (WUTMMCK0) */
#define _00_RTC_CLK_FSXR                                      (0x00U)    /* subsystem clock (fSXR) or fRTC128HZ */
#define _10_RTC_CLK_FIL                                       (0x10U)    /* low-speed on-chip oscillator clock (fIL) */

/*
    Real-Time Clock Control Register 0 (RTCC0)
*/
/* Real-time clock operation control (RTCE) */
#define _00_RTC_COUNTER_STOP                                  (0x00U)    /* stops counter operation */
#define _80_RTC_COUNTER_START                                 (0x80U)    /* starts counter operation */
/* RTC1HZ pin output control (RCLOE1) */
#define _00_RTC_RTC1HZ_DISABLE                                (0x00U)    /* disables output of the RTC1HZ pin (1 Hz) */
#define _20_RTC_RTC1HZ_ENABLE                                 (0x20U)    /* enables output of the RTC1HZ pin (1 Hz) */
/* Operation clock (fRTCCLK) selection (RTC128EN) */
#define _00_RTC_CLK_32KHZ                                     (0x00U)    /* 32.768kHz */
#define _10_RTC_CLK_128HZ                                     (0x10U)    /* 128Hz */
/* Selection of 12-/24-hour system (AMPM) */
#define _08_RTC_HOURSYSTEM_CLEAR                              (0x08U)    /* clear the AMPM bit */
#define _08_RTC_RTCC0_AMPM                                    (0x08U)    /* AMPM bit status detect */
#define _00_RTC_12HOUR_MODE                                   (0x00U)    /* 12-hour system */
#define _08_RTC_24HOUR_MODE                                   (0x08U)    /* 24-hour system */
/* Constant-period interrupt (INTRTC) selection (CT2 - CT0) */
#define _F8_RTC_INTRTC_CLEAR                                  (0xF8U)    /* clear constant-period interrupt function */
#define _00_RTC_INTRTC_NOT_GENERATE                           (0x00U)    /* does not use constant-period
                                                                            interrupt function */
#define _01_RTC_INTRTC_CLOCK_05SEC                            (0x01U)    /* once per 0.5 second */
#define _02_RTC_INTRTC_CLOCK_1SEC                             (0x02U)    /* once per 1 second */
#define _03_RTC_INTRTC_CLOCK_1MINU                            (0x03U)    /* once per 1 minute */
#define _04_RTC_INTRTC_CLOCK_1HOUR                            (0x04U)    /* once per 1 hour */
#define _05_RTC_INTRTC_CLOCK_1DAY                             (0x05U)    /* once per 1 day */
#define _06_RTC_INTRTC_CLOCK_1MONTH                           (0x06U)    /* once per 1 month */

/*
    Real-Time Clock Control Register 1 (RTCC1)
*/
/* Alarm operation control (WALE) */
#define _00_RTC_ALARM_DISABLE                                 (0x00U)    /* alarm match operation is invalid */
#define _80_RTC_ALARM_ENABLE                                  (0x80U)    /* alarm match operation is valid */
/* Control of alarm interrupt (INTRTC) function operation (WALIE) */
#define _00_RTC_ALARM_INT_DISABLE                             (0x00U)    /* does not generate interrupt on
                                                                            matching of alarm */
#define _40_RTC_ALARM_INT_ENABLE                              (0x40U)    /* generates interrupt on matching of alarm */
/* Alarm detection status flag (WAFG) */
#define _00_RTC_ALARM_MISMATCH                                (0x00U)    /* alarm mismatch */
#define _10_RTC_ALARM_MATCH                                   (0x10U)    /* detection of matching of alarm */
/* Constant-period interrupt status flag (RIFG) */
#define _00_RTC_INTC_NOTGENERATE_FLAG                         (0x00U)    /* constant-period interrupt
                                                                            is not generated */
#define _08_RTC_INTC_GENERATE_FLAG                            (0x08U)    /* constant-period interrupt is generated */
/* Wait status flag of real-time clock (RWST) */
#define _00_RTC_COUNTER_OPERATING                             (0x00U)    /* counter is operating */
#define _02_RTC_COUNTER_STOP                                  (0x02U)    /* mode to read or write counter value */
/* Wait control of real-time clock (RWAIT) */
#define _00_RTC_COUNTER_SET                                   (0x00U)    /* sets counter operation */
#define _01_RTC_COUNTER_PAUSE                                 (0x01U)    /* stops SEC to YEAR counters.
                                                                            Mode to read or write counter value */

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
/* End user code. Do not edit comment generated here */
#endif
