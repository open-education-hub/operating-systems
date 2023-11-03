// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

#define NUM_SIZES 8

int main(void)
{
	int sizes[NUM_SIZES];
	void *prealloc_ptr, *ptrs[NUM_SIZES];

	/* Init sizes */
	for (int i = 0; i < NUM_SIZES; i++)
		sizes[i] = MMAP_THRESHOLD / (1 << (i + 1));

	/* Create a free block */
	prealloc_ptr = mock_preallocate();
	os_free(prealloc_ptr);

	/* Split the chunk multiple times */
	for (int i = 0; i < NUM_SIZES; i++)
		ptrs[i] = os_malloc_checked(sizes[i]);

	/* Cleanup */
	for (int i = 0; i < NUM_SIZES; i++)
		os_free(ptrs[i]);

	return 0;
}
