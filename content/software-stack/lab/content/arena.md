# Arena

Go through the practice items below to hone your skills in working with layers of the software stack.

## System Calls

Enter the `support/basic-syscall/` folder and go through the practice items below.
If you get stuck, take a sneak peek at the solutions in the `solution/basic-syscall/` folder.

For debugging, use `strace` to trace the system calls from your program and make sure the arguments are set right.

1. Update the `hello.asm` and / or `hello.s` files to pause the execution of the program before the `exit` system call.

   You need to make the `sys_pause` system call, with no arguments.
   Find its ID [here](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/).

1. Update the `hello.asm` and / or `hello.s` files to read a message from standard input and print it to standard output.

   You'll need to define a buffer in the `data` or `bss` section.
   Use the `read` system call to read data in the buffer.
   The return value of `read` (placed in the `rax` register) is the number of bytes read.
   Use that value as the 3rd argument or `write`, i.e. the number of bytes printed.

   Find the ID of the `read` system call [here](https://x64.syscall.sh/).
   To find out more about its arguments, see [its man page](https://man7.org/linux/man-pages/man2/read.2.html).
   Standard input descriptor is `0`.

1. **Difficult**: Port the initial program to ARM on 64 bits (also called **aarch64**).

   Use the skeleton files in the `arm/` folder.
   Find information about the aarch64 system calls [here](https://arm64.syscall.sh/).

1. Create your own program, written in assembly, doing some system calls you want to learn more about.
   Some system calls you could try: `open`, `rename`, `mkdir`.
   Create a Makefile for that program.
   Run the resulting program with `strace` to see the actual system calls being made (and their arguments).

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

## Libraries and libc

Enter the `support/libc/` folder and go through the practice items below.
If you get stuck, take a sneak peek at the solutions in the `solution/libc/` folder.

1. Inside the `vendetta.c` file make a call `open("a.txt", O_RDWR | O_CREAT, 0644)` to open / create the `a.txt` file.
   Make sure you include all required headers.
   Check the system call being made.

   Make an `fopen()` with the proper arguments that gets as close as possible to the `open()` call, i.e. the system call arguments are as close as possible.

1. Inside the `vendetta.c` file make a call to `sin()` function (for sine).
   Compute `sin(0)` and `sin(PI/2)`.

## High-Level Languages

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

## App Investigation

Enter the `support/app-investigation/` folder and go through the practice items below.

1. Check to see whether there are statically-linked application executables in the system.
   The `file` command tells if the file passed as argument is a statically-linked executable.
   If you can't find one, install the `busybox-static` package.

1. Look into what [busybox](https://busybox.net/) is and explain why it's custom to have it as statically-linked executable.

1. Run `ldd`, `nm`, `strace`, `ltrace` on a statically-linked application executable.
   Explain the results.
