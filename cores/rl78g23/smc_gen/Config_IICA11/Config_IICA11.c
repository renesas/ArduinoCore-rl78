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
* File Name    : Config_IICA11.c
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
volatile uint8_t g_iica1_slave_status_flag;      /* iica1 slave flag */
volatile uint8_t * gp_iica1_rx_address;          /* iica1 receive buffer address */
volatile uint16_t g_iica1_rx_len;                /* iica1 receive data length */
volatile uint16_t g_iica1_rx_cnt;                /* iica1 receive data count */
volatile uint8_t * gp_iica1_tx_address;          /* iica1 send buffer address */
volatile uint16_t g_iica1_tx_cnt;                /* iica1 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_IICA11_Create
* Description  : This function initializes the IICA1 slave mode.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA11_Create(void)
{
    IICA1EN = 1U;    /* enables input clock supply */
    IICE1 = 0U;
    IICAMK1 = 1U;    /* disable INTIICA1 interrupt */
    IICAIF1 = 0U;    /* clear INTIICA1 interrupt flag */
    /* Set INTIICA1 low priority */
    IICAPR11 = 1U;
    IICAPR01 = 1U;
    /* Set SCLA1, SDAA1 pin */
    CCDE &= 0x3FU;
    P6 &= 0xF3U;
    PM6 |= 0x0CU;
    IICWL1 = _4C_IICA1_IICWL_VALUE;
    IICWH1 = _55_IICA1_IICWH_VALUE;
    IICRSV1 = 1U;
    SMC1 = 0U;
    IICCTL11 |= _01_IICA_fCLK_HALF;
    SVA1 = _10_IICA1_SLAVEADDRESS;
    STCEN1 = 1U;
    SPIE1 = 0U;
    WTIM1 = 1U;
    ACKE1 = 1U;
    IICAMK1 = 0U;
    IICE1 = 1U;
    LREL1 = 1U;
    /* Set SCLA1, SDAA1 pin */
    PM6 &= 0xF3U;

    R_Config_IICA11_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA11_Stop
* Description  : This function stops IICA1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA11_Stop(void)
{
    IICE1 = 0U;    /* disable IICA1 operation */
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA11_Slave_Send
* Description  : This function starts to send data as slave mode.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA11_Slave_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    g_iica1_tx_cnt = tx_num;
    gp_iica1_tx_address = tx_buf;
    g_iica1_slave_status_flag = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA11_Slave_Receive
* Description  : This function starts to receive data as slave mode.
* Arguments    : rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA11_Slave_Receive(uint8_t * const rx_buf, uint16_t rx_num)
{
    g_iica1_rx_len = rx_num;
    g_iica1_rx_cnt = 0U;
    gp_iica1_rx_address = rx_buf; 
    g_iica1_slave_status_flag = 0U;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
