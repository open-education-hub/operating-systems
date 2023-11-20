/* SPDX-License-Identifier: BSD-3-Clause */

/*
 * Heavily inspired for Linux kernel code:
 * https://github.com/torvalds/linux/blob/master/include/linux/list.h
 */

#ifndef __OS_LIST_H__
#define __OS_LIST_H__	1

#include <stddef.h>

typedef struct os_list_node_t {
	struct os_list_node_t *prev, *next;
} os_list_node_t;

static inline void list_init(os_list_node_t *head)
{
	head->prev = head;
	head->next = head;
}

static inline void list_add(os_list_node_t *head, os_list_node_t *node)
{
	node->next = head->next;
	node->prev = head;
	head->next->prev = node;
	head->next = node;
}

static inline void list_add_tail(os_list_node_t *head, os_list_node_t *node)
{
	node->prev = head->prev;
	node->next = head;
	head->prev->next = node;
	head->prev = node;
}

static inline void list_del(os_list_node_t *node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	node->next = node;
	node->prev = node;
}

static inline int list_empty(os_list_node_t *head)
{
	return (head->next == head);
}

#define list_entry(ptr, type, member) ({			\
		void *tmp = (void *)(ptr);			\
		(type *) (tmp - offsetof(type, member));	\
	})

#define list_for_each(pos, head) \
		for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_safe(pos, tmp, head) \
	for (pos = (head)->next, tmp = pos->next; pos != (head); \
			pos = tmp, tmp = pos->next)

#endif
