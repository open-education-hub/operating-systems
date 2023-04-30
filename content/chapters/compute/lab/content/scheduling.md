# Scheduling

Up to now, we know that the OS decides which **thread** (not process) runs on each CPU core at each time.
Now we'll learn about the component that performs this task specifically: **the scheduler**.

There are thousands of threads running at any time in a modern OS.
The job of the scheduler is to run and pause threads as well as allocate them to the CPU cores, with the following goals:

- **fairness**: we do want all threads to get the same chance to run, i.e. run for about the same amount of time
- **throughput**: we want to run as many threads to completion so as to complete as many tasks as we can

To do this, the scheduler must decide, at given times, to suspend a thread, save its current state and let another one run in its place.
This event is called a **context switch**.
A context switch means changing the state of one thread (the replaced thread) from RUNNING to WAITING, and the state of the replacement thread from READY / WAITING to RUNNING.

<!-- TODO -->
- Quiz?

## User-Level vs Kernel-Level Threads

There are two types of threads.
The threads you've used so far are **kernel-level threads (KLT)**.
They are created and scheduled in the kernel of the OS.
One of the most important of their features is that they offer true parallelism.
With KLTs, we can truly run a program on all the cores of our CPU at once.
But we must pay a price for this: scheduling them is very complex, and context switches are costly (in terms of time), especially when switching threads belonging to different processes.

By contrast, **user-level threads (ULT)** are managed by the user space.
More of the ULTs created by a program are generally mapped to the same kernel thread.
If a process only creates ULTs, then they will all be mapped to the single, main kernel thread of the process.
So if we cannot run code in parallel with ULTs, then why use them?
Well, programs that create many context switches may suffer from the larger overhead if they use kernel-level threads.
In such cases, user-level threads may be useful as context switches bring less overhead between user-level threads.

## Practice: User-Level Threads Scheduler

