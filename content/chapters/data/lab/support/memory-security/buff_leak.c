// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>

int a = 9;
int b;

int main(void)
{
	int c = 15;
	int *k = malloc(sizeof(int));
	*k = 100;
	char d;
	char *p = &d;

	long long offset;

	printf("&a = %lld\n", (long long)&a);
	printf("&b = %lld\n", (long long)&b);
	printf("&c = %lld\n", (long long)&c);
	printf("k = %lld\n",  (long long)k);
	printf("The player pointer is %lld\n", (long long)p);

Lagain1:
	// insert offset of p to c
	printf("What's the offset of c from p?\n");
	scanf("%lld", &offset);

	if ((int *)(p + offset) == &c) {
		printf("Congrats, you have leaked: %d\n\n", c);
	} else {
		printf("Not quite. Try again\n");
		goto Lagain1;
	}

Lagain2:
	// insert offset of p to b
	printf("What's the offset of b from p?\n");
	scanf("%lld", &offset);

	if ((int *)(p + offset) == &b) {
		printf("Congrats, you have leaked: %d\n\n", b);
	} else {
		printf("Not quite. Try again\n");
		goto Lagain2;
	}

Lagain3:
	// insert offset of p to a
	printf("What's the offset of a from p?\n");
	scanf("%lld", &offset);

	if ((int *)(p + offset) == &a) {
		printf("Congrats, you have leaked: %d\n\n", a);
	} else {
		printf("Not quite. Try again\n");
		goto Lagain3;
	}

Lagain4:
	// insert offset of p to k
	printf("What's the offset of k from p?\n");
	scanf("%lld", &offset);

	if ((int *)(p + offset) == k) {
		printf("Congrats, you have leaked: %d\n\n", *k);
	} else {
		printf("Not quite. Try again\n");
		goto Lagain4;
	}

	printf("Well done, padawan!\n");

	return 0;
}
