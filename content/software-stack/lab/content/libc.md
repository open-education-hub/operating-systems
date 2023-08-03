# Libraries and libc

Once we have common functions implemented, we can reuse them at any time.
The main unit for software reusability is the **library**.
In short, a library is a common machine code that can be linked against different other software components.
Each time we want to use the `printf()` function or the `strlen()` function, we don't need to reimplement them.
We also don't need to use existing source code files, rebuild them and reuse them.
We (re)use existing machine code in libraries.

A library is a collection of object files that export given data structures and functions to be used by other programs.
We create a program, we compile and then we link it against the library for all the features it provides.

The most important library in modern operating systems is the **standard C library**, also called **libc**.
This is the library providing system call wrappers and basic functionality for input-output, string management, memory management.
By default, a program is always linked with the standard C library.
In the examples above, we've explicitly disabled the use of the standard C library with the help of the `-nostdlib` linker option.

By using the standard C library, it's much easier to create new programs.
You call existing functionality in the library and implement only features particular to your program.

The `support/libc/` folder stores the implementation of programs using the standard C library: `hello.c`, `main_string.c` and `main_printf.c`.
These programs are almost identical to those used in the past sections:

* `hello.c` is similar to the programs in `solution/basic-syscall/` and `solution/syscall-wrapper/`
* `main_string.c` and `main_printf.c` are similar to the programs in `solution/common-functions/`

Let's build and run them:

```console
student@os:~/.../lab/support/libc$ ls
hello  hello.c  hello.o  main_printf  main_printf.c  main_printf.o  main_string  main_string.c  main_string.o  Makefile

student@os:~/.../lab/support/libc$ make clean
rm -f hello hello.o
rm -f main_printf main_printf.o
rm -f main_string main_string.o

student@os:~/.../lab/support/libc$ ls
hello.c  main_printf.c  main_string.c  Makefile

student@os:~/.../lab/support/libc$ make
cc -Wall   -c -o hello.o hello.c
cc -static  hello.o   -o hello
cc -Wall   -c -o main_printf.o main_printf.c
cc -static  main_printf.o   -o main_printf
cc -Wall   -c -o main_string.o main_string.c
cc -static  main_string.o   -o main_string

student@os:~/.../lab/support/libc$ ls
hello  hello.c  hello.o  main_printf  main_printf.c  main_printf.o  main_string  main_string.c  main_string.o  Makefile

student@os:~/.../lab/support/libc$ ./hello
Hello, world!
Bye, world!
aaa
aaa
^C

student@os:~/.../lab/support/libc$ ./main_string
Destination string is: warhammer40k

student@os:~/.../lab/support/libc$ ./main_printf
[before] src is at 0x492308, len is 12, content: "warhammer40k"
[before] dest is at 0x6bb340, len is 0, content: ""
copying src to dest
[after] src is at 0x492308, len is 12, content: "warhammer40k"
[after] dest is at 0x6bb340, len is 12, content: "warhammer40k"
abc
```

The behavior / output is similar to the ones in the previous sections:

```console
student@os:~/.../lab/support/libc$ ../../solution/basic-syscall/hello-nasm
Hello, world!
Bye, world!
aaa
aaa
^C

student@os:~/.../lab/support/libc$ ../../solution/common-functions/main_string
Destination string is: warhammer40k

student@os:~/.../lab/support/libc$ ../../solution/common-functions/main_printf
[before] src is at 0000000000402680, len is 12, content: "warhammer40k"
[before] dest is at 0000000000604000, len is 0, content: ""
copying src to dest
[after] src is at 0000000000402680, len is 12, content: "warhammer40k"
[after] dest is at 0000000000604000, len is 12, content: "warhammer40k"
abc
```

We can inspect the system calls made to check the similarities.
For example, for the `main_printf` program we get the outputs:

```console
student@os:~/.../lab/support/libc$ strace ./main_printf
execve("./main_printf", ["./main_printf"], 0x7fff7b38c240 /* 66 vars */) = 0
brk(NULL)                               = 0x15af000
brk(0x15b01c0)                          = 0x15b01c0
arch_prctl(ARCH_SET_FS, 0x15af880)      = 0
uname({sysname="Linux", nodename="[...]", ...}) = 0
readlink("/proc/self/exe", "[...]/operating"..., 4096) = 105
brk(0x15d11c0)                          = 0x15d11c0
brk(0x15d2000)                          = 0x15d2000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 18), ...}) = 0
write(1, "[before] src is at 0x492308, len"..., 64[before] src is at 0x492308, len is 12, content: "warhammer40k"
) = 64
write(1, "[before] dest is at 0x6bb340, le"..., 52[before] dest is at 0x6bb340, len is 0, content: ""
) = 52
write(1, "copying src to dest\n", 20copying src to dest
)   = 20
write(1, "[after] src is at 0x492308, len "..., 63[after] src is at 0x492308, len is 12, content: "warhammer40k"
) = 63
write(1, "[after] dest is at 0x6bb340, len"..., 64[after] dest is at 0x6bb340, len is 12, content: "warhammer40k"
) = 64
write(1, "ab", 2ab)                       = 2
write(1, "c\n", 2c
)                      = 2
exit_group(0)                           = ?
+++ exited with 0 +++

student@os:~/.../lab/support/libc$ strace ../../solution/common-functions/main_printf
execve("../../solution/common-functions/main_printf", ["../../solution/common-functions/"...], 0x7ffe204eec00 /* 66 vars */) = 0
write(1, "[before] src is at 0000000000402"..., 72[before] src is at 0000000000402680, len is 12, content: "warhammer40k"
) = 72
write(1, "[before] dest is at 000000000060"..., 60[before] dest is at 0000000000604000, len is 0, content: ""
) = 60
write(1, "copying src to dest\n", 20copying src to dest
)   = 20
write(1, "[after] src is at 00000000004026"..., 71[after] src is at 0000000000402680, len is 12, content: "warhammer40k"
) = 71
write(1, "[after] dest is at 0000000000604"..., 72[after] dest is at 0000000000604000, len is 12, content: "warhammer40k"
) = 72
write(1, "ab", 2ab)                       = 2
write(1, "c\n", 2c
)                      = 2
exit(0)                                 = ?
+++ exited with 0 +++
```

The output is similar, with differences at the beginning and the end of the system call trace.
In the case of the libc-built program, a series of additional system calls (`brk`, `arch_prctl`, `uname` etc.) are made.
Also, there is an implicit call to `exit_group` instead of an explicit one to `exit` in the non-libc case.
These are initialization and cleanup routines that are implicitly added when using the standard C library.
They are generally used for setting and cleaning up the stack, environment variables and other pieces of information required by the program or the standard C library itself.

We could argue that the initialization steps incur overhead, and that's a downside of using the standard C library.
However, these initialization steps are required for almost all programs.
And, given that almost all programs make use of the basic features of the standard C library, libc is almost always used.
We can say the above were exceptions to the rule, where we didn't make use of the standard C library.

Summarizing, the advantages and disadvantages of using the standard C library are:

* (+) easier development: do calls to existing functions already implemented in the standard C library;
  default build and link flags
* (+) portability: if the system provides a standard C library, one calls the library functions that will then interact with the lower-layer API
* (+) implicit initialization and cleanup: no need for you do explicitly create them
* (-) usually larger in size (static) executables
* (-) a level of overhead as the standard C library wraps system calls
* (-) potential security issues: a larger set of (potentially vulnerable) functions are presented by the standard C library

## Practice

Enter the `support/libc/` folder and go through the practice items below.

1. Use `malloc()` and `free()` functions in the `memory.c` program.
   Make your own use of the allocated memory.

   It's very easy to use memory management functions with the libc.
   The alternative (without the libc) would be more cumbersome.

   Use different values for `malloc()`, i.e. the allocation size.
   Use `strace` to check the system calls invoked by `malloc()` and `free()`.
   You'll see that, depending on the size, the `brk` or `mmap` / `munmap` system calls are invoked.
   And for certain calls to `malloc()` / `free()` no syscall is happening.
   You'll find more about them in the [Data chapter](../../../data/lab).

1. Create your own C program with calls to the standard C library in `vendetta.c`.
   Be as creative as you can about the types of functions being made.

[Quiz](../quiz/libc.md)
