# Thread Memory

## Question Text

Is data used by a thread inaccessible from other threads?

## Question Answers

- Yes, each thread has its own stack

+ No, each thread can access every address from the virtual address space

- Only the heap is shared

- Only the heap and the read-only zones are shared

## Feedback

Each thread has the same perspective on the system memory - it thinks it owns it all.
Therefore, it can perform pointer arithmetic to access every memory address.
