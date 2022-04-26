/******************************************************************************

* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY
* DISCLAIMED.

* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

* Renesas reserves the right, without notice, to make changes to this
* software and to discontinue the availability of this software.
* By using this software, you agree to the additional terms and
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/

/*  Copyright (C) 2010(2012) Renesas Electronics Corporation All rights reserved.  */

/*""FILE COMMENT""*******************************************************************
* File Name     : r_mtl_com.c
* Version       : 4.05R00B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description   : Common file
*************************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 28.01.2003 1.00R01 First Release
*               : 02.12.2003 2.00R01
*               : 03.03.2004 2.00R02
*               : 02.12.2004 3.00R01
*               : 20.06.2006 3.10R01
*               : 15.09.2006 4.00R01
*               : 19.01.2007 4.01R00
*               : 06.02.2007 4.02R00
*               : 31.10.2007 4.03R00
*               : 22.06.2010 4.05R00
*               : 25.06.2010 4.05R00A
*               : 02.03.2012 4.05R00B
*""FILE COMMENT END""***************************************************************/
#include "r_mtl_com.h"

/*----------------------------------------------------------------------------------------------*
 Programs
 *----------------------------------------------------------------------------------------------*/

/************************************************************************************************
 * Routines whose processing differs according to MCU and C compiler specifications
 ************************************************************************************************/

/******************************************************************************
* Declaration  : uint16_t R_mtl_ShortPeek2(void *adr)
* Function Name: R_mtl_ShortPeek2
* Description  : Reading of uint16_t type value in little endian
*              : Routine whose processing differs according to MCU and C compiler specifications.
* Argument     : void *adr    ; Address to be read from
* Return Value : Read value (uint16_t)
******************************************************************************/
uint16_t R_mtl_ShortPeek2(void *adr)
{
    uint8_t  *ptr;
    uint16_t ret;

    ptr = adr;                                        /* Convert the address into the uint8_t pointer */
    ret = ptr[1];
    ret = (uint16_t)((uint16_t)(ret << 8) | ptr[0]);  /* Convert the address into the uint8_t pointer */
    return ret;
}

/******************************************************************************
* Declaration  : uint32_t R_mtl_LongPeek2(void *adr)
* Function Name: R_mtl_LongPeek2
* Description  : Reading of uint32_t type value in little endian
*              : Routine whose processing differs according to MCU and C compiler specifications.
* Argument     : void *adr    ; Address to be read from
* Return Value : Read value (uint32_t)
******************************************************************************/
uint32_t R_mtl_LongPeek2(void *adr)
{
    uint8_t  *ptr;
    uint32_t ret;

    ptr = adr;                                        /* Convert the address into the uint8_t pointer */
    ret =              ptr[3];
    ret = (ret << 8) | ptr[2];
    ret = (ret << 8) | ptr[1];
    ret = (ret << 8) | ptr[0];                        /* Read the value      */

    return ret;
}

/******************************************************************************
* Declaration  : void R_mtl_ShortPoke2(void *adr, uint16_t dat)
* Function Name: R_mtl_ShortPoke2
* Description  : Writing of uint16_t type value in little endian
*              : Routine whose processing differs according to MCU and C compiler specifications.
* Argument     : void      *adr   ; Address to be written to
*              : uint16_t  dat    ; Write data
* Return Value : None
******************************************************************************/
void R_mtl_ShortPoke2(void *adr, uint16_t dat)
{
    uint8_t *ptr;

    ptr = adr;                                                   /* Convert the address into the uint8_t pointer */
    ptr[0] = (uint8_t)(dat & (uint16_t)0x00FF);                  /* Write the lower byte   */
    ptr[1] = (uint8_t)((uint16_t)(dat & (uint16_t)0xFF00) >> 8); /* Write the upper byte   */
}

/******************************************************************************
* Declaration  : void R_mtl_LongPoke2(void *adr, uint32_t dat)
* Function Name: R_mtl_LongPoke2
* Description  : Writing of uint32_t type value in little endian
*              : Routine whose processing differs according to MCU and C compiler specifications.
* Argument     : void      *adr   ; Address to be written to
*              : uint32_t  dat    ; Write data
* Return Value : None
******************************************************************************/
void R_mtl_LongPoke2(void *adr, uint32_t dat)
{
    uint8_t *ptr;

    ptr = adr;                                       /* Convert the address into the uint8_t pointer */
    ptr[0] = (uint8_t)(dat & 0x000000FFUL);          /* LSB Write                                    */
    ptr[1] = (uint8_t)((dat & 0x0000FF00UL) >>  8);  /* Byte after LSB write                         */
    ptr[2] = (uint8_t)((dat & 0x00FF0000UL) >> 16);  /* Byte before MSB write                        */
    ptr[3] = (uint8_t)((dat & 0xFF000000UL) >> 24);  /* MSB write                                    */
}

