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
* File Name    : Config_IICA11_user.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_IICA11.
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
#include "Config_IICA11.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t   g_iica1_slave_status_flag;    /* iica1 slave flag */
extern volatile uint8_t * gp_iica1_rx_address;          /* iica1 receive buffer address */
extern volatile uint16_t  g_iica1_rx_len;               /* iica1 receive data length */
extern volatile uint16_t  g_iica1_rx_cnt;               /* iica1 receive data count */
extern volatile uint8_t * gp_iica1_tx_address;          /* iica1 send buffer address */
extern volatile uint16_t  g_iica1_tx_cnt;               /* iica1 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_IICA11_Create_UserInit
* Description  : This function adds user code after initializing the IICA1.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA11_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA11_callback_slave_sendend
* Description  : This function is a callback function when IICA1 finishes slave transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA11_callback_slave_sendend(void)
{
    /* Start user code for r_Config_IICA11_callback_slave_sendend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA11_callback_slave_receiveend
* Description  : This function is a callback function when IICA1 finishes slave reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA11_callback_slave_receiveend(void)
{
    /* Start user code for r_Config_IICA11_callback_slave_receiveend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA11_callback_slave_error
* Description  : This function is a callback function when IICA1 slave error occurs.
* Arguments    : flag -
*                    status flag
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA11_callback_slave_error(MD_STATUS flag)
{
    /* Start user code for r_Config_IICA11_callback_slave_error. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA11_callback_getstopcondition
* Description  : This function is a callback function when IICA1 gets a slave stop condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA11_callback_getstopcondition(void)
{
    /* Start user code for r_Config_IICA11_callback_getstopcondition. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA11_slave_handler
* Description  : This function is IICA1 slave handler
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA11_slave_handler(void)
{
    /* Control for stop condition */
    if (1U == SPD1)
    {
        /* Get stop condition */
        SPIE1 = 0U;
        r_Config_IICA11_callback_getstopcondition();
        g_iica1_slave_status_flag = 1U;
    }
    else
    {
        if (0U == (g_iica1_slave_status_flag & _80_IICA_ADDRESS_COMPLETE))
        {
            if (1U == COI1)
            {
                SPIE1 = 1U;
                g_iica1_slave_status_flag |= _80_IICA_ADDRESS_COMPLETE;
                
                if (1U == TRC1)
                {
                    WTIM1 = 1U;
                    
                    if (g_iica1_tx_cnt > 0U)
                    {
                        IICA1 = *gp_iica1_tx_address;
                        gp_iica1_tx_address++;
                        g_iica1_tx_cnt--;
                    }
                    else
                    {
                        r_Config_IICA11_callback_slave_sendend();
                        WREL1 = 1U;
                    }
                }
                else
                {
                    ACKE1 = 1U;
                    WTIM1 = 0U;
                    WREL1 = 1U;
                }
            }
            else
            {
                r_Config_IICA11_callback_slave_error(MD_ERROR);
            }
        }
        else
        {
            if (1U == TRC1)
            {
                if ((0U == ACKD1) && (0U != g_iica1_tx_cnt))
                {
                    r_Config_IICA11_callback_slave_error(MD_NACK);
                }
                else
                {
                    if (g_iica1_tx_cnt > 0U)
                    {
                        IICA1 = *gp_iica1_tx_address;
                        gp_iica1_tx_address++;
                        g_iica1_tx_cnt--;
                    }
                    else
                    {
                        r_Config_IICA11_callback_slave_sendend();
                        WREL1 = 1U;
                    }
                }
            }
            else
            {
                if (g_iica1_rx_cnt < g_iica1_rx_len)
                {
                    *gp_iica1_rx_address = IICA1;
                    gp_iica1_rx_address++;
                    g_iica1_rx_cnt++;
                    
                    if (g_iica1_rx_cnt == g_iica1_rx_len)
                    {
                        WTIM1 = 1U;
                        WREL1 = 1U;
                        r_Config_IICA11_callback_slave_receiveend();
                    }
                    else
                    {
                        WREL1 = 1U;
                    }
                }
                else
                {
                    WREL1 = 1U;
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA11_interrupt
* Description  : This function is INTIICA1 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_IICA11_interrupt(void)
{
    /* Start user code for r_Config_IICA11_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    if (0U == (IICS1 & _80_IICA_STATUS_MASTER))
    {
        r_Config_IICA11_slave_handler();
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
