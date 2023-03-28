/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __TYPES_H__
#define __TYPES_H__	1

typedef unsigned long size_t;
typedef long ssize_t;
typedef long off_t;
typedef long long quad_t;

typedef unsigned int mode_t;		/* Type of file attribute bitmasks.  */
typedef unsigned int ino_t;		/* Type of file serial numbers.  */
typedef quad_t ino64_t;			/* Type of file serial numbers (LFS).  */
typedef int dev_t;			/* Type of device numbers.  */
typedef unsigned short int nlink_t;	/* Type of file link counts.  */
typedef unsigned int uid_t;		/* Type of user identifications.  */
typedef unsigned int gid_t;		/* Type of group identifications.  */

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef int int32_t;
typedef long int64_t;

#define NULL	((void *) 0)

#endif
