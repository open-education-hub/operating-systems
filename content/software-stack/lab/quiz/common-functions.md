# Common Functions

## printf() System Call

### Question Text

What system call does the `printf()` function invoke?

### Question Answers

- `read`

+ `write`

- `exec`

- `exit`

### Feedback

`printf()` invokes the `write` system call to print messages to standard output.

## strcpy() System Call

### Question Text

What system call does the `strcpy()` function invoke?

### Question Answers

- `cpy`

- `touch`

- `memcpy`

+ no system call

### Feedback

`strcpy()` doesn't invoke system calls, because it doesn't require any feature that is only provided by the operating system

## printf() vs write

### Question Text

What are features provided by `printf()` when compared to `write`? (choose 2 answers)

### Question Answers

+ buffering

- outputs to standard output

- may write to file

+ does output formatting

- can work with binary data

### Feedback

`printf()` can do buffering to reduce the number of system calls.
Also, `printf()`, as it name suggests (the `f` suffix), does output formatting.
