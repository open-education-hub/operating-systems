# Parallel Graph

## Objectives

- Learn how to design and implement parallel programs
- Gain skills in using synchronization primitives for parallel programs
- Get a better understanding of the POSIX threading and synchronization API
- Gain insight on the differences between serial and parallel programs

## Statement

Implement a generic thread pool, then use it to traverse a graph and compute the sum of the elements contained by the nodes.
You will be provided with a serial implementation of the graph traversal and with most of the data structures needed to implement the thread pool.
Your job is to write the thread pool routines and then use the thread pool to traverse the graph.

## Support Code

The support code consists of two directories:

- `src/` is the skeleton parallel graph implementation.
  You will have to implement missing parts marked as `TODO` items.

- `tests/` are tests used to validate (and grade) the assignment.

## Implementation

### Thread Pool Description

A thread pool contains a given number of active threads that simply wait to be given specific tasks.
The threads are created when the thread pool is created they poll a task queue until a task is available.
Once tasks are put in the task queue, the threads start running the task.
A thread pool creates N threads when the thread pool is created and does not destroy (join) them throughout the lifetime of the thread pool.
That way, the penalty of creating and destroying threads ad-hoc is avoided.
As such, you must implement the following functions (marked with `TODO` in the provided skeleton):

- `task_create()`: Creates an `os_task_t` that will be put in the task queue - a task consists of a function pointer and an argument.
- `add_task_in_queue()`: Adds a given task in the thread pool's task queue.
- `get_task()`: Gets a task from the thread pool's task queue.
- `threadpool_create()`: Allocates and initializes a new thread pool.
- `thread_loop_function()`: All the threads in the thread pool will execute this function.
   They all wait until a task is available in the task queue; once they grab a task they simply invoke the function that was provided to `task_create`.
- `threadpool_stop()`: Stop all the threads from execution.

Notice that the thread pool is completely independent of any given application.
Any function can be registered in the task queue.

### Graph Traversal

Once you have implemented the thread pool, you need to test it by using it for computing the sum of all the nodes of a graph.
A serial implementation for this algorithm is provided in `skep/serial.c`
To make use of the thread pool, you will need to create tasks that will be put in the task queue.
A task consists of 2 steps:

1. Add the current node value to the overall sum.
1. Create tasks and add them to the task queue for the neighbouring nodes.

Since the threads are polling the task queue indefinitely, you need to find a condition for the threads to stop once the graph has been traversed completely.
This condition should be implemented in a function that is passed to `threadpool_stop()`.
`threadpool_stop()` then needs to wait for the condition to be satisfied and then joins all the threads.

### Synchronization

For synchronization you can use mutexes, semaphores, spinlocks, condition variables - anything that grinds your gear.
However, you are not allowed to use hacks such as `sleep()`, `printf()` synchronization or adding superfluous computation.

### Input Files

Reading the graphs from the input files is being taken care of the functions implemented in `src/os_graph.c`.
A graph is represented in input files as follows:

- First line contains 2 integers `N` and `M`: `N` - number of nodes, `M` - numbed or edges
- Second line contains `N` integer numbers - the values of the nodes.
- The next `M` lines contain each 2 integers that represent the source and the destination of an edge.

### Data Structures

#### Graph

A graph is represented internally by the `os_graph_t` structure (see `src/os_graph.h`).

#### List

A list is represented internally by the `os_queue_t` structure (see `src/os_list.h`).
You will use this list to implement the task queue.

#### Thread Pool

A thread pool is represented internally by the `os_threadpool_t` structure (see `src/os_threadpool.h`).
The thread pool contains information about the task queue and the threads.

You are not allowed to modify these data structures.
However, you can create other data structures that leverage these ones.

### Requirements

Your implementation needs to be contained in the `src/os_threadpool.c` and `src/os_parallel.c` files.
Any other files that you are using will not be taken into account.
Any modifications that you are doing to the other files in the `src/` directory will not be taken into account.

## Operations

### Building

To build both the serial and the parallel versions, run `make` in the `src/` directory:

```console
student@so:~/.../content/assignments/parallel-graph$ cd src/

student@so:~/.../assignments/parallel-graph/src$ make
```

