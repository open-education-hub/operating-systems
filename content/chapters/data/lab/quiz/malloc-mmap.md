# Malloc `mmap()`

## Question Text

When does `malloc()` use `mmap()`?

## Question Answers

- When you want read-only memory

- When you want zeroed memory

+ When you allocate chunks of memory bigger than an internal threshold

- When the heap is full

## Feedback

`malloc` uses both `brk` and `mmap`, but preffers `mmap` for big chunks of memory (bigger than 128 KB).
These memroy blocks are unlikely to be reused so they are not placed on heap to avoid memory fragmentation.
