/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>
#include <stdlib.h>

static int random_func()
{
	int a = 101, b = 102, c = 103, d = 104;
	int e = 105, f = 106, g = 107;
	return 1;
}

static int *bad()
{
	int p = 10;
	int *q = &p;
	return q;
}

int main(void)
{
	// 1st example
	int *q = bad();
	printf("*q = %d\n", *q);
	random_func();
	printf("*q = %d\n", *q);

	// 2nd example
	int a[10];
	a[20] = 5;
	printf("a[20] = %d\n", a[20]);

	// 3rd example
	a[14] = 0;

	return 0;
}
