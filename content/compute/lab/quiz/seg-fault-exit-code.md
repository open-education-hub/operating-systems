# Seg Fault Exit Code

## Question Text

What is the exit code of the faulty child process spawned by `support/sum-array-bugs/seg-fault/sum_array_processes.d` with more than 2 processes?

## Question Answers

+ 11 because this is the code of the `SIGSEGV` signal

- 11 because this code is always returned when a process ends with an error

- 11 because this is the value of the least significant 4 bytes of the partial array sum calculated by the process

- 6 because the child process was aborted

## Feedback

We can obtain the number of the signal that killed a child process via the second argument of the `waitpid` syscall.
We can use the `WIFSIGNALED()` and `WTERMSIG()` marcros.
By doing so, we see the exit code of the faulty child process is 11.
We can then use the `kill -l` command to view the code of each signal and `SIGSEGV` has the code 11.
