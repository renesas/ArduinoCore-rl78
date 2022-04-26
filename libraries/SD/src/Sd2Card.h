/*
 * Sd2Card.h
 *
 *  Created on: 2022/02/xx
 *      Author: Renesas Electronics
 */

#ifndef _SD2CARD_H_
#define _SD2CARD_H_

#include "Arduino.h"

extern "C"
{
#include "r_TinyFAT.h"
}

#define SD_CHIP_SELECT_PIN  10


class Sd2Card
{

private:
  DSTATUS _Stat;

public:
  boolean
  init (uint8_t drive);

};

typedef struct st_filedata
{
  DIR dir;
  FIL file;
  uint8_t dirPath[260];
  uint8_t filePath[260];
  uint32_t pos;
  uint8_t name[13];
  uint8_t isdir;
} filedata_t;

#endif /* _SD2CARD_H_ */
