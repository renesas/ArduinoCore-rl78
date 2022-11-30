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
* File Name     : r_mmc_mmc.c
* Version       : 1.23B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description   : MMC driver SPI mode MMC module
*************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 10.12.2007 Ver1.20
*              : 17.01.2008 Ver1.21
*              : 29.01.2008 Ver1.22
*              : 26.03.2008 Ver1.23
*              : 25.06.2010 Ver1.23A
*              : 02.03.2012 Ver1.23B
*""FILE COMMENT END""***************************************************************/
#include "r_mmc_mcu_pragma.h"
#include "r_mtl_com.h"         /* Renesas tool common definitions    */
#include "r_mmc.h"             /* MMC driver common definitions    */
#include "r_mmc_sub.h"         /* MMC driver sub module definitions   */
#include "r_mmc_sfr.h"         /* MMC driver SFR definitions     */
#include "r_mmc_io.h"          /* MMC driver I/O module definitions   */

#ifdef MMC_SUPPORT_MMC
/************************************************************************************************/
/* Definitions                                                                                  */
/************************************************************************************************/
#define MMC_FID       (8UL << 6 | 4UL)

/*-------------- Definitions of command --------------*/
/* Definitions of MMC command */                                            /*       SPI  MMC   */
#define MMC_CMD1    (uint8_t)(0x40U |  1U)

/************************************************************************************************/
/* Unions                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Structs                                                                                      */
/************************************************************************************************/

/************************************************************************************************/
/* Globals                                                                                      */
/************************************************************************************************/

/************************************************************************************************/
/* Macros                                                                                       */
/************************************************************************************************/
/*--------- Command transmission processing ----------*/
/* MMC command */    /*                   Cmd      Arg           ResSize       Rty              */
#define mmc_Cmd1()   R_mmc_Send_Cmd_Spi(MMC_CMD1,  (uint32_t)0,  MMC_R1_SIZE,  (natural_uint_t) 1 )

/************************************************************************************************/
/* Prototypes                     */
/************************************************************************************************/
STATIC int16_t R_mmc_Set_MMC_CsdInfo(uint8_t SlotNo, uint8_t *pCsdBuf);

/* 10ms * 1/n to n. but nano second order is defined to 0. */
/*                                         1ns, 10ns, 100ns, 1us  , 10us, 100us, 1ms, 10ms */
STATIC const uint16_t Taac_Unit_Tbl[8]  = {0  , 0   , 0    , 10000, 1000, 100  , 10 , 1    };
STATIC const uint8_t  Taac_Unit_div     = 100;     /* common divisor value */

/* Taac_Value_Tbl[0] is resserved. unit = 0.1 */
STATIC const uint8_t  Taac_Value_Tbl[16] = {0, 10, 12, 13, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 70, 80};
STATIC const uint8_t  Taac_Value_div     = 10;     /* common divisor value */

/******************************************************************************
* Declaration  : int16_t R_mmc_Reset_Mmc(uint8_t SlotNo)
* Function Name: R_mmc_Reset_Mmc
* Description  : Execute a reset sequence of the MMC.
*              : Execute an MMC initialization process.
*              : Perform a provision times initialization process re-try
*              :  until an initialization process is completed.
*              : Get CID.
*              : Get CSD and calculate MMC information.
* Argument     : uint8_t    SlotNo : Slot Number
* Return Value : Return the execution result of the reset sequence.
*              : MMC_OK            ; Success
*              : MMC_ERR_HARD      ; Hardware Error
*              : MMC_ERR_CRC       ; CRC Error
*              : MMC_ERR_IDLE      ; Idle status error
*              : MMC_ERR_OTHER     ; Other Error
******************************************************************************/
int16_t R_mmc_Reset_Mmc(uint8_t SlotNo)
{
    natural_uint_t RtyCnt;        /* Retry counter        */
    uint8_t        *pRegBuf;      /* OCR/CID/CSD receive buffer pointer   */
    int16_t        Ret;

    /* Initialization process */
    Ret = mmc_Cmd0();             /* Reset command transmission     */
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

#ifdef MMC_REGBUF_USED
    pRegBuf = gMmc_OcrBuf[SlotNo];
#else /* #ifdef MMC_REGBUF_USED */
    pRegBuf = gMmc_RegBuf[SlotNo];
#endif /* #ifdef MMC_REGBUF_USED */
    for (RtyCnt = 256; RtyCnt != 0; RtyCnt--)
    {
        Ret = mmc_Cmd1();                        /* Initialization start command transmission */
        if (Ret >= MMC_OK)
        {
            Ret = R_mmc_Get_Ocr(pRegBuf);        /* OCR acquisition        */
            if (Ret >= MMC_OK)
            {
                break;                           /* Initialization process completion   */
            }
        }
        R_mtl_wait_lp(MTL_T_1MS);
        R_mtl_wait_lp(MTL_T_1MS);
        R_mtl_wait_lp(MTL_T_1MS);
        R_mtl_wait_lp(MTL_T_1MS);
    }
    if (RtyCnt == 0)          /* Initialization failure      */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_OTHER;
    }

    R_mmc_Sync_Enable(0, MMC_UBRG_D_TRANSFER);   /* Data Transfer mode change      */

    /* CID acquisition */
