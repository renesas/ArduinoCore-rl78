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
* File Name    : Config_ADC.c
* Version      : 1.0.1
* Device(s)    : R7F100GLGxFB
* Description  : This file implements device driver for Config_ADC.
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
#include "Config_ADC.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Create
* Description  : This function initializes the ADC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Create(void)
{
    volatile uint16_t w_count;
    
    ADCEN = 1U;    /* supply AD clock */
    ADMK = 1U;    /* disable INTAD interrupt */
    ADIF = 0U;    /* clear INTAD interrupt flag */
    /* Set INTAD priority */
    ADPR1 = 1U;
    ADPR0 = 1U;
    /* Set ANI2 pin */
    PMCA2 |= 0x04U;
    PM2 |= 0x04U; 
    ADM0 = _00_AD_OPERMODE_SELECT | _00_AD_CONVERSION_CLOCK_32 | _00_AD_TIME_MODE_NORMAL_1;
    ADM1 = _00_AD_TRIGGER_SOFTWARE | _00_AD_FCLK_BETWEEN_4_32 | _00_AD_CONVMODE_CONSELECT;
    ADM2 = _00_AD_NEGATIVE_VSS | _00_AD_AREA_MODE_1 | _00_AD_RESOLUTION_10BIT;
    ADUL = _FF_AD_ADUL_VALUE;
    ADLL = _00_AD_ADLL_VALUE;
    ADS = _02_AD_INPUT_CHANNEL_2;
    ADM2 &= _3F_AD_POSITIVE_CLEAR;    /* clear ADREFP1 and ADREFP0 */
    ADM2 |= _00_AD_POSITIVE_VDD;    /* set the reference voltage */

    R_Config_ADC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Start
* Description  : This function starts the AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Start(void)
{
    ADIF = 0U;    /* clear INTAD interrupt flag */
    ADMK = 0U;    /* enable INTAD interrupt */
    ADCS = 1U;    /* enables conversion operation */
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Stop
* Description  : This function stops the AD converter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Stop(void)
{
    ADCS = 0U;    /* stops conversion operation */
    ADMK = 1U;    /* disables INTAD interrupt */
    ADIF = 0U;    /* clear INTAD interrupt flag */
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Set_OperationOn
* Description  : This function enables AD voltage comparator operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Set_OperationOn(void)
{
    volatile uint16_t w_count;
    
    ADCE = 1U;    /* enable AD comparator */
    
    /* Reference voltage stability wait time (B) 1us */
    for (w_count = 0U; w_count < AD_WAITTIME_B; w_count++)
    {
        NOP();
    }
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Set_OperationOff
* Description  : This function disables AD voltage comparator operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Set_OperationOff(void)
{
    ADCE = 0U;    /* disable AD comparator */
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Set_SnoozeOn
* Description  : This function enables AD wakeup function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Set_SnoozeOn(void)
{
    AWC = 1U;    /* use wakeup function */
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Set_SnoozeOff
* Description  : This function disables AD wakeup function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Set_SnoozeOff(void)
{
    AWC = 0U;    /* stop wakeup function */
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Get_Result_10bit
* Description  : This function returns the high 10 bits conversion result in the buffer.
* Arguments    : buffer -
*                    the address where to write the conversion result
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Get_Result_10bit(uint16_t * const buffer)
{
    *buffer = (uint16_t)(ADCR0 >> 6U);
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Set_ADChannel
* Description  : This function selects analog input channel.
* Arguments    : channel -
*                    analog input channel
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_ADC_Set_ADChannel(e_ad_channel_t channel)
{
    MD_STATUS status = MD_OK;

    if (((channel > ADCHANNEL7) && (channel < ADCHANNEL16)) || ((channel > ADCHANNEL19) && (channel < ADTEMPERSENSOR0))
        || (channel > ADINTERREFVOLT))
    {
        status = MD_ARGERROR;
    }
    else
    {
        ADS = (uint8_t)channel;
    }

    return (status);
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Set_TestChannel
* Description  : This function sets test function.
* Arguments    : channel -
*                    sets test channel
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/
MD_STATUS R_Config_ADC_Set_TestChannel(e_test_channel_t channel)
{
    MD_STATUS status = MD_OK;

    if ((1U == channel) || (4U <= channel))
    {
        status = MD_ARGERROR;
    }
    else
    {
        ADTES = (uint8_t)channel;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */

//MD_STATUS R_Config_ADC_Set_Refference(uint8_t mode)
//{
//	MD_STATUS status = MD_OK;
//
//	if (mode == DEFAULT) {
//		ADM2 = 0x00;	// Vdd���t�@�����X�ɐݒ�
//	} else if (mode == INTERNAL) {
//		ADM2 = 0x80;	// �������t�@�����X(1.45V)�ɐݒ�
//	} else { // EXTERNAL
//		ADM2 = 0x40;	// �O�����t�@�����X�ɐݒ�
//	}
//	return status;
//}

/* 1006 Nhu */
/***********************************************************************************************************************
* Function Name: R_Config_ADC_Set_Reference
* Description  : This function configures the reference voltage used for analog input.
* Arguments    : mode -
*                    DEFAULT: use VDD as VREF(+)
*                    INTERNAL: use internal voltage as VREF(+)
*                    EXTERNAL: use AVREFP as VREF(+)
* Return Value : None
***********************************************************************************************************************/

MD_STATUS R_Config_ADC_Set_Reference(uint8_t mode)
{
	MD_STATUS status = MD_OK;
	volatile uint16_t w_count;

	if (DEFAULT == mode)
	{
		ADM2 |= _00_AD_POSITIVE_VDD;	/* use VDD as VREF(+) */
	}
	else if (INTERNAL == mode)
	{
		ADM0 |= _04_AD_TIME_MODE_LOWVOLTAGE_1;
		ADM2 |= _01_AD_RESOLUTION_8BIT;
		ADM2 |= _C0_AD_POSITIVE_DISCHARGE;		/* Discharge */

	/* Reference voltage discharge time 1us */
	for (w_count = 0U; w_count < AD_WAITTIME_DISCHARGE; w_count++)
		{
			NOP();
		}

	ADM2 &= _3F_AD_POSITIVE_CLEAR;		/* clear ADREFP1 and ADREFP0 */
	ADM2 |= _80_AD_POSITIVE_INTERVOLT;		/* set the reference voltage */

	/* Internal reference voltage is selected, Reference voltage stability wait time(A), 5us */
	for (w_count = 0U; w_count < AD_WAITTIME_A; w_count++)
		{
			NOP();
		}

		ADM2 |= _80_AD_POSITIVE_INTERVOLT;		/* use internal voltage as VREF(+) */

	}
	else //EXTERNAL
	{
		ADM2 |= _40_AD_POSITIVE_AVREFP;		/* use AVREFP as VREF(+) */
	}
	return status;
}

/***********************************************************************************************************************
* Function Name: R_Config_ADC_Get_Result_8bit
* Description  : This function returns the high 8 bits conversion result in the buffer.
* Arguments    : buffer -
*                    the address where to write the conversion result
* Return Value : None
***********************************************************************************************************************/
void R_Config_ADC_Get_Result_8bit(uint8_t * const buffer)
{
    *buffer = ADCR0H;
}

/* 1006 Nhu add */
/* End user code. Do not edit comment generated here */

