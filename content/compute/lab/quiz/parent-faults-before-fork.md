# Parent Faults before `fork()`

## Question Text

What causes the page faults that occur between the first and second steps?

## Question Answers

- Calling `fork()` duplicates the pages previously allocated by the parent

+ Demand paging makes the pages in the `p` array to be mapped to frames only when written

- The OS duplicates the parent's pages in preparation for `fork()`

- `mmap()` sets the pages to be mapped at a later time, decided by the OS
