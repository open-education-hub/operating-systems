// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptr, *ptr1, *ptr2, *ptr3;
	void *c1, *c2, *c3, *c4, *c5, *c6;

	prealloc_ptr = mock_preallocate();

	/* Have 3 chunks */
	ptr1 = os_realloc_checked(NULL, 1000);
	taint(ptr1, 1000);
	ptr2 = os_realloc_checked(NULL, 1000);
	taint(ptr2, 1000);
	ptr3 = os_realloc_checked(NULL, 1000);
	taint(ptr3, 1000);

	/* Split middle chunk */
	os_free(ptr2);
	c1 = os_realloc_checked(NULL, 300);
	c2 = os_realloc_checked(NULL, 300);
	c3 = os_realloc_checked(NULL, 300);

	/* Split middle chunk */
	os_free(c2);
	c4 = os_realloc_checked(NULL, 70);
	c5 = os_realloc_checked(NULL, 70);
	c6 = os_realloc_checked(NULL, 70);

	/* Rebuild */
	os_free(c4);
	os_free(c5);
	os_free(c6);
	ptr = os_realloc_checked(NULL, 100);
	ptr = os_realloc_checked(ptr, 200);
	ptr = os_realloc_checked(ptr, 300);
	os_free(c1);
	os_free(c3);
	ptr = os_realloc_checked(ptr, 600);
	ptr = os_realloc_checked(ptr, 0);
	ptr = os_realloc_checked(ptr, 1000);
	os_free(ptr1);
	os_free(ptr3);
	ptr = os_realloc_checked(ptr, 2000);
	ptr = os_realloc_checked(ptr, 0);
	ptr = os_realloc_checked(ptr, 3000);

	/* Cleanup */
	os_free(prealloc_ptr);
	os_free(ptr);

	return 0;
}
