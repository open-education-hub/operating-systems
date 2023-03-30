// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr, *prealloc_ptr, *ptrs[NUM_SZ_SM];

	prealloc_ptr = mock_preallocate();

	/* Test coalesce multiple blocks */
	for (int i = 0; i < NUM_SZ_SM; i++)
		ptrs[i] = os_malloc_checked(inc_sz_sm[i]);

	for (int i = 3; i < NUM_SZ_SM; i++)
		os_free(ptrs[i]);

	ptr = os_malloc_checked(8000);

	/* Cleanup */
	os_free(ptrs[0]);
	os_free(ptrs[1]);
	os_free(ptrs[2]);
	os_free(ptr);
	os_free(prealloc_ptr);

	return 0;
}
