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
* File Name    : Config_CSI111.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_CSI111.
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
#include "Config_CSI111.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_csi11_tx_address;    /* csi11 send buffer address */
volatile uint16_t g_csi11_tx_count;        /* csi11 send data count */
volatile uint8_t * gp_csi11_rx_address;    /* csi11 receive buffer address */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_CSI111_Create
* Description  : This function initializes the CSI11 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI111_Create(void)
{
    /* Stop channel 3 */
    ST0 |= _0008_SAU_CH3_STOP_TRG_ON;
    /* Mask channel 3 interrupt */
    CSIMK11 = 1U;    /* disable INTCSI11 interrupt */
    CSIIF11 = 0U;    /* clear INTCSI11 interrupt flag */
    /* Set INTCSI11 low priority */
    CSIPR111 = 1U;
    CSIPR011 = 1U;
    SIR03 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR03 = _0020_SAU_SMRMN_INITIALVALUE | _4000_SAU_CLOCK_MODE_TI0N | _0000_SAU_TRIGGER_SOFTWARE | 
            _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
    SCR03 = _C000_SAU_RECEPTION_TRANSMISSION | _0000_SAU_TIMING_1 | _0080_SAU_LSB | _0007_SAU_LENGTH_8;
    SDR03 = 0U;
    SO0 &= (uint16_t)~_0008_SAU_CH3_DATA_OUTPUT_1;    /* CSI11 SO initial level */
    SOE0 |= _0008_SAU_CH3_OUTPUT_ENABLE;    /* enable CSI11 output */
    
    R_Config_CSI111_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI111_Start
* Description  : This function starts the CSI11 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI111_Start(void)
{
    SO0 &= (uint16_t)~_0008_SAU_CH3_DATA_OUTPUT_1;    /* CSI11 SO initial level */
    SOE0 |= _0008_SAU_CH3_OUTPUT_ENABLE;    /* enable CSI11 output */
    SS0 |= _0008_SAU_CH3_START_TRG_ON;    /* enable CSI11 */
    CSIIF11 = 0U;    /* clear INTCSI11 interrupt flag */
    CSIMK11 = 0U;    /* enable INTCSI11 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI111_Stop
* Description  : This function stops the CSI11 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI111_Stop(void)
{
    CSIMK11 = 1U;    /* disable INTCSI11 interrupt */
    ST0 |= _0008_SAU_CH3_STOP_TRG_ON;    /* disable CSI11 */
    SOE0 &= (uint16_t)~_0008_SAU_CH3_OUTPUT_ENABLE;    /* disable CSI11 output */
    CSIIF11 = 0U;    /* clear INTCSI11 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI111_Send_Receive
* Description  : This function sends and receives CSI11 data.
* Arguments    : tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
*                rx_buf -
*                    receive buffer pointer
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_CSI111_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf)
{
    MD_STATUS status = MD_OK;

    if (tx_num < 1U)
    {
        status = MD_ARGERROR;
    }
    else
    {
        g_csi11_tx_count = tx_num;    /* send data count */
        gp_csi11_tx_address = tx_buf;    /* send buffer pointer */
        gp_csi11_rx_address = rx_buf;    /* receive buffer pointer */
        CSIMK11 = 1U;    /* disable INTCSI11 interrupt */

        if (0U != gp_csi11_tx_address)
        {
            SIO11 = *gp_csi11_tx_address;    /* started by writing data to SDR03[7:0] */
            gp_csi11_tx_address++;
        }
        else
        {
            SIO11 = 0xFFU;
        }

        g_csi11_tx_count--;
        CSIMK11 = 0U;    /* enable INTCSI11 interrupt */
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
