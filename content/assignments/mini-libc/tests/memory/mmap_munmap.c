// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define		ALLOC_SIZE	(4 * 1024 * 1024)
#define		INFINITE	1000000

int main(void)
{
	void *p;

	sleep(2);

	p = mmap(NULL, ALLOC_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (p == MAP_FAILED)
		exit(EXIT_FAILURE);

	munmap(p, ALLOC_SIZE);

	sleep(INFINITE);

	return 0;
}
