/*""FILE COMMENT""*******************************************************************
* File Name     : r_mmc.h
* Version       : 1.23B
* Device(s)     : Renesas MCU
* Tool-Chain    : -
* H/W Platform  : -
* Description   : MMC driver header file
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
#ifndef __MMC_H__
#define __MMC_H__


/************************************************************************************************/
/* Definitions                                                                                  */
/************************************************************************************************/
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*                         Please define resources of each user system.                         */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
/*----------------------------------------------------------------------------------------------*/

/*  Define number of required card slots. (1-N slots)                                           */
/*  Define slot number in accordance with the number of card slots to be connected.             */
/*----------------------------------------------------------------------------------------------*/
/* Define number of slots (devices). */
#define MMC_SLOT_NUM        1               /* 1slots                                           */ /** SET **/

/* Define slot number. */
#define MMC_SLOT0           0               /* Slot 0                                           */ /** SET **/
#define MMC_SLOT1           1               /* Slot 1                                           */ /** SET **/

/*----------------------------------------------------------------------------------------------*/
/*  When use the card which does not support a multi-block command, please define it.           */
/*  Use single block commands in the case of the card which does not support multiple block     */
/*  commands.                                                                                   */
/*----------------------------------------------------------------------------------------------*/
#define MMC_SBLK_CMD                        /*                   Support single block commands  */ /** SET **/

/*----------------------------------------------------------------------------------------------*/
/*  Please define the media to support.                                                         */
/*----------------------------------------------------------------------------------------------*/
#define MMC_SUPPORT_MMC                     /* MMC                                              */ /** SET **/

/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*                              Do not change the following data.                               */
/*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/************************************************************************************************/
/* Macros                                                                                       */
/************************************************************************************************/
/*----------- Definitions of return value ------------*/
#define MMC_OK              (int16_t)( 0)   /* Successful operation                             */
#define MMC_ERR_PARAM       (int16_t)(-1)   /* Parameter error                                  */
#define MMC_ERR_HARD        (int16_t)(-2)   /* Hardware error                                   */
#define MMC_ERR_CRC         (int16_t)(-3)   /* CRC error                                        */
#define MMC_ERR_WP          (int16_t)(-4)   /* Write-protection error                           */
#define MMC_ERR_MBLKCMD     (int16_t)(-5)   /* Multi-block command error                        */
#define MMC_ERR_IDLE        (int16_t)(-6)   /* Idle state error                                 */
#define MMC_ERR_OTHER       (int16_t)(-7)   /* Other error                                      */

/*------------- Definitions of log type --------------*/
#define MMC_LOG_ERR         1      /* Log type : Error                                          */

/*--------------- Definitions of flag ----------------*/
#define MMC_TRUE            (uint8_t)0x01   /* Flag "ON"                                        */
#define MMC_FALSE           (uint8_t)0x00   /* Flag "OFF"                                       */

/*------------- Definitions of card type -------------*/
#define MMC_CARD_UNDETECT   (uint8_t)0x00   /* Card is not found                                */
#define MMC_CARD_MMC        (uint8_t)0x01   /* MMC                                              */
#define MMC_CARD_OTHER      (uint8_t)0xFF   /* Other card                                       */

/*------ Definitions of write-protection status ------*/
#define MMC_NO_PROTECT      (uint8_t)0x00   /* None setting                                     */
#define MMC_W_PROTECT_SOFT  (uint8_t)0x02   /* Software write-protection                        */

/*-------- Definitions of data transfer mode ---------*/
#define MMC_MODE_NORMAL     (uint8_t)0x00   /* Normal transfer mode                             */
#define MMC_MODE_FORCED_W   (uint8_t)0x02   /* Forced writing mode (Normal transfer only)       */

/*--------- Definitions of card information ----------*/
#define MMC_BLK_SIZE        (uint16_t)512   /* Block size                                       */
#define MMC_CRC_SIZE        (uint16_t)2     /* CRC size                                         */
#define MMC_CSD_SIZE        (uint16_t)16    /* CSD size                                         */
#define MMC_CID_SIZE        (uint16_t)16    /* CID size                                         */
#define MMC_OCR_SIZE        (uint16_t)4     /* OCR size                                         */

/************************************************************************************************/
/* Unions                                                                                       */
/************************************************************************************************/

/************************************************************************************************/
/* Structs                                                                                      */
/************************************************************************************************/
/* Definition of MMC information structure */
typedef struct
{
    uint8_t  Card;                          /* Card type                                        */
    uint8_t  WProtect;                      /* Write-protection status                          */
    uint32_t MemSize;                       /* Card capacity                                    */
    uint32_t MaxBlkNum;                     /* The number of the max blocks                     */
} MMC_INFO;


/************************************************************************************************/
/* Externs                                                                                      */
/************************************************************************************************/


/************************************************************************************************/
/* Prototypes                                                                                   */
/************************************************************************************************/
/* MMC driver initialization       */
void R_mmc_Init_Driver(void);
/* MMC slot initialization         */
int16_t R_mmc_Init_Slot(uint8_t SlotNo);
/* MMC slot stop                   */
int16_t R_mmc_Detach(uint8_t SlotNo);
/* Read data                       */
int16_t R_mmc_Read_Data(uint8_t SlotNo, uint32_t BlkNo, uint32_t BlkCnt, uint8_t *pData, uint8_t Mode);
/* Write data                      */
int16_t R_mmc_Write_Data(uint8_t SlotNo, uint32_t BlkNo, uint32_t BlkCnt, uint8_t *pData, uint8_t Mode);
/* MMC insertion check             */
int16_t R_mmc_Chk_Detect(uint8_t SlotNo, uint8_t* pDetSts);
/* MMC information acquisition     */
int16_t R_mmc_Get_MmcInfo(uint8_t SlotNo, MMC_INFO* pMmcInfo);

#endif /* __MMC_H__ */
