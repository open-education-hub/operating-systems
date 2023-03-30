// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptrs[NUM_SZ_SM];

	prealloc_ptr = mock_preallocate();

	/* Test coalesce by expanding to multiple blocks */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptrs[i] = os_realloc_checked(NULL, inc_sz_sm[i]);
		taint(ptrs[i], inc_sz_sm[i]);
	}

	for (int i = 2; i < NUM_SZ_SM; i++)
		os_free(ptrs[i]);

	ptrs[0] = os_realloc_checked(ptrs[0], 1000);
	taint(ptrs[0], 1000);
	ptrs[0] = os_realloc_checked(ptrs[0], 4000);
	taint(ptrs[0], 4000);
	ptrs[0] = os_realloc_checked(ptrs[0], 8000);

	/* Cleanup */
	os_free(ptrs[0]);
	os_free(ptrs[1]);
	os_free(prealloc_ptr);

	return 0;
}
