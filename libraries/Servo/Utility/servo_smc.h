//#include "pins_arduino.h"
//#include "servo_smc.h"
//#include "pintable.h"
#include "r_smc_entry.h"
#include "Config_TAU0_1_Servo.h"
#include "Config_TAU0_2_Servo.h"
#include "Config_TAU0_3_Servo.h"
#include "Config_TAU0_4_Servo.h"
#include "Config_TAU0_5_Servo.h"
#include "Config_TAU0_6_Servo.h"
#include "Config_TAU0_7_Servo.h"
#include "wiring_private.h"

#define SERVO_CH_NUM	(7)

typedef struct {
    void (*open)();
	void (*start)();
	void (*stop)();
} servo_func;

void smc_ServoWrite(uint8_t pin, unsigned int microseconds);
void smc_attach_servo_channel(uint8_t pin);
