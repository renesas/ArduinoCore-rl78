/*""FILE COMMENT""*******************************************************************
* File Name     : r_mmc_sub.h
* Version       : 1.23B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description  : MMC driver sub module common definitions
*************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 27.06.2006 Ver1.13
*              : 21.02.2007 Ver1.14
*              : 21.06.2007 Ver1.15
*              : 10.12.2007 Ver1.20
*              : 17.01.2008 Ver1.21
*              : 29.01.2008 Ver1.22
*              : 26.03.2008 Ver1.23
*              : 25.06.2010 Ver1.23A
*              : 02.03.2012 Ver1.23B
*""FILE COMMENT END""***************************************************************/
#ifndef __MMC_SUB_H__
#define __MMC_SUB_H__

/************************************************************************************************/
/* Definitions                                                                                  */
/************************************************************************************************/
/*--------- Definitions of response-related ----------*/
#define MMC_RES_R1IDX        0                    /* R1 response index                          */
#define MMC_RES_R2IDX        1                    /* R2 response index                          */
#define MMC_RES_R3IDX        1                    /* R3 response index                          */

/*------ Definitions of CSD information-related ------*/
#define MMC_READ_BLK_LEN_MIN  8                   /* READ_BLK_LEN minimum                       */
#define MMC_READ_BLK_LEN_MAX 12                   /* READ_BLK_LEN maximum                       */
#define MMC_C_SIZE_MULT_MAX   8                   /* C_SIZE_MULT maximum                        */
#define MMC_CSD_STRUCTURE_V1 (uint8_t)0x00        /* CSD structure version 1.0                  */
#define MMC_CSD_STRUCTURE_V2 (uint8_t)0x40        /* CSD structure version 2.0                  */

/*-------------- Definitions of command --------------*/
/* Definitions of common command */      /*      SPI   MMC   */
#define MMC_CMD0             (uint8_t)(0x40U |  0U)
#define MMC_CMD2             (uint8_t)(0x40U |  2U)
#define MMC_CMD3             (uint8_t)(0x40U |  3U)
#define MMC_CMD7             (uint8_t)(0x40U |  7U)
#define MMC_CMD9             (uint8_t)(0x40U |  9U)
#define MMC_CMD10            (uint8_t)(0x40U | 10U)
#define MMC_CMD12            (uint8_t)(0x40U | 12U)
#define MMC_CMD13            (uint8_t)(0x40U | 13U)
#define MMC_CMD17            (uint8_t)(0x40U | 17U)
#define MMC_CMD18            (uint8_t)(0x40U | 18U)
#define MMC_CMD24            (uint8_t)(0x40U | 24U)
#define MMC_CMD25            (uint8_t)(0x40U | 25U)
#define MMC_CMD58            (uint8_t)(0x40U | 58U)
#define MMC_CMD59            (uint8_t)(0x40U | 59U)

/*----------- Definitions of response size -----------*/
#define MMC_R1_SIZE          (natural_uint_t)1    /* Response R1                                */
#define MMC_R1B_SIZE         (natural_uint_t)1    /* Response R1b                               */
#define MMC_R2_SIZE          (natural_uint_t)2    /* Response R2                                */
#define MMC_R3_SIZE          (natural_uint_t)5    /* Response R3                                */
#define MMC_R7_SIZE          (natural_uint_t)5    /* Response R7                                */
#define MMC_MAX_RES_SIZE     (natural_uint_t)5    /* Max response size                          */

/*------------ Definitions of CRC option -------------*/
#define MMC_CRC_OP_ON        (uint32_t)0x00000001 /* CRC option ON                              */
#define MMC_CRC_OP_OFF       (uint32_t)0x00000000 /* CRC option OFF                             */

/*- Definitions of CSD/CID/OCR data buffer existence -*/
#define MMC_REGBUF_USED                           /* CSD/CID/OCR data buffer use                */

/************************************************************************************************/
/* Unions                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Structs                                                                                      */
/************************************************************************************************/
/* Definition of CSD information structure */
typedef struct
{
    uint32_t Taac;                                /* Asynchronous data access time : unit= us   */
    uint16_t Nsac;                                /* Synchronization data access time           */
    uint32_t Nac;                                 /* Data access time                           */
    uint32_t MemSize;                             /* Card capacity                              */
    uint32_t MaxBlkNum;                           /* The number of the max blocks               */
    uint8_t  WP;                                  /* Write-protection information               */
    uint8_t  Reserve[3];
} CSD_INFO;                                       /* total 24byte                               */

/************************************************************************************************/
/* Externs                                                                                      */
/************************************************************************************************/
extern const uint8_t T_Mmc_SlotNum[1];            /* The number of slots                        */

extern uint8_t    gMmc_Media[MMC_SLOT_NUM];       /* Card classification                        */
extern uint8_t    gMmc_WP[MMC_SLOT_NUM];          /* Write-protection information               */
extern uint16_t   gMmc_AddrRev[MMC_SLOT_NUM];     /* Read/Write address revision value          */
extern CSD_INFO   gMmc_CsdInfo[MMC_SLOT_NUM];     /* CSD information                            */
#ifdef MMC_REGBUF_USED
extern uint8_t    gMmc_CsdBuf[MMC_SLOT_NUM][MMC_CSD_SIZE]; /* CSD receive buffer                */
extern uint8_t    gMmc_CidBuf[MMC_SLOT_NUM][MMC_CID_SIZE]; /* CID receive buffer                */
extern uint8_t    gMmc_OcrBuf[MMC_SLOT_NUM][MMC_OCR_SIZE]; /* OCR receive buffer                */
#else /* #ifdef MMC_REGBUF_USED */
extern uint8_t    gMmc_RegBuf[MMC_SLOT_NUM][MMC_CSD_SIZE]; /* CSD/CID/OCR receive buffer        */
#endif /* #ifdef MMC_REGBUF_USED */

