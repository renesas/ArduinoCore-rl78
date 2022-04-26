#include "wiring_private.h"
#include "pins_arduino.h"
#include "pintable.h"
//#include "rl78/interrupt_handlers.h"
#include "r_cg_interrupt_handlers.h"
//extern "C"
//#include "r_cg_timer.h"

#define	ADS_TEMP_SENSOR			(0x80)
#define	ADS_REF_VOLTAGE			(0x81)

uint8_t g_u8ResetFlag;
uint8_t g_u8PowerManagementMode = PM_NORMAL_MODE;
uint8_t g_u8OperationClockMode = CLK_HIGH_SPEED_MODE;

extern uint8_t g_u8ResetFlag;
extern uint8_t g_u8PowerManagementMode;
extern uint8_t g_u8OperationClockMode;
extern volatile unsigned long g_u32delay_timer;
extern volatile unsigned long g_timer05_overflow_count;
extern uint8_t g_delay_cnt_flg;
extern uint8_t g_delay_cnt_micros_flg;
extern volatile unsigned long g_u32delay_micros_timer;

extern uint8_t g_u8ADUL;
extern uint8_t g_u8ADLL;

void (*INT_TM_HOOK)() ;

extern "C" {
#include "r_smc_entry.h"
}


// 周期起動ハンドラ関数テーブル
static struct {
	fITInterruptFunc_t afCyclicHandler;
	uint32_t au32CyclicTime;
	uint32_t au32RemainTime;
	uint32_t au32LastTime;
} g_CyclicHandlerTable[MAX_CYCLIC_HANDLER] = {
	{NULL, 0, 0, 0},
};
fITInterruptFunc_t	g_fITInterruptFunc = NULL;	//!< ユーザー定義インターバルタイマハンドラ



#if !defined(G23_FPB)
/**
 * タイマーアレイユニットの開始
 *
 * @param[in] u8TimerCloc タイマクロックを指定してください。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void _startTAU0(uint16_t u16TimerClock)
{
//	R_Config_TAU0_Create(u16TimerClock);
}

void _startTAU1(uint16_t u16TimerClock)
{
//	R_Config_TAU1_Create(u16TimerClock);
}
#endif
/**
 * タイマーチャンネルの開始
 *
 * @param[in] u8Timer 開始するタイマ番号
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
#if !defined(G23_FPB)
void _startTimerChannel(uint8_t u8TimerChannel, uint16_t u16TimerMode, uint16_t u16Interval, bool bPWM, bool bInterrupt)
{
	if(bPWM==true)
	{
		if (u8TimerChannel < 8)
		{
//			R_Config_TAU0_Set_Timer_Channel(u8TimerChannel,u16TimerMode,u16Interval,1);
		}
		else
		{
//			R_Config_TAU1_Set_Timer_Channel(u8TimerChannel,u16TimerMode,u16Interval,1);
		}
	}
	else
	{
		if (u8TimerChannel < 8)
		{
//			R_Config_TAU0_Set_Timer_Channel(u8TimerChannel,u16TimerMode,u16Interval,0);
		}
		else
		{
//			R_Config_TAU1_Set_Timer_Channel(u8TimerChannel,u16TimerMode,u16Interval,0);
		}
	}
	switch (u8TimerChannel)
	{
		case 0:
//			R_Config_TAU0_0_Start();
			break;
		case 1:
//			R_Config_TAU0_1_Start();
			break;
		case 2:
//			R_Config_TAU0_2_Start();
			break;
		case 3:
//			R_Config_TAU0_3_Start();
			break;
		case 4:
//			R_Config_TAU0_4_Start();
			break;
		case 5:
//			R_Config_TAU0_5_Start();
			break;
		case 6:
//			R_Config_TAU0_6_Start();
			break;
		case 7:
//			R_Config_TAU0_7_Start();
			break;

//		case 8:
//			R_Config_TAU1_0_Start();
//			break;
//		case 9:
//			R_Config_TAU1_1_Start();
//			break;
//		case 10:
//			R_Config_TAU1_2_Start();
//			break;
//		case 11:
//			R_Config_TAU1_3_Start();
//			break;
//		case 12:
//			R_Config_TAU1_4_Start();
//			break;
//		case 13:
//			R_Config_TAU1_5_Start();
//			break;
//		case 14:
//			R_Config_TAU1_6_Start();
//			break;
//		case 15:
//			R_Config_TAU1_7_Start();
//			break;
	}

}
#endif



/**
 * タイマーアレイユニットの停止
 *
* @return なし
 *
 * @attention なし
 ***************************************************************************/
