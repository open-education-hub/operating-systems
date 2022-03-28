---

## Mutual Exclusion

---

### Mutual Exclusion - Atomicity

* Access to a resource is restricted to a single thread
* Use **atomic** instructions provided by the ISA: (on x86: the `lock` prefix)
  * Eg: `lock inc dword [var]`
  * The CPU core has exclusive access to the cache and data bus while executing the instruction
* Use architecture-independent wrappers:
  * [GCC built-ins](https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html) (eg. `__atomic_add_fetch`)
  * libc functions from [`stdatomic.h`](https://en.cppreference.com/w/c/atomic) (eg. `atomic_flag_test_and_set`)

----

#### Atomicity in Action

* `demo/race-condition/race_condition_atomic_assembly.c`
* "inline assembly version" of `__atomic_add_fetch`
* similar running times

----

#### Mutual Exclusion - Spinlock

* Makes critical section **atomic**
* `lock` with **busy-waiting** - loop until you gain access (`lock == 1`):

```c
void spin_lock()
{
	while (atomic_flag_test_and_set(&lock))
		;
}
```

* `unlock` - simple assignment.
* The result is the same even with race conditions

```c
void spin_unlock()
{
	lock = 0;
}
```

----

#### Spinlock - Analysis

* Advantages:
  * Simple to implement
  * Fast when lock is (almost) immediately acquired
* Disadvantage:
  * Overhead: runs on the CPU while waiting for the lock (doing nothing)

---

### Mutual Exclusion - Mutex

```c [1 - 3 | 5 - 9 | 12 - 19 | 21 - 26]
struct mutex {
	/* Use internal lock for `atomic_flag_test_and_set`. */
	int lock;

	/**
	 * Store WAITING threads in this queue. Move one thread to READY when
	 * another one calls `mutex_unlock`.
	 */
	struct queue *queue;
};

void mutex_lock(struct mutex *m)
{
	while (atomic_flag_test_and_set(&m->lock)) {
        thread = current_thread();
		queue_push(m->queue, thread);
		move_to_waiting(thread);
    }
}

void mutex_unlock(struct mutex *m)
{
	m->lock = 0;
	thread = queue_pop(m->queue);
	move_to_ready(thread);
}
```

----

#### Mutex - Analysis

* Prevents overhead from busy-waiting
* Threads move to WAITING state while waiting for the lock
* Introduces overhead from context switch
* Releasing a mutex held by another thread is [**undefinded behaviour**](https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_lock.html)

----

#### Who Should Release the Lock?

![Locks Undefined Behaviour](./media/lock-undefined-behaviour.svg)

---

### Mutual Exclusion - Overhead

* The more complex the synchronization mechanism, the higher the overhead:

```console [1 - 2 | 3 - 4 | 5 - 6 | 7 - 8]
student@os:~/.../compute/lecture/demo/race-condition$ ./race_condition
var = 1232611; time = 14 ms
student@os:~/.../compute/lecture/demo/race-condition$ ./race_condition_atomic
var = 2000000; time = 31 ms
student@os:~/.../compute/lecture/demo/race-condition$ ./race_condition_spinlock
var = 2000000; time = 73 ms
student@os:~/.../compute/lecture/demo/race-condition$ ./race_condition_mutex
var = 2000000; time = 98 ms
```

* Why is the spinlock faster?
  * **Short** critical section, so the lock is acquired fast
  * The context switches performed by the mutex are costlier

----

#### Spinlock vs Mutex

| Spinlock                                 | Mutex                                    |
| :--------------------------------------- | :--------------------------------------- |
| Busy waiting                             | Yields CPU                               |
| Good for short critical sections         | Good for complex critical sections       |
| Only 1 thread can enter critical section | Only 1 thread can enter critical section |

----

### Critical Section - Granularity

* What if we place all the code in `increase_var` in a critical section?
* Short critical sections mean more frequent context switches
* Large critical sections mean less parallelism (code runs almost sequentially)

```console
student@os:~/.../compute/lecture/demo/granularity$ ./coarse_granularity
var = 2000000; time = 36 ms
student@os:~/.../compute/lecture/demo/granularity$ ./fine_granularity
var = 2000000; time = 1268 ms
```

---

### Deadlock

* Circular dependency
* Threads cyclically wait for each other

![Deadlock](./media/deadlock.svg)

```console
student@os:~/.../compute/lecture/demo/deadlock$ python3 deadlock.py
Thread 1: locked resource 1. Waiting for resource 2...
Thread 2: locked resource 2. Waiting for resource 1...
```
