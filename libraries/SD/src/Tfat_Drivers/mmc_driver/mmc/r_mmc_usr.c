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
* File Name     : r_mmc_usr.c
* Version       : 1.23B
* Device(s)     : Renesas MUC
* Tool-Chain    : -
* H/W Platform  : -
* Description   : MMC driver user I/F module
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
*               : 03.02.2012 Ver1.23B
*""FILE COMMENT END""***************************************************************/
#include <stddef.h>
#include "r_mtl_com.h"                           /* Renesas tool common definitions             */
#include "r_mmc.h"                               /* MMC driver common definitions               */
#include "r_mmc_sub.h"                           /* MMC driver sub module definitions           */
#include "r_mmc_io.h"                            /* MMC driver I/O module definitions           */

/************************************************************************************************/
/* Definitions                                                                                  */
/************************************************************************************************/
#define MMC_FID       (8UL << 6 | 1UL)

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

/************************************************************************************************/
/* Prototypes                                                                                   */
/************************************************************************************************/

/******************************************************************************
* Declaration  : void R_mmc_Init_Driver(void)
* Function Name: R_mmc_Init_Driver
* Description  : MMC driver initialization processing
*              : -Initialize SFR for card control.
*              : -The following process is done in every slot.
*              :   (1)Open card control port.
*              :   (2)Initialize card control RAM.
*              : Execute once when the system starts up.
* Argument     : None
* Return Value : None
******************************************************************************/
void R_mmc_Init_Driver(void)
{
    uint8_t    SlotNo;                            /* Slot number         */

    R_mmc_Init_Sfr();                             /* SFR initialization       */

    R_mmc_Init_IO();                              /* Driver use terminal initial setting   */

    for (SlotNo = MMC_SLOT0; SlotNo < T_Mmc_SlotNum[0]; SlotNo++)
    {
        R_mmc_Open_Port(SlotNo);                  /* Port open         */
        R_mmc_Init_Ram(SlotNo);                   /* RAM initialization       */
    }
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Init_Slot(uint8_t SlotNo)
* Function Name: R_mmc_Init_Slot
* Description  : MMC slot initialization processing
*              : Initializes card slot.
*              : -Initializes card control RAM.
*              : -Initializes card control ports.
*              : -Initializes of card.
*              : Execute when card insertion is detected.
* Argument     : uint8_t  SlotNo    ; Slot number
* Return Value : MMC_OK             ; Successful operation
*              : MMC_ERR_PARAM      ; Parameter error
*              : MMC_ERR_HARD       ; Hard error
*              : MMC_ERR_CRC        ; CRC error
*              : MMC_ERR_IDLE       ; Idle state error
*              : MMC_ERR_OTHER      ; Other error
******************************************************************************/
int16_t R_mmc_Init_Slot(uint8_t SlotNo)
{
    int16_t    Ret;

    /* Parameter check */
    if (SlotNo >= T_Mmc_SlotNum[0])
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    R_mmc_Init_Ram(SlotNo);                      /* RAM initialization       */
    R_mmc_Init_Port(SlotNo);                     /* Port initialization       */

    Ret = R_mmc_Init_Media(SlotNo);              /* Media initialization       */
    if (Ret < MMC_OK)
    {
        R_mmc_Init_Sfr();                        /* SFR initialization       */
        R_mmc_Init_Port(SlotNo);                 /* Port initialization       */
        R_mmc_Init_Ram(SlotNo);                  /* RAM initialization       */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    R_mmc_Init_Sfr();                            /* SFR initialization       */
    R_mmc_Init_Port(SlotNo);                     /* Port initialization       */

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Detach(uint8_t SlotNo)
* Function Name: R_mmc_Detach
* Description  : MMC slot detach processing
*              : Process when removing card from designated slot.
*              : -Initialize card control SFR.
*              : -Open card control port.
*              : -Initialize card control RAM.
*              : Execute when card removal is detected.
* Argument     : uint8_t  SlotNo    ; Slot number
*              : MMC_OK             ; Successful operation
*              : MMC_ERR_PARAM      ; Parameter error
******************************************************************************/
int16_t R_mmc_Detach(uint8_t SlotNo)
{
    /* Parameter check */
    if (SlotNo >= T_Mmc_SlotNum[0])
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    R_mmc_Init_Sfr();                            /* SFR initialization       */
    R_mmc_Open_Port(SlotNo);                     /* Port open         */
    R_mmc_Init_Ram(SlotNo);                      /* RAM initialization       */

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Read_Data(uint8_t SlotNo, uint32_t BlkNo, uint32_t BlkCnt, uint8_t *pData, uint8_t Mode)
* Function Name: R_mmc_Read_Data
* Description  : Data reading process
*              : -Readout the data from card by block (512byte)
*              : -Readout the data in the designated number of blocks from the designated block.
*              : -Transfer mode 'Mode' is used for choosing a transfer method of data.
*              :   MMC_MODE_NORMAL: This is a mode that transfers data to the designated buffer 'pData'.
*              : -Maximum number of blocks is the maximum block number (MmcInfo.MaxBlkNum)+1
*              :  from the "R_mmc_Get_MmcInfo()" function.
* Argument     : uint8_t   SlotNo     ; Slot number
*              : uint32_t   BlkNo     ; Block number to start readout
*              : uint32_t   BlkCnt    ; Number of readout blocks
*              : uint8_t    *pData    ; Pointer to the area where the data which is read must be stored
*              : uint8_t   Mode       ; Transfer mode of reading data
* Return Value : MMC_OK               ; Successful operation
*              : MMC_ERR_PARAM        ; Parameter error
*              : MMC_ERR_HARD         ; Hardware error
*              : MMC_ERR_CRC          ; CRC error
*              : MMC_ERR_OTHER        ; Other error
******************************************************************************/
int16_t R_mmc_Read_Data(uint8_t SlotNo, uint32_t BlkNo, uint32_t BlkCnt, uint8_t *pData, uint8_t Mode)
{
    int16_t    RSts = MMC_OK;
    int16_t    Ret;

    /* Parameter check */
    if (SlotNo            >= T_Mmc_SlotNum[0])
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    if ((Mode             != MMC_MODE_NORMAL)
            || (pData            == NULL))
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    if ((BlkCnt           == 0)
            || ((BlkNo + BlkCnt) < BlkNo)
            || ((BlkNo + BlkCnt) > (gMmc_CsdInfo[SlotNo].MaxBlkNum + 1)))
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    /* Card detection check */
    if (gMmc_Media[SlotNo] == MMC_CARD_UNDETECT)   /* Card non-detection       */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_OTHER;
    }

    R_mmc_Init_Port(SlotNo);                     /* Port initialization       */

    /* Reading start */
    Ret = R_mmc_Read_Start(SlotNo, BlkNo);
#ifdef MMC_SBLK_CMD
    if (Ret == MMC_ERR_MBLKCMD)                  /* Illegal command ?       */
    {
        for (; BlkCnt != 0; BlkCnt--)
        {
            /* Single block reading start */
            Ret = R_mmc_SBRead_Start(SlotNo, BlkNo);
            if (Ret < MMC_OK)
            {
                R_mmc_Init_Sfr();                /* SFR initialization       */
                R_mmc_Init_Port(SlotNo);         /* Port initialization       */
                R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
                return Ret;
            }
            /* 1 block data reading */
            Ret = R_mmc_Read_BlkData(SlotNo, pData, Mode);
            if (Ret < MMC_OK)
            {
                R_mmc_Init_Sfr();                /* SFR initialization       */
                R_mmc_Init_Port(SlotNo);         /* Port initialization       */
                R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
                return Ret;
            }
            /* Single block reading end */
            Ret = R_mmc_SBRead_End();
            if (Ret < MMC_OK)
            {
                R_mmc_Init_Sfr();                /* SFR initialization       */
                R_mmc_Init_Port(SlotNo);         /* Port initialization       */
                R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
                return Ret;
            }
            BlkNo++;
            pData += MMC_BLK_SIZE;
        }
        R_mmc_Init_Sfr();                        /* SFR initialization       */
        R_mmc_Init_Port(SlotNo);                 /* Port initialization       */

        return MMC_OK;
    }
#endif /* #ifdef MMC_SBLK_CMD */
    if (Ret < MMC_OK)
    {
        R_mmc_Init_Sfr();                        /* SFR initialization       */
        R_mmc_Init_Port(SlotNo);                 /* Port initialization       */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Data reading */
    for (; BlkCnt != 0; BlkCnt--)
    {
        RSts = R_mmc_Read_BlkData(SlotNo, pData, Mode); /* 1 block data reading       */
        if (RSts < MMC_OK)
        {
            break;                               /* Even an error is not finished    */
        }
        pData += MMC_BLK_SIZE;
    }

    /* Reading end */
    Ret = R_mmc_Read_End();
    if ((Ret < MMC_OK) || (RSts < MMC_OK))
    {
        R_mmc_Init_Sfr();                        /* SFR initialization       */
        R_mmc_Init_Port(SlotNo);                 /* Port initialization       */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        if (RSts < MMC_OK)
        {
            return RSts;
        }
        return Ret;
    }

// R_mmc_Init_Sfr();                             /* SFR initialization       */
    /* Initialization by lower processing   */
    R_mmc_Init_Port(SlotNo);                     /* Port initialization       */

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Write_Data(uint8_t SlotNo, uint32_t BlkNo, uint32_t BlkCnt, uint8_t *pData, uint8_t Mode)
* Function Name: R_mmc_Write_Data
* Description  : Data writing process
*              : -Write the data to card by block (512byte).
*              : -Write the data in the designated number of blocks to the designated block.
*              : -Transfer mode 'Mode' is used for choosing a transfer method of data.
*              :   MMC_MODE_NORMAL  : This is a mode that transfers data from the designated buffer 'pData'
*              :   MMC_MODE_FORCED_W: This is a mode that writes forcibly without affecting a Write-protection status.
*              : -Maximum number of blocks is the maximum block number (MmcInfo.MaxBlkNum)+1
*              :  from the "R_mmc_Get_MmcInfo()" function.
*              : -Reading from card can be made when card information from "R_mmc_Get_MmcInfo()"
*              :  function meets the following requirements.
*              :   1.Write-protection status (MmcInfo.WProtect) is MMC_NO_PROTECT.
*              : -Maximum number of blocks is the maximum block number (MmcInfo.MaxBlkNum)+1
*              :  from the "R_mmc_Get_MmcInfo()" function.
* Argument     : uint8_t   SlotNo     ; Slot number
*              : uint32_t   BlkNo     ; Block number to start writing
*              : uint32_t   BlkCnt    ; Number of writing blocks
*              : uint8_t    *pData    ; Pointer to the area where the data which is written must be stored
*              : uint8_t   Mode       ; Transfer mode of writing data
* Return Value : MMC_OK               ; Successful operation
*              : MMC_ERR_PARAM        ; Parameter error
*              : MMC_ERR_HARD         ; Hardware error
*              : MMC_ERR_WP           ; Write-protection error
*              : MMC_ERR_OTHER        ; Other error
******************************************************************************/
int16_t R_mmc_Write_Data(uint8_t SlotNo, uint32_t BlkNo, uint32_t BlkCnt, uint8_t *pData, uint8_t Mode)
{
    int16_t    WSts = MMC_OK;
    int16_t    Ret;

    /* Parameter check */
    if (SlotNo            >= T_Mmc_SlotNum[0])
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }
    if ((Mode             != MMC_MODE_NORMAL)
            && (Mode             != MMC_MODE_FORCED_W))
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }
    if (pData             == NULL)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    if ((BlkCnt           == 0)
            || ((BlkNo + BlkCnt) < BlkNo)
            || ((BlkNo + BlkCnt) > (gMmc_CsdInfo[SlotNo].MaxBlkNum + 1)))
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    /* Card detection check */
    if (gMmc_Media[SlotNo] == MMC_CARD_UNDETECT)   /* Card non-detection       */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_OTHER;
    }

    /* Write-protection check */
    if ((gMmc_WP[SlotNo] != MMC_NO_PROTECT)
            && (Mode            != MMC_MODE_FORCED_W))   /* Write-protection state ?      */
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_WP;
    }

    R_mmc_Init_Port(SlotNo);                     /* Port initialization       */

    /* Writing start */
    Ret = R_mmc_Write_Start(SlotNo, BlkNo);
#ifdef MMC_SBLK_CMD
    if (Ret == MMC_ERR_MBLKCMD)                  /* Illegal command ?       */
    {
        for (; BlkCnt != 0; BlkCnt--)
        {
            /* Single block writing start */
            Ret = R_mmc_SBWrite_Start(SlotNo, BlkNo);
            if (Ret < MMC_OK)
            {
                R_mmc_Init_Sfr();                /* SFR initialization       */
                R_mmc_Init_Port(SlotNo);         /* Port initialization       */
                R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
                return Ret;
            }
            /* 1 block data writing */
            Ret = R_mmc_SBWrite_BlkData(pData, Mode);
            if (Ret < MMC_OK)
            {
                R_mmc_Init_Sfr();                /* SFR initialization       */
                R_mmc_Init_Port(SlotNo);         /* Port initialization       */
                R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
                return Ret;
            }
            /* Single block writing end */
            Ret = R_mmc_SBWrite_End();
            if (Ret < MMC_OK)
            {
                R_mmc_Init_Sfr();                /* SFR initialization       */
                R_mmc_Init_Port(SlotNo);         /* Port initialization       */
                R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
                return Ret;
            }
            BlkNo++;
            pData += MMC_BLK_SIZE;
        }
        R_mmc_Init_Sfr();                        /* SFR initialization       */
        R_mmc_Init_Port(SlotNo);                 /* Port initialization       */

        return MMC_OK;
    }
#endif /* #ifdef MMC_SBLK_CMD */
    if (Ret < MMC_OK)
    {
        R_mmc_Init_Sfr();                        /* SFR initialization       */
        R_mmc_Init_Port(SlotNo);                 /* Port initialization       */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    /* Data writing */
    for (; BlkCnt != 0; BlkCnt--)
    {
        WSts = R_mmc_Write_BlkData(pData, Mode); /* 1 block data writing       */
        if (WSts < MMC_OK)
        {
            break;                               /* Even an error is not finished    */
        }
        pData += MMC_BLK_SIZE;
    }

    /* Writing end */
    Ret = R_mmc_Write_End();
    if ((Ret < MMC_OK) || (WSts < MMC_OK))
    {
        R_mmc_Init_Sfr();                        /* SFR initialization       */
        R_mmc_Init_Port(SlotNo);                 /* Port initialization       */
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        if (WSts < MMC_OK)
        {
            return WSts;
        }
        return Ret;
    }

// R_mmc_Init_Sfr();                             /* SFR initialization       */
    /* Initialization by lower processing   */
    R_mmc_Init_Port(SlotNo);                    /* Port initialization       */

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Chk_Detect(uint8_t SlotNo, uint8_t* pDetSts)
* Function Name: R_mmc_Chk_Detect
* Description  : Card insertion checking process
*              : -Check the condition of card being inserted.
*              : -The port status of card detecting will be in buffer 'pDetSts'.
*              :   MMC_TRUE :The port status of card detecting is active
*              :   MMC_FALSE:The port status of card detecting Non is non-active
*              : -Cannot remove chattering in this process.
*              : -Remove chattering in upper system if needed.
* Argument     : uint8_t    SlotNo     ; Slot number
*              : uint8_t*   pDetSts    ; buffer pointer for card insertion condition
* Return Value : MMC_OK                ; Successful operation
*              : MMC_ERR_PARAM         ; Parameter error
******************************************************************************/
int16_t R_mmc_Chk_Detect(uint8_t SlotNo, uint8_t* pDetSts)
{
    /* Parameter check */
    if ((SlotNo  >= T_Mmc_SlotNum[0])
            || (pDetSts == NULL))
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    /* MMC insertion state acquisition */
    *pDetSts = R_mmc_Get_Detect(SlotNo);

    return MMC_OK;
}


/******************************************************************************
* Declaration  : int16_t R_mmc_Get_MmcInfo(uint8_t SlotNo, MMC_INFO* pMmcInfo)
* Function Name: R_mmc_Get_MmcInfo
* Description  : Card information obtaining process
*              : -It returns MMC information.
*              : -The buffer 'pMmcInfo' holds card information.
*              :   pMmcInfo.Card     : Card types
*              :                       MMC_CARD_UNDETECT   :Card not detected
*              :                       MMC_CARD_MMC    :MMC
*              :                       MMC_CARD_OTHER   :Other card
*              :  pMmcInfo.Wprotect  : Write-protection status
*              :                       MMC_NO_PROTECT   :Write-protection cancel
*              :                       bit1: MMC_W_PROTECT_SOFT :Software write-protection
*              :  pMmcInfo.MemSize   : Card capacity(byte)
*              :  pMmcInfo.MaxBlkNum : Maximum block number
*              : -A case of 0xFFFFFFFF has card capacity 'pMmcInfo.MemSize' with the card partly.
*              :  In this case please calculate card capacity from greatest block number 'pMmcInfo.MaxBlkNum'.
* Argument     : uint8_t     SlotNo     ; Slot number
*              : MMC_INFO*   pMmcInfo   ; Buffer pointer for card information
* Return Value : MMC_OK                 ; Successful operation
*              : MMC_ERR_PARAM          ; Parameter error
*              : MMC_ERR_OTHER          ; Other error
******************************************************************************/
int16_t R_mmc_Get_MmcInfo(uint8_t SlotNo, MMC_INFO* pMmcInfo)
{
    /* Parameter check */
    if ((SlotNo   >= T_Mmc_SlotNum[0])
            || (pMmcInfo == NULL))
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_PARAM;
    }

    /* Card classification setting */
    pMmcInfo->Card      = gMmc_Media[SlotNo];

    /* Write-protection state setting */
    pMmcInfo->WProtect  = R_mmc_Get_Wp(SlotNo);

    /* Card capacity setting */
    pMmcInfo->MemSize   = gMmc_CsdInfo[SlotNo].MemSize;

    /* The number of the max blocks setting */
    pMmcInfo->MaxBlkNum = gMmc_CsdInfo[SlotNo].MaxBlkNum;

    return MMC_OK;
}
