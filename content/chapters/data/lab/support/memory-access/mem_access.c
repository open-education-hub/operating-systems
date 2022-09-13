/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdio.h>

int main(void )
{
	int a;
	const int ca = 2;

	char *p = "LeString";
	char *const cp = "ConstLeString";
	const char *const cp2 = "LeConstString";

	int arr[20];
	char c_arr[20];

	printf("sizeof(a) = %ld\n", sizeof(a));
	printf("sizeof(ca) = %ld\n", sizeof(ca));
	printf("sizeof(p) = %ld\n", sizeof(p));
	printf("sizeof(cp) = %ld\n", sizeof(cp));
	printf("sizeof(cp2) = %ld\n", sizeof(cp2));
	printf("sizeof(arr) = %ld\n", sizeof(arr));
	printf("sizeof(c_arr) = %ld\n", sizeof(c_arr));

	return 0;
}
