/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <string.h>

static const char src[] = "warhammer40k";
static char dest[128];

int main(void)
{
	printf("[before] src is at %p, len is %lu, content: \"%s\"\n", src, strlen(src), src);
	printf("[before] dest is at %p, len is %lu, content: \"%s\"\n", dest, strlen(dest), dest);

	printf("copying src to dest\n");
	strcpy(dest, src);

	printf("[after] src is at %p, len is %lu, content: \"%s\"\n", src, strlen(src), src);
	printf("[after] dest is at %p, len is %lu, content: \"%s\"\n", dest, strlen(dest), dest);

	printf("a");
	printf("b");
	fflush(stdout);
	printf("c\n");

	return 0;
}
