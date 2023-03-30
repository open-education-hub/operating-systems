// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptrs[NUM_SZ_SM];

	prealloc_ptr = mock_preallocate();

	/* Initialize blocks */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptrs[i] = os_realloc_checked(NULL, inc_sz_sm[i]);
		taint(ptrs[i], inc_sz_sm[i]);
	}

	/* Test block reuse - same size */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptrs[i] = os_realloc_checked(ptrs[i], 0);
		ptrs[i] = os_realloc_checked(ptrs[i], inc_sz_sm[i]);
	}

	/* Test block reuse - smaller size */
	for (int i = NUM_SZ_SM - 1; i >= 2; i--) {
		ptrs[i] = os_realloc_checked(ptrs[i], 0);
		ptrs[i] = os_realloc_checked(ptrs[i], inc_sz_sm[i] - 30);
	}

	/* Test new block creation */
	ptrs[0] = os_realloc_checked(ptrs[0], 10000);

	/* Cleanup */
	os_free(prealloc_ptr);
	for (int i = 0; i < NUM_SZ_SM; i++)
		os_free(ptrs[i]);

	return 0;
}
