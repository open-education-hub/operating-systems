# Memory Leaks

## Question Text

What happens to the leaked memory when the process finishes execution?

## Question Answers

- It will be freed by the OS garbage collector

- It remains unusable until the first restart

+ It is freed alongside all memory used by process

- It will remain reachable untill another process explicitely frees it

## Feedback

When a process ends, all its memory zones are returned to the OS to be reused.
Leaking memory on a server is a major problem as it can lead to a memory outage.
