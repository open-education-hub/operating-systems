# File Descriptors

## Reaching the File

You've most likely had to deal with files in the past.
To manipulate the file (read its contents, modify them, change its size etc.), each process must first get a **handler** to this file.
Think of this handler as an object by which the process can identify and refer to the file.

Now take a look at the code examples in `support/file-descriptors`.
Each of them reads the contents of `file.txt`, modifies them, and then reads the previously modified file again.
Use `make` to compile the C code, and `make java-file-operations` to compile the Java code.

Now run the programs repeatedly in whatever order you wish:

```console
student@os:~/.../lab/support/file-descriptors$ python3 file_operations.py
File contents are: OS Rullz!
Wrote new data to file
File contents are: Python was here!

student@os:~/.../lab/support/file-descriptors$ ./file_operations  # from the C code
File contents are: Python was here!
Wrote new data to file
File contents are: C was here!

student@os:~/.../lab/support/file-descriptors$ java FileOperations
File contents are: Python was here!
Wrote new data to file
File contents are: Java was here!
```

Note that each piece of code creates a variable, which is then used as a handler.

[Answer this quiz](../quiz/file-handler-c.md)

### Practice

Open `support/file-descriptors/file_operations.c`.
Change `write_file()` to append `"C was here!"` on a new line rather than replacing file content.
Print an empty line and then print a timestamp like `"Wed Jun 22 13:01:44 2022"`.

**HINT**: You can use [`localtime`](https://linux.die.net/man/3/localtime) and [`asctime`](https://linux.die.net/man/3/asctime) for the timestamp.

## File Descriptors

Behind the scenes, a handler is a structure built on top of an OS interface.
Let us use `strace` to find what system calls are used to open a file.

```console
student@OS:~/.../support/file-descriptors$ strace ./file_operations 2>&1 | grep file.txt
openat(AT_FDCWD, "file.txt", O_RDONLY)  = 3
openat(AT_FDCWD, "file.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
openat(AT_FDCWD, "file.txt", O_RDONLY)  = 3
```

So `fopen()`'s (main) underlying syscall is `openat()` but for simplicity we will use [`open()`](https://man7.org/linux/man-pages/man2/open.2.html), which is a wrapper over `openat()`.

`open()` allocates a new `open file struct` in the kernel space and creates a new entry in the **file descriptor table**, which is just a fancy name for an array of pointers to open files.
Its return value is the newly created index, which is called **file descriptor**.

[Answer this quiz](../quiz/o-trunc.md)

You've most likely used file descriptors before without knowing.
Remember the following concepts:

- `stdin` (standard input)
- `stdout` (standard output)
- `stderr` (standard error)

When you wanted to run a shell command and ignore its errors, you wrote something like:

```console
student@os:~$ ls 2> /dev/null
```

The command above uses `2> /dev/null` to **redirect** `stderr` to `/dev/null`.
It roughly translates to "make file descriptor `2` refer `/dev/null`".

This hints at the following corellation between I/O channels and file descriptors:

- `stdin` (standard input): 0
- `stdout` (standard output): 1
- `stderr` (standard error): 2

All processes start with these 3 default file descriptors.
This is in fact the reason why the calls to `openat()` from above return `3` - it is the first free index in the file descriptor table.

To illustrate all this information, look at the image below.
All data structures shown below are stored in the Kernel's memory area and are transparent to the user space and are supposed to be accessed only using [`file operations`](file-operations.md).

![File Descriptors](../media/file-descriptors.svg)

### Practice

Open `support/file-descriptors/print_errors.c`.
Use `open()` and `close()` to replicate the effect of `2>/dev/null` in code.

[Answer this quiz](../quiz/io-atomicity.md)

<!-- TODO move all source files to support/file-descriptors -->