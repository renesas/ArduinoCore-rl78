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
* File Name     : r_mmc_io.c
* Version       : 1.23B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description   : MMC driver SPI mode I/O module
*************************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 27.06.2006 Ver1.13
*               : 21.02.2007 Ver1.14
*               : 21.06.2007 Ver1.15
*               : 10.12.2007 Ver1.20
*               : 17.01.2008 Ver1.21
*               : 29.01.2008 Ver1.22
*               : 26.03.2008 Ver1.23
*               : 25.06.2010 Ver1.23A
*               : 02.03.2012 Ver1.23B
*""FILE COMMENT END""***************************************************************/
#include "r_mmc_mcu_pragma.h"
#include "r_mtl_com.h"                     /* Renesas tool common definitions                   */
#include "r_mmc.h"                         /* MMC driver common definitions                     */
#include "r_mmc_sub.h"                     /* MMC driver sub module definitions                 */
#include "r_mmc_io.h"                      /* MMC driver I/O module definitions                 */
#include "r_mmc_sfr.h"                     /* MMC driver SFR definitions                        */

/************************************************************************************************/
/* Definitions                                                                                  */
/************************************************************************************************/
#define MMC_FID            (8UL << 6 | 3UL)

/*---------- Definitions of command-related ----------*/
#define MMC_CMD_CMD_IDX    0               /* Command buffer : Command index                    */
#define MMC_CMD_ARG_IDX    1               /* Command buffer : Operand index                    */
#define MMC_CMD_CRC_IDX    5               /* Command buffer : CRC7 index                       */
#define MMC_CMD_NCR_IDX    6               /* Command buffer : NCR MIN index                    */
#define MMC_CMD_SIZE       (uint16_t)6     /* Command size(Byte)                                */

/*-------- Definitions of response check data --------*/
#define MMC_RES1_CHKDATA   (uint8_t)0xFE   /* Response 1 check data                             */
#define MMC_RES1_CHKDATA2  (uint8_t)0xBE   /* Response 1 check data of CMD12                    */

/************************************************************************************************/
/* Unions                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Structs                                                                                      */
/************************************************************************************************/

/************************************************************************************************/
/* Globals                                                                                      */
/************************************************************************************************/
#ifdef MMC_CRC_SOFT
/*""VAL DEF""*/
const uint16_t  T_Crc_Ccitt[] =            /* CRC-CCITT calculation table                       */
{
    /*""VAL DEF END""*/
    /*  0x*0    0x*1    0x*2    0x*3    0x*4    0x*5    0x*6    0x*7    0x*8    0x*9    0x*A    0x*B    0x*C    0x*D    0x*E    0x*F        */
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7, 0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF, /* 0x0* */
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6, 0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE, /* 0x1* */
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485, 0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D, /* 0x2* */
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4, 0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC, /* 0x3* */
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823, 0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B, /* 0x4* */
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12, 0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A, /* 0x5* */
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41, 0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49, /* 0x6* */
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70, 0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78, /* 0x7* */
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F, 0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067, /* 0x8* */
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E, 0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256, /* 0x9* */
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D, 0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, /* 0xA* */
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C, 0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634, /* 0xB* */
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB, 0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3, /* 0xC* */
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A, 0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92, /* 0xD* */
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9, 0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1, /* 0xE* */
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8, 0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0, /* 0xF* */
};
#endif /* #ifdef MMC_CRC_SOFT */

