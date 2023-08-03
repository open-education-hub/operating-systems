## Libraries and libc

Enter the `support/libc/` folder and go through the practice items below.
If you get stuck, take a sneak peek at the solutions in the `solution/libc/` folder.

1. Inside the `vendetta.c` file make a call `open("a.txt", O_RDWR | O_CREAT, 0644)` to open / create the `a.txt` file.
   Make sure you include all required headers.
   Check the system call being made.

   Make an `fopen()` with the proper arguments that gets as close as possible to the `open()` call, i.e. the system call arguments are as close as possible.

1. Inside the `vendetta.c` file make a call to `sin()` function (for sine).
   Compute `sin(0)` and `sin(PI/2)`.
