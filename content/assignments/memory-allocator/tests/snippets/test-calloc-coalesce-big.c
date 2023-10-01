// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr, *prealloc_ptr, *ptrs[NUM_SZ_SM/2];

	prealloc_ptr = mock_preallocate();

	/* Test coalesce multiple blocks */
	for (int i = 0; i < NUM_SZ_SM/2; i++) {
		ptrs[i] = os_calloc_checked(1, inc_sz_sm[i]);
		taint(ptrs[i], inc_sz_sm[i]);
	}

	for (int i = 0; i < NUM_SZ_SM/2; i++)
		os_free(ptrs[i]);

	ptr = os_calloc_checked(20, 30);

	/* Cleanup */
	os_free(ptr);
	os_free(prealloc_ptr);

	return 0;
}