/*""VAL DEF""*/
STATIC const uint8_t  T_Crc7[] =           /* CRC7 calculation table                            */
{
    /*""VAL DEF END""*/
    /* 0x*0  0x*1  0x*2  0x*3  0x*4  0x*5  0x*6  0x*7  0x*8  0x*9  0x*A  0x*B  0x*C  0x*D  0x*E  0x*F          */
    0x00, 0x12, 0x24, 0x36, 0x48, 0x5A, 0x6C, 0x7E, 0x90, 0x82, 0xB4, 0xA6, 0xD8, 0xCA, 0xFC, 0xEE, /* 0x0* */
    0x32, 0x20, 0x16, 0x04, 0x7A, 0x68, 0x5E, 0x4C, 0xA2, 0xB0, 0x86, 0x94, 0xEA, 0xF8, 0xCE, 0xDC, /* 0x1* */
    0x64, 0x76, 0x40, 0x52, 0x2C, 0x3E, 0x08, 0x1A, 0xF4, 0xE6, 0xD0, 0xC2, 0xBC, 0xAE, 0x98, 0x8A, /* 0x2* */
    0x56, 0x44, 0x72, 0x60, 0x1E, 0x0C, 0x3A, 0x28, 0xC6, 0xD4, 0xE2, 0xF0, 0x8E, 0x9C, 0xAA, 0xB8, /* 0x3* */
    0xC8, 0xDA, 0xEC, 0xFE, 0x80, 0x92, 0xA4, 0xB6, 0x58, 0x4A, 0x7C, 0x6E, 0x10, 0x02, 0x34, 0x26, /* 0x4* */
    0xFA, 0xE8, 0xDE, 0xCC, 0xB2, 0xA0, 0x96, 0x84, 0x6A, 0x78, 0x4E, 0x5C, 0x22, 0x30, 0x06, 0x14, /* 0x5* */
    0xAC, 0xBE, 0x88, 0x9A, 0xE4, 0xF6, 0xC0, 0xD2, 0x3C, 0x2E, 0x18, 0x0A, 0x74, 0x66, 0x50, 0x42, /* 0x6* */
    0x9E, 0x8C, 0xBA, 0xA8, 0xD6, 0xC4, 0xF2, 0xE0, 0x0E, 0x1C, 0x2A, 0x38, 0x46, 0x54, 0x62, 0x70, /* 0x7* */
    0x82, 0x90, 0xA6, 0xB4, 0xCA, 0xD8, 0xEE, 0xFC, 0x12, 0x00, 0x36, 0x24, 0x5A, 0x48, 0x7E, 0x6C, /* 0x8* */
    0xB0, 0xA2, 0x94, 0x86, 0xF8, 0xEA, 0xDC, 0xCE, 0x20, 0x32, 0x04, 0x16, 0x68, 0x7A, 0x4C, 0x5E, /* 0x9* */
    0xE6, 0xF4, 0xC2, 0xD0, 0xAE, 0xBC, 0x8A, 0x98, 0x76, 0x64, 0x52, 0x40, 0x3E, 0x2C, 0x1A, 0x08, /* 0xA* */
    0xD4, 0xC6, 0xF0, 0xE2, 0x9C, 0x8E, 0xB8, 0xAA, 0x44, 0x56, 0x60, 0x72, 0x0C, 0x1E, 0x28, 0x3A, /* 0xB* */
    0x4A, 0x58, 0x6E, 0x7C, 0x02, 0x10, 0x26, 0x34, 0xDA, 0xC8, 0xFE, 0xEC, 0x92, 0x80, 0xB6, 0xA4, /* 0xC* */
    0x78, 0x6A, 0x5C, 0x4E, 0x30, 0x22, 0x14, 0x06, 0xE8, 0xFA, 0xCC, 0xDE, 0xA0, 0xB2, 0x84, 0x96, /* 0xD* */
    0x2E, 0x3C, 0x0A, 0x18, 0x66, 0x74, 0x42, 0x50, 0xBE, 0xAC, 0x9A, 0x88, 0xF6, 0xE4, 0xD2, 0xC0, /* 0xE* */
    0x1C, 0x0E, 0x38, 0x2A, 0x54, 0x46, 0x70, 0x62, 0x8C, 0x9E, 0xA8, 0xBA, 0xC4, 0xD6, 0xE0, 0xF2  /* 0xF* */
};

#if ((defined(MMC_CRC_HARD) && !defined(MMC_CRC_MSBF)) || defined(MMC_SYNC_LSBF))
/*""VAL DEF""*/
#if defined(__RX)
#pragma section MMCBITCHG
#endif
const uint8_t  T_ExchgBit[] =              /* bit upper lower exchange table                    */
    {
        /*""VAL DEF END""*/
        /* 0x*0  0x*1  0x*2  0x*3  0x*4  0x*5  0x*6  0x*7  0x*8  0x*9  0x*A  0x*B  0x*C  0x*D  0x*E  0x*F          */
        0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, /* 0x0* */
        0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, /* 0x1* */
        0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, /* 0x2* */
        0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, /* 0x3* */
        0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, /* 0x4* */
        0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA, /* 0x5* */
        0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, /* 0x6* */
        0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, /* 0x7* */
        0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1, /* 0x8* */
        0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, /* 0x9* */
        0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, /* 0xA* */
        0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD, /* 0xB* */
        0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, /* 0xC* */
        0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, /* 0xD* */
        0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, /* 0xE* */
        0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF /* 0xF* */
    };
