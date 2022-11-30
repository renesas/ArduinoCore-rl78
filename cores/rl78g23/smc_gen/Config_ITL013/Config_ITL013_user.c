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
* File Name    : Config_ITL013_user.c
* Version      : 1.1.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_ITL013.
* Creation Date: 
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
#include "Config_ITL013.h"
/* Start user code for include. Do not edit comment generated here */

/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

#include "utilities.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
extern volatile unsigned long g_u32timer_periodic;
// void execCyclicHandler(void);
void (*INT_TM_HOOK)() = NULL;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_ITL013_Create_UserInit
* Description  : This function adds user code after initializing the ITL013 channel.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ITL013_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    g_u32timer_periodic = 0;
    /* End user code. Do not edit comment generated here */
}

extern fITInterruptFunc_t    g_fITInterruptFunc;

/***********************************************************************************************************************
* Function Name: R_Config_ITL013_Callback_Shared_Interrupt
* Description  : This function handles the ITL013 shared interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ITL013_Callback_Shared_Interrupt(void)
{
    /* Start user code for R_Config_ITL013_Callback_Shared_Interrupt. Do not edit comment generated here */
    g_u32timer_periodic ++;

// Add 20221006
    if(g_fITInterruptFunc != NULL)
    {
        g_fITInterruptFunc(g_u32timer_periodic);
    }

    execCyclicHandler();

    // for MsTImer2
    if(NULL != INT_TM_HOOK)
    {
        INT_TM_HOOK();
    }
    /* End user code. Do not edit comment generated here */
}


/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