void _stopTAU0()
{
	// タイマ・アレイ・ユニットが動作しているか？
	if (TAU0EN != 0) {
		if (TE0 == 0x00000) {
#ifdef WORKAROUND_READ_MODIFY_WRITE
			CBI2(SFR2_PER0, SFR2_BIT_TAU0EN);// タイマ・アレイ・ユニットにクロック供
#else	/* WORKAROUND_READ_MODIFY_WRITE*/
			TAU0EN    = 0;   			// タイマ・アレイ・ユニットにクロック供給停止
#endif
		}
	}
}



/**
 * タイマー周期の変更
 *
 * @param[in] u8Timer 変更するタイマ番号
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void _modifyTimerPeriodic(uint8_t u8TimerChannel, uint16_t u16Interval)
{
	switch (u8TimerChannel) {
	case 1:
		TDR01 = u16Interval;	// インターバル（周期）の設定
		break;

	case 2:
		TDR02 = u16Interval;	// インターバル（周期）の設定
		break;

	case 3:
		TDR03 = u16Interval;	// インターバル（周期）の設定
		break;

	case 4:
		TDR04 = u16Interval;	// インターバル（周期）の設定
		break;

	case 5:
		TDR05 = u16Interval;	// インターバル（周期）の設定
		break;

	case 6:
		TDR06 = u16Interval;	// インターバル（周期）の設定
		break;

	case 7:
		TDR07 = u16Interval;	// インターバル（周期）の設定
		break;
	}

}


/**
 * タイマーチャンネルの停止
 *
 * @param[in] u8Timer 停止するタイマ番号
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void _stopTimerChannel(uint8_t u8TimerChannel)
{
#ifdef WORKAROUND_READ_MODIFY_WRITE
	TT0   |=  (1 << u8TimerChannel);	// タイマ動作停止
	TOE0 &=  ~(1 << u8TimerChannel);	// タイマ出力禁止の設定
	TO0   &= ~(1 << u8TimerChannel);	// タイマ出力の設定

	switch (u8TimerChannel) {
	case 1:	SBI(SFR_MK1L,    5);// 割り込みマスクを禁止に設定
		break;

	case 2:	SBI(SFR_MK1L,    6);// 割り込みマスクを禁止に設定
		break;

	case 3:	SBI(SFR_MK1L,    7);// 割り込みマスクを禁止に設定
		break;

	case 4:	SBI(SFR_MK1H,    7);// 割り込みマスクを禁止に設定
		break;

	case 5: SBI(SFR_MK2L,    0);// 割り込みマスクを禁止に設定
		break;

	case 6:	SBI(SFR_MK2L,    1);// 割り込みマスクを禁止に設定
		break;

	case 7:	SBI(SFR_MK2L,    2);// 割り込みマスクを禁止に設定
		break;
	}
	if (!(TE0 & 0x009E)) {
		TT0 |= 0x0001;		// Master チャンネルの停止
	}
#else /* WORKAROUND_READ_MODIFY_WRITE */
	TT0   |=  (1 << u8TimerChannel);	// タイマ動作停止
	TOE0 &=  ~(1 << u8TimerChannel);	// タイマ出力禁止の設定
	TO0   &= ~(1 << u8TimerChannel);	// タイマ出力の設定
	// 割り込みマスクを禁止に設定
	switch (u8TimerChannel) {
	case 1:	TMMK01  = 1; break;
	case 2:	TMMK02  = 1; break;
	case 3:	TMMK03  = 1; break;
	case 4:	TMMK04  = 1; break;
	case 5:	TMMK05  = 1; break;
	case 6:	TMMK06  = 1; break;
	case 7:	TMMK07  = 1; break;
	}
	if (!(TE0 & 0x009E)) {
		TT0 |= 0x0001;		// Master チャンネルの停止
	}
#endif
}


