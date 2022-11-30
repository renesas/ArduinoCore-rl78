/*""FILE COMMENT""*******************************************************************
* File Name		: r_TinyFAT.h
* Version      	:
* Device(s)    	: Renesas MCUs
* Tool-Chain 	:
* H/W Platform 	:
* Description	: TFAT FS library header file
*************************************************************************************
* History	: DD.MM.YYYY Version Description
* 			: 15.06.2010 1.00	 First Release
* 			: 20.07.2012 1.01	 Added Version Information strcture and macro
*""FILE COMMENT END""****************************************************************/

/*----------------------------------------------------------------------------/
/  FatFs - Tiny FAT file system module  R0.06                 (C)ChaN, 2008
/-----------------------------------------------------------------------------/
/ The FatFs module is an experimenal project to implement FAT file system to
/ cheap microcontrollers. This is a free software and is opened for education,
/ research and development under license policy of following trems.
/
/  Copyright (C) 2008, ChaN, all right reserved.
/
/ * The FatFs module is a free software and there is no warranty.
/ * You can use, modify and/or redistribute it for personal, non-profit or
/   commercial use without any restriction under your responsibility.
/ * Redistributions of source code must retain the above copyright notice.
/
/-----------------------------------------------------------------------------/
*/

#ifndef _R_TINYFAT_H_
#define _R_TINYFAT_H_

#include "r_stdint.h"
#include "r_mw_version.h"

/**********************************************************************************
Macro Defines
***********************************************************************************/
/* The _TFAT_MCU_ENDIAN defines which access method is used to the FAT structure.
  1: Little Endian (Enable word access)
  2: Big Endian (Disable word access and use byte-by-byte access instead.)	*/
#if (defined(__RX) && defined(__BIG)) ||\
        (defined(_SH))  ||\
        (defined (__ICCRL78__))	||\
        (defined(__K0R__) ) ||\
        (defined(__CCRL__)) ||\
        (defined(__llvm__) && defined(__RL78__))
#define _TFAT_MCU_ENDIAN        2
#elif ((defined(__RX) && defined(__LIT)) ||\
		(defined(__v850)) )
#define _TFAT_MCU_ENDIAN		1
#endif
/* Setting _TFAT_FS_READONLY to 1 defines read only configuration.
   This exclude following writing functions -
   R_tfat_f_write, R_tfat_f_sync, R_tfat_f_unlink, R_tfat_f_mkdir, R_tfat_f_chmod, R_tfat_f_rename, R_tfat_f_truncate,
   R_tfat_f_getfree and internal write action. */
#define _TFAT_FS_READONLY       0

/* The _TFAT_FS_MINIMIZE option defines minimization level to exclude some functions.
  0: All functions included.
  1: R_tfat_f_stat, R_tfat_f_getfree, R_tfat_f_unlink, R_tfat_f_mkdir, R_tfat_f_chmod, R_tfat_f_truncate and R_tfat_f_rename are excluded.
  2: R_tfat_f_opendir and R_tfat_f_readdir are excluded in addition to level 1.
  3: R_tfat_f_lseek is excluded in addition to level 2. */
#define _TFAT_FS_MINIMIZE       0

/* To enable string functions, set _TFAT_USE_STRFUNC to 1 */
#define _TFAT_USE_STRFUNC       0

/* To enable R_tfat_f_forward function, set _TFAT_USE_FORWARD to 1. */
#define _TFAT_USE_FORWARD       1

/* To enable FAT32 support in addition of FAT12/16, set _TFAT_FAT32 to 1. */
#define _TFAT_FAT32             1

/* To enable FSInfo support on FAT32 volume, set _TFAT_USE_FSINFO to 1. */
#define _TFAT_USE_FSINFO        1

/* When _TFAT_USE_SJIS is set to 1, Shift-JIS code transparency is enabled, otherwise
   only US-ASCII(7bit) code can be accepted as file/directory name. */
