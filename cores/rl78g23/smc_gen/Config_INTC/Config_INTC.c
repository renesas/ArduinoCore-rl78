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
* File Name    : Config_INTC.c
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
#include <stdio.h>
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
typedef struct {
    uint8_t intNum;
    uint8_t pinNum;
    int modeNum;
} Num;
Num value;

/* End user code. Do not edit comment generated here */
/***********************************************************************************************************************
* Function Name: R_Config_INTC_Create
* Description  : This function initializes the INTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_Create(void)
{
    PMK1 = 1U;    /* disable INTP1 operation */
    PIF1 = 0U;    /* clear INTP1 interrupt flag */
    PMK2 = 1U;    /* disable INTP2 operation */
    PIF2 = 0U;    /* clear INTP2 interrupt flag */
    PMK3 = 1U;    /* disable INTP3 operation */
    PIF3 = 0U;    /* clear INTP3 interrupt flag */
    PMK4 = 1U;    /* disable INTP4 operation */
    PIF4 = 0U;    /* clear INTP4 interrupt flag */
    PMK10 = 1U;    /* disable INTP10 operation */
    PIF10 = 0U;    /* clear INTP10 interrupt flag */
    PMK11 = 1U;    /* disable INTP11 operation */
    PIF11 = 0U;    /* clear INTP11 interrupt flag */
    /* Set INTP1 low priority */
    PPR11 = 1U;
    PPR01 = 1U;
    /* Set INTP2 low priority */
    PPR12 = 1U;
    PPR02 = 1U;
    /* Set INTP3 low priority */
    PPR13 = 1U;
    PPR03 = 1U;
    /* Set INTP4 low priority */
    PPR14 = 1U;
    PPR04 = 1U;
    /* Set INTP10 low priority */
    PPR110 = 1U;
    PPR010 = 1U;
    /* Set INTP11 low priority */
    PPR111 = 1U;
    PPR011 = 1U;
    EGN0 = _10_INTP4_EDGE_FALLING_SEL | _08_INTP3_EDGE_FALLING_SEL | _04_INTP2_EDGE_FALLING_SEL | 
           _02_INTP1_EDGE_FALLING_SEL;
    EGP0 = _00_INTP4_EDGE_RISING_UNSEL | _00_INTP3_EDGE_RISING_UNSEL | _00_INTP2_EDGE_RISING_UNSEL | 
           _00_INTP1_EDGE_RISING_UNSEL;
    EGN1 = _08_INTP11_EDGE_FALLING_SEL | _04_INTP10_EDGE_FALLING_SEL;
    EGP1 = _00_INTP11_EDGE_RISING_UNSEL | _00_INTP10_EDGE_RISING_UNSEL;
    /* Set INTP1 pin */
    PMCT5 &= 0xFEU;
    PMCE5 &= 0xFEU;
    CCDE &= 0xF7U;
    PM5 |= 0x01U;
    /* Set INTP2 pin */
    PMCE5 &= 0xFDU;
    CCDE &= 0xFBU;
    PM5 |= 0x02U;
    /* Set INTP3 pin */
    PMCT3 &= 0xFEU;
    PM3 |= 0x01U;
    /* Set INTP4 pin */
    PMCT3 &= 0xFDU;
    PM3 |= 0x02U;
    /* Set INTP10 pin */
    PMCT7 &= 0xBFU;
    PM7 |= 0x40U;
    /* Set INTP11 pin */
    PMCT7 &= 0x7FU;
    PM7 |= 0x80U;

    R_Config_INTC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP1_Start
