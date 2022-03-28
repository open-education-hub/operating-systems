---

## Barrier

---

### Barrier

* The code before the barrier is executed by **all threads** before the code after the barrier
* Threads move to WAITING upon reaching the barrier
* Threads move back to READY when the last thread reaches the barrier

----

#### Barrier - Demo

```console [1 - 7 | 9 - 16]
student@os:~/.../compute/lecture/demo/barrier$ python3 barrier.py
Before barrier: thread name = thread-0
After barrier: thread name = thread-0
Before barrier: thread name = thread-2
After barrier: thread name = thread-2
Before barrier: thread name = thread-1
After barrier: thread name = thread-1

student@os:~/.../compute/lecture/demo/barrier$ python3 barrier.py --use-barrier
Before barrier: thread name = thread-0
Before barrier: thread name = thread-1
Before barrier: thread name = thread-2
After barrier: thread name = thread-2
After barrier: thread name = thread-0
After barrier: thread name = thread-1
```

* Notice that threads reach the barrier and end in arbitrary order
