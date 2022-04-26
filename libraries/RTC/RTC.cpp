/***************************************************************************
 *
 * PURPOSE
 *   RTC(Real Time Clock) class module file.
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
 * @file  RTC.cpp
 * @brief RL78マイコン内蔵の時計機能（RTC：リアル・タイム・クロック）を使うためのクラスライブラリです。
 */

/***************************************************************************/
/*    Include Header Files                                                 */
/***************************************************************************/
#include "RTC.h"


/***************************************************************************/
/*    Macro Definitions                                                    */
/***************************************************************************/
#define RTC_WAIT_10USEC 320 //!< 10 us待ちカウント値


/***************************************************************************/
/*    Type  Definitions                                                    */
/***************************************************************************/


/***************************************************************************/
/*    Function prototypes                                                  */
/***************************************************************************/
static void rtc_pause()
{
    RTCMK        = 1;       // INTRTC割り込み禁止
    RTCC1 |=  0x01;
    RTCMK        = 0;       // INTRTC割り込み許可
     for(int i = 0; i < RTC_WAIT_10USEC; i++ ) {
        NOP();
    }
}

static void rtc_resume()
{
    RTCMK        = 1;       // INTRTC割り込み禁止
    RTCC1 &= ~0x01;
    RTCMK        = 0;       // INTRTC割り込み許可
    for(int i = 0; i < RTC_WAIT_10USEC; i++ ) {
        NOP();
    }
}

static inline uint8_t HEX2BCD(int s16HEX)
{
    return ((s16HEX / 10) << 4) | (s16HEX % 10);
}

static inline int BCD2HEX(uint8_t u8BCD)
{
    return ((u8BCD >> 4) * 10) + (u8BCD & 0x0F);
}

/***************************************************************************/
/*    Global Variables                                                     */
/***************************************************************************/

/***************************************************************************/
/*    Local Variables                                                      */
/***************************************************************************/
RTCClass RTC;

/***************************************************************************/
/*    Global Routines                                                      */
/***************************************************************************/
/** ************************************************************************
 * @addtogroup group101
 * 
 * @{
 ***************************************************************************/
/** ************************************************************************
 * @defgroup group13 時計機能（クラスライブラリ）
 * 
 * @{
 ***************************************************************************/
/**
 * RTCクラスのコンストラクタ
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
RTCClass::RTCClass(void)
{

}

/**
 * RTCクラスのデストラクタ
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
RTCClass::~RTCClass()
{
	end();
}

/**
 * RTCを開始します。
 *
 * @return 
 *
 * @attention なし
 ***************************************************************************/
int RTCClass::begin()
{
#if !defined(G23_FPB)
    return rtc_init();
#else
  if (RTCE == 0)
  {
    // Initialize RTC
    R_Config_RTC_Create();

    // Start RTC
    R_Config_RTC_Start();

    return true;
  }
  else
  {
      if (!R_RTC_IsPowerOn())
      {
        R_RTC_Set_PowerOn();
      }

      // When called while the RTC counter is running.
      return false;
  }
#endif
}


/**
 * RTCを停止します。
 *
 * @return 
 *
 * @attention なし
 ***************************************************************************/
int RTCClass::end()
{
#if !defined(G23_FPB)
    return rtc_deinit();
#else
  if (!R_RTC_IsPowerOn())
  {
    R_RTC_Set_PowerOn();
  }

  if (RTCE == 0)
  {
      return false;
  }
  else
  {
      // Stop RTC
      R_Config_RTC_Stop();

      // Clear handler
      alarmUserCallback = NULL;
      periodTimeUserCallback = NULL;

      return true;
  }
#endif
}


/**
 * RTCの時間を設定します。
 *
 * @param[in] year 年を指定します。
 * @param[in] mon  月を指定します。
 * @param[in] day  日を指定します。
 * @param[in] hour 時を指定します。
 * @param[in] min  分を指定します。
 * @param[in] sec  秒を指定します。
 * @param[in] week 曜日を指定します。
 *
 * @return 時間の設定に成功した場合はtrueを返却します。失敗した場合はfalseを返却します。
 *
 * @attention なし
 ***************************************************************************/
bool RTCClass::setDateTime(int year, int mon, int day, int hour, int min, int sec, int week)
{
	bool bError = true;
#if !defined(G23_FPB)
	RTC_TIMETYPE time;

	time.year   = year;
	time.mon    = mon;
	time.day    = day;
	time.hour   = hour;
	time.min    = min;
	time.second = sec;
	time.weekday= week;

	if (rtc_set_time(&time) == 0) {
		bError = false;
	}
#else
    st_rtc_counter_value_t val;
    MD_STATUS ret;

    val.year    = HEX2BCD(year % 100);
    val.month   = HEX2BCD(mon);
    val.day     = HEX2BCD(day);
    val.hour    = HEX2BCD(hour);
    val.min     = HEX2BCD(min);
    val.sec     = HEX2BCD(sec);
    val.week    = HEX2BCD(week);

    /**
     * Follow the implementation contents of the sample program of APN (R01AN5618).
     */
#if (false)
    ret = R_Config_RTC_Set_CounterValue(val);
#else
    /* This function does not use R_Config_RTC_Set_CounterValue(),
       because it always returns MD_BUSY1 until RTC is running. */
    {
        /* Initialize an RTC. */
        SUBCUD = 0x00;                /* The clock error corrections are NOT used. */

        /************************************/
        /* Set the Current time             */
        /************************************/
        rtc_pause();
        if (RWST == 1)
        {
            SEC   = val.sec;
            MIN   = val.min;
            HOUR  = val.hour;
            WEEK  = val.week;
            DAY   = val.day;
            MONTH = val.month;
            YEAR  = val.year;
            rtc_resume();
            if (RWST == 1U) {
                bError =  false;
            }
        }
        else
        {
            bError =  false;
        }
    }
    ret = MD_OK;
#endif
    if (MD_OK != ret)
    {
        bError =  false;
    }

#endif

	return (bError);
}


