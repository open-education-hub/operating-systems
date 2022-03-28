---

## `fork()`

---

### `fork()`

* Spawns child process
* Child process starts execution right after the call to `fork()`
* Returns twice
  * `0` in child process
  * Child's PID in parent process
* [Quiz](../quiz/process-creation.md)
* Initially child and parent share the same PAS (Physical Address Space)
* Child's writable pages are marked **copy-on-write**

----

#### `fork` and Threads

* `fork` also creates a new thread...
* ... but part of a different process

![fork - new Thread](./media/fork-thread.svg)
