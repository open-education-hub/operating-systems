# Common Functions

By using wrapper calls, we are able to write our programs in C.
However, we still need to implement common functions for string management, working with I/O, working with memory.

The simple attempt is to implement these functions (`printf()` or `strcpy()` or `malloc()`) once in a C source code file and then reuse them when needed.
This saves us time (we don't have to reimplement) and allows us to constantly improve one implementation constantly;
there will only be one implementation that we update to increase its safety, efficiency or performance.

The `support/common-functions/` folder stores the implementation of string management functions, in `string.c` and `string.h` and of printing functions in `printf.c` and `printf.h`.
The `printf` implementation is [this one](https://github.com/mpaland/printf).

There are two programs: `main_string.c` showcases string management functions, `main_printf.c` showcases the `printf()` function.

`main_string.c` depends on the `string.h` and `string.c` files that implement the `strlen()` and `strcpy()` functions.
We print messages using the `write()` system call wrapper implemented in `syscall.s`

Let's build and run the program:

```console
student@os:~/.../lab/support/common-functions$ make main_string
gcc -fno-stack-protector   -c -o main_string.o main_string.c
gcc -fno-stack-protector   -c -o string.o string.c
nasm -f elf64 -o syscall.o syscall.s
gcc -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none  main_string.o string.o syscall.o   -o main_string

student@os:~/.../lab/support/common-functions$ ./main_string
Destination string is: warhammer40k

student@os:~/.../lab/support/common-functions$ strace ./main_string
execve("./main_string", ["./main_string"], 0x7ffd544d0a70 /* 63 vars */) = 0
write(1, "Destination string is: ", 23Destination string is: ) = 23
write(1, "warhammer40k\n", 13warhammer40k
)          = 13
exit(0)                                 = ?
+++ exited with 0 +++
```

When using `strace` we see that only the `write()` system call wrapper triggers a system call.
There are no system calls triggered by `strlen()` and `strcpy()` as can be seen in their implementation.

In addition, `main_printf.c` depends on the `printf.h` and `printf.c` files that implement the `printf()` function.
There is a requirement to implement the `_putchar()` function;
we implement it in the `main_printf.c` file using the `write()` syscall call wrapper.
The `main()` function `main_printf.c` file contains all the string and printing calls.
`printf()` offers a more powerful printing interface, allowing us to print addresses and integers.

Let's build and run the program:

```console
student@os:~/.../lab/support/common-functions$ make main_printf
gcc -fno-stack-protector   -c -o printf.o printf.c
gcc -nostdlib -no-pie -Wl,--entry=main -Wl,--build-id=none  main_printf.o printf.o string.o syscall.o   -o main_printf

student@os:~/.../lab/support/common-functions$ ./main_printf
[before] src is at 00000000004026A0, len is 12, content: "warhammer40k"
[before] dest is at 0000000000603000, len is 0, content: ""
copying src to dest
[after] src is at 00000000004026A0, len is 12, content: "warhammer40k"
[after] dest is at 0000000000603000, len is 12, content: "warhammer40k"

student@os:~/.../lab/support/common-functions$ strace ./main_printf
execve("./main_printf", ["./main_printf"], 0x7ffcaaa1d660 /* 63 vars */) = 0
write(1, "[", 1[)                        = 1
write(1, "b", 1b)                        = 1
write(1, "e", 1e)                        = 1
write(1, "f", 1f)                        = 1
write(1, "o", 1o)                        = 1
write(1, "r", 1r)                        = 1
write(1, "e", 1e)                        = 1
write(1, "]", 1])                        = 1
write(1, " ", 1 )                        = 1
write(1, "s", 1s)                        = 1
write(1, "r", 1r)                        = 1
[...]
```

We see that we have greater printing flexibility with the `printf()` function.
However, one downside of the current implementation is that it makes a system call for each character.
This is inefficient and could be improved by printing a whole string.

## Practice

Enter the `support/common-functions/` folder and go through the practice items below.

1. Update `string.c` and `string.h` to make available the `strcat()` function.
   Call that function in `main_string.c` and print the result.

1. Update the `main_printf.c` file to use the implementation of `sprintf()` to collect information to be printed inside a buffer.
   Call the `write()` function to print the information.
   The `printf()` function will no longer be called.
   This results in a single `write` system call.

Using previously implemented functions allows us to more efficiently write new programs.
These functions provide us with extensive features that we use in our programs.

[Quiz](../quiz/common-functions.md)
