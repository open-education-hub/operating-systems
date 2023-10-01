// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	int sizes[8];
	void *prealloc_ptr, *end[3], *ptrs[8];

	/* Init sizes */
	for (int i = 0; i < 8; i++)
		sizes[i] = 60000 / (1 << (i + 1));

	/* Create a list of blocks ending with a free block */
	prealloc_ptr = mock_preallocate();
	end[0] = os_malloc_checked(1000);
	end[1] = os_malloc_checked(2000);
	end[2] = os_malloc_checked(60000);
	os_free(end[2]);

	/* Split the last block multiple times */
	for (int i = 0; i < 8; i++)
		ptrs[i] = os_malloc_checked(sizes[i]);

	/* Cleanup */
	os_free(prealloc_ptr);
	os_free(end[0]);
	os_free(end[1]);
	for (int i = 0; i < 8; i++)
		os_free(ptrs[i]);

	return 0;
}
