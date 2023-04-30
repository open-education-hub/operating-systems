# Threads

## Spreading the Work Among Other Threads

Compile the code in `support/sum-array/c/sum_array_threads.c` and run it using 1, 2, 4 and 8 threads as you did before.
Each thread runs the `calculateArrayPartSum` function and then finishes.
Running times should be _slightly_ smaller than the implementation using processes.
This slight time difference is caused by process creation actions, which are costlier than thread creation actions.
Because a process needs a separate virtual address space (VAS) and needs to duplicate some internal structures such as the file descriptor table and page table, it takes the operating system more time to create it than to create a thread.
On the other hand, threads belonging to the same process share the same VAS and, implicitly, the same OS-internal structures.
Therefore, they are more lightweight than processes.

### Practice: Wait for Me Once More

Go to `support/wait-for-me/wait_for_me_threads.c`.
Spawn a thread that executes the `negate_array()` function.
For now, do not wait for it to finish;
simply start it.

Compile the code and run the resulting executable several times.
See that the negative numbers appear from different indices.
This is precisely the nondeterminism that we talked about [in the previous section](./processes.md#practice-wait-for-me).

Now wait for that thread to finish and see that all the printed numbers are consistently negative.

As you can see, waiting is a very coarse form of synchronization.
If we only use waiting, we can expect no speedup as a result of parallelism, because one thread must finish completely before another can continue.
We will discuss more fine-grained synchronization mechanisms [later in this lab](./synchronization.md).

Also, at this point, you might be wondering why this exercise is written in D, while [the same exercise, but with processes](./processes.md#practice-wait-for-me) was written in Python.
There is a very good reason for this and has to do with how threads are synchronized by default in Python.
You can find out what this is about [in the Arena section](./arena.md#the-gil), after you have completed the [Synchronization section](./synchronization.md).

## Threads vs Processes

So why use the implementation that spawns more processes if it's slower than the one using threads?
The table below lists the differences between threads and processes.
Generally, if we only want to do some computing, we use threads.
If we need to drastically change the behaviour of the program, we need a new program altogether, or we need more than computing (e.g. communication on the network to create a computing cluster), we use processes.

| PROCESS                                              | THREAD                                                                  |
| :--------------------------------------------------- | :---------------------------------------------------------------------- |
| independent                                          | part of a process                                                       |
| collection of threads                                | shares VAS with other threads                                           |
| slower creation (new page table must be created)     | faster creation                                                         |
| longer context switch duration (TLB must be flushed) | shorter context switch duration (part of the same process, so same TLB) |
| ending means ending all threads                      | other threads continue when finished                                    |

### Safety

Compile and run the two programs in `support/sum-array-bugs/seg-fault/`, first with 2 processes and threads and then with 4.
They do the same thing as before: compute the sum of the elements in an array, but with a twist: each of them contains a bug causing a segfault.
Notice that `sum_array_threads` doesn't print anything with 4 threads, but merely a "Segmentation fault" message.
On the other hand, `sum_array_processes` prints a sum and a running time, albeit different from the sums we've seen so far.

The reason is that signals such as `SIGSEGV`, which is used when a segmentation fault happens affect the entire process that handles them.
Therefore, when we split our workload between several threads and one of them causes an error such as a segfault, that error is going to terminate the entire process.
The same thing happens when we use processes instead of threads: one process causes an error, which gets it killed, but the other processes continue their work unhindered.
This is why we end up with a lower sum in the end: because one process died too early and didn't manage to write the partial sum it had computed to the `results` array.

### Practice: Wait for It

The process that spawns all the others and subsequently calls `waitpid` to wait for them to finish can also get their return codes.
Update the code in `support/sum-array-bugs/seg-fault/sum_array_processes.c` and modify the call to `waitpid` to obtain and investigate this return code.
Display an appropriate message if one of the child processes returns an error.

Remember to use the appropriate [macros](https://linux.die.net/man/2/waitpid) for handling the `status` variable that is modified by `waitpid()`, as it is a bit-field.
When a process runs into a system error, it receives a signal.
A signal is a means to interrupt the normal execution of a program from the outside.
It is associated with a number.
Use `kill -l` to find the full list of signals.

[Quiz](../quiz/seg-fault-exit-code.md)

So up to this point we've seen that one advantage of processes is that they offer better safety than threads.
Because they use separate virtual address spaces, sibling processes are better isolated than threads.
Thus, an application that uses processes can be more robust to errors than if it were using threads.

### Memory Corruption

Because they share the same address space, threads run the risk of corrupting each other's data.
Take a look at the code in `support/sum-array-bugs/memory-corruption/python/`.
The two programs only differ in how they spread their workload.
One uses threads while the other uses processes.

Run both programs with and without memory corruption.
Pass any value as a third argument to trigger the corruption.

```console
student@os:~/.../sum-array-bugs/memory-corruption/python$ python3 memory_corruption_processes.py <number_of_processes>  # no memory corruption
[...]

student@os:~/.../sum-array-bugs/memory-corruption/python$ python3 memory_corruption_processes.py <number_of_processes> 1  # do memory corruption
[...]
```

The one using threads will most likely print a negative sum, while the other displays the correct sum.
This happens because all threads refer to the same memory for the array `arr`.
What happens to the processes is a bit more complicated.

[Later in this lab](./copy-on-write.md), we will see that initially, the page tables of all processes point to the same physical frames or `arr`.
When the malicious process tries to corrupt this array by **writing data to it**, the OS duplicates the original frames of `arr` so that the malicious process writes the corrupted values to these new frames, while leaving the original ones untouched.
This mechanism is called **Copy-on-Write** and is an OS optimisation so that memory is shared between the parent and the child process, until one of them attempts to write to it.
At this point, this process receives its own separate copies of the previously shared frames.

Note that in order for the processes to share the `sums` dictionary, it is not created as a regular dictionary, but using the `Manager` module.
This module provides some special data structures that are allocated in **shared memory** so that all processes can access them.
You can learn more about shared memory and its various implementations [in the Arena section](./arena.md#shared-memory).

## Memory Layout of Multithreaded Programs

When a new thread is created, a new stack is allocated for a thread.
The default stack size if `8 MB` / `8192 KB`:

```console
student@os:~$ ulimit -s
8192
```

Enter the `support/multithreaded/` directory to observe the update of the memory layout when creating new threads.

Build the `multithreaded` executable:

```console
student@os:~/.../lab/support/multithreaded$ make
```

Start the program:

```console
student@os:~/.../lab/support/multithreaded$ ./multithreaded
Press key to start creating threads ...
[...]
```

And investigate it with `pmap` on another console, while pressing a key to create new threads.

As you can see, there is a new `8192 KB` area created for every thread, also increasing the total virtual size.

### Practice

1. Build the multithreaded program as a static executable by adding `LDFLAGS = -static` to the Makefile:
   Run it.
   You can check the executable is statically linked by executing the command `ldd multithreaded`.
   Notice the same effect of the thread creation on the process memory layout: the creation of a new stack of `8192 KB`.

1. Make a program in another language of your choice that creates threads.
   Investigate it with `pmap`.

[Quiz](../quiz/thread-memory.md)