/**
 * Software Reset
 *
 * Generate software reset.
 *
 * @return なし
 *
 * @attention:  This function uses trap instruction.
 *              So RESF register in MCU is set to 0x80 after reset.
 *              Unable to use when using debugger.
 *
 ***************************************************************************/

void softwareReset(void) {
	__asm __volatile(" .byte 0xff");
}

/**
 * Get Reset Flag
 *
 * Get the flag why reset occur.
 *
 * @return 0x00: External reset or Power on reset
 *         0x01: Low voltage detection
 *         0x02: Illegal memory access
 *         0x04: RAM parity error ( read from no initialized area )
 *         0x10: Watch dog timer
 *         0x80: Illegal instruction
 *
 * @attention:
 *
 ***************************************************************************/

uint8_t getResetFlag() {
	return g_u8ResetFlag;
}

/**
 * RLduino78のバージョン情報を取得します。
 *
 * @return バージョン情報を返却します。
 *
 * @attention なし
 ***************************************************************************/
uint16_t getVersion()
{
	return RLDUINO78_VERSION;
}

#define USE_POWER_MANAGEMENT (0) // Set 1 when issue was solved.

#if USE_POWER_MANAGEMENT == 1
/** @} group14 その他 */


/** ************************************************************************
 * @defgroup group15 パワーマネージメント/クロック制御関数
 *
 * @{
 ***************************************************************************/
/**
 * パワーマネージメントモードを取得します。
 *
 * 現在のパワーマネージメントモードを取得します。
 * - 通常モード：PM_NORMAL_MODE
 * - 省電力(HALT)モード：PM_HALT_MODE
 * - 省電力(STOP)モード：PM_STOP_MODE
 * - 省電力(SNOOZE)モード：PM_SNOOZE_MODE
 *
 * @return パワーマネージメントモードを返却します。
 *
 * @attention なし
 ***************************************************************************/
uint8_t getPowerManagementMode()
{
	return g_u8PowerManagementMode;
}


/**
 * パワーマネージメントモードを設定します。
 *
 * パワーマネージメントモードを設定します。
 * - 通常モード：PM_NORMAL_MODE
 * - 省電力(HALT)モード  ：PM_HALT_MODE
 * - 省電力(STOP)モード  ：PM_STOP_MODE
 * - 省電力(SNOOZE)モード：PM_SNOOZE_MODE
 *
 * パワーマネージメントモードに省電力(HALT/STOP/SNOOZE)モードを指定して delay()
 * 関数を呼び出すと、一時停止期間中はHALT/STOP命令によりスタンバイ状態になります。
 * また、パワーマネージメントモードに省電力(SNOOZE)モード指定して、 analogRead()
 * 関数を呼び出すと、SNOOZE状態になります。
 *
 * @param[in] u8PowerManagementMode パワーマネージメントモードを指定します。
 * @param[in] u16ADLL               A/D変換結果範囲の下限値を指定します。省略した場合デフォルト値（0）が設定されます。
 * @param[in] u16ADUL               A/D変換結果範囲の上限値を指定します。省略した場合デフォルト値（1023）が設定されます。
 *
 * @return なし
 *
 * @attention
 * - 動作クロックの状態によっては、パワーマネージメントモードが変更されない
 *   場合があります。
 * - A/D変換結果下限値/上限値には0から1023の範囲を指定してください。
 *   なお、下限値/上限値の下位2bitは無視されます。
 ***************************************************************************/
void setPowerManagementMode(uint8_t u8PowerManagementMode, uint16_t u16ADLL, uint16_t u16ADUL)
{

	switch (u8PowerManagementMode) {
	case PM_NORMAL_MODE:
	case PM_HALT_MODE:
		g_u8ADLL = 0x00;
		g_u8ADUL = 0xFF;
		g_u8PowerManagementMode = u8PowerManagementMode;
		break;

	case PM_STOP_MODE:
		if (CLS == 0) {
			g_u8ADLL = 0x00;
			g_u8ADUL = 0xFF;
			g_u8PowerManagementMode = u8PowerManagementMode;
		}
		break;

	case PM_SNOOZE_MODE:
		if ((CLS == 0) && (MCS == 0)) {
			if (u16ADLL > 1023) {
				u16ADLL = 1023;
			}
			if (u16ADUL > 1023) {
				u16ADUL = 1023;
			}
			if (u16ADLL > u16ADUL) {
				u16ADLL = 0x00;
				u16ADUL = 0xFF;
			} else {
				g_u8ADLL = (uint8_t)(u16ADLL >> 2);
				g_u8ADUL = (uint8_t)(u16ADUL >> 2);
			}
			g_u8PowerManagementMode = u8PowerManagementMode;
		}
		break;

	default:
		break;
	}

}


