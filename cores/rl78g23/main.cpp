/*
  main.cpp - Main loop for Arduino sketches
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Arduino.h>
#ifdef __RL78__
#include "utilities.h"
#endif

#if USE_SMART_CONFIGRATOR == 1
extern "C" {
	#include "r_smc_entry.h"
}
#endif

//#include <Wire.h>

// Declared weak in Arduino.h to allow user redefinitions.
#ifndef __RL78__
int atexit(void (* /*func*/ )()) { return 0; }
#endif /* __RL78__ */

// Weak empty variant initialization function.
// May be redefined by variant files.
#ifndef __RL78__
void initVariant() __attribute__((weak));
void initVariant() { }
#endif /* __RL78__ */

#if defined(USBCON)
void setupUSB() __attribute__((weak));
void setupUSB() { }
#endif /* defined(USBCON) */

int main(void)
{
/******************************************************/
	interrupts();				/* Enable Interrupt */

/* Start Interval Timer */
	R_Config_ITL000_Create();	/* Create 1ms Interval Timer */
	R_Config_ITL000_Start();	/* Start 1ms Interval Timer */
	R_ITL_Start_Interrupt();	/* Start ITL Interrupt */


/* Power Off unused Peripheral */
/* SERIAL ARRAY UNIT (SAU) */
#if !defined(UART_CHANNEL) & (UART1_CHANNEL == 0) & !defined(CSI_CHANNEL)
	R_SAU0_Set_Reset();
	R_SAU0_Set_PowerOff();
#endif
#if !defined(UART1_CHANNEL) || UART1_CHANNEL == 0
	R_Config_UART1_Stop();
#endif
#if !defined(CSI_CHANNEL)
	R_Config_CSI11_Stop();
#endif
#if !defined(UART2_CHANNEL) || (UART2_CHANNEL == 0)
	R_SAU1_Set_Reset();
	R_SAU1_Set_PowerOff();
#endif

/* IICA UNIT(IICA*) */
#if !defined(IIC_CHANNEL0) | (IIC_CHANNEL0!=0)
	R_IICA0_Set_Reset();
	R_IICA0_Set_PowerOff();
#endif
#if (IIC_CHANNEL1!=1)
	R_IICA1_Set_Reset();
	R_IICA1_Set_PowerOff();
#endif

/* RTC */
#if !defined(RTC_ON) | (RTC_ON!=0)
	R_RTC_Set_PowerOff();
#endif

#if WDT_EN==1
	R_Config_WDT_Start();
#endif

	SOE0 &= 0xf3;
	SO0 |= 0x08;

/******************************************************/

#ifndef __RL78__
	init();
#endif

#ifndef __RL78__
	initVariant();
#endif

#if defined(USBCON)
	USBDevice.attach();
#endif
	
	setup();
    
	for (;;) {
		loop();
#ifdef __RL78__
#endif
	}
        
	return 0;
}

#ifdef __RL78__
/**
 * Finish Function
 *
 * RLduino78 Framework finish
 *  *
 * @return None
 *
 * @attention No return
 ***************************************************************************/
#include <stdlib.h>

void abort(void)
{
	for(;;);
}

void exit(int) __attribute__ ((weak, alias ("abort")));

#include <exception>

#endif
