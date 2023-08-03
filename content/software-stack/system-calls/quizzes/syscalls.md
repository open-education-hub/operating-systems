# Syscalls

## Syscall ID

### Question Text

What register stores the system call ID on x86_64?

### Question Answers

- `RIP`

- `RSP`

+ `RAX`

- `RDX`

### Feedback

`RAX` is the register used for passing the syscall ID and the result code.

## Syscall Tool

### Question Text

What tool do we use to capture system calls?

### Question Answers

+ `strace`

- `make`

- `gcc`

- `./exec`

### Feedback

`strace` is used to trace system calls invoked by a running program.

## Syscall Numbers

### Question Text

What is the approximate number of system call numbers in Linux?

### Question Answers

- 3

- 30

+ 300

- 3000

### Feedback

As show [here](https://x64.syscall.sh/), they're about 300 system calls in Linux.
