/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdlib.h>

int main(void)
{
	char *p;

	p = malloc(1000);
	free(p);
	p = malloc(10000);
	free(p);
	p = malloc(100000);
	free(p);
	p = malloc(1000000);
	free(p);

	return 0;
}
