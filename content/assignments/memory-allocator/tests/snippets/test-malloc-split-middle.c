// SPDX-License-Identifier: BSD-3-Clause

#include "test-utils.h"

int main(void)
{
	void *prealloc_ptr, *ptr, *ptr1, *ptr2, *ptr3;
	void *c1, *c2, *c3, *c4, *c5, *c6;

	prealloc_ptr = mock_preallocate();

	ptr1 = os_malloc_checked(1000);
	ptr2 = os_malloc_checked(1000);
	ptr3 = os_malloc_checked(1000);

	os_free(ptr2);
	c1 = os_malloc_checked(300);
	c2 = os_malloc_checked(300);
	c3 = os_malloc_checked(300);

	os_free(c2);
	c4 = os_malloc_checked(70);
	c5 = os_malloc_checked(70);
	c6 = os_malloc_checked(70);

	/* Expect new block  */
	ptr = os_malloc_checked(2000);
	os_free(ptr);

	/* Cleanup */
	os_free(prealloc_ptr);
	os_free(ptr1);
	os_free(ptr3);
	os_free(c1);
	os_free(c3);
	os_free(c4);
	os_free(c5);
	os_free(c6);

	return 0;
}