#define _TFAT_USE_SJIS          1

/* When _TFAT_USE_NTFLAG is set to 1, upper/lower case of the file name is preserved.
   Note that the files are always accessed in case insensitive. */
#define _TFAT_USE_NTFLAG        1

/* File access control and file status flags (FIL.flag) */
#define TFAT_FA_OPEN_EXISTING   0x00
#define TFAT_FA_READ            0x01
#define TFAT_FA__ERROR          0x80

#if !_TFAT_FS_READONLY
#define TFAT_FA_WRITE           0x02
#define TFAT_FA_CREATE_NEW      0x04
#define TFAT_FA_CREATE_ALWAYS   0x08
#define TFAT_FA_OPEN_ALWAYS     0x10
#define TFAT_FA__WRITTEN        0x20
#endif

/* FAT sub type (FATFS.fs_type) */

#define TFAT_FS_FAT12           1
#define TFAT_FS_FAT16           2
#define TFAT_FS_FAT32           3

/* File attribute bits for directory entry */
#define TFAT_AM_RDO             0x01    /* Read only */
#define TFAT_AM_HID             0x02    /* Hidden */
#define TFAT_AM_SYS             0x04    /* System */
#define TFAT_AM_VOL             0x08    /* Volume label */
#define TFAT_AM_LFN             0x0F    /* LFN entry */
#define TFAT_AM_DIR             0x10    /* Directory */
#define TFAT_AM_ARC             0x20    /* Archive */

/* Offset of FAT structure members */
#define TFAT_BS_jmpBoot         0
#define TFAT_BS_OEMName         3
#define TFAT_BPB_BytsPerSec     11
#define TFAT_BPB_SecPerClus     13
#define TFAT_BPB_RsvdSecCnt     14
#define TFAT_BPB_NumFATs        16
#define TFAT_BPB_RootEntCnt     17
#define TFAT_BPB_TotSec16       19
#define TFAT_BPB_Media          21
#define TFAT_BPB_FATSz16        22
#define TFAT_BPB_SecPerTrk      24
#define TFAT_BPB_NumHeads       26
#define TFAT_BPB_HiddSec        28
#define TFAT_BPB_TotSec32       32
#define TFAT_BS_55AA            510

#define TFAT_BS_DrvNum          36
#define TFAT_BS_BootSig         38
#define TFAT_BS_VolID           39
#define TFAT_BS_VolLab          43
#define TFAT_BS_FilSysType      54

#define TFAT_BPB_FATSz32        36
#define TFAT_BPB_ExtFlags       40
#define TFAT_BPB_FSVer          42
#define TFAT_BPB_RootClus       44
#define TFAT_BPB_FSInfo         48
#define TFAT_BPB_BkBootSec      50
#define TFAT_BS_DrvNum32        64
#define TFAT_BS_BootSig32       66
#define TFAT_BS_VolID32         67
#define TFAT_BS_VolLab32        71
#define TFAT_BS_FilSysType32    82

#define TFAT_FSI_LeadSig        0
#define TFAT_FSI_StrucSig       484
#define TFAT_FSI_Free_Count     488
#define TFAT_FSI_Nxt_Free       492

#define TFAT_MBR_Table          446

#define TFAT_DIR_Name           0
#define TFAT_DIR_Attr           11
#define TFAT_DIR_NTres          12
#define TFAT_DIR_CrtTime        14
#define TFAT_DIR_CrtDate        16
#define TFAT_DIR_FstClusHI      20
#define TFAT_DIR_WrtTime        22
#define TFAT_DIR_WrtDate        24
#define TFAT_DIR_FstClusLO      26
#define TFAT_DIR_FileSize       28

