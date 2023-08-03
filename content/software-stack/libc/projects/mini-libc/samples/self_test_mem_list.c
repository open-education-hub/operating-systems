// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <unistd.h>

static const char msg_failed[] = "failed\n";
static const char msg_passed[] = "passed\n";

static void test(const char *msg, size_t msglen, int condition)
{
	write(1, msg, msglen);
	write(1, " .......... ", 12);
	if (condition)
		write(1, msg_passed, sizeof(msg_passed)-1);
	else
		write(1, msg_failed, sizeof(msg_failed)-1);
}

int main(void)
{
	mem_list_init();
	test("num aftter init", 15, mem_list_num_items() == 0);

	mem_list_add((void *) 0x1000, 256);
	test("add 0x1000", 10, mem_list_num_items() == 1);

	mem_list_add((void *) 0x2000, 1024);
	test("add 0x2000", 10, mem_list_num_items() == 2);

	mem_list_add((void *) 0x3000, 2048);
	test("add 0x3000", 10, mem_list_num_items() == 3);

	test("find 0x1000", 11, mem_list_find((void *) 0x1000) != NULL);
	test("find 0x2000", 11, mem_list_find((void *) 0x2000) != NULL);
	test("find 0x3000", 11, mem_list_find((void *) 0x3000) != NULL);
	test("find 0x4000", 11, mem_list_find((void *) 0x4000) == NULL);

	test("find 0x2000 start", 17, mem_list_find((void *) 0x2000)->start == (void *) 0x2000);
	test("find 0x2000 len", 15, mem_list_find((void *) 0x2000)->len == 1024);

	mem_list_del((void *) 0x1000);
	test("num after del 0x1000", 20, mem_list_num_items() == 2);

	mem_list_del((void *) 0x3000);
	test("num after del 0x3000", 20, mem_list_num_items() == 1);

	mem_list_cleanup();
	test("num after cleanup", 17, mem_list_num_items() == 0);

	return 0;
}
