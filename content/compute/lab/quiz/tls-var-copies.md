# TLS `var` Copies

## Question Text

How many copies of the `var` variable from `support/race-condition/c/race_condition_tls.c` are there after each thread has modified it at leas once?

## Question Answers

- 1

- 2

+ 3

- 5

## Feedback

There are 3 copies one for the `main()` thread, another one for `increment_var()` and the third for `decrement_var()`.