/* Multi-byte word access macros  */
#if _TFAT_MCU_ENDIAN == 1	/* Use word access */
#define	TFAT_LD_WORD(ptr)		(uint16_t)(*(uint16_t*)(uint8_t*)(ptr))
#define	TFAT_LD_DWORD(ptr)		(uint32_t)(*(uint32_t*)(uint8_t*)(ptr))
#define	TFAT_ST_WORD(ptr,val)	*(uint16_t*)(uint8_t*)(ptr)=(uint16_t)(val)
#define	TFAT_ST_DWORD(ptr,val)	*(uint32_t*)(uint8_t*)(ptr)=(uint32_t)(val)
#elif _TFAT_MCU_ENDIAN == 2	/* Use byte-by-byte access */
#define	TFAT_LD_WORD(ptr)		(uint16_t)(((uint16_t)*(volatile uint8_t*)((ptr)+1)<<8)|(uint16_t)*(volatile uint8_t*)(ptr))
#define	TFAT_LD_DWORD(ptr)		(uint32_t)(((uint32_t)*(volatile uint8_t*)((ptr)+3)<<24)|((uint32_t)*(volatile uint8_t*)((ptr)+2)<<16)|((uint16_t)*(volatile uint8_t*)((ptr)+1)<<8)|*(volatile uint8_t*)(ptr))
#define	TFAT_ST_WORD(ptr,val)	*(volatile uint8_t*)(ptr)=(uint8_t)(val); *(volatile uint8_t*)((ptr)+1)=(uint8_t)((uint16_t)(val)>>8)
#define	TFAT_ST_DWORD(ptr,val)	*(volatile uint8_t*)(ptr)=(uint8_t)(val); *(volatile uint8_t*)((ptr)+1)=(uint8_t)((uint16_t)(val)>>8); *(volatile uint8_t*)((ptr)+2)=(uint8_t)((uint32_t)(val)>>16); *(volatile uint8_t*)((ptr)+3)=(uint8_t)((uint32_t)(val)>>24)
#else
#error Do not forget to set _TFAT_MCU_ENDIAN properly!
#endif

/* 1: Read-only mode */
#define _TFAT_READONLY	0
#define _TFAT_USE_IOCTL	1

/* Disk Status Bits (DSTATUS) */

/* Drive not initialized */
#define TFAT_STA_NOINIT         0x01
/* No medium in the drive */
#define TFAT_STA_NODISK         0x02
/* Write protected */
#define TFAT_STA_PROTECT        0x04

/* Command code for disk_ioctrl() */

/* Generic command */
/* Mandatory for write functions */
#define TFAT_CTRL_SYNC          0
/* Mandatory for only f_mkfs() */
#define TFAT_GET_SECTOR_COUNT   1
#define TFAT_GET_SECTOR_SIZE    2
/* Mandatory for only f_mkfs() */
#define TFAT_GET_BLOCK_SIZE     3
#define TFAT_CTRL_POWER         4
#define TFAT_CTRL_LOCK          5
#define TFAT_CTRL_EJECT         6

/* MMC/SDC command */
#define TFAT_MMC_GET_TYPE       10
#define TFAT_MMC_GET_CSD        11
#define TFAT_MMC_GET_CID        12
#define TFAT_MMC_GET_OCR        13
#define TFAT_MMC_GET_SDSTAT     14

/* ATA/CF command */
#define TFAT_ATA_GET_REV        20
#define TFAT_ATA_GET_MODEL      21
#define TFAT_ATA_GET_SN         22

/**********************************************************************************
Type Defines
***********************************************************************************/
/* Boolean type */
typedef enum
{
    TFAT_FALSE = 0,
    TFAT_TRUE
} BOOL;

/* Status of Disk Functions */
typedef uint8_t	DSTATUS;

/* Results of Disk Functions */
typedef enum
{
    TFAT_RES_OK = 0,            /* 0: Successful */
    TFAT_RES_ERROR,             /* 1: R/W Error */
    TFAT_RES_WRPRT,             /* 2: Write Protected */
    TFAT_RES_NOTRDY,            /* 3: Not Ready */
    TFAT_RES_PARERR             /* 4: Invalid Parameter */
} DRESULT;