Go to `support/libult`.
It contains a minimalist **user-level threads** scheduler.
Compiling it produces a shared library called `libult.so`.
You can also consult its [documentation](https://www.schaertl.me/posts/a-bare-bones-user-level-thread-library/).
It explains the API as well as its implementation.
The API exposed by the scheduling library is very simple.
It is only made up of 3 functions:

- `threads_create()` creates a new ULT
- `threads_exit()` moves the current ULT to the COMPLETED state
- `threads_join()` waits for a given thread to end and saves its return value in the `result` argument

Look inside `support/libult/threads.c`.
Here you will find the 3 functions mentioned above.

The scheduler only uses 3 states: RUNNING, READY, COMPLETED.

[Quiz](../quiz/number-of-running-ults.md)

The threads in the READY and COMPLETED states are kept in 2 separate queues.
When the scheduler wants to run a new thread, it retrieves it from the READY queue.
When a thread ends its execution, it is added to the COMPLETED queue, together with its return value.

[Quiz](../quiz/why-use-completed-queue.md)

## Thread Control Block

Let's dissect the `threads_create()` function a bit.
It first initialises its queues and the timer for preemption.
We'll discuss preemption [in the next section](#scheduling---how-is-it-done).
After performing initialisations, the function creates a `TCB` object.
TCB stands for **Thread Control Block**.

During the [lecture](../../lecture/), you saw that the kernel stores one instance of a [`task_struct`](https://elixir.bootlin.com/linux/v5.19.11/source/include/linux/sched.h#L726) for each thread.
Remember that its most important fields are:

```C
struct task_struct {
	unsigned int                    __state;

	void                           *stack;

	unsigned int                    flags;

	int                             on_cpu;
	int                             prio;

	/* Scheduler information */
	struct sched_entity             se;
	const struct sched_class        *sched_class;

	/* The VAS: memory mappings */
	struct mm_struct                *mm;

	int                             exit_state;
	int                             exit_code;

	pid_t                           pid;

	struct task_struct __rcu        *parent;

	/* Child processes */
	struct list_head                children;

	/* Open file information */
	struct files_struct             *files;
};
```

As you can see, this `struct` stores _metadata_ regarding a given thread.
The same is true about the `TCB` in `libult.so`:

```c
typedef struct {
	int id;
	ucontext_t context;
	bool has_dynamic_stack;
	void *(*start_routine) (void *);
	void *argument;
	void *return_value;
} TCB;
```

It stores the thread ID (tid - `id`), similar to the PID of a process.
It stores a pointer to the function passed as argument to `threads_create()` (`start_routine`), as well as the argument (`argument`) and the returned value (`return_value`) of said function.

In addition, the `TCB` stores a `context`.
From the [man page of the `ucontext.h` header](https://pubs.opengroup.org/onlinepubs/7908799/xsh/ucontext.h.html), we can see this type is a `struct` that stores a pointer to the stack of the current thread (`uc_stack`).
This is similar to the `stack` pointer in the `task_struct` above.
In short, we can say a context defines an execution unit, such as a thread.
**This is why changing the running thread is called a context switch.**

Let's compare this context with another thread implementation, from [Unikraft](https://unikraft.org/).
We'll look at the [`uk_thread`](https://github.com/unikraft/unikraft/blob/9bf6e63314a401204c02597834fb02f63a29aaf4/lib/uksched/include/uk/thread.h#L55-L76) `struct`, which is the TCB used in Unikraft:

```c
struct uk_thread {
	const char *name;
	void *stack;
	void *tls;
	void *ctx;
	UK_TAILQ_ENTRY(struct uk_thread) thread_list;
	uint32_t flags;
	__snsec wakeup_time;
	bool detached;
	struct uk_waitq waiting_threads;
	struct uk_sched *sched;
	void (*entry)(void *);
	void *arg;
	void *prv;
};
```

There are some visible similarities between the two TCBs.

[Quiz](../quiz/tcb-libult-unikraft.md)

Therefore, the workflow for creating and running a thread goes like this:

```console
main thread
    |
    `--> threads_create()
            |
	    |--> tcb_new()
            `--> makecontext()
	            |
		    `--> handle_thread_start() - called using the context
		            |
			    |--> start_routine() - the thread runs
                            `--> threads_exit()
```

Compile and run the code in `support/libult/test_ult.c`.
If you encounter the following error when running `test_ult`, remember what you learned about the loader and using custom shared libraries in the [Software Stack lab](../../../software-stack/lab).

```console
./test_ult: error while loading shared libraries: libult.so: cannot open shared object file: No such file or directory
```

> Hint: Use the `LD_LIBRARY_PATH` variable.

Notice that the threads run their code and alternatively, because their prints appear interleaved.
[In the next section](#scheduling---how-is-it-done), we'll see how this is done.

[Quiz](../quiz/ult-thread-ids.md)

## Scheduling - How is it done?

There are two types of schedulers: **preemptive** and **cooperative**.
When discussing this distinction, we need to first define the notion of **yielding**.
Yielding the CPU means that a thread suspends its own execution and enters the WAITING or READY state, either as a result of a blocking call (I/O operations or calling the scheduler's `yield()` function directly).
So, yielding the CPU triggers a context switch whereby the current thread stops running and another one resumes or starts running in its place.

### Cooperative Scheduling

Cooperative scheduling relies on the fact that threads themselves would yield the CPU at some point.
If threads don't abide by this convention, they end up monopolising the CPU (since there is no one to suspend them) and end up starving the others.
You can get a feel of this behaviour by running the cooperative [scheduler from Unikraft](https://github.com/unikraft/unikraft/blob/staging/lib/ukschedcoop/schedcoop.c) in the [lecture demos](../../lecture/demo/cooperative-scheduling).

This type of schedulers have the advantage of being lightweight, thus resulting in less overhead caused by context switches.
However, as we've already stated, they rely on the "good will" of threads to yield the CPU at some point.

### Preemptive Scheduling

Preemptive scheduling solves the issue stated above by leaving the task of suspending the currently RUNNING thread and replacing it with another one from the READY queue up to the scheduler.
This increases its complexity and the duration of context switches, but threads now are not required to worry about yielding themselves and can focus on running their code and performing the task for which they are created.

Preemptive schedulers allow threads to run only for a maximum amount of time, called a **time slice** (usually a few milliseconds).
They use timers which fire when a new time slice passes.
The firing of one such timer causes a context switch whereby the currently RUNNING thread is _preempted_ (i.e. suspended) and replaced with another one.

[Quiz](../quiz/type-of-scheduler-in-libult.md)

Look at the `init_profiling_timer()` function.
It creates a timer that generates a `SIGPROF` signal and then defines a handler (the `handle_sigprof()` function) that is executed whenever the `SIGPROF` signal is received.

[Quiz](../quiz/time-slice-value.md)

It is this handler that performs the context switch per se.
Look at its code.
It first saves the context of the current thread:

```C
ucontext_t *stored = &running->context;
ucontext_t *updated = (ucontext_t *) context;

stored->uc_flags = updated->uc_flags;
stored->uc_link = updated->uc_link;
stored->uc_mcontext = updated->uc_mcontext;
stored->uc_sigmask = updated->uc_sigmask;
```

Then it places the current thread in the `ready` queue and replaces it with the first thread in the same queue.
This algorithm (that schedules the first thread in the READY queue) is called _Round-Robin_:

```C
if (queue_enqueue(ready, running) != 0) {
	abort();
}

if ((running = queue_dequeue(ready)) == NULL) {
	abort();
}
```

The new `running` thread is resumed upon setting the current context to it:

```C
if (setcontext(&running->context) == -1) {
	abort();
}
```

This is how scheduling is done!

### Practice: Another Time Slice

1. Modify the time slice set to the timer to 2 seconds.
Re-run the code in `support/libult/test_ult.c`.
Notice that now no context switch happens between the 2 created threads because they end before the timer can fire.

1. Now change the `printer_thread()` function in `test_ult.c` to make it run for more than 2 seconds.
See that now the prints from the two threads appear intermingled.
Add prints to the `handle_sigprof()` function in `support/libult/threads.c` to see the context switch happen.