/**
 * 動作クロックモードを取得します。
 *
 * CPU/周辺ハードウェアの動作クロックモードを取得します。
 * - 高速動作モード(高速オンチップ・オシレータ)：CLK_HIGH_SPEED_MODE
 * - 低速動作モード(XT1発信回路)               ：CLK_LOW_SPEED_MODE
 *
 * @return 動作クロックモードを返却します。
 *
 * @attention なし
 ***************************************************************************/
uint8_t getOperationClockMode()
{
	return g_u8OperationClockMode;
}


/**
 * 動作クロックを設定します。
 *
 * CPU/周辺ハードウェアの動作クロックを設定します。
 * - 高速動作モード(高速オンチップ・オシレータ)：CLK_HIGH_SPEED_MODE
 * - 低速動作モード(XT1発信回路)               ：CLK_LOW_SPEED_MODE
 *
 * 高速動作モードを指定すると、CPU/周辺ハードウェアに供給するクロックに
 * メイン・システム・クロック（高速オンチップ・オシレータ）を設定します。
 * 低速動作モードを指定すると、CPU/周辺ハードウェアに供給するクロックに
 * サブシステム・クロック（XT1発信回路）を設定します。
 *
 * @param[in] u8ClockMode 動作クロックを指定します。
 *
 * @return なし
 *
 * @attention
 * - パワーマネージメントモードが省電力(STOP/SNOOZE)の場合は低速動作モード
 *   を設定することができません。
 * - GR-KURUMIの場合、高速動作モード（CLK_HIGH_SPEED_MODE）を指定すると
 *   32 MHzで動作し、低速動作モード（CLK_LOW_SPEED_MODE）を指定すると 32.768
 *   kHzで動作します。
 ***************************************************************************/
void setOperationClockMode(uint8_t u8ClockMode)
{
#if !defined(G23_FPB)
	if (u8ClockMode == CLK_HIGH_SPEED_MODE) {
		// 動作クロックの変更
		if (HIOSTOP == 1) {
			HIOSTOP = 0;	// 高速オンチップ・オシレータの動作開始
			CSS     = 0;	// CPU/周辺ハードウェア・クロックににメイン・システム・クロックを選択
			while (CLS != 0);
	#if (RTC_CLK_SOURCE == CLK_SOURCE_FIL)
			XTSTOP  = 1;	// XT1発信回路の発振停止
			CMC.cmc = 0x00;	// XT1発信回路の動作停止
	#endif
		}
		g_u8OperationClockMode = CLK_HIGH_SPEED_MODE;
	} else if (u8ClockMode == CLK_LOW_SPEED_MODE) {
		if ((g_u8PowerManagementMode != PM_STOP_MODE) &&
			(g_u8PowerManagementMode != PM_SNOOZE_MODE)) {
			// 動作クロックの変更
			if (CLS == 0) {
		#if (RTC_CLK_SOURCE == CLK_SOURCE_FIL)
				unsigned long i;
				CMC.cmc  = 0x10;// XT1発振回路の発振開始
				XTSTOP  = 0;	// XT1発信回路の発振開始
				for (i = 0; i < WAIT_XT1_CLOCK; i++) {
					NOP();		// 1秒以上のwait
				}
		#endif
				CSS     = 1;	// CPU/周辺ハードウェア・クロックににサブシステム・クロックを選択
				while (CLS != 1);
				HIOSTOP = 1;	// 高速オンチップ・オシレータの動作停止
			}
			g_u8OperationClockMode = CLK_LOW_SPEED_MODE;
		}
	}
#else // !defined(G23_FPB)
    if (g_u8OperationClockMode == u8ClockMode)
    {
        // If there is no change from the existing mode, it will not be processed.
        return;
    }
    else
    if (u8ClockMode == CLK_HIGH_SPEED_MODE)
    {
        // The high-speed on-chip oscillator starts operating.
        R_BSP_StartClock (HIOCLK);
        // Switch to a high-speed on-chip oscillator.
        if (BSP_OK == R_BSP_SetClockSource (HIOCLK))
        {
            g_u8OperationClockMode = CLK_HIGH_SPEED_MODE;
        }
        else
        {
            /* not implementation */
        }
    }
    else
    if (u8ClockMode == CLK_LOW_SPEED_MODE)
    {
        // Stops the operation of the high-speed on-chip oscillator.
        R_BSP_StopClock (HIOCLK);
        // Switch to a low-speed on-chip oscillator.
        if (BSP_OK == R_BSP_SetClockSource (LOCLK))
        {
            g_u8OperationClockMode = CLK_LOW_SPEED_MODE;
        }
        else
        {
            /* not implementation */
        }
    }
#endif
}
/** @} group15 パワーマネージメント/クロック制御関数 */
#endif /* USE_POWER_MANAGEMENT == 1


