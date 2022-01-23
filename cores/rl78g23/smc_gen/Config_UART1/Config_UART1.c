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
* File Name    : Config_UART1.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_UART1.
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
#include "Config_UART1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_uart1_tx_address;    /* uart1 transmit buffer address */
volatile uint16_t g_uart1_tx_count;        /* uart1 transmit data number */
volatile uint8_t * gp_uart1_rx_address;    /* uart1 receive buffer address */
volatile uint16_t g_uart1_rx_count;        /* uart1 receive data number */
volatile uint16_t g_uart1_rx_length;       /* uart1 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_UART1_Create
* Description  : This function initializes the UART1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART1_Create(void)
{
    SPS0 &= _000F_SAU_CK01_CLEAR;
    SPS0 |= _0040_SAU_CK01_FCLK_4;
    ST0 |= (_0008_SAU_CH3_STOP_TRG_ON | _0004_SAU_CH2_STOP_TRG_ON);
    STMK1 = 1U;    /* disable INTST1 interrupt */
    STIF1 = 0U;    /* clear INTST1 interrupt flag */
    SRMK1 = 1U;    /* disable INTSR1 interrupt */
    SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
    SREMK1 = 1U;    /* disable INTSRE1 interrupt */
    SREIF1 = 0U;    /* clear INTSRE1 interrupt flag */
    /* Set INTST1 low priority */
    STPR11 = 1U;
    STPR01 = 1U;
    /* Set INTSR1 low priority */
    SRPR11 = 1U;
    SRPR01 = 1U;
    /* Set INTSRE1 low priority */
    SREPR11 = 1U;
    SREPR01 = 1U;
    SMR02 = _0020_SAU_SMRMN_INITIALVALUE | _8000_SAU_CLOCK_SELECT_CK01 | _0000_SAU_TRIGGER_SOFTWARE | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR02 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | 
            _0010_SAU_STOP_1 | _0007_SAU_LENGTH_8;
    SDR02 = _CE00_SAU0_CH2_TRANSMIT_DIVISOR;
    NFEN0 |= _04_SAU_RXD1_FILTER_ON;
    SIR03 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR03 = _0020_SAU_SMRMN_INITIALVALUE | _8000_SAU_CLOCK_SELECT_CK01 | _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR03 = _4000_SAU_RECEPTION | _0400_SAU_INTSRE_ENABLE | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | 
            _0007_SAU_LENGTH_8;
    SDR03 = _CE00_SAU0_CH3_RECEIVE_DIVISOR;
    SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;
    SOL0 |= _0000_SAU_CHANNEL2_NORMAL;    /* output level normal */
    SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable UART1 output */

    R_Config_UART1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_UART1_Start
* Description  : This function starts UART1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART1_Start(void)
{
    SO0 |= _0004_SAU_CH2_DATA_OUTPUT_1;    /* output level normal */
    SOE0 |= _0004_SAU_CH2_OUTPUT_ENABLE;    /* enable UART1 output */
    SS0 |= (_0008_SAU_CH3_START_TRG_ON | _0004_SAU_CH2_START_TRG_ON);    /* enable UART1 receive and transmit */
    STIF1 = 0U;    /* clear INTST1 interrupt flag */
    SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
    SREIF1 = 0U;    /* clear INTSRE1 interrupt flag */
    STMK1 = 0U;    /* enable INTST1 interrupt */
    SRMK1 = 0U;    /* enable INTSR1 interrupt */
    SREMK1 = 0U;    /* enable INTSRE1 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_UART1_Stop
* Description  : This function stops UART1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART1_Stop(void)
{
    STMK1 = 1U;    /* disable INTST1 interrupt */
    SRMK1 = 1U;    /* disable INTSR1 interrupt */
    SREMK1 = 1U;    /* disable INTSRE1 interrupt */
    ST0 |= (_0008_SAU_CH3_STOP_TRG_ON | _0004_SAU_CH2_STOP_TRG_ON);
    SOE0 &= (uint16_t)~_0004_SAU_CH2_OUTPUT_ENABLE;    /* disable UART1 output */
    STIF1 = 0U;    /* clear INTST1 interrupt flag */
    SRIF1 = 0U;    /* clear INTSR1 interrupt flag */
    SREIF1 = 0U;    /* clear INTSRE1 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_UART1_Send
* Description  : This function sends UART1 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_UART1_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart1_tx_address = tx_buf;
        g_uart1_tx_count = tx_num;
        STMK1 = 1U;    /* disable INTST1 interrupt */
        TXD1 = *gp_uart1_tx_address;
        gp_uart1_tx_address++;
        g_uart1_tx_count--;
        STMK1 = 0U;    /* enable INTST1 interrupt */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_UART1_Receive
* Description  : This function receives UART1 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_UART1_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart1_rx_count = 0U;
        g_uart1_rx_length = rx_num;
        gp_uart1_rx_address = rx_buf;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_UART1_Loopback_Enable
* Description  : This function enables the UART1 loopback function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART1_Loopback_Enable(void)
{
    ULBS1 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_UART1_Loopback_Disable
* Description  : This function disables the UART1 loopback function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART1_Loopback_Disable(void)
{
    ULBS1 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
