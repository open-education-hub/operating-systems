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
	end[0] = os_realloc_checked(NULL, 1000);
	end[1] = os_realloc_checked(NULL, 2000);
	end[2] = os_realloc_checked(NULL, 60000);
	taint(end[2], 60000);
	os_free(end[2]);

	/* Split the last block multiple times */
	for (int i = 0; i < 8; i++)
		ptrs[i] = os_realloc_checked(NULL, sizes[i]);

	/* Free the first ptr and fit all other inside */
	ptrs[0] = os_realloc_checked(ptrs[0], 0);

	for (int i = 1; i < 8; i++)
		ptrs[i] = os_realloc_checked(ptrs[i], sizes[i] + 30);

	/* Free the first ptr and reallocate the others */
	ptrs[0] = os_realloc_checked(ptrs[0], 0);

	/* Use ptrs[1] as a separator to prevent block coalesce */
	for (int i = 2; i < 7; i++)
		ptrs[i] = os_realloc_checked(ptrs[i], sizes[i-1] + 30);

	/* Cleanup */
	os_free(prealloc_ptr);
	os_free(end[0]);
	os_free(end[1]);
	for (int i = 0; i < 8; i++)
		os_free(ptrs[i]);

	return 0;
}
