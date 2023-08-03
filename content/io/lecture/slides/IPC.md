### Interprocess Communication

---

### Interprocess Communication

- A communication channel involves a process and a data endpoint
- We can use persistent data and I/O devices as endpoints with the **file interface**
- Another possible endpoint is a **process**
  - [Law of the hammer](https://en.wikipedia.org/wiki/Law_of_the_instrument)
  - Socket interface

----

### IPC - File Interface

![IPC through File Interface](./media/IPC-file-interface.svg)

- Writing to disk and reading from disk is tedious

----

### IPC - Pipe

![IPC through pipe](./media/IPC-pipe.svg)

- Same idea as above

----

- **Proc1** writes at one end
- **Proc2** reads from the other end
  - Why is it better?
  - The **pipe** is stored in Kernel Space, we no longer use the disk
- Only works for related processes ([fork](https://man7.org/linux/man-pages/man2/fork.2.html))

----

### Pipe - Walkthrough

![Pipe walkthrough - 1](./media/pipe-walkthrough-1.svg)

----

### Pipe - Walkthrough

![Pipe walkthrough - 2](./media/pipe-walkthrough-2.svg)

----

### Pipe - Walkthrough

![Pipe walkthrough - 3](./media/pipe-walkthrough-3.svg)

----

### Pipe - Walkthrough

![Pipe walkthrough - 4](./media/pipe-walkthrough-4.svg)

----

### Pipe - Walkthrough

![Pipe walkthrough - 5](./media/pipe-walkthrough-5.svg)

----

### `pipe()` demo

- `demo/IPC/pipe.c`

---

### IPC - Named Pipe (FIFO)

- Bypass unnamed pipes limitations:
  - Can be used by more than 2 processes
  - Can be used by unrelated processes
- Stored on disk as a **special file**

```console
student@os:~$ ls -l my_fifo
prw-r--r-- 1 student student 0 nov 22 18:38 my_fifo
```

----

### `mkfifo()` demo

- `demo/IPC/fifo.c`

---

### IPC - Socket Interface

![Socket Interface](./media/socket-interface.svg)

----

### Socket

- The endpoint in the interprocess communication
- Uniquely identifies the process in the communication
- Supports multiple transmission types
  - e.g.: `stream`, `datagram`

----

### Socket Interface - `socket()`

![socket()](./media/socket-interface-socket.svg)

----

- Creates a socket with given **domain** and **type**
- Returns a **file descriptor**
  - Compatible with `read()`/`write()` operations
  - Does not support `fseek`

----

### Socket Attributes

- **Domain**
  - `AF_UNIX` for communication on the **same host**
  - `AF_INET` for communication over the internet
- **Type**
  - **Stream** establishes a reliable connection and ensures all data is transmitted
  - **Datagram** sends data faster without checking its integrity

----

### Stream and Datagram

![Stream and Datagram simplified](./media/stream-datagram-simplified.png)

---

### Client-Server

- Socket communication uses the **client-server** model
- **Server**
  - **Bound** to an **address** and **accepts** connections
  - Answers queries from clients
- **Client**
  - **Connects** to a server using its **address**
  - Sends queries to the server

---

### Server Workflow

----

#### Server - `socket()`

![socket()](./media/socket-interface-socket.svg)

- Create socket

----

#### Server - `bind()`

![bind()](./media/socket-interface-bind.svg)

- Assign address to the socket

----

#### Server - `listen()`

![listen()](./media/socket-interface-listen.svg)

- Mark the socket **passive** - will be used to accept connections

----

#### Server - `accept()`

![accept()](./media/socket-interface-accept.svg)

- Wait for a connection
- Accept the connection and create a socket for it

---

### Client Workflow

----

#### Client - `socket()`

![socket()](./media/socket-interface-socket.svg)

- Create a socket

----

#### Client - `connect()`

![TCP socket](./media/socket-interface-connect.svg)

- Establish connection with server

---

### `send()`/`recv()`

![Socket send recv](./media/socket-interface-send-recv.svg)

- Same as `read()`/`write()`

----

#### `send()`

- Use socket to send bytes
- Return number of sent bytes
  - **-1** - send failed
  - **<num** - partial send

----

#### `recv()`

- Use socket to receive bytes
- Return number of received bytes
  - **-1** - recv failed
  - **0** - connection end (similar to EOF)
  - **<num** - partial recv

---

### Unix Socket

- Used in communication on the **same host**
- Uses a **special file** on disk as the address
  - Server is `bound` to the file
  - Client `connects` to the server using the file

```console
student@os:~/.../demo/IPC$ ls -l
srwxrwxr-x 1 student student    0 dec  2 16:03 unix_socket
```

----

### Unix Socket demo

- `demo/IPC/unix_socket_server.c`
- `demo/IPC/unix_socket_client.c`

---

### IP Sockets

- Used in communication on **different hosts**
- Each host is identified by an [**IP address**](https://ocw.cs.pub.ro/courses/uso/laboratoare/laborator-05)
- For a host to support multiple applications that require network connection we use **ports**
  - A port is an integer between **0** and **65536**
- An application is identified by an IP address and a port
  - e.g.: `217.182.27.243:25565`

----

### Stream Socket demo

- `demo/IPC/stream_socket_server.c`
- `demo/IPC/stream_socket_client.c`

----

### Datagram Socket demo

- `demo/IPC/datagram_socket_server.c`
- `demo/IPC/datagram_socket_client.c`

---

### Socket Summary

![Socket Summary](./media/socket-summary-generated.gif)
