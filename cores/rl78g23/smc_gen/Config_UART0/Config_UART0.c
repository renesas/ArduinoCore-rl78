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
* File Name    : Config_UART0.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_UART0.
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_uart0_tx_address;    /* uart0 transmit buffer address */
volatile uint16_t g_uart0_tx_count;        /* uart0 transmit data number */
volatile uint8_t * gp_uart0_rx_address;    /* uart0 receive buffer address */
volatile uint16_t g_uart0_rx_count;        /* uart0 receive data number */
volatile uint16_t g_uart0_rx_length;       /* uart0 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Create
* Description  : This function initializes the UART0 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Create(void)
{
    SPS0 &= _00F0_SAU_CK00_CLEAR;
    SPS0 |= _0004_SAU_CK00_FCLK_4;
    ST0 |= (_0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON);
    STMK0 = 1U;    /* disable INTST0 interrupt */
    STIF0 = 0U;    /* clear INTST0 interrupt flag */
    SRMK0 = 1U;    /* disable INTSR0 interrupt */
    SRIF0 = 0U;    /* clear INTSR0 interrupt flag */
    SREMK0 = 1U;    /* disable INTSRE0 interrupt */
    SREIF0 = 0U;    /* clear INTSRE0 interrupt flag */
    /* Set INTST0 low priority */
    STPR10 = 1U;
    STPR00 = 1U;
    /* Set INTSR0 low priority */
    SRPR10 = 1U;
    SRPR00 = 1U;
    /* Set INTSRE0 low priority */
    SREPR10 = 1U;
    SREPR00 = 1U;
    SMR00 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_TRIGGER_SOFTWARE | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR00 = _8000_SAU_TRANSMISSION | _0000_SAU_INTSRE_MASK | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | 
            _0010_SAU_STOP_1 | _0007_SAU_LENGTH_8;
    SDR00 = _CE00_SAU0_CH0_TRANSMIT_DIVISOR;
    NFEN0 |= _01_SAU_RXD0_FILTER_ON;
    SIR01 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR01 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0100_SAU_TRIGGER_RXD | _0000_SAU_EDGE_FALL | 
            _0002_SAU_MODE_UART | _0000_SAU_TRANSFER_END;
    SCR01 = _4000_SAU_RECEPTION | _0400_SAU_INTSRE_ENABLE | _0000_SAU_PARITY_NONE | _0080_SAU_LSB | _0010_SAU_STOP_1 | 
            _0007_SAU_LENGTH_8;
    SDR01 = _CE00_SAU0_CH1_RECEIVE_DIVISOR;
    SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;
    SOL0 |= _0000_SAU_CHANNEL0_NORMAL;    /* output level normal */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable UART0 output */

    R_Config_UART0_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Start
* Description  : This function starts UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Start(void)
{
    SO0 |= _0001_SAU_CH0_DATA_OUTPUT_1;    /* output level normal */
    SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;    /* enable UART0 output */
    SS0 |= (_0002_SAU_CH1_START_TRG_ON | _0001_SAU_CH0_START_TRG_ON);    /* enable UART0 receive and transmit */
    STIF0 = 0U;    /* clear INTST0 interrupt flag */
    SRIF0 = 0U;    /* clear INTSR0 interrupt flag */
    SREIF0 = 0U;    /* clear INTSRE0 interrupt flag */
    STMK0 = 0U;    /* enable INTST0 interrupt */
    SRMK0 = 0U;    /* enable INTSR0 interrupt */
    SREMK0 = 0U;    /* enable INTSRE0 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Stop
* Description  : This function stops UART0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Stop(void)
{
    STMK0 = 1U;    /* disable INTST0 interrupt */
    SRMK0 = 1U;    /* disable INTSR0 interrupt */
    SREMK0 = 1U;    /* disable INTSRE0 interrupt */
    ST0 |= (_0002_SAU_CH1_STOP_TRG_ON | _0001_SAU_CH0_STOP_TRG_ON);
    SOE0 &= (uint16_t)~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable UART0 output */
    STIF0 = 0U;    /* clear INTST0 interrupt flag */
    SRIF0 = 0U;    /* clear INTSR0 interrupt flag */
    SREIF0 = 0U;    /* clear INTSRE0 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Send
* Description  : This function sends UART0 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_UART0_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_uart0_tx_address = tx_buf;
        g_uart0_tx_count = tx_num;
        STMK0 = 1U;    /* disable INTST0 interrupt */
        TXD0 = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
        STMK0 = 0U;    /* enable INTST0 interrupt */
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Receive
* Description  : This function receives UART0 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_UART0_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    MD_STATUS status = MD_OK;

    if (rx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_uart0_rx_count = 0U;
        g_uart0_rx_length = rx_num;
        gp_uart0_rx_address = rx_buf;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Loopback_Enable
* Description  : This function enables the UART0 loopback function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Loopback_Enable(void)
{
    ULBS0 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_UART0_Loopback_Disable
* Description  : This function disables the UART0 loopback function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART0_Loopback_Disable(void)
{
    ULBS0 = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
