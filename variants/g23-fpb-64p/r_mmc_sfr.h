/*""FILE COMMENT""*******************************************************************
* File Name     : r_mmc_sfr.h
* Version       : 1.00
* Device(s)     : RL78/G23
* compiler      : CC-RL
* H/W Platform  : R7F100Gxx
* Description   : MMC driver SFR common definitions
*************************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 04.06.2021 Ver1.00
*""FILE COMMENT END""***************************************************************/
#ifndef __MMC_SFR_H__
#define __MMC_SFR_H__
#include "r_mmc_user_config.h"
#include "r_cg_macrodriver.h"

/************************************************************************************************/
/* Definitions                                                                                  */
/************************************************************************************************/
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*                              Do not change the following data.                               */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#define _MMC_DRIVER_CPU_MODULE_NAME_ "RL78G23_CSI"

//#define CAT_2(a,b) a##b
//#define CAT(a,b) CAT_2(a,b)

/*----------------------------------------------------------------------------------------------*/
/*  Define the control port.                                                                    */
/*----------------------------------------------------------------------------------------------*/

#if (MMC_SAU_UNIT == 0)
#if (MMC_SAU_CHANNEL == 0)
#define MMC_CSI_UNIT            0
#define MMC_CSI_CHANNEL         0

#if (MMC_CSI_PIN == 'A')
#define MMC_DATAI_PORTNO        1  /* MMC DataIn Port No.  */
#define MMC_DATAI_BITNO         1  /* MMC DataIn Bit No.   */
#define MMC_CLK_PORTNO          1  /* MMC CLK Port No.     */
#define MMC_CLK_BITNO           0  /* MMC CLK Bit  No.     */
#define MMC_DATAO_PORTNO        1  /* MMC DataOut Port No. */
#define MMC_DATAO_BITNO         2  /* MMC DataOut Bit No.  */

/*----------- PMCEmn register value -----------*/
#define MMC_PMCE1_TBL       (uint8_t)0xF8
/* 11111000B */    /* PMCEmn setting         */
/* |||||||+-------- PMCE10   : Set to 0     */
/* ||||||+--------- PMCE11   : Set to 0     */
/* |||||+---------- PMCE12   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */

/*----------- PFOE1n register value -----------*/
#define MMC_PFOE1_TBL       (uint8_t)0x05
/* 00000101B */    /* PFOE1n setting         */
/* |||||||+-------- PFOE10 (P12) : Set to 0 */
/* ||||||+--------- Reserved : Set to 1     */
/* |||||+---------- PFOE12 (P10) : Set to 0 */
/* +++++----------- Reserved : Set to 1     */

#elif (MMC_CSI_PIN == 'B')
#define MMC_DATAI_PORTNO        1  /* MMC DataIn Port No.  */
#define MMC_DATAI_BITNO         6  /* MMC DataIn Bit No.   */
#define MMC_CLK_PORTNO          5  /* MMC CLK Port No.     */
#define MMC_CLK_BITNO           5  /* MMC CLK Bit  No.     */
#define MMC_DATAO_PORTNO        1  /* MMC DataOut Port No. */
#define MMC_DATAO_BITNO         7  /* MMC DataOut Bit No.  */

/*----------- PMCEmn register value -----------*/
#define MMC_PMCE1_TBL       (uint8_t)0x3F
/* 00111111B */    /* PMCEmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCE16   : Set to 0     */
/* +--------------- PMCE17   : Set to 0     */

/*----------- CCDE register value -----------*/
#define MMC_CCDE_TBL       (uint8_t)0xFC
/* 11111100B */    /* CCDE setting         */
/* |||||||+-------- CCDE00 (P16) : Set to 0 */
/* ||||||+--------- CCDE01 (P17) : Set to 0 */
/* ++++++---------- Reserved : Set to 1     */

/*----------- PFOE1n register value -----------*/
#define MMC_PFOE1_TBL       (uint8_t)0x05
/* 00000101B */    /* PFOE1n setting         */
/* |||||||+-------- PFOE10 (P17) : Set to 1 */
/* ||||||+--------- Reserved : Set to 0     */
/* |||||+---------- PFOE12 (P55) : Set to 1 */
/* +++++----------- Reserved : Set to 0     */

#endif /* MMC_CSI_PIN */

#define MMC_CSI_SIR_CLEAR       (uint8_t)0x03
/* 00000011B */    /* SIRms setting         */
/* |||||||+-------- OVCTmn   : Clear        */
/* ||||||+--------- PECTmn   : Clear        */
/* ++++++---------- Reserved : Set to 0     */

#define MMC_CLK_SO_BITNO        8
#define MMC_DATAO_SO_BITNO      0

#elif (MMC_SAU_CHANNEL == 1)
#define MMC_CSI_UNIT  0
#define MMC_CSI_CHANNEL  1

#define MMC_DATAI_PORTNO        7  /* MMC DataIn Port No.  */
#define MMC_DATAI_BITNO         4  /* MMC DataIn Bit No.   */
#define MMC_CLK_PORTNO          7  /* MMC CLK Port No.     */
#define MMC_CLK_BITNO           5  /* MMC CLK Bit  No.     */
#define MMC_DATAO_PORTNO        7  /* MMC DataOut Port No. */
#define MMC_DATAO_BITNO         3  /* MMC DataOut Bit No.  */

#define MMC_CSI_SIR_CLEAR       (uint8_t)0x07
/* 00000111B */    /* SIRms setting         */
/* |||||||+-------- OVCTmn   : Clear        */
/* ||||||+--------- PECTmn   : Clear        */
/* |||||+---------- FECTmn   : Clear        */
/* +++++----------- Reserved : Set to 0     */

/*----------- PMCTxx register value -----------*/
#define MMC_PMCT7_TBL       (uint8_t)0xC7
/* 11000111B */    /* PMCTmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCT73   : Set to 0     */
/* |||+------------ PMCT74   : Set to 0     */
/* ||+------------- PMCT75   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */

#define MMC_CLK_SO_BITNO        9
#define MMC_DATAO_SO_BITNO      1

#elif (MMC_SAU_CHANNEL == 2)
#define MMC_CSI_UNIT            1
#define MMC_CSI_CHANNEL         0

#define MMC_DATAI_PORTNO        0  /* MMC DataIn Port No.  */
#define MMC_DATAI_BITNO         3  /* MMC DataIn Bit No.   */
#define MMC_CLK_PORTNO          0  /* MMC CLK Port No.     */
#define MMC_CLK_BITNO           4  /* MMC CLK Bit  No.     */
#define MMC_DATAO_PORTNO        0  /* MMC DataOut Port No. */
#define MMC_DATAO_BITNO         2  /* MMC DataOut Bit No.  */

/*----------- PMCAxx register value -----------*/
#define MMC_PMCA0_TBL       (uint8_t)0xF3
/* 11110011B */    /* PMCAmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCA02   : Set to 0     */
/* ||||++---------- PMCA03   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */

/*----------- PMCTxx register value -----------*/
#define MMC_PMCT0_TBL       (uint8_t)0xF3
/* 11110011B */    /* PMCTmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCT02   : Set to 0     */
/* ||||++---------- PMCT03   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */

#define MMC_CSI_SIR_CLEAR       (uint8_t)0x03
/* 00000011B */    /* SIRms setting         */
/* |||||||+-------- OVCTmn   : Clear        */
/* ||||||+--------- PECTmn   : Clear        */
/* ++++++---------- Reserved : Set to 0     */

#define MMC_CLK_SO_BITNO        10
#define MMC_DATAO_SO_BITNO      2

#elif (MMC_SAU_CHANNEL == 3)
#define MMC_CSI_UNIT            1
#define MMC_CSI_CHANNEL         1

#define MMC_DATAI_PORTNO        5  /* MMC DataIn Port No.  */
#define MMC_DATAI_BITNO         0  /* MMC DataIn Bit No.   */
#define MMC_CLK_PORTNO          3  /* MMC CLK Port No.     */
#define MMC_CLK_BITNO           0  /* MMC CLK Bit  No.     */
#define MMC_DATAO_PORTNO        5  /* MMC DataOut Port No. */
#define MMC_DATAO_BITNO         1  /* MMC DataOut Bit No.  */

/*----------- PMCTxx register value -----------*/
#define MMC_PMCT3_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT30   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */

/*----------- PMCTxx register value -----------*/
#define MMC_PMCT5_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT50   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */

/*----------- PMCExx register value -----------*/
#define MMC_PMCE5_TBL       (uint8_t)0xFC
/* 11111100B */    /* PMCEmn setting         */
/* |||||||+-------- PMCE50   : Set to 0     */
/* ||||||+--------- PMCE51   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */

/*----------- CCDE register value -----------*/
#define MMC_CCDE_TBL       (uint8_t)0xF3
/* 11110011B */    /* CCDE setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- CCDE02 (P51) : Set to 0 */
/* ||||+----------- CCDE03 (P50) : Set to 0 */
/* ++++------------ Reserved : Set to 1     */

#define MMC_CSI_SIR_CLEAR       (uint8_t)0x07
/* 00000111B */    /* SIRms setting         */
/* |||||||+-------- OVCTmn   : Clear        */
/* ||||||+--------- PECTmn   : Clear        */
/* |||||+---------- FECTmn   : Clear        */
/* +++++----------- Reserved : Set to 0     */

#define MMC_CLK_SO_BITNO        11
#define MMC_DATAO_SO_BITNO      3

#endif  /* #if (MMC_SAU_CHANNEL == x) */

