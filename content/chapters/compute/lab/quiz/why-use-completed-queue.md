# The Need for a COMPLETED Queue

## Question Text

Why does the scheduler need a COMPLETED queue and not simply terminate one thread once its function finishes?

## Question Answers

- The COMPLETED queue is an implementation preference.
The scheduler can expose the same functions without it

- Because the OS's scheduler may kill the main kernel-level thread unless we keep the user-level thread in a queue

+ The COMPLETED queue is needed to save the value returned by the thread so that it can later be retrieved by `threads_join()`.

## Feedback

Take a look at the `handle_thread_start()` function.
It is used by `threads_create()` to start executing the given function.
This is a wrapper that calls the function associated with the thread (`this->start_routine`), saves its result and then calls `threads_exit()`
to store this result in the COMPLETED queue.
