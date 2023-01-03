/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <string.h>

static char buf[128];

int main(void)
{
	FILE *f;

	f = fopen("a.txt", "wt");

	strcpy(buf, "Hello, world!\n");
	fwrite(buf, 1, strlen(buf), f);
	strcpy(buf, "Bye, world!\n");
	fwrite(buf, 1, strlen(buf), f);

	fflush(f);

	return 0;
}
