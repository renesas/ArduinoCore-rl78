/*""FILE COMMENT""*******************************************************************
* File Name     : r_mmc_user_config.h
* Version       : 1.00
* Device(s)     : RL78/G23
* compiler      : CC-RL
* H/W Platform  : R7F100Gxx
* Description   : MMC driver SFR for RL78/G23-CSI user configuration definitions
*************************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 04.06.2021 Ver1.00
*""FILE COMMENT END""***************************************************************/
#ifndef __R_MMC_USER_CONFIG_H__
#define __R_MMC_USER_CONFIG_H__

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*                         Please define resources of each user system.                         */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/* Serial Array Unit(SAU) Select ( 0 or 1 )*/
#define MMC_SAU_UNIT            0                 /** SET **/
/* SAU Channel Select ( 0 or 1 or 2 or 3 ) */
#define MMC_SAU_CHANNEL         3                 /** SET **/
/* CSI PIN select  ( 'A' or 'B' ) */
#define MMC_CSI_PIN             'A'               /** SET **/

/*
                                     ||          Select Port           |
------------+------------+-----------++--------------------------------+
  MMC_SAU_  |  MMC_SAU_  | MMC_CSI_  ||    SI    |   SCK    |    SO    |
  UNIT      |  CHANNEL   | PIN       ||  Select  |  Select  |  Select  |
   Value    |   Value    |  Value    ||   port   |   port   |   port   |
============+============+===========++==========+==========+==========+
     0      |     0      |    'A'    ||   P11    |   P10    |   P12    |
(=Use SAU0) |            |-----------++----------+----------+----------+
            |(=Use CSI00)|    'B'    ||   P16    |   P55    |   P17    |
            +------------+-----------++----------+----------+----------+
            |     1      | (invalid) ||   P74    |   P75    |   P73    |
            |(=Use CSI01)|           ||          |          |          |
            +------------+-----------++----------+----------+----------+
            |     2      | (invalid) ||   P03    |   P04    |   P02    |
            |(=Use CSI10)|           ||          |          |          |
           -+------------+-----------++----------+----------+----------+
            |     3      | (invalid) ||   P50    |   P30    |   P51    |
            |(=Use CSI11)|           ||          |          |          |
------------+------------+-----------++----------+----------+----------+
     1      |     0      | (invalid) ||   P14    |   P15    |   P13    |
(=Use SAU1) |(=Use CSI20)|           ||          |          |          |
            +------------+-----------++----------+----------+----------+
            |     1      | (invalid) ||   P71    |   P70    |   P72    |
            |(=Use CSI21)|           ||          |          |          |
------------+------------+-----------++----------+----------+----------+*/

/*----------------------------------------------------------------------------------------------*/
/*  Define the control port.                                                                    */
/*----------------------------------------------------------------------------------------------*/
#define MMC_CS0_PORTNO          0                /* CS0 Port No. */  /** SET **/
#define MMC_CS0_BITNO           5                /* CS0 Bit  No. */  /** SET **/

/* Please define the MMC_DETECT0_CONNECTION macro when the MMC slot Card detect pin connect to MCU. */
//#define MMC_DETECT0_CONNECTION                   /* DETECT0 Port Connection */ /** SET **/

#if defined(MMC_DETECT0_CONNECTION)
#define MMC_DETECT0_PORTNO      0                /* DETECT0 Port No. */ /** SET **/
#define MMC_DETECT0_BITNO       6                /* DETECT0 Bit  No. */ /** SET **/
#endif /* #if defined(MMC_DETECT0_CONNECTION) */


#if (MMC_SLOT_NUM > 1)

#define MMC_CS1_PORTNO                          /* CS1 Port No. */  /** SET **/
#define MMC_CS1_BITNO                           /* CS1 Bit  No. */  /** SET **/


#define MMC_DETECT1_CONNECTION                   /* DETECT1 Port Connection */ /** SET **/

#if defined(MMC_DETECT1_CONNECTION)
#define MMC_DETECT1_PORTNO                   /* DETECT1 Port No. */ /** SET **/
#define MMC_DETECT1_BITNO                    /* DETECT1 Bit  No. */ /** SET **/
#endif /* #if defined(MMC_DETECT0_CONNECTION) */

