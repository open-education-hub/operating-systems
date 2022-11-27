# libs

## Static Executables

### Question Text

Which of the following tools has no influence over statically-linked executables? (choose 2 answers)

### Question Answers

+ `ltrace`

- `strace`

- `nm`

+ `ldd`

- `rm`

### Feedback

`ltrace` and `ldd` are used to capture connections to dynamic libraries.
They have no effect on statically-linked executables.

## Dynamic Libraries

### Question Text

Which of the following is a dynamic library?

### Question Answers

- `libc.a`

+ `libc.so`

- `libc.exe`

- `libc.c`

### Feedback

The `.so` (_shared object_) extension is used for dynamic libraries in Linux.
