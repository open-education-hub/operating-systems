## Devices

---

### I/O Devices

- A hardware component that communicates with our application through bytes
- Various devices fit this description:

----

![mouse keyboard](./media/dev-mouse-keyboard.png)

----

![hard disk](./media/dev-storage.png)

----

![sensors](./media/dev-sensors.png)

----

![devices](./media/devices.png)

How does the OS operates them?

---

### Device Types

| Char Devices                      | Block Devices                               |
| :-------------------------------: | :-----------------------------------------: |
| read/write one byte               | read/write blocks of data                   |
| slow                              | fast                                        |
| no search                         | search                                      |
| no buffering                      | buffering                                   |

----

### Representing I/O Devices

![char and block devices](./media/char-block-devices.svg)

Linux abstracts an I/O device as a **special file**

----

### Device Special Files

- Device special files are in `/dev`
- The letter before permissions describes the file type

```console
student@OS:~$ ls -l /dev/
crw-rw-rw-   1 root root      1,   3 nov  6 20:31 null
crw-rw-rw-   1 root root      1,   8 nov  6 20:31 random
brw-rw----   1 root disk      8,   1 nov  6 20:31 sda1
brw-rw----   1 root disk      8,   2 nov  6 20:31 sda2
brw-rw----   1 root disk      8,   5 nov  6 20:31 sda5
brw-rw----   1 root disk      8,   6 nov  6 20:31 sda6
crw-rw-rw-   1 root tty       5,   0 nov  6 20:31 tty
crw-rw-rw-   1 root root      1,   9 nov  6 20:31 urandom
crw-rw----+  1 root video    81,   0 nov  6 20:31 video0
crw-rw----+  1 root video    81,   1 nov  6 20:31 video1
crw-rw-rw-   1 root root      1,   5 nov  6 20:31 zero
...
```
