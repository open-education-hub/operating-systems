// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	int sizes[10];
	void *prealloc_ptr, *end[3], *ptrs[10];

	/* Init sizes */
	for (int i = 0; i < 10; i++)
		sizes[i] = MMAP_THRESHOLD / (1 << (i + 1));

	/* Create a list of blocks starting with a free block */
	prealloc_ptr = mock_preallocate();
	for (int i = 0; i < 3; i++)
		end[i] = os_malloc_checked(1000);
	os_free(prealloc_ptr);

	/* Split the first chunk multiple times */
	for (int i = 0; i < 10; i++)
		ptrs[i] = os_malloc_checked(sizes[i]);

	/* Cleanup */
	for (int i = 0; i < 3; i++)
		os_free(end[i]);
	for (int i = 0; i < 10; i++)
		os_free(ptrs[i]);

	return 0;
}
