# High-Level Languages

Enter the `high-level-lang/support/` folder and go through the practice items below.

1. Use `make` to create the `hello` executable from the `hello.go` file (a Go "Hello, World!"-printing program).
   Use `ltrace` and `strace` to compute the number of library calls and system calls.
   Use `perf` to measure the running time.

   Compare the values with those from the "Hello, World!"-printing programs in C and Python.

1. Create a "Hello, World!"-printing program in a programming language of your choice (other than C, Python and Go).
   Find the values above (library calls, system calls and running time).

   [Quiz](../drills/questions/high-level-lang.md)

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

If you're having difficulties solving this exercise, go through [this](../../../reading/high-level-lang.md) reading material.
