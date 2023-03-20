// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>

#define		ALLOC_SIZE	(4 * 1024 * 1024)
#define		INFINITE	1000000

int main(void)
{
	void *p, *q, *r;

	sleep(2);

	p = malloc(ALLOC_SIZE);
	if (p == NULL)
		exit(EXIT_FAILURE);

	q = malloc(ALLOC_SIZE);
	if (q == NULL)
		exit(EXIT_FAILURE);

	r = malloc(ALLOC_SIZE);
	if (r == NULL)
		exit(EXIT_FAILURE);

	free(p);
	free(q);
	free(r);

	sleep(INFINITE);

	return 0;
}