#elif (MMC_SAU_UNIT == 1)
#if (MMC_SAU_CHANNEL == 0)
#define MMC_CSI_UNIT            2
#define MMC_CSI_CHANNEL         0

#define MMC_DATAI_PORTNO        1  /* MMC DataIn Port No.  */
#define MMC_DATAI_BITNO         4  /* MMC DataIn Bit No.   */
#define MMC_CLK_PORTNO          1  /* MMC CLK Port No.     */
#define MMC_CLK_BITNO           5  /* MMC CLK Bit  No.     */
#define MMC_DATAO_PORTNO        1  /* MMC DataOut Port No. */
#define MMC_DATAO_BITNO         3  /* MMC DataOut Bit No.  */

#define MMC_CSI_SIR_CLEAR       (uint8_t)0x03
/* 00000011B */    /* SIRms setting         */
/* |||||||+-------- OVCTmn   : Clear        */
/* ||||||+--------- PECTmn   : Clear        */
/* ++++++---------- Reserved : Set to 0     */

/*----------- PMCAmn register value -----------*/
#define MMC_PMCA1_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCAmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCA13   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */

/*----------- PMCExx register value -----------*/
#define MMC_PMCE1_TBL       (uint8_t)0xC7
/* 11000111B */    /* PMCEmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCE13   : Set to 0     */
/* |||+------------ PMCE14   : Set to 0     */
/* ||+------------- PMCE15   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */

#define MMC_CLK_SO_BITNO        8
#define MMC_DATAO_SO_BITNO      0

#elif (MMC_SAU_CHANNEL == 1)
#define MMC_CSI_UNIT            2
#define MMC_CSI_CHANNEL         1

#define MMC_DATAI_PORTNO        7  /* MMC DataIn Port No.  */
#define MMC_DATAI_BITNO         1  /* MMC DataIn Bit No.   */
#define MMC_CLK_PORTNO          7  /* MMC CLK Port No.     */
#define MMC_CLK_BITNO           0  /* MMC CLK Bit  No.     */
#define MMC_DATAO_PORTNO        7  /* MMC DataOut Port No. */
#define MMC_DATAO_BITNO         2  /* MMC DataOut Bit No.  */

#define MMC_CSI_SIR_CLEAR       (uint8_t)0x07
/* 00000111B */    /* SIRms setting         */
/* |||||||+-------- OVCTmn   : Clear        */
/* ||||||+--------- PECTmn   : Clear        */
/* |||||+---------- FECTmn   : Clear        */
/* +++++----------- Reserved : Set to 0     */

/*----------- PMCTxx register value -----------*/
#define MMC_PMCT7_TBL       (uint8_t)0xF8
/* 11111000B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT70   : Set to 0     */
/* ||||||+--------- PMCT71   : Set to 0     */
/* |||||+---------- PMCT72   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */

#define MMC_CLK_SO_BITNO        9
#define MMC_DATAO_SO_BITNO      1


#endif /* MMC_SAU_CHANNEL */
#endif /* MMC_SAU_UNIT */

/*----------- PMCAxx register value -----------*/
#ifndef MMC_PMCA0_TBL
#define MMC_PMCA0_TBL       (uint8_t)0xFF
#endif /* MMC_PMCA0_TBL */

#ifndef MMC_PMCA1_TBL
#define MMC_PMCA1_TBL       (uint8_t)0xFF
#endif /* MMC_PMCA1_TBL */

#define MMC_PMCA2_TBL       (uint8_t)0xFF
#define MMC_PMCA12_TBL      (uint8_t)0xFF
#define MMC_PMCA14_TBL      (uint8_t)0xFF

/*----------- PMCTxx register value -----------*/
#ifndef MMC_PMCT0_TBL
#define MMC_PMCT0_TBL       (uint8_t)0xFF
#endif /* MMC_PMCT0_TBL */
#ifndef MMC_PMCT3_TBL
#define MMC_PMCT3_TBL       (uint8_t)0xFF
#endif /* MMC_PMCT3_TBL */
#ifndef MMC_PMCT5_TBL
#define MMC_PMCT5_TBL       (uint8_t)0xFF
#endif /* MMC_PMCT5_TBL */
#ifndef MMC_PMCT7_TBL
#define MMC_PMCT7_TBL       (uint8_t)0xFF
#endif /* MMC_PMCT7_TBL */
#define MMC_PMCT2_TBL       (uint8_t)0xFF
#define MMC_PMCT6_TBL       (uint8_t)0xFF

/*----------- PMCExx register value -----------*/
#ifndef MMC_PMCE1_TBL
#define MMC_PMCE1_TBL       (uint8_t)0xFF
#endif /* MMC_PMCE1_TBL */
#ifndef MMC_PMCE5_TBL
#define MMC_PMCE5_TBL       (uint8_t)0xFF
#endif /* MMC_PMCE5_TBL */
#define MMC_PMCE0_TBL       (uint8_t)0xFF
#define MMC_PMCE6_TBL       (uint8_t)0xFF

/*----------- CCDE register value -----------*/
#ifndef MMC_CCDE_TBL
#define MMC_CCDE_TBL       (uint8_t)0xFF
#endif /* MMC_CCDE_TBL */

/*----------- PFOE1 register value -----------*/
#ifndef MMC_PFOE1_TBL
#define MMC_PFOE1_TBL       (uint8_t)0x00
#endif /* MMC_PFOE1_TBL */

/*----------- ISC register value -----------*/
#if (MMC_CSI_UNIT == 0)
#if (MMC_CSI_CHANNEL == 0)
#define MMC_ISC_TBL       (uint8_t)0xE3
/* 11100011B */    /* ISC setting         */
/* ||||||++-------- Reserved : Set to 1   */
/* |||||+---------- ISC2     : Set to 0   */
/* ||||+----------- ISC3     : Set to 0   */
/* |||+------------ ISC4     : Set to 0   */
/* +++------------- Reserved : Set to 1   */
#elif (MMC_CSI_CHANNEL == 1)
#define MMC_ISC_TBL       (uint8_t)0x1F
/* 00011111B */    /* ISC setting         */
/* |||+++++-------- Reserved : Set to 1   */
/* ||+------------- ISC2     : Set to 0   */
/* |+-------------- ISC3     : Set to 0   */
/* +--------------- ISC4     : Set to 0   */
#endif /* MMC_CSI_CHANNEL */
#else
#define MMC_ISC_TBL       (uint8_t)0xFF
#endif /* MMC_CSI_UNIT */

/*----------- PMCAxx (CS0) register value -----------*/
#if (MMC_CS0_PORTNO == 0)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCA0_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCAmn setting         */
/* |||||||+-------- PMCA00   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCA0_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCAmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCA01   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 2)
#define MMC_CS0_PMCA0_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCAmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCA02   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 3)
#define MMC_CS0_PMCA0_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCAmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCA03   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 1)
#if (MMC_CS0_BITNO == 3)
#define MMC_CS0_PMCA1_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCAmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCA13   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 2)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCA2_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCAmn setting         */
/* |||||||+-------- PMCA00   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCA2_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCAmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCA21   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 2)
#define MMC_CS0_PMCA2_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCAmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCA22   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 3)
#define MMC_CS0_PMCA2_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCAmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCA23   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 4)
#define MMC_CS0_PMCA2_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCAmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCA24   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 5)
#define MMC_CS0_PMCA2_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCAmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCA25   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 6)
#define MMC_CS0_PMCA2_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCAmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCA26   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 7)
#define MMC_CS0_PMCA2_TBL       (uint8_t)0x7F
/* 01111111B */    /* PMCAmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCA27   : Set to 0     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 12)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCA12_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCAmn setting         */
/* |||||||+-------- PMCA120  : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 14)
#if (MMC_CS0_BITNO == 7)
#define MMC_CS0_PMCA14_TBL       (uint8_t)0x7F
/* 01111111B */    /* PMCAmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCA147  : Set to 0     */
#endif /* MMC_CS0_BITNO */
#endif /* MMC_CS0_PORTNO */

#ifndef MMC_CS0_PMCA0_TBL
#define MMC_CS0_PMCA0_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCA0_TBL */
#ifndef MMC_CS0_PMCA1_TBL
#define MMC_CS0_PMCA1_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCA1_TBL */
#ifndef MMC_CS0_PMCA2_TBL
#define MMC_CS0_PMCA2_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCA2_TBL */
#ifndef MMC_CS0_PMCA12_TBL
#define MMC_CS0_PMCA12_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCA12_TBL */
#ifndef MMC_CS0_PMCA14_TBL
#define MMC_CS0_PMCA14_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCA14_TBL */

