/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *ptr1, *ptr2, *ptr3;
	size_t i;
	FILE *f;
	char c;

	ptr1 = malloc(10000);
	ptr2 = malloc(100000);
	ptr3 = malloc(1000000);

	for (i = 0; i < 10; i++)
		printf("a");
	printf("a\n");

	free(ptr1);
	free(ptr2);
	free(ptr3);

	for (i = 0; i < 10; i++)
		fprintf(stderr, "a");
	fprintf(stderr, "a\n");

	f = fopen("in.txt", "rt");

	for (i = 0; i < 10; i++)
		fread(&c, 1, 1, f);

	return 0;
}
