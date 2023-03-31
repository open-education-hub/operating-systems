// SPDX-License-Identifier: BSD-3-Clause
#include <stdio.h>

void pawned(void)
{
	printf("Oh no! The canary was eaten: https://www.youtube.com/watch?v=JGWOCALy1LI&ab_channel=lou2u\n");
}

void fun1(char *p)
{
	unsigned char a[8] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A'};
	unsigned long long *addr = (unsigned long long *)a;

	printf("%p\n", &pawned);
	for (int i = 0; i < 64; i++) {
		if (i % 8 == 0)
			printf("\n");
		printf("c[%d] = %x\n", i, a[i]);
	}

	printf("overwrite canary:\n");
	// TODO(Student): Add code that overwrites the canary

	printf("overwrite return address:\n");
	// TODO(Student): Add code that overwrites the return address with the addess of pawned

	(void) p;
}

int main(void)
{
	char *p = (char *)0x4343434343434343;

	fun1(p);
	return 0;
}
