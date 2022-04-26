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
* Copyright (C) 2011(2012) Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/

/*""FILE COMMENT""*******************************************************************
* File Name     : r_tfat_drv_if.c
* Version       : 1.00
* Device(s)     : Renesas MCUs
* Tool-Chain    : -
* H/W Platform  : -
* Description   : TFAT FS memory driver interface file
*************************************************************************************
* History       : DD.MM.YYYY Version Description
*""FILE COMMENT END""****************************************************************/

/******************************************************************************
Includes <System Includes> , "Project Includes"
******************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_stdint.h"
#include "r_TinyFAT.h"
#include "r_mtl_com.h"
#include "r_mmc.h"

/******************************************************************************
Exported global variables and functions (to be accessed by other files)
******************************************************************************/
/* Real Time Clock - Time set to 23 FEB 2009 15:02:20 */
uint8_t g_rtcYear = 109;
uint8_t g_rtcMon  = 2;
uint8_t g_rtcMday = 23;
uint8_t g_rtcHour = 15;
uint8_t g_rtcMin  = 2;
uint8_t g_rtcSec  = 20;

MMC_INFO card_info;

void R_countup_clock(void);

extern int16_t R_card_insertion_chk(uint8_t slot_num);
extern void R_init_card_detect_chat(void);

/******************************************************************************
Macro definitions
******************************************************************************/
#define ENABLE_IRQ()  EI()
#define DISABLE_IRQ() DI()

