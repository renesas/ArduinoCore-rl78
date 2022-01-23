/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_bsp_common.c
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 08.03.2021 1.00     First Release

***********************************************************************************************************************/

/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/
#include "platform.h"

/*************************************************
 * Function definition
 *************************************************/

/**********************************************************************************************************************
 * Function Name: R_BSP_StartClock
 ******************************************************************************************************************//**
 * @brief Start the specified clock and return.
 * @param[in] mode Clock to start.
 * @retval BSP_OK BSP_OK if the specified clock is started.
 * @retval BSP_ARG_ERROR BSP_ARG_ERROR if the specified clock is incorrect.
 * @details This function starts the specified clock.
 * Specify one of the following for mode.
 * HIOCLK : High-speed on-chip oscillator
 * SYSCLK : High-speed system clock
 * SXCLK  : Subsystem clock
 * MIOCLK : Middle-speed on-chip oscillator
 * LOCLK  : Low-speed on-chip oscillator
 */
#if BSP_CFG_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t R_BSP_StartClock(e_clock_mode_t mode)
{
    return start_clock(mode);
}
#endif

/**********************************************************************************************************************
 * Function Name: R_BSP_StopClock
 ******************************************************************************************************************//**
 * @brief Stop the specified clock and return.
 * @param[in] mode Clock to stop.
 * @retval BSP_OK BSP_OK if the specified clock is stopped.
 * @retval BSP_ARG_ERROR BSP_ARG_ERROR if the specified clock is incorrect.
 * @details This function stops the specified clock.
 * Specify one of the following for mode.
 * HIOCLK : High-speed on-chip oscillator
 * SYSCLK : High-speed system clock
 * SXCLK  : Subsystem clock
 * MIOCLK : Middle-speed on-chip oscillator
 * LOCLK  : Low-speed on-chip oscillator
 */
#if BSP_CFG_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t R_BSP_StopClock(e_clock_mode_t mode)
{
    return stop_clock(mode);
}
#endif

/**********************************************************************************************************************
 * Function Name: R_BSP_SetClockSource
 ******************************************************************************************************************//**
 * @brief Switch CPU/peripheral hardware clock(fCLK) clock source and return.
 * @param[in] mode Clock to switch.
 * @retval BSP_OK BSP_OK when switching to the specified clock.
 * @retval BSP_ERROR1 When HIOCLK is specified, but high-speed on-chip oscillator is stopped.
 * @retval BSP_ERROR2 When SYSCLK is specified, but high-speed system clock is stopped.
 * @retval BSP_ERROR3 When SXCLK is specified, but Subsystem clock is stopped.
 * @retval BSP_ERROR4 When MIOCLK is specified, but middle-speed on-chip oscillator is stopped.
 * @retval BSP_ARG_ERROR BSP_ARG_ERROR if the specified clock is incorrect.
 * @details This function switches the specified clock.
 * Specify one of the following for mode.
 * HIOCLK : High-speed on-chip oscillator
 * SYSCLK : High-speed system clock
 * SXCLK  : Subsystem clock
 * MIOCLK : Middle-speed on-chip oscillator
 * LOCLK  : Low-speed on-chip oscillator
 */
#if BSP_CFG_API_FUNCTIONS_DISABLE == 0
e_bsp_err_t R_BSP_SetClockSource(e_clock_mode_t mode)
{
    return set_fclk_clock_source(mode);
}
#endif

/**********************************************************************************************************************
 * Function Name: R_BSP_GetFclkFreqHz
 ******************************************************************************************************************//**
 * @brief Returns CPU/peripheral hardware clock(fCLK) frequency.
 * @return CPU/peripheral hardware clock(fCLK) frequency specified by the r_bsp.
 * @details This function returns the CPU/peripheral hardware clock(fCLK) frequency.
 * For example, when the CPU/peripheral hardware clock(fCLK) is set to 20 MHz in r_bsp_config.h
 * and the r_bsp has completed to specify the clock setting, then even if the user changed the
 * CPU/peripheral hardware clock(fCLK) frequency to 10 MHz, the return value is '10000000'.
 */
#if BSP_CFG_API_FUNCTIONS_DISABLE == 0
uint32_t R_BSP_GetFclkFreqHz(void)
{
    return get_fclk_freq_hz();  // Get the MCU specific ICLK frequency
} /* End of function R_BSP_GetFclkFreqHz() */
#endif

