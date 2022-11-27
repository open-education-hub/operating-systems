# Processes Speedup

## Question Text

Why is the speedup from running the program in `support/sum-array/d/sum_array_processes.d` with 1, 2, 4 and 8 processes less than expected?

## Question Answers

- Because the array is split into unequal parts

+ Because of the overhead introduced by the creation of the additional processes

- Because the algorithm is incorrect

- Because the operating systems runs all processes sequentially on the same core

## Feedback

Creating a new process involves an inherent overhead.
The OS calls the loader, launches the new process, then the parent process waits for it to finish, extracts its return value etc.
All this work together with creating the initial process has to be done by a single thread.
In addition, in real-world apps, other actions such as receiving data from the network or reading a file are inherently **sequential**.
Therefore there will always be parts of any given program that cannot be run in parallel.
As a result, the speedup can never be equal to the number of processes between which we spread the workload.

It is possible to compute the speedup obtained from parallelising a portion of a given program.
The formula is rather simple and is called [Amdahl's law](https://en.wikipedia.org/wiki/Amdahl%27s_law)