/************************************************************************************************/
/* Macros                                                                                       */
/************************************************************************************************/
/*--------- Command transmission processing ----------*/
/* Common command */     /*                   Cmd          Arg          ResSize           Rty         */
#define mmc_Cmd0()       R_mmc_Send_Cmd_Spi(MMC_CMD0,  (uint32_t)0,   MMC_R1_SIZE,  (natural_uint_t)64 )
#define mmc_Cmd9()       R_mmc_Send_Cmd_Spi(MMC_CMD9,  (uint32_t)0,   MMC_R1_SIZE,  (natural_uint_t) 1 )
#define mmc_Cmd10()      R_mmc_Send_Cmd_Spi(MMC_CMD10, (uint32_t)0,   MMC_R1_SIZE,  (natural_uint_t) 1 )
#define mmc_Cmd12()      R_mmc_Send_Cmd_Spi(MMC_CMD12, (uint32_t)0,   MMC_R1B_SIZE, (natural_uint_t) 2 )
#define mmc_Cmd13()      R_mmc_Send_Cmd_Spi(MMC_CMD13, (uint32_t)0,   MMC_R2_SIZE,  (natural_uint_t) 1 )
#define mmc_Cmd17(Arg)   R_mmc_Send_Cmd_Spi(MMC_CMD17, (uint32_t)Arg, MMC_R1_SIZE,  (natural_uint_t) 1 )
#define mmc_Cmd18(Arg)   R_mmc_Send_Cmd_Spi(MMC_CMD18, (uint32_t)Arg, MMC_R1_SIZE,  (natural_uint_t) 1 )
#define mmc_Cmd24(Arg)   R_mmc_Send_Cmd_Spi(MMC_CMD24, (uint32_t)Arg, MMC_R1_SIZE,  (natural_uint_t) 1 )
#define mmc_Cmd25(Arg)   R_mmc_Send_Cmd_Spi(MMC_CMD25, (uint32_t)Arg, MMC_R1_SIZE,  (natural_uint_t) 1 )
#define mmc_Cmd58()      R_mmc_Send_Cmd_Spi(MMC_CMD58, (uint32_t)0,   MMC_R3_SIZE,  (natural_uint_t)64 )
#define mmc_Cmd59(Arg)   R_mmc_Send_Cmd_Spi(MMC_CMD59, (uint32_t)Arg, MMC_R1_SIZE,  (natural_uint_t)64 )

/************************************************************************************************/
/* Prototypes                                                                                   */
/************************************************************************************************/
void    R_mmc_Init_Sfr(void);                     /* SFR initialization                         */
void    R_mmc_Init_Ram(uint8_t SlotNo);           /* RAM initialization                         */
int16_t R_mmc_Init_Media(uint8_t SlotNo);         /* Media initialization                       */
uint8_t R_mmc_Get_Wp(uint8_t SlotNo);             /* Write-protection state acquisition         */
int16_t R_mmc_Get_Csd(uint8_t *pCsdBuf);          /* CSD acquisition                            */
int16_t R_mmc_Get_Cid(uint8_t *pCidBuf);          /* CID acquisition                            */
int16_t R_mmc_Get_Ocr(uint8_t *pOcrBuf);          /* OCR acquisition                            */
int16_t R_mmc_Read_Start(uint8_t SlotNo, uint32_t BlkNo);  /* Reading start                     */
int16_t R_mmc_Read_BlkData(uint8_t SlotNo, uint8_t *pData, uint8_t Mode); /* 1 block reading    */
int16_t R_mmc_Read_End(void);                     /* Reading end                                */
#ifdef MMC_SBLK_CMD
int16_t R_mmc_SBRead_Start(uint8_t SlotNo, uint32_t BlkNo); /* Single block reading start       */
int16_t R_mmc_SBRead_End(void);                   /* Single block reading end                   */
#endif /* #ifdef MMC_SBLK_CMD */
int16_t R_mmc_Write_Start(uint8_t SlotNo, uint32_t BlkNo); /* Writing start                     */
int16_t R_mmc_Write_BlkData(uint8_t *pData, uint8_t Mode); /* 1 block writing                   */
int16_t R_mmc_Write_End(void);                    /* Writing end                                */
#ifdef MMC_SBLK_CMD
int16_t R_mmc_SBWrite_Start(uint8_t SlotNo, uint32_t BlkNo); /* Single block writing start      */
int16_t R_mmc_SBWrite_BlkData(uint8_t *pData, uint8_t Mode); /* Single block writing            */

int16_t R_mmc_SBWrite_End(void);                  /* Single block writing end                   */
#endif /* #ifdef MMC_SBLK_CMD */

#ifdef MMC_SUPPORT_MMC
int16_t R_mmc_Reset_Mmc(uint8_t SlotNo);          /* MMC reset         */
#else /* #ifdef MMC_SUPPORT_MMC */
#define R_mmc_Reset_Mmc(SlotNo) MMC_ERR_OTHER
#endif /* #ifdef MMC_SUPPORT_MMC */

uint8_t R_mmc_Get_Detect_Status(uint8_t SlotNo);
#endif /* __MMC_SUB_H__ */
