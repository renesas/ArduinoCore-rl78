/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2012 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/
/*******************************************************************************
* File Name     : r_mmc_csi.c
* Version       : 1.00
* Device(s)     : RL78 Family
* Tool-Chain    : CubeSuite+
* H/W Platform  : -
* Description   : MMC driver SPI mode CSI communication module
******************************************************************************/
/******************************************************************************
* History       : DD.MM.YYYY Version Description
*               : 03.02.2012 1.00
******************************************************************************/
#include "r_mmc_mcu_pragma.h"
#include "r_mtl_com.h"         /* Renesas tool common definitions    */
#include "r_mmc.h"             /* MMC driver common definitions    */
#include "r_mmc_sub.h"         /* MMC driver sub module definitions   */
#include "r_mmc_sfr.h"         /* MMC driver SFR definitions     */
#include "r_mmc_io.h"          /* MMC driver I/O module definitions   */

#if defined(MMC_CSI_USED)
/************************************************************************************************/
/* Definitions                     */
/************************************************************************************************/
#define MMC_FID       (8UL << 6 | 5UL)

#if defined(MMC_NOCHK_TIMEOUT)
#define MMC_CSI_TX_TIMEOUT_CHK(wait , line)
#define MMC_CSI_TRX_TIMEOUT_CHK(wait , line)
#else /* #if defined(MMC_NOCHK_TIMEOUT) */
#define MMC_CSI_TX_TIMEOUT_CHK(wait , line) do                                          \
    {                                                                                   \
        wait--;                                                                         \
        if (wait == 0)                           /* Transmission waiting time over */   \
        {                                                                               \
            MMC_CSI_TX_DI();                     /* CSI transmit disable    */          \
            R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, line);                                   \
            return MMC_ERR_HARD;                                                        \
        }                                                                               \
        R_mtl_wait_lp(MMC_T_CSI_WAIT);                                                  \
    }while(0)

#define MMC_CSI_TRX_TIMEOUT_CHK(wait , line) do                                         \
    {                                                                                   \
        wait--;                                                                         \
        if (wait == 0)                           /* Transmission waiting time over */   \
        {                                                                               \
            MMC_CSI_TRX_DI();                   /* CSI transmit disable    */           \
            R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, line);                                   \
            return MMC_ERR_HARD;                                                        \
        }                                                                               \
        R_mtl_wait_lp(MMC_T_CSI_WAIT);                                                  \
    }while(0)

#endif /* #if defined(MMC_NOCHK_TIMEOUT) */

#if defined(MMC_SYNC_ORERR)
#define MMC_CSI_ORERR_CHK(line) do                                                      \
    {                                                                                   \
        if (MMC_CSI_ORER_CHECK())                /* Overrun error ?     */              \
        {                                                                               \
            MMC_CSI_ERR_CLEAR();                                                        \
            MMC_CSI_TRX_DI();                    /* CSI transmit&receive disable  */    \
            R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, line);                                   \
            return MMC_ERR_HARD;                                                        \
        }                                                                               \
    }while(0)
#else /* #if defined(MMC_SYNC_ORERR) */
#define MMC_CSI_ORERR_CHK(line)
#endif /* #if defined(MMC_SYNC_ORERR) */


/******************************************************************************
* Declaration  : void R_mmc_Init_Sfr(void)
* Function Name: R_mmc_Init_Sfr
* Description  : Initialize SFR to use.
* Argument     : None
* Return Value : None
******************************************************************************/
void R_mmc_Init_Sfr(void)
{
    MMC_CSI_DI();                                /* CSI disable setting       */
}

/******************************************************************************
* Declaration  : vvoid R_mmc_Sync_Enable(uint8_t flag, uint16_t bitrate)
* Function Name: R_mmc_Sync_Enable
* Description  : Enable SIO Module (option) and Set boudrate.
* Argument     : uint8_t  flag : 0=bitrate set ,1=SIO enable + bitrate set
*              : uint16_t bitrate : bitrate
* Return Value : None
******************************************************************************/
void R_mmc_Sync_Enable(uint8_t flag, uint16_t bitrate)
{
    if (flag != 0)
    {
        MMC_CSI_EI();                            /* CSI enable setting       */
    }
    MMC_CSI_BRG_SET(bitrate);                    /* It starts in Identification mode    */
}

