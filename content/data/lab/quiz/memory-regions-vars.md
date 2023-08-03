# Variables in memory regions

## Question Text

In what memory regions are the `a`, `b`, `c`, `k` varaables from `support/memory-security/buff_leak.c` stored?

## Question Answers

- a - `.data`, b - `.bss`, c - `.stack`, k - `.heap`

+ a - `.data`, b - `.bss`, c - `.stack`, k - `.stack`

- a - `.data`, b - `.data`, c - `.stack`, k - `.heap`

- a - `.bss`, b - `.bss`, c - `.stack`, k - `.heap`

## Feedback

Global initialized variables go to `.data` (`a`).
Global uninitialized variables go to `.bss` (`b`).
Non-static local variables go on the`.stack` (`c`, `k`).
`malloc()`'ed memory goes on the`.heap`.
For `k`, the pointer is stored on the`.stack`, but the allocated memory, to which `k` points is stored on the`.heap`.
