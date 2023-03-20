/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __MEM_LIST_H__
#define __MEM_LIST_H__	1

#ifdef __cplusplus
extern "C" {
#endif

#include <internal/types.h>

struct mem_list {
	void *start;
	size_t len;
	struct mem_list *prev;
	struct mem_list *next;
};

extern struct mem_list mem_list_head;

void mem_list_init(void);
int mem_list_add(void *start, size_t len);
struct mem_list *mem_list_find(void *start);
int mem_list_del(void *start);
void mem_list_cleanup(void);
size_t mem_list_num_items(void);

#ifdef __cplusplus
}
#endif

#endif
