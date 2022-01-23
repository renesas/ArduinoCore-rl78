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
* File Name    : Config_ITL001.h
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_ITL001.
* Creation Date: 2021-05-14
***********************************************************************************************************************/

#ifndef Config_ITL001_H
#define Config_ITL001_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_itl.h"

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _1F_ITL_ITLCMP001_VALUE                    (0x1FU)    /* 8-bit compare data register */
#define _FA_ITL_ITLCMP001_VALUE                    (0xFAU)    /* 8-bit compare data register */
#define _01_ITL_ITLCMP001_VALUE                    (0x01U)    /* 8-bit compare data register */
#define _20_ITL_ITLCMP001_VALUE                    (0x20U)    /* 8-bit compare data register */
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_ITL001_Create(void);
void R_Config_ITL001_Start(void);
void R_Config_ITL001_Stop(void);
void R_Config_ITL001_Set_OperationMode(void);
void R_Config_ITL001_Callback_Shared_Interrupt(void);
void R_Config_ITL001_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
void R_Config_ITL001_SetCompareMatch(void);
/* End user code. Do not edit comment generated here */
#endif
