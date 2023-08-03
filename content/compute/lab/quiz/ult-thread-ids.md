# ULT Thread IDs

## Question Text

Why do the thread IDs returned by `threads_create()` start from 2 and not 1?
Why is this necessary.

## Question Answers

- Because ID 1 is associated with the main thread.
This is an implementation detail and can be omitted.

+ Because ID 1 belongs to the main thread.
This is needed in order to associate a `ucontext_t` with the main thread as well, so the main thread can also be run.

- Because the underlying kernel thread is assigned ID 1.
This is mandatory in order for the OS's scheduler to run this thread.

- Because `libult.so` first creates a pool of threads from which it `threads_create()` retrieves the threads it returns.

## Feedback

The `threads_create()` function calls `init_first_context()`, which, in turn, calls `tcb_new()`, thus creating the first context associated with the main thread (the one calling `threads_create()` the first time).
Without this, the scheduler in `libult.so` wouldn't be able to run the main thread.