/** ************************************************************************
 * @defgroup group16 割込みハンドラ/周期起動関数
 *
 * @{
 ***************************************************************************/
/**
 * インターバル・タイマ割り込みハンドラ内から実行するコールバック関数を登録します。
 *
 * コールバック関数を登録すると1[ms]のインターバル・タイマ割り込み毎に登録した
 * コールバック関数が呼び出されます。また、コールバック関数呼び出し時にはシステム
 * 開始からの時間（ms）が引数として渡されます。
 *
 * @param[in] fFunction インターバル・タイマ割り込み時に実行するハンドラを指定します。
 *
 * @return なし
 *
 * @attention
 * - コールバック関数内では時間のかかる処理は行わないでください。
 * - コールバック関数内では以下の関数が呼び出し可能です。
 *
 * pinMode()、 digitalWrite()、 digitalRead()、 millis()、 micros()、 delayMicroseconds()、
 * min()、 max()、 constrain()、 map()、 lowByte()、 highByte()、 bitRead()、 bitWrite()、
 * bitSet()、 bitClear()、 bit()、 randomSeed()、 random()
 * - pinMode()関数と digitalWrite()関数は、 loop()関数内とコールバック関数内で同じピン
 * 番号を指定すると誤動作する可能性があります。
 ***************************************************************************/
void attachIntervalTimerHandler(void (*fFunction)(unsigned long u32Milles))
{
	g_fITInterruptFunc = fFunction;
}


/**
 * インターバル・タイマ割り込みハンドラ内から実行するコールバック関数の登録を解除します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void detachIntervalTimerHandler()
{
	g_fITInterruptFunc = NULL;
}

#if 0
/**
 * インターバル・タイマ割り込みハンドラ内から実行するコールバック関数を登録します。
 *
 * コールバック関数を登録すると引数[us]で指定したインターバル・タイマ割り込み毎に登録した
 * コールバック関数が呼び出されます。
 *
 * @param[in] fFunction インターバル・タイマ割り込み時に実行するハンドラを指定します。
 * @param[in] interval  インターバルの時間を指定します。[us]
 *
 * @return なし
 *
 * @attention
 * - コールバック関数内では時間のかかる処理は行わないでください。
 * - コールバック関数内では以下の関数が呼び出し可能です。
 * - コールバック関数を登録するとtone()が使用できなくなります。（デフォルト）
 * - tone()から変更する場合は、HOOK_TIMER_CHANNELを変更してください。
 *
 * pinMode()、 digitalWrite()、 digitalRead()、 millis()、 micros()、 delayMicroseconds()、
 * min()、 max()、 constrain()、 map()、 lowByte()、 highByte()、 bitRead()、 bitWrite()、
 * bitSet()、 bitClear()、 bit()、 randomSeed()、 random()
 * - pinMode()関数と digitalWrite()関数は、 loop()関数内とコールバック関数内で同じピン
 * 番号を指定すると誤動作する可能性があります。
 ***************************************************************************/
void attachMicroIntervalTimerHandler(void (*fFunction)(void), uint16_t interval)
{
	if((uint8_t)HOOK_TIMER_CHANNEL < 8)
	{
		_startTAU0(TIMER_CLOCK);
	}
	else if((uint8_t)HOOK_TIMER_CHANNEL < 16)
	{
		_startTAU1(TIMER_CLOCK);
	}
	_startTimerChannel( HOOK_TIMER_CHANNEL, INTERVAL_MICRO_MODE, interval - 1, false, true );
	INT_TM_HOOK  = fFunction;
}

