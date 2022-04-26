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
*               : 25.06.2010 4.05R00
*               : 25.06.2010 4.05R00A
*               : 03.02.2012 4.05R00B
*""FILE COMMENT END""***************************************************************/
#include "r_mtl_com.h"

#if defined(__RX)
#pragma option optimize=2
#pragma option size
#pragma noinline R_mtl_wait_lp2
#endif
#if defined(__ICCRL78__)
#pragma optimize=low
#endif
/*----------------------------------------------------------------------------------------------*
 Programs
 *----------------------------------------------------------------------------------------------*/

/************************************************************************************************
 * Loop timer
 ************************************************************************************************/

/******************************************************************************
* Declaration  : void R_mtl_wait_lp2(natural_uint_t time)
* Function Name: R_mtl_wait_lp2
* Description  : loop timer processing
*              : Refer the r_mtl_com.h about timer value.
* Argument     : natural_uint_t  time   ; timer value
* Return Value : None
******************************************************************************/
void R_mtl_wait_lp2(natural_uint_t time)
{
    do
    {
        --time;
    }
    while (time != 0);
}

