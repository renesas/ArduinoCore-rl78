/*
 * SD.cpp
 *
 *  Created on: 2022/02/xx
 *      Author: Renesas Electronics
 */

#include "SD.h"

SDClass SD (1);
SDClass SD2 (2);

/**
 * Private Function
 **/

/**
 * Sets the workspace to the media specified by slot.
 * @param[in] slot          Media slot number
 * @param[in/out] fs        File system object variable pointer
 * @return Success: true / Failure: false
 *
 * @attention none
 */
static boolean mount (uint8_t slot, FATFS *fs)
{
  FRESULT ret;
  g_slotNm = slot;

  noInterrupts();
  memset (fs, 0, sizeof(FATFS));
  ret = R_tfat_f_mount (g_slotNm, fs);
  interrupts();

  return (TFAT_FR_OK == ret);
}

/**
 * Gets the file information specified by filepath.
 * @param[in] filepath      A string representing the file / directory path
 * @param[out] info         Pointer for file information variable
 * @return Success: true / Failure: false
 *
 * @attention none
 */
static boolean getStat (const char *filepath, FILINFO *info)
{
  FRESULT ret;

  noInterrupts();
  ret = R_tfat_f_stat ((uint8_t*) filepath, info);
  interrupts();
  delayMicroseconds(1);

  if (TFAT_FR_OK != ret)
  {
    return false;
  }

  return true;
}

/**
 * Public Function
 **/

/**
 * Initialize SDClass
 *
 * @param[in] csPin       Pin number of CS pin
 *
 * @return none
 *
 * @attention none
 */
boolean SDClass::begin (uint8_t csPin)
{

  // SD / MMC driver initialization
  if (card.init (channel - 1))
    {
      // Mount the media slot after driver initialization
      return mount ((channel - 1), _fatfs);
    }
  return false;
}

/**
 * Opens the file specified by filepath
 *
 * @param[in] filepath      File name you want to open
 * @param[in] mode          Specify the attribute when opening (read: FILE_READ, write: FILE_WRITE)
 *
 * @return On success: Returns a File object. On failure: Returns false.
 *
 * @attention none
 */
File SDClass::open (const char *filepath, uint8_t mode)
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction.
   */

  FRESULT ret;
  FIL file_;
  DIR dir_;

  noInterrupts();
  // Open the file according to the specified mode
  ret = R_tfat_f_open (&file_, (uint8_t*) filepath, mode);
  interrupts();
  if (TFAT_FR_OK == ret) {
    /* If the file can be opened, the File class is initialized and returned
      with the acquired file object as a parameter.
     */
    return File (file_, (uint8_t*) filepath);
  }
  else
  {
    noInterrupts();
    // If it cannot be opened as a file, it will be opened as a directory.
    ret = R_tfat_f_opendir (&dir_, (uint8_t*) filepath);
    interrupts();
    if (TFAT_FR_OK == ret)
    {
      /* If the directory can be opened, the File class is initialized and returned
        with the acquired directory object as a parameter.
       */
      return File (dir_, (uint8_t*) filepath);
    }
    else
    {
      // Returns false if the specified filepath is invalid
      return File ();
    }
  }
}

/**
 * Check if the desired file exists
 *
 * @param[in] filepath      File name you want to look up
 *
 * @return File exists: true. File does not exist or media not found: false.
 *
 * @attention none
 */
boolean SDClass::exists (char *filepath)
{

  FILINFO info_;
  // Get file information and check if the specified filepath exists
  return getStat (filepath, &info_);

}

/**
 * Create a directory
 *
 * @param[in] filepath      Directory name you want to create
 *
 * @return On success: true. On failure: false.
 *
 * @attention none
 */
boolean SDClass::mkdir (char *filepath)
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */

  FRESULT ret;
  FILINFO info;

  if (getStat(filepath, &info))
  {
    // directory already exists.
    return false;
  }

  noInterrupts();
  // Create a new directory with a specified path
  ret = R_tfat_f_mkdir ((uint8_t*) filepath);
  interrupts();
  if (TFAT_FR_OK != ret)
    {
      return false;
    }

  return true;
}

/**
 * Delete the directory
 *
 * @param[in] filepath      Directory name you want to delete
 *
 * @return On success: true On failure: false
 *
 * @attention none
 */
boolean SDClass::rmdir (char *filepath)
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */

  FRESULT ret;
  FILINFO info_;

  // Get the information of the specified filepath
  if (!getStat (filepath, &info_))
  {
    return false;
  }

  // Check if the specified filepath is a directory
  if (TFAT_AM_DIR != (info_.fattrib & TFAT_AM_DIR))
  {
    return false;
  }

  noInterrupts();
  // Delete directory
  ret = R_tfat_f_unlink ((uint8_t*) filepath);
  interrupts();

  if (TFAT_FR_OK != ret)
  {
    return false;
  }

  return true;
}

/**
 * Deletes the specified file
 *
 * @param[in] filepath      File name you want to delete
 *
 * @return On success: true On failure: false
 *
 * @attention none
 */
boolean SDClass::remove (char *filepath)
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */

  FRESULT ret;
  FILINFO info_;

  // Get the information of the specified filepath
  if (!getStat (filepath, &info_))
  {
    return false;
  }

  // Check if the specified filepath is a directory
  if (TFAT_AM_DIR == (info_.fattrib & TFAT_AM_DIR))
  {
    return false;
  }

  noInterrupts();
  // Delete file
  ret = R_tfat_f_unlink ((uint8_t*) filepath);
  interrupts();

  if (TFAT_FR_OK != ret)
  {
    return false;
  }

  return true;
}

