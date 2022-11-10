# `write_file.txt` Permissions

<!-- markdownlint-disable-file MD004 -->

## Question Text

Assume `write_file.txt` is opened like this:
`open("write_file.txt", O_WRONLY | O_CREAT)`.
What might cause it to have different permissions that `read_file.txt`?

## Question Answers

- an undefined behaviour in the kernel

- using the `O_WRONLY` flag

+ not passing a `mode` argument to `open()`, so a random set of permissions is used.

- a filesystem error.

## Feedaback

Quoting from [`open()`'s man page](https://man7.org/linux/man-pages/man2/open.2.html), regarding the `O_CREAT` flag:

> The mode argument must be supplied if O_CREAT or O_TMPFILE is
> specified in flags; if it is not supplied, some arbitrary
> bytes from the stack will be applied as the file mode.

The wording "arbitrary bytes from the stack" is a bit obsolete.
To demistify the quote above, let's consider that `open()` is a function call.
In fact, `libc` defines wrapper functions on top of all system calls and our code actually calls those wrappers, so our assumption is not far-fetched.

To call `open()` correctly, the coulde would look something like this:

```c
open("write_file.txt", O_WRONLY | O_CREAT, 0644).
```

`0644` is the octal representation of `rw-r--r--`.
The approximate Assembly code for this function call would look like this:

```asm
mov rdi, path_to_file   ; first argument: path

mov rsi, O_WRONLY
or rsi, O_CREAT         ; second argument: flags

mov rdx, 0644           ; third argument: mode

call open
```

When we don't specifty a `mode` argument, the `open()` function simply takes this value from `rdx` as it was before the function call.
This is an undefined behaviour because this register might have been modified either way by the program before calling `open()`.
