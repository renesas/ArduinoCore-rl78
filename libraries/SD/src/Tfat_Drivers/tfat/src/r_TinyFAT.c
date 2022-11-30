/************************************************************************************

* DISCLAIMER

* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized.

* This software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.

* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY,
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY
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
************************************************************************************/

/* 	Copyright (C) 2010(2012) Renesas Electronics Corporation All rights reserved.  */

/*""FILE COMMENT""*******************************************************************
* File Name		: r_TinyFAT.c
* Version      	:
* Device(s)    	: Renesas MCU
* Tool-Chain 	:
* H/W Platform 	:
* Description	: Contains FAT handling functions
*************************************************************************************
* History	: DD.MM.YYYY Version Description
* 			: 15.06.2010 1.00	 First Release
* 			: 20.07.2012 1.01	 Moved Version Information to r_version.c
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

/**********************************************************************************
Include Files
***********************************************************************************/
/* Provides prototypes for string functions */
#include <string.h>
#include "r_stdint.h"
/* Tiny-FatFs declarations */
#include "r_TinyFAT.h"

/**********************************************************************************
Variable Defines
***********************************************************************************/
/* Pointer to the file system objects (logical drive) */
static FATFS *FatFs;
/* File system mount ID */
static uint16_t fsid;


/*""FUNC COMMENT""*******************************************************************
* Function Name	: move_window
* Description	: This function moves the sector window in win[]
* Arguments		: uint32_t sector
* Return value	: boolean
*""FUNC COMMENT END""****************************************************************/
static BOOL move_window(uint32_t sector)
{
	/* local variable to store the pointer to current sector 	*/
	uint32_t wsect;
	/* Get the structure of FAT	*/
	FATFS *fs = FatFs;

	/* Get the current sector appearing in the win[]	*/
	wsect = fs->winsect;

	/* Is current window changed? */
	if (wsect != sector)
	{
		/* Following code will only be executed if Read-Only configuration is disabled	*/
#if !_TFAT_FS_READONLY
		uint8_t n;

		/* Check "win[] dirty flag" if set we need to update the current sector entry in the FAT.
		   The "winflag" flag indicates whether the entry for current sector present in FAT is valid */
		if (fs->winflag)
		{
			/* Write the current sector information. If failed exit the function. 	*/
			if (R_tfat_disk_write(0, fs->win, wsect, 1) != TFAT_RES_OK)
				return TFAT_FALSE;

			/* Reset the winflag as we have written the new entry of the current sector */
			fs->winflag = 0;

			/* Check the FAT area */
			if (wsect < (fs->fatbase + fs->sects_fat))
			{
				/* Reflect the change to all FAT copies */
				for (n = fs->n_fats; n >= 2; n--)
				{
					/* Point to next entry */
					wsect += fs->sects_fat;
					/* Update the entry	*/
					R_tfat_disk_write(0, fs->win, wsect, 1);
				}
			}
		}
#endif		/* End of the loop to be executed with Read_Only condition. */

		/* Check if the sector number is valid	*/
		if (sector != 0)
		{
			/* Read the current sector information from the disk	*/
			if (R_tfat_disk_read(0, fs->win, sector, 1) != TFAT_RES_OK)
				return TFAT_FALSE;

			/* Update the sector information in FAT	*/
			fs->winsect = sector;
		}
	}

	/* return 1 if operation is successful	*/
	return TFAT_TRUE;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: sync
* Description	: Synchronizes the write data
* Arguments		: none
* Return value	: Result of execution
*""FUNC COMMENT END""****************************************************************/
#if !_TFAT_FS_READONLY
static FRESULT sync(void)
{
	/* Get the structure of FAT	*/
	FATFS *fs = FatFs;

	/* Make the current sector entry in FAT dirty & call the function "move_window"
	   to update the same. */
	fs->winflag = 1;
	if (!move_window(0))
		return TFAT_FR_RW_ERROR;

#if _TFAT_USE_FSINFO
	/* Update FSInfo sector if needed (i.e. for FAT32 file system) */
	if (fs->fs_type == TFAT_FS_FAT32 && fs->fsi_flag)
	{
		fs->winsect = 0;
		memset(fs->win, 0, 512U);
		TFAT_ST_WORD(&fs->win[TFAT_BS_55AA], 0xAA55);
		TFAT_ST_DWORD(&fs->win[TFAT_FSI_LeadSig], 0x41615252);
		TFAT_ST_DWORD(&fs->win[TFAT_FSI_StrucSig], 0x61417272);
		TFAT_ST_DWORD(&fs->win[TFAT_FSI_Free_Count], fs->free_clust);
		TFAT_ST_DWORD(&fs->win[TFAT_FSI_Nxt_Free], fs->last_clust);
		R_tfat_disk_write(0, fs->win, fs->fsi_sector, 1);
		fs->fsi_flag = 0;
	}
#endif

	/* Make sure that no pending write process in the physical drive */
	if (R_tfat_disk_ioctl(0, TFAT_CTRL_SYNC, NULL) != TFAT_RES_OK)
		return TFAT_FR_RW_ERROR;

	/* Syncronization is successful */
	return TFAT_FR_OK;
}
#endif	/* !_TFAT_FS_READONLY	*/

/*""FUNC COMMENT""*******************************************************************
* Function Name	: get_cluster
* Description	: Read the cluster information
* Arguments		: Cluster number
* Return value	: Cluster number to get the link information
*""FUNC COMMENT END""****************************************************************/
static CLUST get_cluster(CLUST clust)
{
	CLUST wc, bc;
	/* local variable to store the pointer to the required FAT sector 	*/
	uint32_t fatsect;
	/* Get the structure of FAT	*/
	FATFS *fs = FatFs;

	/* Check if the cluster number is valid */
	if (clust >= 2 && clust < fs->max_clust)
	{
		/* Point to FAT start sector	 */
		fatsect = fs->fatbase;

		/* Action depends upon the type of FAT filesystem	*/
		switch (fs->fs_type)
		{
				/* For FAT12 filesystem	*/
			case TFAT_FS_FAT12 :
				bc = (uint16_t)clust * 3 / 2;
				/* Check current window	*/
				if (!move_window(fatsect + bc / 512U))
					break;
				/* Check the sector boundry	*/
				wc = fs->win[bc % 512U];
				bc++;
				if (!move_window(fatsect + bc / 512U))
					break;
				wc |= (uint16_t)fs->win[bc % 512U] << 8;
				return (CLUST)(clust & 1) ? (wc >> 4) : (wc & 0xFFF);

				/* For FAT16 filesystem	*/
			case TFAT_FS_FAT16 :
				/* Consider the current window	*/
				if (!move_window(fatsect + clust / 256))
					break;
				return (CLUST)TFAT_LD_WORD(&fs->win[((uint16_t)clust * 2) % 512U]);
#if _TFAT_FAT32
				/* For FAT32 filesystem	*/
			case TFAT_FS_FAT32 :
				if (!move_window(fatsect + clust / 128))
					break;
				return TFAT_LD_DWORD(&fs->win[((uint16_t)clust * 4) % 512U]) & 0x0FFFFFFF;
#endif
		}
	}
	/* Out of cluster range, or an error occured */
	return 1;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: put_cluster
* Description	: Change the cluster information
* Arguments		: Cluster number to change (must be 2 to fs->max_clust-1)
				  New value to mark the cluster
* Return value	: Cluster number to get the link information
*""FUNC COMMENT END""****************************************************************/
#if !_TFAT_FS_READONLY
static BOOL put_cluster(CLUST clust, CLUST val)
{
	uint16_t bc;
	uint8_t *p;
	/* local variable to store the pointer to the required FAT sector 	*/
	uint32_t fatsect;
	/* Get the structure of FAT	*/
	FATFS *fs = FatFs;

	/* Point to FAT start sector	 */
	fatsect = fs->fatbase;
	switch (fs->fs_type)
	{
		case TFAT_FS_FAT12 :
			bc = (uint16_t)clust * 3 / 2;
			/* Update the current sector information, If failed, returns 0	*/
			if (!move_window(fatsect + bc / 512U))
				return TFAT_FALSE;
			/* Gets info about current window	*/
			p = &fs->win[bc % 512U];
			*p = (clust & 1) ? ((*p & 0x0F) | ((uint8_t)val << 4)) : (uint8_t)val;
			bc++;
			fs->winflag = 1;
			/* Update the current sector information, If failed, returns 0	*/
			if (!move_window(fatsect + bc / 512U))
				return TFAT_FALSE;
			p = &fs->win[bc % 512U];
			*p = (clust & 1) ? (uint8_t)(val >> 4) : ((*p & 0xF0) | ((uint8_t)(val >> 8) & 0x0F));
			break;

		case TFAT_FS_FAT16 :
			/* Update the current sector information, If failed returns 0	*/
			if (!move_window(fatsect + clust / 256))
				return TFAT_FALSE;
			TFAT_ST_WORD(&fs->win[((uint16_t)clust * 2) % 512U], (uint16_t)val);
			break;
#if _TFAT_FAT32
			/* For FAT32	*/
		case TFAT_FS_FAT32 :
			/* Check current window, if failed to 	*/
			if (!move_window(fatsect + clust / 128))
				return TFAT_FALSE;
			TFAT_ST_DWORD(&fs->win[((uint16_t)clust * 4) % 512U], val);
			break;
#endif
		default :
			return TFAT_FALSE;
	}

	fs->winflag = 1;

	/* Operation successful	*/
	return TFAT_TRUE;
}
#endif /* !_TFAT_FS_READONLY */

/*""FUNC COMMENT""*******************************************************************
* Function Name	: remove_chain
* Description	: Remove a cluster chain
* Arguments		: Cluster number to remove chain from
* Return value	: TFAT_TRUE - successful, TFAT_FALSE - failed
*""FUNC COMMENT END""****************************************************************/
#if !_TFAT_FS_READONLY
static BOOL remove_chain(CLUST clust)
{
	CLUST nxt;
	/* Get the structure of FAT	*/
	FATFS *fs = FatFs;

	/* Check if the cluster number is valid */
	while (clust >= 2 && clust < fs->max_clust)
	{
		/* Get current cluster information	*/
		nxt = get_cluster(clust);

		/* Check if the information has been read successfully.	*/
		if (nxt == 1)
			return TFAT_FALSE;

		/* Remove pointer from current cluster	*/
		if (!put_cluster(clust, 0))
			return TFAT_FALSE;

		/* Count free clusters	*/
		if (fs->free_clust != (CLUST)0xFFFFFFFF)
		{
			fs->free_clust++;
#if _TFAT_USE_FSINFO
			fs->fsi_flag = 1;
#endif
		}
		clust = nxt;
	}

	/* 1 if successful	*/
	return TFAT_TRUE;
}
#endif

/*""FUNC COMMENT""*******************************************************************
* Function Name	: create_chain
* Description	: Stretch or create a cluster chain
* Arguments		: Cluster number to stretch, 0 means create new
* Return value	: 0: No free cluster, 1: Error, >=2: New cluster number
*""FUNC COMMENT END""****************************************************************/
#if !_TFAT_FS_READONLY
static CLUST create_chain(CLUST clust)
{
	CLUST cstat, ncl, scl, mcl;
	/* Get the structure of FAT	*/
	FATFS *fs = FatFs;

	/* Read the max. cluster counts the disk may have	*/
	mcl = fs->max_clust;

	/* Create new chain */
	if (clust == 0)
	{
		/* Get last allocated cluster */
		scl = fs->last_clust;
		if (scl < 2 || scl >= mcl) scl = 1;
	}

	/* Stretch existing chain */
	else
	{
		/* Check the cluster status */
		cstat = get_cluster(clust);

		/* It is an invalid cluster */
		if (cstat < 2)
			return 1;

		/* It is already followed by next cluster */
		if (cstat < mcl)
			return cstat;

		scl = clust;
	}

	/* Start cluster */
	ncl = scl;
	while (1)
	{
		/* Next cluster */
		ncl++;

		/* Wrap around */
		if (ncl >= mcl)
		{
			ncl = 2;

			/* No free custer */
			if (ncl > scl)
				return 0;
		}

		/* Get the cluster status */
		cstat = get_cluster(ncl);

		/* Found a free cluster */
		if (cstat == 0)
			break;

		/* Any error occured */
		if (cstat == 1)
			return 1;

		/* No free custer */
		if (ncl == scl)
			return 0;
	}

	/* Mark the new cluster "in use" */
	if (!put_cluster(ncl, (CLUST)0x0FFFFFFF))
		return 1;

	/* Link it to previous one if needed */
	if (clust != 0 && !put_cluster(clust, ncl))
		return 1;

	/* Update fsinfo */
	fs->last_clust = ncl;

	if (fs->free_clust != (CLUST)0xFFFFFFFF)
	{
		fs->free_clust--;
#if _TFAT_USE_FSINFO
		fs->fsi_flag = 1;
#endif
	}

	/* Return new cluster number */
	return ncl;
}
#endif /* !_TFAT_FS_READONLY */

/*""FUNC COMMENT""*******************************************************************
* Function Name	: clust2sect
* Description	: Get sector number from cluster number
* Arguments		: Cluster number to be converted
* Return value	: !=0: sector number, 0: failed - invalid cluster#
*""FUNC COMMENT END""****************************************************************/
static uint32_t clust2sect(CLUST clust)
{
	/* Get the structure of FAT	*/
	FATFS *fs = FatFs;

	clust -= 2;

	/* Check if the cluster number is valid */
	if (clust >= (fs->max_clust - 2))
		return 0;

	/* Calculate the sector no.	*/
	return (uint32_t)clust * fs->csize + fs->database;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: next_dir_entry
* Description	: Move directory pointer to next entry
* Arguments		: Pointer to directory object
* Return value	: TFAT_TRUE: successful, TFAT_FALSE: could not move to next entry
*""FUNC COMMENT END""****************************************************************/
static BOOL next_dir_entry(DIR *dj)
{
	CLUST clust;
	uint16_t idx;

	idx = dj->index + 1;

	/* Table sector changed? */
	if ((idx & 15) == 0)
	{
		/* Next sector */
		dj->sect++;

		/* check the entry in the static table */
		if (dj->clust == 0)
		{
			/* Check if we have reached to the end of table */
			if (idx >= dj->fs->n_rootdir)
				return TFAT_FALSE;
		}

		/* check the entry in the dynamic table */
		else
		{
			/* check if the cluster has changed? */
			if (((idx / 16) & (dj->fs->csize - 1)) == 0)
			{
				/* Get next cluster */
				clust = get_cluster(dj->clust);

				/* Check if we have reached to the end of table  */
				if (clust < 2 || clust >= dj->fs->max_clust)
					return TFAT_FALSE;

				/* Initialize the pointer for new cluster */
				dj->clust = clust;
				dj->sect = clust2sect(clust);
			}
		}
	}

	/* Lower 4 bit of dj->index indicates offset in dj->sect */
	dj->index = idx;
	return TFAT_TRUE;
}

#if _TFAT_FS_MINIMIZE <= 1
/*""FUNC COMMENT""*******************************************************************
* Function Name	: get_fileinfo
* Description	: Get file status from directory entry
* Arguments		: Pointer to store the File Information
				  Pointer to the directory entry
* Return value	: none
*""FUNC COMMENT END""****************************************************************/
static void get_fileinfo(FILINFO *finfo, const uint8_t *dir)
{
	uint8_t n, c;
	int8_t a;
	uint8_t *p;

	/* Pointer to the file name	*/
	p = &finfo->fname[0];

	/* NT flag */
	a = _TFAT_USE_NTFLAG ? dir[TFAT_DIR_NTres] : 0;

	/* Convert file name (body) */
	for (n = 0; n < 8; n++)
	{
		c = dir[n];

		/* Abort, if space character is found	*/
		if (c == ' ')
			break;

		/* Required if S-JIS coding is used	*/
		if (c == 0x05)
			c = 0xE5;

		/* Convert to lowercase if NTFLAG setting is disabled	*/
		if (a & 0x08 && c >= 'A' && c <= 'Z')
			c += 0x20;

		/* Point to next character	*/
		*p++ = c;
	}

	/* Convert file name (extension) */
	if (dir[8] != ' ')
	{
		/* Treat the next 3 characters as file extension	*/
		*p++ = '.';

		/* Convert the file extension	 */
		for (n = 8; n < 11; n++)
		{
			c = dir[n];
			if (c == ' ')
				break;

			/* Convert to lowercase if NTFLAG setting is disabled	*/
			if (a & 0x10 && c >= 'A' && c <= 'Z')
				c += 0x20;

			*p++ = c;
		}
	}
	*p = '\0';

	/* File/Directory Attribute */
	finfo->fattrib = dir[TFAT_DIR_Attr];
	/* File/Directory Size */
	finfo->fsize = TFAT_LD_DWORD(&dir[TFAT_DIR_FileSize]);
	/* File/Directory Date */
	finfo->fdate = TFAT_LD_WORD(&dir[TFAT_DIR_WrtDate]);
	/* File/Directory Timestamp */
	finfo->ftime = TFAT_LD_WORD(&dir[TFAT_DIR_WrtTime]);
}
#endif /* _TFAT_FS_MINIMIZE <= 1 */

/*""FUNC COMMENT""*******************************************************************
* Function Name	: make_dirfile
* Description	: Pick a paragraph and create the name in format of directory entry
* Arguments		: Pointer to the file path pointer
				  Pointer to directory name buffer {Name(8), Ext(3), NT flag(1)}
* Return value	: 1: error - detected an invalid format, '\0'or'/': next character
*""FUNC COMMENT END""****************************************************************/
static uint8_t make_dirfile(const uint8_t **path, uint8_t *dirname)
{
	uint8_t n, t ;
	int8_t a, b;
	int8_t c;

	/* Fill buffer with spaces */
	memset(dirname, ' ', 8 + 3);

	/* NT flag */
	a = 0;
	b = 0x18;
	n = 0;
	t = 8;

	while (1)
	{
		c = *(*path)++;

		/* Reached to end of str or directory separator */
		if (c == '\0' || c == '/')
		{
			if (n == 0)
				break;

			/* Check if NTFLAG is enabled 	*/
			dirname[11] = _TFAT_USE_NTFLAG ? (a & b) : 0;
			return c;
		}

		/* Reject invisible chars */
		if (c <= ' ' || c == 0x7F)
			break;

		if (c == '.')
		{
			/* Enter extension part */
			if (!(a & 1) && n >= 1 && n <= 8)
			{
				n = 8;
				t = 11;
				continue;
			}
			break;
		}

		/* Accept S-JIS code */
		if (_TFAT_USE_SJIS && (((uint8_t)c >= 0x81 && (uint8_t)c <= 0x9F) || ((uint8_t)c >= 0xE0 && (uint8_t)c <= 0xFC)))
		{
			/* Change heading \xE5 to \x05 */
			if (n == 0 && (uint8_t)c == 0xE5)
				c = 0x05;

			a ^= 1;
			goto md_l2;
		}

		/* Reject " */
		if (c == '"')
			break;

		/* Accept ! # $ % & ' ( ) */
		if (c <= ')')
			goto md_l1;

		/* Reject * + , */
		if (c <= ',')
			break;

		/* Accept - 0-9 */
		if (c <= '9')
			goto md_l1;

		/* Reject : ; < = > ? */
		if (c <= '?')
			break;

		/* These checks are not applied to S-JIS 2nd byte */
		if (!(a & 1))
		{
			/* Reject | */
			if (c == '|')
				break;

			/* Reject [ \ ] */
			if (c >= '[' && c <= ']')
				break;

#if	_TFAT_USE_NTFLAG
			if (c >= 'A' && c <= 'Z')
				(t == 8) ? (b &= 0xF7) : (b &= 0xEF);
#endif

			/* Convert to upper case */
			if (c >= 'a' && c <= 'z')
			{
				c -= 0x20;
#if	_TFAT_USE_NTFLAG
				(t == 8) ? (a |= 0x08) : (a |= 0x10);
#endif
			}
		}

md_l1:
		a &= 0xFE;
md_l2:
		if (n >= t)
			break;

		dirname[n++] = c;
	}
	return 1;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: trace_path
* Description	: Trace a file path
* Arguments		: Pointer to directory object to return last directory
				  Full-path string to trace a file or directory
				  Pointer to pointer to found entry to return
* Return value	: TFAT_FR_OK(0): successful, !=0: error code
*""FUNC COMMENT END""****************************************************************/
static FRESULT trace_path(DIR *dj,	uint8_t *fn, const uint8_t *path, uint8_t **dir)
{
	CLUST clust;
	uint8_t ds;
	uint8_t *dptr = NULL;
	FATFS *fs = FatFs;

	/* Initialize directory object */
	dj->fs = fs;
	clust = fs->dirbase;
#if _TFAT_FAT32
	if (fs->fs_type == TFAT_FS_FAT32)
	{
		dj->clust = dj->sclust = clust;
		dj->sect = clust2sect(clust);
	}
	else
#endif
	{
		dj->clust = dj->sclust = 0;
		dj->sect = clust;
	}
	dj->index = 0;

	/* Null path means the root directory */
	if (*path == '\0')
	{
		*dir = NULL;
		return TFAT_FR_OK;
	}

	while (1)
	{
		/* Get a paragraph into fn[] */
		ds = make_dirfile(&path, fn);

		/* Invalid name detected */
		if (ds == 1)
			return TFAT_FR_INVALID_NAME;

		while (1)
		{
			/*	Read/Write error  */
			if (!move_window(dj->sect))
				return TFAT_FR_RW_ERROR;

			/* Pointer to the directory entry */
			dptr = &fs->win[(dj->index & 15) * 32];

			/* Has it reached to end of dir? */
			if (dptr[TFAT_DIR_Name] == 0)
				return !ds ? TFAT_FR_NO_FILE : TFAT_FR_NO_PATH;

			/* Matched? */
			if (dptr[TFAT_DIR_Name] != 0xE5 && !(dptr[TFAT_DIR_Attr] & TFAT_AM_VOL)
			        && !memcmp(&dptr[TFAT_DIR_Name], fn, 8 + 3))
				break;

			/* Next directory pointer */
			if (!next_dir_entry(dj))
				return !ds ? TFAT_FR_NO_FILE : TFAT_FR_NO_PATH;
		}

		/* Matched with end of path */
		if (!ds)
		{
			*dir = dptr;
			return TFAT_FR_OK;
		}

		/* Cannot trace because it is a file */
		if (!(dptr[TFAT_DIR_Attr] & TFAT_AM_DIR)) return TFAT_FR_NO_PATH;
		clust =											/* Get cluster# of the directory */
#if _TFAT_FAT32
		    ((uint32_t)TFAT_LD_WORD(&dptr[TFAT_DIR_FstClusHI]) << 16) |
#endif
		    TFAT_LD_WORD(&dptr[TFAT_DIR_FstClusLO]);

		/* Restart scannig with the new directory */
		dj->clust = dj->sclust = clust;
		dj->sect = clust2sect(clust);
		dj->index = 2;
	}

	return TFAT_FR_NO_FILE;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: reserve_direntry
* Description	: Reserve a directory entry
* Arguments		: Target directory to create new entry
				  Pointer to pointer to created entry to retutn
* Return value	: TFAT_FR_OK: successful, TFAT_FR_DENIED: no free entry,
				  TFAT_FR_RW_ERROR: a disk error occured
*""FUNC COMMENT END""****************************************************************/
#if !_TFAT_FS_READONLY
static FRESULT reserve_direntry(DIR *dj, uint8_t **dir)
{
	CLUST clust;
	uint32_t sector;
	uint8_t c, n, *dptr;
	FATFS *fs = dj->fs;

	/* Re-initialize directory object */
	clust = dj->sclust;

	/* Dynamic directory table */
	if (clust != 0)
	{
		dj->clust = clust;
		dj->sect = clust2sect(clust);
	}

	/* Static directory table */
	else
	{
		dj->sect = fs->dirbase;
	}
	dj->index = 0;

	do
	{
		if (!move_window(dj->sect))
			return TFAT_FR_RW_ERROR;

		/* Pointer to the directory entry */
		dptr = &fs->win[(dj->index & 15) * 32];
		c = dptr[TFAT_DIR_Name];

		/* Found an empty entry! */
		if (c == 0 || c == 0xE5)
		{
			*dir = dptr;
			return TFAT_FR_OK;
		}
	}
	/* Next directory pointer till it reaches to the end of the directory table */
	while (next_dir_entry(dj));

	/* Abort when static table or could not stretch dynamic table */
	if (clust == 0 || !(clust = create_chain(dj->clust)))
		return TFAT_FR_DENIED;

	if (clust == 1 || !move_window(0))
		return TFAT_FR_RW_ERROR;

	/* Clean up the expanded table */
	fs->winsect = sector = clust2sect(clust);
	memset(fs->win, 0, 512U);

	for (n = fs->csize; n; n--)
	{
		if (R_tfat_disk_write(0, fs->win, sector, 1) != TFAT_RES_OK)
			return TFAT_FR_RW_ERROR;

		sector++;
	}

	fs->winflag = 1;
	*dir = fs->win;

	return TFAT_FR_OK;
}
#endif 			/* !_TFAT_FS_READONLY */

/*""FUNC COMMENT""*******************************************************************
* Function Name	: check_fs
* Description	: Load boot record and check if it is an FAT boot record
* Arguments		: Sector# to check if it is an FAT boot record or not
* Return value	: 0:The FAT boot record,
				  1:Valid boot record but not an FAT,
				  2:Not a boot record or error
*""FUNC COMMENT END""****************************************************************/
static uint8_t check_fs(uint32_t sect)
{
	FATFS *fs = FatFs;

	/* Load boot record */
	if (R_tfat_disk_read(0, fs->win, sect, 1) != TFAT_RES_OK)
		return 2;

	/* Check record signature */
	if (TFAT_LD_WORD(&fs->win[TFAT_BS_55AA]) != 0xAA55)
		return 2;

	/* Check FAT signature */
	if (!memcmp(&fs->win[TFAT_BS_FilSysType], "FAT", 3))
		return 0;
#if _TFAT_FAT32
	if (!memcmp(&fs->win[TFAT_BS_FilSysType32], "FAT32", 5) && !(fs->win[TFAT_BPB_ExtFlags] & 0x80))
		return 0;
#endif
	return 1;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: auto_mount
* Description	: Make sure that the file system is valid
* Arguments		: Pointer to pointer to the path name (drive number)
				  !=0: Check media write protection for write access
* Return value	: TFAT_FR_OK(0): successful, !=0: any error occured
*""FUNC COMMENT END""****************************************************************/
static FRESULT auto_mount(const uint8_t **path, uint8_t chk_wp)
{
	uint8_t fmt;
	DSTATUS stat;
	uint32_t bootsect, fatsize, totalsect, maxclust;
	const uint8_t *p = *path;
	FATFS *fs;

	/* Skip leading spaces */
	while (*p == ' ')
		p++;

	/* Skip heading slash */
	if (*p == '/')
		p++;

	/* Return pointer to the path name */
	*path = p;

	/* Is the file system object registered? */
	fs = FatFs;

	if (!fs)
		return TFAT_FR_NOT_ENABLED;

	/* If the logical drive has been mounted */
	if (fs->fs_type)
	{
		stat = R_tfat_disk_status(0);

		/* and physical drive is kept initialized (has not been changed), */
		if (!(stat & TFAT_STA_NOINIT))
		{
#if !_TFAT_FS_READONLY
			/* Check write protection if needed */
			if (chk_wp && (stat & TFAT_STA_PROTECT))
				return TFAT_FR_WRITE_PROTECTED;
#endif
			/* The file system object is valid */
			return TFAT_FR_OK;
		}
	}

	/* The logical drive must be re-mounted.
	   Following code attempts to mount the logical drive */

	/* Clean-up the file system object */
	memset(fs, 0, sizeof(FATFS));

	/* Initialize low level disk I/O layer */
	stat = R_tfat_disk_initialize(0);

	/* Check if the drive is ready */
	if (stat & TFAT_STA_NOINIT)
		return TFAT_FR_NOT_READY;

#if !_TFAT_FS_READONLY
	/* Check write protection if needed */
	if (chk_wp && (stat & TFAT_STA_PROTECT))
		return TFAT_FR_WRITE_PROTECTED;
#endif

	/* Search FAT partition on the drive */
	/* Check sector 0 as an SFD format */
	fmt = check_fs(bootsect = 0);

	/* Not an FAT boot record, it may be patitioned */
	if (fmt == 1)
	{
		/* Check a partition listed in top of the partition table */
		/* Is the 1st partition existing? */
		if (fs->win[TFAT_MBR_Table+4])
		{
			/* Partition offset in LBA */
			bootsect = TFAT_LD_DWORD(&fs->win[TFAT_MBR_Table+8]);
			/* Check the partition */
			fmt = check_fs(bootsect);
		}
	}

	/* No valid FAT patition is found */
	if (fmt || TFAT_LD_WORD(&fs->win[TFAT_BPB_BytsPerSec]) != 512U)
		return TFAT_FR_NO_FILESYSTEM;

	/* Initialize the file system object */
	/* Number of sectors per FAT */
	fatsize = TFAT_LD_WORD(&fs->win[TFAT_BPB_FATSz16]);

	if (!fatsize)
		fatsize = TFAT_LD_DWORD(&fs->win[TFAT_BPB_FATSz32]);

	fs->sects_fat = (CLUST)fatsize;

	/* Number of FAT copies */
	fs->n_fats = fs->win[TFAT_BPB_NumFATs];

	/* (Number of sectors in FAT area) */
	fatsize *= fs->n_fats;

	/* FAT start sector (lba) */
	fs->fatbase = bootsect + TFAT_LD_WORD(&fs->win[TFAT_BPB_RsvdSecCnt]);

	/* Number of sectors per cluster */
	fs->csize = fs->win[TFAT_BPB_SecPerClus];

	/* Nmuber of root directory entries */
	fs->n_rootdir = TFAT_LD_WORD(&fs->win[TFAT_BPB_RootEntCnt]);

	/* Number of sectors on the file system */
	totalsect = TFAT_LD_WORD(&fs->win[TFAT_BPB_TotSec16]);
	if (!totalsect)
		totalsect = TFAT_LD_DWORD(&fs->win[TFAT_BPB_TotSec32]);

	/* max_clust = Last cluster# + 1 */
	fs->max_clust = maxclust =
	                    (totalsect - TFAT_LD_WORD(&fs->win[TFAT_BPB_RsvdSecCnt]) - fatsize - fs->n_rootdir / 16) / fs->csize + 2;

	fmt = TFAT_FS_FAT12;										/* Determine the FAT sub type */
	if (maxclust >= 0xFF7) fmt = TFAT_FS_FAT16;
	if (maxclust >= 0xFFF7)
#if !_TFAT_FAT32
		return TFAT_FR_NO_FILESYSTEM;
#else
		fmt = TFAT_FS_FAT32;
	if (fmt == TFAT_FS_FAT32)
		fs->dirbase = TFAT_LD_DWORD(&fs->win[TFAT_BPB_RootClus]);	/* Root directory start cluster */
	else
#endif

	/* Root directory start sector (lba) */
	fs->dirbase = fs->fatbase + fatsize;
	/* Data start sector (lba) */
	fs->database = fs->fatbase + fatsize + fs->n_rootdir / 16;

#if !_TFAT_FS_READONLY
	/* Initialize allocation information */
	fs->free_clust = (CLUST)0xFFFFFFFF;
#if _TFAT_USE_FSINFO
	/* Get fsinfo if needed */
	if (fmt == TFAT_FS_FAT32)
	{
		fs->fsi_sector = bootsect + TFAT_LD_WORD(&fs->win[TFAT_BPB_FSInfo]);
		if (R_tfat_disk_read(0, fs->win, fs->fsi_sector, 1) == TFAT_RES_OK &&
		        TFAT_LD_WORD(&fs->win[TFAT_BS_55AA]) == 0xAA55 &&
		        TFAT_LD_DWORD(&fs->win[TFAT_FSI_LeadSig]) == 0x41615252 &&
		        TFAT_LD_DWORD(&fs->win[TFAT_FSI_StrucSig]) == 0x61417272)
		{
			fs->last_clust = TFAT_LD_DWORD(&fs->win[TFAT_FSI_Nxt_Free]);
			fs->free_clust = TFAT_LD_DWORD(&fs->win[TFAT_FSI_Free_Count]);
		}
	}
#endif
#endif
	/* FAT syb-type */
	fs->fs_type = fmt;

	/* File system mount ID */
	fs->id = ++fsid;

	return TFAT_FR_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: validate
* Description	: Check if the file/dir object is valid or not
* Arguments		: Pointer to the file system object
				  Member id of the target object to be checked
* Return value	: TFAT_FR_OK(0): The object is valid, !=0: Invalid
*""FUNC COMMENT END""****************************************************************/
static FRESULT validate(const FATFS *fs, uint16_t id)
{
	/* Check the details of the object	*/
	if (!fs || !fs->fs_type || fs->id != id)
		return TFAT_FR_INVALID_OBJECT;

	/* Has disk been initialized?	*/
	if (R_tfat_disk_status(0) & TFAT_STA_NOINIT)
		return TFAT_FR_NOT_READY;

	return TFAT_FR_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_mount
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_mount (uint8_t drv, FATFS *fs)
* Description	: Mount/Unmount a Logical Drive
* Arguments		: Logical drive number to be mounted/unmounted
				  Pointer to new file system object (NULL for unmount)
* Return value	: TFAT_FR_OK(0): The object is valid, !=0: Invalid
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_mount(uint8_t drv, FATFS *fs)
{
	if (drv)
		return TFAT_FR_INVALID_DRIVE;

	/* Clear old object */
	if (FatFs)
		FatFs->fs_type = 0;

	/* Register and clear new object */
	FatFs = fs;

	if (fs)
		fs->fs_type = 0;

	return TFAT_FR_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_open
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_open (FIL *fp, const uint8_t *path, uint8_t mode)
* Description	: Open or Create a File
* Arguments		: Pointer to the blank file object
				  Pointer to the file name
				  Access mode and file open mode flags
* Return value	: TFAT_FR_OK(0): The object is valid, !=0: Invalid
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_open(FIL *fp, const uint8_t *path, uint8_t mode)
{
	FRESULT res;
	DIR dj;
	uint8_t *dir;
	uint8_t fn[8+3+1];

	/* Clear file object */
	fp->fs = NULL;

#if !_TFAT_FS_READONLY
	/* Set the file opening mode	*/
	mode &= (TFAT_FA_READ | TFAT_FA_WRITE | TFAT_FA_CREATE_ALWAYS | TFAT_FA_OPEN_ALWAYS | TFAT_FA_CREATE_NEW);
	res = auto_mount(&path, (uint8_t)(mode & (TFAT_FA_WRITE | TFAT_FA_CREATE_ALWAYS | TFAT_FA_OPEN_ALWAYS | TFAT_FA_CREATE_NEW)));
#else
	/* Open in Read Only mode, if the Read Only mode is enabled	*/
	mode &= TFAT_FA_READ;
	res = auto_mount(&path, 0);
#endif

	if (res != TFAT_FR_OK)
		return res;

	/* Trace the file path */
	res = trace_path(&dj, fn, path, &dir);

#if !_TFAT_FS_READONLY
	/* Create or Open a File */
	if (mode & (TFAT_FA_CREATE_ALWAYS | TFAT_FA_OPEN_ALWAYS | TFAT_FA_CREATE_NEW))
	{
		CLUST rs;
		uint32_t dw;

		/* No file, create new */
		if (res != TFAT_FR_OK)
		{
			if (res != TFAT_FR_NO_FILE)
				return res;

			res = reserve_direntry(&dj, &dir);

			if (res != TFAT_FR_OK)
				return res;

			/* Initialize the new entry with opened file */
			memset(dir, 0, 32);
			memcpy(&dir[TFAT_DIR_Name], fn, 8 + 3);
			dir[TFAT_DIR_NTres] = fn[11];
			mode |= TFAT_FA_CREATE_ALWAYS;
		}

		/* Any object is already existing */
		else
		{
			/* Cannot create new */
			if (mode & TFAT_FA_CREATE_NEW)
				return TFAT_FR_EXIST;

			/* Cannot overwrite (R/O or DIR) */
			if (!dir || (dir[TFAT_DIR_Attr] & (TFAT_AM_RDO | TFAT_AM_DIR)))
				return TFAT_FR_DENIED;

			/* If one must create the file even if it exists	*/
			if (mode & TFAT_FA_CREATE_ALWAYS)
			{
				/* Resize it to zero */
#if _TFAT_FAT32
				rs = ((uint32_t)TFAT_LD_WORD(&dir[TFAT_DIR_FstClusHI]) << 16) | TFAT_LD_WORD(&dir[TFAT_DIR_FstClusLO]);
				TFAT_ST_WORD(&dir[TFAT_DIR_FstClusHI], 0);
#else
				rs = TFAT_LD_WORD(&dir[TFAT_DIR_FstClusLO]);
#endif
				/* cluster = 0 */
				TFAT_ST_WORD(&dir[TFAT_DIR_FstClusLO], 0);

				/* size = 0 */
				TFAT_ST_DWORD(&dir[TFAT_DIR_FileSize], 0);
				dj.fs->winflag = 1;

				/* Remove the cluster chain */
				dw = dj.fs->winsect;

				if (!remove_chain(rs) || !move_window(dw))
					return TFAT_FR_RW_ERROR;

				/* Reuse the cluster hole */
				dj.fs->last_clust = rs - 1;
			}
		}

		if (mode & TFAT_FA_CREATE_ALWAYS)
		{
			/* Reset attribute */
			dir[TFAT_DIR_Attr] = 0;
			dw = R_tfat_get_fattime();

			/* Created time */
			TFAT_ST_DWORD(&dir[TFAT_DIR_CrtTime], dw);
			dj.fs->winflag = 1;

			/* Set file changed flag */
			mode |= TFAT_FA__WRITTEN;
		}
	}

	/* Open an existing file */
	else
	{
#endif /* !_TFAT_FS_READONLY */

		/* Trace failed */
		if (res != TFAT_FR_OK)
			return res;

		/* It is a directory */
		if (!dir || (dir[TFAT_DIR_Attr] & TFAT_AM_DIR))
			return TFAT_FR_NO_FILE;

#if !_TFAT_FS_READONLY
		/* R/O violation */
		if ((mode & TFAT_FA_WRITE) && (dir[TFAT_DIR_Attr] & TFAT_AM_RDO))
			return TFAT_FR_DENIED;
	}

	/* Pointer to the directory entry */
	fp->dir_sect = dj.fs->winsect;
	fp->dir_ptr = dir;
#endif

	/* File access mode */
	fp->flag = mode;
	/* File start cluster */
	fp->org_clust =
#if _TFAT_FAT32
	    ((uint32_t)TFAT_LD_WORD(&dir[TFAT_DIR_FstClusHI]) << 16) |
#endif
	    TFAT_LD_WORD(&dir[TFAT_DIR_FstClusLO]);

	/* File size */
	fp->fsize = TFAT_LD_DWORD(&dir[TFAT_DIR_FileSize]);

	/* File pointer */
	fp->fptr = 0;
	fp->csect = 255;

	/* Owner file system object of the file */
	fp->fs = dj.fs;
	fp->id = dj.fs->id;

	return TFAT_FR_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_read
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_read (FIL *fp, void *buff, uint16_t btr, uint16_t *br)
* Description	: Read File
* Arguments		: Pointer to the file object
				  Pointer to data buffer
				  Number of bytes to read
				  Pointer to number of bytes read
* Return value	: TFAT_FR_OK: successful
				  TFAT_FR_RW_ERROR: failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_read(FIL *fp, void *buff, uint16_t btr, uint16_t *br)
{
	FRESULT res;
	uint32_t sect, remain;
	uint16_t rcnt, cc;
	CLUST clust;
	uint8_t *rbuff = buff;

	*br = 0;

	/* Check validity of the object */
	res = validate(fp->fs, fp->id);

	if (res != TFAT_FR_OK)
		return res;

	/* Check error flag */
	if (fp->flag & TFAT_FA__ERROR)
		return TFAT_FR_RW_ERROR;

	/* Check access mode */
	if (!(fp->flag & TFAT_FA_READ))
		return TFAT_FR_DENIED;

	remain = fp->fsize - fp->fptr;

	/* Truncate btr by remaining bytes */
	if (btr > remain) btr = (uint16_t)remain;

	/* Repeat until all data transferred */
	for (;  btr; rbuff += rcnt, fp->fptr += rcnt, *br += rcnt, btr -= rcnt)
	{
		/* On the sector boundary? */
		if ((fp->fptr % 512U) == 0)
		{
			/* On the cluster boundary? */
			if (fp->csect >= fp->fs->csize)
			{
				/* On the top of the file? */
				clust = (fp->fptr == 0) ?
				        fp->org_clust : get_cluster(fp->curr_clust);

				if (clust < 2 || clust >= fp->fs->max_clust)
					goto fr_error;

				/* Update current cluster */
				fp->curr_clust = clust;

				/* Reset sector address in the cluster */
				fp->csect = 0;
			}

			/* Get current sector */
			sect = clust2sect(fp->curr_clust) + fp->csect;
			/* When remaining bytes >= sector size, */
			cc = btr / 512U;

			/* Read maximum contiguous sectors directly */
			if (cc)
			{
				/* Clip at cluster boundary */
				if (fp->csect + cc > fp->fs->csize)
					cc = fp->fs->csize - fp->csect;

				if (R_tfat_disk_read(0, rbuff, sect, (uint8_t)cc) != TFAT_RES_OK)
					goto fr_error;

				/* Next sector address in the cluster */
				fp->csect += (uint8_t)cc;
				/* Number of bytes transferred */
				rcnt = 512U * cc;

				continue;
			}

			/* Next sector address in the cluster */
			fp->csect++;
		}

		/* Get current sector */
		sect = clust2sect(fp->curr_clust) + fp->csect - 1;

		/* Move sector window */
		if (!move_window(sect))
			goto fr_error;

		/* Get partial sector from sector window */
		rcnt = 512U - (uint16_t)(fp->fptr % 512U);
		if (rcnt > btr)
			rcnt = btr;

		memcpy(rbuff, &fp->fs->win[fp->fptr % 512U], rcnt);
	}

	return TFAT_FR_OK;

	/* Abort this file due to an unrecoverable error */
fr_error:
	fp->flag |= TFAT_FA__ERROR;

	return TFAT_FR_RW_ERROR;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_write
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_write (FIL *fp, const void *buff,	uint16_t btw, uint16_t *bw)
* Description	: Write File
* Arguments		: Pointer to the file object
				  Pointer to the data to be written
				  Number of bytes to write
				  Pointer to number of bytes written
* Return value	: TFAT_FR_OK: successful
				  TFAT_FR_RW_ERROR: failed
*""FUNC COMMENT END""****************************************************************/
#if !_TFAT_FS_READONLY
FRESULT R_tfat_f_write(FIL *fp, const void *buff,	uint16_t btw, uint16_t *bw)
{
	FRESULT res;
	uint32_t sect;
	uint16_t wcnt, cc;
	CLUST clust;
	const uint8_t *wbuff = buff;

	*bw = 0;

	/* Check validity of the object */
	res = validate(fp->fs, fp->id);

	if (res != TFAT_FR_OK)
		return res;

	/* Check error flag */
	if (fp->flag & TFAT_FA__ERROR)
		return TFAT_FR_RW_ERROR;

	/* Check access mode */
	if (!(fp->flag & TFAT_FA_WRITE))
		return TFAT_FR_DENIED;

	/* File size cannot reach 4GB */
	if (fp->fsize + btw < fp->fsize)
		return TFAT_FR_OK;

	/* Repeat until all data transferred */
	for (;  btw; wbuff += wcnt, fp->fptr += wcnt, *bw += wcnt, btw -= wcnt)
	{
		/* On the sector boundary? */
		if ((fp->fptr % 512U) == 0)
		{
			/* On the cluster boundary? */
			if (fp->csect >= fp->fs->csize)
			{
				/* On the top of the file? */
				if (fp->fptr == 0)
				{
					/* Follow from the origin */
					clust = fp->org_clust;

					/* When there is no cluster chain, */
					if (clust == 0)
						/* Create a new cluster chain */
						fp->org_clust = clust = create_chain(0);
				}

				/* Middle or end of the file */
				else
				{
					/* Trace or streach cluster chain */
					clust = create_chain(fp->curr_clust);
				}

				/* Could not allocate a new cluster (disk full) */
				if (clust == 0)
					break;

				if (clust == 1 || clust >= fp->fs->max_clust)
					goto fw_error;

				/* Update current cluster */
				fp->curr_clust = clust;
				/* Reset sector address in the cluster */
				fp->csect = 0;
			}

			/* Get current sector */
			sect = clust2sect(fp->curr_clust) + fp->csect;
			/* When remaining bytes >= sector size, */
			cc = btw / 512U;

			/* Write maximum contiguous sectors directly */
			if (cc)
			{
				/* Clip at cluster boundary */
				if (fp->csect + cc > fp->fs->csize)
					cc = fp->fs->csize - fp->csect;

				if (R_tfat_disk_write(0, wbuff, sect, (uint8_t)cc) != TFAT_RES_OK)
					goto fw_error;

				/* Next sector address in the cluster */
				fp->csect += (uint8_t)cc;
				/* Number of bytes transferred */
				wcnt = 512U * cc;

				continue;
			}

			/* Flush R/W window without reading if needed */
			if (fp->fptr >= fp->fsize)
			{
				if (!move_window(0))
					goto fw_error;

				fp->fs->winsect = sect;
			}

			/* Next sector address in the cluster */
			fp->csect++;
		}

		/* Get current sector */
		sect = clust2sect(fp->curr_clust) + fp->csect - 1;

		/* Move sector window */
		if (!move_window(sect))
			goto fw_error;

		/* Put partial sector into sector window */
		wcnt = 512U - (uint16_t)(fp->fptr % 512U);
		if (wcnt > btw) wcnt = btw;
		memcpy(&fp->fs->win[fp->fptr % 512U], wbuff, wcnt);

		fp->fs->winflag = 1;
	}

	/* Update file size if needed */
	if (fp->fptr > fp->fsize)
		fp->fsize = fp->fptr;

	/* Set file changed flag */
	fp->flag |= TFAT_FA__WRITTEN;

	return res;

	/* Abort this file due to an unrecoverable error */
fw_error:
	fp->flag |= TFAT_FA__ERROR;

	return TFAT_FR_RW_ERROR;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_sync
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_sync (FIL *fp)
* Description	: Synchronize the file object
* Arguments		: Pointer to the file object
* Return value	: TFAT_FR_OK: successful
				  TFAT_FR_RW_ERROR: failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_sync(FIL *fp)
{
	FRESULT res;
	uint32_t tim;
	uint8_t *dir;

	/* Check validity of the object */
	res = validate(fp->fs, fp->id);
	if (res == TFAT_FR_OK)
	{
		/* Has the file been written? */
		if (fp->flag & TFAT_FA__WRITTEN)
		{
			/* Update the directory entry */
			if (!move_window(fp->dir_sect))
				return TFAT_FR_RW_ERROR;

			dir = fp->dir_ptr;

			/* Set archive bit */
			dir[TFAT_DIR_Attr] |= TFAT_AM_ARC;

			/* Update file size */
			TFAT_ST_DWORD(&dir[TFAT_DIR_FileSize], fp->fsize);

			/* Update start cluster */
			TFAT_ST_WORD(&dir[TFAT_DIR_FstClusLO], fp->org_clust);

#if _TFAT_FAT32
			TFAT_ST_WORD(&dir[TFAT_DIR_FstClusHI], fp->org_clust >> 16);
#endif
			/* Updated time */
			tim = R_tfat_get_fattime();
			TFAT_ST_DWORD(&dir[TFAT_DIR_WrtTime], tim);
			fp->flag &= (uint8_t)~TFAT_FA__WRITTEN;
			res = sync();
		}
	}
	return res;
}

#endif /* !_TFAT_FS_READONLY */

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_close
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_close (FIL *fp)
* Description	: Close the opened file
* Arguments		: Pointer to the file object to be closed
* Return value	: TFAT_FR_OK: successful
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_close(FIL *fp)
{
	FRESULT res;

	/* Check if it is a valid file name & also ensure that the entry is upto date
	   in local buffer  	*/
#if !_TFAT_FS_READONLY
	res = R_tfat_f_sync(fp);
#else
	res = validate(fp->fs, fp->id);
#endif

	/* Unlink the file	*/
	if (res == TFAT_FR_OK)
		fp->fs = NULL;

	/* Return 0 if successful	 */
	return res;
}

#if _TFAT_FS_MINIMIZE <= 2

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_lseek
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_lseek (FIL *fp, uint32_t ofs)
* Description	: Seek File R/W Pointer
* Arguments		: Pointer to the file object
* Return value	: TFAT_FR_OK successful
				  other - failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_lseek(FIL *fp, uint32_t ofs)
{
	FRESULT res;
	CLUST clust;
	uint32_t csize, ifptr;

	/* Check validity of the object */
	res = validate(fp->fs, fp->id);

	/* If validation fails then return 1	*/
	if (res != TFAT_FR_OK)
		return res;

	/* Indicates error status	*/
	if (fp->flag & TFAT_FA__ERROR)
		return TFAT_FR_RW_ERROR;

	/* In read-only mode, clip offset with the file size */
	if (ofs > fp->fsize
#if !_TFAT_FS_READONLY
	        && !(fp->flag & TFAT_FA_WRITE)
#endif
	   ) ofs = fp->fsize;

	ifptr = fp->fptr;
	fp->fptr = 0;
	fp->csect = 255;

	if (ofs > 0)
	{
		/* Cluster size (byte) */
		csize = (uint32_t)fp->fs->csize * 512U;
		if (ifptr > 0 && (ofs - 1) / csize >= (ifptr - 1) / csize)
		{
			/* When seek to same or following cluster, start from the current cluster */
			fp->fptr = (ifptr - 1) & ~(csize - 1);
			ofs -= fp->fptr;
			clust = fp->curr_clust;
		}

		else
		{
			/* When seek to back cluster, start from the first cluster */
			clust = fp->org_clust;
#if !_TFAT_FS_READONLY
			/* If no cluster chain, create a new chain */
			if (clust == 0)
			{
				/* Creates the linked lists for storing the data	*/
				clust = create_chain(0);

				/* Can't use first cluster	*/
				if (clust == 1)
					goto fk_error;

				/* store the no. of the cluster	*/
				fp->org_clust = clust;
			}
#endif
			fp->curr_clust = clust;
		}

		if (clust != 0)
		{
			/* Cluster following loop */
			while (ofs > csize)
			{
#if !_TFAT_FS_READONLY
				/* Check if in write mode or not */
				if (fp->flag & TFAT_FA_WRITE)
				{
					/* Force streached if in write mode */
					clust = create_chain(clust);

					/* When disk gets full, clip file size */
					if (clust == 0)
					{
						ofs = csize;
						break;
					}
				}

				else
#endif
					/* Follow cluster chain if not in write mode */
					clust = get_cluster(clust);

				if (clust < 2 || clust >= fp->fs->max_clust)
					goto fk_error;

				fp->curr_clust = clust;
				fp->fptr += csize;
				ofs -= csize;
			}
			fp->fptr += ofs;

			/* Sector offset in the cluster */
			fp->csect = (uint8_t)(ofs / 512U);

			if (ofs % 512U)
				fp->csect++;
		}
	}

#if !_TFAT_FS_READONLY
	if (fp->fptr > fp->fsize)
	{	/* Set changed flag if the file was extended */
		fp->fsize = fp->fptr;
		fp->flag |= TFAT_FA__WRITTEN;
	}
#endif

	return TFAT_FR_OK;

	/* Abort this file due to an unrecoverable error */
fk_error:
	fp->flag |= TFAT_FA__ERROR;
	return TFAT_FR_RW_ERROR;
}

#if _TFAT_FS_MINIMIZE <= 1

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_opendir
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_opendir (DIR *dj, const uint8_t *path)
* Description	: Create a directroy object
* Arguments		: Pointer to directory object to create
				  Pointer to the directory path
* Return value	: TFAT_FR_OK successful
				  other - failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_opendir(DIR *dj, const uint8_t *path)
{
	FRESULT res;
	uint8_t *dir;
	uint8_t fn[8+3+1];

	/* Get the FAT entry	*/
	res = auto_mount(&path, 0);
	if (res == TFAT_FR_OK)
	{
		/* Trace the directory path */
		res = trace_path(dj, fn, path, &dir);

		/* Trace completed */
		if (res == TFAT_FR_OK)
		{
			/* It is not the root dir */
			if (dir)
			{
				if (dir[TFAT_DIR_Attr] & TFAT_AM_DIR)
				{	/* The entry is a directory */
					dj->clust =
#if _TFAT_FAT32
					    ((uint32_t)TFAT_LD_WORD(&dir[TFAT_DIR_FstClusHI]) << 16) |
#endif
					    TFAT_LD_WORD(&dir[TFAT_DIR_FstClusLO]);
					dj->sect = clust2sect(dj->clust);
					dj->index = 2;
				}

				/* The entry is not a directory */
				else
				{
					res = TFAT_FR_NO_FILE;
				}
			}
			dj->id = dj->fs->id;
		}
	}

	return res;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_readdir
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_readdir (DIR *dj,	FILINFO *finfo)
* Description	: Read Directory Entry in Sequence
* Arguments		: Pointer to the directory object
				  Pointer to file information to return
* Return value	: TFAT_FR_OK successful
				  other - failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_readdir(DIR *dj,	FILINFO *finfo)
{
	FRESULT res;
	uint8_t *dir, c;

	/* Check validity of the object */
	res = validate(dj->fs, dj->id);

	if (res != TFAT_FR_OK)
		return res;

	finfo->fname[0] = 0;
	while (dj->sect)
	{
		/*	*/
		if (!move_window(dj->sect))
			return TFAT_FR_RW_ERROR;

		/* pointer to the directory entry */
		dir = &dj->fs->win[(dj->index & 15) * 32];
		c = dir[TFAT_DIR_Name];

		/* Has it reached to end of dir? */
		if (c == 0)
			break;

		/* Is it a valid entry? */
		if (c != 0xE5 && !(dir[TFAT_DIR_Attr] & TFAT_AM_VOL))
			get_fileinfo(finfo, dir);

		/* Next entry */
		if (!next_dir_entry(dj)) dj->sect = 0;

		/* Found valid entry */
		if (finfo->fname[0])
			break;
	}

	return TFAT_FR_OK;
}

#if _TFAT_FS_MINIMIZE == 0

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_stat
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_stat (const uint8_t *path, FILINFO *finfo)
* Description	: Get File Status
* Arguments		: Pointer to the file path
				  Pointer to file information to return
* Return value	: TFAT_FR_OK successful
				  other - failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_stat(const uint8_t *path, FILINFO *finfo)
{
	FRESULT res;
	DIR dj;
	uint8_t *dir;
	uint8_t fn[8+3+1];

	res = auto_mount(&path, 0);
	if (res == TFAT_FR_OK)
	{
		/* Trace the file path */
		res = trace_path(&dj, fn, path, &dir);

		/* Trace completed */
		if (res == TFAT_FR_OK)
		{
			/* Found an object */
			if (dir)
				get_fileinfo(finfo, dir);

			/* It is root dir */
			else
				res = TFAT_FR_INVALID_NAME;
		}
	}

	return res;
}

#if !_TFAT_FS_READONLY

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_truncate
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_truncate (FIL *fp)
* Description	: Truncate File
* Arguments		: Pointer to the file object
				  Pointer to file information to return
* Return value	: TFAT_FR_OK successful
				  other - failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_truncate(FIL *fp)
{
	FRESULT res;
	CLUST ncl;

	/* Check validity of the object */
	res = validate(fp->fs, fp->id);
	if (res != TFAT_FR_OK)
		return res;

	/* Check error flag */
	if (fp->flag & TFAT_FA__ERROR)
		return TFAT_FR_RW_ERROR;

	/* Check access mode */
	if (!(fp->flag & TFAT_FA_WRITE))
		return TFAT_FR_DENIED;

	if (fp->fsize > fp->fptr)
	{
		/* Set file size to current R/W point */
		fp->fsize = fp->fptr;
		fp->flag |= TFAT_FA__WRITTEN;

		/* When set file size to zero, remove entire cluster chain */
		if (fp->fptr == 0)
		{
			if (!remove_chain(fp->org_clust))
				goto ft_error;
			fp->org_clust = 0;
		}

		else
		{	/* When truncating a part of the file, remove remaining clusters */
			ncl = get_cluster(fp->curr_clust);

			if (ncl < 2)
				goto ft_error;

			if (ncl < fp->fs->max_clust)
			{
				if (!put_cluster(fp->curr_clust, (CLUST)0x0FFFFFFF))
					goto ft_error;

				if (!remove_chain(ncl))
					goto ft_error;
			}
		}
	}

	return TFAT_FR_OK;

	/* Abort this file due to an unrecoverable error */
ft_error:
	fp->flag |= TFAT_FA__ERROR;

	return TFAT_FR_RW_ERROR;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_getfree
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_getfree (const uint8_t *drv,	uint32_t *nclust, FATFS **fatfs)
* Description	: Get Number of Free Clusters
* Arguments		: Pointer to the logical drive number (root dir)
				  Pointer to the variable to return number of free clusters
				  Pointer to pointer to corresponding file system object to return
* Return value	: TFAT_FR_OK successful
				  other - failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_getfree(const uint8_t *drv,	uint32_t *nclust, FATFS **fatfs)
{
	FRESULT res;
	FATFS *fs;
	uint32_t n, sect;
	CLUST clust;
	uint8_t fat, f, *p;

	/* Get drive number */
	res = auto_mount(&drv, 0);

	if (res != TFAT_FR_OK)
		return res;

	*fatfs = fs = FatFs;

	/* If number of free cluster is valid, return it without cluster scan. */
	if (fs->free_clust <= fs->max_clust - 2)
	{
		*nclust = fs->free_clust;

		return TFAT_FR_OK;
	}

	/* Get number of free clusters */
	fat = fs->fs_type;
	n = 0;

	/* Get max. count of clusters	*/
	if (fat == TFAT_FS_FAT12)
	{
		clust = 2;
		do
		{
			if ((uint16_t)get_cluster(clust) == 0)
				n++;
		}
		while (++clust < fs->max_clust);
	}

	else
	{
		clust = fs->max_clust;

		/* Get base address of FAT structure	*/
		sect = fs->fatbase;
		f = 0;
		p = 0;

		/* Read cluster information	*/
		do
		{
			if (!f)
			{
				/* Abort, if error status is returned from move_window section */
				if (!move_window(sect++))
					return TFAT_FR_RW_ERROR;

				p = fs->win;
			}

			if (!_TFAT_FAT32 || fat == TFAT_FS_FAT16)
			{
				if (TFAT_LD_WORD(p) == 0) n++;
				p += 2;
				f += 1;
			}

			else
			{
				if (TFAT_LD_DWORD(p) == 0) n++;
				p += 4;
				f += 2;
			}
		}
		while (--clust);
	}
	/* Store the result at destination	*/
	fs->free_clust = n;
#if _TFAT_USE_FSINFO
	if (fat == TFAT_FS_FAT32)
		fs->fsi_flag = 1;
#endif
	*nclust = n;

	return TFAT_FR_OK;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_unlink
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_unlink (const uint8_t *path)
* Description	: Delete a File or Directory
* Arguments		: Pointer to the file or directory path
* Return value	: TFAT_FR_OK - success
				  else fail
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_unlink(const uint8_t *path)
{
	FRESULT res;
	DIR dj;
	uint8_t *dir, *sdir;
	uint32_t dsect;
	uint8_t fn[8+3+1];
	CLUST dclust;

	/* Check if the filesystem is valid	*/
	res = auto_mount(&path, 1);

	if (res != TFAT_FR_OK)
		return res;

	/* Trace the file path */
	res = trace_path(&dj, fn, path, &dir);

	/* Trace failed */
	if (res != TFAT_FR_OK)
		return res;

	/* It is the root directory */
	if (!dir)
		return TFAT_FR_INVALID_NAME;

	/* It is a R/O object */
	if (dir[TFAT_DIR_Attr] & TFAT_AM_RDO)
		return TFAT_FR_DENIED;

	dsect = dj.fs->winsect;
	dclust =
#if _TFAT_FAT32
	    ((uint32_t)TFAT_LD_WORD(&dir[TFAT_DIR_FstClusHI]) << 16) |
#endif
	    TFAT_LD_WORD(&dir[TFAT_DIR_FstClusLO]);

	/* It is a sub-directory */
	if (dir[TFAT_DIR_Attr] & TFAT_AM_DIR)
	{
		/* Check if the sub-dir is empty or not */
		dj.clust = dclust;
		dj.sect = clust2sect(dclust);
		dj.index = 2;
		do
		{
			/* Update the current sector information, If failed, returns 0	*/
			if (!move_window(dj.sect))
				return TFAT_FR_RW_ERROR;

			sdir = &dj.fs->win[(dj.index & 15) * 32];

			if (sdir[TFAT_DIR_Name] == 0)
				break;

			/* The directory is not empty */
			if (sdir[TFAT_DIR_Name] != 0xE5 && !(sdir[TFAT_DIR_Attr] & TFAT_AM_VOL))
				return TFAT_FR_DENIED;
		}
		while (next_dir_entry(&dj));
	}

	/* Mark the directory entry 'deleted' */
	if (!move_window(dsect))
		return TFAT_FR_RW_ERROR;

	dir[TFAT_DIR_Name] = 0xE5;
	dj.fs->winflag = 1;

	/* Remove the cluster chain */
	if (!remove_chain(dclust))
		return TFAT_FR_RW_ERROR;

	return sync();
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_mkdir
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_mkdir (const uint8_t *path)
* Description	: Create a Directory
* Arguments		: Pointer to the directory path
* Return value	: TFAT_FR_OK - success
				  else fail
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_mkdir(const uint8_t *path)
{
	FRESULT res;
	DIR dj;
	uint8_t *dir, *fw, n;
	uint8_t fn[8+3+1];
	uint32_t sect, dsect, tim;
	CLUST dclust, pclust;

	res = auto_mount(&path, 1);

	if (res != TFAT_FR_OK)
		return res;

	/* Trace the file path */
	res = trace_path(&dj, fn, path, &dir);

	/* Any file or directory is already existing */
	if (res == TFAT_FR_OK)
		return TFAT_FR_EXIST;

	/* File or directory not found	*/
	if (res != TFAT_FR_NO_FILE)
		return res;

	/* Reserve a directory entry */
	res = reserve_direntry(&dj, &dir);

	if (res != TFAT_FR_OK)
		return res;

	sect = dj.fs->winsect;

	/* Allocate a cluster for new directory table */
	dclust = create_chain(0);

	/* Cluster can't be 1	*/
	if (dclust == 1)
		return TFAT_FR_RW_ERROR;
	dsect = clust2sect(dclust);

	if (!dsect)
		return TFAT_FR_DENIED;

	/* Update the current sector information, If failed, returns 0	*/
	if (!move_window(dsect))
		return TFAT_FR_RW_ERROR;

	fw = dj.fs->win;

	/* Clear the directory table */
	memset(fw, 0, 512U);
	for (n = 1; n < dj.fs->csize; n++)
	{
		if (R_tfat_disk_write(0, fw, ++dsect, 1) != TFAT_RES_OK)
			return TFAT_FR_RW_ERROR;
	}

	/* Create "." entry */
	memset(&fw[TFAT_DIR_Name], ' ', 8 + 3);
	fw[TFAT_DIR_Name] = '.';
	fw[TFAT_DIR_Attr] = TFAT_AM_DIR;
	tim = R_tfat_get_fattime();
	TFAT_ST_DWORD(&fw[TFAT_DIR_WrtTime], tim);

	/* Create ".." entry */
	memcpy(&fw[32], &fw[0], 32);
	fw[33] = '.';
	pclust = dj.sclust;
#if _TFAT_FAT32
	TFAT_ST_WORD(&fw[   TFAT_DIR_FstClusHI], dclust >> 16);
	if (dj.fs->fs_type == TFAT_FS_FAT32 && pclust == dj.fs->dirbase)
		pclust = 0;
	TFAT_ST_WORD(&fw[32+TFAT_DIR_FstClusHI], pclust >> 16);
#endif
	TFAT_ST_WORD(&fw[TFAT_DIR_FstClusLO], dclust);
	TFAT_ST_WORD(&fw[32+TFAT_DIR_FstClusLO], pclust);
	dj.fs->winflag = 1;

	if (!move_window(sect))
		return TFAT_FR_RW_ERROR;

	/* Clean-up the new entry */
	memset(&dir[0], 0, 32);
	/* Name */
	memcpy(&dir[TFAT_DIR_Name], fn, 8 + 3);
	dir[TFAT_DIR_NTres] = fn[11];
	/* Attribute */
	dir[TFAT_DIR_Attr] = TFAT_AM_DIR;
	/* Crated time */
	TFAT_ST_DWORD(&dir[TFAT_DIR_WrtTime], tim);
	/* Table start cluster */
	TFAT_ST_WORD(&dir[TFAT_DIR_FstClusLO], dclust);
#if _TFAT_FAT32
	TFAT_ST_WORD(&dir[TFAT_DIR_FstClusHI], dclust >> 16);
#endif

	/* Update the entry in FAT	*/
	return sync();
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_chmod
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_chmod (const uint8_t *path, uint8_t value, uint8_t mask)
* Description	: Change File Attribute
* Arguments		: Pointer to the file path
				  Attribute bits
				  Attribute mask to change
* Return value	: TFAT_FR_OK - success
				  else fail
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_chmod(const uint8_t *path, uint8_t value, uint8_t mask)
{
	FRESULT res;
	DIR dj;
	uint8_t *dir;
	uint8_t fn[8+3+1];

	res = auto_mount(&path, 1);
	if (res == TFAT_FR_OK)
	{
		/* Trace the file path */
		res = trace_path(&dj, fn, path, &dir);
		/* Trace completed */
		if (res == TFAT_FR_OK)
		{
			if (!dir)
			{
				/* Root directory */
				res = TFAT_FR_INVALID_NAME;
			}

			else
			{
				/* Valid attribute mask */
				mask &= TFAT_AM_RDO | TFAT_AM_HID | TFAT_AM_SYS | TFAT_AM_ARC;
				/* Apply attribute change */
				dir[TFAT_DIR_Attr] = (value & mask) | (dir[TFAT_DIR_Attr] & (uint8_t)~mask);
				res = sync();
			}
		}
	}

	return res;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_utime
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_utime (const uint8_t *path, const FILINFO *finfo)
* Description	: Change Timestamp
* Arguments		: Pointer to the file/directory name
				  Pointer to the timestamp to be set
* Return value	: TFAT_FR_OK - success
				  else fail
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_utime(const uint8_t *path, const FILINFO *finfo)
{
	FRESULT res;
	DIR dj;
	uint8_t *dir;
	uint8_t fn[8+3+1];

	res = auto_mount(&path, 1);
	if (res == TFAT_FR_OK)
	{
		/* Trace the file path */
		res = trace_path(&dj, fn, path, &dir);
		/* Trace completed */
		if (res == TFAT_FR_OK)
		{
			if (!dir)
			{
				/* Root directory */
				res = TFAT_FR_INVALID_NAME;
			}

			else
			{
				TFAT_ST_WORD(&dir[TFAT_DIR_WrtTime], finfo->ftime);
				TFAT_ST_WORD(&dir[TFAT_DIR_WrtDate], finfo->fdate);
				res = sync();
			}
		}
	}

	return res;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_rename
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_rename (const uint8_t *path_old,	const uint8_t *path_new)
* Description	: Rename File/Directory
* Arguments		: Pointer to the old name
				  Pointer to the new name
* Return value	: TFAT_FR_OK successful
				  other - failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_rename(const uint8_t *path_old,	const uint8_t *path_new)
{
	FRESULT res;
	uint32_t sect_old;
	uint8_t *dir_old, *dir_new, direntry[32-11];
	DIR dj;
	uint8_t fn[8+3+1];

	res = auto_mount(&path_old, 1);

	if (res != TFAT_FR_OK)
		return res;

	/* Check old object */
	res = trace_path(&dj, fn, path_old, &dir_old);

	/* The old object is not found */
	if (res != TFAT_FR_OK)
		return res;

	if (!dir_old)
		return TFAT_FR_NO_FILE;

	/* Save the object information */
	sect_old = dj.fs->winsect;
	memcpy(direntry, &dir_old[TFAT_DIR_Attr], 32 - 11);

	/* Check new object */
	res = trace_path(&dj, fn, path_new, &dir_new);

	/* The new object name is already existing */
	if (res == TFAT_FR_OK)
		return TFAT_FR_EXIST;

	/* Is there no old name? */
	if (res != TFAT_FR_NO_FILE)
		return res;

	/* Reserve a directory entry */
	res = reserve_direntry(&dj, &dir_new);

	if (res != TFAT_FR_OK)
		return res;

	/* Create new entry */
	memcpy(&dir_new[TFAT_DIR_Attr], direntry, 32 - 11);
	memcpy(&dir_new[TFAT_DIR_Name], fn, 8 + 3);
	dir_new[TFAT_DIR_NTres] = fn[11];
	dj.fs->winflag = 1;

	/* Delete old entry */
	if (!move_window(sect_old))
		return TFAT_FR_RW_ERROR;

	dir_old[TFAT_DIR_Name] = 0xE5;

	return sync();
}

#endif /* !_TFAT_FS_READONLY */
#endif /* _TFAT_FS_MINIMIZE == 0 */
#endif /* _TFAT_FS_MINIMIZE <= 1 */
#endif /* _TFAT_FS_MINIMIZE <= 2 */

#if _TFAT_USE_FORWARD
/*""FUNC COMMENT""*******************************************************************
* Function Name	: R_tfat_f_forward
* Include		: r_TinyFAT.h
* Declaration	: FRESULT R_tfat_f_forward (FIL *fp, uint16_t (*func)(const uint8_t*,uint16_t),	uint16_t btr, uint16_t *br)
* Description	: Forward data to the stream directly
* Arguments		: Pointer to the file object
				  Pointer to the streaming function
				  Number of bytes to forward
				  Pointer to number of bytes forwarded
* Return value	: TFAT_FR_OK successful
				  other - failed
*""FUNC COMMENT END""****************************************************************/
FRESULT R_tfat_f_forward(FIL *fp, uint16_t (*func)(const uint8_t*, uint16_t),	uint16_t btr, uint16_t *br)
{
	FRESULT res;
	uint32_t remain;
	uint16_t rcnt;
	CLUST clust;

	*br = 0;

	/* Check validity of the object */
	res = validate(fp->fs, fp->id);

	if (res != TFAT_FR_OK)
		return res;

	/* Check error flag */
	if (fp->flag & TFAT_FA__ERROR)
		return TFAT_FR_RW_ERROR;

	/* Check access mode */
	if (!(fp->flag & TFAT_FA_READ))
		return TFAT_FR_DENIED;

	remain = fp->fsize - fp->fptr;

	/* Truncate btr by remaining bytes */
	if (btr > remain)
		btr = (uint16_t)remain;

	/* Repeat until all data transferred */
	for (;  btr && (*func)(NULL, 0);fp->fptr += rcnt, *br += rcnt, btr -= rcnt)
	{
		/* On the sector boundary? */
		if ((fp->fptr % 512U) == 0)
		{
			/* On the cluster boundary? */
			if (fp->csect >= fp->fs->csize)
			{
				/* On the top of the file? */
				clust = (fp->fptr == 0) ?
				        fp->org_clust : get_cluster(fp->curr_clust);

				if (clust < 2 || clust >= fp->fs->max_clust)
					goto ff_error;
				/* Update current cluster */
				fp->curr_clust = clust;
				/* Reset sector address in the cluster */
				fp->csect = 0;
			}

			/* Next sector address in the cluster */
			fp->csect++;
		}

		/* Move sector window */
		if (!move_window(clust2sect(fp->curr_clust) + fp->csect - 1))
			goto ff_error;

		/* Forward data from sector window */
		rcnt = 512U - (uint16_t)(fp->fptr % 512U);

		if (rcnt > btr)
			rcnt = btr;

		rcnt = (*func)(&fp->fs->win[(uint16_t)fp->fptr % 512U], rcnt);

		if (rcnt == 0)
			goto ff_error;
	}

	return TFAT_FR_OK;

	/* Abort this function due to an unrecoverable error */
ff_error:
	fp->flag |= TFAT_FA__ERROR;

	return TFAT_FR_RW_ERROR;
}
#endif /* _TFAT_USE_FORWARD */


#if _TFAT_USE_STRFUNC >= 1
/*""FUNC COMMENT""*******************************************************************
* Function Name	: fgets
* Include		: r_TinyFAT.h
* Declaration	: uint8_t* fgets (uint8_t* buff, int16_t len, FIL* fil)
* Description	: Get a string from the file
* Arguments		: Pointer to the string buffer to read
				  Size of string buffer
				  Pointer to the file object
* Return value	: String received
*""FUNC COMMENT END""****************************************************************/
uint8_t* fgets(uint8_t* buff, int16_t len, FIL* fil)
{
	int16_t i = 0;
	uint8_t *p = buff;
	uint16_t rc;

	/* Read bytes until buffer gets filled */
	while (i < len - 1)
	{
		R_tfat_f_read(fil, p, 1, &rc);

		/* Break when no data to read */
		if (rc != 1)
			break;

#if _TFAT_USE_STRFUNC >= 2
		/* Strip '\r' */
		if (*p == '\r')
			continue;
#endif
		i++;

		/* Break when reached end of line */
		if (*p++ == '\n')
			break;
	}
	*p = 0;

	/* When no data read (eof or error), return with error. */
	return i ? buff : 0;
}

#if !_TFAT_FS_READONLY
#include <stdarg.h>
/*""FUNC COMMENT""*******************************************************************
* Function Name	: fputc
* Include		: r_TinyFAT.h
* Declaration	: int16_t fputc (int16_t chr,FIL* fil)
* Description	: Put a character to the file
* Arguments		: A character to be output
				  Pointer to the file object
* Return value	: Character written to the file
*""FUNC COMMENT END""****************************************************************/
int16_t fputc(int16_t chr, FIL* fil)
{
	uint16_t bw;
	uint8_t c;

#if _TFAT_USE_STRFUNC >= 2
	/* LF -> CRLF conversion */
	if (chr == '\n')
		fputc('\r', fil);
#endif

	/* Special value may be used to switch the destination to any other device */
	if (!fil)
	{
		return chr;
	}

	c = (uint8_t)chr;

	/* Write the character to the file */
	R_tfat_f_write(fil, &c, 1, &bw);

	/* Return the result */
	return bw ? chr : EOF;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: fputs
* Include		: r_TinyFAT.h
* Declaration	: int16_t fputs (const uint8_t* str,	FIL* fil)
* Description	: Put a string to the file
* Arguments		: Pointer to the string to be output
				  Pointer to the file object
* Return value	: no. of characters written
*""FUNC COMMENT END""****************************************************************/
int16_t fputs(const uint8_t* str,	FIL* fil)
{
	int16_t n;

	/* Write each character to the file till the EOF is detected	*/
	for (n = 0; *str; str++, n++)
	{
		if (fputc(*str, fil) == EOF)
			return EOF;
	}

	return n;
}

/*""FUNC COMMENT""*******************************************************************
* Function Name	: fprintf
* Include		: r_TinyFAT.h
* Declaration	: int16_t fprintf (FIL* fil, const uint8_t* str, ...)
* Description	: Put a formatted string to the file
* Arguments		: Pointer to the file object
				  Pointer to the format string
				  Optional arguments...
* Return value	: On success -> Total number of characters written
				  On failure -> -1 (EOF) is returned.
*""FUNC COMMENT END""****************************************************************/
int16_t fprintf(FIL* fil, const uint8_t* str, ...)
{
	/* Type to hold information about variable arguments	*/
	va_list arp;
	uint8_t c, f, r;
	uint32_t val;
	uint8_t s[16];
	int16_t i, w, res, cc;

	/*	Initializes the object "arp" (whose type is va_list) to hold the information
	    needed to retrieve the additional arguments after parameter "str" with
		function va_arg. */
	va_start(arp, str);

	/* Read the string till EOF is detected	*/
	for (cc = res = 0; cc != EOF; res += cc)
	{
		/* Read one character	*/
		c = *str++;

		/* Break the loop if null character is found */
		if (c == 0)
			break;

		/* If it is non escape character, keep writing it to the file.	*/
		if (c != '%')
		{
			cc = fputc(c, fil);

			if (cc != EOF)
				cc = 1;

			continue;
		}
		w = f = 0;

		/* Determine the type of format */
		c = *str++;

		/* Flag: '0' padding */
		if (c == '0')
		{
			f = 1;
			c = *str++;
		}

		/* Precision */
		while (c >= '0' && c <= '9')
		{
			w = w * 10 + (c - '0');
			c = *str++;
		}

		/* Prefix: Size is long int */
		if (c == 'l')
		{
			f |= 2;
			c = *str++;
		}

		/* Type is string */
		if (c == 's')
		{
			/* Write the string received by "va_arg" as variable arguments 	*/
			cc = fputs(va_arg(arp, uint8_t*), fil);
			continue;
		}

		/* Type is character */
		if (c == 'c')
		{
			/* Write the character received by "va_arg" as variable arguments 	*/
			cc = fputc(va_arg(arp, uint8_t), fil);

			/* check for EOF */
			if (cc != EOF)
				cc = 1;
			continue;
		}
		r = 0;

		/* Type is signed decimal */
		if (c == 'd')
			r = 10;

		/* Type is unsigned decimal */
		if (c == 'u')
			r = 10;

		/* Type is unsigned hexdecimal */
		if (c == 'X')
			r = 16;

		/* Unknown type */
		if (r == 0)
			break;

		/* Get the value */
		if (f & 2)
		{
			val = (uint32_t)va_arg(arp, int32_t);
		}

		else
		{
			val = (c == 'd') ? (uint32_t)(int32_t)va_arg(arp, int16_t) : (uint32_t)va_arg(arp, uint16_t);
		}

		/* Put numeral string */
		if (c == 'd')
		{
			/* If the type is signed decimal and the value is negative, then convert it to
			   positive integer	*/
			if (val >= 0x80000000)
			{
				val = 0 - val;
				f |= 4;
			}
		}

		i = sizeof(s) - 1;
		s[i] = 0;
		do
		{
			c = (uint8_t)(val % r + '0');

			if (c > '9')
				c += 7;

			s[--i] = c;
			val /= r;
		}
		while (i && val);

		if (i && (f & 4))
			s[--i] = '-';

		w = sizeof(s) - 1 - w;

		while (i && i > w)
			s[--i] = (f & 1) ? '0' : ' ';

		cc = fputs(&s[i], fil);
	}

	/* Performs the appropiate actions to facilitate a normal return by this
	   function by making a call to "va_end" function. */
	va_end(arp);

	return (cc == EOF) ? cc : res;
}

#endif /* !_TFAT_FS_READONLY */
#endif /* _TFAT_USE_STRFUNC >= 1*/
