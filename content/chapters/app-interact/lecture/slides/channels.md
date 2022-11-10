---

## Interaction Channels

---

App components interact via interaction channels.

----

### Interaction Types

- Sending / waiting for notifications (**synchronization**)
- Passing messages (**communication**)

----

### Reminder: App Components

- Threads and processes
- Processes may be colocated on the same system
- Processes may be distributed on multiple systems

----

### Interaction Use-Cases

- Inter-thread interaction (the same process)
- Inter-process colocated
- Inter-process distributed

---

### Synchronization

- One component waits, the other notifies
- A synchronization object is required
  - The object typically has a binary value: set or unset
- Notification may happen without a wait
  - Interruption of normal execution flow

----

### Synchronization

![Synchronization](./media/synchronization-generated.gif)

----

### Interruption

![Interruption](./media/interruption-generated.gif)

---

### Communication

- One component sends / writes data, the other receives / reads it
- A communication buffer is required
- Accessing the buffer
  - Directly, via memory address: shared memory
  - Indirectly, via endpoints (file descriptors)
    - Required for distributed communication

----

### Shared Memory

- Threads share the virtual address space of a process
  - Different threads use the same virtual address
- Processes use virtual memory to share a phyisical memory region
  - Different processes use different virtual addresses mapped to the same physical address
- Communication is not synchronized
  - Receiver doesn't know when data has been sent

----

### Shared Memory

![Shared Memory](./media/shared-memory.svg)

----

### Communication Channel

- Underlying buffer is not directly exposed
- Access via endpoints (file descriptors)
- The only mean for distributed communication
  - For distributed communication, there are multiple buffers: one on each host, buffers in middleboxes
- Synchronization is implicit
  - Reader is blocked (waits) until data is available
  - Writer is blocked (waits) until room is available
- Protocols are used to make communication reliable

----

### Communication Channel

![Communication Channel](./media/communication-channel.svg)