void attachClockIntervalTimerHandler(void (*fFunction)(void), uint16_t interval)
{
	_startTimerChannel( HOOK_TIMER_CHANNEL, INTERVAL_FCLK_MODE, interval - 1, false, true );
	INT_TM_HOOK  = fFunction;
}


/**
 * インターバル・タイマ割り込みハンドラ内から実行するコールバック関数の登録を解除します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void detachMicroIntervalTimerHandler()
{
	_stopTimerChannel(SW_PWM_TIMER);
	INT_TM_HOOK  = NULL;
}
#endif

/**
 * 周期起動コールバック関数を登録します。
 *
 * 登録したコールバック関数は、u32CyclicTimeで指定した周期間隔[ms]で呼び出されます。
 * また、コールバック関数呼び出し時にはシステム開始からの時間(ms)が引数として渡されます。
 *
 * @param[in] u8HandlerNumber 周期起動コールバック関数の識別番号(0~7)を指定します。
 * @param[in] fFunction       インターバル・タイマ割り込み時に実行するハンドラを指定します。
 * @param[in] u32CyclicTime   周期起動する間隔[ms]を指定します。
 *
 * @return なし
 *
 * @attention なし
 ***************************************************************************/
void attachCyclicHandler(uint8_t u8HandlerNumber, void (*fFunction)(unsigned long u32Milles), uint32_t u32CyclicTime)
{
	if (u8HandlerNumber < MAX_CYCLIC_HANDLER) {
		detachCyclicHandler(u8HandlerNumber);
		g_CyclicHandlerTable[u8HandlerNumber].au32CyclicTime  = u32CyclicTime;
		g_CyclicHandlerTable[u8HandlerNumber].au32RemainTime = u32CyclicTime;
		g_CyclicHandlerTable[u8HandlerNumber].au32LastTime = millis();
		g_CyclicHandlerTable[u8HandlerNumber].afCyclicHandler = fFunction;
	}
}


/**
 * 周期起動コールバック関数の登録を解除します。
 *
 * @param[in] u8HandlerNumber 周期起動コールバック関数の識別番号( 0 ～ 7 )を指定します。
 *
 * @return なし
 *
 * @attention
 ***************************************************************************/
void detachCyclicHandler(uint8_t u8HandlerNumber)
{
	if (u8HandlerNumber < MAX_CYCLIC_HANDLER) {
		g_CyclicHandlerTable[u8HandlerNumber].afCyclicHandler = NULL;
		g_CyclicHandlerTable[u8HandlerNumber].au32CyclicTime  = 0;
		g_CyclicHandlerTable[u8HandlerNumber].au32RemainTime = 0;
		g_CyclicHandlerTable[u8HandlerNumber].au32LastTime = 0;
	}
}


/// @cond
/**
 * 周期起動コールバック関数を起動します。
 *
 * @return なし
 *
 * @attention
 ***************************************************************************/
void execCyclicHandler()
{
	int i;

	for (i = 0; i < MAX_CYCLIC_HANDLER; i++) {
		if (g_CyclicHandlerTable[i].afCyclicHandler != NULL) {
			unsigned long currentTime = millis();
			unsigned long elapsedTime = currentTime - g_CyclicHandlerTable[i].au32LastTime;
			g_CyclicHandlerTable[i].au32LastTime = currentTime;
			bool exec = g_CyclicHandlerTable[i].au32RemainTime <= elapsedTime;
			g_CyclicHandlerTable[i].au32RemainTime -= elapsedTime;
			if (exec) {
				g_CyclicHandlerTable[i].au32RemainTime += g_CyclicHandlerTable[i].au32CyclicTime;
				g_CyclicHandlerTable[i].afCyclicHandler(currentTime);
			}
		}
	}
}
/// @endcond
/** @} group16 割込みハンドラ/周期起動関数 */

#if !defined(G23_FPB)
/** ************************************************************************
 * @addtogroup group14
 *
 * @{
 ***************************************************************************/
