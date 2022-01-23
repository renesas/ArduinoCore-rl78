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
* File Name    : Config_IICA01_user.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_IICA01.
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
#include "Config_IICA01.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t   g_iica0_slave_status_flag;    /* iica0 slave flag */
extern volatile uint8_t * gp_iica0_rx_address;          /* iica0 receive buffer address */
extern volatile uint16_t  g_iica0_rx_len;               /* iica0 receive data length */
extern volatile uint16_t  g_iica0_rx_cnt;               /* iica0 receive data count */
extern volatile uint8_t * gp_iica0_tx_address;          /* iica0 send buffer address */
extern volatile uint16_t  g_iica0_tx_cnt;               /* iica0 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_IICA01_Create_UserInit
* Description  : This function adds user code after initializing the IICA0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA01_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA01_callback_slave_sendend
* Description  : This function is a callback function when IICA0 finishes slave transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA01_callback_slave_sendend(void)
{
    /* Start user code for r_Config_IICA01_callback_slave_sendend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA01_callback_slave_receiveend
* Description  : This function is a callback function when IICA0 finishes slave reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA01_callback_slave_receiveend(void)
{
    /* Start user code for r_Config_IICA01_callback_slave_receiveend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA01_callback_slave_error
* Description  : This function is a callback function when IICA0 slave error occurs.
* Arguments    : flag -
*                    status flag
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA01_callback_slave_error(MD_STATUS flag)
{
    /* Start user code for r_Config_IICA01_callback_slave_error. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA01_callback_getstopcondition
* Description  : This function is a callback function when IICA0 gets a slave stop condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA01_callback_getstopcondition(void)
{
    /* Start user code for r_Config_IICA01_callback_getstopcondition. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA01_slave_handler
* Description  : This function is IICA0 slave handler
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA01_slave_handler(void)
{
    /* Control for stop condition */
    if (1U == SPD0)
    {
        /* Get stop condition */
        SPIE0 = 0U;
        r_Config_IICA01_callback_getstopcondition();
        g_iica0_slave_status_flag = 1U;
    }
    else
    {
        if (0U == (g_iica0_slave_status_flag & _80_IICA_ADDRESS_COMPLETE))
        {
            if (1U == COI0)
            {
                SPIE0 = 1U;
                g_iica0_slave_status_flag |= _80_IICA_ADDRESS_COMPLETE;
                
                if (1U == TRC0)
                {
                    WTIM0 = 1U;
                    
                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    }
                    else
                    {
                        r_Config_IICA01_callback_slave_sendend();
                        WREL0 = 1U;
                    }
                }
                else
                {
                    ACKE0 = 1U;
                    WTIM0 = 0U;
                    WREL0 = 1U;
                }
            }
            else
            {
                r_Config_IICA01_callback_slave_error(MD_ERROR);
            }
        }
        else
        {
            if (1U == TRC0)
            {
                if ((0U == ACKD0) && (0U != g_iica0_tx_cnt))
                {
                    r_Config_IICA01_callback_slave_error(MD_NACK);
                }
                else
                {
                    if (g_iica0_tx_cnt > 0U)
                    {
                        IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    }
                    else
                    {
                        r_Config_IICA01_callback_slave_sendend();
                        WREL0 = 1U;
                    }
                }
            }
            else
            {
                if (g_iica0_rx_cnt < g_iica0_rx_len)
                {
                    *gp_iica0_rx_address = IICA0;
                    gp_iica0_rx_address++;
                    g_iica0_rx_cnt++;
                    
                    if (g_iica0_rx_cnt == g_iica0_rx_len)
                    {
                        WTIM0 = 1U;
                        WREL0 = 1U;
                        r_Config_IICA01_callback_slave_receiveend();
                    }
                    else
                    {
                        WREL0 = 1U;
                    }
                }
                else
                {
                    WREL0 = 1U;
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA01_interrupt
* Description  : This function is INTIICA0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_IICA01_interrupt(void)
{
    /* Start user code for r_Config_IICA01_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    if (0U == (IICS0 & _80_IICA_STATUS_MASTER))
    {
        r_Config_IICA01_slave_handler();
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
