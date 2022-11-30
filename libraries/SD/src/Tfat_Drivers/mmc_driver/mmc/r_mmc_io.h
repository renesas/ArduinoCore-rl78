/*""FILE COMMENT""*******************************************************************
* File Name     : r_mmc_io.h
* Version       : 1.23B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description   : MMC driver I/O module common definitions
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
#ifndef __MMC_IO_H__
#define __MMC_IO_H__

/************************************************************************************************/
/* Definitions                                                                                  */
/************************************************************************************************/

/*----------- Definitions of port control ------------*/
#define MMC_HI            (uint8_t)0x01               /* Port "H"                               */
#define MMC_LOW           (uint8_t)0x00               /* Port "L"                               */
#define MMC_OUT           (uint8_t)0x01               /* Port output setting                    */
#define MMC_IN            (uint8_t)0x00               /* Port input setting                     */
#define MMC_NOT_CONNECT   (uint8_t)0xFF               /* Pin not conection                      */

/*------- Definitions of software timer value --------*/
/* Transmit&receive waiting time */
#define MMC_TAAC_WAIT     (natural_uint_t)8000        /* TAAC waiting time           80* 1ms =  80ms */
#define MMC_READY_WAIT    (natural_uint_t)50000       /* Write busy waiting time  50000*10us = 500ms */

/* Access time */
#define MMC_T_REGSET_WAIT (natural_uint_t)MTL_T_10US  /* Register setting waiting time          */
#define MMC_T_TAAC_WAIT   (natural_uint_t)MTL_T_10US  /* TAAC waiting polling time              */
#define MMC_T_READY_WAIT  (natural_uint_t)MTL_T_10US  /* Write busy completion waiting polling time */

/*------------- Each timing definitions --------------*/
/* unit: 8clock cycles */
#define MMC_NRC_MIN       (natural_uint_t)1           /* NRC minimum                            */
#define MMC_NCR_MIN       (natural_uint_t)1           /* NCR minimum                            */
#define MMC_NCR_MAX       (natural_uint_t)8           /* NCR maximum                            */
#define MMC_NCX_MAX       (natural_uint_t)9           /* NCX maximum                            */
#define MMC_NAC_MIN       (natural_uint_t)1           /* NAC minimum                            */
#define MMC_NWR_MIN       (natural_uint_t)1           /* NWR minimum                            */
#define MMC_NBR_MIN       (natural_uint_t)1           /* NBR minimum                            */
#define MMC_SPI_SEL       (natural_uint_t)16          /* SPI mode select                        */
#define MMC_DUMMY_MAXLEN  MMC_SPI_SEL                 /* DummyClk maximam length                */

/*---- Definitions of resource used for debugging ----*/
//#define MMC_OPTION_TEST                             /* Resource used for debugging is effective  */

#ifdef MMC_OPTION_TEST
#undef MMC_CRC_SOFT                                   /* Invalid                                */
#undef MMC_CRC_HARD                                   /* Invalid                                */
#undef MMC_CRC_MSBF                                   /* Invalid                                */
#undef MMC_SYNC_LSBF                                  /* Invalid                                */

//#define MMC_CRC_SOFT                                /* Encode by soft CRC (ROM table used)    */
//#define MMC_CRC_HARD                                /* Encode by hard CRC                     */
//#define MMC_CRC_MSBF                                /* CRC MSB first                          */
//#define MMC_SYNC_LSBF                               /* SYNC LSB first                         */
#endif /* #ifdef MMC_OPTION_TEST */

/*- Definitions of SYNC overrun error check existence -*/
//#define MMC_SYNC_ORERR                              /* SYNC overrun error check invalid       */


#ifdef MMC_SYNC_LSBF
#define MMC_BIT_EXCHG(Data) do {                      /* Data bit upper lower exchange          */ \
        Data = T_ExchgBit[Data];                                                                   \
    } while (0)
#else /* #ifdef MMC_SYNC_LSBF */
#define MMC_BIT_EXCHG(Data)
#endif /* #ifdef MMC_SYNC_LSBF */

/************************************************************************************************/
/* Unions                                                                                       */
/************************************************************************************************/
/* uint32_t <-> uint8_t conversion */
typedef union
{
    uint32_t ul;
    uint8_t  uc[4];
} MMC_EXCHG_LONG;                                     /* total 4byte                            */

/* uint16_t <-> uint8_t conversion */
typedef union
{
    uint16_t us;
    uint8_t  uc[2];
} MMC_EXCHG_SHORT;                                    /* total 2byte                            */

/************************************************************************************************/
/* Structs                                                                                      */
/************************************************************************************************/

/************************************************************************************************/
/* Externs                                                                                      */
/************************************************************************************************/
extern uint8_t                gMmc_ResBuf[];         /* Card response receive buffer            */
extern MMC_EXCHG_SHORT        gMmc_CrcData;
extern const uint8_t          T_ExchgBit[];
extern const uint16_t         T_Crc_Ccitt[];
extern const uint8_t          gMmcDummyData[];
//#ifdef MMC_DTC_USED
//extern uint32_t             gDtcVctTbl[];
//extern MMC_DTCALLOC_FULL_t  gDtcAlloc[];
//#endif
/************************************************************************************************/
/* Macros                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Prototypes                                                                                   */
/************************************************************************************************/
/* SPI mode command transmission    */
int16_t   R_mmc_Send_Cmd_Spi(uint8_t Cmd, uint32_t Arg, natural_uint_t ResSize, natural_uint_t RtyCnt);

void      R_mmc_Sync_Disable(void);                                 /* SYNC disable setting     */
void      R_mmc_Sync_Enable(uint8_t flag, uint16_t bitrate);        /* SYNC enable setting      */
int16_t   R_mmc_Sync_MultTx(natural_uint_t TxCnt, uint8_t *pData);  /* SYNC transmission        */
int16_t   R_mmc_Sync_Rx(natural_uint_t RxCnt, uint8_t *pData);      /* SYNC receive             */
int16_t   R_mmc_Sync_Chk_RxData(uint32_t RtyCnt, uint8_t ChkData);  /* SYNC receive data check  */

void      R_mmc_Init_IO(void);                                     /* Port initialization       */
void      R_mmc_Init_Port(uint8_t SlotNo);                         /* Port initialization       */
void      R_mmc_Open_Port(uint8_t SlotNo);                         /* Port open                 */
uint8_t   R_mmc_Get_Detect(uint8_t SlotNo);                        /* Detect check              */
int16_t   R_mmc_Sync_DummyClk(natural_uint_t TxCnt);           /* Dummy clock transmission      */

int16_t   R_mmc_Sync_DataOut(uint8_t *pData);                      /* Data transmission         */
int16_t   R_mmc_Sync_DataIn(uint8_t *pData);                       /* Data receive              */

uint16_t  R_mmc_CrcCcitt_Reg(uint8_t *pData, uint16_t CrcCnt);  /* CRC-CCITT calculation for register   */

uint8_t   R_mmc_Crc7_Reg(uint8_t *pData, natural_uint_t CrcCnt);  /* CRC7 calculation for register    */
uint16_t  R_mmc_ExchgShort(uint16_t ChgData);               /* uint16_t type endian exchange    */
uint32_t  R_mmc_ExchgLong(uint32_t ChgData);                /* uint32_t type endian exchange    */

extern    uint16_t R_ExchgCrc(void);      /* Calculation CRC data conversion  */

#endif /* __MMC_IO_H__ */
