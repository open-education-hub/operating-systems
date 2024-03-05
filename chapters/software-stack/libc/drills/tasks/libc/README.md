# Libraries and libc

Enter the `libc/support/` folder and go through the practice items below.

1. Use `malloc()` and `free()` functions in the `memory.c` program.
   Make your own use of the allocated memory.

   It's very easy to use memory management functions with the libc.
   The alternative (without the libc) would be more cumbersome.

   Use different values for `malloc()`, i.e. the allocation size.
   Use `strace` to check the system calls invoked by `malloc()` and `free()`.
   You'll see that, depending on the size, the `brk()` or `mmap()` / `munmap()` system calls are invoked.
   And for certain calls to `malloc()` / `free()` no syscall is happening.
   You'll find more about them in the [Data chapter](../../../data/lab).

1. Create your own C program with calls to the standard C library in `vendetta.c`.
   Be as creative as you can about the types of functions being made.

   [Quiz](../drills/questions/libc.md)

1. Inside the `vendetta.c` file make a call `open("a.txt", O_RDWR | O_CREAT, 0644)` to open / create the `a.txt` file.
   Make sure you include all required headers.
   Check the system call being made.

   Make an `fopen()` with the proper arguments that gets as close as possible to the `open()` call, i.e. the system call arguments are as close as possible.

1. Inside the `vendetta.c` file make a call to `sin()` function (for sine).
   Compute `sin(0)` and `sin(PI/2)`.

If you're having difficulties solving this exercise, go through [this](../../../reading/libc.md) reading material.
