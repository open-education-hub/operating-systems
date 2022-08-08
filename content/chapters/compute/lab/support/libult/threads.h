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
 * threads.h
 * Interface to a barebones user level thread library.
 */

#ifndef THREADS_H
#define THREADS_H


/* Create a new thread. func is the function that will be run once the
   thread starts execution and arg is the argument for that
   function. On success, returns an id equal or greater to 0. On
   failure, errno is set and -1 is returned. */
int threads_create(void *(*start_routine) (void *), void *arg);


/* Stop execution of the thread calling this function. */
void threads_exit(void *result);


/* Wait for the thread with matching id to finish execution, that is,
   for it to call threads_exit. On success, the threads result is
   written into result and id is returned. If no completed thread with
   matching id exists, 0 is returned. On error, -1 is returned and
   errno is set. */
int threads_join(int id, void **result);


#endif
