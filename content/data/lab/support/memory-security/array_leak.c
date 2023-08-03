// SPDX-License-Identifier: BSD-3-Clause
#include <stdio.h>

int main(void)
{
	int c[5] = {6, 7, 8, 9, 10};
	int a = 20;
	int b[5] = {1, 2, 3, 4, 5};

	for (int i = -1; i < 25; i++)
		printf("c[%d] = %x\n", i, c[i]);

	(void) a;
	(void) b;
	return 0;
}
