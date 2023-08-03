---

## Processes

---

### Processes

* A process is a **running program**
  * It is a collection of resources (Memory, CPU, I/O) and abstractions over them (VAS, threads, file descriptors)
* An application can spawn multiple processes
* The OS allows each [thread](./threads.md) to run on a **core** for a few milliseconds (time slice)
* Then the OS pauses the thread and replaces it with another one (context switch)

----

#### What We Want

* Run more apps than cores
* Use resources efficiently:
  * Memory: isolated data
  * CPU: low idle times
  * I/O: responsiveness

----

#### Resource Management - Overview

![Resource Management](media/resource-management.svg)

----

#### What We Don't Want

* Unresponsive processes
* Processes monopolizing resources
* System freezes

---

### Process Address Space

* Each process has its own **Virtual Address Space (VAS)**:
  * Isolation
  * The process "thinks" it uses the entire address space

----

#### Process Virtual Address Space

![Process VAS](media/vas.svg)

---

### Process Attributes - from User Space

* PID: numeric identifier
* PPID: parent's PID (one parent per process)
* running time
* threads

```console
student@os:~/.../compute/lecture/demo/create-process$ python3 create_process.py
[parent] PID = 186411
[parent] Before starting, child PID = None
[parent] After starting, child PID = 186412
[child] PID = 186412; PPID = 186411
[child] Message from parent: OS Rullz!
```