/*----------- PMCTxx (CS0) register value -----------*/
#if (MMC_CS0_PORTNO == 0)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCT0_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT00   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCT0_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCTmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCT01   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 2)
#define MMC_CS0_PMCT0_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCTmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCT02   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 3)
#define MMC_CS0_PMCT0_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCTmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCT03   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 5)
#define MMC_CS0_PMCT0_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCTmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCT05   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 6)
#define MMC_CS0_PMCT0_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCTmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCT06   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 2)
#if (MMC_CS0_BITNO == 2)
#define MMC_CS0_PMCT2_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCTmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCT22   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 3)
#define MMC_CS0_PMCT2_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCTmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCT23   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 4)
#define MMC_CS0_PMCT2_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCTmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCT24   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 5)
#define MMC_CS0_PMCT2_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCTmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCT25   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 6)
#define MMC_CS0_PMCT2_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCTmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCT26   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 7)
#define MMC_CS0_PMCT2_TBL       (uint8_t)0x7F
/* 01111111B */    /* PMCTmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCT27   : Set to 0     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 3)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCT3_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT30   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCT3_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCTmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCT31   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 5)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCT5_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT50   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 6)
#if (MMC_CS0_BITNO == 4)
#define MMC_CS0_PMCT6_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCTmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCT64   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 5)
#define MMC_CS0_PMCT6_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCTmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCT65   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 6)
#define MMC_CS0_PMCT6_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCTmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCT66   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 7)
#define MMC_CS0_PMCT6_TBL       (uint8_t)0x7F
/* 01111111B */    /* PMCTmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCT67   : Set to 0     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 7)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCT7_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT70   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCT7_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCTmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCT71   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 2)
#define MMC_CS0_PMCT7_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCTmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCT72   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 3)
#define MMC_CS0_PMCT7_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCTmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCT73   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 4)
#define MMC_CS0_PMCT7_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCTmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCT74   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 5)
#define MMC_CS0_PMCT7_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCTmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCT75   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 6)
#define MMC_CS0_PMCT7_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCTmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCT76   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 7)
#define MMC_CS0_PMCT7_TBL       (uint8_t)0x7F
/* 01111111B */    /* PMCTmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCT77   : Set to 0     */
#endif /* MMC_CS0_BITNO */
#endif /* MMC_CS0_PORTNO */

#ifndef MMC_CS0_PMCT0_TBL
#define MMC_CS0_PMCT0_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCT0_TBL */
#ifndef MMC_CS0_PMCT2_TBL
#define MMC_CS0_PMCT2_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCT2_TBL */
#ifndef MMC_CS0_PMCT3_TBL
#define MMC_CS0_PMCT3_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCT3_TBL */
#ifndef MMC_CS0_PMCT5_TBL
#define MMC_CS0_PMCT5_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCT5_TBL */
#ifndef MMC_CS0_PMCT6_TBL
#define MMC_CS0_PMCT6_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCT6_TBL */
#ifndef MMC_CS0_PMCT7_TBL
#define MMC_CS0_PMCT7_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCT7_TBL */

/*----------- PMCExx (CS0) register value -----------*/
#if (MMC_CS0_PORTNO == 0)
#if (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCE0_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCEmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCE01   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 1)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCE1_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCEmn setting         */
/* |||||||+-------- PMCE10   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCE1_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCEmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCE11   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 2)
#define MMC_CS0_PMCE1_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCEmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCE12   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 3)
#define MMC_CS0_PMCE1_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCEmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCE13   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 4)
#define MMC_CS0_PMCE1_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCEmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCE14   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 5)
#define MMC_CS0_PMCE1_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCEmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCE15   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 6)
#define MMC_CS0_PMCE1_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCEmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCE16   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 7)
#define MMC_CS0_PMCE1_TBL       (uint8_t)0x7F
/* 01111111B */    /* PMCEmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCE17   : Set to 0     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 5)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCE5_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCEmn setting         */
/* |||||||+-------- PMCE50   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCE5_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCEmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCE51   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */

#elif (MMC_CS0_PORTNO == 6)
#if (MMC_CS0_BITNO == 0)
#define MMC_CS0_PMCE6_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCEmn setting         */
/* |||||||+-------- PMCE60   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 1)
#define MMC_CS0_PMCE6_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCEmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCE61   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */
#endif /* MMC_CS0_PORTNO */

#ifndef MMC_CS0_PMCE0_TBL
#define MMC_CS0_PMCE0_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCE0_TBL */
#ifndef MMC_CS0_PMCE1_TBL
#define MMC_CS0_PMCE1_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCE1_TBL */
#ifndef MMC_CS0_PMCE5_TBL
#define MMC_CS0_PMCE5_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCE5_TBL */
#ifndef MMC_CS0_PMCE6_TBL
#define MMC_CS0_PMCE6_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_PMCE6_TBL */

/*----------- CCDE (CS0) register value -----------*/
#if (MMC_CS0_PORTNO == 1)
#if (MMC_CS0_BITNO == 6)
#define MMC_CS0_CCDE_TBL       (uint8_t)0xFE
/* 11111110B */    /* CCDE setting         */
/* |||||||+-------- CCDE00 (P16) : Set to 0 */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_CS0_BITNO == 7)
#define MMC_CS0_CCDE_TBL       (uint8_t)0xFD
/* 11111101B */    /* CCDE setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- CCDE01 (P17) : Set to 0 */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_CS0_BITNO */
#endif /* MMC_CS0_PORTNO */

#ifndef MMC_CS0_CCDE_TBL
#define MMC_CS0_CCDE_TBL       (uint8_t)0xFF
#endif /* MMC_CS0_CCDE_TBL */


/*----------- PMCAxx (DETECT0) register value -----------*/
#if (MMC_DETECT0_PORTNO == 0)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCA0_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCAmn setting         */
/* |||||||+-------- PMCA00   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCA0_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCAmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCA01   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 2)
#define MMC_DETECT0_PMCA0_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCAmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCA02   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 3)
#define MMC_DETECT0_PMCA0_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCAmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCA03   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 1)
#if (MMC_DETECT0_BITNO == 3)
#define MMC_DETECT0_PMCA1_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCAmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCA13   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 2)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCAmn setting         */
/* |||||||+-------- PMCA00   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCAmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCA21   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 2)
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCAmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCA22   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 3)
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCAmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCA23   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 4)
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCAmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCA24   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 5)
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCAmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCA25   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 6)
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCAmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCA26   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 7)
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0x7F
/* 10111111B */    /* PMCAmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCA27   : Set to 0     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 12)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCA12_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCAmn setting         */
/* |||||||+-------- PMCA120  : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 14)
#if (MMC_DETECT0_BITNO == 7)
#define MMC_DETECT0_PMCA14_TBL       (uint8_t)0x7F
/* 01111111B */    /* PMCAmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCA147  : Set to 0     */
#endif /* MMC_DETECT0_BITNO */
#endif /* MMC_DETECT0_PORTNO */

#ifndef MMC_DETECT0_PMCA0_TBL
#define MMC_DETECT0_PMCA0_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCA0_TBL */
#ifndef MMC_DETECT0_PMCA1_TBL
#define MMC_DETECT0_PMCA1_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCA1_TBL */
#ifndef MMC_DETECT0_PMCA2_TBL
#define MMC_DETECT0_PMCA2_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCA2_TBL */
#ifndef MMC_DETECT0_PMCA12_TBL
#define MMC_DETECT0_PMCA12_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCA12_TBL */
#ifndef MMC_DETECT0_PMCA14_TBL
#define MMC_DETECT0_PMCA14_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCA14_TBL */

/*----------- PMCTxx (DETECT0) register value -----------*/
#if (MMC_DETECT0_PORTNO == 0)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCT0_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT00   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCT0_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCTmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCT01   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 2)
#define MMC_DETECT0_PMCT0_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCTmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCT02   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 3)
#define MMC_DETECT0_PMCT0_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCTmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCT03   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 5)
#define MMC_DETECT0_PMCT0_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCTmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCT05   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 6)
#define MMC_DETECT0_PMCT0_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCTmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCT06   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 2)
#if (MMC_DETECT0_BITNO == 2)
#define MMC_DETECT0_PMCT2_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCTmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCT22   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 3)
#define MMC_DETECT0_PMCT2_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCTmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCT23   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 4)
#define MMC_DETECT0_PMCT2_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCTmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCT24   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 5)
#define MMC_DETECT0_PMCT2_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCTmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCT25   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 6)
#define MMC_DETECT0_PMCT2_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCTmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCT26   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 7)
#define MMC_DETECT0_PMCT2_TBL       (uint8_t)0x7F
/* 10111111B */    /* PMCTmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCT27   : Set to 0     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 3)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCT3_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT30   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCT3_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCTmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCT31   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 5)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCT5_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT50   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 6)
#if (MMC_DETECT0_BITNO == 4)
#define MMC_DETECT0_PMCT6_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCTmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCT64   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 5)
#define MMC_DETECT0_PMCT6_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCTmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCT65   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 6)
#define MMC_DETECT0_PMCT6_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCTmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCT66   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 7)
#define MMC_DETECT0_PMCT6_TBL       (uint8_t)0x7F
/* 10111111B */    /* PMCTmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCT67   : Set to 0     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 7)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCTmn setting         */
/* |||||||+-------- PMCT70   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCTmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCT71   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 2)
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCTmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCT72   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 3)
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCTmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCT73   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 4)
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCTmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCT74   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 5)
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCTmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCT75   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 6)
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCTmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCT76   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 7)
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0x7F
/* 10111111B */    /* PMCTmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCT77   : Set to 0     */
#endif /* MMC_DETECT0_BITNO */
#endif /* MMC_DETECT0_PORTNO */

#ifndef MMC_DETECT0_PMCT0_TBL
#define MMC_DETECT0_PMCT0_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCT0_TBL */
#ifndef MMC_DETECT0_PMCT2_TBL
#define MMC_DETECT0_PMCT2_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCT2_TBL */
#ifndef MMC_DETECT0_PMCT3_TBL
#define MMC_DETECT0_PMCT3_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCT3_TBL */
#ifndef MMC_DETECT0_PMCT5_TBL
#define MMC_DETECT0_PMCT5_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCT5_TBL */
#ifndef MMC_DETECT0_PMCT6_TBL
#define MMC_DETECT0_PMCT6_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCT6_TBL */
#ifndef MMC_DETECT0_PMCT7_TBL
#define MMC_DETECT0_PMCT7_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCT7_TBL */

