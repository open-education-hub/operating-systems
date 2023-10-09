# High-Level Languages

Enter the `support/high-level-lang/` folder and go through the practice items below.
If you get stuck, take a sneak peek at the solutions in the `solution/high-level-lang/` folder.

1. Create programs in C, Python and Go that compute the N-th Fibonacci number.
   `N` is passed as a command-line argument.

   Use `ltrace` and `strace` to compute the number of library calls and system calls.
   Use `perf` to measure the running time.

   Compare the values of the three programs.

1. Create programs in C, Python and Go that copy a source file into a destination file.
   Both files are passed as the two command-line arguments for the program.
   Sample run:

   ```console
   student@so:~$ cp src dest
   ```

   Use `ltrace` and `strace` to compute the number of library calls and system calls.
   Use `perf` to measure the running time.
   Use source files of different sizes.
   Compare the outputs of these commands on the three programs.