/**
 * RTCの時間を取得します。
 *
 * @param[out] year 年の格納先を指定します。
 * @param[out] mon  月の格納先を指定します。
 * @param[out] day  日の格納先を指定します。
 * @param[out] hour 時の格納先を指定します。
 * @param[out] min  分の格納先を指定します。
 * @param[out] sec  秒の格納先を指定します。
 * @param[out] week 曜日の格納先を指定します。
 *
 * @return 時間の取得に成功した場合はtrueを返却します。失敗した場合はfalseを返却します。
 *
 * @attention なし
 ***************************************************************************/
bool RTCClass::getDateTime(int &year, int &mon, int &day, int &hour, int &min, int &sec, int &week)
{
	bool bError = true;
#if !defined(G23_FPB)
	RTC_TIMETYPE time;

	if (rtc_get_time(&time) == 0) {
		year = 0;
		mon  = 0;
		day  = 0;
		hour = 0;
		sec  = 0;
		week = 0;
		bError = false;
	}
	else {
		year = time.year;
		mon  = time.mon;
		day  = time.day;
		hour = time.hour;
		min  = time.min;
		sec  = time.second;
		week = time.weekday;
	}
#else
    st_rtc_counter_value_t val;
    MD_STATUS ret;

    /**
     * Follow the implementation contents of the sample program of APN (R01AN5618).
     */
#if (false)
    if (MD_OK == R_Config_RTC_Get_CounterValue(&val))
    {
        year    = BCD2HEX(val.year);
        mon     = BCD2HEX(val.month);
        day     = BCD2HEX(val.day);
        hour    = BCD2HEX(val.hour);
        min     = BCD2HEX(val.min);
        sec     = BCD2HEX(val.sec);
        week    = BCD2HEX(val.week);
#else
    rtc_pause();
    if (RWST == 1)
    {
        year    = BCD2HEX(YEAR);
        mon     = BCD2HEX(MONTH);
        day     = BCD2HEX(DAY);
        hour    = BCD2HEX(HOUR);
        min     = BCD2HEX(MIN);
        sec     = BCD2HEX(SEC);
        week    = BCD2HEX(WEEK);

        rtc_resume();
        if (RWST == 1U) {
            bError  = false;
        }
#endif
    }
    else
    {
        year    = 0;
        mon     = 0;
        day     = 0;
        hour    = 0;
        min     = 0;
        sec     = 0;
        bError  = false;
    }
#endif
	return (bError);
}


/**
 * アラーム時に実行するハンドラを登録します。
 *
 * @param[in] fFunction アラーム時に実行するハンドラを指定します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void RTCClass::attachAlarmHandler(void (*fFunction)(void))
{
    alarmUserCallback = NULL;
	// Handler registration when using the alarm function.
    alarmUserCallback = fFunction;

}


/**
 * アラーム時間を設定します。
 *
 * @param[in] hour      時を指定します。
 * @param[in] min       分を指定します。
 * @param[in] week_flag 曜日を指定します。複数の曜日を指定する場合は論理和で接続します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void RTCClass::setAlarmTime(int hour, int min, int week_flag)
{
    st_rtc_alarm_value_t val;

    // Stop RTC
    R_Config_RTC_Stop();

    val.alarmwh = HEX2BCD(hour);
    val.alarmwm = HEX2BCD(min);
    val.alarmww = week_flag;

    R_Config_RTC_Set_AlarmValue(val);

    // Start RTC
    R_Config_RTC_Start();

}

/**
 * アラームをONにします。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void RTCClass::alarmOn()
{
    R_Config_RTC_Set_AlarmOn();
}

/**
 * アラームをOFFにします。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void RTCClass::alarmOff()
{
    attachAlarmHandler(NULL);
    R_Config_RTC_Set_AlarmOff();
    if (1 == RTCMK)
    {
        RTCMK = 0;
    }
}

/**
 * register a handler that executes at regular intervals.
 *
 * @param[in] fFunction     set handler to execute
 *
 * @return none
 *
 * @attention none
 */
void RTCClass::attachConstantPeriodHandler(void (*fFunction)(void))
{
    periodTimeUserCallback = NULL;
    periodTimeUserCallback = fFunction;
}


/**
 * Start periodic processing.
 *
 * @return none
 *
 * @attention none
 */
void RTCClass::constantPeriodOn(int cycle)
{
    int ret;
    e_rtc_int_period_t ct = (e_rtc_int_period_t)cycle;

    ret = R_Config_RTC_Set_ConstPeriodInterruptOn(ct);
    if (1 == ret) {};

}

/**
 * Stop periodec processing.
 *
 * @return none
 *
 * @attention none
 */
void RTCClass::constantPeriodOff()
{
    attachConstantPeriodHandler(NULL);
    R_Config_RTC_Set_ConstPeriodInterruptOff();
    if (1 == RTCMK)
    {
        RTCMK = 0;
    }
}
/** @} */
/** @} group101 */


/***************************************************************************/
/*    Local Routines                                                       */
/***************************************************************************/


/***************************************************************************/
/* End of module                                                           */
/***************************************************************************/
