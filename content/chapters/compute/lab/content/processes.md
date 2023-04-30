# Processes

A process is simply a running program.
Let's take the `ls` command as a trivial example.
`ls` is a **program** on your system.
It has a binary file which you can find and inspect with the help of the `which` command:

```console
student@os:~$ which ls
/usr/bin/ls

student@os:~$ file /usr/bin/ls
/usr/bin/ls: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=6e3da6f0bc36b6398b8651bbc2e08831a21a90da, for GNU/Linux 3.2.0, stripped
```

When you run it, the `ls` binary stored **on the disk** at `/usr/bin/ls` is read by another application called the **loader**.
The loader spawns a **process** by copying some of the contents `/usr/bin/ls` in memory (such as the `.text`, `.rodata` and `.data` sections).
Using `strace`, we can see the [`execve`](https://man7.org/linux/man-pages/man2/execve.2.html) system call:

```console
student@os:~$ strace -s 100 ls -a  # -s 100 limits strings to 100 bytes instead of the default 32
execve("/usr/bin/ls", ["ls", "-a"], 0x7fffa7e0d008 /* 61 vars */) = 0
[...]
write(1, ".  ..  content\tCONTRIBUTING.md  COPYING.md  .git  .gitignore  README.md  REVIEWING.md\n", 86.  ..  content	CONTRIBUTING.md  COPYING.md  .git  .gitignore  README.md  REVIEWING.md
) = 86
close(1)                                = 0
close(2)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```

Look at its parameters:

- the path to the **program**: `/usr/bin/ls`
- the list of arguments: `"ls", "-a"`
- the environment variables: the rest of the syscall's arguments

`execve` invokes the loader to load the VAS of the `ls` process **by replacing that of the existing process**.
All subsequent syscalls are performed by the newly spawned `ls` process.
We will get into more details regarding `execve` [towards the end of this lab](./arena.md#first-step-system-dissected).

![Loading of `ls` Process](../media/loading-of-ls-process.svg)

## Sum of the Elements in an Array

Let's assume we only have one process on our system, and that process knows how to add the numbers in an array.
It can use however many resources it wants, since there is no other process to contest it.
It would probably look like the code in `support/sum-array/c/sum_array_sequential.c`.
The program also measures the time spent computing the sum.
Let's compile and run it:

```console
student@os:~/.../lab/support/sum-array/c$ ./sum_array_sequential
Array sum is: 49945994146
Time spent: 127 ms
```

You will most likely get a different sum (because the array is made up of random numbers) and a different time than the ones shown above.
This is perfectly fine.
Use these examples qualitatively, not quantitatively.

## Spreading the Work Among Other Processes

Due to how it's implemented so far, our program only uses one of our CPU's cores.
We never tell it to distribute its workload to other cores.
This is wasteful as the rest of our cores remain unused:

```console
student@os:~$ lscpu | grep ^CPU\(s\):
CPU(s):                          8
```

We have 7 more cores waiting to add numbers in our array.

![What if we used 100% of the CPU?](../media/100-percent-cpu.jpeg)

What if we use 7 more processes and spread the task of adding the numbers in this array between them?
If we split the array into several equal parts and designate a separate process to calculate the sum of each part, we should get a speedup because now the work performed by each individual process is reduced.

Let's take it methodically.
Compile and run `sum_array_processes.c` using 1, 2, 4 and 8 processes respectively.
If your system only has 4 cores ([hyperthreading](https://www.intel.com/content/www/us/en/gaming/resources/hyper-threading.html) included), limit your runs to 4 processes.
Note the running times for each number of processes.
We expect the speedups compared to our reference run to be 1, 2, 4 and 8 respectively, right?

[Quiz](../quiz/processes-speedup.md)

You most likely did get some speedup, especially when using 8 processes.
Now we will try to improve this speedup by using **threads** instead.

Also notice that we're not using hundreds or thousands of processes.
Assuming our system has 8 cores, only 8 _threads_ (we'll see this later in the lab) can run at the same time.
In general, **the maximum number of threads that can run at the same time is equal to the number of cores**.
In our example, each process only has one thread: its main thread.
So by consequence and by forcing the terminology (because it's the main thread of these processes that is running, not the processes themselves), we can only run in parallel a number of processes equal to at most the number of cores.

### Practice: Baby steps - Python

Run the code in `support/create-process/popen.py`.
It simply spawns a new process running the `ls` command using [`subprocess.Popen()`](https://docs.python.org/3/library/subprocess.html#subprocess.Popen).
Do not worry about the huge list of arguments that `Popen()` takes.
They are used for **inter-process-communication**.
You'll learn more about this in the [Application Interaction chapter](../../../app-interact/).

Note that this usage of `Popen()` is not entirely correct.
You'll discover why in the next exercise, but for now focus on simply understanding how to use `Popen()` on its own.

Now change the command to anything you want.
Also give it some arguments.
From the outside, it's as if you were running these commands from the terminal.

### Practice: High level - Python

Head over to `support/sleepy/sleepy_creator.py`.
Use `subprocess.Popen()` to spawn 10 `sleep 1000` processes.

1. Solve `TODO 1`: use `subprocess.Popen()` to spawn 10 `sleep 1000` processes.

   Start the script:

   ```console
   student@os:~/.../lab/support/sleepy$ python3 sleepy_creator.py
   ```

   Look for the parent process:

   ```console
   student@os:~$ ps -e -H -o pid,ppid,cmd | (head -1; grep "python3 sleepy_creator.py")
   ```

   It is a `python3` process, as this is the interpreter that runs the script, but we call it the `sleepy_creator.py` process for simplicity.
   No output will be provided by the above command, as the parent process (`sleepy_creator.py`) dies before its child processes (the 10 `sleep 1000` subprocesses) finish their execution.
   The parent process of the newly created child processes is an `init`-like process: either `systemd`/`init` or another system process that adopts orphan processes.
   Look for the `sleep` child processes using:

   ```console
   student@os:~$ ps -e -H -o pid,ppid,cmd | (head -1; grep sleep)
    PID    PPID         CMD
   4164    1680     sleep 1000
   4165    1680     sleep 1000
   4166    1680     sleep 1000
   4167    1680     sleep 1000
   4168    1680     sleep 1000
   4169    1680     sleep 1000
   4170    1680     sleep 1000
   4171    1680     sleep 1000
   4172    1680     sleep 1000
   4173    1680     sleep 1000
   ```

   Notice that the child processes do not have `sleepy_creator.py` as a parent.
   What's more, as you saw above, `sleepy_creator.py` doesn't even exist anymore.
   The child processes have been adopted by an `init`-like process (in the output above, that process has PID `1680` - `PPID` stands for _parent process ID_).

   [Quiz](../quiz/parent-of-sleep-processes.md)

1. Solve `TODO 2`: change the code in `sleepy_creator.py` so that the `sleep 1000` processes remain the children of `sleepy_creator.py`.
   This means that the parent / creator process must **not** exit until its children have finished their execution.
   In other words, the parent / creator process must **wait** for the termination of its children.
   Check out [`Popen.wait()`](https://docs.python.org/3/library/subprocess.html#subprocess.Popen.wait) and add the code that makes the parent / creator process wait for its children.
   Before anything, terminate the `sleep` processes created above:

   ```console
   student@os:~$ pkill sleep
   ```

   Start the program, again, as you did before:

   ```console
   student@os:~/.../lab/support/sleepy$ python3 sleepy_creator.py
   ```

   On another terminal, verify that `sleepy_creator.py` remains the parent of the `sleep` processes it creates:

   ```console
   student@os:~$ ps -e -H -o pid,ppid,cmd | (head -1; grep sleep)
    PID    PPID                CMD
   16107   9855         python3 sleepy_creator.py
   16108   16107           sleep 1000
   16109   16107           sleep 1000
   16110   16107           sleep 1000
   16111   16107           sleep 1000
   16112   16107           sleep 1000
   16113   16107           sleep 1000
   16114   16107           sleep 1000
   16115   16107           sleep 1000
   16116   16107           sleep 1000
   16117   16107           sleep 1000
   ```

   Note that the parent process `sleepy_creator.py` (`PID 16107`) is still alive, and its child processes (the 10 `sleep 1000`) have its ID as their `PPID`.
   You've successfully waited for the child processes to finish their execution.

### Practice: Lower level - C

Now let's see how to create a child process in C.
There are multiple ways of doing this.
For now, we'll start with a higher-level approach.

Go to `support/sleepy/sleepy_creator.c` and use [`system`](https://man7.org/linux/man-pages/man3/system.3.html) to create a `sleep 1000` process.

[Quiz](../quiz/create-sleepy-process-ending.md)

The `man` page also mentions that `system` calls `fork()` and `exec()` to run the command it's given.
If you want to find out more about them, head over to the [Arena and create your own mini-shell](./arena.md#mini-shell).

### Practice: Wait for Me

Run the code in `support/wait-for-me/wait_for_me_processes.py`.
The parent process creates one child that writes and message to the given file.
Then the parent reads that message.
Simple enough, right?
But running the code raises a `FileNotFoundError`.
If you inspect the file you gave the script as an argument, it does contain a string.
What's going on?

[Quiz](../quiz/cause-of-file-not-found-error.md)

In order to solve race conditions, we need **synchronization**.
This is a mechanism similar to a set of traffic lights in a crossroads.
Just like traffic lights allow some cars to pass only after others have already passed, synchronization is a means for threads to communicate with each other and tell each other to access a resource or not.

The most basic form of synchronization is **waiting**.
Concretely, if the parent process **waits** for the child to end, we are sure the file is created and its contents are written.
Use `join()` to make the parent wait for its child before reading the file.

### Practice: `fork()`

Up to now we've been creating processes using various high-level APIs, such as `Popen()`, `Process()` and `system()`.
Yes, despite being a C function, as you've seen from its man page, `system()` itself calls 2 other functions: `fork()` to create a process and `execve()` to execute the given command.
As you already know from the [Software Stack](../../../software-stack/) chapter, library functions may call one or more underlying system calls or other functions.
Now we will move one step lower on the call stack and call `fork()` ourselves.

`fork()` creates one child process that is _almost_ identical to its parent.
We say that `fork()` returns **twice**: once in the parent process and once more in the child process.
This means that after `fork()` returns, assuming no error has occurred, both the child and the parent resume execution from the same place: the instruction following the call to `fork()`.
What's different between the two processes is the value returned by `fork()`:

- **child process**: `fork()` returns 0
- **parent process**: `fork()` returns the PID of the child process (> 0)
- **on error**: `fork()` returns -1, only once, in the initial process

Therefore, the typical code for handling a `fork()` is available in `support/create-process/fork.c`.
Take a look at it and then run it.
Notice what each of the two processes prints:

- the PID of the child is also known by the parent
- the PPID of the child is the PID of the parent

Unlike `system()`, who also waits for its child, when using `fork()` we must do the waiting ourselves.
In order to wait for a process to end, we use the [`waitpid()`](https://linux.die.net/man/2/waitpid) syscall.
It places the exit code of the child process in the `status` parameter.
This argument is actually a bit-field containing more information than merely the exit code.
To retrieve the exit code, we use the `WEXITSTATUS` macro.
Keep in mind that `WEXITSTATUS` only makes sense if `WIFEXITED` is true, i.e. if the child process finished on its own and wasn't killed by another one or by an illegal action (such as a segfault or illegal instruction) for example.
Otherwise, `WEXITSTATUS` will return something meaningless.
You can view the rest of the information stored in the `status` bit-field [in the man page](https://linux.die.net/man/2/waitpid).

Now modify the example to do the following:

1. Change the return value of the child process so that the value displayed by the parent is changed.

1. Create a child process of the newly created child.
Use a similar logic and a similar set of prints to those in the support code.
Take a look at the printed PIDs.
Make sure the PPID of the "grandchild" is the PID of the child, whose PPID is, in turn, the PID of the parent.

**Moral of the story**: Usually the execution flow is:

1. `fork()`, followed by

1. `wait()` (called by the parent)

1. `exit()`, called by the child.

The order of last 2 steps may be swapped.
