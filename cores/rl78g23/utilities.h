
#ifndef UTILITIES_H_
#define UTILITIES_H_
#include <stdint.h>


/* Power Management Mode. */
#define PM_NORMAL_MODE	0
#define PM_HALT_MODE	1
#define PM_STOP_MODE	2
#define PM_SNOOZE_MODE	3

/* Operation Clock Mode. */
#define CLK_HIGH_SPEED_MODE		0
#define CLK_LOW_SPEED_MODE		1

/* Temperature Mode. */
#define TEMP_MODE_CELSIUS		0
#define TEMP_MODE_FAHRENHEIT	1

typedef void (*fInterruptFunc_t)(void);
typedef void (*fITInterruptFunc_t)(unsigned long u32timer_millis);

extern uint8_t g_u8ResetFlag;
extern uint8_t g_u8PowerManagementMode;
extern uint8_t g_u8OperationClockMode;
extern fITInterruptFunc_t	g_fITInterruptFunc;

extern fInterruptFunc_t	g_fMicroInterruptFunc;

uint16_t getVersion();
uint8_t getPowerManagementMode();
#ifdef __cplusplus
void setPowerManagementMode(uint8_t u8PowerManagementMode, uint16_t u16ADLL = 0, uint16_t u16ADUL = 1023);
#else
void setPowerManagementMode(uint8_t u8PowerManagementMode, uint16_t u16ADLL, uint16_t u16ADUL);
#endif
uint8_t getOperationClockMode();
void setOperationClockMode(uint8_t u8ClockMode);
void attachIntervalTimerHandler(void (*fFunction)(unsigned long u32Milles));
void detachIntervalTimerHandler();

void attachMicroIntervalTimerHandler(void (*fFunction)(void), uint16_t interval);

void attachClockIntervalTimerHandler(void (*fFunction)(void), uint16_t interval);
void detachMicroIntervalTimerHandler();
void detachClockIntervalTimerHandler();
void attachCyclicHandler(uint8_t u8HandlerNumber, void (*fFunction)(unsigned long u32Milles), uint32_t u32CyclicTime);
void detachCyclicHandler(uint8_t u8HandlerNumber);
void outputClock(uint8_t u8Pin, uint32_t u32Frequency);
int getTemperature(uint8_t u8Mode);
void softwareReset(void);
uint8_t getResetFlag(void);
// void execCyclicHandler(void);

#ifdef __cplusplus
extern "C" {
#endif
void _startTAU0(uint16_t u16TimerClock);
void _stopTAU0();
void _startTimerChannel(uint8_t u8TimerChannel, uint16_t u16TimerMode, uint16_t u16Interval, bool bPWM, bool bInterrupt);
void _modifyTimerPeriodic(uint8_t u8TimerChannel, uint16_t u16Interval);
void _stopTimerChannel(uint8_t u8TimerChannel);
void _turnOffPwmPin(uint8_t u8Pin);
void _softwarePWM(void);
void enterPowerManagementMode(unsigned long u32ms);
void _readResetFlag();
// 2022/10/11
void execCyclicHandler(void);
#ifdef __cplusplus
}
#endif


#endif // UTILITIES_H_
