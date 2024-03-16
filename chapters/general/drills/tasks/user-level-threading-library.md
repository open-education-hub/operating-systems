# User-level Threading Library

## Scenario

We aim to implement a user-level threading library that provides a POSIX Threads (`pthreads`) API.
The library should be portable across different operating systems and architectures and should be usable in programs written in various programming languages.

Answer the following questions with "True" or "False" and justify the answer.
Justification should be simple, 2-3 sentences for each answer.

## Questions

1. The library can only be used in programs written in compiled languages, NOT interpreted ones.
Answer: False

1. The library can work on operating systems with and without kernel-level thread support.
Answer: True

1. The library does not need to expose synchronization primitives (working with mutexes, spinlocks, condition variables).
Answer: False

1. Programs using the library must be dynamically linked.
Answer: False

1. Code within the library does produce page faults.
Answer: False

1. Code within the library does not lead to system calls.
Answer: False

1. For creating a thread on Linux, the library uses the `clone()` system call.
Answer: False

1. Programs using the library can run in a Docker container.
Answer: True

1. Modifying a file cursor in one thread will be visible in another thread.
Answer: True

1. A program using the library will use only one core/processor.
Answer: True

1. Programs using the library cannot use shared memory to communicate with other processes.
Answer: False
