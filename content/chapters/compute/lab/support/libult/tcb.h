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
 * tcb.h
 * Defines the TCB (thread control block) data structure and functions
 * to work with it.
 */

#ifndef TCB_H
#define TCB_H


#include <stdbool.h>
#include <stdint.h>
#include <ucontext.h>


typedef struct {
	int id;
	ucontext_t context;
	bool has_dynamic_stack;
	void *(*start_routine) (void *);
	void *argument;
	void *return_value;
} TCB;


/* Create a new zeroed TCB on the heap. Returns a pointer to the new
   block or NULL on error. */
TCB *tcb_new(void);


/* Destroy block, freeing all associated memory with it */
void tcb_destroy(TCB *block);


#endif
