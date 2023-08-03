# Threads Shared Data

## Question Text

Which section may store per-thread non-shared (variables) variables?

## Question Answers

- On the heap

- In the `.rodata` section

+ On the stack

- In the `.text` section

## Feedback

Each thread has its own separate stack.
Every other section is shared with the other threads.
Data can also be stored in the `.text` section, albeit this is a bit unorthodox.
