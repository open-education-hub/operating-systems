---

## Programming Interface

---

### Summary of Channel Types

- Synchronization
- Interruption
- Shared memory
- Communication channels

---

### Synchronization

- Synchronization object
  - To be created / allocated before use
- mutex / spinlock / file locking: `lock()` / `unlock()`
- semaphore: `up()` / `down()`
- monitor / condition variable: `wait()` / `notify()`
- signals (Unix / Linux): `kill()` / `sigwait()`
- Generally used for inter-thread synchronization

----

### Inter-Process Synchronization

- Named semaphores
  - Entry in filesystem
- File locking
  - Uses actual file

----

### Synchronization Demos

In `./demo/lock/`

In `./demo/sync/`

---

### Interruption

- Asynchronous to normal execution flow
- Generally used for inter-process interaction on the same system
- Associate function handler to run when interruption is received
- signals (Unix / Linux): `sigaction()`, `kill()`, `sigqueue()`, `sigsuspend()`
- exceptions (Windows): `AddVectoredExceptionHandler()`, `RaiseException()`

---

### Interruption Demos

In `./demo/interrupt/`

---

### Shared Memory

- Implicit for inter-thread communication
- Explicit API for processes
  - Create shared memory mapping
  - Filesystem entry as backing store
- No API for using it
  - Just use memory operations

----

### Shared Memory Demos

In `./demo/shared-mem/`

---

### Communication Channels

- Discussed in I/O chapter, socket-like
- Created before-hand
- `read()` / `write()`, `send()` / `recv()`
- (anonymous) pipes: related processes
- named pipes (filesystem entry): any colocated processes
- UNIX / local sockets (filesystem entry): any colocated processes
- network sockets: colocated or distributed processes

----

### Communication Channels

In `./demo/comm-channels/`

----

### Case study: Our Own Server

- Server computes Fibonacci, sends it back
- single-process server
- multi-threaded server: uses a thread per-connection
- multi-process server: use a process per-connection
- thread-pool server: uses pre-created threads to serve
- process-pool server: use pre-created processes to serve

----

## Case study: Our Own Server

In `./demo/fibonacci-server/`
