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

/*
 * queue.h
 * Defines a queue to mange TCB elements.
 */

#ifndef QUEUE_H
#define QUEUE_H


#include "tcb.h"

#include <unistd.h>


typedef struct queue QUEUE;


/* Create a new initialized QUEUE on the heap. Returns a pointer to
   the new block or NULL on error. */
QUEUE *queue_new(void);


/* Destroy queue, freeing all associated memory with it. It also frees
   all memory of the elements inside the queue. */
void queue_destroy(QUEUE *queue);


/* Return the number of items in queue. */
size_t queue_size(const QUEUE *queue);


/* Add elem to the end of queue. Returns 0 on succes and non-zero on
   failure.*/
int queue_enqueue(QUEUE *queue, TCB *elem);


/* Remove the first item from the queue and return it. The caller will
   have to free the reuturned element. Returns NULL if the queue is
   empty. */
TCB *queue_dequeue(QUEUE *queue);


/* Remove element with matching id from the queue. Returns the removed
   element or NULL if no such element exists. */
TCB *queue_remove_id(QUEUE *queue, int id);


#endif
