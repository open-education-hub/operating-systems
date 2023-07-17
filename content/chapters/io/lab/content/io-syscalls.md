# I/O Syscalls

Each operation for the `FILE` handler is implemented on top of a syscall:

|    libc      |  syscall  |
| :--------:   | :-------: |
| `fopen()`    | `open()`  |
| `fread()`    | `read()`  |
| `fwrite()`   | `write()` |
| `fseek()`    | `lseek()` |
| `fclose()`   | `close()` |

## `open()` and `close()`

```console
int open(const char *pathname, int flags, mode_t mode);
```

The `open()` system call opens the file specified by `pathname` with the given `flags` (permissions).

| `fopen()` mode |          `open()` flag          |
| :------------: | :-----------------------------: |
|     `"r"`      |           `O_RDONLY`            |
|     `"w"`      | `O_WRONLY │ O_CREAT │ O_TRUNC`  |
|     `"a"`      | `O_WRONLY │ O_CREAT │ O_APPEND` |
|     `"r+"`     |            `O_RDWR`             |
|     `"w+"`     |  `O_RDWR │ O_CREAT │ O_TRUNC`   |
|     `"a+"`     |  `O_RDWR │ O_CREAT │ O_APPEND`  |

[Answer this quiz](../quiz/write-file-permissions.md)

If the specified file does not exist, it may optionally (if `O_CREAT` is specified in `flags`) be created by `open()`.
**It is mandatory that we pass a `mode` argument to `open()` when using the `O_CREAT` flag.**
This is the only case when `mode` parameter is required.

```console
int close(int fd);
```

`close()` closes a file descriptor, so that it no longer refers to any file and may be reused.
It also decrements the referrence counter inside the open file struct and frees the structure when there are no referrences to it.

[Answer this quiz](../quiz/multiple-open-calls.md)

## `read()` and `write()`

```console
ssize_t read(int fd, void buf[.count], size_t count);
```

`read()` attempts to read **up to** `count` bytes from file descriptor `fd` into the buffer starting at `buf`.
On success, `read()` returns the number of bytes read, which **might be less** than `count`.
This is not an error and might appear when not enough bytes are available to read or the operation was interrupted by a signal.

```console
ssize_t write(int fd, const void buf[.count], size_t count);
```

`write()` writes **up to** `count` bytes from the buffer starting at `buf` to the file referred to by the file descriptor `fd`.
On success, `write` returns the number of bytes written, which **might be less** than `count`.
This is not an error and might appear when there is not enough free space on the disk or the operation was interrupted by a signal.

**It is mandatory that we always use `read()` and `write()` inside `while` loops.**
Higher-level functions like `fread()` and `fwrite()` also use `while` loops when calling `read()` and `write()` respectively.

### Practice

Open `support/io-syscalls/open-read-write.c`.
Implement `write_to_file()` similarly to `read_from_file()`.
