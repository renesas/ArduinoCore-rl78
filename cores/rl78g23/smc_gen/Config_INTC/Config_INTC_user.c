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
* File Name    : Config_INTC_user.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_INTC.
* Creation Date: 2021-11-04
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
#include "Config_INTC.h"
/* Start user code for include. Do not edit comment generated here */
#include "wiring_private.h"
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
extern fInterruptFunc_t g_afInterruptFuncTable[EXTERNAL_NUM_INTERRUPTS] __attribute__((weak));;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_INTC_Create_UserInit
* Description  : This function adds user code after initializing the INTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_INTC_intp0_interrupt
* Description  : This function is INTP0 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_INTC_intp0_interrupt(void)
{
    /* Start user code for r_Config_INTC_intp0_interrupt. Do not edit comment generated here */
    if (g_afInterruptFuncTable[6] != NULL) {
        (*g_afInterruptFuncTable[6])();
    }
    /* End user code. Do not edit comment generated here */
}


/***********************************************************************************************************************
* Function Name: r_Config_INTC_intp1_interrupt
* Description  : This function is INTP1 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_INTC_intp1_interrupt(void)
{
    /* Start user code for r_Config_INTC_intp1_interrupt. Do not edit comment generated here */
    if (g_afInterruptFuncTable[4] != NULL) {
        (*g_afInterruptFuncTable[4])();
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_INTC_intp2_interrupt
* Description  : This function is INTP2 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_INTC_intp2_interrupt(void)
{
    /* Start user code for r_Config_INTC_intp2_interrupt. Do not edit comment generated here */
    if (g_afInterruptFuncTable[3] != NULL) {
        (*g_afInterruptFuncTable[3])();
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_INTC_intp3_interrupt
* Description  : This function is INTP3 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_INTC_intp3_interrupt(void)
{
    /* Start user code for r_Config_INTC_intp3_interrupt. Do not edit comment generated here */
    if (g_afInterruptFuncTable[5] != NULL) {
        (*g_afInterruptFuncTable[5])();
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_INTC_intp4_interrupt
* Description  : This function is INTP4 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_INTC_intp4_interrupt(void)
{
    /* Start user code for r_Config_INTC_intp4_interrupt. Do not edit comment generated here */
    if (g_afInterruptFuncTable[1] != NULL) {
        (*g_afInterruptFuncTable[1])();
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_INTC_intp10_interrupt
* Description  : This function is INTP10 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_INTC_intp10_interrupt(void)
{
    /* Start user code for r_Config_INTC_intp10_interrupt. Do not edit comment generated here */
    if (g_afInterruptFuncTable[2] != NULL) {
        (*g_afInterruptFuncTable[2])();
    }
    /* End user code. Do not edit comment generated here */
}
/***********************************************************************************************************************
* Function Name: r_Config_INTC_intp11_interrupt
* Description  : This function is INTP11 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_INTC_intp11_interrupt(void)
{
    /* Start user code for r_Config_INTC_intp11_interrupt. Do not edit comment generated here */
    if (g_afInterruptFuncTable[0] != NULL) {
        (*g_afInterruptFuncTable[0])();
    }
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
