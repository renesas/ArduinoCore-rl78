;;/***********************************************************************************************************************
;;* DISCLAIMER
;;* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No 
;;* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
;;* applicable laws, including copyright laws. 
;;* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
;;* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
;;* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
;;* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
;;* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS 
;;* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
;;* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
;;* this software. By using this software, you agree to the additional terms and conditions found by accessing the 
;;* following link:
;;* http://www.renesas.com/disclaimer
;;*
;;* Copyright (C) 2021 Renesas Electronics Corporation. All rights reserved.
;;***********************************************************************************************************************/
;;/***********************************************************************************************************************
;;* File Name    : start.S
;;* Description  : 
;;***********************************************************************************************************************/
;;/***********************************************************************************************************************
;;* History : DD.MM.YYYY Version  Description
;;*         : 08.03.2021 1.00     First Release
;;*         : 23.06.2021 1.11     Renamed the following section
;;*                               - __mdata
;;*                               - __ebss
;;*                               - __bss
;;*                               - __edata
;;*         : 04.08.2021 1.12     Updated base file version 1.05 to 1.06
;;*                               Added processing for C++
;;*         : 25.11.2021 1.13     Deleted processing for C++
;;
;;***********************************************************************************************************************/

/************************************************************************/
/*    File Version: V1.06                                               */
/*    Date Generated: 09/06/2021                                        */
/************************************************************************/

    /*reset_program.asm*/

    .global _PowerON_Reset  /*! global Start routine */
    .short _PowerON_Reset
    
#ifdef CPPAPP    
___dso_handle:
    .global ___dso_handle
#endif


    .extern _bsp_init_system /*! external Sub-routine to initialise BSP*/
    .extern __data
    .extern __mdata
    .extern __ebss
    .extern __bss
    .extern __edata
    .extern _bsp_init_hardware /*! external Sub-routine to initialise Hardware*/
    .extern _main 
    .extern __stack
    .extern _exit
    .extern ___do_init
    .extern ___do_fini

    /*  ;; HL = start of list
        ;; DE = end of list
        ;; BC = step direction (+2 or -2)
    */
    
    .text

/* call to _PowerON_Reset */
_PowerON_Reset:
/* initialise user stack pointer */
    movw sp,#__stack /* Set stack pointer */

/* call the bsp initialiser */
    call    !!_bsp_init_system
    nop

/* load data section from ROM to RAM */    
;; block move to initialize .data

	mov	es, #0
	movw	bc, #__romdatacopysize
1:
	movw	ax, bc
	cmpw	ax, #0
	bz	$1f
	decw	bc
	decw	bc
	movw	ax, es:__romdatastart[bc]
	movw	__datastart[bc], ax
	br	$1b

1:
	mov	es, #0
	movw	bc, #__romdatafcopysize
1:
	movw	ax, bc
	cmpw	ax, #0
	bz	$1f
	decw	bc
	decw	bc
	movw	ax, es:__romdatafstart[bc]
	movw	__datafstart[bc], ax
	br	$1b

1:
	mov	es, #0
	movw	bc, #__romsdatacopysize
1:
	movw	ax, bc
	cmpw	ax, #0
	bz	$1f
	decw	bc
	decw	bc
	movw	ax, es:__romsdatastart[bc]
	movw	__sdatastart[bc], ax
	br	$1b

1:
	mov	es, #0
	movw	bc, #__romsaddrcopysize
1:
	movw	ax, bc
	cmpw	ax, #0
	bz	$1f
	decw	bc
	decw	bc
	movw	ax, es:__romsaddrstart[bc]
	movw	__saddrstart[bc], ax
	br	$1b
1:

;; block fill to .sbss
	movw    bc, #__sbsssize
	movw    ax, #0
	cmpw    ax, bc
	bz      $_sbss_zero_done
1:
	decw    bc
	decw    bc
	movw    __sbssstart[bc], ax
	cmpw    ax, bc
	bnz      $1b

_sbss_zero_done:

;; block fill to .bss

	movw    bc, #__bsssize
	movw    ax, #0
	cmpw    ax, bc
	bz      $_bss_zero_done
1:
	decw    bc
	decw    bc
	movw    __bssstart[bc], ax
	cmpw    ax, bc
	bnz      $1b

_bss_zero_done:
    

;; block fill to .bssf

	movw    bc, #__bssfsize
	movw    ax, #0
	cmpw    ax, bc
	bz      $_bssf_zero_done
1:
	decw    bc
	decw    bc
	movw    __bssfstart[bc], ax
	cmpw    ax, bc
	bnz      $1b

_bssf_zero_done:


/* call the hardware initialiser */
    call    !!_bsp_init_hardware
    nop

    call    !!__rl78_init

/* start user program */

	clrw	ax	/* argv */
	clrw	bc	/* argc */
	call	!!_main

/* call to exit*/
_exit:
     br    $_exit

.global	_rl78_run_preinit_array
.type	_rl78_run_preinit_array,@function
_rl78_run_preinit_array:
	movw	hl, #__preinit_array_start
	movw	de, #__preinit_array_end
	movw	bc, #-2
	br	$_rl78_run_inilist

	.global	_rl78_run_init_array
	.type	_rl78_run_init_array,@function
_rl78_run_init_array:
	movw	hl, #__init_array_start
	movw	de, #__init_array_end
	movw	bc, #2
	br	$_rl78_run_inilist

	.global	_rl78_run_fini_array
	.type	_rl78_run_fini_array,@function
_rl78_run_fini_array:
	movw	hl, #__fini_array_start
	movw	de, #__fini_array_end
	movw	bc, #-2
	/* fall through */

	;; HL = start of list
	;; DE = end of list
	;; BC = step direction (+2 or -2)
_rl78_run_inilist:
next_inilist:
	movw	ax, hl
	cmpw	ax, de
	bz	$done_inilist
	movw	ax, [hl]
	cmpw	ax, #-1
	bz	$skip_inilist
	cmpw	ax, #0
	bz	$skip_inilist
	push	ax
	push	bc
	push	de
	push	hl
	call	ax
	pop	hl
	pop	de
	pop	bc
	pop	ax
skip_inilist:
	movw	ax, hl
	addw	ax, bc
	movw	hl, ax
	br	$next_inilist
done_inilist:
	ret

    .section  .init,"ax"

    .global __rl78_init
__rl78_init:
	call	!!_rl78_run_preinit_array
	call	!!_rl78_run_init_array
	ret

    .section    .fini,"ax"

    .global __rl78_fini
.end

