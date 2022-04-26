/*
 * Sd2Card.cpp
 *
 *  Created on: 2022/02/xx
 *      Author: Renesas Electronics
 */

#include "Sd2Card.h"

extern "C"
{
  extern void R_mmc_Init_Driver (void);
  extern void   R_init_card_detect_chat (void);
  extern DSTATUS R_tfat_disk_initialize (uint8_t drive);
}

/**
 * SD/MMCドライバを初期化します
 *
 * @param[in] drive     初期化するドライブ番号
 *
 * @return      成功時:true 失敗時:false
 *
 * @attention   none
 */
boolean Sd2Card::init (uint8_t drive)
{

  noInterrupts();
  /* Initialize MMC driver. */
  R_mmc_Init_Driver ();

  /* Initialize card detect chattering. */
  R_init_card_detect_chat ();

  /* Check if the Card has been inserted  */
  _Stat = TFAT_STA_NOINIT;
  while ((_Stat & (TFAT_STA_NODISK | TFAT_STA_NOINIT)) != 0)
    {
      /* If the card is not inserted then stop here. */
      _Stat = R_tfat_disk_initialize (drive);
    }
  interrupts();

  return (TFAT_RES_OK == _Stat);
}
