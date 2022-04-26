/**
* PURPOSE
*    SD Library header file
*
* TARGET DEVICE
*    RL78/G23
*
* AUTHOR
*    Renesas Electronics Corp.
*
*/
/**
 * @file SD.h
 * @brief
 */


#ifndef __SD_H__
#define __SD_H__

#include <Arduino.h>

#include "Sd2Card.h"

extern "C"
{
#include "r_mmc.h"
#include "r_TinyFAT.h"
}

#define FILE_READ   TFAT_FA_READ
#define FILE_WRITE  (TFAT_FA_READ | TFAT_FA_WRITE | TFAT_FA_CREATE_ALWAYS)
#define FILE_READONLY FILE_READ

/**
 * File Class
 */
class File : public Stream
{
private:
  filedata_t *_data;  // underlying file pointer

  boolean
  setParentDirPath (const uint8_t *filepath, bool isfile);

public:
  File (DIR dir, const uint8_t *path);
  File (FIL file, const uint8_t *path);
  File (void);      // 'empty' constructor
  ~File (void);     // destructor
  virtual size_t
  write (uint8_t val);
  virtual size_t
  write (const uint8_t *buf, size_t size);
  int
  read ();
  int
  peek ();
  int
  available ();
  void
  flush ();
  int
  read (void *buf, uint16_t nbyte);
  boolean
  seek (uint32_t pos);
  uint32_t
  position ();
  uint32_t
  size ();
  void
  close ();
  operator bool ();
  char*
  name ();

  boolean
  isDirectory (void);
  File
  openNextFile (uint8_t mode = FILE_READONLY);
  void
  rewindDirectory (void);

  using Print::write;
};

/**
 * SDClass Class
 */
class SDClass
{

private:
  // These are required for initialisation and use of sdfatlib
  Sd2Card card;
  FATFS *_fatfs;

public:
  SDClass (unsigned char ch)
  {
    channel = ch;
    _fatfs = (FATFS*) malloc (sizeof(FATFS));
  }
  ;
  // This needs to be called to set up the connection to the SD card
  // before other methods are used.
  boolean begin (uint8_t csPin = SD_CHIP_SELECT_PIN);

  // Open the specified file/directory with the supplied mode (e.g. read or
  // write, etc). Returns a File object for interacting with the file.
  // Note that currently only one file can be open at a time.
  File open (const char *filename, uint8_t mode = FILE_READ);

  // Methods to determine if the requested file path exists.
  boolean exists (char *filepath);

  // Create the requested directory heirarchy--if intermediate directories
  // do not exist they will be created.
  boolean mkdir (char *filepath);

  // Delete the file.
  boolean remove (char *filepath);

  boolean rmdir (char *filepath);

private:

  // This is used to determine the mode used to open a file
  // it's here because it's the easiest place to pass the 
  // information through the directory walking function. But
  // it's probably not the best place for it.
  // It shouldn't be set directly--it is set via the parameters to `open`.
  unsigned char channel;

};

extern SDClass SD;
extern SDClass SD2;

static uint8_t g_slotNm;

#endif
