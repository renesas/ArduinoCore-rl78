/***************************************************************************
 *
 * PURPOSE
 *   RTC(Real Time Clock) class header file.
 *
 * TARGET DEVICE
 *   RL78/G13
 *
 * AUTHOR
 *   Renesas Solutions Corp.
 *
 * $Date:: 2013-01-25 14:32:21 +0900#$
 *
 ***************************************************************************
 * Copyright (C) 2012 Renesas Electronics. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * See file LICENSE.txt for further informations on licensing terms.
 ***************************************************************************/
/**
 * @file  RTC.h
 * @brief RL78マイコン内蔵の時計機能（RTC：リアル・タイム・クロック）を使うため
 * のクラスライブラリのヘッダファイルです。
 */
#ifndef RTC_H
#define RTC_H
/***************************************************************************/
/*    Include MCU depend defines.                                          */
/***************************************************************************/
#include <Arduino.h>
#include <utility/RLduino78_RTC.h>

extern "C"
{
#include "Config_RTC.h"
}

/***************************************************************************/
/*    Interrupt handler                                                    */
/***************************************************************************/


/***************************************************************************/
/*    Include Header Files                                                 */
/***************************************************************************/


/***************************************************************************/
/*    Macro Definitions                                                    */
/***************************************************************************/

#define PERIOD_TIME_NONE        0
#define PERIOD_TIME_HALFSEC     HALFSEC
#define PERIOD_TIME_ONESEC      ONESEC
#define PERIOD_TIME_ONEMIN      ONEMIN
#define PERIOD_TIME_ONEHOUR     ONEHOUR
#define PERIOD_TIME_ONEDAY      ONEDAY
#define PERIOD_TIME_ONEMON      ONEMONTH

/***************************************************************************/
/*    Type  Definitions                                                    */
/***************************************************************************/
/**
 * RTCクラス
 ***************************************************************************/
class RTCClass
{
private:

public:
    RTCClass();
    ~RTCClass();

    int begin();
    int end();
    bool setDateTime(int year, int mon, int day, int hour, int min, int sec, int week = RTC_WEEK_SUNDAY);
    bool getDateTime(int &year, int &mon, int &day, int &hour, int &min, int &sec, int &week);

    void attachAlarmHandler(void (*fFunction)(void));
    void setAlarmTime(int hour, int min, int week_flag = RTC_ALARM_EVERYDAY);
    void alarmOn();
    void alarmOff();

    void attachConstantPeriodHandler(void (*fFunction)(void));
    void constantPeriodOn(int cycle = PERIOD_TIME_ONESEC);
    void constantPeriodOff();
};

extern RTCClass RTC;

/***************************************************************************/
/*    Function prototypes                                                  */
/***************************************************************************/


/***************************************************************************/
/*    Global Variables                                                     */
/***************************************************************************/

extern "C"
{
extern voidFunc_t alarmUserCallback;
extern voidFunc_t periodTimeUserCallback;
}


/***************************************************************************/
/*    Local Variables                                                      */
/***************************************************************************/


/***************************************************************************/
/*    Global Routines                                                      */
/***************************************************************************/


/***************************************************************************/
/*    Local Routines                                                       */
/***************************************************************************/


/***************************************************************************/
/* End of module                                                           */
/***************************************************************************/
#endif /* RTC_H */

