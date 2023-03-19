# Malloc `brk()`

## Question Text

When does `malloc()` use `brk()`?

## Question Answers

- `brk()` is outdated, `malloc()` always uses `mmap()`

+ When it allocates a small chunk of memory

- When it allocates an array

- When it's working with dynamic libraries

## Feedback

`malloc()` uses both `brk()` and `mmap()`, but preffers `brk()` for small chunks of memory to keep granular allocations in a contiguous area.
This way, `free()` does not necessarily return the memory to the OS as it might only mark the zone as "free" within `libc`'s allocator and reuse it for later allocations.
