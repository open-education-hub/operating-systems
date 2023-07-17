# Multiple `open()` Calls

<!-- markdownlint-disable-file MD004 -->

## Question Text

How do multiple `open("file.txt", "O_RDWR")` update impact the file descriptor table?

## Question Answers

- Only the first call creates a new file descriptor

- `open()` fails if the file is already opened

- Each `open()` will have its diferrent file descriptor, but will referrence the same `open file struct`

+ Each `open()` will create a file descriptor

## Feedaback

`open()` crates a new `file struct` and a file descriptor that references it.
