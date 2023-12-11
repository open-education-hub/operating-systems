# `write_file.txt` Permissions

<!-- markdownlint-disable-file MD004 -->

## Question Text

Assume `write_file.txt` is opened like this:
`open("write_file.txt", O_WRONLY | O_CREAT)`.
What might cause it to have different permissions than `read_file.txt`?

## Question Answers

- an undefined behaviour in the kernel

- using the `O_WRONLY` flag

+ not passing a `mode` argument to `open()`, so a random set of permissions is used.

- a filesystem error.

## Feedback

Quoting from [`open()`'s man page](https://man7.org/linux/man-pages/man2/open.2.html), regarding the `O_CREAT` flag:

> The mode argument must be supplied if O_CREAT or O_TMPFILE is
> specified in flags; if it is not supplied, some arbitrary
> bytes from the stack will be applied as the file mode.

The wording "arbitrary bytes from the stack" is a bit obsolete on x86-64 systems.

The x86 calling convention specifies that arguments are pushed on the stack, and because the `open()` wrapper is a variadic function in `libc` this would result in arbitrary bytes being read from the stack when `mode` is required but not provided.

On the other hand, the x86-64 calling convention places arguments in registers.

A correct `open()` call would look something like this:

```c
open("write_file.txt", O_WRONLY | O_CREAT, 0644).
```

`0644` is the octal representation of `rw-r--r--`.
The approximate x86-64 assembly code for this function call would look like this:

```asm
mov rdi, path_to_file   ; first argument: path

mov rsi, O_WRONLY
or rsi, O_CREAT         ; second argument: flags

mov rdx, 0644           ; third argument: mode

call open
```

When we don't specify a `mode` argument, the `open()` function simply takes this value from `rdx` as it was before the function call, resulting in undefined behavior.
