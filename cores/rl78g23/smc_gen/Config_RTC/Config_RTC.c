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
* File Name    : Config_RTC.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_RTC.
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
#include "Config_RTC.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Create
* Description  : This function initializes the real-time clock module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Create(void)
{
    /* Supplies input clock */
    RTCWEN = 1U;
    /* Disable RTC clock operation */
    RTCE = 0U;
    /* Disable INTRTC interrupt */
    RTCMK = 1U;
    /* Clear INTRTC interrupt flag */
    RTCIF = 0U;
    /* Set INTRTC Low priority */
    RTCPR1 = 1U;
    RTCPR0 = 1U;
    /* Set fRTCCK */
    RTCC0 = _00_RTC_CLK_32KHZ;
    /* Set 12-/24-hour system and period of Constant-period interrupt (INTRTC) */
    RTCC0 |= (_00_RTC_RTC1HZ_DISABLE | _08_RTC_24HOUR_MODE | _02_RTC_INTRTC_CLOCK_1SEC);

    R_Config_RTC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Start
* Description  : This function enables the real-time clock.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Start(void)
{
    /* Clear INTRTC interrupt flag */
    RTCIF = 0U;
    /* Enable INTRTC interrupt */
    RTCMK = 0U;
    /* Enable RTC clock operation */
    RTCE = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Stop
* Description  : This function disables the real-time clock.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Stop(void)
{
    /* Disable RTC clock operation */
    RTCE = 0U;
    /* Disable INTRTC interrupt */
    RTCMK = 1U;
    /* Clear INTRTC interrupt flag */
    RTCIF = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Set_HourSystem
* Description  : This function chooses 12-hour system or 24-hour system.
* Arguments    : hour_system -
*                    the selection of real-time clock hour system
* Return Value : status -
*                    MD_OK, MD_ARGERROR, MD_BUSY1 or MD_BUSY2
***********************************************************************************************************************/
MD_STATUS R_Config_RTC_Set_HourSystem(e_rtc_hour_system_t hour_system)
{
    MD_STATUS status = MD_OK;
    volatile uint16_t w_count;

    switch (hour_system)
    {
        case HOUR12:

            if (_08_RTC_24HOUR_MODE == (RTCC0 & _08_RTC_RTCC0_AMPM))
            {
                RTCC1 |= _01_RTC_COUNTER_PAUSE;
                /* Change the waiting time according to the system */
                for (w_count = 0U; w_count < RTC_WAITTIME_2CYCLE; w_count++)
                {
                    NOP();
                }
                if (0U == RWST)
                {
                    status = MD_BUSY1;
                }
                else
                {
                    RTCC0 &= (uint8_t)~_08_RTC_24HOUR_MODE;
                    RTCC1 &= (uint8_t)~_01_RTC_COUNTER_PAUSE;
                    /* Change the waiting time according to the system */
                    for (w_count = 0U; w_count < RTC_WAITTIME_2CYCLE; w_count++)
                    {
                        NOP();
                    }

                    if (1U == RWST)
                    {
                        status = MD_BUSY2;
                    }
                }
            }

            break;

        case HOUR24:

            if (_00_RTC_12HOUR_MODE == (RTCC0 & _08_RTC_RTCC0_AMPM))
            {
                RTCC1 |= _01_RTC_COUNTER_PAUSE;
                /* Change the waiting time according to the system */
                for (w_count = 0U; w_count < RTC_WAITTIME_2CYCLE; w_count++)
                {
                    NOP();
                }

                if (0U == RWST)
                {
                    status = MD_BUSY1;
                }
                else
                {
                    RTCC0 |= _08_RTC_24HOUR_MODE;
                    RTCC1 &= (uint8_t)~_01_RTC_COUNTER_PAUSE;
                    /* Change the waiting time according to the system */
                    for (w_count = 0U; w_count < RTC_WAITTIME_2CYCLE; w_count++)
                    {
                        NOP();
                    }

                    if (1U == RWST)
                    {
                        status = MD_BUSY2;
                    }
                }
            }

            break;

        default:
            status = MD_ARGERROR;
            break;
    }
    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Get_CounterValue
* Description  : This function reads the results of real-time clock and store them in the variables.
* Arguments    : counter_read_val -
*                    the current real-time clock value (BCD code)
* Return Value : status -
*                    MD_OK, MD_BUSY1 or MD_BUSY2
***********************************************************************************************************************/
MD_STATUS R_Config_RTC_Get_CounterValue(st_rtc_counter_value_t * const counter_read_val)
{
    MD_STATUS status = MD_OK;
    volatile uint16_t w_count;
    /*Stops SEC to YEAR counters, read or write counter value*/
    RTCC1 |= _01_RTC_COUNTER_PAUSE;
    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_2CYCLE; w_count++)
    {
        NOP();
    }
    /* Checks wait status of counter */
    if (0U == RWST)
    {
        status = MD_BUSY1;
    }
    else
    {
        counter_read_val->sec = SEC;
        counter_read_val->min = MIN;
        counter_read_val->hour = HOUR;
        counter_read_val->week = WEEK;
        counter_read_val->day = DAY;
        counter_read_val->month = MONTH;
        counter_read_val->year = YEAR;
        /* Sets counter operation */
        RTCC1 &= (uint8_t)~_01_RTC_COUNTER_PAUSE;
        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count < RTC_WAITTIME_2CYCLE; w_count++)
        {
            NOP();
        }

        if (1U == RWST)
        {
            status = MD_BUSY2;
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Set_CounterValue
* Description  : This function changes the real-time clock value.
* Arguments    : counter_write_val -
*                    the expected real-time clock value (BCD code)
* Return Value : status -
*                    MD_OK, MD_BUSY1 or MD_BUSY2
***********************************************************************************************************************/
MD_STATUS R_Config_RTC_Set_CounterValue(st_rtc_counter_value_t counter_write_val)
{
    MD_STATUS status = MD_OK;
    volatile uint16_t w_count;
    /*Stops SEC to YEAR counters, read or write counter value*/
    RTCC1 |= _01_RTC_COUNTER_PAUSE;
    /* Change the waiting time according to the system */
    for (w_count = 0U; w_count < RTC_WAITTIME_2CYCLE; w_count++)
    {
        NOP();
    }

    if (0U == RWST)
    {
        status = MD_BUSY1;
    }
    else
    {
        if ((1U == RTCE) && (0U == RTCMK))
        {
            /* Disable INTRTC interrupt */
            RTCMK = 1U;

            SEC = counter_write_val.sec;
            MIN = counter_write_val.min;
            HOUR = counter_write_val.hour;
            WEEK = counter_write_val.week;
            DAY = counter_write_val.day;
            MONTH = counter_write_val.month;
            YEAR = counter_write_val.year;
            /* Clear matching detection flag */
            WAFG = 0U;
            /* Clear constant-period interrupt flag */
            RIFG = 0U;
            /* Clear INTRTC interrupt flag */
            RTCIF = 0U;
            /* Enable INTRTC interrupt */
            RTCMK = 0U;
        }
        else
        {
            SEC = counter_write_val.sec;
            MIN = counter_write_val.min;
            HOUR = counter_write_val.hour;
            WEEK = counter_write_val.week;
            DAY = counter_write_val.day;
            MONTH = counter_write_val.month;
            YEAR = counter_write_val.year;
        }
        /* Sets counter operation */
        RTCC1 &= (uint8_t)~_01_RTC_COUNTER_PAUSE;
        /* Change the waiting time according to the system */
        for (w_count = 0U; w_count < RTC_WAITTIME_2CYCLE; w_count++)
        {
            NOP();
        }

        if (1U == RWST)
        {
            status = MD_BUSY2;
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Set_ConstPeriodInterruptOn
* Description  : This function enables constant-period interrupt.
* Arguments    : period -
*                    the constant period of INTRTC
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_RTC_Set_ConstPeriodInterruptOn(e_rtc_int_period_t period)
{
    MD_STATUS status = MD_OK;
    if ((period < HALFSEC) || (period > ONEMONTH))
    {
        status = MD_ARGERROR;
    }
    else
    {
        /* Disable INTRTC */
        RTCMK = 1U;
        RTCC0 = (RTCC0 & _F8_RTC_INTRTC_CLEAR) | period;
        RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;
        /* Clear INTRTC interrupt flag */
        RTCIF = 0U;
        /* Enable INTRTC interrupt */
        RTCMK = 0U;
    }
    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_RTC_Set_ConstPeriodInterruptOff
* Description  : This function disables constant-period interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_RTC_Set_ConstPeriodInterruptOff(void)
{
    RTCC0 &= _F8_RTC_INTRTC_CLEAR;
    RTCC1 &= (uint8_t)~_08_RTC_INTC_GENERATE_FLAG;
    /* Clear INTRTC interrupt flag */
    RTCIF = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