/*----------- PMCExx (DETECT0) register value -----------*/
#if (MMC_DETECT0_PORTNO == 0)
#if (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCE0_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCEmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCE01   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 1)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCEmn setting         */
/* |||||||+-------- PMCE10   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCEmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCE11   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 2)
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0xFB
/* 11111011B */    /* PMCEmn setting         */
/* ||||||++-------- Reserved : Set to 1     */
/* |||||+---------- PMCE12   : Set to 0     */
/* +++++----------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 3)
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0xF7
/* 11110111B */    /* PMCEmn setting         */
/* |||||+++-------- Reserved : Set to 1     */
/* ||||+----------- PMCE13   : Set to 0     */
/* ++++------------ Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 4)
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0xEF
/* 11101111B */    /* PMCEmn setting         */
/* ||||++++-------- Reserved : Set to 1     */
/* |||+------------ PMCE14   : Set to 0     */
/* +++------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 5)
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0xDF
/* 11011111B */    /* PMCEmn setting         */
/* |||+++++-------- Reserved : Set to 1     */
/* ||+------------- PMCE15   : Set to 0     */
/* ++-------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 6)
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0xBF
/* 10111111B */    /* PMCEmn setting         */
/* ||++++++-------- Reserved : Set to 1     */
/* |+-------------- PMCE16   : Set to 0     */
/* +--------------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 7)
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0x7F
/* 01111111B */    /* PMCEmn setting         */
/* |+++++++-------- Reserved : Set to 1     */
/* +--------------- PMCE17   : Set to 0     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 5)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCE5_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCEmn setting         */
/* |||||||+-------- PMCE50   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCE5_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCEmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCE51   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */

#elif (MMC_DETECT0_PORTNO == 6)
#if (MMC_DETECT0_BITNO == 0)
#define MMC_DETECT0_PMCE6_TBL       (uint8_t)0xFE
/* 11111110B */    /* PMCEmn setting         */
/* |||||||+-------- PMCE60   : Set to 0     */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 1)
#define MMC_DETECT0_PMCE6_TBL       (uint8_t)0xFD
/* 11111101B */    /* PMCEmn setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- PMCE61   : Set to 0     */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */
#endif /* MMC_DETECT0_PORTNO */

#ifndef MMC_DETECT0_PMCE0_TBL
#define MMC_DETECT0_PMCE0_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCE0_TBL */
#ifndef MMC_DETECT0_PMCE1_TBL
#define MMC_DETECT0_PMCE1_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCE1_TBL */
#ifndef MMC_DETECT0_PMCE5_TBL
#define MMC_DETECT0_PMCE5_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCE5_TBL */
#ifndef MMC_DETECT0_PMCE6_TBL
#define MMC_DETECT0_PMCE6_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_PMCE6_TBL */

/*----------- CCDE (DETECT0) register value -----------*/
#if (MMC_DETECT0_PORTNO == 1)
#if (MMC_DETECT0_BITNO == 6)
#define MMC_DETECT0_CCDE_TBL       (uint8_t)0xFE
/* 11111110B */    /* CCDE setting         */
/* |||||||+-------- CCDE00 (P16) : Set to 0 */
/* +++++++--------- Reserved : Set to 1     */
#elif (MMC_DETECT0_BITNO == 7)
#define MMC_DETECT0_CCDE_TBL       (uint8_t)0xFD
/* 11111101B */    /* CCDE setting         */
/* |||||||+-------- Reserved : Set to 1     */
/* ||||||+--------- CCDE01 (P17) : Set to 0 */
/* ++++++---------- Reserved : Set to 1     */
#endif /* MMC_DETECT0_BITNO */
#endif /* MMC_DETECT0_PORTNO */

#ifndef MMC_DETECT0_CCDE_TBL
#define MMC_DETECT0_CCDE_TBL       (uint8_t)0xFF
#endif /* MMC_DETECT0_CCDE_TBL */



#define __PM( x,y )              PM ## x ##_bit.no ## y
#define  _PM( x,y )             __PM( x , y )
#define __POM( x,y )            POM ## x ##_bit.no ## y
#define  _POM( x,y )            __POM( x , y )
#define __PIM( x,y )            PIM ## x ##_bit.no ## y
#define  _PIM( x,y )            __PIM( x , y )
#define __P( x,y )              P ## x ##_bit.no ## y
#define  _P( x,y )              __P( x , y )
#define __PMC( x,y )            PMC ## x ##_bit.no ## y
#define  _PMC( x,y )            __PMC( x , y )

#define __SPS( x )              SPS ## x
#define  _SPS( x )              __SPS( x )
#define __SPSL( x )             SPS ## x ## L
#define  _SPSL( x )             __SPSL( x )

#define __SMR( x,y )            SMR ## x ## y
#define  _SMR( x,y )            __SMR( x , y )

#define __SCR( x,y )            SCR ## x ## y
#define  _SCR( x,y )            __SCR( x , y )

#define __SDR( x,y )            SDR ## x ## y
#define  _SDR( x,y )            __SDR( x , y )
#define __SIO( x,y )            SIO ## x ## y
#define  _SIO( x,y )            __SIO( x , y )

#define __SIR( x,y )            SIR ## x ## y
#define  _SIR( x,y )            __SIR( x , y )
#define __SIRL( x,y )           SIR ## x ## y ## L
#define  _SIRL( x,y )           __SIRL( x , y )

#define __SSR( x,y )            SSR ## x ## y
#define  _SSR( x,y )            __SSR( x , y )
#define __SSRL( x,y )           SSR ## x ## y ## L
#define  _SSRL( x,y )           __SSRL( x , y )

#define __SS( x )               SS ## x
#define  _SS( x )               __SS( x )
#define __SSL( x )              SS ## x ## L
#define  _SSL( x )              __SSL( x )
#define __SSLB( x,y )           SS ## x ## L_bit.no ## y
#define  _SSLB( x,y )           __SSLB( x,y )

#define __ST( x )               ST ## x
#define  _ST( x )               __ST( x )
#define __STL( x )              ST ## x ## L
#define  _STL( x )              __STL( x )
#define __STLB( x,y )           ST ## x ## L_bit.no ## y
#define  _STLB( x,y )           __STLB( x,y )

#define __SE( x )               SE ## x
#define  _SE( x )               __SE( x )
#define __SEL( x )              SE ## x ## L
#define  _SEL( x )              __SEL( x )
#define __SELB( x,y )           SE ## x ## L_bit.no ## y
#define  _SELB( x,y )           __SELB( x,y )

#define __SOE( x )              SOE ## x
#define  _SOE( x )              __SOE( x )
#define __SOEL( x )             SOE ## x ## L
#define  _SOEL( x )             __SOEL( x )
#define __SOELB( x,y )          SOE ## x ## L_bit.no ## y
#define  _SOELB( x,y )          __SOELB( x,y )

#define __SO( x )               SO ## x
#define  _SO( x )               __SO( x )

#define __CSIIF( x,y )          CSIIF ## x ## y
#define  _CSIIF( x,y )          __CSIIF( x , y )
#define __CSIMK( x,y )          CSIMK ## x ## y
#define  _CSIMK( x,y )          __CSIMK( x , y )
#define __SAUEN( x )            SAU ## x ## EN
#define  _SAUEN( x )            __SAUEN( x )
#define __SAURES( x )           SAU ## x ## RES
#define  _SAURES( x )           __SAURES( x )

#define MMC_PM_DATAI             _PM( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )     /* MMC DataIn */
#define MMC_PORT_DATAI            _P( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )     /* MMC DataIn */
#define MMC_PIM_DATAI           _PIM( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )     /* MMC DataIn */
#define MMC_POM_DATAI           _POM( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )     /* MMC DataIn */
#define MMC_PMC_DATAI           _PMC( MMC_DATAI_PORTNO , MMC_DATAI_BITNO )     /* MMC DataIn */
#define MMC_PM_CLK               _PM( MMC_CLK_PORTNO , MMC_CLK_BITNO )         /* MMC CLK  */
#define MMC_PORT_CLK              _P( MMC_CLK_PORTNO , MMC_CLK_BITNO )         /* MMC CLK  */
#define MMC_PIM_CLK             _PIM( MMC_CLK_PORTNO , MMC_CLK_BITNO )         /* MMC CLK  */
#define MMC_POM_CLK             _POM( MMC_CLK_PORTNO , MMC_CLK_BITNO )         /* MMC CLK  */
#define MMC_PMC_CLK             _PMC( MMC_CLK_PORTNO , MMC_CLK_BITNO )         /* MMC CLK  */
#define MMC_PM_DATAO             _PM( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )     /* MMC DataOut */
#define MMC_PORT_DATAO            _P( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )     /* MMC DataOut */
#define MMC_PIM_DATAO           _PIM( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )     /* MMC DataOut */
#define MMC_POM_DATAO           _POM( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )     /* MMC DataOut */
#define MMC_PMC_DATAO           _PMC( MMC_DATAO_PORTNO , MMC_DATAO_BITNO )     /* MMC DataOut */

#define MMC_PM_CS0               _PM( MMC_CS0_PORTNO , MMC_CS0_BITNO )         /* MMC CS0 (Negative-true logic) */
#define MMC_PORT_CS0              _P( MMC_CS0_PORTNO , MMC_CS0_BITNO )         /* MMC CS0 (Negative-true logic) */
#define MMC_PIM_CS0             _PIM( MMC_CS0_PORTNO , MMC_CS0_BITNO )         /* MMC CS0 (Negative-true logic) */
#define MMC_POM_CS0             _POM( MMC_CS0_PORTNO , MMC_CS0_BITNO )         /* MMC CS0 (Negative-true logic) */

