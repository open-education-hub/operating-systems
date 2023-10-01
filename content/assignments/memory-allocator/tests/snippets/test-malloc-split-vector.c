// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

#define NUM_SPLITS 7

int main(void)
{
	void *prealloc_ptr, *ptrs[NUM_SZ_SM], *splits[NUM_SPLITS];

	prealloc_ptr = mock_preallocate();

	/* Test split block */
	for (int i = 0; i < NUM_SZ_SM; i++)
		ptrs[i] = os_malloc_checked(inc_sz_sm[i]);

	os_free(ptrs[4]);
	splits[0] = os_malloc_checked(20);
	splits[1] = os_malloc_checked(20);

	/* Test split block multiple times */
	os_free(ptrs[8]);
	for (int i = 2; i < NUM_SPLITS; i++)
		splits[i] = os_malloc_checked(200);

	/* Cleanup */
	for (int i = 0; i < NUM_SPLITS; i++)
		os_free(splits[i]);
	for (int i = 0; i < NUM_SZ_SM; i++) {
		if (i == 4 || i == 8)
			continue;
		os_free(ptrs[i]);
	}
	os_free(prealloc_ptr);

	return 0;
}
