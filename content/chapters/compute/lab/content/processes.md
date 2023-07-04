# Processes

## Hardware Perspective

Look at the [graph on this site](https://www.pcbenchmarks.net/number-of-cpu-cores.html) regarding the evolution of the number of cores in modern processors.
Notice they contain more and more of these cores.
You can think of a core as a unit of computation.
The more the CPU has, the more it can compute **at the same time**.

The hardware is just the "muscle" doing the work.
We need a "brain" to control it, which is the operating system.
It needs to separate its tasks into smaller chunks and run each of them on one of the CPU cores.
The coarsest level of separation is to split tasks into independent **processes**,

## Process Model

A process is simply a running program.
It exists asa a binary executable file on the disk.
When we run the file (for example via `./file` from the terminal), a new process is created and its address space is initially **populated with the contents of the executable file**.
Another program, called the _loader_ handles initializing the address space of the new process.
We'll go into it [later in the lab](./arena.md#first-step-system-dissected).

## Sum of the Elements in an Array

Navigate to the code in `support/sum-array/c/sum_array_sequential.c`.
The program measures the time spent computing the sum of the elements in an array.
Compile and run it.
Note the running time.

## Spreading the Work Among Other Processes

Run the following command to find the number of cores in your CPU: `lscpu | grep ^CPU\(s\)`.
Due to how it's implemented so far, our program only uses one of our CPU's cores.

To make our code run faster, we can split the array into smaller chunks and have separate processes compute partial sums of their specific chunks as shown in the image below.
The sum of the whole array is obviously the sum of the partial sums.

![Splitting the Array](../media/splitting-array.svg)

### Practice

Compile and run `sum_array_processes.c`.
First use 1 process then keep increasing the number until you reach the number of cores in you CPU (that you determined earlier).
Note the running times and compare them to the running time of `sum_array_sequential.c`.

[Answer this quiz](../quiz/processes-speedup.md)

Notice that we're not using hundreds or thousands of processes.
Assuming the CPU has 8 cores, it can only run 8 tasks at the same time (we'll see this [in another section](./scheduling.md) how the OS can support thousands of processes).

## Creating Processes

Remember that the simplest way to create a new process is to just run their executable file.
We can also create processes from code.
It's equivalent to running the program associated with a given process.

Run the code in `support/create-process/popen.py`.
It simply spawns a new process running the `ls` command using [`subprocess.Popen()`](https://docs.python.org/3/library/subprocess.html#subprocess.Popen).
Do not worry about the huge list of arguments that `Popen()` takes.
They are used for **inter-process-communication**.
You'll learn more about this in the [Application Interaction chapter](../../../app-interact/).

### Practice

Head over to `support/sleepy/sleepy_creator.py`.
Use `subprocess.Popen()` to spawn 10 `sleep 1000` processes.
Draw inspiration from `support/create-process/popen.py`.

1. Solve `TODO 1`: use `subprocess.Popen()` to spawn 10 `sleep 1000` processes.

   Start the script:

   ```console
   student@os:~/.../lab/support/sleepy$ python3 sleepy_creator.py
   ```

   Look for the parent process:

   ```console
   student@os:~$ ps -e -H -o pid,ppid,cmd | (head -1; grep "python3 sleepy_creator.py")
   ```

   The parent is `python3`, as this is the interpreter that runs the script, but we call it the `sleepy_creator.py` process for simplicity.

   [Answer this Quiz](../quiz/python3-process.md)

1. Use a similar command to look for the `sleep` processes created by running the script.

   [Answer this Quiz](../quiz/parent-of-sleep-processes.md)

1. Solve `TODO 2`: change the code in `sleepy_creator.py` so that the `sleep 1000` processes remain the children of `sleepy_creator.py`.
   For this to be correct, `sleepy_creator.py` must be visible when running `ps -e -H -o pid,ppid,cmd | (head -1; grep "sleep")`.
   In addition the `PPID`s of the `sleep` processes must be the same as the `PID` of `sleepy_creator`.
   TODO: add checker.

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

The order of the last 2 steps may be reversed.
