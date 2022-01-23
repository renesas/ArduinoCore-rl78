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
* File Name    : Config_IICA1.c
* Version      : 1.0.0
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_IICA1.
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
#include "Config_IICA1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t g_iica1_master_status_flag;      /* iica1 master flag */
volatile uint8_t * gp_iica1_rx_address;           /* iica1 receive buffer address */
volatile uint16_t g_iica1_rx_len;                 /* iica1 receive data length */
volatile uint16_t g_iica1_rx_cnt;                 /* iica1 receive data count */
volatile uint8_t * gp_iica1_tx_address;           /* iica1 send buffer address */
volatile uint16_t g_iica1_tx_cnt;                 /* iica1 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_IICA1_Create
* Description  : This function initializes the IICA1 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA1_Create(void)
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
    SMC1 = 0U;
    IICWL1 = _4C_IICA1_IICWL_VALUE;
    IICWH1 = _55_IICA1_IICWH_VALUE;
    IICCTL11 |= _01_IICA_fCLK_HALF;
    SVA1 = _10_IICA1_MASTERADDRESS;
    STCEN1 = 1U;
    IICRSV1 = 1U;
    SPIE1 = 0U;
    WTIM1 = 1U;
    ACKE1 = 1U;
    IICAMK1 = 0U;
    IICE1 = 1U;
    LREL1 = 1U;
    /* Set SCLA1, SDAA1 pin */
    PM6 &= 0xF3U;

    R_Config_IICA1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA1_Stop
* Description  : This function stops IICA1 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA1_Stop(void)
{
    IICE1 = 0U;    /* disable IICA1 operation */
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA1_StopCondition
* Description  : This function stops the IICA1 condition.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_IICA1_StopCondition(void)
{
    SPT1 = 1U;    /* set stop condition flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA1_Master_Send
* Description  : This function starts to send data as master mode.
* Arguments    : adr -
*                    transfer address
*                tx_buf -
*                    transfer buffer pointer
*                tx_num -
*                    buffer size
*                wait -
*                    wait for start condition
* Return Value : status -
*                    MD_OK, MD_ERROR1 or MD_ERROR2
***********************************************************************************************************************/
MD_STATUS R_Config_IICA1_Master_Send(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num, uint8_t wait)
{
    MD_STATUS status = MD_OK;

    IICAMK1 = 1U;    /* disable INTIICA1 interrupt */

    if ((1U == IICBSY1) && (0U == MSTS1))
    {
        /* Check bus busy */
        IICAMK1 = 0U;    /* enable INTIICA1 interrupt */
        status = MD_ERROR1;
    }
    else
    {
        STT1 = 1U;    /* send IICA1 start condition */
        IICAMK1 = 0U;    /* enable INTIICA1 interrupt */

        /* Wait */
        while (0U == STD1)
        {
            if (0U == (wait--))
            {
                status = MD_ERROR2;
                break;
            }
        }

        /* Detect start condition */
        if (MD_OK == status)
        {
            g_iica1_tx_cnt = tx_num;
            gp_iica1_tx_address = tx_buf;
            g_iica1_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
            adr &= (uint8_t)~0x01U;    /* set send mode */
            IICA1 = adr;    /* send address */
        }
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_IICA1_Master_Receive
* Description  : This function starts to receive data as master mode.
* Arguments    : adr -
*                    receive address
*                rx_buf -
*                    receive buffer pointer
*                rx_num -
*                    buffer size
*                wait -
*                    wait for start condition
* Return Value : status -
*                    MD_OK, MD_ERROR1 or MD_ERROR2
***********************************************************************************************************************/
MD_STATUS R_Config_IICA1_Master_Receive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num, uint8_t wait)
{
    MD_STATUS status = MD_OK;

    IICAMK1 = 1U;    /* disable INTIICA1 interrupt */

    if ((1U == IICBSY1) && (0U == MSTS1))
    {
        /* Check bus busy */
        IICAMK1 = 0U;    /* enable INTIICA1 interrupt */
        status = MD_ERROR1;
    }
    else
    {
        STT1 = 1U;    /* send IICA1 start condition */
        IICAMK1 = 0U;    /* enable INTIICA1 interrupt */
        
        /* Wait */
        while (0U == STD1)
        {
            if (0U == (wait--))
            {
                status = MD_ERROR2;
                break;
            }
        }

        /* Detect start condition */
        if (MD_OK == status)
        {
            /* Set parameter */
            g_iica1_rx_len = rx_num;
            g_iica1_rx_cnt = 0U;
            gp_iica1_rx_address = rx_buf;
            g_iica1_master_status_flag = _00_IICA_MASTER_FLAG_CLEAR;
            adr |= 0x01U;    /* set receive mode */
            IICA1 = adr;    /* receive address */
        }
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */

/**********************************************************************************************************************
 * Function Name: R_Config_IICA1_Master_SetClock
 * Description  : This function sets I2C clock frequency
 * Arguments    : clock - clock frequency to set
 *              :   The given frequency is normalized
 *              :   cutting off to the either one of the frequencies below:
 *              :     I2C_CLOCK_FAST_PLUS = 1,000,000 Hz (fast     mode plus)
 *              :     I2C_CLOCK_FAST      =   400,000 Hz (fast     mode     )
 *              :     I2C_CLOCK_STANDARD  =   100,000 Hz (standard mode     )
 *              :   If the given frequency is lower than above all,
 *              :   considers it as the lowest clock or standard mode 100,000 Hz.
 * Return Value : None
 *********************************************************************************************************************/
void R_Config_IICA1_Master_SetClock(uint32_t clock) {
    if (IICA1EN == 0U || IICE1 == 0U) {
        return;
    }

    double coeffL, coeffH;
#if !defined(DISABLE_CLOCK_FAST_PLUS)
    if      ( clock >= I2C_CLOCK_FAST_PLUS ) { clock = I2C_CLOCK_FAST_PLUS; coeffL = 0.50; coeffH = 0.50; }
    else
#endif /* !defined(DISABLE_CLOCK_FAST_PLUS) */
    if      ( clock >= I2C_CLOCK_FAST      ) { clock = I2C_CLOCK_FAST     ; coeffL = 0.52; coeffH = 0.48; }
    else                                     { clock = I2C_CLOCK_STANDARD ; coeffL = 0.47; coeffH = 0.53; }

    /*
     * XXX:
     * Register access code is copied from `R_Config_IICA1_Create()`.
     * Do the same settings but clock `IICWL1` / `IICWH1`.
     */

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
    SMC1 = 0U;

    IICWL1 = (uint8_t)(ceil((configCPU_CLOCK_HZ / 2 * coeffL) / clock));
    IICWH1 = (uint8_t)(ceil((configCPU_CLOCK_HZ / 2 * coeffH) / clock));

    IICCTL11 |= _01_IICA_fCLK_HALF;
    SVA1 = _10_IICA1_MASTERADDRESS;
    STCEN1 = 1U;
    IICRSV1 = 1U;
    SPIE1 = 0U;
    WTIM1 = 1U;
    ACKE1 = 1U;
    IICAMK1 = 0U;
    IICE1 = 1U;
    LREL1 = 1U;
    /* Set SCLA1, SDAA1 pin */
    PM6 &= 0xF3U;
}

/* End user code. Do not edit comment generated here */
