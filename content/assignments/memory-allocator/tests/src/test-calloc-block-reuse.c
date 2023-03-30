// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptrs[NUM_SZ_SM];

	prealloc_ptr = mock_preallocate();

	/* Test block reuse - same size */
	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptrs[i] = os_calloc_checked(1, inc_sz_sm[i]);
		taint(ptrs[i], inc_sz_sm[i]);
	}

	for (int i = 0; i < NUM_SZ_SM; i++) {
		os_free(ptrs[i]);
		ptrs[i] = os_calloc_checked(1, inc_sz_sm[i]);
		taint(ptrs[i], inc_sz_sm[i]);
	}

	/* Test block reuse - smaller size */
	for (int i = NUM_SZ_SM - 1; i >= 2; i--) {
		os_free(ptrs[i]);
		ptrs[i] = os_calloc_checked(1, inc_sz_sm[i] - 30);
		taint(ptrs[i], inc_sz_sm[i] - 30);
	}

	/* Test new block creation */
	os_free(ptrs[0]);
	ptrs[0] = os_calloc_checked(1, 4000);

	/* Cleanup */
	for (int i = 0; i < NUM_SZ_SM; i++)
		os_free(ptrs[i]);
	os_free(prealloc_ptr);

	return 0;
}
