# Fiber Strace

## Question Text

How many `clone()` system calls are performed when creating a fiber?

## Question Answers

+ none

- one for each fiber

- one for every 2 fibers

- 2 for each fiber

## Feedback

Being **user-level threads**, the fibers aren't created by the operating system.
The only system calls that you see used are `mmap()` and `munmap()`, used to create each fiber's stack.
