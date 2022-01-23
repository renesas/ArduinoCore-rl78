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
* File Name    : Config_IICA01.c
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
volatile uint8_t g_iica0_slave_status_flag;      /* iica0 slave flag */
volatile uint8_t * gp_iica0_rx_address;          /* iica0 receive buffer address */
volatile uint16_t g_iica0_rx_len;                /* iica0 receive data length */
volatile uint16_t g_iica0_rx_cnt;                /* iica0 receive data count */
volatile uint8_t * gp_iica0_tx_address;          /* iica0 send buffer address */
volatile uint16_t g_iica0_tx_cnt;                /* iica0 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_IICA01_Create
* Description  : This function initializes the IICA0 slave mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA01_Create(void)
{
    IICA0EN = 1U;    /* enables input clock supply */
    IICE0 = 0U;
    IICAMK0 = 1U;    /* disable INTIICA0 interrupt */
    IICAIF0 = 0U;    /* clear INTIICA0 interrupt flag */
    /* Set INTIICA0 low priority */
    IICAPR10 = 1U;
    IICAPR00 = 1U;
    /* Set SCLA0, SDAA0 pin */
    PMCE6 &= 0xFCU;
    CCDE &= 0xCFU;
    P6 &= 0xFCU;
    PM6 |= 0x03U;
    IICWL0 = _4C_IICA0_IICWL_VALUE;
    IICWH0 = _55_IICA0_IICWH_VALUE;
    IICRSV0 = 1U;
    SMC0 = 0U;
    IICCTL01 |= _01_IICA_fCLK_HALF;
    SVA0 = _10_IICA0_SLAVEADDRESS;
    STCEN0 = 1U;
    SPIE0 = 0U;
    WTIM0 = 1U;
    ACKE0 = 1U;
    IICAMK0 = 0U;
    IICE0 = 1U;
    LREL0 = 1U;
    /* Set SCLA0, SDAA0 pin */
    PM6 &= 0xFCU;

    R_Config_IICA01_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA01_Stop
* Description  : This function stops IICA0 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA01_Stop(void)
{
    IICE0 = 0U;    /* disable IICA0 operation */
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA01_Slave_Send
* Description  : This function starts to send data as slave mode.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA01_Slave_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    g_iica0_tx_cnt = tx_num;
    gp_iica0_tx_address = tx_buf;
    g_iica0_slave_status_flag = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA01_Slave_Receive
* Description  : This function starts to receive data as slave mode.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA01_Slave_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    g_iica0_rx_len = rx_num;
    g_iica0_rx_cnt = 0U;
    gp_iica0_rx_address = rx_buf; 
    g_iica0_slave_status_flag = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
