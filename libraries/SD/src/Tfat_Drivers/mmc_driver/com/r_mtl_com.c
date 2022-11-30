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
 Globals
 *----------------------------------------------------------------------------------------------*/
/*""VAL DEF""*/
uint32_t gMtlLogTbl[MTL_LOG_MAX];  /* Log buffer     */             /*   4*n bytes */ /* Due to MTL_LOG_MAX */
uint16_t gMtlLogIdx;               /* Log buffer index counter  */  /*   2 bytes   */
/*""VAL DEF END""*/

/*----------------------------------------------------------------------------------------------*
 Programs
 *----------------------------------------------------------------------------------------------*/

/************************************************************************************************
 * Debugging sub-modules
 ************************************************************************************************/

/******************************************************************************
* Declaration  : uint32_t R_mtl_Log2(uint32_t data)
* Function Name: R_mtl_Log2
* Description  : Usage of mtl_Log() macro is recommended. (mtl_Log(FLG, VAL, FID, LINE))
*              : This function can be used in any way but basically the following purpose is intended.
*              :
*              : Write this function where there is information to be saved.
*              : Write this function also at a location determined to cause an error.
*              : By internally setting breakpoints in this function at debugging,
*              : breakpoints do not have to be set at various locations.
*              : On exiting this function, execution returns to the calling function.
*              :
*              : Since the file ID and error occurrence line are saved when an error occurs,
*              : if an I/F for referencing the data is generated,
*              : information can be acquired without even using a debugger.
*              : Arbitrary debugging information can be saved in a uint32_t type variable.
*              : When not used, 0 should be set.
*              :
*              : 0xFF is used as the last mark.
*              :
*              : To generate a break under particular conditions based on the debugging information,
*              : create the conditions after the breakpoint processing,
* Argument     : uint32_t data     ; Debugging information
* Return Value : = 0               ; Successful operation
*              : = 1               ; Failed operation
******************************************************************************/
uint32_t R_mtl_Log2(uint32_t data)
{
    /* -------------------------------------------------|* LOG save processing     */
    if (gMtlLogIdx >= MTL_LOG_MAX)
    {
        /* The range is exceeded    */
        gMtlLogIdx = 0;
    }

    /* Save the debugging information  */
    gMtlLogTbl[gMtlLogIdx] = data;

    ++gMtlLogIdx;
    /* Maximum buffer value exceeded?  */
    if (gMtlLogIdx >= MTL_LOG_MAX)
    {
        gMtlLogIdx = 0;
    }

    /* Write the last mark     */
    gMtlLogTbl[gMtlLogIdx] = 0xFFFFFFFF;

    /* -------------------------------------------------|* Breakpoint processing    */
    if ((data & 0x80000000) == 0x80000000)
    {
        /* Breakpoint setting location   */
        return 1;
    }

    return 0;
}

/******************************************************************************
* Declaration  : void R_mtl_LogClear(void)
* Function Name: R_mtl_LogClear
* Description  : All logs are cleared.
* Argument     : None
* Return Value : None
******************************************************************************/
void R_mtl_LogClear(void)
{
    uint16_t    i;

    /* Clear the counter        */
    gMtlLogIdx = 0;

    /* Clear the log buffer     */
    for (i = 0 ; i < MTL_LOG_MAX ; ++i)
    {
        gMtlLogTbl[i] = 0;
    }
}

