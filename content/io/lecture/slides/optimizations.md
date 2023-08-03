## IO Buffering

---

## `libc` Buffering

----

### `stdout` vs `stderr`

- `demo/optimizations/stdout-vs-stderr.c`

----

### Investigate

```console
student@os:~/.../demo/optimizations$ ./stdout-vs-stderr
Join the dark side!
Hello from the other side!
```

- Not what we expected

```console
strace --trace=write ./stdout-vs-stderr
```

----

### Observations

- Each print to `stderr` results in a `write()`
- Prints to `stdout` result in one single `write()`

----

### Behind The Scenes

- Printing to `stdout` is **buffered** to avoid multiple context switches
- The same is not true for `stderr` as we want to see errors as they occur

----

### Does It Work?

- Attempt to write **10000 bytes** to a file, **1 byte** at a time
  - `demo/optimizations/fwrite-10000.c`
  - `demo/optimizations/write-10000.c`

----

### Can We Do More?

---

## Kernel Buffering

----

### Context

- `libc` buffering reduces the number of context switches
- But **synchronizing** the disk after every `write()` is a major bottleneck

----

### Kernel Buffer

- Same as idea as `libc`
- Each `write()` fills a buffer in kernel space
- Transfer data to disk when
  - Buffer is full
  - `fsynk()` is called
  - Enough time has passed since the last `write()`

```console
student@os:~$ cat /proc/sys/vm/dirty_expire_centisecs
3000
```

----

### Overview

![IO Buffering Overview](./media/io-buffering-overview.svg)

----

### Does It Work?

- Write **10000 bytes** to disk, **1 byte** at a time - with buffering
  - `demo/optimizations/write-10000.c`
- Write **1000 bytes** to disk, **1 byte** at a time - without buffering
  - `demo/optimizations/write-1000-unbuf.c`

---

## IO Buffering Drawbacks

- Transfer of information between kernel buffers requires user space transitions
- Operations might **block**
  - Read when buffer is empty
  - Write when buffer is full

---

## Kernel Buffers Transfer

![Repeated Copy](./media/repeated-copy.svg)

----

### Obvious Problems

- We have an intermediary buffer
  - Data from **read buffer** is copied to **application buffer**
  - Data from **application buffer** is copied to **socket buffer**
- We perform two context switches

----

### `zero-copy`

![Zero-copy](./media/zero-copy.svg)

----

- `sendfile()` instructs kernel to copy data from one of its buffers to another
- We perform a single context switch
- Data is copied a single time

---

## Blocking IO

- Reading from an empty buffer
  - The kernel buffer is filled with information from the device
  - The library buffer is filled from the kernel buffer
  - `read()` operation resumes
- What happens if the device has no information to share?
  - `read()` **blocks**

----

### Non-Blocking IO

- `O_NONBLOCK` makes operations return rather than block
  - `SOCK_NONBLOCK` for sockets
- Allows handling of input on multiple file descriptors
  - Does not scale with number of file descriptors
  - The thread is busy waiting instead of entering WAITING state
  - Ugly

---

## `epoll` Interface

- Linux interface, non-portable
- Kernel keeps an internal structure to monitor file descriptors
- The thread enters WAITING state until new connections emerge
- User updates the interface using the exposed interface
  - `epoll_create()`
  - `epoll_ctl()`
  - `epoll_wait()`

----

### `epoll_create()`

![epoll_create()](./media/epoll-create.svg)

---

### `epoll_ctl()`

![epoll_ctl()](./media/epoll-ctl-1.svg)

----

#### `epoll_ctl()`

![epoll_ctl()](./media/epoll-ctl-2.svg)

----

#### `epoll_ctl()`

![epoll_ctl()](./media/epoll-ctl-3.svg)

----

#### `epoll_ctl()`

![epoll_ctl()](./media/epoll-ctl-4.svg)

----

#### `epoll_ctl()`

![epoll_ctl()](./media/epoll-ctl-5.svg)

----

#### `epoll_ctl()`

![epoll_ctl()](./media/epoll-ctl-6.svg)

---

### `epoll_wait()`

![epoll_wait()](./media/epoll-wait.svg)

---

## Asynchronous IO

---

## Client-Server 2.0

- Real-life applications use **Client-Server** model
- But they take into consideration scalability
- Let us see what it takes to go from 1 client to **8**
  - Use `demo/optimizations/client.py` for the client implementation
  - Use `demo/optimizations/client_bench.sh` to compare implementations

----

### Trivial Server

- Run server in a loop
- `demo/optimizations/server.py`

----

### Good Old Processes

- Create a process to handle each new client
- `demo/optimizations/mp_server.py`

----

### Good Old Lightweight Processes

- Create a process to handle each new client
- `demo/optimizations/mt_server.py`

---

### Asynchronous IO

- `demo/optimizations/async_server.py`

----

- The python asynchronous interface abstracts a lot of the functionality
- The idea behind:
  - The server socket is added to an **epoll instance**
  - The specified **handle** is called for each event (new connection)