#if defined(__RX)
#pragma section
#endif
#endif /* #if ((defined(MMC_CRC_HARD) && !defined(MMC_CRC_MSBF)) || defined(MMC_SYNC_LSBF)) */

const uint8_t gMmcDummyData[MMC_DUMMY_MAXLEN] =
{
    MMC_DUMMY_DATA, MMC_DUMMY_DATA, MMC_DUMMY_DATA, MMC_DUMMY_DATA,
    MMC_DUMMY_DATA, MMC_DUMMY_DATA, MMC_DUMMY_DATA, MMC_DUMMY_DATA,
    MMC_DUMMY_DATA, MMC_DUMMY_DATA, MMC_DUMMY_DATA, MMC_DUMMY_DATA,
    MMC_DUMMY_DATA, MMC_DUMMY_DATA, MMC_DUMMY_DATA, MMC_DUMMY_DATA
};


/*""VAL DEF""*/
STATIC uint8_t  gMmc_CmdBuf[MMC_CMD_SIZE+MMC_NCR_MIN]; /* Command transmission buffer           */
uint8_t         gMmc_ResBuf[MMC_MAX_RES_SIZE];         /* Response receive buffer               */
#ifdef MMC_CRC_SOFT
MMC_EXCHG_SHORT gMmc_CrcData;                          /* Calculation CRC data storage buffer   */
#endif /* #ifdef MMC_CRC_SOFT */
/*""VAL DEF END""*/

/************************************************************************************************/
/* Macros                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Prototypes                                                                                   */
/************************************************************************************************/
STATIC uint8_t R_mmc_Crc7_Cmd(uint8_t *pData);         /* CRC7 calculation for CMD              */
uint16_t R_ExchgCrc(void);                             /* Calculation CRC data conversion       */

/*----------------------------------------------------------------------------------------------*/
/* Port control processing                                                                      */
/*----------------------------------------------------------------------------------------------*/

/******************************************************************************
* Declaration  : void R_mmc_Init_IO(void)
* Function Name: R_mmc_Init_IO
* Description  : Initialize all ports which an MMC driver uses
* Argument     : None
* Return Value : None
******************************************************************************/
void R_mmc_Init_IO(void)
{
    MMC_IO_INIT();
}

/******************************************************************************
* Declaration  : void R_mmc_Init_Port(uint8_t SlotNo)
* Function Name: R_mmc_Init_Port
* Description  : Initialize the port in conjunction with the designated slot.
*              : All slots common port (DataOut,DataIn,CLK) initializes it forcibly
* Argument     : uint8_t SlotNo  : slot number
* Return Value : None
******************************************************************************/
void R_mmc_Init_Port(uint8_t SlotNo)
{
    MMC_CS_INIT(SlotNo);           /* CS        "H" / Output    */
    MMC_DETECT_INIT(SlotNo);       /* DETECT          Input     */

    MMC_DATAI_INIT();              /* DataIn          Input     */
    MMC_DATAO_INIT();              /* DataOut   "H" / Output    */
    MMC_CLK_INIT();                /* CLK       "H" / Output    */
}

/******************************************************************************
* Declaration  : void R_mmc_Open_Port(uint8_t SlotNo)
* Function Name: R_mmc_Open_Port
* Description  : Make the port about the designated slot an available state.
*              : Make all slots common port (DataOut,DataIn,CLK) an available state forcibly.
* Argument     : uint8_t SlotNo  : slot number
* Return Value : None
******************************************************************************/
void R_mmc_Open_Port(uint8_t SlotNo)
{
    MMC_CS_OPEN(SlotNo);           /* CS              Input    */
    MMC_DETECT_INIT(SlotNo);       /* DETECT          Input    */

    MMC_DATAI_INIT();              /* DataIn          Input    */
    MMC_DATAO_OPEN();              /* DataOut         Input    */
    MMC_CLK_OPEN();                /* CLK             Input    */
}

