## Question Text

What is the chronological order of appearance for the given events for a typical correct program?

## Question Answers

- memory allocation, memory access, page fault, page fault handling, physical memory allocation, re-execution of the original instruction
+ memory allocation, memory access, page fault, page fault handling, re-execution of the original instruction
- memory access, page fault, page fault handling, memory allocation, re-execution of the original instruction
- memory access, page fault, memory allocation, re-execution of the oriringal instruction

## Feedback

A typical correct program will first allocate and then access some memory.
Next, the first access will cause a page fault, then the page fault handler with resolve the situation by allocating a physical frame.
Therefore, one of the actions that are performed during page fault handling is to allocate physical memory.

