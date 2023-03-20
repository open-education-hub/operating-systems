// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>

#define		ALLOC_SIZE	(4 * 1024 * 1024)
#define		INFINITE	1000000

int main(void)
{
	void *p;

	sleep(2);

	p = malloc(ALLOC_SIZE);
	if (p == NULL)
		exit(EXIT_FAILURE);
	free(p);

	sleep(INFINITE);

	return 0;
}
