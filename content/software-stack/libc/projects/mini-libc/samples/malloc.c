// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int *p, *q, *r;
	size_t i;

	p = malloc(10 * sizeof(*p));
	if (p == NULL)
		exit(EXIT_FAILURE);
	write(1, "Allocated p\n", 12);

	q = malloc(20 * sizeof(*q));
	if (q == NULL)
		exit(EXIT_FAILURE);
	write(1, "Allocated q\n", 12);
	free(q);
	write(1, "Freed q\n", 8);

	for (i = 0; i < 10; i++)
		p[i] = 33;

	r = realloc(p, 100);
	if (r == NULL)
		exit(EXIT_FAILURE);
	write(1, "Allocated r\n", 12);

	for (i = 0; i < 10; i++)
		if (r[i] != 33)
			write(2, "Not equal\n", 10);
	write(1, "Realloc good\n", 13);

	free(r);
	write(1, "Freed r\n", 8);

	return 0;
}