#if defined(MMC_DETECT0_CONNECTION)
#define MMC_PM_DETECT0           _PM( MMC_DETECT0_PORTNO , MMC_DETECT0_BITNO ) /* MMC Detect0 (Negative-true logic) */
#define MMC_PORT_DETECT0          _P( MMC_DETECT0_PORTNO , MMC_DETECT0_BITNO ) /* MMC Detect0 (Negative-true logic) */
#define MMC_PIM_DETECT0         _PIM( MMC_DETECT0_PORTNO , MMC_DETECT0_BITNO ) /* MMC Detect0 (Negative-true logic) */
#define MMC_POM_DETECT0         _POM( MMC_DETECT0_PORTNO , MMC_DETECT0_BITNO ) /* MMC Detect0 (Negative-true logic) */
#endif /* #if defined(MMC_DETECT0_CONNECTION) */

#if (MMC_SLOT_NUM > 1)
#define MMC_PM_CS1               _PM( MMC_CS1_PORTNO , MMC_CS1_BITNO )         /* MMC CS1 (Negative-true logic) */
#define MMC_PORT_CS1              _P( MMC_CS1_PORTNO , MMC_CS1_BITNO )         /* MMC CS1 (Negative-true logic) */
#define MMC_PIM_CS1             _PIM( MMC_CS1_PORTNO , MMC_CS1_BITNO )         /* MMC CS1 (Negative-true logic) */
#define MMC_POM_CS1             _POM( MMC_CS1_PORTNO , MMC_CS1_BITNO )         /* MMC CS1 (Negative-true logic) */

#if defined(MMC_DETECT1_CONNECTION)
#define MMC_PM_DETECT1           _PM( MMC_DETECT1_PORTNO , MMC_DETECT1_BITNO ) /* MMC Detect1 (Negative-true logic) */
#define MMC_PORT_DETECT1          _P( MMC_DETECT1_PORTNO , MMC_DETECT1_BITNO ) /* MMC Detect1 (Negative-true logic) */
#define MMC_PIM_DETECT1         _PIM( MMC_DETECT1_PORTNO , MMC_DETECT1_BITNO ) /* MMC Detect1 (Negative-true logic) */
#define MMC_POM_DETECT1         _POM( MMC_DETECT1_PORTNO , MMC_DETECT1_BITNO ) /* MMC Detect1 (Negative-true logic) */
#endif /* #if defined(MMC_DETECT1_CONNECTION) */

#endif /* #if (MMC_SLOT_NUM > 1) */


/*----------- Definitions of resource used -----------*/
#define MMC_CSI_USED                             /* CSI used        */
#define MMC_SYNC_MSBF                            /* CSI MSB first      */

#ifdef MMC_OPTION_1
#define MMC_CRC_SOFT                             /* Encode by soft CRC (ROM table used) */
#endif /* #ifdef MMC_OPTION_1 */

#ifdef MMC_OPTION_2
#define MMC_CRC_HARD                             /* Encode by hard CRC     */
#define MMC_CRC_LSBF
#endif /* #ifdef MMC_OPTION_2 */


/*----------------- CSI definitions -----------------*/

/* 16bits 8bits */
#define MMC_CSI_SPSmL           _SPSL( MMC_SAU_UNIT )                   /* SPSmL register  :  8bits */
#define MMC_CSI_SMRmn           _SMR( MMC_SAU_UNIT ,MMC_SAU_CHANNEL )   /* SMRmn register  : 16bits */
#define MMC_CSI_SCRmn           _SCR( MMC_SAU_UNIT ,MMC_SAU_CHANNEL )   /* SCRmn register  : 16bits */
#define MMC_CSI_SDRmn           _SDR( MMC_SAU_UNIT ,MMC_SAU_CHANNEL )   /* SDRmn register  : 16bits */
#define MMC_CSI_SIOmn           _SIO( MMC_CSI_UNIT ,MMC_CSI_CHANNEL )   /* SIOmn register  :  8bits */
#define MMC_CSI_SIRmnL          _SIRL( MMC_SAU_UNIT ,MMC_SAU_CHANNEL )  /* SIRmnL register :  8bits */
#define MMC_CSI_SSRmnL          _SSRL( MMC_SAU_UNIT ,MMC_SAU_CHANNEL )  /* SSRmnL register :  8bits */

#define MMC_CSI_SSmn            _SSLB( MMC_SAU_UNIT ,MMC_SAU_CHANNEL )  /* SSm register Bit n  : 1bit */
#define MMC_CSI_STmn            _STLB( MMC_SAU_UNIT ,MMC_SAU_CHANNEL )  /* STm register Bit n  : 1bit */
#define MMC_CSI_SEmn            _SELB( MMC_SAU_UNIT ,MMC_SAU_CHANNEL )  /* SEm register Bit n  : 1bit */
#define MMC_CSI_SOEmn           _SOELB( MMC_SAU_UNIT ,MMC_SAU_CHANNEL ) /* SOEm register Bit n : 1bit */
#define MMC_CSI_SOm             _SO( MMC_SAU_UNIT )                     /* SOm register        : 16bits */
#define MMC_CSI_ISC             ISC                                     /* ISC register        :  8bits */
#define MMC_CSI_IFmn            _CSIIF( MMC_CSI_UNIT , MMC_CSI_CHANNEL) /* CSI Interrupt flag  :  1bit */
#define MMC_CSI_MKmn            _CSIMK( MMC_CSI_UNIT , MMC_CSI_CHANNEL) /* CSI Interrupt enable flag : 1bit */
#define MMC_SAUmEN              _SAUEN( MMC_SAU_UNIT )                  /* SAU enable flag     :  1bit  */
#define MMC_SAUmRES             _SAURES( MMC_SAU_UNIT )                 /* SAU reset flag      :  1bit  */

#define MMC_CSI_TXBUF           MMC_CSI_SIOmn
#define MMC_CSI_RXBUF           MMC_CSI_SIOmn

#if (MMC_OPERATION_CLK_SELECT == 0)
#define MMC_SPS_MASK            (uint8_t)0xF0
/* xxxx0000B */    /* SPSmnL setting                 */
/* ||||++++-------- PRSm[03:00] : CKm0 = fCLK        */
/* ++++------------ PRSm[07:04] : CKm1 = No change   */
#define MMC_SPS_SET             (uint8_t)(MMC_FCLK_PRESCALER_SELECT)
/* xxxx****B */    /* SPSmnL setting                 */
/* ||||++++-------- PRSm[03:00] : CKm0 set           */
/* ++++------------ PRSm[07:04] : CKm1 = No change   */
#elif (MMC_OPERATION_CLK_SELECT == 1)
#define MMC_SPS_MASK            (uint8_t)0x0F
/* 0000xxxxB */    /* SPSmnL setting                 */
/* ||||++++-------- PRSm[03:00] : CKm0 = No change   */
/* ++++------------ PRSm[07:04] : CKm1 = fCLK        */

#define MMC_SPS_SET             (uint8_t)(MMC_FCLK_PRESCALER_SELECT << 4)
/* ****xxxxB */ /* SPSmnL setting                    */
/* ||||++++-------- PRSm[03:00] : CKm0 = No change   */
/* ++++------------ PRSm[07:04] : CKm1 set           */
#endif

/* CSI setting */
#define MMC_SMR_TX              (uint16_t)0x0021 | ((uint16_t)MMC_OPERATION_CLK_SELECT << 15)
/* 00000000 00100001B */    /* SMRmn setting                                    */
/* |||||||| |||||||+-------- MDmn0      : Buffer empty interrupt                */
/* |||||||| |||||++--------- MDmn[2-1]  : CSI mode                              */
/* |||||||| |||++----------- Reserved   : Set to 0                              */
/* |||||||| ||+------------- Reserved   : Set to 1                              */
/* |||||||| |+-------------- SISmn      : Read by failing edge                  */
/* |||||||| +--------------- Reserved   : Set to 0                              */
/* |||||||+ ---------------- STSmn      : Software trigger is valid             */
/* ||+++++- ---------------- Reserved   : Set to 0                              */
/* |+------ ---------------- CCSmn      : Clock fMCK specified by the CKSmn bit */
/* +------- ---------------- CKSmn      : Operation clock CKmX set by the SPSm  */

#define MMC_SMR_RX              (uint16_t)0x0020 | ((uint16_t)MMC_OPERATION_CLK_SELECT << 15)
/* x0000000 00100000B */    /* SMRmn setting                                    */
/* |||||||| |||||||+-------- MDmn0      : Transfer end interrupt                */
/* |||||||| |||||++--------- MDmn[2-1]  : CSI mode                              */
/* |||||||| |||++----------- Reserved   : Set to 0                              */
/* |||||||| ||+------------- Reserved   : Set to 1                              */
/* |||||||| |+-------------- SISmn      : Read by failing edge                  */
/* |||||||| +--------------- Reserved   : Set to 0                              */
/* |||||||+ ---------------- STSmn      : Software trigger is valid             */
/* ||+++++- ---------------- Reserved   : Set to 0                              */
/* |+------ ---------------- CCSmn      : Clock fMCK specified by the CKSmn bit */
/* +------- ---------------- CKSmn      : Operation clock CKmX set by user      */

