/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>

int main(void)
{
	/*
	 * TODO: Use standard C library functions.
	 * Be as creative as you can.
	 */

	char *string = malloc(30 * sizeof(*string));

	scanf("%s", string);
	printf("string length: %d\n", strlen(string));

	free(string);

	return 0;
}
