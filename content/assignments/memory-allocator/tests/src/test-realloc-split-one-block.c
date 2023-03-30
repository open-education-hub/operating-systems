// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	int sizes[9];
	void *prealloc_ptr, *ptrs[9];

	/* Init sizes */
	for (int i = 0; i < 9; i++)
		sizes[i] = MMAP_THRESHOLD / (1 << (i + 1));

	/* Create a free block */
	prealloc_ptr = mock_preallocate();
	taint(prealloc_ptr, MOCK_PREALLOC);
	os_free(prealloc_ptr);

	/* Split the chunk multiple times */
	for (int i = 0; i < 9; i++)
		ptrs[i] = os_realloc_checked(NULL, sizes[i]);

	/* Free the first ptr and reallocate the others */
	ptrs[0] = os_realloc_checked(ptrs[0], 0);

	/* Use ptrs[1] as a separator to prevent block coalesce */
	for (int i = 2; i < 8; i++)
		ptrs[i] = os_realloc_checked(ptrs[i], sizes[i-1] + 30);

	/* Cleanup */
	for (int i = 0; i < 9; i++)
		os_free(ptrs[i]);

	return 0;
}