/*""FUNC COMMENT""*******************************************************************
* Function Name : R_tfat_disk_initialize
* Include       : r_tfat_drv_if.h
* Declaration   : DSTATUS R_tfat_disk_initialize ()
* Description   : This function initializes the memory medium for file operations
* Arguments     : none
* Return value  : Status of the memory medium
*""FUNC COMMENT END""****************************************************************/
DSTATUS R_tfat_disk_initialize(uint8_t drive)
{
    /* Please put the code for disk_initalize driver interface function over here */
    /* Please refer the application note for details                              */
    /* Please put the code for memory driver initialization, if any, over here    */
    int16_t ret_value;

    (void) drive;

    ret_value = R_card_insertion_chk(MMC_SLOT0);
    if (ret_value < MMC_OK)
    {
        R_init_card_detect_chat();
        return TFAT_STA_NODISK;
    }

    if (ret_value != MMC_TRUE)
    {
        return TFAT_STA_NODISK;
    }

    ret_value = R_mmc_Init_Slot(MMC_SLOT0);
    if (ret_value < MMC_OK)
    {
        R_init_card_detect_chat();
        return TFAT_STA_NOINIT;
    }

    ret_value = R_mmc_Get_MmcInfo(MMC_SLOT0, &card_info);
    if (ret_value < MMC_OK)
    {
        R_init_card_detect_chat();
        return TFAT_STA_NOINIT;
    }

    return  TFAT_RES_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name : R_tfat_disk_read
* Include       : r_tfat_drv_if.h
* Declaration   : DRESULT R_tfat_disk_read (uint8_t Drive, uint8_t* Buffer, uint32_t SectorNumber, uint8_t SectorCount)
* Description   : This function reads data from the specified location of the memory medium
* Arguments     : uint8_t  Drive        : Physical drive number
*               : uint8_t* Buffer       : Pointer to the read data buffer
*               : uint32_t SectorNumber : uint32_t SectorNumber
*               : uint8_t SectorCount   : Number of sectors to read
* Return value  : Result of function execution
*""FUNC COMMENT END""****************************************************************/
DRESULT R_tfat_disk_read(
    uint8_t Drive,         /* Physical drive number            */
    uint8_t* Buffer,       /* Pointer to the read data buffer  */
    uint32_t SectorNumber, /* Start sector number              */
    uint8_t SectorCount    /* Number of sectors to read        */
)
{
    /* Please put the code for R_tfat_disk_read driver interface function over here */
    /* Please refer the application note for details                                */
    int16_t  Ret;

    Ret = R_mmc_Read_Data(0, SectorNumber, SectorCount, Buffer, MMC_MODE_NORMAL);
    if (Ret < MMC_OK)
    {
        return TFAT_RES_ERROR;
    }
    return TFAT_RES_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name : R_tfat_disk_write
* Include       : r_tfat_drv_if.h
* Declaration   : DRESULT R_tfat_disk_write (uint8_t Drive, const uint8_t* Buffer, uint32_t SectorNumber, uint8_t SectorCount)
* Description   : This function writes data to a specified location of the memory medium
* Arguments     : uint8_t Drive : Physical drive number
*               : const uint8_t* Buffer       : Pointer to the write data
*               : uint32_t       SectorNumber : Sector number to write
*               : uint8_t        SectorCount  : Number of sectors to write
* Return value  : Result of function execution
*""FUNC COMMENT END""****************************************************************/
DRESULT R_tfat_disk_write(
    uint8_t Drive,          /* Physical drive number        */
    const uint8_t* Buffer,  /* Pointer to the write data    */
    uint32_t SectorNumber,  /* Sector number to write       */
    uint8_t SectorCount     /* Number of sectors to write   */
)
{
    /* Please put the code for R_tfat_disk_write driver interface function over here */
    /* Please refer the application note for details                                 */
    int16_t Ret;

    Ret = R_mmc_Write_Data(0, SectorNumber, SectorCount, (uint8_t *)Buffer, MMC_MODE_NORMAL);
    if (Ret < MMC_OK)
    {
        return TFAT_RES_ERROR;
    }
    return TFAT_RES_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name : R_tfat_disk_ioctl
* Include       : r_tfat_drv_if.h
* Declaration   : DRESULT R_tfat_disk_ioctl (uint8_t Drive, uint8_t Command, void* Buffer)
* Description   : This function is used to execute memory operations other than read\write
* Arguments     : uint8_t Drive   : Drive number
*               : uint8_t Command : Control command code
*               : void*   Buffer  : Data transfer buffer
* Return value  : Result of function execution
*""FUNC COMMENT END""****************************************************************/
DRESULT R_tfat_disk_ioctl(
    uint8_t Drive,          /* Drive number          */
    uint8_t Command,        /* Control command code  */
    void* Buffer            /* Data transfer buffer  */
)
{
    /* Please put the code for R_tfat_disk_ioctl driver interface function over here */
    /* Please refer the application note for details                                 */
    return TFAT_RES_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name : R_tfat_disk_status
* Include       : r_tfat_drv_if.h
* Declaration   : DSTATUS R_tfat_disk_status (uint8_t Drive)
* Description   : This function is used to retrieve the current status of the disk
* Arguments     : uint8_t Drive : Physical drive number
* Return value  : Status of the disk
*""FUNC COMMENT END""****************************************************************/
DSTATUS R_tfat_disk_status(
    uint8_t Drive           /* Physical drive number  */
)
{
    /* Please put the code for R_tfat_disk_status driver interface function over here */
    /* Please refer the application note for details                                  */
    return TFAT_RES_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name : R_tfat_get_fattime
* Include       : r_tfat_sample_software.h
* Declaration   : void R_tfat_get_fattime(void)
* Description   : This function returns the current date and time
* Arguments     : none
* Return value  : uint32_t
* NOTE          : Please DO NOT modify this function. This function is used by the FAT
                : library to get the current date and time during file manipulations.
*""FUNC COMMENT END""****************************************************************/
uint32_t R_tfat_get_fattime(void)
{
    uint32_t tmr;

    /* Disable interrupts */
    DISABLE_IRQ();

    /* Convert the time to store in FAT entry  */
    tmr = (((uint32_t)g_rtcYear - 80) << 25);
    tmr |= ((uint32_t)g_rtcMon << 21);
    tmr |= ((uint32_t)g_rtcMday << 16);
    tmr |= ((uint32_t)g_rtcHour << 11);
    tmr |= ((uint32_t)g_rtcMin << 5);
    tmr |= ((uint32_t)g_rtcSec >> 1);

    /* Enable interrupts */
    ENABLE_IRQ();

    return tmr;
}




/*""FUNC COMMENT""*******************************************************************
* Function Name : R_countup_clock
* Include       :
* Declaration   : void R_countup_clock(void);
* Description   : This interrupt service routine increments the real time clock every second
* Arguments     : none
* Return value  : none
*""FUNC COMMENT END""****************************************************************/
void R_countup_clock(void)
{
    static const uint8_t stTime[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    uint8_t n;

    if (++g_rtcSec >= 60)
    {
        g_rtcSec = 0;
        if (++g_rtcMin >= 60)
        {
            g_rtcMin = 0;
            if (++g_rtcHour >= 24)
            {
                g_rtcHour = 0;
                n = stTime[g_rtcMon - 1];
                if ((n == 28) && !(g_rtcYear & 3))
                {
                    n++;
                }
                if (++g_rtcMday > n)
                {
                    g_rtcMday = 1;
                    if (++g_rtcMon > 12)
                    {
                        g_rtcMon = 1;
                        g_rtcYear++;
                    }
                }
            }
        }
    }
}
