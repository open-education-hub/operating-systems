# System Call Wrappers

Enter the `syscall-wrapper/support/` folder and go through the practice items below.

1. Update the files in the `syscall-wrapper/` folder to make `read` system call available as a wrapper.
   Make a call to the `read` system call to read data from standard input in a buffer.
   Then call `write()` to print data from that buffer.

   Note that the `read` system call returns the number of bytes `read`.
   Use that as the argument to the subsequent `write` call that prints read data.

   We can see that it's easier to have wrapper calls and write most of the code in C than in assembly language.

   [Quiz](../drills/questions/syscall-wrapper.md)

1. Update the files in the `syscall-wrapper/` folder to make the `getpid` system call available as a wrapper.
   Create a function with the signature `unsigned int itoa(int n, char *a)` that converts an integer to a string.
   It returns the number of digits in the string.
   For example, it will convert the number `1234` to the string `"1234"` string (`NULL`-terminated, 5 bytes long);
   the return value is `4` (the number of digits of the `"1234"` string).

   Then make the call to `getpid`;
   it gets no arguments and returns an integer (the PID - *process ID- of the current process).

If you're having difficulties solving this exercise, go through [this](../../../reading/syscall-wrapper.md) reading material.
