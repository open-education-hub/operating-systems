# I/O Errors

## Question Text

Which of the following types of errors are **unlikely** to occur during an I/O operation?

## Question Answers

- The current user does not have sufficient permisions to access a given file

- There is not enough space left on the disk

+ The file offset has reached the end of the file when reading

- Some data blocks in the filesystem are corrupted

## Feedback

We can always reposition the file offset within a given file with either a `fseek()` library call or an `lseek()` syscall, so this is not an error.
The others are more difficult to manage, so can be regarded as errors.
