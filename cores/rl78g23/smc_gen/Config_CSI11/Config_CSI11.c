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
* File Name    : Config_CSI11.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_CSI11.
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
#include "Config_CSI11.h"
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
volatile uint16_t g_csi11_status_flag;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_CSI11_Create
* Description  : This function initializes the CSI11 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI11_Create(void)
{
    SPS0 &= _000F_SAU_CK01_CLEAR;
//    SPS0 |= _0040_SAU_CK01_FCLK_4;
	SPS0 |= _0000_SAU_CK01_FCLK_0;
    /* Stop channel 3 */
    ST0 |= _0008_SAU_CH3_STOP_TRG_ON;
    /* Mask channel 3 interrupt */
    CSIMK11 = 1U;    /* disable INTCSI11 interrupt */
    CSIIF11 = 0U;    /* clear INTCSI11 interrupt flag */
    /* Set INTCSI11 low priority */
    CSIPR111 = 1U;
    CSIPR011 = 1U;
    SIR03 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;    /* clear error flag */
    SMR03 = _0020_SAU_SMRMN_INITIALVALUE | _8000_SAU_CLOCK_SELECT_CK01 | _0000_SAU_CLOCK_MODE_CKS | 
            _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_MODE_CSI | _0000_SAU_TRANSFER_END;
    SCR03 = _C000_SAU_RECEPTION_TRANSMISSION | _0000_SAU_TIMING_1 | _0080_SAU_LSB | _0007_SAU_LENGTH_8;
    SDR03 = _0C00_SAU0_CH3_BAUDRATE_DIVISOR;
    SO0 |= _0800_SAU_CH3_CLOCK_OUTPUT_1;    /* CSI11 clock initial level */
    SO0 &= (uint16_t)~_0008_SAU_CH3_DATA_OUTPUT_1;    /* CSI11 SO initial level */
    SOE0 |= _0008_SAU_CH3_OUTPUT_ENABLE;    /* enable CSI11 output */
    /* Set SI11 pin */
    PMCT5 &= 0xFEU;
    PMCE5 &= 0xFEU;
    CCDE &= 0xF7U;
    PM5 |= 0x01U;
    /* Set SO11 pin */
    PMCE5 &= 0xFDU;
    CCDE &= 0xFBU;
    P5 |= 0x02U;
    PM5 &= 0xFDU;
    /* Set SCK11 pin */
    PMCT3 &= 0xFEU;
    P3 |= 0x01U;
    PM3 &= 0xFEU;
    
    R_Config_CSI11_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI11_Start
* Description  : This function starts the CSI11 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI11_Start(void)
{
    SO0 |= _0800_SAU_CH3_CLOCK_OUTPUT_1;    /* CSI11 clock initial level */
    SO0 &= (uint16_t)~_0008_SAU_CH3_DATA_OUTPUT_1;    /* CSI11 SO initial level */
    SOE0 |= _0008_SAU_CH3_OUTPUT_ENABLE;    /* enable CSI11 output */
    SS0 |= _0008_SAU_CH3_START_TRG_ON;    /* enable CSI11 */
    CSIIF11 = 0U;    /* clear INTCSI11 interrupt flag */
    CSIMK11 = 0U;    /* enable INTCSI11 interrupt */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI11_Stop
* Description  : This function stops the CSI11 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_CSI11_Stop(void)
{
    CSIMK11 = 1U;    /* disable INTCSI11 interrupt */
    ST0 |= _0008_SAU_CH3_STOP_TRG_ON;    /* disable CSI11 */
    SOE0 &= (uint16_t)~_0008_SAU_CH3_OUTPUT_ENABLE;    /* disable CSI11 output */
    CSIIF11 = 0U;    /* clear INTCSI11 interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_CSI11_Send_Receive
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
MD_STATUS R_Config_CSI11_Send_Receive(uint8_t * const tx_buf, uint16_t tx_num, uint8_t * const rx_buf)
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

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_GetBitOrder
 * Description  : Get the order of the bits shifted out of and into the SPI bus.
 * Arguments    : -
 * Return Value : Current bit order setting
 *              :   LSBFIRST
 *              :   MSBFIRST
 *********************************************************************************************************************/
uint8_t R_Config_CSI11_GetBitOrder(void) {
    return (SCR03 & (uint16_t)_0080_SAU_LSB) == _0080_SAU_LSB
                ? LSBFIRST : MSBFIRST;
}

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_SetBitOrder
 * Description  : Set the order of the bits shifted out of and into the SPI bus.
 * Arguments    : bitOrder - Bit order setting
 *              :   LSBFIRST
 *              :   MSBFIRST
 * Return Value : -
 *********************************************************************************************************************/
void R_Config_CSI11_SetBitOrder(uint8_t bitOrder) {
    ST0     |= _0008_SAU_CH3_STOP_TRG_ON;                       /* Stop channel 3 */
    SOE0    &= (uint16_t)~_0008_SAU_CH3_OUTPUT_ENABLE;          /* disable CSI11 output */

    SCR03    = (SCR03 & (uint16_t)~_0080_SAU_LSB)
             | (bitOrder == LSBFIRST ? _0080_SAU_LSB : _0000_SAU_MSB);

    CSIIF11  = 0U;                                              /* clear INTCSI11 interrupt flag */

    SO0     |= _0800_SAU_CH3_CLOCK_OUTPUT_1;                    /* CSI11 clock initial level */
    SO0     &= (uint16_t)~_0008_SAU_CH3_DATA_OUTPUT_1;          /* CSI11 SO initial level */
    SOE0    |= _0008_SAU_CH3_OUTPUT_ENABLE;                     /* enable CSI11 output */
    SS0     |= _0008_SAU_CH3_START_TRG_ON;                      /* enable CSI11 */
}

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_SetDataMode
 * Description  : Set the SPI data mode (clock polarity and phase).
 * Arguments    : dataMode - SPI data mode
 *              :   SPI_MODE0
 *              :   SPI_MODE1
 *              :   SPI_MODE2
 *              :   SPI_MODE3
 * Return Value : -
 *********************************************************************************************************************/
void R_Config_CSI11_SetDataMode(uint8_t dataMode) {

    ST0     |= _0008_SAU_CH3_STOP_TRG_ON;                       /* Stop channel 3 */
    SOE0    &= (uint16_t)~_0008_SAU_CH3_OUTPUT_ENABLE;          /* disable CSI11 output */

    #warning XXX: Check whether this register setting mapping is correct.
    /*
     * This mapping is obeying the base code.
     * Fix the `SPI_MODEx` macros together.
     */
    switch (dataMode) {
    case SPI_MODE3:     SCR03 = (SCR03 & (uint16_t)~SPI_MODE_MASK) | _0000_SAU_TIMING_1; break;
    case SPI_MODE2:     SCR03 = (SCR03 & (uint16_t)~SPI_MODE_MASK) | _2000_SAU_TIMING_3; break;
    case SPI_MODE1:     SCR03 = (SCR03 & (uint16_t)~SPI_MODE_MASK) | _1000_SAU_TIMING_2; break;
    case SPI_MODE0:
    default:            SCR03 = (SCR03 & (uint16_t)~SPI_MODE_MASK) | _3000_SAU_TIMING_4; break;
    }

    CSIIF11  = 0U;                                              /* clear INTCSI11 interrupt flag */

    SO0     |= _0800_SAU_CH3_CLOCK_OUTPUT_1;                    /* CSI11 clock initial level */
    SO0     &= (uint16_t)~_0008_SAU_CH3_DATA_OUTPUT_1;          /* CSI11 SO initial level */
    SOE0    |= _0008_SAU_CH3_OUTPUT_ENABLE;                     /* enable CSI11 output */
    SS0     |= _0008_SAU_CH3_START_TRG_ON;                      /* enable CSI11 */
}

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_SetClockDivider
 * Description  : Set the SPI clock divider relative to the system clock.
 * Arguments    : clockDiv - SPI clock divider
 *              :   SPI_CLOCK_DIV2
 *              :   SPI_CLOCK_DIV4
 *              :   SPI_CLOCK_DIV8
 *              :   SPI_CLOCK_DIV16
 *              :   SPI_CLOCK_DIV32
 *              :   SPI_CLOCK_DIV64
 *              :   SPI_CLOCK_DIV128
 *              :   or an immediate { 2, 4, 6, 8, ..., 256 }
 * Return Value : -
 *********************************************************************************************************************/
void R_Config_CSI11_SetClockDivider(uint16_t clockDiv) {
    ST0     |= _0008_SAU_CH3_STOP_TRG_ON;                       /* Stop channel 3 */
    SOE0    &= (uint16_t)~_0008_SAU_CH3_OUTPUT_ENABLE;          /* disable CSI11 output */

    clockDiv = clockDiv <   2 ?   2U
             : clockDiv > 256 ? 256U
             :                  clockDiv + (clockDiv & 1U);

    SDR03    = ((clockDiv >> 1) - 1) << 9;

    CSIIF11  = 0U;                                              /* clear INTCSI11 interrupt flag */

    SO0     |= _0800_SAU_CH3_CLOCK_OUTPUT_1;                    /* CSI11 clock initial level */
    SO0     &= (uint16_t)~_0008_SAU_CH3_DATA_OUTPUT_1;          /* CSI11 SO initial level */
    SOE0    |= _0008_SAU_CH3_OUTPUT_ENABLE;                     /* enable CSI11 output */
    SS0     |= _0008_SAU_CH3_START_TRG_ON;                      /* enable CSI11 */
}

/**********************************************************************************************************************
 * Function Name: R_Config_CSI11_SetClock
 * Description  : Set the SPI maximum speed of communication.
 * Arguments    : clock - SPI clock speed
 * Return Value : -
 *********************************************************************************************************************/
void R_Config_CSI11_SetClock(uint32_t clock) {
    uint16_t clockDiv;
    uint32_t spi_frequency = R_BSP_GetFclkFreqHz() >> ((SPS0 >> 4) & 0x0F);

    for (clockDiv = 2; clockDiv < 256; clockDiv += 2) {
    	if (clock >= spi_frequency / clockDiv) {
            break;
        }
    }

    R_Config_CSI11_SetClockDivider(clockDiv);
}

/* End user code. Do not edit comment generated here */
