// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "access_counter.h"
#include "utils.h"
#include "graded_test.h"

static long page_size;

static void do_read(const void *addr)
{
	char a;

	a = *(char *) addr;
}

static void do_write(void *addr)
{
	*(char *) addr = 'a';
}

static void do_exec(void *addr)
{
	((void (*)(void)) addr)();
}

static int test_acess_read(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	counter = 0;
	do_read(addr);

	return counter == 1;
}

static int test_acess_write(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	counter = 0;
	do_write(addr);

	return counter == 2;
}

static int test_acess_exec(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	counter = 0;
	do_exec(addr);

	return counter == 3;
}

static int test_acess_read_write(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	do_read(addr);
	counter = 0;
	do_write(addr);

	return counter == 1;
}

static int test_acess_read_exec(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	do_read(addr);
	counter = 0;
	do_exec(addr);

	return counter == 2;
}

static int test_acess_write_exec(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	do_write(addr);
	counter = 0;
	do_exec(addr);

	return counter == 1;
}

static int test_acess_exec_read(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	do_exec(addr);
	counter = 0;
	do_read(addr);

	return counter == 0;
}

static int test_acess_exec_write(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	do_exec(addr);
	counter = 0;
	do_write(addr);

	return counter == 0;
}

static int test_acess_write_read(void)
{
	void *addr;

	addr = mmap(NULL, page_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	DIE(addr == MAP_FAILED, "mmap");

	do_write(addr);
	counter = 0;
	do_read(addr);

	return counter == 0;
}

static struct graded_test all_tests[] = {
	{ test_acess_read, "test_acess_read", 9 },
	{ test_acess_write, "test_acess_write", 9 },
	{ test_acess_exec, "test_acess_exec", 10 },
	{ test_acess_read_write, "test_acess_read_write", 12 },
	{ test_acess_read_exec, "test_acess_read_exec", 12 },
	{ test_acess_write_exec, "test_acess_write_exec", 12 },
	{ test_acess_exec_read, "test_acess_exec_read", 12 },
	{ test_acess_exec_write, "test_acess_exec_write", 12 },
	{ test_acess_write_read, "test_acess_write_read", 12 }
};

int main(void)
{
	page_size = sysconf(_SC_PAGESIZE);

	register_sigsegv_handler();

	/* Update to LOG_DEBUG to print debug messages. */
	log_set_level(LOG_INFO);

	run_tests(all_tests, sizeof(all_tests) / sizeof(all_tests[0]));

	return 0;
}

