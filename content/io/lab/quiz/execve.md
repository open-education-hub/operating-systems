# Effect of `execve()` Syscall

## Question Text

What is the effect of the `execve()` syscall?

## Question Answers

- it spawns a new process as the child of the current one

- it executes a given shell command

+ it replaces the VAS of the current process with that of the file given as argument

- it spawns a new shell and executes the given command

## Feedback

The [`man` page](https://man7.org/linux/man-pages/man2/execve.2.html) says it all:

> execve() executes the program referred to by pathname.  This
> causes the program that is currently being run by the calling
> process to be replaced with a new program, with newly initialized
> stack, heap, and (initialized and uninitialized) data segments.

Simply put, we can say that `execve()` replaces the VAS of the current process with that of the program given as argument.
