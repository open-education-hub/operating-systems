# String Buffer Overflow

## Question Text

Why does the buffer overflow occur?

## Question Answers

- the initial string, declared in `main()`, does not contain a terminating null byte.

- the buffer is not large enough to store the copied bytes.

- `memcpy()` skips the copying of terminating null bytes.

+ `memcpy()` copies 4 bytes, whereas the size of the string, including the terminating null byte, is 5.

## Feedback

The string "soso" has length equal to 4, however, 5 bytes are actually used to store it, including the terminating null byte.
Even though the buffer declared in `fun()` is not large enough to store the 5 bytes, the underlying issue is that we copying just 4 bytes, thus skipping the null byte.
