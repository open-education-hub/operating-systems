// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptr, *ptrs[NUM_SZ_SM];

	prealloc_ptr = mock_preallocate();
	os_free(prealloc_ptr);

	for (int i = 0; i < NUM_SZ_SM; i++)
		ptrs[i] = os_malloc_checked(inc_sz_sm[i]);

	/* Test blocks coalesce on the first 2 block */
	os_free(ptrs[0]);
	os_free(ptrs[1]);
	ptrs[0] = os_malloc_checked(inc_sz_sm[0] + inc_sz_sm[1]);

	/* Test blocks coalesce on the middle 2 block */
	os_free(ptrs[4]);
	os_free(ptrs[5]);
	ptrs[4] = os_malloc_checked(inc_sz_sm[4] + inc_sz_sm[5]);

	/* Test blocks coalesce on the last 2 block */
	os_free(ptrs[8]);
	os_free(ptrs[9]);
	ptrs[8] = os_malloc_checked(inc_sz_sm[8] + inc_sz_sm[9]);

	/* Expect new block  */
	ptr = os_malloc_checked(3000);
	os_free(ptr);

	/* Cleanup */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		if (i == 1 || i == 5 || i == 9)
			continue;
		os_free(ptrs[i]);
	}

	return 0;
}
