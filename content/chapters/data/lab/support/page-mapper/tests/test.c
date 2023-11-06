// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "page_mapper.h"
#include "utils.h"
#include "graded_test.h"

static long page_size;

#define test_page(diff, num_pages)		\
	((diff) >= (num_pages) * page_size &&	\
	 (diff) < ((num_pages) + 1) * page_size)

#define vsz_prologue()				\
	long vsz_before, vsz_after, vsz_diff;	\
	vsz_before = get_current_vsz()

#define vsz_epilogue(np)			\
	vsz_after = get_current_vsz();		\
	vsz_diff = vsz_after - vsz_before;	\
	return test_page(vsz_diff, (np))


static long get_current_vsz(void)
{
	FILE *f;
	pid_t pid;
	static char proc_buffer[8192];
	char filename[256];
	long size;
	char *p;

	pid = getpid();
	sprintf(filename, "/proc/%d/status", pid);
	f = fopen(filename, "rt");
	DIE(f == NULL, "fopen");
	fread(proc_buffer, 1, 8192, f);
	fclose(f);

	p = strstr(proc_buffer, "VmSize");
	size = strtol(p+7, NULL, 10) * 1024;
	log_debug("size: %ld", size);

	return size;
}

static int test_res_1(void)
{
	vsz_prologue();
	do_map(1);
	vsz_epilogue(1);
}

static int test_res_2(void)
{
	vsz_prologue();
	do_map(2);
	vsz_epilogue(2);
}

static int test_res_10(void)
{
	vsz_prologue();
	do_map(10);
	vsz_epilogue(10);
}

static int test_res_10_res_20(void)
{
	vsz_prologue();
	do_map(20);
	do_map(10);
	vsz_epilogue(30);
}

static struct graded_test all_tests[] = {
	{ test_res_1, "test_res_1", 25 },
	{ test_res_2, "test_res_2", 25 },
	{ test_res_10, "test_res_10", 25 },
	{ test_res_10_res_20, "test_res_10_res_20", 25 },
};

int main(void)
{
	page_size = sysconf(_SC_PAGESIZE);

	/* Change to LOG_DEBUG for more messages. */
	log_set_level(LOG_INFO);

	run_tests(all_tests, sizeof(all_tests) / sizeof(all_tests[0]));

	return 0;
}
