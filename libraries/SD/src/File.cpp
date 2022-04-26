/**
 * PURPOSE
 *   File.cpp
 *
 * TARGET DEVICE
 *   RL78/G23
 *
 * AUTHOR
 *   Renesas Electronics Corp.
 *
 *  Created on: 2022/02/xx
 */
/**
 * @file  File.cpp
 * @brief
 */


#include "SD.h"

/**
 * Private Function
 */

/**
 * Extracts the directory path from the specified filepath
 *
 * @param filepath[in]      File / directory path to check
 * @param isfile[in]        Flag if filepath is a file
 *
 * @return 成功時:true 失敗時:false
 *
 * @attention none
 */
boolean File::setParentDirPath (const uint8_t *filepath, bool isfile)
{
  uint16_t idx;

  for (idx = strlen ((char*) filepath) - 1; 0 < idx; idx--)
  {
    if ('/' == filepath[idx])
    {
      break;
    }
  }

  if (idx >= strlen ((char*) filepath) - 1)
  {
    strcpy ((char*) _data->name, "/");
  }
  else
  {
    strncpy ((char*) _data->name, (char*) filepath + idx + 1, 12);
    _data->name[12] = 0;
  }

  if (isfile)
  {
    memset (_data->dirPath, 0, idx);
    return (0 != strncpy ((char*) _data->dirPath, (char*) filepath, idx));
  }
  else
  {
    return true;
  }

}

/**
 * Generate filename by combining specified dirpath and filename
 *
 * @param[in] dirpath       Directory path
 * @param[in] filename      file name
 * @param[out] combinedpath Generated file path
 *
 * @return none
 *
 * @attention none
 */
static int combineFilename (const uint8_t *dirpath,
                            const uint8_t *filename,
                            uint8_t *combinedpath)
{
  // Copy the directory path after initializing the combined path
  memset (combinedpath, 0, strlen ((char*) combinedpath));
  strncpy ((char*) combinedpath, (char*) dirpath, strlen ((char*) dirpath));
  if ('/' != combinedpath[strlen ((char*) combinedpath) - 1])
  {
    // Add ‘/’ if the end of the directory path does not appear ‘/’
    combinedpath[strlen ((char*) combinedpath)] = '/';
  }
  // Copy the file name after the directory path
  strncat ((char*) combinedpath, (char*) filename, strlen ((char*) filename));

  return 0;
}

/**
 * Public Function
 */

/**
 * File class constructor
 *
 * @attention none
 */
File::File (void)
{
  /* blank constructor */
  _data = 0;
}

/**
 * File class constructor
 *
 * @param dir[in]       Object information of the opened directory
 * @param path[in]      Opened directory path
 *
 * @attention none
 */
File::File (DIR dir, const uint8_t *path)
{
  /* constructor */
  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction.
   */

  _data = (filedata_t*) malloc (sizeof(filedata_t));
  memset (_data, 0, sizeof(filedata_t));
  strcpy ((char*) _data->dirPath, (char*) path);
  memcpy (&_data->dir, &dir, sizeof(DIR));
  setParentDirPath (path, 0);
  _data->isdir = 1;
}

/**
 * File class constructor
 *
 * @param file[in]      Object information of the opened file
 * @param path[in]      Opened file path
 *
 * @attention none
 */
File::File (FIL file, const uint8_t *path)
{
  /* constructor */
  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */

  _data = (filedata_t*) malloc (sizeof(filedata_t));
  memset (_data, 0, sizeof(filedata_t));
  strcpy ((char*) _data->filePath, (char*) path);
  memcpy (&_data->file, &file, sizeof(FIL));
  setParentDirPath (path, 1);
  _data->isdir = 0;

}

/**
 * File class destructor
 */
File::~File (void)
{
  /* destructor */

}

/**
 * Returns the name of the open file
 *
 * @return File name of the open file
 *
 * @attention none
 */
char* File::name (void)
{
  // Returns the file name
  return (char*) _data->name;
}

/**
 * Returns whether the open object is a directory
 *
 * @return For directories: true For files: false
 *
 * @attention none
 */
boolean File::isDirectory (void)
{

  // Returns whether it is a directory
  return (_data->isdir);
}

/**
 * Write 1 byte to an open file
 *
 * @param[in] val       Data to write
 *
 * @return none
 *
 * @attention none
 */
size_t File::write (uint8_t val)
{
  return write (&val, 1);
}

/**
 * Writes the length specified by size to the open file
 *
 * @param[in] buf       Pointer for data to write
 * @param[in] size      Number of bytes to write
 *
 * @return none
 *
 * @attention none
 */
size_t File::write (const uint8_t *buf, size_t size)
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */

  FRESULT ret;
  uint16_t rw_cnt;
  rw_cnt = 0;

  noInterrupts();
  // Write a string by specifying a file object.
  ret = R_tfat_f_write (&_data->file, buf, size, &rw_cnt);
  interrupts();
  if (size > rw_cnt)
  {
    return TFAT_FR_RW_ERROR;
  }
  return ret;
}

/**
 * Read 1 byte from an open file without changing the calling position
 *
 * @return Read data
 *
 * @attention none
 */
int File::peek ()
{

  char data;

  if (0 != read (&data, 1))
  {
    seek (_data->pos - 1);
    return (int) data;
  }
  return 0;
}

