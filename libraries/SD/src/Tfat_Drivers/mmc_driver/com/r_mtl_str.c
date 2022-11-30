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
* File Name     : r_mtl_str.c
* Version       : 4.05R00B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description   : Common file
*************************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 28.01.2003 1.00R01 First Release
*   : 02.12.2003 2.00R01
*   : 03.03.2004 2.00R02
*   : 02.12.2004 3.00R01
*   : 20.06.2006 3.10R01
*   : 15.09.2006 4.00R01
*   : 19.01.2007 4.01R00
*   : 06.02.2007 4.02R00
*   : 31.10.2007 4.03R00
*   : 22.06.2010 4.05R00
*    : 25.06.2010 4.05R00A
*    : 02.03.2012 4.05R00B
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
* Declaration  : char *R_mtl_strcat2(char *s1, char *s2)
* Function Name: R_mtl_strcat2
* Description  : Character string linkage (substitute standard function)
*              : Links the character string indicated by "s2" to the end of the character string indicated by "s1".
*              : The character string after linkage ends with NULL.
* Arguments    : char *s1 ; Pointer to character string to which linkage is performed
*              : char *s2 ; Pointer to character string which is to be linked
* Return Value : Pointer to character string after linkage
******************************************************************************/
char *R_mtl_strcat2(char *s1, char *s2)
{
#ifdef MTL_USER_LIB /* ---------------------------------|* Original processing is used   */
    char *ptr = s1;

    while (*s1 != 0)
    {
        s1++;                   /* Search for end of "s1"    */
    }
    while (*s2 != 0)
    {
        *s1++ = *s2++;          /* Link "s2" to "s1"     */
    }
    *s1 = *s2;                  /* Add NULL        */

    return ptr;                 /* Pointer to character string to which linkage is performed */

#else /* ---------------------------------------------|* Standard library is used    */
    return strcat(s1, s2);
#endif
}

/******************************************************************************
* Declaration  : int32_t R_mtl_strcmp2(char *s1, char *s2)
* Function Name: R_mtl_strcmp2
* Description  : Comparison of two character strings (substitute standard function)
*              : Compares two character strings which end with NULL in byte units.
* Arguments    : char   *s1  ; Pointer to first character string to be compared
*              : char   *s2  ; Pointer to second character string to be compared
* Return Value : == 0        ; The two character strings are equal
*              :  > 0        ; First character string (s1) is longer
*              :  < 0        ; Second character string (s2) is longer
******************************************************************************/
int32_t R_mtl_strcmp2(char *s1, char *s2)
{
#ifdef MTL_USER_LIB /* ---------------------------------|* Original processing is used   */
    for (; *s1 == *s2 ; s1++, s2++)
    {
        if (*s1 == '\0')
        {
            return 0;         /*The two character strings are equal */
        }
    }

    return ((natural_int_t)*s1 - (natural_int_t)*s2);      /*The two character strings are different*/

#else /* ---------------------------------------------|* Standard library is used    */
    return strcmp(s1, s2);
#endif
}

/******************************************************************************
* Declaration  : char *R_mtl_strcpy2(char *s1, char *s2)
* Function Name: R_mtl_strcpy2
* Description  : Copy of character string (substitute standard function)
*              : Copies the character string (ends with NULL) indicated by "s2" to the area indicated by "s1".
*              : The character string to which copy is performed ends with NULL.
* Arguments    : char   *s1  ; Pointer to character string to which copy is performed
*              : char   *s2  ; Pointer to character string which is copied
* Return Value : Pointer to character string to which copy is performed
******************************************************************************/
char *R_mtl_strcpy2(char *s1, char *s2)
{
#ifdef MTL_USER_LIB /* ---------------------------------|* Original processing is used   */
    char *ptr = s1;

    while (*s2 != 0)
    {
        *s1++ = *s2++;         /* Copy s2 to s1      */
    }
    *s1 = *s2;           /* Add Null        */

    return ptr;      /*Pointer to character string to which copy is performed */

#else /* ---------------------------------------------|* Standard library is used    */
    return strcpy(s1, s2);
#endif
}

/******************************************************************************
* Declaration  : uint16_t R_mtl_strlen2(char *s)
* Function Name: R_mtl_strlen2
* Description  : Acquisition of character string length (substitute standard function)
*              : Obtains the length of the character string (NULL included) indicated by "s".
* Arguments    : char   *s ; Pointer to character string whose length is to be obtained
* Return Value : Character string length
******************************************************************************/
uint16_t R_mtl_strlen2(char *s)
{
#ifdef MTL_USER_LIB /* ---------------------------------|* Original processing is used   */
    char *ptr = s;

    while (*s != 0)
    {
        s++;
    }

    return (uint16_t)((uint32_t)s - (uint32_t)ptr);  /* Character string length     */

#else /* ---------------------------------------------|* Standard library is used    */
    return ((uint16_t)strlen(s));
#endif
}