#define MMC_SCR_INIT            (uint16_t)0x0007
/* 00000000 00000111B */    /* SCRmn setting                                    */
/* |||||||| ||||||++-------- DLSmn[1:0] : 8-bit data length                     */
/* |||||||| |||||+---------- Reserved   : Set to 1                              */
/* |||||||| ||||+----------- Reserved   : Set to 0                              */
/* |||||||| ||++------------ SLCmn[1:0] : No stop bit                           */
/* |||||||| |+-------------- Reserved   : Set to 0                              */
/* |||||||| +--------------- DIRmn      : MSB first                             */
/* ||||||++ ---------------- PTCmn[1:0] : Receives without parity               */
/* |||||+-- ---------------- EOCmn      : Masks error interrupt                 */
/* ||||+--- ---------------- Reserved   : Set to 0                              */
/* |||+---- ---------------- CKPmn      : Select type 1                         */
/* ||+----- ---------------- DAPmn      : Select type 1                         */
/* |+------ ---------------- RXEmn      : Disable Reception                     */
/* +------- ---------------- TXEmn      : Disable Transmission                  */

#define MMC_SCR_TX              (uint16_t)0x8007
/* 10000000 00000111B */    /* SCRmn setting                                    */
/* |||||||| ||||||++-------- DLSmn[1:0] : 8-bit data length                     */
/* |||||||| |||||+---------- Reserved   : Set to 1                              */
/* |||||||| ||||+----------- Reserved   : Set to 0                              */
/* |||||||| ||++------------ SLCmn[1:0] : No stop bit                           */
/* |||||||| |+-------------- Reserved   : Set to 0                              */
/* |||||||| +--------------- DIRmn      : MSB first                             */
/* ||||||++ ---------------- PTCmn[1:0] : Receives without parity               */
/* |||||+-- ---------------- EOCmn      : Masks error interrupt                 */
/* ||||+--- ---------------- Reserved   : Set to 0                              */
/* |||+---- ---------------- CKPmn      : Select type 1                         */
/* ||+----- ---------------- DAPmn      : Select type 1                         */
/* |+------ ---------------- RXEmn      : Disable Reception                     */
/* +------- ---------------- TXEmn      : Enable Transmission                   */

#define MMC_SCR_RX              (uint16_t)0x4007
/* 10000000 00000111B */    /* SCRmn setting                                    */
/* |||||||| ||||||++-------- DLSmn[1:0] : 8-bit data length                     */
/* |||||||| |||||+---------- Reserved   : Set to 1                              */
/* |||||||| ||||+----------- Reserved   : Set to 0                              */
/* |||||||| ||++------------ SLCmn[1:0] : No stop bit                           */
/* |||||||| |+-------------- Reserved   : Set to 0                              */
/* |||||||| +--------------- DIRmn      : MSB first                             */
/* ||||||++ ---------------- PTCmn[1:0] : Receives without parity               */
/* |||||+-- ---------------- EOCmn      : Masks error interrupt                 */
/* ||||+--- ---------------- Reserved   : Set to 0                              */
/* |||+---- ---------------- CKPmn      : Select type 1                         */
/* ||+----- ---------------- DAPmn      : Select type 1                         */
/* |+------ ---------------- RXEmn      : Enable Reception                      */
/* +------- ---------------- TXEmn      : Disable Transmission                  */

#define MMC_CLKOUT_BIT          (uint16_t)(0x0001 << (8 + MMC_SAU_CHANNEL))
/* 0000xxxx 00000000B */    /* SOmn setting                                     */
/* |||||||| ++++++++-------- Reserved   : Set to 0                              */
/* |||||||+ ---------------- CKOm0      : CKOm0 Output level                    */
/* ||||||+- ---------------- CKOm1      : CKOm1 Output level                    */
/* |||||+-- ---------------- CKOm2      : CKOm2 Output level                    */
/* ||||+--- ---------------- CKOm3      : CKOm3 Output level                    */
/* ++++---- ---------------- Reserved   : Set to 0                              */

#define MMC_SOOUT_BIT           (uint16_t)(0x0001 << (MMC_SAU_CHANNEL))
/* 00000000 0000xxxxB */    /* SOmn setting                                     */
/* |||||||| |||||||+-------- SOm0       : SOm0 Output level                     */
/* |||||||| ||||||+--------- SOm1       : SOm1 Output level                     */
/* |||||||| |||||+---------- SOm2       : SOm2 Output level                     */
/* |||||||| ||||+----------- SOm3       : SOm3 Output level                     */
/* ++++++++ ++++------------ Reserved   : Set to 0                              */

#define MMC_TXNEXT_MASK         (uint8_t)(0x20)
/* 00100000B */    /* SSRmn reading           */
/* |||||||+-------- OVFmn     : Not Check     */
/* ||||||+--------- PEFmn     : Not Check     */
/* |||||+---------- FEFmn     : Not Check     */
/* |||++----------- Reserved  : Not Check     */
/* ||+------------- BFFmn     : Check         */
/* |+-------------- TSFmn     : Not Check     */
/* +--------------- Reserved  : Not Check     */

#define MMC_TXEND_MASK          (uint8_t)(0x40)
/* 01000000B */    /* SSRmn reading       */
/* |||||||+-------- OVFmn     : Not Check     */
/* ||||||+--------- PEFmn     : Not Check     */
/* |||||+---------- FEFmn     : Not Check     */
/* |||++----------- Reserved  : Not Check     */
/* ||+------------- BFFmn     : Not Check     */
/* |+-------------- TSFmn     : Check         */
/* +--------------- Reserved  : Not Check     */

#define MMC_RX_COMPLETE_MASK    (uint8_t)(0x20)
/* 01000000B */    /* SSRmn reading           */
/* |||||||+-------- OVFmn     : Not Check     */
/* ||||||+--------- PEFmn     : Not Check     */
/* |||||+---------- FEFmn     : Not Check     */
/* |||++----------- Reserved  : Not Check     */
/* ||+------------- BFFmn     : Check         */
/* |+-------------- TSFmn     : Not Check     */
/* +--------------- Reserved  : Not Check     */

#define MMC_OVF_MASK            (uint8_t)(0x01)
/* 00000001B */    /* SSRmn reading           */
/* |||||||+-------- OVFmn     : Not Check     */
/* ||||||+--------- PEFmn     : Not Check     */
/* |||||+---------- FEFmn     : Not Check     */
/* |||++----------- Reserved  : Not Check     */
/* ||+------------- BFFmn     : Not Check     */
/* |+-------------- TSFmn     : Check         */
/* +--------------- Reserved  : Not Check     */


#define MMC_DUMMY_DATA          (uint8_t)0xFF    /* MMC dummy data for some command */

/*----------------- CRC definitions ------------------*/
#ifdef MMC_CRC_HARD
#define MMC_CRCIN               CRCIN            /* CRC input register     */
#define MMC_CRCD                CRCD             /* CRC data register      */

#endif /* #ifdef MMC_CRC_HARD */


/************************************************************************************************/
/* Unions                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Structs                                                                                      */
/************************************************************************************************/

/************************************************************************************************/
/* Externs                                                                                      */
/************************************************************************************************/

/************************************************************************************************/
/* Macros                                                                                       */
/************************************************************************************************/

/*------------- Driver use port control --------------*/
#if (MMC_SLOT_NUM == 1)
/* !!!! The other Ports are set to input mode. !!!! */
#define MMC_IO_INIT()           do               /* Driver use terminal initial setting         */ \
    {                                                                                              \
        PMCA0          &= (MMC_PMCA0_TBL & MMC_CS0_PMCA0_TBL & MMC_DETECT0_PMCA0_TBL); \
        PMCA1          &= (MMC_PMCA1_TBL & MMC_CS0_PMCA1_TBL & MMC_DETECT0_PMCA1_TBL); \
        PMCA2          &= (MMC_PMCA2_TBL & MMC_CS0_PMCA2_TBL & MMC_DETECT0_PMCA2_TBL); \
        PMCA12         &= (MMC_PMCA12_TBL & MMC_CS0_PMCA12_TBL & MMC_DETECT0_PMCA12_TBL); \
        PMCA14         &= (MMC_PMCA14_TBL & MMC_CS0_PMCA14_TBL & MMC_DETECT0_PMCA14_TBL); \
        PMCT0          &= (MMC_PMCT0_TBL & MMC_CS0_PMCT0_TBL & MMC_DETECT0_PMCT0_TBL); \
        PMCT2          &= (MMC_PMCT2_TBL & MMC_CS0_PMCT2_TBL & MMC_DETECT0_PMCT2_TBL); \
        PMCT3          &= (MMC_PMCT3_TBL & MMC_CS0_PMCT3_TBL & MMC_DETECT0_PMCT3_TBL); \
        PMCT5          &= (MMC_PMCT5_TBL & MMC_CS0_PMCT5_TBL & MMC_DETECT0_PMCT5_TBL); \
        PMCT6          &= (MMC_PMCT6_TBL & MMC_CS0_PMCT6_TBL & MMC_DETECT0_PMCT6_TBL); \
        PMCT7          &= (MMC_PMCT7_TBL & MMC_CS0_PMCT7_TBL & MMC_DETECT0_PMCT7_TBL); \
        PMCE0          &= (MMC_PMCE0_TBL & MMC_CS0_PMCE0_TBL & MMC_DETECT0_PMCE0_TBL); \
        PMCE1          &= (MMC_PMCE1_TBL & MMC_CS0_PMCE1_TBL & MMC_DETECT0_PMCE1_TBL); \
        PMCE5          &= (MMC_PMCE5_TBL & MMC_CS0_PMCE5_TBL & MMC_DETECT0_PMCE5_TBL); \
        PMCE6          &= (MMC_PMCE6_TBL & MMC_CS0_PMCE6_TBL & MMC_DETECT0_PMCE6_TBL); \
        CCDE           &= (MMC_CCDE_TBL & MMC_CS0_CCDE_TBL & MMC_DETECT0_CCDE_TBL); \
        PFOE1          |= MMC_PFOE1_TBL; \
        MMC_PORT_DATAO = MMC_TRUE;               /* DataOut   "H"                               */ \
        MMC_PM_DATAO   = MMC_FALSE;              /* DataOut   Output                            */ \
        MMC_PORT_CLK   = MMC_TRUE;               /* CLK       "H"                               */ \
        MMC_PM_CLK     = MMC_FALSE;              /* CLK       Output                            */ \
        MMC_PM_DATAI   = MMC_TRUE;               /* DataIn    Input                             */ \
        MMC_PORT_CS0   = MMC_TRUE;               /* CS0       "H"                               */ \
        MMC_PM_CS0     = MMC_FALSE;              /* CS0       Output                            */ \
        MMC_DETECT0_INIT();                      /* DETECT0   Input                             */ \
    } while (0)
