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
* File Name    : r_bsp_rl78_compiler.h
* Description  : 
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 08.03.2021 1.00     First Release
*         : 22.04.2021 1.10     Added "__far" to the address of the option byte.
*         : 04.08.2021 1.12     Added include guard.

***********************************************************************************************************************/

/*************************************************
 * Includes  <System Includes> , "Project Includes"
 *************************************************/

#ifndef R_RL78_COMPILER_H
#define R_RL78_COMPILER_H

/* Macro definition for option byte reference */
/* 000C0H or 040C0H
 * Setting of watchdog timer operation
 * - Enabling or disabling of counter operation
 * - Enabling or stopping of counter operation in the HALT or STOP mode
 * Setting of overflow time of watchdog timer
 * Setting of window open period of watchdog timer
 * Setting of interval interrupt of watchdog timer
 * - Interval interrupt is used or not used
 */
#if defined(__CCRL__)
#define OPTBYTE_C0    (*(volatile __far unsigned char *)0x000C0)
#elif defined(__ICCRL78__)
#define OPTBYTE_C0    (*(volatile __far unsigned char *)0x000C0)
#elif defined(__llvm__)
#define OPTBYTE_C0    (*(volatile __far unsigned char *)0x000C0)
#endif

/* 000C1H or 040C1H
 * Setting of LVD0 operation mode
 * - Reset mode
 * - Interrupt mode
 * - -LVD0 off(by controlling the externally input reset signal on the RESET pin)
 * Setting of LVD0 detection level(VLVD0)
 */
#if defined(__CCRL__)
#define OPTBYTE_C1    (*(volatile __far unsigned char *)0x000C1)
#elif defined(__ICCRL78__)
#define OPTBYTE_C1    (*(volatile __far unsigned char *)0x000C1)
#elif defined(__llvm__)
#define OPTBYTE_C1    (*(volatile __far unsigned char *)0x000C1)
#endif

/* 000C2H or 040C2H
 * Setting of flash operation mode
 *  Make the setting depending on the main system clock frequency(fMAIN)
 *  and power supply voltage(VDD) to be used.
 *  - LS(low-speed main) mode
 *  - HS(high-speed main) mode
 *  - LP(low-power main) mode
 * Setting of the frequency of the high-speed on-chip oscillator
 * - Select from 1 MHz to 32 MHz
 */
#if defined(__CCRL__)
#define OPTBYTE_C2    (*(volatile __far unsigned char *)0x000C2)
#elif defined(__ICCRL78__)
#define OPTBYTE_C2    (*(volatile __far unsigned char *)0x000C2)
#elif defined(__llvm__)
#define OPTBYTE_C2    (*(volatile __far unsigned char *)0x000C2)
#endif

/* 000C3H or 040C3H
 * Control of on-chip debug operation
 * - On-chip debug operation is disabled or enabled.
 * Handling of data of flash memory in case of failure in security ID codes for on-chip debug authentication
 * - Data of flash memory is erased or not erased in case of failure in 
 *   security ID codes for on-chip debug authentication
 */
#if defined(__CCRL__)
#define OPTBYTE_C3    (*(volatile __far unsigned char *)0x000C3)
#elif defined(__ICCRL78__)
#define OPTBYTE_C3    (*(volatile __far unsigned char *)0x000C3)
#elif defined(__llvm__)
#define OPTBYTE_C3    (*(volatile __far unsigned char *)0x000C3)
#endif

#if defined(__CCRL__)
#define BSP_FAR_FUNC               __far
#define BSP_NOP()                  __nop()    /* NOP instruction */
#define BSP_DISABLE_INTERRUPT()    __DI()
#define BSP_ENABLE_INTERRUPT()     __EI()
#elif defined(__ICCRL78__)
#define BSP_FAR_FUNC               __far_func
#define BSP_NOP()                  __no_operation()
#define BSP_DISABLE_INTERRUPT()    __disable_interrupt()
#define BSP_ENABLE_INTERRUPT()     __enable_interrupt()
#elif defined(__llvm__)
#define BSP_NOP()                  NOP()
#define BSP_DISABLE_INTERRUPT()    DI()
#define BSP_ENABLE_INTERRUPT()     EI()
#endif

/* Sections */
#if defined(__CCRL__)
#define R_BSP_SECTOP(name)         __sectop(#name)
#define R_BSP_SECEND(name)         __secend(#name)
#define R_BSP_SECSIZE(name)        __secsize(#name)
#elif defined(__ICCRL78__)
#elif defined(__llvm__)
#endif

/* ========== #pragma Directive ========== */
#if defined(__CCRL__)
#define R_BSP_PRAGMA(...)                                      _Pragma(#__VA_ARGS__)
#define __R_BSP_ATTRIB_SECTION_CHANGE_F(type, section_name)    R_BSP_PRAGMA(section type section_name)
#define _R_BSP_ATTRIB_SECTION_CHANGE_text(section_tag)         __R_BSP_ATTRIB_SECTION_CHANGE_F(text, ##section_tag)
#define _R_BSP_ATTRIB_SECTION_CHANGE_data(section_tag)         __R_BSP_ATTRIB_SECTION_CHANGE_F(data, ##section_tag)
#define R_BSP_ATTRIB_SECTION_CHANGE(type, section_tag)         _R_BSP_ATTRIB_SECTION_CHANGE_##type(section_tag)
#define R_BSP_ATTRIB_SECTION_CHANGE_END                        R_BSP_PRAGMA(section)
#elif defined(__ICCRL78__)
#define R_BSP_PRAGMA(...)                                      _Pragma(#__VA_ARGS__)
#elif defined(__llvm__)
#endif

/* ---------- Interrupt Function Creation ---------- */
#if defined(__CCRL__)
/* Standard */
#define R_BSP_PRAGMA_INTERRUPT(function_name, vector)           R_BSP_PRAGMA(interrupt function_name(vect=vector))\
                                                                extern void function_name(void);
#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vector)    R_BSP_PRAGMA(interrupt function_name(vect=vector))\
                                                                static void function_name(void);
#define R_BSP_ATTRIB_INTERRUPT                                  extern
#define R_BSP_ATTRIB_STATIC_INTERRUPT                           static

#elif defined(__ICCRL78__)
/* Standard */
#define R_BSP_PRAGMA_INTERRUPT(function_name, vect)             R_BSP_PRAGMA(vector=vect)\
                                                                extern __interrupt void function_name(void);
#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vect)      R_BSP_PRAGMA(vector=vect)\
                                                                static __interrupt void function_name(void);
#define R_BSP_ATTRIB_INTERRUPT                                  extern __interrupt
#define R_BSP_ATTRIB_STATIC_INTERRUPT                           static __interrupt

#elif defined(__llvm__)
#define R_BSP_PRAGMA_INTERRUPT(function_name, vector)           extern void function_name(void) __attribute__((interrupt(vect=vector), used));
#define R_BSP_PRAGMA_STATIC_INTERRUPT(function_name, vector)    static void function_name(void) __attribute__((interrupt(vect=vector), used));
#define R_BSP_ATTRIB_INTERRUPT                                  extern
#define R_BSP_ATTRIB_STATIC_INTERRUPT                           static
#endif

#endif /* R_RL78_COMPILER_H */

