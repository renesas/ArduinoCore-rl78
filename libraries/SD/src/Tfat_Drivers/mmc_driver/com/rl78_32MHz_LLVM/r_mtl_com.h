/*""FILE COMMENT""*******************************************************************
* File Name     : r_mtl_com.h
* Version       : 4.05R00B
* Device(s)     : RL78 Family MCUs
* Tool-Chain    : CubeSuite+
* H/W Platform  : -
* Description   : Common header file
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
#ifndef __MTL_COM_H__
#define __MTL_COM_H__

/*----------------------------------------------------------------------------------------------*/
/** SET **/
/** SET **/
/* In order to use definitions of MCU SFR area,                                            */ /** SET **/
/* include the header file of MCU SFR definition.                                          */ /** SET **/


/*----------------------------------------------------------------------------------------------*/
/** SET **/
/* When not using the loop timer, put the following 'include' as comments.                 */ /** SET **/
#define MTL_TIM_RL78__32MHz_noWait_LLVM

#include "r_mtl_tim.h"

/*----------------------------------------------------------------------------------------------*
 Definitions
 *----------------------------------------------------------------------------------------------*/
/** SET **/
/** SET **/
#define MTL_MCU_LITTLE          /* Little Endian                                           */ /** SET **/
/*----------------------------------------------------------------------------------------------*/
/** SET **/
/** SET **/
/** SET **/
/* Specify the type of user standard library.                                              */ /** SET **/
/* When using the compiler-bundled library for the following processes,                    */ /** SET **/
/* put the following 'define' as comments.                                                 */ /** SET **/
/* memcmp() / memmove() / memcpy() / memset() / strcat() / strcmp() / strcpy() / strlen()  */ /** SET **/
#define MTL_USER_LIB                                           /* use optimized library    */ /** SET **/

/*==============================================================================================*/
#include "r_stdint.h"
#include "r_mtl_com2.h"

#endif /* __MTL_COM_H__ */
