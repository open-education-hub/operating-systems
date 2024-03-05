# System Call Wrappers

The `syscall-wrapper/support/` folder stores the implementation of a simple program written in C (`main.c`) that calls the `write()` and `exit()` functions.
The functions are defined in `syscall.asm` as wrappers around corresponding system calls.
Each function invokes the corresponding system call using the specific system call ID and the arguments provided for the function call.

The implementation of the two wrapper functions in `syscall.asm` is very simple, as the function arguments are passed in the same registers required by the system call.
This is because of the overlap of the first three registers for the [x86_64 Linux function calling convention](https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI) and the [x86_64 Linux system call convention](https://x64.syscall.sh/).

`syscall.h` contains the declaration of the two functions and is included in `main.c`.
This way, C programs can be written that make function calls that end up making system calls.

Let's build, run and trace system calls for the program:

```console
student@os:~/.../tasks/syscall-wrapper/support$ ls
main.c  Makefile  syscall.h  syscall.s

student@os:~/.../tasks/syscall-wrapper/support$ make
gcc -c -o main.o main.c
nasm -f elf64 -o syscall.o syscall.s
cc -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none  main.o syscall.o   -o main

student@os:~/.../tasks/syscall-wrapper/support$ ls
main  main.c  main.o  Makefile  syscall.h  syscall.o  syscall.s

student@os:~/.../software-stack/lab/syscall-wrapper$ ./main
Hello, world!

student@os:~/.../tasks/syscall-wrapper/support$ strace ./main
execve("./main", ["./main"], 0x7ffee60fb590 /- 63 vars */) = 0
write(1, "Hello, world!\n", 14Hello, world!
)         = 14
exit(0)                                 = ?
+++ exited with 0 +++
```

The trace is similar to the previous example, showing the `write()` and `exit()` system calls.

By creating system call wrappers as C functions, we are now relieved of the burden of writing assembly language code.
Of course, there has to be an initial implementation of wrapper functions written in assembly language;
but, after that, we can use C only.