#endif /* #if (MMC_SLOT_NUM > 1) */


/*----------------------------------------------------------------------------------------------*/
/* Macro "MMC_NOCHK_TIMEOUT" omits detecting timeout during communication.                      */
/* If user omits detecting timeout, please define this macro.                                   */
/* If this macro is defined, processing speed would be increased.                               */
/*----------------------------------------------------------------------------------------------*/
#define MMC_NOCHK_TIMEOUT                        /* No Check Communication Timeout  */ /** SET **/

/*----------------------------------------------------------------------------------------------*/
/* If MMC_NOCHK_TIMEOUT would be not defined, please set timeout time.                          */
/* MMC_T_CSI_WAIT is unit of measuring timeout.                                                 */
/* Please select value from "r_mtl_tim.h"                                                       */
/* Please set value of (timeout time/unit) to MMC_CSI_TX_WAIT(transmitting)                     */
/* and MMC_CSI_RX_WAIT(receiving).                                                              */
/*----------------------------------------------------------------------------------------------*/
/* CSI transmit&receive completion waiting polling time   */
#define MMC_T_CSI_WAIT   (natural_uint_t)MTL_T_1US                                    /** SET **/

/* CSI transmission completion waiting time 50000 * 1us = 50ms */
#define MMC_CSI_TX_WAIT  (natural_uint_t)50000                                        /** SET **/
/* CSI receive completion waiting time  50000 * 1us = 50ms */
#define MMC_CSI_RX_WAIT  (natural_uint_t)50000                                        /** SET **/


/*----------------------------------------------------------------------------------------------*/
/*  Define the combination of the MCU's resources.                                              */
/*----------------------------------------------------------------------------------------------*/
//#define MMC_OPTION_1   /* CSI                            */ /** SET **/
#define MMC_OPTION_2   /* CSI + CRC calculation circuit  */ /** SET **/


/*----------------------------------------------------------------------------------------------*/
/*  Define the value of the bit rate register according to a communication baud rate.           */
/*  Set the frequency of CLK to 12MHz or less.                                                  */
/*  The possible maximum transfer frequency of CLK is depends on hardware circuit               */
/*  and MCU conditions.                                                                         */
/*   Refer to MCU hardware manual/memory card specifications and specify the buad rate.         */
/*  When operating card with SPI mode,                                                          */
/*  specify the following two definitions of Identification mode and Data Transfer mode.        */
/*  Specify the definition to meet tODLY of both Identification mode and Data Transfer mode.    */
/*  In addition, meet tOD (100KHz <= tOD <= 400KHz) at Identification mode                      */
/*  and tPP (0.1MHz <= tPP <= 20MHz ) at Data Transfer mode.                                    */
/*  The maximum frequency depends on MCU type.                                                  */
/*                                                                                              */
/*  Transfer clock frequency(fTCLK) = (fMCK) / (SDRmn[15:9] + 1) / 2 [Hz]                       */
/*  fMCK: Operation clock                                                                       */
/*        fMCK is determined by serial clock select register m (SPSm)                           */
/*          and bit 15 (CKSmn) of serial mode register mn (SMRmn).                              */
/*----------------------------------------------------------------------------------------------*/
/* fCLK = 32MHz , fMCK = 16MHz , fTCLK = 8MHz */
#define MMC_FCLK_PRESCALER_SELECT 1              /* SPSm.PRSmk[3:0]                             */ /** SET **/

#define MMC_OPERATION_CLK_SELECT  0              /* select SMRm.CKmX 0:CKm0  1:CKm1             */ /** SET **/

#define MMC_UBRG_IDENTIFICATION   (uint8_t)19    /* BRR identification mode setting             */ /** SET **/
/*                                         ++---------------- 400KHz                */
#define MMC_UBRG_D_TRANSFER       (uint8_t)0    /* BRR data Transfer mode setting               */ /** SET **/
/*                                         ++---------------- 8.0MHz       */
#define MMC_CLK_D_TRANSFER        (uint32_t)8000000  /* Data Transfer mode clock frequency      */ /** SET **/

#endif /* #ifndef __R_MMC_USER_CONFIG_H__ */
