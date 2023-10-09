# libc

## `malloc()`

### Question Text

What system calls are invoked by the `malloc()` library call for Linux libc? (choose 2 answers)

### Question Answers

+ `brk`

- `free`

- `dup`

+ `mmap`

- `copy`

### Feedback

Depending on the allocation size, `malloc()` invokes `brk` or `mmap`.

## Syscall Tool

### Question Text

Which of following is **not** and advantage of using libc for programs?

### Question Answers

- increased portability

+ reduced executable size

- richer set of features

- easier development

### Feedback

When using libc, because we add a new software component, the size of the resulting executable increases.