/* Type definition for cluster number */
#if _TFAT_FAT32
typedef uint32_t    CLUST;
#else
typedef uint16_t    CLUST;
#undef _TFAT_USE_FSINFO
#define _TFAT_USE_FSINFO    0
#endif

/* File system object structure */
typedef struct _FATFS
{
    uint16_t    id;         /* File system mount ID */
    uint16_t    n_rootdir;  /* Number of root directory entries */
    uint32_t    winsect;    /* Current sector appearing in the win[] */
    uint32_t    fatbase;    /* FAT start sector */
    uint32_t    dirbase;    /* Root directory start sector */
    uint32_t    database;   /* Data start sector */
    CLUST       sects_fat;  /* Sectors per fat */
    CLUST       max_clust;  /* Maximum cluster# + 1 */
#if !_TFAT_FS_READONLY
    CLUST       last_clust; /* Last allocated cluster */
    CLUST       free_clust; /* Number of free clusters */
#if _TFAT_USE_FSINFO
    uint32_t    fsi_sector; /* fsinfo sector */
    uint8_t     fsi_flag;   /* fsinfo dirty flag (1:must be written back) */
    uint8_t     pad1;
#endif
#endif
    uint8_t     fs_type;    /* FAT sub type */
    uint8_t     csize;      /* Number of sectors per cluster */
    uint8_t     n_fats;     /* Number of FAT copies */
    uint8_t     winflag;    /* win[] dirty flag (1:must be written back) */
    uint8_t     win[512];   /* Disk access window for Directory/FAT/File */
} FATFS;

/* Directory object structure */
typedef struct _DIR
{
    uint16_t    id;         /* Owner file system mount ID */
    uint16_t    index;      /* Current index */
    FATFS       *fs;        /* Pointer to the owner file system object */
    CLUST       sclust;     /* Start cluster */
    CLUST       clust;      /* Current cluster */
    uint32_t    sect;       /* Current sector */
} DIR;

/* File object structure */
typedef struct _FIL
{
    uint16_t    id;         /* Owner file system mount ID */
    uint8_t     flag;       /* File status flags */
    uint8_t     csect;      /* Sector address in the cluster */
    FATFS       *fs;        /* Pointer to owner file system */
    uint32_t    fptr;       /* File R/W pointer */
    uint32_t    fsize;      /* File size */
    CLUST       org_clust;  /* File start cluster */
    CLUST       curr_clust; /* Current cluster */
    uint32_t    curr_sect;  /* Current sector */
#if !_TFAT_FS_READONLY
    uint32_t    dir_sect;   /* Sector containing the directory entry */
    uint8_t     *dir_ptr;   /* Ponter to the directory entry in the window */
#endif
} FIL;

/* File status structure */
typedef struct _FILINFO
{
    uint32_t    fsize;      /* Size */
    uint16_t    fdate;      /* Date */
    uint16_t    ftime;      /* Time */
    uint8_t     fattrib;    /* Attribute */
    uint8_t     fname[8 + 1 + 3 + 1]; /* Name (8.3 format) */
} FILINFO;

/* File function return code (FRESULT) */
typedef enum
{
    TFAT_FR_OK = 0,         /* 0 */
    TFAT_FR_NOT_READY,      /* 1 */
    TFAT_FR_NO_FILE,        /* 2 */
    TFAT_FR_NO_PATH,        /* 3 */
    TFAT_FR_INVALID_NAME,   /* 4 */
    TFAT_FR_INVALID_DRIVE,  /* 5 */
    TFAT_FR_DENIED,         /* 6 */
    TFAT_FR_EXIST,          /* 7 */
    TFAT_FR_RW_ERROR,       /* 8 */
    TFAT_FR_WRITE_PROTECTED, /* 9 */
    TFAT_FR_NOT_ENABLED,    /* 10 */
    TFAT_FR_NO_FILESYSTEM,  /* 11 */
    TFAT_FR_INVALID_OBJECT, /* 12 */
    TFAT_FR_MKFS_ABORTED    /* 13 (not used) */
} FRESULT;

