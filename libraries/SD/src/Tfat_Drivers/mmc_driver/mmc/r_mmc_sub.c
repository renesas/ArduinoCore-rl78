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
* File Name     : r_mmc_sub.c
* Version       : 1.23B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description   : MMC driver SPI mode sub module
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
#include "r_mtl_com.h"         /* Renesas tool common definitions    */
#include "r_mmc.h"          /* MMC driver common definitions    */
#include "r_mmc_sub.h"         /* MMC driver sub module definitions   */
#include "r_mmc_io.h"         /* MMC driver I/O module definitions   */
#include "r_mmc_sfr.h"         /* MMC driver SFR definitions     */

/************************************************************************************************/
/* Definitions                                                                                  */
/************************************************************************************************/
#define MMC_FID       (8UL << 6 | 2UL)

/*------------ Definitions of data token -------------*/
#define MMC_DTOKEN_SIZE     (uint16_t)1     /* Data token size        */
#define MMC_DTOKEN_STR_SR   (uint8_t)0xFE   /* Start block : Single block read    */
#define MMC_DTOKEN_STR_MR   (uint8_t)0xFE   /* Start block : Multi  block read    */
#define MMC_DTOKEN_STR_SW   (uint8_t)0xFE   /* Start block : Single block write   */
#define MMC_DTOKEN_STR_MW   (uint8_t)0xFC   /* Start block : Multi  block write   */
#define MMC_DTOKEN_STP_MW   (uint8_t)0xFD   /* Stop tran : Multi  block write   */

/*----------- Definitions of data response -----------*/
#define MMC_DATARES_SIZE    (uint16_t)1     /* Data response size       */
#define MMC_DATARES_MASK    (uint8_t)0x1F   /* Data response mask data      */
#define MMC_DATARES_OK      (uint8_t)0x05   /* Data response : OK      */
#define MMC_DATARES_CRCERR  (uint8_t)0x0B   /* Data response : CRC error     */
#define MMC_DATARES_WERR    (uint8_t)0x0D   /* Data response : Write error    */

/*--------------- Definitions of ready ---------------*/
#define MMC_READY_SIZE      (uint16_t)1     /* Ready size         */
#define MMC_READY_DATA      (uint8_t)0xFF   /* Ready data         */

/*------ Definitions of response R2 check data -------*/
#define MMC_RES2_CHKDATA    (uint8_t)0x04   /* Status error         */

/*-------------- Definitions of CSD/CID --------------*/
#define MMC_CSD_CRC7IDX     15              /* CSD CRC7 index        */
#define MMC_CID_CRC7IDX     15              /* CID CRC7 index        */

/*------------ Definitions of OCR fields -------------*/
#define MMC_OCR_BUSY        (uint8_t)0x80   /* Card power up status bit (busy)    */

/************************************************************************************************/
/* Unions                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Structs                                                                                      */
/************************************************************************************************/

/************************************************************************************************/
/* Globals                                                                                      */
/************************************************************************************************/
/*""VAL DEF""*/
const uint8_t   T_Mmc_SlotNum[] = { MMC_SLOT_NUM };  /* Number of slots                         */
/*""VAL DEF END""*/

/*""VAL DEF""*/
uint8_t     gMmc_Media[MMC_SLOT_NUM];                /* Card classification                     */
uint8_t     gMmc_WP[MMC_SLOT_NUM];                   /* Write-protection information            */
uint16_t    gMmc_AddrRev[MMC_SLOT_NUM];              /* Read/Write address revision value       */
CSD_INFO    gMmc_CsdInfo[MMC_SLOT_NUM];              /* CSD information                         */
#ifdef MMC_REGBUF_USED
uint8_t     gMmc_CsdBuf[MMC_SLOT_NUM][MMC_CSD_SIZE]; /* CSD receive buffer                      */
uint8_t     gMmc_CidBuf[MMC_SLOT_NUM][MMC_CID_SIZE]; /* CID receive buffer                      */
uint8_t     gMmc_OcrBuf[MMC_SLOT_NUM][MMC_OCR_SIZE]; /* OCR receive buffer                      */
#else /* #ifdef MMC_REGBUF_USED */
uint8_t     gMmc_RegBuf[MMC_SLOT_NUM][MMC_CSD_SIZE]; /* CSD/CID/OCR receive buffer              */
#endif /* #ifdef MMC_REGBUF_USED */
/*""VAL DEF END""*/

/************************************************************************************************/
/* Macros                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Prototypes                                                                                   */
/************************************************************************************************/
STATIC int16_t R_mmc_Chk_Sts(void);                  /* Status check                            */
STATIC int16_t R_mmc_Wait_Ready(void);               /* Waiting busy cancellation               */
STATIC int16_t R_mmc_Chk_DataRes(void);              /* Data response check                     */

