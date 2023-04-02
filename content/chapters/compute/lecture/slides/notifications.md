---

## Notifications

---

### Locks vs Notifications

![Lock vs Notification](./media/lock-vs-notify.svg)

----

#### Locks vs Notifications

* Locks:
  * isolate **critical sections**
  * thread that calls `unlock()` must hold the lock

* Notifications (conditions and semaphores):
  * one thread waits for an **event**
  * **another thread** notifies waiting thread on event completion

----

#### Two Types of Primitives

1. For mutual exclusion:

* mutexes, spinlocks
* methods: `lock()` and `unlock()`

1. For ordering:

* semaphore, condition variables
* methdos: `wait()` and `notify()`

---

### Semaphores

* Atomic counter
* Counter can take values greater than 1
* `acquire() ~ counter--`:
  * Returns if `counter > 0`
  * Thread blocks if `counter == 0`
* `release() ~ counter++`:
  * Signals waiting threads

---

### Condition Variables

* More complex synchronization logic
* Similar to but more flexible than semaphores
* A thread is suspended until a condition (logical predicate) is met
* Always used with mutexes (evaluating the condition is **not atomic**)

----

#### Condition Variables - API

* `wait`: suspend the thread until the condition is met
  * need to acquire the lock before waiting
  * this is needed to check the condition in a thread-safe manner
  * `wait` releases the lock

```python
cond.acquire()
cond.wait()
```

* `notify`: wake up **one** thread waiting on the condition
* `notify_all`: wake up **all** threads waiting on the condition

* If no thread is woken up (because none is waiting), the notification has no effect!

----

#### Condition Variables - Demo

```console
student@os:~/.../compute/lecture/demo/condition$ python3 condition.py
Waiting thread: waiting for main thread...
Main thread: type "notify" to notify waiting thread

waiting thread is sleeping until woken up by main thread

notify
Waiting thread: notified by main thread
```