/******************************************************************************
* Declaration  : uint8_t R_mmc_Get_Detect(uint8_t SlotNo)
* Function Name: R_mmc_Get_Detect
* Description  : Check the state of the Detect terminal
* Argument     : uint8_t SlotNo  : slot number
* Return Value : MMC_TRUE  ;Detect terminal is "L"
*              : MMC_FALSE ;Detect terminal is "H"
******************************************************************************/
uint8_t R_mmc_Get_Detect(uint8_t SlotNo)
{
    uint8_t Lv;

    MMC_GET_DETECT(SlotNo, Lv);       /* Detect state input              */
    if (Lv == MMC_NOT_CONNECT)
    {
        /* MMC insertion state acquisition */
        Lv = R_mmc_Get_Detect_Status(SlotNo);
        return Lv;
    }

    if (Lv == MMC_LOW)                /* MMC insertion detection         */
    {
        return MMC_TRUE;
    }
    else                              /* MMC insertion non-detection     */
    {
        return MMC_FALSE;
    }
}

/*----------------------------------------------------------------------------------------------*/
/* Command transmission processing                                                              */
/*----------------------------------------------------------------------------------------------*/
/******************************************************************************
* Declaration  : int16_t R_mmc_Send_Cmd_Spi(uint8_t Cmd, uint32_t Arg, uint32_t ResSize, uint32_t RtyCnt)
* Function Name: R_mmc_Send_Cmd_Spi
* Description  : Publish a command and check a response.
*              : Make a transmission command and publish it.
*              : Receive a response for designated size.
*              : Wait for NRC other than R/W command publication.
*              : Check response R1 data.
*              : When a response is NG, drvier performs a rule number of times command transmission re-try.
*              : Please check "R1 in idle state", "R2", "R3" at a high rank.
* Argument     : uint8_t        Cmd      ; Command number
*              : uint32_t       Arg      ; Operand data
*              : natural_uint_t ResSize  ; Response data size
*              : natural_uint_t RtyCnt   ; Retry count
* Return Value : MMC_OK                  : Normal end
*              : MMC_ERR_HARD            ; Hardware error
*              : MMC_ERR_IDLE            ; Idle status error
*              : MMC_ERR_OTHER           ; Other error
******************************************************************************/
int16_t R_mmc_Send_Cmd_Spi(uint8_t Cmd, uint32_t Arg, natural_uint_t ResSize, natural_uint_t RtyCnt)
{
    natural_uint_t i;
    uint8_t *pArg;
    int16_t Ret;

    /* The specified command is stored in the buffer */
    gMmc_CmdBuf[MMC_CMD_CMD_IDX]   = Cmd;
    pArg = (uint8_t*) & Arg;
    gMmc_CmdBuf[MMC_CMD_ARG_IDX+0] = *(pArg + 0);
    gMmc_CmdBuf[MMC_CMD_ARG_IDX+1] = *(pArg + 1);
    gMmc_CmdBuf[MMC_CMD_ARG_IDX+2] = *(pArg + 2);
    gMmc_CmdBuf[MMC_CMD_ARG_IDX+3] = *(pArg + 3);

    /* CRC7 calculation */
    gMmc_CmdBuf[MMC_CMD_CRC_IDX] = R_mmc_Crc7_Cmd((uint8_t *)gMmc_CmdBuf);

    /* NCR MIN wait dummy data storage */
    gMmc_CmdBuf[MMC_CMD_NCR_IDX] = MMC_DUMMY_DATA;

    for (; RtyCnt != 0; RtyCnt--)
    {
        /* Re-try loop         */
        /* waiting for NRC */
        R_mmc_Sync_DummyClk(MMC_NRC_MIN);

        /* 48bit Command transmission & Waiting for NCR MIN */
        Ret = R_mmc_Sync_MultTx(MMC_CMD_SIZE + MMC_NCR_MIN, gMmc_CmdBuf);
        if (Ret >= MMC_OK)
        {
            /* Waiting for response & Response top byte receive */

            R_mtl_wait_lp(MMC_T_REGSET_WAIT);

            *gMmc_ResBuf = 0xFF;
            for (i = MMC_NCR_MAX; i != 0; i--)       /* Max waiting : NCR       */
            {
                Ret = R_mmc_Sync_Rx((natural_uint_t)1, gMmc_ResBuf);
                if ((*gMmc_ResBuf & 0x80U) == 0x00)  /* Response top byte receive     */
                {
                    break;
                }
            }
            if (i == 0)                              /* Response non-detection      */
            {
                R_mmc_Sync_DummyClk(MMC_NRC_MIN);    /* Waiting for NRC        */
                R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
                return MMC_ERR_OTHER;
            }

            /* Response receive after 2byte */
            if (ResSize > 1)
            {
                Ret = R_mmc_Sync_Rx((natural_uint_t)ResSize - 1, &gMmc_ResBuf[1]);
                if (Ret < MMC_OK)
                {
                    R_mmc_Sync_DummyClk(MMC_NRC_MIN);  /* Waiting for NRC        */
                    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
                    return Ret;
                }
            }

            /* Response check */
            if (gMmc_CmdBuf[MMC_CMD_CMD_IDX] == MMC_CMD12)
            {
                /* CMD12 respons check ?      */
                if ((gMmc_ResBuf[MMC_RES_R1IDX] & MMC_RES1_CHKDATA2) == 0x00)
                {
                    /* Response R1 OK        */
                    return MMC_OK;
                }
            }
            else
            {
                if ((gMmc_ResBuf[MMC_RES_R1IDX] & MMC_RES1_CHKDATA) == 0x00)
                {
                    /* Response R1 OK        */
                    return MMC_OK;
                }
            }
        }
    }
    if ((gMmc_ResBuf[MMC_RES_R1IDX] & 0x01) == 0x01)  /* Idle state error        */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_IDLE;
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_OTHER;
}


