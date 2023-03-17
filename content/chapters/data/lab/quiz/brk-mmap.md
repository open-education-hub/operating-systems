# `brk()` and `mmap()`

## Question Text

Is `mmap()` better than `brk()`?

## Question Answers

- `brk()` is outdated, you should always use `mmap()`

- `mmap()` is only used for static zones of a process: `.text`, `.rodata`, `.data`, `.bss`

- `brk()` is better than `mmap()` as it allows small allocations

- Depends on the use case

## Feedback

`mmap()` is used to allocate big chunks of memory, map files into memory and share memory.

`brk()` changes the end of heap to allocate/deallocate memory.
It is less flexible than `mmap()`, but allocates memory in a single zone, making it easier to manage.
