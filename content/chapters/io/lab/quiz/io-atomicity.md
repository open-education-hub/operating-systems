# IO Atomicity

<!-- markdownlint-disable-file MD004 -->

## Question Text

Suppose you are in a multithreaded environment.
What is the value of `fd` in the following snippet?

```C
close(0);

int fd = open("aa.txt", O_RDWR);
```

## Question Answers

+ We do not know for sure

- 0

- stdin

## Feedback

It is enough for another thread to call `open()` and the assumption that `fd` will be `0` will crumble.
The solution to this problem is not adding a mutex, but rather using `dup()` syscall that guarantees that the sequence is performed atomically.
