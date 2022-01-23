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
* File Name    : r_cg_iica_common.c
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_IICA0_Set_PowerOn
* Description  : This function starts the clock supply for IICA0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IICA0_Set_PowerOn(void)
{
    IICA0EN = 1;    /* start IICA0 clock */
}

/***********************************************************************************************************************
* Function Name: R_IICA0_Set_PowerOff
* Description  : This function stops the clock supply for IICA0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IICA0_Set_PowerOff(void)
{
    IICA0EN = 0;    /* stop IICA0 clock */
}

/***********************************************************************************************************************
* Function Name: R_IICA1_Set_PowerOn
* Description  : This function starts the clock supply for IICA1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IICA1_Set_PowerOn(void)
{
    IICA1EN = 1;    /* start IICA1 clock */
}

/***********************************************************************************************************************
* Function Name: R_IICA1_Set_PowerOff
* Description  : This function stops the clock supply for IICA1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IICA1_Set_PowerOff(void)
{
    IICA1EN = 0;    /* stop IICA1 clock */
}

/***********************************************************************************************************************
* Function Name: R_IICA0_Set_Reset
* Description  : This function sets IICA0 module in reset state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IICA0_Set_Reset(void)
{
    IICA0RES = 1U;    /* reset IICA0 module */
}

/***********************************************************************************************************************
* Function Name: R_IICA0_Release_Reset
* Description  : This function releases IICA0 module from reset state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IICA0_Release_Reset(void)
{
    IICA0RES = 0U;    /* release IICA0 module */
}

/***********************************************************************************************************************
* Function Name: R_IICA1_Set_Reset
* Description  : This function sets IICA1 module in reset state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IICA1_Set_Reset(void)
{
    IICA1RES = 1U;    /* reset IICA1 module */
}

/***********************************************************************************************************************
* Function Name: R_IICA1_Release_Reset
* Description  : This function releases IICA1 module from reset state.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_IICA1_Release_Reset(void)
{
    IICA1RES = 0U;    /* release IICA1 module */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
