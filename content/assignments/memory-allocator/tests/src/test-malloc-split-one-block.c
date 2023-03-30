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
	os_free(prealloc_ptr);

	/* Split the chunk multiple times */
	for (int i = 0; i < 9; i++)
		ptrs[i] = os_malloc_checked(sizes[i]);

	/* Cleanup */
	for (int i = 0; i < 9; i++)
		os_free(ptrs[i]);

	return 0;
}