* Description  : This function clears INTP1 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP1_Start(void)
{
    PIF1 = 0U;    /* clear INTP1 interrupt flag */
    PMK1 = 0U;    /* enable INTP1 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP1_Stop
* Description  : This function disables INTP1 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP1_Stop(void)
{
    PMK1 = 1U;    /* disable INTP1 interrupt */
    PIF1 = 0U;    /* clear INTP1 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP2_Start
* Description  : This function clears INTP2 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP2_Start(void)
{
    PIF2 = 0U;    /* clear INTP2 interrupt flag */
    PMK2 = 0U;    /* enable INTP2 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP2_Stop
* Description  : This function disables INTP2 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP2_Stop(void)
{
    PMK2 = 1U;    /* disable INTP2 interrupt */
    PIF2 = 0U;    /* clear INTP2 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP3_Start
* Description  : This function clears INTP3 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP3_Start(void)
{
    PIF3 = 0U;    /* clear INTP3 interrupt flag */
    PMK3 = 0U;    /* enable INTP3 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP3_Stop
* Description  : This function disables INTP3 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP3_Stop(void)
{
    PMK3 = 1U;    /* disable INTP3 interrupt */
    PIF3 = 0U;    /* clear INTP3 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP4_Start
* Description  : This function clears INTP4 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP4_Start(void)
{
    PIF4 = 0U;    /* clear INTP4 interrupt flag */
    PMK4 = 0U;    /* enable INTP4 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP4_Stop
* Description  : This function disables INTP4 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP4_Stop(void)
{
    PMK4 = 1U;    /* disable INTP4 interrupt */
    PIF4 = 0U;    /* clear INTP4 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP10_Start
* Description  : This function clears INTP10 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP10_Start(void)
{
    PIF10 = 0U;    /* clear INTP10 interrupt flag */
    PMK10 = 0U;    /* enable INTP10 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP10_Stop
* Description  : This function disables INTP10 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP10_Stop(void)
{
    PMK10 = 1U;    /* disable INTP10 interrupt */
    PIF10 = 0U;    /* clear INTP10 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP11_Start
* Description  : This function clears INTP11 interrupt flag and enables interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP11_Start(void)
{
    PIF11 = 0U;    /* clear INTP11 interrupt flag */
    PMK11 = 0U;    /* enable INTP11 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP11_Stop
* Description  : This function disables INTP11 interrupt and clears interrupt flag.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP11_Stop(void)
{
    PMK11 = 1U;    /* disable INTP11 interrupt */
    PIF11 = 0U;    /* clear INTP11 interrupt flag */
}

/* Start user code for adding. Do not edit comment generated here */

