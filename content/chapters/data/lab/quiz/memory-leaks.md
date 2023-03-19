# Memory Leaks

## Question Text

What happens to the leaked memory when the process finishes execution?

## Question Answers

- It will be freed by the OS garbage collector

- It remains unusable until the first restart

+ It is freed alongside all memory used by process

- It will remain reachable untill another process explicitely frees it

## Feedback

When a process ends, all its memory zones are freed by the OS to be reused.
Leaking memory becomes a major problem in case of programs that run indefinitely, because the leaked memory will stack, causing a memory outage.