#endif /* #if (MMC_SLOT_NUM == 1) */

#if (MMC_SLOT_NUM > 1)
/* !!!! The other Ports are set to input mode. !!!! */
#define MMC_IO_INIT()           do               /* Driver use terminal initial setting         */ \
    {                                                                                              \
        PMCA0          &= (MMC_PMCA0_TBL & MMC_CS0_PMCA0_TBL & MMC_DETECT0_PMCA0_TBL); \
        PMCA1          &= (MMC_PMCA1_TBL & MMC_CS0_PMCA1_TBL & MMC_DETECT0_PMCA1_TBL); \
        PMCA2          &= (MMC_PMCA2_TBL & MMC_CS0_PMCA2_TBL & MMC_DETECT0_PMCA2_TBL); \
        PMCA12         &= (MMC_PMCA12_TBL & MMC_CS0_PMCA12_TBL & MMC_DETECT0_PMCA12_TBL); \
        PMCA14         &= (MMC_PMCA14_TBL & MMC_CS0_PMCA14_TBL & MMC_DETECT0_PMCA14_TBL); \
        PMCT0          &= (MMC_PMCT0_TBL & MMC_CS0_PMCT0_TBL & MMC_DETECT0_PMCT0_TBL); \
        PMCT2          &= (MMC_PMCT2_TBL & MMC_CS0_PMCT2_TBL & MMC_DETECT0_PMCT2_TBL); \
        PMCT3          &= (MMC_PMCT3_TBL & MMC_CS0_PMCT3_TBL & MMC_DETECT0_PMCT3_TBL); \
        PMCT5          &= (MMC_PMCT5_TBL & MMC_CS0_PMCT5_TBL & MMC_DETECT0_PMCT5_TBL); \
        PMCT6          &= (MMC_PMCT6_TBL & MMC_CS0_PMCT6_TBL & MMC_DETECT0_PMCT6_TBL); \
        PMCT7          &= (MMC_PMCT7_TBL & MMC_CS0_PMCT7_TBL & MMC_DETECT0_PMCT7_TBL); \
        PMCE0          &= (MMC_PMCE0_TBL & MMC_CS0_PMCE0_TBL & MMC_DETECT0_PMCE0_TBL); \
        PMCE1          &= (MMC_PMCE1_TBL & MMC_CS0_PMCE1_TBL & MMC_DETECT0_PMCE1_TBL); \
        PMCE5          &= (MMC_PMCE5_TBL & MMC_CS0_PMCE5_TBL & MMC_DETECT0_PMCE5_TBL); \
        PMCE6          &= (MMC_PMCE6_TBL & MMC_CS0_PMCE6_TBL & MMC_DETECT0_PMCE6_TBL); \
        CCDE           &= (MMC_CCDE_TBL & MMC_CS0_CCDE_TBL & MMC_DETECT0_CCDE_TBL); \
        PFOE1          |= MMC_PFOE1_TBL; \
        MMC_PORT_DATAO = MMC_TRUE;               /* DataOut   "H"                               */ \
        MMC_PM_DATAO   = MMC_FALSE;              /* DataOut   Output                            */ \
        MMC_PORT_CLK   = MMC_TRUE;               /* CLK       "H"                               */ \
        MMC_PM_CLK     = MMC_FALSE;              /* CLK       Output                            */ \
        MMC_PM_DATAI   = MMC_TRUE;               /* DataIn    Input                             */ \
        MMC_PORT_CS0   = MMC_TRUE;               /* CS0       "H"                               */ \
        MMC_PM_CS0     = MMC_FALSE;              /* CS0       Output                            */ \
        MMC_DETECT0_INIT();                      /* DETECT0   Input                             */ \
        MMC_PORT_CS1   = MMC_TRUE;               /* CS1       "H"                               */ \
        MMC_PM_CS1     = MMC_FALSE;              /* CS1       Output                            */ \
        MMC_DETECT1_INIT();                      /* DETECT1   Input                             */ \
    } while (0)
#endif /* #if (MMC_SLOT_NUM > 1) */

/*------------------ DataIn control ------------------*/
#define MMC_DATAI_INIT()        do               /* DataIn initial setting                      */ \
    {                                                                                              \
    } while (0)

/*----------------- DataOut control ------------------*/
#define MMC_DATAO_INIT()        do               /* DataOut initial setting                     */ \
    {                                                                                              \
    } while (0)

#define MMC_DATAO_OPEN()        do               /* DataOut open setting                        */ \
    {                                                                                              \
    } while (0)

/*------------------- CLK control --------------------*/
#define MMC_CLK_INIT()          do               /* CLK initial setting                         */ \
    {                                                                                              \
    } while (0)

#define MMC_CLK_OPEN()          do                /* CLK open setting                           */ \
    {                                                                                              \
    } while (0)

/*------------------ DETECT control ------------------*/
#if defined(MMC_DETECT0_CONNECTION)
#define MMC_DETECT0_INIT() do                    /* DETECT initial setting                      */ \
    {                                                                                              \
        MMC_PM_DETECT0     = MMC_TRUE;           /* DETECT   Input                              */ \
    } while (0)

#define MMC_GET_DETECT0(Lv) do                   /* DETECT input control                        */ \
    {                                                                                              \
        Lv = MMC_PORT_DETECT0;                                                                     \
    } while (0)
#else /* #if defined(MMC_DETECT0_CONNECTION) */
#define MMC_DETECT0_INIT()                       /* DETECT initial setting                      */
#define MMC_GET_DETECT0(Lv)                      /* DETECT input control                        */
#endif /* #if defined(MMC_DETECT0_CONNECTION) */


#if (MMC_SLOT_NUM > 1)
#if defined(MMC_DETECT1_CONNECTION)
#define MMC_DETECT1_INIT() do                    /* DETECT initial setting                      */ \
    {                                                                                              \
        MMC_PM_DETECT1     = MMC_TRUE;           /* DETECT   Input                              */ \
    } while (0)

#define MMC_GET_DETECT1(Lv) do                   /* DETECT input control                        */ \
    {                                                                                              \
        Lv = MMC_PORT_DETECT1;                                                                     \
    } while (0)
#else /* #if defined(MMC_DETECT0_CONNECTION) */
#define MMC_DETECT1_INIT()                       /* DETECT initial setting                      */
#define MMC_GET_DETECT1(Lv)                      /* DETECT input control                        */
#endif /* #if defined(MMC_DETECT1_CONNECTION) */
#endif /* #if (MMC_SLOT_NUM > 1) */

#if (MMC_SLOT_NUM == 1)
#define MMC_DETECT_INIT(SlotNo) do               /* DETECT initial setting                      */ \
    {                                                                                              \
        MMC_DETECT0_INIT();                                                                        \
    } while (0)
#define MMC_GET_DETECT(SlotNo, Lv) do            /* DETECT input control                        */ \
    {                                                                                              \
        Lv = MMC_NOT_CONNECT;                    /* Initialize by non-detection                 */ \
        MMC_GET_DETECT0(Lv);                                                                       \
    } while (0)
#endif /* #if (MMC_SLOT_NUM > 1) */

#if (MMC_SLOT_NUM > 1)
#define MMC_DETECT_INIT(SlotNo) do               /* DETECT initial setting                      */ \
    {                                                                                              \
        switch (SlotNo) {                                                                          \
            case MMC_SLOT0:  MMC_DETECT0_INIT();        break;                                     \
            case MMC_SLOT1:  MMC_DETECT1_INIT();        break;                                     \
            default:                                    break;                                     \
        }                                                                                          \
    } while (0)
#define MMC_GET_DETECT(SlotNo, Lv) do            /* DETECT input control                        */ \
    {                                                                                              \
        Lv = MMC_NOT_CONNECT;                    /* Initialize by non-detection                 */ \
        switch (SlotNo)                                                                            \
        {                                                                                          \
            case MMC_SLOT0:  MMC_GET_DETECT0(Lv);    break;                                        \
            case MMC_SLOT1:  MMC_GET_DETECT1(Lv);    break;                                        \
            default:                                 break;                                        \
        }                                                                                          \
    } while (0)
#endif /* #if (MMC_SLOT_NUM > 1) */

/*-------------------- CS control --------------------*/
#if (MMC_SLOT_NUM == 1)
#define MMC_CS_INIT(SlotNo)     do               /* CS initial setting                          */ \
    {                                                                                              \
        MMC_PORT_CS0       = MMC_HI;             /* CS0    "H"                                  */ \
        MMC_PM_CS0         = MMC_FALSE;          /* CS0    Output                               */ \
    } while (0)

#define MMC_CS_OPEN(SlotNo)     do               /* CS open setting                             */ \
    {                                                                                              \
        MMC_PM_CS0     = MMC_TRUE;               /* CS0    Input                                */ \
    } while (0)

