# Syscall Used by `fopen()`

<!-- markdownlint-disable-file MD004 -->

## Question Text

Use `strace` to determine the syscall called by `fopen()` to access the file.
Which one is it?

## Question Answers

- `read()`

+ `openat()`

- `write()`

- `fstat()`

## Feedaback

```console
student@os:~/.../lab/support/simple-file-handling$ strace ./file_operations
[...]
openat(AT_FDCWD, "file.txt", O_RDONLY)  = 3
fstat(3, {st_mode=S_IFREG|0664, st_size=11, ...}) = 0
read(3, "C was here!", 4096)            = 11
[...]
```

So `fopen()`'s (main) underlying syscall is `openat()`.
