# File Handling

You've most likely had to deal with files in the past.
Go to `support/simple-file-operations` and run a most basic command:
`cat file.txt`:

```console
student@os:~/.../lab/support/simple-file-operations$ cat file.txt
OS Rullz!
```

But how does `cat` actually "reach" the file, then read its contents, then print them to standard output?
This is part of what we're going to learn.

## Reaching the File

To manipulate the file (read its contents, modify them, change its size etc.), each process must first get a **handler** to this file.
Think of this handler as an object by which the process can identify and refer to the file.

Now take a look at the code examples in `support/simple-file-operations`.
Each of them reads the contents of `file.txt`, modifies them, and then reads the previously modified file again.
Use `make` to compile the C code, and `make java-file-operations` to compile the Java code.

Now run the programs repeatedly in whatever order you wish:

```console
student@os:~/.../lab/support/simple-file-operations$ python3 file_operations.py
File contents are: OS Rullz!
Wrote new data to file
File contents are: Python was here!

student@os:~/.../lab/support/simple-file-operations$ ./file_operations  # from the C code
File contents are: Python was here!
Wrote new data to file
File contents are: C was here!

student@os:~/.../lab/support/simple-file-operations$ java FileOperations
File contents are: Python was here!
Wrote new data to file
File contents are: Java was here!
```

Note that each piece of code creates a variable, which is then used as a handler.

[Quiz](../quiz/file-handler-c.md)

### Limitations of High-level File Handlers

**Everything in Linux is a file.**
This statement says that the Linux OS treats every entry in a file system (regular file, directory, block device, char device, link, UNIX socket) as a file.
This is very convenient for creating a unified interface that deals with all these files.
We would like our file handlers to also be able to handle all types of files.

Let's try this.
Navigate to `support/simple-file-operations/directory_operations.c`.
Read the code.
It does something very simple:
it attempts to open the `dir` directory the same way `file_operations.c` tried to open `file.txt`.
Compile and run the code.

```console
student@os:~/.../lab/support/simple-file-operations$ ./directory_operations
18:18:11 FATAL directory_operations.c:14: fopen: Is a directory
```

The error message is crystal clear: we cannot use `fopen()` on directories.
So the `FILE` structure is unsuited for directories.
Therefore, this handler is not generic enough for a regular Linux filesystem.

To get to the directory, we need to use a lower-level function.
Let's take a look at the syscall used by `fopen()`.

[Quiz](../quiz/fopen-syscall.md)

We will use a simpler syscall, called [`open()`](https://man7.org/linux/man-pages/man2/open.2.html).
In fact, `open()` is a wrapper over `openat()`.
Navigate to `support/file-descriptors/directory_open.c`.
Inspect, compile and run the code.

```console
student@os:~/.../lab/support/file-descriptors$ ./open_directory
Directory file descriptor is: 3
```

We can now see that the `open()` syscall is capable of also handling directories, so it's closer to what we want.
Note that it is rather uncommon to use `open()` for directories.
Most of the time, [`opendir()`](https://man7.org/linux/man-pages/man3/opendir.3.html) is used instead.
But what does it return?
Find out in [the "File Descriptors" section](./file-descriptors.md).
