// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>

#include "./graded_test.h"

static int test_mmap(void)
{
	void *p = NULL;

	p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	return (long) p > 0;
}

static int test_mmap_bad_fd(void)
{
	void *p = NULL;

	p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, 2000, 0);

	return p == MAP_FAILED && errno == EBADF;
}

static int test_mmap_bad_flags(void)
{
	void *p = NULL;

	p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0);

	return p == MAP_FAILED && errno == EINVAL;
}

static int test_mremap(void)
{
	void *p;

	p = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	p = mremap(p, 4096, 8192, MREMAP_MAYMOVE);

	return (long) p > 0;
}

static int test_malloc(void)
{
	void *p = NULL;

	p = malloc(1024);

	return p != NULL;
}

static int test_malloc_two(void)
{
	void *p = NULL, *q = NULL;

	p = malloc(1024);
	q = malloc(1024);

	return p != NULL && q != NULL;
}

static int test_malloc_access(void)
{
	char *p = NULL;

	p = malloc(1024);
	p[0] = 'a';
	p[1023] = 'a';

	/* Simply test access to see if seg fault occurs. */
	return 1;
}

static int test_malloc_memset(void)
{
	char *p = NULL;

	p = malloc(1024);
	memset(p, 'a', 1024);

	return p[0] == 'a' && p[1023] == 'a';
}

static int test_malloc_memcpy(void)
{
	char *p = NULL, *q = NULL;

	p = malloc(1024);
	q = malloc(1024);
	memset(p, 'a', 1024);
	memcpy(q, p, 1024);

	return q[0] == 'a' && q[1023] == 'a';
}

static int test_calloc(void)
{
	void *p = NULL;

	p = calloc(1024, 1);

	return p != NULL;
}

static int test_realloc(void)
{
	void *p = NULL;

	p = malloc(1024);
	p = realloc(p, 4096);

	return p != NULL;
}

static int test_realloc_access(void)
{
	char *p = NULL;

	p = malloc(1024);
	p = realloc(p, 4096);
	p[0] = 'a';
	p[4095] = 'a';

	/* Simply test access to see if seg fault occurs. */
	return 1;
}

static int test_realloc_memset(void)
{
	char *p = NULL;

	p = malloc(1024);
	p = realloc(p, 4096);
	memset(p, 'a', 4096);

	return p[0] == 'a' && p[4095] == 'a';
}

static int test_realloc_array(void)
{
	void *p = NULL;

	p = malloc(1024);
	p = reallocarray(p, 4096, 1);

	return p != NULL;
}

static struct graded_test memory_tests[] = {
	{ test_mmap, "test_mmap", 8 },
	{ test_mmap_bad_fd, "test_mmap_bad_fd", 8 },
	{ test_mmap_bad_flags, "test_mmap_bad_flags", 8 },
	{ test_mremap, "test_mremap", 8 },
	{ test_malloc, "test_malloc", 8 },
	{ test_malloc_two, "test_malloc_two", 8 },
	{ test_malloc_access, "test_malloc_access", 8 },
	{ test_malloc_memset, "test_malloc_memset", 8 },
	{ test_malloc_memcpy, "test_malloc_memcpy", 8 },
	{ test_calloc, "test_calloc", 8 },
	{ test_realloc, "test_realloc", 8 },
	{ test_realloc_access, "test_realloc_access", 8 },
	{ test_realloc_memset, "test_realloc_memset", 8 },
	{ test_realloc_array, "test_realloc_array", 8 },
};

int main(void)
{
	run_tests(memory_tests, sizeof(memory_tests) / sizeof(memory_tests[0]));

	return 0;
}
