/*
  This file is part of UFFS, the Ultra-low-cost Flash File System.
  
  Copyright (C) 2005-2009 Ricky Zheng <ricky_gz_zheng@yahoo.co.nz>

  UFFS is free software; you can redistribute it and/or modify it under
  the GNU Library General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any
  later version.

  UFFS is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
  or GNU Library General Public License, as applicable, for more details.
 
  You should have received a copy of the GNU General Public License
  and GNU Library General Public License along with UFFS; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA  02110-1301, USA.

  As a special exception, if other files instantiate templates or use
  macros or inline functions from this file, or you compile this file
  and link it with other works to produce a work based on this file,
  this file does not by itself cause the resulting work to be covered
  by the GNU General Public License. However the source code for this
  file must still be made available in accordance with section (3) of
  the GNU General Public License v2.
 
  This exception does not invalidate any other reasons why a work based
  on this file might be covered by the GNU General Public License.
*/

/**
 * \file uffs_fd.h
 * \brief PISIX like file operations
 * \author Ricky Zheng, created 8th Jun, 2005
 */

#include "uffs/uffs_config.h"
#include "uffs/uffs_core.h"
#include "uffs/uffs_fs.h"
#include "uffs/uffs.h"
#include "uffs/uffs_find.h"
#include <string.h>


/**
 * \brief POSIX dirent
 */
struct uffs_dirent {
    int d_ino;							/* inode number (serial number or this record) */
	char d_name[MAX_FILENAME_LENGTH];	/* name of this record */

    int d_off;							/* offset to this dirent */
    unsigned short int d_reclen;		/* length of this uffs_dirent */
    unsigned short int d_namelen;		/* length of this d_name */
	unsigned char d_type;				/* type of this record */
};

/**
 * \brief POSIX DIR
 */
typedef struct uffs_dirSt {
    struct uffs_ObjectSt   *obj;		/* dir object */
    struct uffs_FindInfoSt f;			/* find info */
    struct uffs_ObjectInfoSt info;		/* object info */
    struct uffs_dirent dirent;			/* dir entry */
} uffs_DIR;

/**
 * \brief POSIX stat
 */
struct uffs_stat {
    int			st_dev;     /* ID of device containing file */
    int			st_ino;     /* inode number */
    int			st_mode;    /* protection */
    int			st_nlink;   /* number of hard links */
    int			st_uid;     /* user ID of owner */
    int			st_gid;     /* group ID of owner */
    int			st_rdev;    /* device ID (if special file) */
    long		st_size;    /* total size, in bytes */
    int			st_blksize; /* blocksize for filesystem I/O */
    int			st_blocks;  /* number of blocks allocated */
    u32			st_atime;   /* time of last access */
    u32			st_mtime;   /* time of last modification */
    u32			st_ctime;   /* time of last status change */
};


URET uffs_InitDirEntryBuf(void);
URET uffs_ReleaseDirEntryBuf(void);

/* POSIX compliant file system APIs */

int uffs_open(const char *name, int oflag, ...);
int uffs_close(int fd);
int uffs_read(int fd, void *data, int len);
int uffs_write(int fd, void *data, int len);
long uffs_seek(int fd, long offset, int origin);
long uffs_tell(int fd);
int uffs_eof(int fd);
int uffs_flush(int fd);
int uffs_rename(const char *old_name, const char *new_name);
int uffs_remove(const char *name);
int uffs_truncate(int fd, long remain);

int uffs_stat(const char *filename, struct uffs_stat *buf);
int uffs_lstat(const char *filename, struct uffs_stat *buf);
int uffs_fstat(int fd, struct uffs_stat *buf);

int uffs_closedir(uffs_DIR *dirp);
uffs_DIR * uffs_opendir(const char *path);
struct uffs_dirent * uffs_readdir(uffs_DIR *dirp);

void uffs_rewinddir(uffs_DIR *dirp);

#if 0
void uffs_seekdir(uffs_DIR *dirp, long loc);
long uffs_telldir(uffs_DIR *dirp);
#endif

int uffs_get_error(void);
int uffs_set_error(int err);