That will create the `serial` and `parallel` binaries.

## Testing and Grading

Testing is automated.
Tests are located in the `tests/` directory.

```console
student@so:~/.../assignments/parallel-graph/tests$ ls -F
Makefile  checker.py  grade.sh@  in/
```

To test and grade your assignment solution, enter the `tests/` directory and run `grade.sh`.
Note that this requires linters being available.
The easiest is to use a Docker-based setup with everything installed and configured.
When using `grade.sh` you will get grades for checking correctness (maximum `90` points) and for coding style (maxim `10` points).
A successful run will provide you an output ending with:

```console
### GRADE


Checker:                                                         90/ 90
Style:                                                           10/ 10
Total:                                                          100/100


### STYLE SUMMARY


```

### Running the Checker

To run only the checker, use the `make check` command in the `tests/` directory:

```console
student@so:~/.../assignments/parallel-graph/tests$ make check
[...]
SRC_PATH=../src python checker.py
make[1]: Entering directory '...'
rm -f *~
[...]
TODO
test_mmap_perm_ok                ........................ failed ...  0
test_mmap_perm_notok             ........................ failed ...  0
test_mmap_perm_none              ........................ failed ...  0

Total:                                                             0/100
```

Some files will fail to build, it's expected.
This is because there are missing files or missing functions that cause build errors.
You'll need to add those files and implement those functions for the build error to disappear.

Obviously, most tests will fail, as there is no implementation.
Some tests don't fail because the missing implementation equates to the bad behavior being tested not happening.

Each test is worth a number of points.
The maximum grade is `90`.

A successful run will show the output:

```console
student@so:~/.../assignments/parallel-graph/tests$ make check
[...]
SRC_PATH=../src python checker.py
test1.in                         ....................... passed ...   4.5
test2.in                         ....................... passed ...   4.5
test3.in                         ....................... passed ...   4.5
test4.in                         ....................... passed ...   4.5
test5.in                         ....................... passed ...   4.5
test6.in                         ....................... passed ...   4.5
test7.in                         ....................... passed ...   4.5
test8.in                         ....................... passed ...   4.5
test9.in                         ....................... passed ...   4.5
test10.in                        ....................... passed ...   4.5
test11.in                        ....................... passed ...   4.5
test12.in                        ....................... passed ...   4.5
test13.in                        ....................... passed ...   4.5
test14.in                        ....................... passed ...   4.5
test15.in                        ....................... passed ...   4.5
test16.in                        ....................... passed ...   4.5
test17.in                        ....................... passed ...   4.5
test18.in                        ....................... passed ...   4.5
test19.in                        ....................... passed ...   4.5
test20.in                        ....................... passed ...   4.5

Total:                                                              90/100
```

### Running the Linters

To run the linters, use the `make lint` command in the `tests/` directory:

```console
student@so:~/.../assignments/parallel-graph/tests$ make lint
[...]
cd .. && checkpatch.pl -f checker/*.sh tests/*.sh
[...]
cd .. && cpplint --recursive src/ tests/ checker/
[...]
cd .. && shellcheck checker/*.sh tests/*.sh
```

Note that the linters have to be installed on your system: [`checkpatch.pl`](https://.com/torvalds/linux/blob/master/scripts/checkpatch.pl), [`cpplint`](https://github.com/cpplint/cpplint), [`shellcheck`](https://www.shellcheck.net/).
They also need to have certain configuration options.
It's easiest to run them in a Docker-based setup with everything configured:

### Fine-Grained Testing

Input tests cases are located in `tests/in/`.
If you want manually run a single test, use commands such as below while in the `src/` directory:

```console
$./parallel ../tests/in/test5.in
-11

$ ./serial ../tests/in/test5.in
-11
```

Results provided by the serial and parallel implementation must be the same for the test to successfully pass.

## Grading

The grade that the checker outputs is not the final grade.
Your homework will be manually inspected and may suffer from penalties ranging from 1 to 100 points depending on the severity of the hack, including, but not limited to:

- using a single mutex at the beginning of the traversal
- not using the thread pool to solve the homework
- inefficient usage of synchronization
- incorrect graph traversal
