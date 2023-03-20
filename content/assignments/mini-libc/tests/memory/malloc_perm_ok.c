// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <unistd.h>

#define		ALLOC_SIZE	(4 * 1024 * 1024)
#define		INFINITE	1000000

int main(void)
{
	char *p;
	char value;

	p = malloc(ALLOC_SIZE);
	if (p == NULL)
		exit(EXIT_FAILURE);

	value = p[0];
	p[1023] = value;

	return 0;
}
