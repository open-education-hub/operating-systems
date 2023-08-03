# User-Level Threads

User-level threads differ from the threads you are used to (kernel-level threads, those created by pthread_create).
This kind of threads are scheduled by an user-level scheduler, and can run on the same kernel-level thread.
From now on, we will reffer to user-level threads as fibers, and kernel-level threads as simply threads.

We will use the fiber implementation from libboost.
This implementation uses a cooperative scheduler on each thread, meaning that each fiber has to yield, in order for other fiber to be executed.
We will also use C++, and the standard `thread` implementation.

## Prerequisites

Unless you are using the OS docker image, you will need to install `cmake` and `libboost`.
You can do this with the following command:

```console
student@os:~$ sudo apt-get install cmake libboost-context-dev libboost-fiber-dev
```

## Creation

Follow the `support/user-level-threads/simple.cc` implementation.
It creates `NUM_FIBERS` fibers, that each prints "Hello World".
To compile and run the program, do the following steps:

```console
student@os:~/.../lab/support/user-level-threads$ mkdir build/
student@os:~/.../lab/support/user-level-threads$ cd build/
student@os:~/.../lab/support/user-level-threads$ cmake -S .. -B .
student@os:~/.../lab/support/user-level-threads$ make
student@os:~/.../lab/support/user-level-threads$ ./simple
```

The `cmake` step must be executed only once.
After modifying the source files, it is enough to run `make`.

### Practice: Sleeper Fiber

Add in `support/user-level-threads/simple.cc` a fiber that sleeps for 5 seconds, before the other ones are created.
What happens?
Answer in this [quiz](../quiz/sleeping-on-a-fiber.md).

## No system calls

Use `strace` to find calls to `clone()` in the execution of `simple`.
Can you find any?
Provide your answer in this [quiz](../quiz/fiber-strace.md)
Remember that `clone()` is the system call used to create **kernel-level** threads, as pointed out [here](./arena.md#threads-and-processes-clone).

## Synchronization

By default, the fibers that run on the same thread are synchronized - no race-conditions can occur.
This is illustrated by the `support/user-level-threads/sum.cc` implementation.

The user can, however, implement further synchronization, by using the `yield()` call, or classic synchronization methods, like mutexes, barriers and condition variables.

### Yielding

As the scheduler is cooperative, each fiber can yield (or not), to allow another fiber to run.
Follow the `support/user-level-threads/yield_launch.cc` implementation and run it.
Note the `boost::fibers::launch::dispatch` parameter provided to the fiber constructor.
It notifies the scheduler to start the fibre as soon as it is created.
In order to explain the output, we must consider that the fibers are created by a **main fiber**, that is scheduled along with the others, in this case.

#### Practice

Modify the launch parameter into `boost::fibers::launch::post`, compile and notice the differences.
The `post` parameter notifies the scheduler not to start the fibers imediately, but rather place them into an execution queue.
Their execution will start after the main fiber calls the `join()` function.

### Barriers

Follow the `support/user-level-threads/yield_barrier.cc` implementation.
It uses a barrier to achieve the same result as the previos implementation, that used `post` as the launch parameter.

## Interaction Between Threads and Fibers

As we mentioned before, multiple fibers can run on the same thread, and a scheduler is implemented on each thread.
By default, the scheduling algorithm is [`round_robin`](https://www.guru99.com/round-robin-scheduling-example.html).
It runs the fibers, in the order of their creation, until they yield or finish their work.
If a fiber yields, it is placed at the back of the round-robin queue.
Using this scheduler, each thread only uses its fibers;
if one thread has more work to do than another, bad luck.
This may lead to starvation.

But there are other scheduler implementations, such as `shared_work` and `work_stealing`.
Follow the `support/user-level-threads/threads_and_fibers.cc` implementation.
It creates multiple fibers and threads, and uses the `shared_work` scheduler to balance the workload between the threads.
Each main fiber, from each thread, is suspended until all worker fibers have completed their work, using a condition variable.

```cpp
cnd_count.wait( lk, [](){ return 0 == fiber_count; } );
```

The program also uses `thread local storage` and `fiber local storage` to store the ID of each thread / fiber.

Now change the `shared_work` scheduler into the `work_stealing` one.
It takes a parameter, the number of threads that will use that scheduler.

Compile, rerun and note the differences.
The `work_stealing` scheduler, as the name suggests, will "steal" fibers from other schedulers.
So, if the `shared_work` scheduler tried to balance the available work between the available threads, the `work_stealing` one will focus on having as many threads as possible on 100% workload.
Vary the number of threads and fibers, and the workload (maybe put each fibre to do some computational-intensive work), and observe the results.

### C++ unique_lock

`unique_lock` is a type of mutex that is unlocked automatically when the end of its scope is reached (end of function or bracket-pair).
