# `mmap()` file

## Question Text

What is one advantage of mapping a file in memory?

## Question Answers

+ It reduces interaction with the disk

- Consumes less memory

- It is faster because it does not uses the file API

- Allows all threads to use the same memory area

## Feedback

After mapping a file in memory, all changes will be visible only in memory.
When removing the mapping or explicitely calling `msync()` the information from memory will be visible on disk.
