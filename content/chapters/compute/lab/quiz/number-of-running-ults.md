# Number of RUNNING User-Level Threads

## Question Text

How many threads can be RUNNING simultaneously if we only create them using the API exposed by `libult.so`?

## Question Answers

- Equal to the number of cores on the CPU

+ 1

- None

- 2: the main thread and another one for the created threads

## Feedback

Only kernel-level threads can run in parallel.
Since all `libult.so` threads are user-level threads, they run within the same kernel-level thread, so only one of them can run at any time.
