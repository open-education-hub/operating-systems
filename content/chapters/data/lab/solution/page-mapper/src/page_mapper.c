// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

#include "page_mapper.h"
#include "utils.h"

void do_map(unsigned int num_pages)
{
	/* TODO 2: Obtain page size. */
	long page_size = sysconf(_SC_PAGESIZE);
	void *ptr;

	/* TODO 2: Map pages in memory using mmap(). */
	ptr = mmap(NULL, num_pages * page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	DIE(ptr == NULL, "mmap");
}
