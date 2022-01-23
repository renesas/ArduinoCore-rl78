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
* File Name    : Config_IICA0_user.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_IICA0.
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
#include "Config_IICA0.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint8_t g_iica0_master_status_flag;      /* iica0 master flag */
extern volatile uint8_t * gp_iica0_rx_address;           /* iica0 receive buffer address */
extern volatile uint16_t g_iica0_rx_len;                 /* iica0 receive data length */
extern volatile uint16_t g_iica0_rx_cnt;                 /* iica0 receive data count */
extern volatile uint8_t * gp_iica0_tx_address;           /* iica0 send buffer address */
extern volatile uint16_t g_iica0_tx_cnt;                 /* iica0 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_IICA0_Create_UserInit
* Description  : This function adds user code after initializing the IICA0.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA0_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA0_callback_master_sendend
* Description  : This function is a callback function when IICA0 finishes master transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA0_callback_master_sendend(void)
{
    SPT0 = 1U;
/* Start user code for r_Config_IICA0_callback_master_sendend. Do not edit comment generated here */

    g_iica0_master_status_flag |= _40_IICA_DATA_COMPLETE;

/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA0_callback_master_receiveend
* Description  : This function is a callback function when IICA0 finishes master reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA0_callback_master_receiveend(void)
{
    SPT0 = 1U;
/* Start user code for r_Config_IICA0_callback_master_receiveend. Do not edit comment generated here */

    g_iica0_master_status_flag |= _40_IICA_DATA_COMPLETE;

/* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA0_callback_master_error
* Description  : This function is a callback function when IICA0 master error occurs.
* Arguments    : flag -
*                    status flag
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA0_callback_master_error(MD_STATUS flag)
{
    /* Start user code for r_Config_IICA0_callback_master_error. Do not edit comment generated here */

    g_iica0_master_status_flag = (g_iica0_master_status_flag & 0xF0U) | (flag & 0x0FU);

    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA0_master_handler
* Description  : This function is IICA0 master handler
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_Config_IICA0_master_handler(void)
{
    /* Control for communication */
    if ((0U == IICBSY0) && (0U != g_iica0_tx_cnt))
    {
        r_Config_IICA0_callback_master_error(MD_SPT);
    }
    /* Control for sended address */
    else
    {
        if (0U == (g_iica0_master_status_flag & _80_IICA_ADDRESS_COMPLETE))
        {
            if (1U == ACKD0)
            {
                g_iica0_master_status_flag |= _80_IICA_ADDRESS_COMPLETE;
                
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
                        r_Config_IICA0_callback_master_sendend();
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
                r_Config_IICA0_callback_master_error(MD_NACK);
            }
        }
        else
        {
            /* Master send control */
            if (1U == TRC0)
            {
                if ((0U == ACKD0) && (0U != g_iica0_tx_cnt))
                {
                    r_Config_IICA0_callback_master_error(MD_NACK);
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
                        r_Config_IICA0_callback_master_sendend();
                    }
                }
            }
            /* Master receive control */
            else
            {
                if (g_iica0_rx_cnt < g_iica0_rx_len)
                {
                    *gp_iica0_rx_address = IICA0;
                    gp_iica0_rx_address++;
                    g_iica0_rx_cnt++;
                    
                    if (g_iica0_rx_cnt == g_iica0_rx_len)
                    {
                        ACKE0 = 0U;
                        WTIM0 = 1U;
                        WREL0 = 1U;
                    }
                    else
                    {
                        WREL0 = 1U;
                    }
                }
                else
                {
                    r_Config_IICA0_callback_master_receiveend();
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_IICA0_interrupt
* Description  : This function is INTIICA0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_IICA0_interrupt(void)
{
    /* Start user code for r_Config_IICA0_interrupt. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    if (0x80U == (IICS0 & _80_IICA_STATUS_MASTER))
    {
        r_Config_IICA0_master_handler();
    }
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