#ifdef MMC_REGBUF_USED
    pRegBuf = gMmc_CidBuf[SlotNo];
#else /* #ifdef MMC_REGBUF_USED */
    pRegBuf = gMmc_RegBuf[SlotNo];
#endif /* #ifdef MMC_REGBUF_USED */
    Ret = R_mmc_Get_Cid(pRegBuf);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* CSD acquisition */
#ifdef MMC_REGBUF_USED
    pRegBuf = gMmc_CsdBuf[SlotNo];
#else /* #ifdef MMC_REGBUF_USED */
    pRegBuf = gMmc_RegBuf[SlotNo];
#endif /* #ifdef MMC_REGBUF_USED */
    Ret = R_mmc_Get_Csd(pRegBuf);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    Ret = R_mmc_Set_MMC_CsdInfo(SlotNo, pRegBuf);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* MMC detection setting */
    gMmc_Media[SlotNo] = MMC_CARD_MMC;

    return MMC_OK;
}

/******************************************************************************
* Declaration  : STATIC int16_t R_mmc_Set_MMC_CsdInfo(uint8_t SlotNo, uint8_t *pCsdBuf)
* Function Name: R_mmc_Set_MMC_CsdInfo
* Description  : Analyze CSD and take out various information.
* Argument     : uint8_t SlotNo   : Slot Number
*              : uint8_t *pCsdBuf : CSD buffer pointer
* Return Value : Return the acquisition result.
*              : MMC_OK           ; Success
*              : MMC_ERR_OTHER    ; Other Error
******************************************************************************/
STATIC int16_t R_mmc_Set_MMC_CsdInfo(uint8_t SlotNo, uint8_t *pCsdBuf)
{
    uint32_t RBlkLen, CSize, CSizeMult;          /* Temp for card capacity calculation   */
    CSD_INFO *pCsdInfo;                          /* CSD information pointer              */
    uint32_t work_nac;
    uint32_t wk;
    uint8_t  taac_unit_tbl_idx;
    uint8_t  taac_value;

    pCsdInfo = &gMmc_CsdInfo[SlotNo];

    /* Data block length calculation */
    RBlkLen = (uint32_t)pCsdBuf[5] & 0x000FU;
    if ((RBlkLen <= MMC_READ_BLK_LEN_MIN) || (RBlkLen >= MMC_READ_BLK_LEN_MAX))
    {
        /* READ_BLK_LEN error       */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_OTHER;
    }

    /* Card capacity calculation */
    CSize     = (((uint32_t)pCsdBuf[6] << 10) | ((uint32_t)pCsdBuf[7] << 2) | ((uint32_t)pCsdBuf[8] >> 6)) & 0x0FFFU;
    CSizeMult = (((uint32_t)pCsdBuf[9] << 1) | ((uint32_t)pCsdBuf[10] >> 7)) & 0x0007U;
    if (CSizeMult >= MMC_C_SIZE_MULT_MAX)     /* C_SIZE_MULT error       */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_OTHER;
    }

    pCsdInfo->MemSize = (CSize + 1) * (1U << (CSizeMult + 2)) * (1U << RBlkLen);
    if (pCsdInfo->MemSize == 0)       /* Card capacity error       */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_OTHER;
    }

    /* Number of the max blocks calculation */
    pCsdInfo->MaxBlkNum = (pCsdInfo->MemSize / MMC_BLK_SIZE) - 1;

    /* Asynchronous data access time calculation */
    taac_unit_tbl_idx = pCsdBuf[1] & 0x07;
    taac_value    = Taac_Value_Tbl[(pCsdBuf[1] & 0x78) >> 3];

    if (taac_unit_tbl_idx >= 3)
    {
        wk = ((uint32_t)Taac_Value_div * Taac_Unit_div * Taac_Unit_Tbl[taac_unit_tbl_idx]);
        pCsdInfo->Taac = ((uint32_t)1000000  * taac_value) / wk; // 1000000 is "1 = 1000000 micro".
        work_nac   = (MMC_CLK_D_TRANSFER * taac_value) / wk;
    }
    else
    {
        /* Nano seconds order's TAAC is defined to 0.  */
        pCsdInfo->Taac = 0;
        work_nac = 0;
    }

    /* Synchronization data access time calculation */
    pCsdInfo->Nsac = (uint16_t)pCsdBuf[2] * 100;
    pCsdInfo->Nac  = (work_nac + (uint32_t)pCsdInfo->Nsac) * 10;

    /* At least two times  checks start token. */
    if (pCsdInfo->Nac < 16)
    {
        pCsdInfo->Nac = 16;
    }

    /* Write-protection setting */
    pCsdInfo->WP   = (pCsdBuf[14] >> 4) & 0x03;
    gMmc_WP[SlotNo] = MMC_NO_PROTECT;            /* No protection setting      */
    if (pCsdInfo->WP != 0x00)
    {
        gMmc_WP[SlotNo] |= MMC_W_PROTECT_SOFT;   /* Software write-protection setting   */
    }

    gMmc_AddrRev[SlotNo] = MMC_BLK_SIZE;

    return MMC_OK;
}

#endif /* #ifdef MMC_SUPPORT_MMC */
