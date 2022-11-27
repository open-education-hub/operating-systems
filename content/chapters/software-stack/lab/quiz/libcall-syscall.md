# Libcall with Syscall

## Question Text

Which of the following library calls will for sure invoke a system call?

## Question Answers

+ `fopen()`

- `fwrite()`

- `printf()`

- `strcpy()`

## Feedback

`fopen()` requires opening a file and access to the operating system (for filesystem access).
The others may not require a system call (`strcpy()`) or may use buffering to delay the invocation of a system call (`fwrite()`, `printf()`).
