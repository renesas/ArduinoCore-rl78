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
#ifndef MTL_USER_LIB
#include <string.h>
#endif

/*----------------------------------------------------------------------------------------------*
 Programs
 *----------------------------------------------------------------------------------------------*/
/************************************************************************************************
 * Standard Functions
 ************************************************************************************************/

/******************************************************************************
* Declaration  : int32_t R_mtl_memcmp2(void *s1, void *s2, uint32_t n)
* Function Name: R_mtl_memcmp2
* Description  : Compares two memory areas for n bytes in byte units.
* Argument     : void           *s1  ; Pointer to first memory area to be compared
*              : void           *s2  ; Pointer to second memory area to be compared
*              : natural_uint_t n    ; Number of bytes to be compared
* Return Value : == 0                ; The two memory areas are equal
*              :  > 0                ; First memory area (s1) is larger
*              :  < 0                ; Second memory area (s2) is larger
******************************************************************************/
natural_int_t R_mtl_memcmp2(void *s1, void *s2, natural_uint_t n)
{
#ifdef MTL_USER_LIB /* ---------------------------------|* original processing is used   */
    char *ss1 = s1;
    char *ss2 = s2;

    while (n > 0)
    {
        if (*ss1 != *ss2)
        {
            return ((natural_int_t)*ss1 - (natural_int_t)*ss2);   /* The two memory areas are different */
        }
        ss1++;
        ss2++;
        n--;
    }

    return 0;           /* The two memory areas are equal  */

#else /* ---------------------------------------------|* Standard library is used    */
    return memcmp(s1, s2, (size_t)n);
#endif
}

/******************************************************************************
* Declaration  : void *R_mtl_memmove2(void *s1, void *s2, uint32_t n)
* Function Name: R_mtl_memmove2
* Description  : Data is moved from a area to other area which may overlap
* Argument     : void           *s1  ; Pointer to memory area to which data is moved
*              : void           *s2  ; Pointer to memory area from which data is moved
*              : natural_uint_t n    ; Number of bytes to be moved
* Return Value : None (Pointer to memory area to which data is moved.)
******************************************************************************/
void *R_mtl_memmove2(void *s1, void *s2, natural_uint_t n)
{
#ifdef MTL_USER_LIB /* ---------------------------------|* original processing is used   */
    char *pp1;
    char *pp2;

    pp1 = (char *)s1;
    pp2 = (char *)s2;
    if (pp2 >= pp1)   /* Data are copied from the top when left shift copy is performed. */
    {
        for (; n > 0 ; n--)
        {
            *pp1++ = *pp2++;
        }

    }
    else              /* Data are copied from the end when right shift copy is performed. */
    {
        pp1 += (n - 1);
        pp2 += (n - 1);
        for (; n > 0 ; n--)
        {
            *pp1-- = *pp2--;
        }
    }

    return s1;

#else /* ---------------------------------------------|* Standard library is used    */
    return memmove(s1, s2, (size_t)n);
#endif
}

/******************************************************************************
* Declaration  : void *R_mtl_memcpy2(void *s1, void *s2, uint32_t n)
* Function Name: R_mtl_memcpy2
* Description  : Copy of memory area (n bytes) (substitute standard function)
*              : Copies data for the number of bytes specified by "n" from the memory
*              : area indicated by "s2" to the memory area indicated by "s1".
* Argument     : void           *s1  ; Pointer to memory area to which data is moved
*              : void           *s2  ; Pointer to memory area from which data is moved
*              : natural_uint_t n    ; Number of bytes to be moved
* Return Value : None (Pointer to memory area to which data is moved.)
******************************************************************************/
void *R_mtl_memcpy2(void *s1, void *s2, natural_uint_t n)
{
#ifdef MTL_USER_LIB /* ---------------------------------|* original processing is used   */
    char *ss1 = s1;
    char *ss2 = s2;

    while (n > 0)
    {
        *ss1++ = *ss2++;
        n--;
    }

    return s1;                         /* Pointer to memory area to which data is copied */

#else /* ---------------------------------------------|* Standard library is used    */
    return memcpy(s1, s2, (size_t)n);
#endif
}

/******************************************************************************
* Declaration  : void *R_mtl_memcpy_w2(void *s1, void *s2, uint32_t n)
* Function Name: R_mtl_memcpy_w2
* Description  : Copy of memory area (n word) (substitute standard function)
*              : Copies data for the number of words specified by "n" from the memory
*              : area indicated by "s2" to the memory area indicated by "s1".
* Argument     : void           *s1  ; Pointer to memory area to which data is copied
*              : void           *s2  ; Pointer to memory area from which data is copied
*              : natural_uint_t n    ; Number of words to be copied
* Return Value : None(Pointer to memory area to which data is copied.)
******************************************************************************/
void *R_mtl_memcpy_w2(void *s1, void *s2, natural_uint_t n)
{
    int16_t *ss1 = s1;
    int16_t *ss2 = s2;

    while (n > 0)
    {
        *ss1++ = *ss2++;
        n--;
    }

    return s1;        /* Pointer to memory area to which data is copied */
}


/******************************************************************************
* Declaration  : void *R_mtl_memset2(void *s1, void *s2, uint32_t n)
* Function Name: R_mtl_memset2
* Description  : Memory area setting (substitute standard function)
*              : Sets the data specified by "c" for the number of bytes specified
*              : by "n" to the memory area indicated by "s".
* Argument     : void           *s   ; Pointer to memory area to which data is set
*              : natural_int_t  c    ; Data to be set
*              : natural_uint_t n    ; Number of bytes to be set
* Return Value : None (Pointer to memory area to which data is set)
******************************************************************************/
void *R_mtl_memset2(void *s, natural_int_t c, natural_uint_t n)
{
#ifdef MTL_USER_LIB /* ---------------------------------|* original processing is used   */
    char *ss = s;

    while (n > 0)
    {
        *ss++ = (char)c;
        n--;
    }

    return s;         /* Pointer to memory area to which data is set */

#else /* ---------------------------------------------|* Standard library is used    */
    return memset(s, c, (size_t)n);
#endif
}

