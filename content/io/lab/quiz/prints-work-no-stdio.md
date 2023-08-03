# Prints Working after Closing `stdio`

## Question Text

Why does `support/redirect/redirect.c`, still print messages to the console after closing file descriptor 1 (`stdout`)?

## Question Answers

+ because `wait_for_input()` calls `fprintf(stderr, ...)`, which prints to `stderr` (file descriptor 2)

- because the default file descriptors cannot be "truly" closed

- because the other two default file descriptors are still linked to the console

- because the `wait_for_input()` function started printed before closing the `stdout` file descriptor

## Feedback

If you look at `wait_for_input()` closely, you'll notice it calls `fprintf(stderr, ...)`.
`stderr` is liked to file descriptor 2, which is left unchanged so we can still write data to it.