/*----------------------------------------------------------------------------------------------*/
/* Initialization                                                                               */
/*----------------------------------------------------------------------------------------------*/



/******************************************************************************
* Declaration  : void R_mmc_Init_Ram(uint8_t SlotNo)
* Function Name: R_mmc_Init_Ram
* Description  : Initialize the RAM to control a specified slot.
* Argument     : uint8_t    SlotNo : Slot Number
* Return Value : None
******************************************************************************/
void R_mmc_Init_Ram(uint8_t SlotNo)
{
    gMmc_Media[SlotNo] = MMC_CARD_UNDETECT;                    /* Card is not found setting     */
    gMmc_WP[SlotNo]    = MMC_W_PROTECT_SOFT;                   /* Write-protection setting      */

    R_mtl_memset((void *)&gMmc_CsdInfo[SlotNo], 0, sizeof(CSD_INFO)); /* CSD information clear  */

#ifdef MMC_REGBUF_USED
    R_mtl_memset((void *)&gMmc_CsdBuf[SlotNo], 0, (uint16_t)MMC_CSD_SIZE); /* CSD receive buffer clear */
    R_mtl_memset((void *)&gMmc_CidBuf[SlotNo], 0, (uint16_t)MMC_CID_SIZE); /* CID receive buffer clear */
    R_mtl_memset((void *)&gMmc_OcrBuf[SlotNo], 0, (uint16_t)MMC_OCR_SIZE); /* OCR receive buffer clear */
#endif /* #ifdef MMC_REGBUF_USED */
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Init_Media(uint8_t SlotNo)
* Function Name: R_mmc_Init_Media
* Description  : Media initialization processing.
*              : Execute SPI mode initialization sequence of the media.
*              : Execute MMC reset processing.
*              : Perform a status check.
*              : Turn on a CRC option.
* Argument     : uint8_t    SlotNo : Slot Number
* Return Value : MMC_OK            ; Success
*              : MMC_ERR_HARD      ; Hardware Error
*              : MMC_ERR_CRC       ; CRC Error
*              : MMC_ERR_IDLE      ; Idle status error
*              : MMC_ERR_OTHER     ; Other Error
******************************************************************************/
int16_t R_mmc_Init_Media(uint8_t SlotNo)
{
    int16_t    Ret;

    R_mmc_Sync_Enable(1, MMC_UBRG_IDENTIFICATION);  /* SYNC enable setting       */

    /* SPI mode select */
    MMC_SET_CS(SlotNo, MMC_HI);                     /* CS "H"          */
    R_mmc_Sync_DummyClk(MMC_SPI_SEL);

    MMC_SET_CS(SlotNo, MMC_LOW);                    /* CS "L"          */

    /* Media reset */                               /* Supports MMC only.       */
    Ret = R_mmc_Reset_Mmc(SlotNo);                  /* MMC reset         */
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Status check */
    Ret = R_mmc_Chk_Sts();
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* CRC option setting */
    Ret = mmc_Cmd59(R_mmc_ExchgLong(MMC_CRC_OP_ON));
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Waiting busy cancellation */
    Ret = R_mmc_Wait_Ready();
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    return MMC_OK;
}

/******************************************************************************
* Declaration  : uint8_t R_mmc_Get_Wp(uint8_t SlotNo)
* Function Name: R_mmc_Get_Wp
* Description  : Return WP setting state.
* Argument     : uint8_t    SlotNo : Slot Number
* Return Value : WP setting state.
******************************************************************************/
uint8_t R_mmc_Get_Wp(uint8_t SlotNo)
{
    return gMmc_WP[SlotNo];
}

/*----------------------------------------------------------------------------------------------*/
/* MMC information acquisition                                                                  */
/*----------------------------------------------------------------------------------------------*/

/******************************************************************************
* Declaration  : int16_t R_mmc_Get_Csd(uint8_t *pCsdBuf)
* Function Name: R_mmc_Get_Csd
* Description  : CSD acquisition processing
* Argument     : uint8_t *pCsdBuf    : CSD receive buffer pointer
* Return Value : MMC_OK              ; Success
*              : MMC_ERR_HARD        ; Hardware Error
*              : MMC_ERR_CRC         ; CRC Error
*              : MMC_ERR_IDLE        ; Idle status error
*              : MMC_ERR_OTHER       ; Other Error
******************************************************************************/
int16_t R_mmc_Get_Csd(uint8_t *pCsdBuf)
{
    MMC_EXCHG_SHORT  CrcCcittBuf;      /* Receive CRC-CCITT data storage buffer  */
    uint16_t         CrcCcittData;     /* Calculation CRC-CCITT data storage buffer */
    uint8_t          Crc7Data;         /* Calculation CRC7 data storage buffer   */
    int16_t          Ret;

    /* CSD send request command transmission */
    Ret = mmc_Cmd9();
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Waiting for start block (NCX max = 72cycle) */
    Ret = R_mmc_Sync_Chk_RxData((uint32_t)MMC_NCX_MAX, MMC_DTOKEN_STR_SR);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_HARD;
    }

    /* CSD receive */
    Ret = R_mmc_Sync_Rx(MMC_CSD_SIZE, pCsdBuf);
    if (Ret < MMC_OK)
    {
        R_mtl_memset((void *)pCsdBuf, 0, (uint16_t)MMC_CSD_SIZE); /* CSD receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* CRC-CCITT receive */
    Ret = R_mmc_Sync_Rx((natural_uint_t)1, (uint8_t *) & CrcCcittBuf.uc[1]);
    if (Ret < MMC_OK)
    {
        R_mtl_memset((void *)pCsdBuf, 0, (uint16_t)MMC_CSD_SIZE); /* CSD receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }
    Ret = R_mmc_Sync_Rx((natural_uint_t)1, (uint8_t *) & CrcCcittBuf.uc[0]);
    if (Ret < MMC_OK)
    {
        R_mtl_memset((void *)pCsdBuf, 0, (uint16_t)MMC_CSD_SIZE); /* CSD receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* CRC7 calculation */
    Crc7Data = R_mmc_Crc7_Reg(pCsdBuf, (natural_uint_t)(MMC_CSD_SIZE - 1));

    /* CRC7 check */
    if (Crc7Data != pCsdBuf[MMC_CSD_CRC7IDX])
    {
        R_mtl_memset((void *)pCsdBuf, 0, (uint16_t)MMC_CSD_SIZE); /* CSD receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_CRC;
    }

    /* CRC-CCITT calculation */
    CrcCcittData = R_mmc_CrcCcitt_Reg(pCsdBuf, MMC_CSD_SIZE);

    /* CRC-CCITT check */
    if (CrcCcittData != CrcCcittBuf.us)
    {
        R_mtl_memset((void *)pCsdBuf, 0, (uint16_t)MMC_CSD_SIZE); /* CSD receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_CRC;
    }

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Get_Cid(uint8_t *pCidBuf)
* Function Name: R_mmc_Get_Cid
* Description  : CID acquisition processing
* Argument     : uint8_t *pCidBuf    : CID receive buffer pointer
* Return Value : MMC_OK              ; Success
*              : MMC_ERR_HARD        ; Hardware Error
*              : MMC_ERR_CRC         ; CRC Error
*              : MMC_ERR_IDLE        ; Idle status error
*              : MMC_ERR_OTHER       ; Other Error
******************************************************************************/
int16_t R_mmc_Get_Cid(uint8_t *pCidBuf)
{
    MMC_EXCHG_SHORT  CrcCcittBuf;      /* Receive CRC-CCITT data storage buffer  */
    uint16_t         CrcCcittData;     /* Calculation CRC-CCITT data storage buffer */
    uint8_t          Crc7Data;         /* Calculation CRC7 data storage buffer   */
    int16_t          Ret;

    /* CID send request command transmission */
    Ret = mmc_Cmd10();
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Waiting for start block (NCX max = 72cycle) */
    Ret = R_mmc_Sync_Chk_RxData((uint32_t)MMC_NCX_MAX, MMC_DTOKEN_STR_SR);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_HARD;
    }

    /* CID receive */
    Ret = R_mmc_Sync_Rx(MMC_CID_SIZE, pCidBuf);
    if (Ret < MMC_OK)
    {
        R_mtl_memset((void *)pCidBuf, 0, (uint16_t)MMC_CID_SIZE); /* CID receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* CRC-CCITT receive */
    Ret = R_mmc_Sync_Rx((natural_uint_t)1, (uint8_t *) & CrcCcittBuf.uc[1]);
    if (Ret < MMC_OK)
    {
        R_mtl_memset((void *)pCidBuf, 0, (uint16_t)MMC_CID_SIZE); /* CID receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }
    Ret = R_mmc_Sync_Rx((natural_uint_t)1, (uint8_t *) & CrcCcittBuf.uc[0]);
    if (Ret < MMC_OK)
    {
        R_mtl_memset((void *)pCidBuf, 0, (uint16_t)MMC_CID_SIZE); /* CID receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* CRC7 calculation */
    Crc7Data = R_mmc_Crc7_Reg(pCidBuf, (natural_uint_t)(MMC_CID_SIZE - 1));

    /* CRC7 check */
    if (Crc7Data != pCidBuf[MMC_CID_CRC7IDX])
    {
        R_mtl_memset((void *)pCidBuf, 0, (uint16_t)MMC_CID_SIZE); /* CID receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_CRC;
    }

    /* CRC-CCITT calculation */
    CrcCcittData = R_mmc_CrcCcitt_Reg(pCidBuf, MMC_CID_SIZE);

    /* CRC-CCITT check */
    if (CrcCcittData != CrcCcittBuf.us)
    {
        R_mtl_memset((void *)pCidBuf, 0, (uint16_t)MMC_CID_SIZE); /* CID receive buffer clear   */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_CRC;
    }

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Get_Ocr(uint8_t *pOcrBuf)
* Function Name: R_mmc_Get_Ocr
* Description  : OCR acquisition processing
* Argument     : uint8_t *pOcrBuf    : OCR receive buffer pointer
* Return Value : MMC_OK              ; Success
*              : MMC_ERR_HARD        ; Hardware Error
*              : MMC_ERR_IDLE        ; Idle status error
*              : MMC_ERR_OTHER       ; Other Error
******************************************************************************/
int16_t R_mmc_Get_Ocr(uint8_t *pOcrBuf)
{
    int16_t    Ret;

    /* OCR reading command transmission */
    Ret = mmc_Cmd58();
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    if ((gMmc_ResBuf[MMC_RES_R1IDX]                 != 0x00) /* During an initialization process ? */
            || ((gMmc_ResBuf[MMC_RES_R3IDX] & MMC_OCR_BUSY) != MMC_OCR_BUSY))
    {
        /* Busy ?          */
        return MMC_ERR_OTHER;
    }

    /* Acquisition data -> OCR buffer */
    R_mtl_memcpy((void *)pOcrBuf, (void *)&gMmc_ResBuf[MMC_RES_R3IDX], (uint16_t)MMC_OCR_SIZE);

    return MMC_OK;
}

/******************************************************************************
* Declaration  : STATIC int16_t R_mmc_Chk_Sts(void)
* Function Name: R_mmc_Chk_Sts
* Description  : Publish a status request command and
*              :   perform an error check of the status that driver received.
* Argument     : None
* Return Value : MMC_OK            ; Success
*              : MMC_ERR_OTHER     ; Other Error
******************************************************************************/
STATIC int16_t R_mmc_Chk_Sts(void)
{
    natural_uint_t  RtyCnt;        /* Retry counter        */
    uint8_t         *pStatus;      /* Status data pointer       */
    int16_t         Ret;

    pStatus = &gMmc_ResBuf[MMC_RES_R2IDX];
    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        Ret = mmc_Cmd13();        /* Status send request command transmission  */
        if (Ret >= MMC_OK)
        {
            if ((*pStatus & MMC_RES2_CHKDATA) != MMC_RES2_CHKDATA)
            {
                /* Status OK         */
                return MMC_OK;
            }
        }
    }
    /* Status NG */
    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_OTHER;
}

/*----------------------------------------------------------------------------------------------*/
/* Data reading processing                                                                      */
/*----------------------------------------------------------------------------------------------*/

/******************************************************************************
* Declaration  : int16_t R_mmc_Read_Start(uint8_t SlotNo, uint32_t BlkNo)
* Function Name: R_mmc_Read_Start
* Description  : Process of Reading start.
*              : It is the processing for exclusive use of the multi-block.
* Argument     : uint8_t SlotNo     ; Slot Number
*              : uint32_t BlkNo     ; Reading start block number
* Return Value : MMC_OK             ; Success
*              : MMC_ERR_OTHER      ; Other Error
*              : MMC_ERR_MBLKCMD    ; Multi block command error
******************************************************************************/
int16_t R_mmc_Read_Start(uint8_t SlotNo, uint32_t BlkNo)
{
    natural_uint_t  RtyCnt;        /* Retry counter        */
    uint32_t        DataAddr;      /* Data address         */
    int16_t         Ret;

    R_mmc_Sync_Enable(1, MMC_UBRG_D_TRANSFER);   /* SYNC enable setting       */
    MMC_SET_CS(SlotNo, MMC_LOW);                 /* CS "L"          */

    DataAddr = BlkNo * gMmc_AddrRev[SlotNo];
    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        /* Multiple block read command transmission */
        Ret = mmc_Cmd18(R_mmc_ExchgLong(DataAddr));
#ifdef MMC_SBLK_CMD
        if (gMmc_ResBuf[MMC_RES_R1IDX] == 0x04)
        {  /* Illegal command ?       */
            return MMC_ERR_MBLKCMD;
        }
#endif /* #ifdef MMC_SBLK_CMD */
        if (Ret >= MMC_OK)
        {
            return MMC_OK;
        }

        /* Status check */
        R_mmc_Chk_Sts();                         /* Do not error check       */
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Read_BlkData(uint8_t SlotNo, uint8_t *pData, uint8_t Mode)
* Function Name: R_mmc_Read_BlkData
* Description  : 1 block read processing
*              : read data for 1 block.
*              : Detect the start block until maximum NAC time.
*              : After the start block detection, it begins to read 1 block data.
*              : It is single/multi block common processing.
* Argument     : uint8_t SlotNo     ; Slot Number
*              : uint32_t BlkNo     ; Reading start block number
* Return Value : MMC_OK             ; Success
*              : MMC_ERR_HARD       ; Hardware Error
*              : MMC_ERR_CRC        ; CRC Error
******************************************************************************/
int16_t R_mmc_Read_BlkData(uint8_t SlotNo, uint8_t *pData, uint8_t Mode)
{
    int16_t    Ret;

    /* Waiting for start block */
    R_mmc_Sync_DummyClk(MMC_NAC_MIN);            /* Waiting for NAC min       */

    Ret = R_mmc_Sync_Chk_RxData(gMmc_CsdInfo[SlotNo].Nac / 8, MMC_DTOKEN_STR_MR);
    if (Ret < MMC_OK)                            /* Start block detection      */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_HARD;
    }

    /* Data receive & CRC-CCITT check */
    Ret = R_mmc_Sync_DataIn(pData);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Read_End(void)
* Function Name: R_mmc_Read_End
* Description  : Process of Reading finish.
*              : It is the processing for exclusive use of the multi-block.
*              : When it detect an error,
*              :   it execute the setting prohibited in SYNC at a high rank.
* Argument     : None
* Return Value : MMC_OK           ; Success
*              : MMC_ERR_HARD     ; Hardware Error
******************************************************************************/
int16_t R_mmc_Read_End(void)
{
    natural_uint_t   RtyCnt;                     /* Retry counter        */
    int16_t    Ret;

    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        Ret = mmc_Cmd12();                       /* Stop command transmission     */
        if (Ret >= MMC_OK)
        {
            Ret = R_mmc_Chk_Sts();               /* Status check         */
            if (Ret >= MMC_OK)
            {
                Ret = R_mmc_Wait_Ready();        /* Waiting busy cancellation     */
                if (Ret >= MMC_OK)
                {
                    R_mmc_Sync_Disable();        /* SYNC disable setting       */
                    return MMC_OK;
                }
            }
        }
        R_mmc_Chk_Sts();                         /* Do not error check       */
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

#ifdef MMC_SBLK_CMD

/******************************************************************************
* Declaration  : int16_t R_mmc_SBRead_Start(uint8_t SlotNo, uint32_t BlkNo)
* Function Name: R_mmc_SBRead_Start
* Description  : Process of Reading start.
*              : It is the processing for exclusive use of the single-block.
* Argument     : uint8_t SlotNo     ; Slot Number
*              : uint32_t BlkNo     ; Reading start block number
* Return Value : MMC_OK             ; Success
*              : MMC_ERR_HARD       ; Hardware Error
******************************************************************************/
int16_t R_mmc_SBRead_Start(uint8_t SlotNo, uint32_t BlkNo)
{
    natural_uint_t  RtyCnt;                      /* Retry counter        */
    uint32_t        DataAddr;                    /* Data address         */
    int16_t         Ret;

    DataAddr = BlkNo * gMmc_AddrRev[SlotNo];
    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        /* Single block read command transmission */
        Ret = mmc_Cmd17(R_mmc_ExchgLong(DataAddr));
        if (Ret >= MMC_OK)
        {
            return MMC_OK;
        }

        /* Status check */
        R_mmc_Chk_Sts();                         /* Do not error check       */
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_SBRead_End(void)
* Function Name: R_mmc_SBRead_End
* Description  : Process of Reading finish.
*              : It is the processing for exclusive use of the single-block.
*              : When it detect an error,
*              :   it execute the setting prohibited in SYNC at a high rank.
* Argument     : None
* Return Value : MMC_OK           ; Success
*              : MMC_ERR_HARD     ; Hardware Error
******************************************************************************/
int16_t R_mmc_SBRead_End(void)
{
    natural_uint_t  RtyCnt;                      /* Retry counter        */
    int16_t         Ret;

    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        Ret = R_mmc_Chk_Sts();                   /* Status check         */
        if (Ret >= MMC_OK)
        {
            Ret = R_mmc_Wait_Ready();            /* Waiting busy cancellation     */
            if (Ret >= MMC_OK)
            {
                return MMC_OK;
            }
        }
        R_mmc_Chk_Sts();                         /* Do not error check       */
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

#endif /* #ifdef MMC_SBLK_CMD */
/*----------------------------------------------------------------------------------------------*/
/* Data writing processing                                                                      */
/*----------------------------------------------------------------------------------------------*/

/******************************************************************************
* Declaration  : int16_t R_mmc_Write_Start(uint8_t SlotNo, uint32_t BlkNo)
* Function Name: R_mmc_Write_Start
* Description  : Process of Writing start.
*              : It is the processing for exclusive use of the multi-block.
* Argument     : uint8_t SlotNo     ; Slot Number
*              : uint32_t BlkNo     ; Reading start block number
* Return Value : MMC_OK             ; Success
*              : MMC_ERR_HARD       ; Hardware Error
*              : MMC_ERR_MBLKCMD    ; Multi block command error
******************************************************************************/
int16_t R_mmc_Write_Start(uint8_t SlotNo, uint32_t BlkNo)
{
    natural_uint_t  RtyCnt;                      /* Retry counter        */
    uint32_t        DataAddr;                    /* Data address         */
    uint8_t         TxBuf;                       /* Transmission temp buffer      */
    int16_t         Ret;

    R_mmc_Sync_Enable(1, MMC_UBRG_D_TRANSFER);   /* SYNC enable setting       */
    MMC_SET_CS(SlotNo, MMC_LOW);                 /* CS "L"          */

    DataAddr = BlkNo * gMmc_AddrRev[SlotNo];
    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        /* Multiple block write command transmission */
        Ret = mmc_Cmd25(R_mmc_ExchgLong(DataAddr));
#ifdef MMC_SBLK_CMD
        if (gMmc_ResBuf[MMC_RES_R1IDX] == 0x04)  /* Illegal command ?       */
        {
            return MMC_ERR_MBLKCMD;
        }
#endif /* #ifdef MMC_SBLK_CMD */
        if (Ret >= MMC_OK)
        {
            return MMC_OK;
        }

        /* Status check */
        R_mmc_Chk_Sts();                         /* Do not error check       */

        /* Stop block token transmission */
        TxBuf = MMC_DTOKEN_STP_MW;
        R_mmc_Sync_MultTx(MMC_DTOKEN_SIZE, &TxBuf);  /* Do not error check       */

        /* Waiting busy cancellation */
        Ret = R_mmc_Wait_Ready();
        if (Ret < MMC_OK)
        {
            R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
            return Ret;
        }
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Write_BlkData(uint8_t *pData, uint8_t Mode)
* Function Name: R_mmc_Write_BlkData
* Description  : 1 block write processing
*              : Wait at NWR time.
*              : Transmit Start block token.
*              : Write in data of 1 block.
*              : Check the response data.
*              : It is the processing for exclusive use of the multi-block.
* Argument     : uint8_t *pData     ; Writing data storage buffer pointer
*              : uint8_t Mode       ; writing data transmission mode
* Return Value : MMC_OK             ; Success
*              : MMC_ERR_HARD       ; Hardware Error
*              : MMC_ERR_CRC        ; CRC Error
******************************************************************************/
int16_t R_mmc_Write_BlkData(uint8_t *pData, uint8_t Mode)
{
    uint8_t    TxBuf[MMC_NWR_MIN+MMC_DTOKEN_SIZE]; /* Transmission temp buffer      */
    int16_t    Ret;

    /* Waiting for NWR & Start block token transmission */
    TxBuf[0] = MMC_DUMMY_DATA;
    TxBuf[1] = MMC_DTOKEN_STR_MW;
    Ret = R_mmc_Sync_MultTx((natural_uint_t)(MMC_NWR_MIN + MMC_DTOKEN_SIZE), TxBuf);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Data transmission & CRC-CCITT transmission */
    Ret = R_mmc_Sync_DataOut(pData);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Data response check */
    Ret = R_mmc_Chk_DataRes();
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Write_End(void)
* Function Name: R_mmc_Write_End
* Description  : Process of writing finish.
*              : Wait at NWR time.
*              : Transmit Stop block token.
*              : Check the ready and status.
*              : It is the processing for exclusive use of the multi-block.
*              : When it detect an error,
*              :   it execute the setting prohibited in SYNC at a high rank.
* Argument     : None
* Return Value : MMC_OK           ; Success
*              : MMC_ERR_HARD     ; Hardware Error
******************************************************************************/
int16_t R_mmc_Write_End(void)
{
    natural_uint_t   RtyCnt;                     /* Retry counter        */
    uint8_t          TxBuf[MMC_DTOKEN_SIZE+MMC_NBR_MIN]; /* Transmission temp buffer      */
    int16_t          Ret;

    /* Waiting for NWR */
    Ret = R_mmc_Sync_DummyClk(MMC_NWR_MIN);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        TxBuf[0] = MMC_DTOKEN_STP_MW;
        TxBuf[1] = MMC_DUMMY_DATA;
        Ret = R_mmc_Sync_MultTx((natural_uint_t)(MMC_DTOKEN_SIZE + MMC_NBR_MIN), TxBuf);  /* Stop block tokentransmission & Waiting for NBR */
        if (Ret >= MMC_OK)
        {
            Ret = R_mmc_Wait_Ready();            /* Waiting busy cancellation     */
            if (Ret >= MMC_OK)
            {
                Ret = R_mmc_Chk_Sts();           /* Status check         */
                if (Ret >= MMC_OK)
                {
                    Ret = R_mmc_Wait_Ready();
                    if (Ret >= MMC_OK)
                    {
                        R_mmc_Sync_Disable();
                        return MMC_OK;
                    }
                }
            }
        }
        R_mmc_Chk_Sts();                         /* Do not error check       */
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

#ifdef MMC_SBLK_CMD

/******************************************************************************
* Declaration  : int16_t R_mmc_SBWrite_Start(uint8_t SlotNo, uint32_t BlkNo)
* Function Name: R_mmc_SBWrite_Start
* Description  : Process of Writing start.
*              : It is the processing for exclusive use of the single-block.
* Argument     : uint8_t SlotNo     ; Slot Number
*              : uint32_t BlkNo     ; Reading start block number
* Return Value : MMC_OK             ; Success
*              : MMC_ERR_HARD       ; Hardware Error
******************************************************************************/
int16_t R_mmc_SBWrite_Start(uint8_t SlotNo, uint32_t BlkNo)
{
    natural_uint_t  RtyCnt;                      /* Retry counter        */
    uint32_t        DataAddr;                    /* Data address         */
    int16_t         Ret;

    DataAddr = BlkNo * gMmc_AddrRev[SlotNo];
    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        /* Single block write command transmission */
        Ret = mmc_Cmd24(R_mmc_ExchgLong(DataAddr));
        if (Ret >= MMC_OK)
        {
            return MMC_OK;
        }

        /* Status check */
        R_mmc_Chk_Sts();                         /* Do not error check       */

        /* Waiting busy cancellation */
        Ret = R_mmc_Wait_Ready();
        if (Ret < MMC_OK)
        {
            R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
            return Ret;
        }
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_SBWrite_BlkData(uint8_t *pData, uint8_t Mode)
* Function Name: R_mmc_SBWrite_BlkData
* Description  : 1 block write processing
*              : Wait at NWR time.
*              : Transmit Start block token.
*              : Write in data of 1 block.
*              : Check the response data.
*              : It is the processing for exclusive use of the single-block.
* Argument     : uint8_t *pData     ; Writing data storage buffer pointer
*              : uint8_t Mode       ; writing data transmission mode
* Return Value : MMC_OK             ; Success
*              : MMC_ERR_HARD       ; Hardware Error
*              : MMC_ERR_CRC        ; CRC Error
******************************************************************************/
int16_t R_mmc_SBWrite_BlkData(uint8_t *pData, uint8_t Mode)
{
    uint8_t    TxBuf[MMC_NWR_MIN+MMC_DTOKEN_SIZE]; /* Transmission temp buffer      */
    int16_t    Ret;

    /* Waiting for NWR & Start block token transmission */
    TxBuf[0] = MMC_DUMMY_DATA;
    TxBuf[1] = MMC_DTOKEN_STR_SW;
    Ret = R_mmc_Sync_MultTx((natural_uint_t)(MMC_NWR_MIN + MMC_DTOKEN_SIZE), TxBuf);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Data transmission & CRC-CCITT transmission */
    Ret = R_mmc_Sync_DataOut(pData);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Data response check */
    Ret = R_mmc_Chk_DataRes();
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_SBWrite_End(void)
* Function Name: R_mmc_SBWrite_End
* Description  : Process of writing finish.
*              : Wait at NWR time.
*              : Check the ready and status.
*              : It is the processing for exclusive use of the single-block.
*              : When it detect an error,
*              :   it execute the setting prohibited in SYNC at a high rank.
* Argument     : None
* Return Value : MMC_OK           ; Success
*              : MMC_ERR_HARD     ; Hardware Error
******************************************************************************/
int16_t R_mmc_SBWrite_End(void)
{
    natural_uint_t  RtyCnt;       /* Retry counter        */
    int16_t    Ret;

    for (RtyCnt = 128; RtyCnt != 0; RtyCnt--)
    {
        Ret = R_mmc_Wait_Ready();                /* Waiting busy cancellation     */
        if (Ret >= MMC_OK)
        {
            Ret = R_mmc_Chk_Sts();               /* Status check         */
            if (Ret >= MMC_OK)
            {
                Ret = R_mmc_Wait_Ready();        /* Waiting busy cancellation     */
                if (Ret >= MMC_OK)
                {
                    return MMC_OK;
                }
            }
        }
        R_mmc_Chk_Sts();                         /* Do not error check       */
    }

    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

#endif /* #ifdef MMC_SBLK_CMD */

/******************************************************************************
* Declaration  : STATIC int16_t R_mmc_Wait_Ready(void)
* Function Name: R_mmc_Wait_Ready
* Description  : Processing waiting busy cancel
* Argument     : None
* Return Value : MMC_OK           ; Success
*              : MMC_ERR_HARD     ; Hardware Error
******************************************************************************/
STATIC int16_t R_mmc_Wait_Ready(void)
{
    natural_uint_t  WaitCnt;                     /* Wait counter         */
    int16_t         Ret;

    for (WaitCnt = MMC_READY_WAIT; WaitCnt != 0; WaitCnt--)
    {
        Ret = R_mmc_Sync_Chk_RxData((uint32_t)1, MMC_READY_DATA);
        if (Ret >= MMC_OK)
        {
            /* Ready */
            return MMC_OK;
        }
        R_mtl_wait_lp(MMC_T_READY_WAIT);
    }

    /* Busy */
    R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
    return MMC_ERR_HARD;
}

/******************************************************************************
* Declaration  : STATIC int16_t R_mmc_Chk_DataRes(void)
* Function Name: R_mmc_Chk_DataRes
* Description  : Data response check processing
* Argument     : None
* Return Value : MMC_OK           ; Success
*              : MMC_ERR_HARD     ; Hardware Error
*              : MMC_ERR_CRC      ; CRC Error
******************************************************************************/
STATIC int16_t R_mmc_Chk_DataRes(void)
{
    uint8_t         RxBuf;                       /* Receive temp buffer       */
    natural_uint_t  RtyCnt;                      /* Retry counter        */
    int16_t         Ret;

    RxBuf = 0x00;
    for (RtyCnt = 10; RtyCnt != 0; RtyCnt--)
    {
        R_mmc_Sync_Rx(MMC_DATARES_SIZE, (uint8_t *)&RxBuf);
        /* A return value at the time of receive OK is MMC_OK */
        RxBuf &= MMC_DATARES_MASK;
        if (RxBuf == MMC_DATARES_OK)             /* OK response receive       */
        {
            break;
        }
        if (RxBuf == MMC_DATARES_CRCERR)         /* CRC error response receive     */
        {
            R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
            return MMC_ERR_CRC;
        }
        if (RxBuf == MMC_DATARES_WERR)           /* Write error response receive     */
        {
            R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
            return MMC_ERR_HARD;
        }
    }
    if (RtyCnt == 0)                             /* Response non-receive       */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_HARD;
    }

    /* Waiting busy cancellation */
    Ret = R_mmc_Wait_Ready();
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    return MMC_OK;
}


/******************************************************************************
* Declaration  : uint8_t R_mmc_Get_Detect_Status(uint8_t SlotNo)
* Function Name: R_mmc_Get_Detect_Status
* Description  : Check the state of the Detect terminal
* Argument     : uint8_t SlotNo  : slot number
* Return Value : MMC_TRUE   ; Card is insert
*              : MMC_FALSE  ; Card is not insert
******************************************************************************/
uint8_t R_mmc_Get_Detect_Status(uint8_t SlotNo)
{
    int16_t Ret;

    R_mmc_Init_Port(SlotNo);                     /* Port initialization                          */
    if (gMmc_Media[SlotNo] == MMC_CARD_UNDETECT)
    {
        R_mmc_Sync_Enable(1, MMC_UBRG_IDENTIFICATION);      /* SYNC enable setting               */

        /* SPI mode select */
        MMC_SET_CS(SlotNo, MMC_HI);              /* CS "H"                                       */
        R_mmc_Sync_DummyClk(MMC_SPI_SEL);

        MMC_SET_CS(SlotNo, MMC_LOW);             /* CS "L"                                       */

        Ret = mmc_Cmd0();                              /* Reset command transmission                   */
    }
    else
    {
        R_mmc_Sync_Enable(1, MMC_UBRG_D_TRANSFER);      /* SYNC enable setting                   */

        MMC_SET_CS(SlotNo, MMC_LOW);             /* CS "L"                                       */

        Ret = mmc_Cmd13();

    }

    MMC_SET_CS(SlotNo, MMC_HI);                  /* CS "H"                                       */
    R_mmc_Sync_Disable();                        /* SYNC enable setting                          */
    R_mmc_Init_Port(SlotNo);                     /* Port initialization                          */

    if (Ret == MMC_OK)
    {
        return MMC_TRUE;
    }
    else
    {
        return MMC_FALSE;
    }
}
