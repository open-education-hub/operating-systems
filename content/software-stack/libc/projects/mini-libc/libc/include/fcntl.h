/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef	_FCNTL_H
#define	_FCNTL_H	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

#define O_ACCMODE		0003
#define O_RDONLY		00
#define O_WRONLY		01
#define O_RDWR			02
#define FD_CLOEXEC		1

#ifndef O_CREAT
# define O_CREAT		0100	/* Not fcntl.  */
#endif
#ifndef O_EXCL
# define O_EXCL			0200	/* Not fcntl.  */
#endif
#ifndef O_NOCTTY
# define O_NOCTTY		0400	/* Not fcntl.  */
#endif
#ifndef O_TRUNC
# define O_TRUNC		01000	/* Not fcntl.  */
#endif
#ifndef O_APPEND
# define O_APPEND		02000
#endif
#ifndef O_DIRECTORY
# define O_DIRECTORY	0200000
#endif
#ifndef O_TMPFILE
# define O_TMPFILE		(020000000 | O_DIRECTORY)
#endif
#ifndef O_CLOEXEC
# define O_CLOEXEC		02000000
#endif

#ifndef S_IRUSR
#define S_ISUID 04000
#define S_ISGID 02000
#define S_ISVTX 01000
#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#define S_IRWXU 0700
#define S_IRGRP 0040
#define S_IWGRP 0020
#define S_IXGRP 0010
#define S_IRWXG 0070
#define S_IROTH 0004
#define S_IWOTH 0002
#define S_IXOTH 0001
#define S_IRWXO 0007
#endif

#define F_DUPFD		0	/* Duplicate file descriptor.  */
#define F_GETFD		1	/* Get file descriptor flags.  */
#define F_SETFD		2	/* Set file descriptor flags.  */
#define F_GETFL		3	/* Get file status flags.  */
#define F_SETFL		4	/* Set file status flags.  */

#define AT_FDCWD	-100	/* Special value used to indicate openat should use the current working directory. */

int open(const char *filename, int flags, ...);

#ifdef __cplusplus
}
#endif

#endif