#define MMC_SET_CS(SlotNo, Lv) do                /* CS output control                           */ \
    {                                                                                              \
        MMC_PORT_CS0       = Lv;                                                                   \
    } while (0)
#endif /* #if (MMC_SLOT_NUM == 1) */

#if (MMC_SLOT_NUM > 1)
#define MMC_CS_INIT(SlotNo)     do               /* CS initial setting                          */ \
    {                                                                                              \
        switch (SlotNo)                                                                            \
        {                                                                                          \
            case MMC_SLOT0:                                                                        \
                MMC_PORT_CS0  = MMC_HI;          /* CS0    Output                               */ \
                MMC_PM_CS0    = MMC_FALSE;       /* CS0    "H"                                  */ \
                break;                                                                             \
            case MMC_SLOT1:                                                                        \
                MMC_PORT_CS1  = MMC_HI;          /* CS1    Output                               */ \
                MMC_PM_CS1    = MMC_FALSE;       /* CS1    "H"                                  */ \
                break;                                                                             \
            default:                                                                               \
                break;                                                                             \
        }                                                                                          \
    } while (0)

#define MMC_CS_OPEN(SlotNo)     do               /* CS open setting                             */ \
    {                                                                                              \
        switch (SlotNo)                                                                            \
        {                                                                                          \
            case MMC_SLOT0:  MMC_PM_CS0 = MMC_TRUE; break; /* CS0   Input                       */ \
            case MMC_SLOT1:  MMC_PM_CS1 = MMC_TRUE; break; /* CS1   Input                       */ \
            default:                                break;                                         \
        }                                                                                          \
    } while (0)

#define MMC_SET_CS(SlotNo, Lv)  do               /* CS output control                           */ \
    {                                                                                              \
        switch (SlotNo)                                                                            \
        {                                                                                          \
            case MMC_SLOT0:  MMC_PORT_CS0 = Lv;  break;                                            \
            case MMC_SLOT1:  MMC_PORT_CS1 = Lv;  break;                                            \
            default:                             break;                                            \
        }                                                                                          \
    } while (0)

#endif /* #if (MMC_SLOT_NUM > 1) */

/*------------------- CSI control -------------------*/
#define MMC_CSI_ERR_CLEAR()     do               /* CSI enable setting                          */ \
    {                                                                                              \
        MMC_CSI_SIRmnL  = MMC_CSI_SIR_CLEAR;     /* clear error flag                            */ \
    } while (0)


#define MMC_CSI_EI() do                          /* CSI enable setting                          */ \
    {                                                                                              \
        MMC_SAUmRES     = MMC_FALSE;             /* SAUm reset control                          */ \
        MMC_SAUmEN      = MMC_TRUE;              /* supply SAUm clock                           */ \
        __nop();                                 /* wait 4 clocks                               */ \
        __nop();                                                                                   \
        __nop();                                                                                   \
        __nop();                                                                                   \
        MMC_CSI_SPSmL   = (MMC_CSI_SPSmL & MMC_SPS_MASK | MMC_SPS_SET); /* Serial clock setting */ \
        MMC_CSI_STmn    =  MMC_TRUE;             /* clear error flag                            */ \
        MMC_CSI_MKmn    =  MMC_TRUE;             /* disable INTCSImn interrupt                  */ \
        MMC_CSI_IFmn    =  MMC_FALSE;            /* clear INTCSImn interrupt flag               */ \
        MMC_CSI_SIRmnL  =  MMC_CSI_SIR_CLEAR;    /* clear error flag                            */ \
        MMC_CSI_SCRmn   =  MMC_SCR_INIT;         /* init SCR setting                            */ \
        MMC_CSI_SOm     |= MMC_CLKOUT_BIT;                                                         \
        MMC_CSI_SOm     |= MMC_SOOUT_BIT;                                                          \
        MMC_CSI_SOEmn   =  MMC_TRUE;                                                               \
        MMC_CSI_ISC     &= MMC_ISC_TBL;                                                            \
    } while (0)

#define MMC_CSI_DI()            do               /* CSI disable setting                         */ \
    {                                                                                              \
        MMC_CSI_SCRmn   = MMC_SCR_INIT;          /* init SCR setting                            */ \
    } while (0)

#define MMC_CSI_BRG_SET(BR_DATA) do              /* CSI bit rate setting                        */ \
    {                                                                                              \
        MMC_CSI_SDRmn   = ((uint16_t)BR_DATA << 9);  /* Clock setting                           */ \
    } while (0)

#define MMC_CSI_TX_EI()         do               /* CSI transmit enable setting                 */ \
    {                                                                                              \
        MMC_CSI_SMRmn   = MMC_SMR_TX;            /* Transmission mode setting                   */ \
        MMC_CSI_SCRmn   = MMC_SCR_TX;            /* Transmission mode setting                   */ \
        MMC_CSI_SOEmn   = MMC_TRUE;                                                                \
        MMC_CSI_IFmn    = MMC_FALSE;             /* clear INTCSImn interrupt flag               */ \
        MMC_CSI_SSmn    = MMC_TRUE;              /* enable CSIxy                                */ \
    } while (0)

#define MMC_CSI_TRX_EI()        do               /* CSI transmit&receive enable setting         */ \
    {                                                                                              \
        MMC_CSI_SMRmn   = MMC_SMR_RX;            /* Transmission mode setting                   */ \
        MMC_CSI_SCRmn   = MMC_SCR_RX;            /* Transmission mode setting                   */ \
        MMC_CSI_SOEmn   = MMC_TRUE;              /* enable CSI                                  */ \
        MMC_CSI_IFmn    = MMC_FALSE;             /* clear INTCSImn interrupt flag               */ \
        MMC_CSI_SSmn    = MMC_TRUE;              /* start CSI                                   */ \
    } while (0)

#define MMC_CSI_TX_DI()         do               /* CSI transmit disable setting                */ \
    {                                                                                              \
        MMC_CSI_STmn    = MMC_TRUE;              /* stop CSI                                    */ \
        MMC_CSI_SOEmn   = MMC_FALSE;             /* disable CSI output                          */ \
        MMC_CSI_IFmn    = MMC_FALSE;             /* clear INTCSImn interrupt flag               */ \
        MMC_CSI_SOm    |= ((uint16_t)1 << MMC_CLK_SO_BITNO) | ((uint16_t)1 << MMC_DATAO_SO_BITNO);             /* Port init    */ \
    } while (0)

#define MMC_CSI_TRX_DI()        do              /* CSI transmit&receive disable setting         */ \
    {                                                                                              \
        MMC_CSI_STmn    = MMC_TRUE;             /* stop CSI                                     */ \
        MMC_CSI_SOEmn   = MMC_FALSE;            /* disable CSI output                           */ \
        MMC_CSI_IFmn    = MMC_FALSE;            /* clear INTCSImn interrupt flag                */ \
        MMC_CSI_SOm    |= ((uint16_t)1 << MMC_CLK_SO_BITNO) | ((uint16_t)1 << MMC_DATAO_SO_BITNO);             /* Port init    */ \
    } while (0)

#define MMC_TXNEXT_CHECK()      ((MMC_CSI_SSRmnL & MMC_TXNEXT_MASK) != 0)
#define MMC_TXNEXT_CLR()        do                                                                 \
    {                                                                                              \
        MMC_CSI_IFmn  = MMC_FALSE;                                                                 \
    } while (0)

#define MMC_TXEND_CHECK()       ((MMC_CSI_SSRmnL & MMC_TXEND_MASK) != 0)


#define MMC_CSI_ORER_CHECK()    ((MMC_CSI_SSRmnL & MMC_OVF_MASK) != 0)

#define MMC_RX_COMPLETE_CHECK() ((MMC_CSI_SSRmnL & MMC_RX_COMPLETE_MASK) == 0)
#define MMC_RXNEXT_CLR()

/*----------------- CRC calculation ------------------*/
#ifdef MMC_CRC_HARD
#define MMC_CRC_CLR()           MMC_CRCD  = 0x0000
#define MMC_CRC_SET(Data)       do                                                                 \
    {                                                                                              \
        MMC_CRCIN = T_ExchgBit[Data];                                                              \
    }while(0);

#define MMC_CRC_GET(Data)       Data = MMC_CRCD
#else /* #ifdef MMC_CRC_HARD */
#define MMC_CRC_CLR()           gMmc_CrcData.us = 0x0000
#ifdef MTL_MCU_LITTLE
#define MMC_CRC_SET(Data)       do                                                                 \
    {                                                                                              \
        uint8_t ucTmp;                                                                             \
        ucTmp              = gMmc_CrcData.uc[0];                                                   \
        gMmc_CrcData.us    = T_Crc_Ccitt[gMmc_CrcData.uc[1] ^ Data];                               \
        gMmc_CrcData.uc[1] = gMmc_CrcData.uc[1] ^ ucTmp;                                           \
    } while (0)
#else /* #ifdef MTL_MCU_LITTLE */
#define MMC_CRC_SET(Data)       do                                                                 \
    {                                                                                              \
        uint8_t ucTmp;                                                                             \
        ucTmp              = gMmc_CrcData.uc[1];                                                   \
        gMmc_CrcData.us    = T_Crc_Ccitt[gMmc_CrcData.uc[0] ^ Data];                               \
        gMmc_CrcData.uc[0] = gMmc_CrcData.uc[0] ^ ucTmp;                                           \
    } while (0)
#endif /* #ifdef MTL_MCU_LITTLE */
#define MMC_CRC_GET(Data)       Data = gMmc_CrcData.us
#endif /* #ifdef MMC_CRC_HARD */

#endif /* __MMC_SFR_H__ */
