# Malloc `mmap()`

## Question Text

When does `malloc()` use `mmap()`?

## Question Answers

- When it allocates read-only memory

- When it allocates zeroed memory

+ When it allocates chunks of memory bigger than an internal threshold

- When the heap is full

## Feedback

`malloc` uses both `brk()` and `mmap()`, but prefers `mmap()` for big chunks of memory (by default larger than 128 KB).
This value can be altered using [`mallopt()`](https://linux.die.net/man/3/mallopt) with the `param` argument set to `M_MMAP_THRESHOLD`.
These memroy blocks are unlikely to be reused so they are not placed on heap to avoid memory fragmentation.
