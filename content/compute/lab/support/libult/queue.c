/**
* MIT License
* 
* Copyright (c) 2020  Andreas Schärtl and Contributors
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

/* Github link: https://github.com/kissen/threads */

#include "queue.h"


#include <errno.h>
#include <stdlib.h>


struct node {
	TCB *thread;
	struct node *next;
};


struct queue {
	struct node *head;
	size_t size;
};




QUEUE *queue_new(void)
{
	QUEUE *new;

	if ((new = calloc(1, sizeof(QUEUE))) == NULL) {
		return NULL;
	}

	return new;
}


void queue_destroy(QUEUE *queue)
{
	struct node *prev = NULL;
	struct node *cursor = queue->head;

	while (cursor != NULL) {
		prev = cursor;
		cursor = cursor->next;

		tcb_destroy(prev->thread);
		free(prev);
	}

	free(queue);
}


size_t queue_size(const QUEUE *queue)
{
	return queue->size;
}


int queue_enqueue(QUEUE *queue, TCB *elem)
{
	// Create the new node

	struct node *new;

	if ((new = malloc(sizeof(struct node))) == NULL) {
	return errno;
	}

	new->thread = elem;
	new->next = NULL;

	// Enqueue the new node

	if (queue->head == NULL) {
		queue->head = new;
	} else {
		struct node *parent = queue->head;
		while (parent->next != NULL) {
			parent = parent->next;
		}
		parent->next = new;
	}

	queue->size += 1;
	return 0;
}


TCB *queue_dequeue(QUEUE *queue)
{
	struct node *old_head = queue->head;
	if (old_head == NULL || queue->size == 0) {
		return NULL;
	}
	queue->head = queue->head->next;
	queue->size -= 1;

	TCB *retval = old_head->thread;
	free(old_head);

	return retval;
}


TCB *queue_remove_id(QUEUE *queue, int id)
{
	if (queue->head == NULL) {
		return NULL;
	}

	struct node *prev = NULL;
	struct node *cur = queue->head;

	while (cur != NULL) {
		if (cur->thread->id == id) {
			if (prev == NULL) {
				queue->head = cur->next;
			} else {
				prev->next = cur->next;
			}

			TCB *retval = cur->thread;
			free(cur);
			return retval;
		}

		prev = cur;
		cur = cur->next;
	}

	return NULL;
}