/******************************************************************************
* Declaration  : void R_mmc_Sync_Disable(void)
* Function Name: R_mmc_Sync_Disable
* Description  : Disable SIO Module.
* Argument     : None
* Return Value : None
******************************************************************************/
void R_mmc_Sync_Disable(void)
{
    MMC_CSI_DI();
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_MultTx(natural_uint_t TxCnt, uint8_t *pData)
* Function Name: R_mmc_Sync_MultTx
* Description  : Transmit the data for the designated number of bytes consecutively.
* Argument     : natural_uint_t TxCnt  ; Number of send bytes
*              : uint8_t        *pData ; Send data buffer pointer
* Return Value : MMC_OK                ; Success
*              : MMC_ERR_HARD          ; Hardware Error
******************************************************************************/
int16_t R_mmc_Sync_MultTx(natural_uint_t TxCnt, uint8_t *pData)
{
#if !defined(MMC_NOCHK_TIMEOUT)
    natural_uint_t  TxWait = MMC_CSI_TX_WAIT;    /* Transmission waiting counter     */
#endif /* #if !defined(MMC_NOCHK_TIMEOUT) */
    uint8_t         TxData;

    MMC_CSI_TX_EI();                             /* CSI transmit enable       */
    do                                           /* Loop for transmission byte     */
    {
        TxData = *pData++;
        MMC_BIT_EXCHG(TxData);
        MMC_CSI_TXBUF  = TxData;                 /* Transmission data setting     */
        /* Transmission preparation completion check */
        while (MMC_TXNEXT_CHECK())
        {
            MMC_CSI_TX_TIMEOUT_CHK(TxWait , __LINE__);
        }
        /* Transmission data -> Transmission buffer register */
        MMC_TXNEXT_CLR();
        TxCnt--;
    }
    while (TxCnt != 0);

    /* Final data transmission completion check */
    while (MMC_TXEND_CHECK())                    /* Loop for transmission completion    */
    {
        MMC_CSI_TX_TIMEOUT_CHK(TxWait , __LINE__);
    }

    /* Clear IR bit of IR register */
    MMC_TXNEXT_CLR();                            /* Transmission empty flag clear   */
    MMC_CSI_TX_DI();                             /* CSI transmit disable      */

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_Rx(natural_uint_t RxCnt, uint8_t *pData)
* Function Name: R_mmc_Sync_Rx
* Description  : Receive the data for the designated number of bytes.
* Argument     : natural_uint_t RxCnt  ; Number of recieve bytes
*              : uint8_t        *pData ; Recieve data buffer pointer
* Return Value : MMC_OK                ; Success
*              : MMC_ERR_HARD          ; Hardware Error
******************************************************************************/
int16_t R_mmc_Sync_Rx(natural_uint_t RxCnt, uint8_t *pData)
{
#if !defined(MMC_NOCHK_TIMEOUT)
    natural_uint_t  RxWait = MMC_CSI_RX_WAIT;    /* Receive waiting counter      */
#endif /* #if !defined(MMC_NOCHK_TIMEOUT) */
    uint8_t         RxData;

    MMC_CSI_TRX_EI();                            /* CSI transmit&receive enable     */

    if (RxCnt > 0)
    {
        MMC_CSI_TXBUF  = MMC_DUMMY_DATA;
        RxCnt--;

        while (RxCnt != 0)
        {
            /* Receive completion check */
            while (MMC_RX_COMPLETE_CHECK())      /* Loop for receive completion     */
            {
                MMC_CSI_ORERR_CHK(__LINE__);
                MMC_CSI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
            }
            /* Receive data -> Receive data buffer */
            MMC_RXNEXT_CLR();                    /* Receive completion flag clear    */
            RxData = MMC_CSI_RXBUF;              /* Receive data taking       */

            MMC_CSI_TXBUF  = MMC_DUMMY_DATA;
            MMC_BIT_EXCHG(RxData);
            *pData = RxData;
            pData++;
            RxCnt--;
        }

        while (MMC_RX_COMPLETE_CHECK())          /* Loop for transmission empty     */
        {
            MMC_CSI_ORERR_CHK(__LINE__);
            MMC_CSI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
        }
        /* Receive data -> Receive data buffer */
//  MMC_RXNEXT_CLR();                            /* Receive completion flag clear    */
        RxData = MMC_CSI_RXBUF;                  /* Receive data taking       */
        MMC_BIT_EXCHG(RxData);
        *pData = RxData;
    }

    /* Clear IR bit of IR register */
// MMC_TXNEXT_CLR();                             /* Transmission empty flag clear    */
// MMC_RXNEXT_CLR();                             /* Receive completion flag clear    */
    MMC_CSI_TRX_DI();                            /* CSI transmit&receive disable    */

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_DataOut(uint8_t *pData)
* Function Name: R_mmc_Sync_DataOut
* Description  : Transmit data and CRC-CCITT for 1 block.
* Argument     : uint8_t *pData  ; Send data buffer pointer
* Return Value : MMC_OK          ; Success
*              : MMC_ERR_HARD    ; Hardware Error
******************************************************************************/
int16_t R_mmc_Sync_DataOut(uint8_t *pData)
{
#if !defined(MMC_NOCHK_TIMEOUT)
    natural_uint_t   TxWait = MMC_CSI_TX_WAIT;   /* Transmission waiting counter     */
#endif /* #if !defined(MMC_NOCHK_TIMEOUT) */
    natural_uint_t   TxCnt;                      /* Transmission byte counter     */
    uint8_t          *pwk;                       /* Transmission CRC data buffer pointer   */
    uint16_t         CrcBuf;                     /* Transmission CRC data buffer     */
    int16_t          Ret;
    uint8_t          work[2];                    /* Transmission CRC data buffer     */

    MMC_CRC_CLR();

    MMC_CSI_TX_EI();                             /* CSI transmit enable       */

    TxCnt = MMC_BLK_SIZE - 2;
    work[0] = *pData++;
    MMC_CRC_SET(work[0]);                        /* CRC-CCITT calculation      */
    MMC_BIT_EXCHG(work[0]);

    work[1] = *pData++;
    MMC_CRC_SET(work[1]);                        /* CRC-CCITT calculation      */
    MMC_BIT_EXCHG(work[1]);

    MMC_CSI_TXBUF  = work[0];                    /* Transmission data setting     */
    while (MMC_TXNEXT_CHECK())
    {
        MMC_CSI_TX_TIMEOUT_CHK(TxWait , __LINE__);
    }
    /* Transmission data -> Transmission buffer register */
    MMC_CSI_TXBUF  = work[1];                    /* Transmission data setting     */

    do
    {
        work[0] = *pData++;
        MMC_CRC_SET(work[0]);                    /* CRC-CCITT calculation      */
        MMC_BIT_EXCHG(work[0]);

        work[1] = *pData++;
        MMC_CRC_SET(work[1]);                    /* CRC-CCITT calculation      */
        MMC_BIT_EXCHG(work[1]);

        while (MMC_TXNEXT_CHECK())
        {
            MMC_CSI_TX_TIMEOUT_CHK(TxWait , __LINE__);
        }
        MMC_CSI_TXBUF  = work[0];                /* Transmission data setting     */

        while (MMC_TXNEXT_CHECK())
        {
            MMC_CSI_TX_TIMEOUT_CHK(TxWait , __LINE__);
        }
        MMC_CSI_TXBUF  = work[1];                /* Transmission data setting     */

        /* Transmission data -> Transmission buffer register */
        TxCnt -= 2;
    }
    while (TxCnt != 0);                          /* Loop for 1block        */

    /* Final data transmission completion check */
    while (MMC_TXEND_CHECK())                    /* Loop for transmission completion    */
    {
        MMC_CSI_TX_TIMEOUT_CHK(TxWait , __LINE__);
    }
    /* Clear IR bit of IR register */
    MMC_TXNEXT_CLR();                           /* Transmission empty flag clear   */
    MMC_CSI_TX_DI();                            /* CSI transmit disable      */


    /* Calculation CRC-CCITT data acquisition */
    CrcBuf = R_ExchgCrc();

    /* CRC-CCITT data transmission */
    pwk = (uint8_t*) & CrcBuf;

    work[0] = *(pwk + 1);
    work[1] = *(pwk + 0);
    Ret = R_mmc_Sync_MultTx(MMC_CRC_SIZE, work);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    return MMC_OK;
}

/******************************************************************************
* Declaration  : int16_t R_mmc_Sync_DataIn(uint8_t *pData)
* Function Name: R_mmc_Sync_DataIn
* Description  : Receive data for the specified byte and CRC-CCITT, and check CRC-CCITT.
* Argument     : uint8_t   *pData   ; Recieve data storage buffer pointer
* Return Value : MMC_OK             ; Success
*              : MMC_ERR_HARD       ; Hardware Error
*              : MMC_ERR_CRC        ; CRC check error
******************************************************************************/
int16_t R_mmc_Sync_DataIn(uint8_t *pData)
{
    natural_uint_t   RxCnt = MMC_BLK_SIZE;
#if !defined(MMC_NOCHK_TIMEOUT)
    natural_uint_t   RxWait = MMC_CSI_RX_WAIT;   /* Receive waiting counter      */
#endif /* #if !defined(MMC_NOCHK_TIMEOUT) */
    MMC_EXCHG_SHORT  CrcBuf;                     /* Receive CRC-CCITT data buffer    */
    uint16_t         CrcData;                    /* Calculation CRC-CCITT data storage buffer */
    int16_t          Ret;
    uint8_t          RxData;
    uint8_t          work[MMC_CRC_SIZE];


    work[0] = 0xff;
    MMC_CRC_CLR();
    MMC_CSI_TRX_EI();                            /* CSI transmit&receive enable     */

    if (RxCnt > 0)
    {
        MMC_CSI_TXBUF  = MMC_DUMMY_DATA;
        RxCnt--;

        while (RxCnt != 0)
        {
            while (MMC_RX_COMPLETE_CHECK())
            {
                MMC_CSI_ORERR_CHK(__LINE__);
                MMC_CSI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
            }
            /* Receive data -> Receive data buffer */
            MMC_RXNEXT_CLR();
            RxData = MMC_CSI_RXBUF;

            MMC_CSI_TXBUF  = MMC_DUMMY_DATA;

            MMC_BIT_EXCHG(RxData);
            *pData++ = RxData;                   /* Receive data taking */
            MMC_CRC_SET(RxData);                 /* CRC-CCITT calculation      */
            RxCnt--;
        }

        while (MMC_RX_COMPLETE_CHECK())
        {
            MMC_CSI_ORERR_CHK(__LINE__);
            MMC_CSI_TRX_TIMEOUT_CHK(RxWait , __LINE__);
        }
        /* Receive data -> Receive data buffer */
        RxData = MMC_CSI_RXBUF;                  /* Receive data taking       */
        MMC_BIT_EXCHG(RxData);
        *pData = RxData;
        MMC_CRC_SET(RxData);                     /* CRC-CCITT calculation      */
    }
    /* Clear IR bit of IR register */
    MMC_CSI_TRX_DI();                            /* CSI transmit&receive disable    */

    /* Calculation CRC-CCITT data acquisition */
    CrcData = R_ExchgCrc();

    Ret = R_mmc_Sync_Rx(MMC_CRC_SIZE, work);
    if (Ret < MMC_OK)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return Ret;
    }

    CrcBuf.uc[1] = work[0];
    CrcBuf.uc[0] = work[1];

    /* CRC check */
    if (CrcData != CrcBuf.us)
    {
        R_mtl_Log(MMC_LOG_ERR, 0, MMC_FID, __LINE__);
        return MMC_ERR_CRC;
    }

    return MMC_OK;
}

#endif /* #if defined(MMC_CSI_USED) */
