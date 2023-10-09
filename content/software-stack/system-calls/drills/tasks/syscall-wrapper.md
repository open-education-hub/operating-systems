## System Call Wrappers

Enter the `support/syscall-wrapper/` folder and go through the practice items below.
If you get stuck, take a sneak peek at the solutions in the `solution/syscall-wrapper/` folder.

1. Update the files in the `syscall-wrapper/` folder to make the `getpid` system call available as a wrapper.
   Create a function with the signature `unsigned int itoa(int n, char *a)` that converts an integer to a string.
   It returns the number of digits in the string.
   For example, it will convert the number `1234` to the string `"1234"` string (`NULL`-terminated, 5 bytes long);
   the return value is `4` (the number of digits of the `"1234"` string).

   Then make the call to `getpid`;
   it gets no arguments and returns an integer (the PID - *process ID* of the current process).
