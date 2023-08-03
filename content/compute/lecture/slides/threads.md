---

## Threads

---

### Threads - Backstory

* You have an application that applies filters to a set of images
* If we used processes to spread the work:
  * images (like all data) would be marked copy-on-write
  * processes cannot easily modify the "shared" images
* **Solution:** use threads
  * No copy-on-write: threads share the heap and data sections

----

#### Threads - Definitions

* Scheduling unit
* Lightweight processes (LWP)
* Each process has at least one thread

---

### App, Process, Thread - The Bigger Picture

* [Quiz](../quiz/threads-shared-data.md)

![Application Architecture](media/app-process-thread.svg)

---

### Process vs Thread

| PROCESS                          | THREAD                               |
| :------------------------------- | :----------------------------------- |
| independent                      | part of a process                    |
| isolated VAS                     | shares VAS with other threads        |
| slower creation                  | faster creation                      |
| larger context switch duration   | shorter context switch duration      |
| ending means ending all threads  | other threads continue when finished |

----

#### Process vs Thread

`demo/create-thread/create_thread.py`

vs

`demo/create-process/create_process.py`
