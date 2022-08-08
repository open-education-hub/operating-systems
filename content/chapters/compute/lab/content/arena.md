## Arena

### Threads and Processes: `clone`

Let's go back to our initial demos that used threads and processes.
We'll see that in order to create both threads and processes, the underlying Linux syscall is `clone`.
For this, we'll run both `sum_array_threads` and `sum_array_processes` under `strace`.
As we've already established, we're only interested in the `clone` syscall:

```
student@os:~/.../lab/support/sum-array/d$ strace -e clone ./sum_array_threads 2
clone(child_stack=0x7f60b56482b0, flags=CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID, parent_tid=[1819693], tls=0x7f60b5649640, child_tidptr=0x7f60b5649910) = 1819693
clone(child_stack=0x7f60b4e472b0, flags=CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID, parent_tid=[1819694], tls=0x7f60b4e48640, child_tidptr=0x7f60b4e48910) = 1819694

student@os:~/.../lab/support/sum-array/d$ strace -e clone ./sum_array_processes 2
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7f7a4e346650) = 1820599
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7f7a4e346650) = 1820600
```

We ran each program with an argument of 2, so we have 2 calls to `clone`.
Notice that in the case of threads, the `clone` syscall receives more arguments.
The relevant flags passed as arguments when creating threads are documented in [`clone`'s man page](https://man.archlinux.org/man/clone3.2.en):
- `CLONE_VM`: the child and the parent process share the same VAS
- `CLONE_{FS,FILES,SIGHAND}`: the new thread shares the filesystem information, file and signal handlers with the one that created it
The syscall also receives valid pointers to the new thread's stack and TLS, i.e. the only parts of the VAS that are distinct between threads (although they are technically accessible from all threads).

By contrast, when creating a new process, the arguments of the `clone` syscall are simpler (i.e. fewer flags are present).
Remember that in both cases `clone` creates a new **thread**.
When creating a process, `clone` creates this new thread within a new separate address space.

### Libraries for Parallel Processing

In `support/sum-array/d/sum_array_threads.d` we spawned threads "manually" by using the `spawn` function.
This is **not** a syscall, but a wrapper over the most common thread-management API in POSIX-based operating systems (such as Linux, FreeBSD, macOS): POSIX Threads or `pthreads`.
By inspecting the [implementation of `spawn`](https://github.com/dlang/phobos/blob/352258539ca54e640e862f79b2b8ec18aafa7d94/std/concurrency.d#L618-L622), we see that it creates a `Thread` object, on which it calls the `start()` method.
In turn, [`start()` uses `pthread_create()`](https://github.com/dlang/dmd/blob/cc117cd45c7d72ce5a87b775e65a9d13fa4d4424/druntime/src/core/thread/osthread.d#L454-L486) on POSIX systems.

Still, `pthread_create()` is not yet a syscall.
In order to see what syscall `pthread_create()` uses, check out [this section at the end of the lab](#threads-and-processes-clone).

Most programming languages provide a more advanced API for handling parallel computation.
D makes no exception.
Its standard library exposes the [`std.parallelism`](https://dlang.org/phobos/std_parallelism.html), which provides a series of parallel processing functions.
One such function is `reduce` which splits an array between a given number of threads and applies a given operation to these chunks.
In our case, the operation simply adds the elements to an accumulator: `a + b`.
Follow and run the code in `support/sum-array/d/sum_array_threads_reduce.d`.

The number of threads is used within a [`TaskPool`](https://dlang.org/phobos/std_parallelism.html#.TaskPool).
This structure is a thread manager (not scheduler).
It silently creates the number of threads we request and then `reduce` spreads its workload between these threads.

Now run the `sum_array_threads_reduce` binary using 1, 2, 4, and 8 threads as before.
You'll see lower running times than `sum_array_threads` due to the highly-optimised code of the `reduce` function.
For this reason and because library functions are usually much better tested than your own code, it is always preferred to use a library function for a given task.

### Shared Memory

As you remember from the [Data chapter](../../data/), one way to allocate a given number of pages is to use the `mmap()` syscall.
Let's look at its [man page](https://man7.org/linux/man-pages/man2/mmap.2.html), specifically at the `flags` argument.
Its main purpose is to determine the way in which child processes interact with the mapped pages.

[Quiz](../quiz/mmap-cow-flag.md)

Now let's test this flag, as well as its opposite: `MAP_SHARED`.
Compile and run the code in `support/shared-memory/shared_memory.c`.

1. See the value read by the parent id different from that written by the child.
Modify the `flags` parameter of `mmap()` so they are the same.

2. Create a semaphore in the shared page and use it to make the parent signal the child before it can exit.
Use the API defined in [`semaphore.h`](https://man7.org/linux/man-pages/man0/semaphore.h.0p.html).
**Be careful!**
The value written and read previously by the child and the parent, respectively, must not change.

One way of creating a shared semaphore is to place it within a shared memory area, as we've just done.
This only works between "related" processes.
If you want to share a semaphore or other types of memory between any two processes, you need filesystem support.
For this, you should use **named semaphores**, created using [`sem_open()`](https://man7.org/linux/man-pages/man3/sem_open.3.html).
You'll get more accustomed to such functions in the [Application Interaction chapter](../../../app-interact/).

### Mini-shell

#### First Step: `system` Dissected

You already know that `system` calls `fork()` and `execve()` to create the new process.
Let's see how and why.
First, we run the following command to trace the `execve()` syscalls used by `sleepy_creator`.
We'll leave `fork()` for later.

```
student@os:~/.../support/sleepy$ strace -e execve -ff -o syscalls ./sleepy_creator
```

At this point you will get two files whose names start with `syscalls`, followed by some numbers.
Those numbers are the PIDs of the parent and the child process.
Therefore, the file with the higher number contains logs of the `execve` and `clone` syscalls issued by the parent process, while
the other logs those two syscalls when made by the child process.
Let's take a look at them.
The numbers below will differ from those on your system:

```
student@os:~/.../support/sleepy:$ cat syscalls.2523393  # syscalls from parent process
execve("sleepy_creator", ["sleepy_creator"], 0x7ffd2c157758 /* 39 vars */) = 0
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=2523394, si_uid=1052093, si_status=0, si_utime=0, si_stime=0} ---
+++ exited with 0 +++

student@os:~/.../support/sleepy:$ cat syscalls.2523394  # syscalls from child process
execve("/bin/sh", ["sh", "-c", "sleep 10"], 0x7ffd36253be8 /* 39 vars */) = 0
execve("/usr/bin/sleep", ["sleep", "10"], 0x560f41659d40 /* 38 vars */) = 0
+++ exited with 0 +++
```

[Quiz](../quiz/who-calls-execve-parent.md)

Now notice that the child process doesn't simply call `execve("/usr/bin/sleep" ...)`.
It first changes its virtual address space (VAS) to that of a `bash` process (`execve("/bin/sh" ...)`) and then that `bash` process switches its VAS to `sleep`.
Therefore, calling `system(<some_command>)` is equivalent to running `<some_command>` in the command-line.

With this knowledge in mind, let's implement our own mini-shell.
Start from the skeleton code in `support/mini-shell/mini_shell.c`.
We're already running our Bash interpreter from the command-line, so there's no need to `exec` another Bash from it.
Simply `exec` the command.

[Quiz](../quiz/mini-shell-stops-after-command.md)

So we need a way to "save" the `mini_shell` process before `exec()`-ing our command.
Find a way to do this.

> **Hint**:  You can see what `sleepy` does and draw inspiration from there.
> Use `strace` to also list the calls to `clone()` perfromed by `sleepy` or its children.
> [Remember](#threads-and-processes-clone) what `clone()` is used for and use its parameters to deduce which of the two scenarios happens to `sleepy`. 

**Moral of the story**: We can add another step to the moral of [our previous story](./processes.md#practice-fork).
When spawning a new command, the call order is:
- parent: `fork()`, `exec()`, `wait()`
- child: `exit()`

#### Command Executor in Another language

Now implement the same functionality (a Bash command executor) in any other language, other than C/C++.
Use whatever API is provided by your language of choice for creating and waiting for processes.

### The GIL

Throughout this lab you might have noticed that there were no thread exercises _in Python_.
If you did, you probably wondered why.
It's not because Python does not support threads, because it does, but because of a mechanism called the **Global Interpreter Lock**, or GIL.
As its name suggests, this is a lock implemented inside most commonly used Python interpreter (CPython), which only allows **one** thread to run at a given time.
As a consequence, multithreaded programs written in Python run **concurrently**, not in parallel.
For this reason, you will see no speedup even when you run an embarrassingly parallel code in parallel.

However, keep in mind that this drawback does not make threads useless in Python.
They are still useful and widely used when a process needs to perform many IO-bound tasks (i.e.: tasks that involve many file reads / writes or network requests).
Such tasks run many blocking syscalls that require the thread to switch from the RUNNING state to WAITING.
Doing so voluntarily makes threads viable because they rarely run for their entire time slice and spend most of the time waiting for data.
So it doesn't hurt them to run concurrently, instead of in parallel.

Do not make the confusion to believe threads in Python are [user-level threads](./scheduling.md#user-level-vs-kernel-level-threads).
[`threading.Thread`](https://docs.python.org/3/library/threading.html#threading.Thread)s are kernel-level threads.
It's just that they are forced to run concurrenntly by the GIL.

#### Practice: Array Sum in Python

Let's first probe this by implementing two parallel versions of the code in `support/sum-array/python/sum_array_sequential.py`.
One version should use threads and the other should use processes.
Run each of them using 1, 2, 4, and 8 threads / processes respectively and compare the running times.
Notice that the running times of the multithreaded implementation do not decrease.
This is because the GIL makes it so that those threads that you create essentially run sequentially.

The GIL also makes it so that individual Python instructions are atomic.
Run the code in `support/race-condition/python/race_condition.py`.
Every time, `var` will be 0 because the GIL doesn't allow the two threads to run in parallel and reach the critical section at the same time.
This means that the instructions `var += 1` and `var -= 1` become atomic.

#### But Why?

Unlike Bigfoot, or the Loch Ness monster, we have proof that the GIL is real.
At first glance, this seems like a huge disadvantage.
Why force threads to run sequentially?
The answer has to do with memory management.
In the [Data chapter](../../../data), you learned that one way of managing memory is via _garbage collection_ (GC).
In Python, the GC uses reference counting, i.e. each object also stores the number of live pointers to it (variables that reference it).
You can see that this number needs to be modified atomically by the interpreter to avoid race conditions.
This involves adding locks to **all** Python data structures.
This large number of locks doesn't scale for a language as large and open as Python.
In addition, it also introduces the risk of _deadlocks_.
You can read more on this topic [in this article](https://realpython.com/python-gil/) and if you think eliminating the GIL looks like an easy task, which should have been done long ago, check the requirements [here](https://wiki.python.org/moin/GlobalInterpreterLock).
They're not trivial to meet.

Single-threadedness is a common trope for interpreted languages to use some sort of GIL.
[Ruby MRI, the reference Ruby interpreter](https://git.ruby-lang.org/ruby.git) uses a similar mechanism, called the [Global VM Lock](https://ivoanjo.me/blog/2022/07/17/tracing-ruby-global-vm-lock/).
JavaScript is even more straightforward: it is single-threaded by design, also for GC-related reasons.
It does, however support asynchronous actions, but these are executed on the same thread as every other code.
This is implemented by placing each instruction on a [call stack](https://medium.com/swlh/what-does-it-mean-by-javascript-is-single-threaded-language-f4130645d8a9). 

### Atomic Assembly

No, this section is not about nukes, sadly :(.
Instead, we aim to get accustomed to the way in which the x86 ISA provides atomic instructions.

This mechanism looks very simple.
It is but **one instruction prefix**: `lock`.
It is not an instruction with its own separate opcode, but a prefix that slightly modifie the opcode of the following instructions to make the CPU execute it atomically (i.e. with exclusive access to the data bus).

`lock` must only be place before an instruction that executes a _read-modify-write_ action.
For example, we cannot place it before a `mov` instruction, as the action of a `mov` is simply `read` or `write`.
Instead, we can place it in front of an `inc` instruction if its operand is memory.

Look at the code in `support/race-condition/asm/race_condition_lock.S`.
It's an Assembly equivalent of the code you've already seen many times so far (such as `support/race-condition/d/race_condition.d`).
Assemble and run it a few times.
Notice the different results you get.

Now add the `lock` prefix before `inc` and `dec`.
Reassemble and rerun the code.
And now we have synchronized the two threads by leveraging CPU support.

### Synchronization - Thread-Safe Data Structure

Now it's time for a fully practical exercise.
Go to `support/CLIST/`.
In the file `clist.c` you'll find a simple implementation of an array list.
Although correct, it is not (yet) thread-safe.

The code in `test.c` verifies its single-threaded correctness while the one in `test_parallel.c` verifies it works properly with multiple threads.
Your task is to synchronize this data structure using whichever primitives you like.
Try to keep the implementation efficient.
Aim to decrease your running times as much as you can.
