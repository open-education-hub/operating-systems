// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>

void fun(void)
{
	int a = 42;
	int b[3];

	for (int i = 0; i < 4; i++)
		scanf("%d", &b[i]);

	printf("a = %d\n", a);
}

int main(void)
{
	fun();
}
