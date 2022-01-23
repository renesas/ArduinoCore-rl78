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
* File Name    : Config_UART2_user.c
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
extern volatile uint8_t * gp_uart2_tx_address;    /* uart2 transmit buffer address */
extern volatile uint16_t g_uart2_tx_count;        /* uart2 transmit data number */
extern volatile uint8_t * gp_uart2_rx_address;    /* uart2 receive buffer address */
extern volatile uint16_t g_uart2_rx_count;        /* uart2 receive data number */
extern volatile uint16_t g_uart2_rx_length;       /* uart2 receive data length */
/* Start user code for global. Do not edit comment generated here */
void Set_Char_Serial_to_buf(uint8_t chn);
void Set_Char_Serial_from_buf(uint8_t chn);
extern fInterruptFunc_t uart_receive_callback_table[3] __attribute__((weak));
extern fInterruptFunc_t uart_transmit_callback_table[3] __attribute__((weak));
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_UART2_Create_UserInit
* Description  : This function adds user code after initializing UART2.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_UART2_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART2_callback_sendend
* Description  : This function is a callback function when UART2 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UART2_callback_sendend(void)
{
    /* Start user code for r_Config_UART2_callback_sendend. Do not edit comment generated here */
	Set_Char_Serial_from_buf(2);
	(*uart_transmit_callback_table[2])();
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART2_callback_receiveend
* Description  : This function is a callback function when UART2 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UART2_callback_receiveend(void)
{
    /* Start user code for r_Config_UART2_callback_receiveend. Do not edit comment generated here */
	Set_Char_Serial_to_buf(2);
	(*uart_receive_callback_table[2])();
	/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART2_callback_error
* Description  : This function is a callback function when UART2 reception error occurs.
* Arguments    : err_type -
*                    error type info
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UART2_callback_error(uint8_t err_type)
{
    /* Start user code for r_Config_UART2_callback_error. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART2_callback_softwareoverrun
* Description  : This function is a callback when UART2 receives an overflow data.
* Arguments    : rx_data -
*                    receive data
* Return Value : None
***********************************************************************************************************************/
static void r_Config_UART2_callback_softwareoverrun(uint16_t rx_data)
{
    /* Start user code for r_Config_UART2_callback_softwareoverrun. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_UART2_interrupt_send
* Description  : This function is UART2 send interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_UART2_interrupt_send(void)
{
    if (g_uart2_tx_count > 0U)
    {
        TXD2 = *gp_uart2_tx_address;
        gp_uart2_tx_address++;
        g_uart2_tx_count--;
    }
    else
    {
        r_Config_UART2_callback_sendend();
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_UART2_interrupt_receive
* Description  : This function is UART2 receive interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_UART2_interrupt_receive(void)
{
    uint8_t rx_data;

    rx_data = RXD2;

    if (g_uart2_rx_length > g_uart2_rx_count)
    {
        *gp_uart2_rx_address = rx_data;
        gp_uart2_rx_address++;
        g_uart2_rx_count++;

        if (g_uart2_rx_length == g_uart2_rx_count)
        {
            r_Config_UART2_callback_receiveend();
        }
    }
    else
    {
        r_Config_UART2_callback_softwareoverrun(rx_data);
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_UART2_interrupt_error
* Description  : This function is UART2 error interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_UART2_interrupt_error(void)
{
    uint8_t err_type;

    *gp_uart2_rx_address = RXD2;
    err_type = (uint8_t)(SSR11 & 0x0007U);
    SIR11 = (uint16_t)err_type;
    r_Config_UART2_callback_error(err_type);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
