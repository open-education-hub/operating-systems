## Common Functions

Enter the `support/common-functions/` folder and go through the practice items below.
If you get stuck, take a sneak peek at the solutions in the `solution/common-functions/` folder.

1. Update the `putchar()` function in `main_printf.c` to implement a buffered functionality of `printf()`.
   Characters passed via the `putchar()` call will be stored in a predefined static global buffer.
   The `write()` call will be invoked when a newline is encountered or when the buffer is full.
   This results in a reduced number of `write` system calls.
   Use `strace` to confirm the reduction of the number of `write` system calls.

1. Update the `main_printf.c` file to also feature a `flush()` function that forces the flushing of the static global buffer and a `write` system call.
   Make calls to `printf()` and `flush()` to validate the implementation.
   Use `strace` to inspect the `write` system calls invoked by `printf()` and `flush()`.
