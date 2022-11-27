## File Interface

---

### File Interface - `open()`

![open](./media/file-interface-open.svg)

----

- Creates a new session to communicate with the file
- Returns a **file handle** - used to reference the **communication channel**

---

### File Descriptor

- In higher level languages the file handle is an object that allows working with files
- Implementation-wise, it is an integer between **0** and **1023**
- To keep track of open files, each process holds a **FDT (File Descriptor Table)**
- Each entry in the **FDT** is either null or a pointer to an **Open File Structure**

----

### File Descriptor Table

![File Descriptor Table](./media/file-descriptor-table.svg)

----

### Open File Structure

- Contains:
  - Permissions
  - The offset inside the file
  - Number of handles referencing it
  - **inode** (pointer to data and metadata)
- The OS keeps track of all **Open File Structures** and stores them in the **Open File Table**

---

### File Interface - `read()`/`write()`

![read write](./media/file-interface-read-write.svg)

----

### File Interface - `read()`

- Uses the **file handle** to read bytes
- Return number of read bytes
  - **-1**    - read failed
  - **0**     - EOF reached
  - **< num** - partial read

----

### File Interface - `write()`

- Uses the **file handle** to write bytes
- Return number of written bytes
  - **-1**    - write failed
  - **< num** - partial write

---

### File Interface - `close()`

![close](./media/file-interface-close.svg)

----

- Decrements the reference count in the Open File Structure
  - Deletes the Open File Structure if the reference count is 0
- Flushes OS buffers

---

### File Interface - `lseek()`

![lseek](./media/file-interface-lseek.svg)

----

- Uses the **file handle** to update the **offset** in file
- Returns the new **offset** in file
  - **-1** on error

----

### Sparse file

What happens if the **offset** is bigger than the file size?

- `demo/file-interface/sparse-file.c`

---

### File Interface - `ftruncate()`

![ftruncate](./media/file-interface-ftruncate.svg)

----

- Truncates the file indicated by the **file handle** to the indicated **length**
- If the file size is smaller than **length**, the file is extended and "filled" with binary zeros to the indicated **length**

----

### `ftruncate()` demo

- `demo/file-interface/truncate.c`

---

### File Interface in Python

- `demo/file-interface/py-file-ops.py`

----

### File Interface in C

- `demo/file-interface/c-file-ops.c`

---

### File Interface - `dup()`

![dup](./media/file-interface-dup.svg)

----

- Results in two **file handles** that refer the same Open File Structure
  - Duplicates a file descriptor into the smallest unused file descriptor

----

### `open()` vs `dup()` demo

- `demo/file-interface/open-vs-dup.c`
- `demo/file-interface/close-stdout.c`
  - What could go wrong between **closing** `stdout` and **calling dup**?
  - "Everything."

----

### File Interface - `dup2()`

- Duplicates a file descriptor into a **designated** file descriptor
- If the new file descriptor is open, it will be closed before being reused
  - This action will be performed **atomically**
