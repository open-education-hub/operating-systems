## Devices

---

### I/O Devices

- A hardware component that communicates with our application through bytes
- Various devices fit this description

----

![mouse keyboard](./media/dev-mouse-keyboard.png)

----

![hard disk](./media/dev-storage.png)

----

![sensors](./media/dev-sensors.png)

----

![devices](./media/devices.png)

How does the OS operate them?

---

### Device Types

| Char Devices          | Block Devices             |
| :-------------------: | :-----------------------: |
| read/write one byte   | read/write blocks of data |
| slow                  | fast                      |
| no seek             	| seek	                    |
| no buffering          | buffering                 |

----

### Representing I/O Devices

![char and block devices](./media/char-block-devices.svg)

Linux abstracts an I/O device as a **special file**

----

### Device Special Files

- Device files are in `/dev`
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

----

### Device Types demo

- `demo/devices/read-from-device.sh`

---

### Using Devices

- Devices are abstracted as files and follow the **File Interface**
  - Can we simply read to a device?

```console
student@OS:~$ cat /dev/input/mouse1
```

----

If not friend, why friend shaped?

![snow leopard](./media/snow-leopard.png)

----

### Software Stacks All Over Again

![Device Software Stack](./media/device-software-stack.svg)

----

- The **file abstraction** and **file interface** are only the middle part
- The overlay is a **communication protocol** describing how to **encode**/**decode** data
- The underlay is the **driver interface** communicating with the device through control codes

----

### `ioctl()` - I/O Control

- General purpose interface that uses **control codes** to communicate directly with the device driver
- Might be used for every IO operation
- **Not intuitive**: requires knowledge on how the device communicates
- **Not portable**: arguments depend on the OS version and the device

----

### `ioctl()` demo

- `demo/devices/hwaddr-ioctl.c`
- `demo/devices/filesystem-size.c`

---

### Virtual Devices

- Not all device files in `/dev` have a corresponding physical device
  - e.g.: `/dev/zero`, `/dev/null`
- We can fully cover their behaviour using software

----

### `read()` from `/dev/null`

```c
static ssize_t read_null(struct file *file, char __user *buf,
			size_t count, loff_t *ppos) {
	return 0;
}
```

----

### `write()` to `/dev/null`

```c
static ssize_t write_null(struct file *file,
      const char __user *buf, size_t count, loff_t *ppos) {
	return count;
}
```

----

### `read()` from `/dev/zero` (simplified)

```c
static ssize_t read_zero(struct file *file, char __user *buf,
			 size_t count, loff_t *ppos) {
	size_t cleared = 0;

	while (count) {
		size_t chunk = min_t(size_t, count, PAGE_SIZE);
		size_t left = clear_user(buf + cleared, chunk);

		cleared += chunk;
		count -= chunk;
	}

	return cleared;
}
```

----

### `write()` to `/dev/zero`

```c
static ssize_t write_zero(struct file *file,
      const char __user *buf, size_t count, loff_t *ppos) {
	return count;
}
```
