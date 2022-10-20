### Interprocess Communication

<!-- TODO: Talk about the 2 possible endpoints: storage/devices and sockets -->
- Using persistent data and I/O devices we can feed data to our application
- But we are still limited when transmiting data between processes

----

### IPC - Basic

![bad IPC](./media/bad-IPC.svg)

- Writing to disk and reading from disk is tedious

----

### IPC - Unnamed Pipe

![unnamed pipe IPC](./media/unnamed-pipe-IPC.svg)

- Same idea as above

----

### IPC - Unnamed Pipe(2)

- Proc1 writes at one end and Proc2 read from the other end
  - Why is it better?
  - **pipe** is stored in kernel space, we do not work directly with disk
- Only works for related processes ([fork](https://man7.org/linux/man-pages/man2/fork.2.html))

----

### IPC - Named Pipe (FIFO)

- Bypass unnamed pipes limitations:
  - Works for unrelated processes
  - Multiple processes can use it
  - Not bound to the process life span
- Stored on disk to be reused
- Might be used over network

----

### IPC - Socket

- Allows interprocess communication over network
  - Connects to a remote socket identified by address and port
- Allows for the connection to be configured (protocol)