/**********************************************************************************
Function Prototypes
***********************************************************************************/
/* Mount a file system */
FRESULT R_tfat_f_mount(uint8_t, FATFS*);
/* Open or create a file */
FRESULT R_tfat_f_open(FIL*, const uint8_t*, uint8_t);
/* Read data from a file */
FRESULT R_tfat_f_read(FIL*, void*, uint16_t, uint16_t*);
/* Write data to a file */
FRESULT R_tfat_f_write(FIL*, const void*, uint16_t, uint16_t*);
/* Move file pointer of a file object */
FRESULT R_tfat_f_lseek(FIL*, uint32_t);
/* Close an open file object */
FRESULT R_tfat_f_close(FIL*);
/* Open an existing directory */
FRESULT R_tfat_f_opendir(DIR*, const uint8_t*);
/* Read a directory item */
FRESULT R_tfat_f_readdir(DIR*, FILINFO*);
/* Get file status */
FRESULT R_tfat_f_stat(const uint8_t*, FILINFO*);
/* Get number of free clusters on the drive */
FRESULT R_tfat_f_getfree(const uint8_t*, uint32_t*, FATFS**);
/* Truncate file */
FRESULT R_tfat_f_truncate(FIL*);
/* Flush cached data of a writing file */
FRESULT R_tfat_f_sync(FIL*);
/* Delete an existing file or directory */
FRESULT R_tfat_f_unlink(const uint8_t*);
/* Create a new directory */
FRESULT	R_tfat_f_mkdir(const uint8_t*);
/* Change file/dir attriburte */
FRESULT R_tfat_f_chmod(const uint8_t*, uint8_t, uint8_t);
/* Change file/dir timestamp */
FRESULT R_tfat_f_utime(const uint8_t*, const FILINFO*);
/* Rename/Move a file or directory */
FRESULT R_tfat_f_rename(const uint8_t*, const uint8_t*);
/* Forward data to the stream */
#if defined(__K0R__)
FRESULT R_tfat_f_forward(FIL*, uint16_t(*)(const uint8_t*, uint16_t), unsigned short, uint16_t*);
#else
FRESULT R_tfat_f_forward(FIL*, uint16_t(*)(const uint8_t*, uint16_t), uint16_t, uint16_t*);
#endif

#if _TFAT_USE_STRFUNC
#define feof(fp) ((fp)->fptr == (fp)->fsize)
#define EOF -1
/* Put a character to the file */
int16_t fputc(int16_t, FIL*);
/* Put a string to the file */
int16_t fputs(const uint8_t*, FIL*);
/* Put a formatted string to the file */
int16_t fprintf(FIL*, const uint8_t*, ...);
/* Get a string from the file */
uint8_t* fgets(uint8_t*, int16_t, FIL*);
#endif

/* External functions */

/* User defined function to give a current time to fatfs module */
/* 31-25: Year(0-127 +1980), 24-21: Month(1-12), 20-16: Day(1-31)
   15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
extern uint32_t R_tfat_get_fattime(void);

extern DSTATUS R_tfat_disk_initialize(uint8_t drive);
extern DSTATUS R_tfat_disk_status(uint8_t);
extern DRESULT R_tfat_disk_read(uint8_t, uint8_t*, uint32_t, uint8_t);

#if	_TFAT_READONLY == 0
extern DRESULT R_tfat_disk_write(uint8_t, const uint8_t*, uint32_t, uint8_t);
#endif

extern DRESULT R_tfat_disk_ioctl(uint8_t, uint8_t, void*);
extern void	disk_timerproc(void);

/* TFAT library version */
extern const mw_version_t R_tfat_version;

#endif /* _R_TINYFAT_H_ */
