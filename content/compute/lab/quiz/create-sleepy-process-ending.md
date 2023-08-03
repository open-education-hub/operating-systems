# `create_sleepy` Process Ending

## Question Text

Why does the `create_sleepy` process wait a very long time before ending?
Use [`system`'s man page](https://man7.org/linux/man-pages/man3/system.3.html) to find the answer.

## Question Answers

- Because the code is unoptimised (the default optimisation level is `-O0`)

- Because the operating system takes very long to finish the process

+ Because `system` returns when the command given to it (`sleep 1000`) ends

- Because the CPU is very slow

## Feedback

The [man page](https://man7.org/linux/man-pages/man3/system.3.html) says it clearly:

```text
system() returns after the command has been completed.
```

Therefore, in our case, it returns after `sleep 1000` ends.
