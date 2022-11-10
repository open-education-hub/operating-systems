# `open()` equivalent of `fopen(..., "w")`

<!-- markdownlint-disable-file MD004 -->

## Question Text

Use `strace` on the code in `support/simple-file-operations/file_operations.c` to find the flags used by `openat()` when calling `fopen(file_name, "w")`.
First, try to make an educated guess and only then verify your answer by running `strace`.

## Question Answers

+ `O_WRONLY | O_CREAT | O_TRUNC`

- `O_WRONLY | O_CREAT`

- `O_WRONLY`

- `O_WRONLY | O_TRUNC`

## Feedback

```console
student@os:~/.../lab/support/simple-file-operations$ strace ./file_operations
[...]
openat(AT_FDCWD, "file.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
[...]
```
