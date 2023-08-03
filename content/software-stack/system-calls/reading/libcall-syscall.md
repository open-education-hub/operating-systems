# Library calls vs system calls

The standard C library has primarily two uses:

1. wrapping system calls into easier to use C-style library calls, such as `open()`, `write()`, `read()`
1. adding common functionality required for our program, such as string management (`strcpy`), memory management (`malloc()`) or formatted I/O (`printf()`)

The first use means a 1-to-1 mapping between library calls and system calls: one library call means one system call.
The second group doesn't have a standard mapping.
A library call could be mapped to no system calls, one system call, two or more system calls, or it may depend (a system call may or may not happen).

The `support/libcall-syscall/` folder stores the implementation of a simple program that makes different library calls.
Let's build the program and then trace the library calls (with `ltrace`) and the system calls (with `strace`):

```console
student@os:~/.../lab/support/libcall-syscall$ make
cc -Wall   -c -o call.o call.c
cc   call.o   -o call
cc -Wall   -c -o call2.o call2.c
cc   call2.o   -o call2

student@os:~/.../lab/support/libcall-syscall$ ltrace ./call
fopen("a.txt", "wt")                                                                                             = 0x556d57679260
strlen("Hello, world!\n")                                                                                        = 14
fwrite("Hello, world!\n", 1, 14, 0x556d57679260)                                                                 = 14
strlen("Bye, world!\n")                                                                                          = 12
fwrite("Bye, world!\n", 1, 12, 0x556d57679260)                                                                   = 12
fflush(0x556d57679260)                                                                                           = 0
+++ exited (status 0) +++

student@os:~/.../lab/support/libcall-syscall$ strace ./call
[...]
openat(AT_FDCWD, "a.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
fstat(3, {st_mode=S_IFREG|0664, st_size=0, ...}) = 0
write(3, "Hello, world!\nBye, world!\n", 26) = 26
exit_group(0)                           = ?
+++ exited with 0 +++
```

We have the following mappings:

* The `fopen()` library call invokes the `openat` and the `fstat` system calls.
* The `fwrite()` library call invokes no system calls.
* The `strlen()` library call invokes no system calls.
* The `fflush()` library call invokes the `write` system call.

This all seems to make sense.
The main reason for `fwrite()` not making any system calls is the use of a standard C library buffer.
Calls the `fwrite()` end up writing to that buffer to reduce the number of system calls.
Actual system calls are made either when the standard C library buffer is full or when an `fflush()` library call is made.

Note that on some systems, `ltrace` **does not work** as expected, due to **now binding**.
To avoid this behaviour, you can force the **lazy binding** (based on which `ltrace` is constructed to work).
An example can be found in `support/libcall-syscall/Makefile`, however for system binaries, such as `ls` or `pwd`, the only alternative is to add the `-x "*"` argument to force the command to trace all symbols in the symbol table:

```console
student@os:~$ ltrace -x "*" ls
```

You can always choose what library functions `ltrace` is investigating, by replacing the wildcard with their name:

```console
student@os:~$ ltrace -x "malloc" -x "free" ls
malloc@libc.so.6(5)                                                    = 0x55c42b2b8910
free@libc.so.6(0x55c42b2b8910)                                         = <void>
malloc@libc.so.6(120)                                                  = 0x55c42b2b8480
malloc@libc.so.6(12)                                                   = 0x55c42b2b8910
malloc@libc.so.6(776)                                                  = 0x55c42b2b8930
malloc@libc.so.6(112)                                                  = 0x55c42b2b8c40
malloc@libc.so.6(1336)                                                 = 0x55c42b2b8cc0
malloc@libc.so.6(216)                                                  = 0x55c42b2b9200
malloc@libc.so.6(432)                                                  = 0x55c42b2b92e0
malloc@libc.so.6(104)                                                  = 0x55c42b2b94a0
malloc@libc.so.6(88)                                                   = 0x55c42b2b9510
malloc@libc.so.6(120)                                                  = 0x55c42b2b9570
[...]
```

If you would like to know more about **lazy binding**, **now binding** or **PLT** entries, check out [this blog post](https://maskray.me/blog/2021-09-19-all-about-procedure-linkage-table).

## Practice

Enter the `support/libcall-syscall/` folder and go through the practice items below.

1. Check library calls and system calls for the `call2.c` file.
   Use `ltrace` and `strace`.

   Find explanations for the calls being made and the library call to system call mapping.

[Quiz](../quiz/libcall-syscall.md)