/**
 * 指定したピンからクロックを出力します。
 *
 * 他のデバイスに任意のクロックを供給することができます。例えば、Smart Analogの
 * フィルタ（LPF/HPF）の外部クロック入力に指定したピンを接続して任意のカットオフ
 * 周波数を得ることができます。
 *
 * @param[in] u8Pin        ピン番号を指定します。
 * @param[in] u32Frequency 出力するクロック（ 244 Hz ～ 32 MHz）を指定します。
 *                         0を指定した場合はクロックの出力を停止します。
 *
 * @return なし
 *
 * @attention ピン番号にはデジタルピンのD3、D5、D6、D9、D10を指定してください。
 ***************************************************************************/
void outputClock(uint8_t u8Pin, uint32_t u32Frequency)
{
	uint8_t u8Timer;
	uint16_t u16Interval;

	if ((u8Pin < NUM_DIGITAL_PINS) &&
		((u32Frequency == 0) ||
		((OUTPUT_CLOCK_MIN <= u32Frequency) && (u32Frequency <= OUTPUT_CLOCK_MAX)))) {
//		u8Timer = getPinTable(u8Pin)->timer;
		if (u8Timer != SWPWM_PIN) {
			// 出力モードに設定
			pinMode(u8Pin, OUTPUT);

			if (u32Frequency != 0) {
				// タイマーアレイユニットの開始
				_startTAU0(TIMER_CLOCK);

				// タイマーの開始
				u16Interval = (uint16_t)(OUTPUT_CLOCK_CKx / (u32Frequency * 2) - 1);
				_startTimerChannel(u8Timer, OUTPUT_CLOCK_MODE, u16Interval, false, false);
			}
			else {
				// タイマーの停止
				_stopTimerChannel(u8Timer);

				// タイマーアレイユニットの停止
				_stopTAU0();

			}
		}
	}

}
#endif

#if 0
/**
 * MCUに内蔵されている温度センサから温度（摂氏/華氏）を取得します。
 *
 * @param[in] u8Mode 摂氏/華氏を指定します。
 *			@arg TEMP_MODE_CELSIUS    ： 摂氏
 *			@arg TEMP_MODE_FAHRENHEIT ： 華氏
  *
 * @return 温度を返却します。
 *
 ***************************************************************************/
int getTemperature(uint8_t u8Mode)
{
#if 0
	int s16Result1, s16Result2;
	float fResult;

	FUNC_MUTEX_LOCK;

	s16Result1 = _analogRead(ADS_TEMP_SENSOR);
	s16Result2 = _analogRead(ADS_REF_VOLTAGE);

	fResult = (1450 * (float)s16Result1 / (float)s16Result2 - 1050) / -3.6 + 25;
	if (u8Mode == TEMP_MODE_FAHRENHEIT) {
		// 摂氏を華氏へ変換
		fResult = 1.8 * fResult + 32;
	}

	FUNC_MUTEX_UNLOCK;

	return (int)fResult;
#else
	int s16Result1, s16Result2;
	long s32Temp;
	int s16Result;

	ADM0 = 0x00;	// A/Dコンバータの動作停止、fclk/64、ノーマル1モードに設定
	ADM1 = 0x20;	// ソフトウェア・トリガ・モード、ワンショットに設定
	ADM2 = 0x00;	// Vddリファレンスに設定
	ADUL = 0xff;
	ADLL = 0;
	SBI(SFR_MK1H, 0);	// INTADの割り込み禁止
	CBI(SFR_IF1H, 0);	// INTADの割り込みフラグのクリア
	ADS = ADS_TEMP_SENSOR;		// アナログチャンネルの設定
	SBI(SFR_ADM0, SFR_BIT_ADCE);	// A/Dコンパレータを有効に設定
	CBI(SFR_IF1H, 0);	// INTADの割り込みフラグのクリア
	SBI(SFR_ADM0, SFR_BIT_ADCS);	// A/Dコンバータの開始
	while (ADIF == 0);	// A/Dコンバート待ち
	CBI(SFR_IF1H, 0);	// INTADの割り込みフラグのクリア
	SBI(SFR_ADM0, SFR_BIT_ADCS);// A/Dコンバータの開始
	while (ADIF == 0);	// A/Dコンバート待ち
	s16Result1 = (ADCR >> 6);// A/Dコンバート結果の取得
	CBI(SFR_ADM0, SFR_BIT_ADCE);		// A/Dコンパレータを無効に設定

	ADM0 = 0x00;	// A/Dコンバータの動作停止、fclk/64、ノーマル1モードに設定
	ADM2 = 0x00;	// Vddリファレンスに設定
	CBI(SFR_IF1H, 0);		// INTADの割り込みフラグのクリア
	ADS = ADS_REF_VOLTAGE;		// アナログチャンネルの設定
	SBI(SFR_ADM0, SFR_BIT_ADCE);	// A/Dコンパレータを有効に設定
	CBI(SFR_IF1H, 0);	// INTADの割り込みフラグのクリア
	SBI(SFR_ADM0, SFR_BIT_ADCS);	// A/Dコンバータの開始
	while (ADIF == 0);	// A/Dコンバート待ち
	CBI(SFR_IF1H, 0);		// INTADの割り込みフラグのクリア
	SBI(SFR_ADM0, SFR_BIT_ADCS);// A/Dコンバータの開始
	while (ADIF == 0);	// A/Dコンバート待ち
	s16Result2 = (ADCR >> 6);// A/Dコンバート結果の取得
	CBI(SFR_IF1H, 0);		// INTADの割り込みフラグのクリア
	CBI(SFR_ADM0, SFR_BIT_ADCE);		// A/Dコンパレータを無効に設定

	if (s16Result2 == 0) {
		s16Result2 = 1;
	}

	volatile long n14500L = 14500L;
	s32Temp = n14500L * s16Result1 / s16Result2 - 10500L;
	if (u8Mode == TEMP_MODE_FAHRENHEIT) {
		s16Result = s32Temp / -20;
		s16Result += 77;
	} else {
		s16Result = s32Temp / -36;
		s16Result += 25;
	}

	return s16Result;
#endif
}
#endif

