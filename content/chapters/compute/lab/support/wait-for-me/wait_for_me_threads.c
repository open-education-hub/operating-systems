// SPDX-License-Identifier: BSD-3-Clause
#include <stdio.h>

#define ARR_LEN 400

static inline void negate_array(int *arr, size_t len)
{
	for (int i = len - 1; i != -1; --i)
		arr[i] = -arr[i];
}

int main(void)
{
	int arr[ARR_LEN];

	for (int i = 0; i < ARR_LEN; ++i)
		arr[i] = i + 1;

	/* TODO: Call the `negate_array()` function in a separate thread. */

	for (int i = 0; i < ARR_LEN; ++i)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}