/**
 * Read 1 byte from an open file
 *
 * @return 読み出したデータ
 *
 * @attention none
 */
int File::read ()
{

  /* Read 1 byte from the current position */
  char data;

  if (0 != read (&data, 1))
  {
    return (int) data;
  }
  return -1;
}

/**
 *Reads the number of bytes specified by nbyte from the open file.
 *
 * @param[out] buf      Read data
 * @param[in] nbyte     Number of bytes to read
 *
 * @return 読み出したデータ数
 *
 * @attention none
 */
int File::read (void *buf, uint16_t nbyte)
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */
  FRESULT ret;
  uint16_t rw_cnt;
  rw_cnt = 0;

  noInterrupts();
  // Specify a file object and read the specified number of bytes of data
  ret = R_tfat_f_read (&_data->file, buf, nbyte, &rw_cnt);
  interrupts();
  if (TFAT_FR_OK == ret)
  {
    if (nbyte < rw_cnt)
    {
      return 0;
    }
    _data->pos += rw_cnt;
    return rw_cnt;
  }

  return 0;
}

/**
 * Write unwritten data in an open file
 *
 * @return none
 *
 * @attention none
 */
void File::flush ()
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */
  noInterrupts();
  R_tfat_f_sync (&_data->file);
  interrupts();

  return;
}

/**
 * Moves the read position from the file
 *
 * @param[in] pos       Read position (in bytes) counted from the beginning of the file
 *
 * @return On success: true. On failure: false.
 *
 * @attention none
 */
boolean File::seek(uint32_t pos)
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */
  FRESULT ret;

  _data->pos = pos;
  noInterrupts();
  // Moves the number of bytes specified by pos from the beginning of the file
  ret = R_tfat_f_lseek (&_data->file, pos);
  interrupts();
  return (TFAT_FR_OK == ret);
}

/**
 * Gets the current call position of an open file
 *
 * @return          Current call position
 *
 * @attention none
 */
uint32_t File::position()
{
  // Returns a read / write pointer value for a file object
  return _data->file.fptr;
}

/**
 * Gets the file size of an open file
 *
 * @return          file size
 *
 * @attention       Returns 0 for directories
 */
uint32_t File::size()
{

  return _data->file.fsize;
}

/**
 * Close the open file
 *
 * @return none
 *
 * @attention none
 */
void File::close()
{

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */

  noInterrupts();
  R_tfat_f_close (&_data->file);
  free(_data);
  interrupts();

}

/**
 * Check if there is data that can be read in the opened file
 *
 * @return If there is data: true If there is no data: false
 *
 * @attention none
 */
int File::available()
{

  /* Subtract the R / W pointer value from the size of the file object
     and if it is not 0, there is data
   */
  return (_data->file.fsize - _data->file.fptr);
}

/**
 * Check if the file is open
 *
 * @return When open: true When closed: false
 *
 * @attention none
 */
File::operator bool()
{

  /* File object / directory object file system object pointer is open if non-zero
   */
  return (0 != _data->file.fs || 0 != _data->dir.fs);
}

/**
 * Moves the search position of an open directory back to the beginning
 *
 * @return none
 *
 * @attention none
 */
void File::rewindDirectory(void)
{

  FRESULT ret;
  DIR dir;

  /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */

  noInterrupts();
  R_tfat_f_opendir (&dir, _data->dirPath);
  interrupts();
  memcpy (&_data->dir, &dir, sizeof(DIR));

  return;
}

/**
 * Returns the following file object from the list of files in an open directory
 *
 * @param[in] mode      Attributes when opening a file
 *
 * @return When exists: File object When does not exist: false
 *
 * @attention none
 */
File File::openNextFile(uint8_t mode)
{

   /**
   * attention： When using TinyFAT API, interrupt control to prevent malfunction
   */
  FRESULT ret;
  FILINFO info1;
  FILINFO info2;
  uint8_t nextfile[260];

  FIL file_;
  DIR dir_;

  memset (nextfile, 0, sizeof(nextfile));

  /* Get the file information in the directory
   * If index is 0: first file object
   * If index is greater than or equal to 1: Next file object
   */
  noInterrupts();
  ret = R_tfat_f_readdir (&_data->dir, &info2);
  interrupts();
  if (TFAT_FR_OK == ret)
  {
      if (0 == strlen ((char*) info2.fname))
      {
        // If the file name is null, it reaches the end
      }
      else
      {
        // Generate a file path with the directory path and the acquired file name (directory name)
        combineFilename (_data->dirPath, info2.fname, (uint8_t*) &nextfile);
      }
  }

  /* Open a file (directory)
   * If the file path is generated by preprocessing
   */
  if (0 != strlen ((char*) nextfile))
  {
    if (0 == info2.fsize)
    {
      // If the size of the file information is 0, it opens as a directory and returns a File object.
      noInterrupts();
      ret = R_tfat_f_opendir (&dir_, nextfile);
      interrupts();
      if (TFAT_FR_OK == ret)
      {
        return File (dir_, nextfile);
      }
    }
    else
    {
      // Opens a file and returns a File object
      noInterrupts();
      ret = R_tfat_f_open (&file_, nextfile, mode);
      interrupts();
      if (TFAT_FR_OK == ret)
      {
        return File (file_, nextfile);
      }
    }
  }

  // Returns false if not applicable
  return File ();

}

