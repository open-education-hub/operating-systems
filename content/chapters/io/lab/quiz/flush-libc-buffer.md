# Flush Libc Buffer

## Question Text

Which of the following is a method of flushing libc's internal buffer?

## Question Answers

- print a `\0` character

+ print a `\n` character

- print a space character

- print a `\t` character

## Feedback

Newlines (`\n`) force `printf()` to dump the internal buffer associated with the `stdout` `FILE` `struct`.
If you place a `\n` character within one of the strings in `support/buffering/printf_buffering.c`, a `write()` syscall will be made right after it.
