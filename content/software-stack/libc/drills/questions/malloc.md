# `malloc()`

## Question Text

What system calls are invoked by the `malloc()` library call for Linux libc? (choose 2 answers)

## Question Answers

+ `brk`

- `free`

- `dup`

+ `mmap`

- `copy`

## Feedback

Depending on the allocation size, `malloc()` invokes `brk` or `mmap`.
