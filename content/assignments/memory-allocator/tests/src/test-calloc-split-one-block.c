// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptrs[NUM_SZ_SM];

	/* Create a free block */
	prealloc_ptr = mock_preallocate();
	os_free(prealloc_ptr);

	/* Split the chunk multiple times */
	for (int i = 0; i < NUM_SZ_SM; i++)
		ptrs[i] = os_calloc_checked(1, dec_sz_sm[i]);

	/* Cleanup */
	for (int i = 0; i < NUM_SZ_SM; i++)
		os_free(ptrs[i]);

	return 0;
}
