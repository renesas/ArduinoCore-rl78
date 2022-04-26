/*
 * servo_smc_if.h
 *
 *  Created on: 2022/03/08
 *      Author: hmU11457
 */

#ifndef SERVO_UTILITY_SERVO_SMC_IF_H_
#define SERVO_UTILITY_SERVO_SMC_IF_H_

extern volatile uint8_t g_servo_enable_interrupt_flag[7];
void R_Config_TAU0_1_Servo_Stop(void);
void R_Config_TAU0_2_Servo_Stop(void);
void R_Config_TAU0_3_Servo_Stop(void);
void R_Config_TAU0_4_Servo_Stop(void);
void R_Config_TAU0_5_Servo_Stop(void);
void R_Config_TAU0_6_Servo_Stop(void);
void R_Config_TAU0_7_Servo_Stop(void);

#endif /* SERVO_UTILITY_SERVO_SMC_IF_H_ */
