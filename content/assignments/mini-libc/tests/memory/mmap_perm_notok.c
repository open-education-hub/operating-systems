// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define		ALLOC_SIZE	(4 * 1024 * 1024)
#define		INFINITE	1000000

int main(void)
{
	char *p;

	p = mmap(NULL, ALLOC_SIZE, PROT_READ, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (p == MAP_FAILED)
		exit(EXIT_FAILURE);
	p[0] = 10;

	return 0;
}