void enterPowerManagementMode(unsigned long u32ms)
{
#if !defined(G23_FPB)
	uint8_t  u8PMmode;


    // 設定された省電力モードとRL78の状態をチェックし、実際に発行できる命令を決定する。
    if (TE0 & 0x00DE) {
        u8PMmode = PM_HALT_MODE;
    } else {
        u8PMmode = PM_STOP_MODE;
    }


	if (u32ms == 0xFFFFFFFF) {
		ITLMK       = 1;			// Mask Interval Timer
		_STOP();
		ITLMK       = 0;			// Unmask Interval Timer
	}
	else {
		g_u32delay_timer = u32ms;
		TMMK05     = 1;
		//Note: TM05 stops during STOP, overflow count should be adjusted.
		//    : have a margin of error of approx. 50ms.
		g_timer05_overflow_count = g_timer05_overflow_count + (u32ms / MILLISECONDS_PER_TIMER05_OVERFLOW);
		do {
            if (u8PMmode == PM_STOP_MODE) {
                _STOP();
            }
            else {
                _HALT();
            }
		} while (g_u32delay_timer  != 0);
		TMMK05     = 0;

	}
#else
    uint8_t u8PMmode;

    /* Check the set power saving mode and the status of RL78,
       and determine the instruction that can be actually issued.
     */
    u8PMmode = g_u8PowerManagementMode;

    if (u32ms == 0xFFFFFFFF)
    {
//        ITLMK = 1;            // Mask Interval Timer
        /* When the interrupt of TML32 is masked and the mode is changed to STOP mode,
           the interrupt mask is not applied as a temporary measure because the
           implementation that clears ITLS0 to 0 has not been completed.
         */
        _STOP();
        ITLMK = 0;            // Unmask Interval Timer
    }
    else
    {
        if (1U == g_delay_cnt_flg)
        {
            while (g_u32delay_timer < u32ms) {
                if (u8PMmode == PM_STOP_MODE) {
                    _STOP();
                }
                else if (u8PMmode == PM_HALT_MODE){
                    _HALT();
                }
                else
                {
                    NOP();
                }
            }
        }
        else
        if (1U == g_delay_cnt_micros_flg)
        {
            while (g_u32delay_micros_timer < u32ms) {
                if (u8PMmode == PM_STOP_MODE) {
                    _STOP();
                }
                else if (u8PMmode == PM_HALT_MODE){
                    _HALT();
                }
                else
                {
                    NOP();
                }
            }
        }
    }

#endif
}
