// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	int sizes[5];
	void *prealloc_ptr, *end[3], *ptrs[5];

	/* Init sizes */
	for (int i = 0; i < 5; i++)
		sizes[i] = 4000 / (1 << (i + 1));

	/* Create a list of blocks ending with a free block */
	prealloc_ptr = mock_preallocate();
	end[0] = os_calloc_checked(1, 1000);
	end[1] = os_calloc_checked(1, 2000);
	end[2] = os_calloc_checked(1, 4000);
	os_free(end[2]);

	/* Split the last block multiple times */
	for (int i = 0; i < 5; i++)
		ptrs[i] = os_calloc_checked(1, sizes[i]);

	/* Cleanup */
	os_free(prealloc_ptr);
	os_free(end[0]);
	os_free(end[1]);
	for (int i = 0; i < 5; i++)
		os_free(ptrs[i]);

	return 0;
}
