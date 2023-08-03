/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __SYS_MMAN_H__
#define __SYS_MMAN_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

#define PROT_READ	0x1		/* Page can be read.  */
#define PROT_WRITE	0x2		/* Page can be written.  */
#define PROT_EXEC	0x4		/* Page can be executed.  */
#define PROT_NONE	0x0		/* Page can not be accessed.  */

/* Sharing types (must choose one and only one of these).  */
#define MAP_SHARED	0x01		/* Share changes.  */
#define MAP_PRIVATE	0x02		/* Changes are private.  */
#define MAP_ANONYMOUS	0x20		/* Don't use a file.  */
#define MAP_ANON	MAP_ANONYMOUS

#define MREMAP_MAYMOVE	1

#define MAP_FAILED	((void *) -1)

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
void *mremap(void *old_address, size_t old_size, size_t new_size, int flags);
int munmap(void *addr, size_t length);

#ifdef __cplusplus
}
#endif

#endif