/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_DummyClk(natural_uint_t TxCnt)
* Function Name: R_mmc_Sync_DummyClk
* Description  : Output the dummy clock for the appointed number of bytes.
* Argument     : natural_uint_t TxCnt ; Number of send bytes
* Return Value : MMC_OK               ; Success
*              : MMC_ERR_HARD         ; Hardware Error
******************************************************************************/
int16_t R_mmc_Sync_DummyClk(natural_uint_t TxCnt)
{
    int16_t Ret;

    Ret = R_mmc_Sync_MultTx(TxCnt, (uint8_t *)gMmcDummyData);
    return Ret;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_Chk_RxData(uint32_t RtyCnt, uint8_t ChkData)
* Function Name: R_mmc_Sync_Chk_RxData
* Description  : Receive data of 1byte and check whether reception data accord with designated data.
*              : When data do not accord, it repeats itself for the prescribed number of times.
* Argument     : uint32_t RtyCnt  ; Retry count
*              : uint8_t ChkData  ; Comparison data
* Return Value : MMC_OK           ; Success
*              : MMC_ERR_HARD     ; Hardware Error
*              : MMC_ERR_OTHER    ; Other Error
******************************************************************************/
int16_t R_mmc_Sync_Chk_RxData(uint32_t RtyCnt, uint8_t ChkData)
{
    uint8_t    RxBuf;                       /* Receive temp buffer       */

    int16_t    Ret;

    for (; RtyCnt != 0; RtyCnt--)           /* Re-try loop         */
    {
        Ret = R_mmc_Sync_Rx(1, &RxBuf);     /* 1byte data receive       */
        if (Ret < MMC_OK)
        {
            R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
            return Ret;
        }

        if (ChkData == RxBuf)
        {
            return MMC_OK;
        }
    }

// mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_OTHER;
}

/*----------------------------------------------------------------------------------------------*/
/* CRC calculation processing                                                                   */
/*----------------------------------------------------------------------------------------------*/
/******************************************************************************
* Declaration  : uint16_t R_mmc_CrcCcitt_Reg(uint8_t *pData, uint16_t CrcCnt)
* Function Name: R_mmc_CrcCcitt_Reg
* Description  : Calculate CRC-CCITT of specified data (x16+x12+x5+1)
* Argument     : uint8_t *pData  ; calculation data pointer
*              : uint8_t CrcCnt  ; Number of the data to calculate
* Return Value : Calculated CRC-CCITT value
******************************************************************************/
uint16_t R_mmc_CrcCcitt_Reg(uint8_t *pData, uint16_t CrcCnt)
{
    natural_uint_t   i;

    MMC_CRC_CLR();

    for (i = CrcCnt; i != 0; i--)
    {
        MMC_CRC_SET(*pData);                /* CRC-CCITT calculation      */
        pData++;
    }

    /* Endian conversion */
    return R_ExchgCrc();
}

/******************************************************************************
* Declaration  : STATIC uint8_t R_mmc_Crc7_Cmd(uint8_t *pData)
* Function Name: R_mmc_Crc7_Cmd
* Description  : Calculate CRC7 of specified command data (x7+x3+1)
* Argument     : uint8_t *pData  ; calculation data pointer
* Return Value : Calculated CRC-CCITT value
******************************************************************************/
STATIC uint8_t R_mmc_Crc7_Cmd(uint8_t *pData)
{
    uint8_t    CrcData = 0x00;

    CrcData = T_Crc7[CrcData ^ *pData];
    pData++;
    CrcData = T_Crc7[CrcData ^ *pData];
    pData++;
    CrcData = T_Crc7[CrcData ^ *pData];
    pData++;
    CrcData = T_Crc7[CrcData ^ *pData];
    pData++;
    CrcData = T_Crc7[CrcData ^ *pData];

    CrcData |= 0x01U;                       /* Make last 1bit 1 (CMD Stop bit)    */

    return CrcData;
}

/******************************************************************************
* Declaration  : uint8_t R_mmc_Crc7_Reg(uint8_t *pData, natural_uint_t CrcCnt)
* Function Name: R_mmc_Crc7_Reg
* Description  : Calculate CRC7 of specified data (x7+x3+1)
* Argument     : uint8_t *pData        ; calculation data pointer
*              : natural_uint_t CrcCnt ; Number of the data to calculate
* Return Value : Calculated CRC-CCITT value
******************************************************************************/
uint8_t R_mmc_Crc7_Reg(uint8_t *pData, natural_uint_t CrcCnt)
{
    uint8_t    CrcData = 0x00;

    for (; CrcCnt != 0; CrcCnt--)
    {
        CrcData = T_Crc7[CrcData ^ *pData];
        pData++;
    }

    CrcData |= 0x01U;                       /* Make last 1bit 1 (CMD Stop bit)    */

    return CrcData;
}

/******************************************************************************
* Declaration  : uint16_t R_ExchgCrc(void)
* Function Name: R_ExchgCrc
* Description  : Convert calculated CRC into little endian to compare it with received CRC .
* Argument     : None
* Return Value : Conversion data
******************************************************************************/
uint16_t R_ExchgCrc(void)
{
#ifdef MMC_CRC_HARD
    uint16_t    CrcData;
#ifndef MMC_CRC_MSBF
    uint16_t    CrcTemp;
#endif /* #ifndef MMC_CRC_MSBF */

    MMC_CRC_GET(CrcData);
#ifndef MMC_CRC_MSBF
    CrcTemp  = T_ExchgBit[CrcData & 0x00FFU];
    CrcData  = T_ExchgBit[(CrcData >> 8) & 0x00FFU];
    CrcData |= (CrcTemp << 8);
#endif /* #ifndef MMC_CRC_MSBF */
    R_mtl_ShortPoke((void *)&CrcData, CrcData);
    return CrcData;

#else /* #ifdef MMC_CRC_HARD */
    R_mtl_ShortPoke((void *)&gMmc_CrcData.us, gMmc_CrcData.us);
    return gMmc_CrcData.us;
#endif /* #ifdef MMC_CRC_HARD */
}

/******************************************************************************
* Declaration  : uint16_t R_mmc_ExchgShort(uint16_t ChgData)
* Function Name: R_mmc_ExchgShort
* Description  : convert the data of the uint16_t type into big endian from little endian.
* Argument     : uint16_t ChgData : Data before conversion
* Return Value : Data after conversion
******************************************************************************/
uint16_t R_mmc_ExchgShort(uint16_t ChgData)
{
#ifdef MTL_MCU_LITTLE
    MMC_EXCHG_SHORT  Tmp, Ret;

    Tmp.us = ChgData;
    Ret.uc[0] = Tmp.uc[1];
    Ret.uc[1] = Tmp.uc[0];

    return Ret.us;

#else /* #ifdef MTL_MCU_LITTLE */
    return ChgData;
#endif /* #ifdef MTL_MCU_LITTLE */
}

/******************************************************************************
* Declaration  : uint32_t R_mmc_ExchgLong(uint32_t ChgData)
* Function Name: R_mmc_ExchgLong
* Description  : convert the data of the uint32_t type into big endian from little endian.
* Argument     : uint32_t ChgData : Data before conversion
* Return Value : Data after conversion
******************************************************************************/
uint32_t R_mmc_ExchgLong(uint32_t ChgData)
{
#ifdef MTL_MCU_LITTLE
    MMC_EXCHG_LONG  Tmp, Ret;

    Tmp.ul = ChgData;
    Ret.uc[0] = Tmp.uc[3];
    Ret.uc[1] = Tmp.uc[2];
    Ret.uc[2] = Tmp.uc[1];
    Ret.uc[3] = Tmp.uc[0];

    return Ret.ul;

#else /* #ifdef MTL_MCU_LITTLE */
    return ChgData;
#endif /* #ifdef MTL_MCU_LITTLE */
}
