// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *ptr;
	int free_idx[] = {0, 2, 3, 4, 7, 11, 12, 13, 14, 17, 18, 20, 21, 25, 27, 28, 29, 30, 32};
	int realloc_sz[] = {32, 24, 75, 1034, 284352, 277, 31, 876, 223455, 12, 745, 248, 1367, 3929995, 27322, 82};
	void *ptrs_sm1[NUM_SZ_SM * 3];
	void *ptrs_sm2[NUM_SZ_SM * 3];

	ptr = os_malloc_checked(0);
	os_free(ptr);

	ptr = os_malloc_checked(1000);
	taint(ptr, 1000);

	ptr = os_realloc_checked(ptr, 2000);
	os_free(ptr);

	ptr = os_calloc_checked(0, 100);
	os_free(ptr);

	ptr = os_calloc_checked(10, 100);
	taint(ptr, 1000);
	os_free(ptr);
	ptr = os_calloc_checked(10, 100);

	ptr = os_realloc_checked(ptr, MMAP_THRESHOLD + 1000);
	os_free(ptr);

	ptr = os_calloc(1, 5000);
	taint(ptr, 5000);

	ptr = os_realloc_checked(ptr, 2000);
	ptr = os_realloc_checked(ptr, 5000);
	os_free(ptr);

	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptrs_sm1[3 * i] = os_calloc_checked(1, inc_sz_sm[i]);
		taint(ptrs_sm1[3 * i], inc_sz_sm[i]);
		ptrs_sm1[3 * i + 1] = os_malloc_checked(dec_sz_sm[i]);
		taint(ptrs_sm1[3 * i + 1], dec_sz_sm[i]);
		ptrs_sm1[3 * i + 2] = os_calloc_checked(alt_sz_sm[i], 1);
		taint(ptrs_sm1[3 * i + 2], alt_sz_sm[i]);
	}

	for (unsigned int i = 0; i < sizeof(free_idx) / sizeof(int); i++)
		os_free(ptrs_sm1[free_idx[i]]);

	for (int i = 0; i < NUM_SZ_SM; i++) {
		ptrs_sm2[3 * i] = os_malloc_checked(alt_sz_sm[i]);
		taint(ptrs_sm2[3 * i], alt_sz_sm[i]);
		ptrs_sm2[3 * i + 1] = os_malloc_checked(inc_sz_sm[i]);
		taint(ptrs_sm2[3 * i + 1], inc_sz_sm[i]);
		ptrs_sm2[3 * i + 2] = os_calloc_checked(1, dec_sz_sm[i]);
		taint(ptrs_sm2[3 * i + 2], dec_sz_sm[i]);
	}

	for (unsigned int i = 0; i < sizeof(realloc_sz) / sizeof(int); i++) {
		ptrs_sm2[i] = os_realloc_checked(ptrs_sm2[i], realloc_sz[i]);
		ptrs_sm2[i + 16] = os_realloc_checked(ptrs_sm2[i + 16], realloc_sz[i]);
	}

	for (int i = 0; i < NUM_SZ_MD; i++) {
		ptrs_sm2[i] = os_realloc_checked(ptrs_sm2[i], inc_sz_md[i]);
		ptrs_sm2[i + 8] = os_realloc_checked(ptrs_sm2[i + 8], inc_sz_md[i]);
		ptrs_sm2[i + 21] = os_realloc_checked(ptrs_sm2[i + 21], inc_sz_md[i]);
	}

	for (int i = 6; i < NUM_SZ_LG; i++) {
		ptrs_sm2[i] = os_realloc_checked(ptrs_sm2[i], inc_sz_lg[i]);
		ptrs_sm2[i + 20] = os_realloc_checked(ptrs_sm2[i + 20], inc_sz_lg[i]);
	}

	for (unsigned int i = 0; i < sizeof(free_idx) / sizeof(int); i++)
		ptrs_sm1[free_idx[i]] = os_malloc_checked(100);

	/* Cleanup */
	for (int i = 0; i < NUM_SZ_SM * 3; i++) {
		os_free(ptrs_sm1[i]);
		os_free(ptrs_sm2[i]);
	}

	return 0;
}
