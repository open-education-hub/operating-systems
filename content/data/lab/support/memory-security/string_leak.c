// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>

void fun(char *p)
{
	int var = 0xAABBCCDD;
	char dst[4];

	memcpy(dst, p, 4);
	printf("%s\n", dst);

	(void) var;
}

int main(void)
{
	char *str = "soso";

	fun(str);
	return 0;
}
