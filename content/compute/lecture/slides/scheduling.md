---

## Scheduling

---

### Scheduling - Why?

* For multitasking: more threads than CPU cores
* For responsiveness: small waiting time
* For productivity: execute more threads

----

#### Typical Thread Execution

![Thread Execution](media/thread-behaviour.svg)

----

#### Thread States

* At most one RUNNING thread per core
* Queues for BLOCKED and READY threads
* [Quiz](../quiz/number-of-running-threads.md)

<img src="media/thread-states.svg" alt="Thread State Diagram" style="width:700px;"/>

A more detailed diagram is [here](./cool-extra-stuff.md#the-suspended-states)

---

### Context Switch - When?

* Voluntary - initiated by the running thread:
  * RUNNING thread performs a blocking action (eg: I/O call)
  * The thread calls `yield()` / `SwitchToThread()`
* Involuntary - initiated by the OS:
  * RUNNING thread ends
  * RUNNING thread's time slice expires
  * A thread with higher priority is READY

----

#### Context Switch - How?

![Context Switch and TCBs](media/context-switch-tcb.svg)

---

### Types of Threads

* CPU-intensive / CPU-bound = mostly CPU bursts:
  * compute the digits of Pi
  * compilers
  * machine learning
* I/O-intensive / I/O-bound = mostly I/O bursts:
  * servers
  * databases
  * text editors

----

#### IO-bound vs CPU-bound

* `demo/context-switch/cpu_bound.c`:

```[1 - 4]
student@os:~$ cat /proc/$(pidof cpu_bound)/status
[...]
voluntary_ctxt_switches:        13
nonvoluntary_ctxt_switches:     7
```

----

#### IO-bound vs CPU-bound

* `demo/context-switch/io_bound.c`:

```console
student@os:~$ cat /proc/$(pidof io_bound)/status
[...]
voluntary_ctxt_switches:        3729
nonvoluntary_ctxt_switches:     3
```

---

### Context Switch - Overhead

* Causes of overhead:
  * running the scheduler itself
  * flushing the [TLB](../../data/lecture) of the evicted thread is required
  * the new thread starts with an empty TLB
* Faster context switches between threads of the same process because their TLB is not flushed
