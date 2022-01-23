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
* File Name    : r_cg_sau_common.c
* Version      : 1.0.1
* Device(s)    : R7F100GLGxFB
* Description  : None
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
#include "Config_UART0.h"
#include "Config_UART1.h"
#include "Config_UART2.h"
#include "Config_CSI11.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_SAU0_Create
* Description  : This function enables SAU0 input clock supply and initializes SAU0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Create(void)
{
    SAU0EN = 1U;    /* supplies input clock */
    R_Config_UART0_Create();
    R_Config_UART1_Create();
    R_Config_CSI11_Create();
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Create
* Description  : This function enables SAU1 input clock supply and initializes SAU1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Create(void)
{
    SAU1EN = 1U;    /* supplies input clock */
    R_Config_UART2_Create();
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Set_PowerOn
* Description  : This function starts the clock supply for SAU0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Set_PowerOn(void)
{
    SAU0EN = 1U;    /* supplies input clock */
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Set_PowerOff
* Description  : This function stops the clock supply for SAU0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Set_PowerOff(void)
{
    SAU0EN = 0U;    /* stops input clock supply */
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Set_PowerOn
* Description  : This function starts the clock supply for SAU1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Set_PowerOn(void)
{
    SAU1EN = 1U;    /* supplies input clock */
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Set_PowerOff
* Description  : This function stops the clock supply for SAU1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Set_PowerOff(void)
{
    SAU1EN = 0U;    /* stops input clock supply  */
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Set_Reset
* Description  : This function sets SAU0 module in reset state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Set_Reset(void)
{
    SAU0RES = 1U;    /* reset serial array unit */
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Release_Reset
* Description  : This function releases SAU0 module from reset state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Release_Reset(void)
{
    SAU0RES = 0U;    /* reset release of serial array unit */
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Set_Reset
* Description  : This function sets SAU1 module in reset state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Set_Reset(void)
{
    SAU1RES = 1U;    /* reset serial array unit */
}

/***********************************************************************************************************************
* Function Name: R_SAU1_Release_Reset
* Description  : This function releases SAU1 module from reset state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU1_Release_Reset(void)
{
    SAU1RES = 0U;    /* reset release of serial array unit */
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Set_SnoozeOn
* Description  : This function enables SAU0 wakeup function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Set_SnoozeOn(void)
{
    SSC0 |= _0001_SAU_CH0_SNOOZE_ON;
}

/***********************************************************************************************************************
* Function Name: R_SAU0_Set_SnoozeOff
* Description  : This function disables SAU0 wakeup function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_SAU0_Set_SnoozeOff(void)
{
    SSC0 &= (uint16_t)~_0001_SAU_CH0_SNOOZE_ON;
}

/* Start user code for adding. Do not edit comment generated here */
void r_Config_CSI11_UART1_interrupt_switching(void) {
#if defined(UART1_CHANNEL) && ( UART1_CHANNEL == 1 )
    /* Check bit [2:1] of register SMR03 == 01 , which is set in R_Config_UART1_Create(). */
	if ( (SMR03 & _0002_SAU_MODE_UART) == _0002_SAU_MODE_UART) {
        /*
         */
        r_Config_UART1_interrupt_receive();
        return;
    }
#endif

#if defined(CSI_CHANNEL3)
    /* Check bit [2:1] of register SMR03 == 00 , which is set in R_Config_CSI11_Create(). */
	if ( (SMR03 & _0000_SAU_MODE_CSI) == _0000_SAU_MODE_CSI) {
        /* Call the interrupt handler for CSI11 (Master)
         * If it is possible to distinguish between CSI11 (master) and CSI111 (slave), do so here. */
        r_Config_CSI11_interrupt();
        return;
    }
#endif
}
/* End user code. Do not edit comment generated here */