void R_Config_INTC_Create_Mode(uint8_t interruptNum, int mode)
{
    switch (interruptNum) {
    case 0:
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_0;
        value.modeNum = mode;
        /* 割り込みモードの設定 */
        if (value.modeNum == FALLING) {
            EGP1_bit.no3 = 0U;
            EGN1_bit.no3 = 1U;
        }
        else if (value.modeNum == RISING) {
            EGP1_bit.no3 = 1U;
            EGN1_bit.no3 = 0U;
            }
        else if (value.modeNum == CHANGE){
            EGP1_bit.no3 = 1U;
            EGN1_bit.no3 = 1U;
        }
        else{
            EGP1_bit.no3 = 0U;
            EGN1_bit.no3 = 0U;
        }
        break;
    case 1:
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_1;
        value.modeNum = mode;
        /* 割り込みモードの設定 */
        if (value.modeNum == FALLING) {
            EGP0_bit.no4 = 0U;
            EGN0_bit.no4 = 1U;
        }
        else if (value.modeNum == RISING) {
            EGP0_bit.no4 = 1U;
            EGN0_bit.no4 = 0U;
            }
        else if (value.modeNum == CHANGE){
            EGP0_bit.no4 = 1U;
            EGN0_bit.no4 = 1U;
        }
        else{
            EGP0_bit.no4 = 0U;
            EGN0_bit.no4 = 0U;
        }
        break;
    case 2:
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_2;
        value.modeNum = mode;
        /* 割り込みモードの設定 */
        if (value.modeNum == FALLING) {
            EGP1_bit.no2 = 0U;
            EGN1_bit.no2 = 1U;
        }
        else if (value.modeNum == RISING) {
            EGP1_bit.no2 = 1U;
            EGN1_bit.no2 = 0U;
            }
        else if (value.modeNum == CHANGE){
            EGP1_bit.no2 = 1U;
            EGN1_bit.no2 = 1U;
        }
        else{
            EGP1_bit.no2 = 0U;
            EGN1_bit.no2 = 0U;
        }
        break;
    case 3:
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_3;
        value.modeNum = mode;
        /* 割り込みモードの設定 */
        if (value.modeNum == FALLING) {
            EGP0_bit.no2 = 0U;
            EGN0_bit.no2 = 1U;
        }
        else if (value.modeNum == RISING) {
            EGP0_bit.no2 = 1U;
            EGN0_bit.no2 = 0U;
            }
        else if (value.modeNum == CHANGE){
            EGP0_bit.no2 = 1U;
            EGN0_bit.no2 = 1U;
        }
        else{
            EGP0_bit.no2 = 0U;
            EGN0_bit.no2 = 0U;
        }
        break;
    case 4:
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_4;
        value.modeNum = mode;
        /* 割り込みモードの設定 */
        if (value.modeNum == FALLING) {
            EGP0_bit.no1 = 0U;
            EGN0_bit.no1 = 1U;
        }
        else if (value.modeNum == RISING) {
            EGP0_bit.no1 = 1U;
            EGN0_bit.no1 = 0U;
            }
        else if (value.modeNum == CHANGE){
            EGP0_bit.no1 = 1U;
            EGN0_bit.no1 = 1U;
        }
        else{
            EGP0_bit.no1 = 0U;
            EGN0_bit.no1 = 0U;
        }
        break;
    case 5:
        value.intNum = interruptNum;
        value.pinNum = EXTERNAL_INTERRUPT_5;
        value.modeNum = mode;
        /* 割り込みモードの設定 */
        if (value.modeNum == FALLING) {
            EGP0_bit.no3 = 0U;
            EGN0_bit.no3 = 1U;
        }
        else if (value.modeNum == RISING) {
            EGP0_bit.no3 = 1U;
            EGN0_bit.no3 = 0U;
            }
        else if (value.modeNum == CHANGE){
            EGP0_bit.no3 = 1U;
            EGN0_bit.no3 = 1U;
        }
        else{
            EGP0_bit.no3 = 0U;
            EGN0_bit.no3 = 0U;
        }
        break;
    }
}

void R_Config_INTC_INTP_Start(void){
    if(value.pinNum == EXTERNAL_INTERRUPT_0){
        R_Config_INTC_INTP11_Start();
    }
    else if (value.pinNum == EXTERNAL_INTERRUPT_1){
        R_Config_INTC_INTP4_Start();
    }
    else if (value.pinNum == EXTERNAL_INTERRUPT_2){
        R_Config_INTC_INTP10_Start();
    }
    else if (value.pinNum == EXTERNAL_INTERRUPT_3){
        R_Config_INTC_INTP2_Start();
    }
    else if (value.pinNum == EXTERNAL_INTERRUPT_4){
        R_Config_INTC_INTP1_Start();
    }
    else if (value.pinNum == EXTERNAL_INTERRUPT_5){
        R_Config_INTC_INTP3_Start();
    }
}

void R_Config_INTC_INTP_Stop(uint8_t interruptNum){
    switch (interruptNum) {
        case 0:
            R_Config_INTC_INTP11_Stop();
            break;
        case 1:
            R_Config_INTC_INTP4_Stop();
            break;
        case 2:
            R_Config_INTC_INTP10_Stop();
            break;
        case 3:
            R_Config_INTC_INTP2_Stop();
            break;
        case 4:
            R_Config_INTC_INTP1_Stop();
            break;
        case 5:
            R_Config_INTC_INTP3_Stop();
            break;
    }
}
/* End user code. Do not edit comment generated here */
