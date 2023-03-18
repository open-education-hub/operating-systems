# Malloc `brk()`

## Question Text

When does `malloc()` use `brk()`?

## Question Answers

- `brk()` is outdated, you should always use `mmap()`

+ When you want a small chunk of memory

- When you allocate an array

- When you are working with dynamic libraries

## Feedback

`malloc` uses both `brk` and `mmap`, but preffers `brk` for small chunks of memory to keep granullar allocations in a contiguous area.
This way, `free` does not necessarily returns the memory to the OS as it might only mark the zone as "free" and reuse it for later allocations.
