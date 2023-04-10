---

## Scheduling Algorithms

---

### Scheduling - Ideals

* **Interactivity:** decrease time spent in READY
  * low waiting time
  * also known as **fairness**
* **Throughput:** finish threads as quickly as possible
  * low turnaround time

----

#### Scheduling - Reality

* There is no free lunch
* Trade-off between interactivity and throughput

----

#### Types of Schedulers

* **Cooperative:** only allow voluntary context switches
  * Advantage: Simple to implement
  * Disadvantage: starvation - a thread might never yield its CPU core
* **Preemptive:** also allows involuntary context switches
  * Each process can run at most a certain _time slice_
  * When it expires, a context switch is triggered

----

#### Scheduling Algorithms - The Bigger Picture

* **Round-Robin**:
  * Push each new thread to a queue
  * Every time slice, dequeue one thread, run it, then reenqueue it
  * Threads run in the order in which they're spawned

----

#### Scheduling Algorithms - The Bigger Picture

* **Completely Fair Scheduler (CFS)**:
  * Add new threads to a red-black tree sorted by total running time
  * Every time slice, remove, run and add the thread that has run the least back to the tree
  * Each thread runs approximately the same amount of time

---

### Scheduling Algorithms - Round-Robin

1. Add each new thread to a queue
1. Remove one thread from the queue and run it
1. The thread runs until finished or until its time slice ends
1. If the thread is not finished, add it back to the queue
1. Repeat from step 2

----

#### Round-Robin - Example

| Process | Running time |
| :-----: | :----------: |
| P1      | 4            |
| P2      | 3            |
| P3      | 5            |

* Assume a time slice of 2

----

#### Round-Robin - Live Scheduling

![Round-Robin Scheduling](./media/round-robin-generated.gif)

----

#### Round-Robin - Analysis

* Large time slice:
  * high throughput (fewer context switches)
  * low fairness (threads at the back of the queue spend more time in READY)
* Small time slice:
  * low throughput
  * high fairness

---

### Round-Robin - Real Life (Unikraft)

* [Cooperative scheduler](https://github.com/unikraft/unikraft/blob/staging/lib/ukschedcoop/schedcoop.c)
* Lists used as queues for READY and WAITING processes:

```c
struct schedcoop_private {
	struct uk_thread_list thread_list;
	struct uk_thread_list sleeping_threads;
};
```

* `yield` means scheduling another thread:

```c
static void schedcoop_yield(struct uk_sched *s)
{
	schedcoop_schedule(s);
}
```

----

#### Cooperative Scheduler - Demo

* First, run `./do.sh setup && ./do.sh build`
* Without calling `uk_sched_yield`, Thread 1 runs until finished:

```console [1 - 12 | 14 - 25]
student@os:~/.../demo/cooperative-scheduling$ ./do.sh run_nocoop
[...]
Thread 1 created!
Thread 1: step 0
Thread 1: step 1
Thread 1: step 2
Thread 1 finished!
Thread 2 created!
Thread 2: step 0
Thread 2: step 1
Thread 2: step 2
Thread 2 finished!

student@os:~/.../demo/cooperative-scheduling$ ./do.sh run_coop
[...]
Thread 1 created!
Thread 1: step 0
Thread 2 created!
Thread 2: step 0
Thread 1: step 1
Thread 2: step 1
Thread 1: step 2
Thread 2: step 2
Thread 1 finished!
Thread 2 finished!
```

---

### Completely Fair Scheduler (CFS)

* Schedule the thread that has run **the least amount of time (vruntime)**
* Store READY threads in a **Red-Black Tree**, sorted by **vruntime**
* Use time slices, like Round-Robin
* During a context switch:
  * If the currently RUNNING task is over, terminate it
  * Otherwise, increase its vruntime and add it to RBTree
  * Move the **leftmost** thread in RBTree to RUNNING

----

#### CFS - Analysis

* Context switch complexity:
  * Add thread to RBTree: `O(log(num_threads))`
  * Extract leftmost thread in the RBTree: `O(1)` (keep a pointer to it)
  * Overall complexity: `O(log(num_threads))`
* Time slice size: same tradeoff as Round-Robin

---

### Fixed Priority Scheduling

* Each thread has a priority
* Threads with higher priority run more often
* Threads with lower priority are starved
* Easier to implement

----

#### Fixed Priority Scheduling - `nice`

* Lower `nice`-ness = higher priority
* Values in `[-20, 19]`

```console [1 - 2 | 3 - 8 | 9 - 10 | 11 - 12]
student@os:~$ nice -10 bash &
[1] 5753
student@os:~$ ps -e -o pid,ni,comm
  PID  NI COMMAND
    1   0 init
 [...]
 5753  10 bash
 5752   0 ps
student@os:~$ sudo renice -n -20 -p 5753
5753 (process ID) old priority 10, new priority -20
student@os:~$ ps -e -o pid,ni,comm | grep 5753
 5753 -20 bash
```

----

#### Priority-Based Round-Robin

* The scheduler keeps a list of queues, one for each priority
* During a context switch, the new RUNNING thread is chosen from the highest priority non-empty queue

![Priority-Based Round-Robin](media/priority-round-robin.svg)

---

### Dynamic-Priority Scheduling

* Problems with static priorities:
  * Low-priority threads are starved
  * Unfair for I/O bound threads
* Solution:
  * Decrease priority of RUNNING threads
  * Increase priority of WAITING threads
