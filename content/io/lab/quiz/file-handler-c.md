# File handler in C

<!-- markdownlint-disable-file MD004 -->

## Question Text

What is the type of the file handler in the C code located in `support/simple-file-operations/file_operations.c`?

## Question Answers

- `File`

+ `FILE *`

- `FILE`

- `void *`

- `struct file`

## Feedaback

The file is opened using either of the following lines:

```c
f = fopen(file_name, "r");

f = fopen(file_name, "w");
```

The type of `f` is `FILE *`:
`FILE *f`.
