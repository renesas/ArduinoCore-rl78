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
* File Name    : Config_UART2.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_UART2.
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
#include "Config_UART2.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_uart2_tx_address;    /* uart2 transmit buffer address */
volatile uint16_t g_uart2_tx_count;        /* uart2 transmit data number */
volatile uint8_t * gp_uart2_rx_address;    /* uart2 receive buffer address */
volatile uint16_t g_uart2_rx_count;        /* uart2 receive data number */
volatile uint16_t g_uart2_rx_length;       /* uart2 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_UART2_Create
* Description  : This function initializes the UART2 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART2_Create(void)
{
    SPS1 &= _00F0_SAU_CK00_CLEAR;
    SPS1 |= _0004_SAU_CK00_FCLK_4;
    ST1 |= (_0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON);
    STMK2 = 1U;    /* disable INTST2 interrupt */
    STIF2 = 0U;    /* clear INTST2 interrupt flag */
    SRMK2 = 1U;    /* disable INTSR2 interrupt */
    SRIF2 = 0U;    /* clear INTSR2 interrupt flag */
    SREMK2 = 1U;    /* disable INTSRE2 interrupt */
    SREIF2 = 0U;    /* clear INTSRE2 interrupt flag */
    /* Set INTST2 low priority */
    STPR12 = 1U;
    STPR02 = 1U;
    /* Set INTSR2 low priority */
    SRPR12 = 1U;
    SRPR02 = 1U;
    /* Set INTSRE2 low priority */
    SREPR12 = 1U;
    SREPR02 = 1U;
    SMR10 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_TRIGGER_SOFTWARE | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR10 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | 
            _0010_SAU_STOP_1 | _0007_SAU_LENGTH_8;
    SDR10 = _CE00_SAU1_CH0_TRANSMIT_DIVISOR;
    NFEN0 |= _10_SAU_RXD2_FILTER_ON;
    SIR11 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR11 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR11 = _4000_SAU_RECEPTION | _0400_SAU_INTSRE_ENABLE | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | 
            _0007_SAU_LENGTH_8;
    SDR11 = _CE00_SAU1_CH1_RECEIVE_DIVISOR;
    SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;
    SOL1 |= _0000_SAU_CHANNEL0_NORMAL;    /* output level normal */
    SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable UART2 output */

    R_Config_UART2_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_UART2_Start
* Description  : This function starts UART2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART2_Start(void)
{
    SO1 |= _0001_SAU_CH0_DATA_OUTPUT_1;    /* output level normal */
    SOE1 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable UART2 output */
    SS1 |= (_0002_SAU_CH1_START_TRG_ON | _0001_SAU_CH0_START_TRG_ON);    /* enable UART2 receive and transmit */
    STIF2 = 0U;    /* clear INTST2 interrupt flag */
    SRIF2 = 0U;    /* clear INTSR2 interrupt flag */
    SREIF2 = 0U;    /* clear INTSRE2 interrupt flag */
    STMK2 = 0U;    /* enable INTST2 interrupt */
    SRMK2 = 0U;    /* enable INTSR2 interrupt */
    SREMK2 = 0U;    /* enable INTSRE2 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_UART2_Stop
* Description  : This function stops UART2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART2_Stop(void)
{
    STMK2 = 1U;    /* disable INTST2 interrupt */
    SRMK2 = 1U;    /* disable INTSR2 interrupt */
    SREMK2 = 1U;    /* disable INTSRE2 interrupt */
    ST1 |= (_0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON);
    SOE1 &= (uint16_t)~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable UART2 output */
    STIF2 = 0U;    /* clear INTST2 interrupt flag */
    SRIF2 = 0U;    /* clear INTSR2 interrupt flag */
    SREIF2 = 0U;    /* clear INTSRE2 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_UART2_Send
* Description  : This function sends UART2 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_UART2_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart2_tx_address = tx_buf;
        g_uart2_tx_count = tx_num;
        STMK2 = 1U;    /* disable INTST2 interrupt */
        TXD2 = *gp_uart2_tx_address;
        gp_uart2_tx_address++;
        g_uart2_tx_count--;
        STMK2 = 0U;    /* enable INTST2 interrupt */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_UART2_Receive
* Description  : This function receives UART2 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_UART2_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart2_rx_count = 0U;
        g_uart2_rx_length = rx_num;
        gp_uart2_rx_address = rx_buf;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_UART2_Loopback_Enable
* Description  : This function enables the UART2 loopback function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART2_Loopback_Enable(void)
{
    ULBS2 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_UART2_Loopback_Disable
* Description  : This function disables the UART2 loopback function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART2_Loopback_Disable(void)
{
    ULBS2 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
