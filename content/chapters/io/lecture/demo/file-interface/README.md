# File Interface

These are some examples on the IO interface.

## Build

To build the C examples on Linux, run `make`.

## Running

### Sparse file

We open a file write some bytes, make a jump using `lseek()` and repeat two times.
Zones between writes are empty, yet the total size of the `sparse.dat` keeps track of them.

Follow this example using the following command to track `sparse.dat` file size.

```console
student@os:~/.../demo/file-interface$ watch -n 0.5 ls -l sparse.dat
```

Expected output:

```console
# After the first write
-rw-r--r-- 1 student student 1024 nov 19 15:43 sparse.dat
# After the second write
-rw-r--r-- 1 student student 3072 nov 19 15:43 sparse.dat
# After the third write
-rw-r--r-- 1 student student 5120 nov 19 15:43 sparse.dat
```

### Truncate

We open `fake-gargantua.dat` for write and use `ftruncate()` to set its size to `20GB`.
This only impacts the metadata of the file, so the size (number of used blocks) stays **0**.

Expected output:

```console
student@os:~/.../demo/file-interface$ ./truncate
 * Open an empty file for writting
 -- Press ENTER to continue ...

 * Use truncate to update the file length to 20GB
 -- Press ENTER to continue ...

 * Use fstat to read file information
 -- Press ENTER to continue ...

file size is: 21474836480
number of blocks is: 0
 * Close file
 -- Press ENTER to continue ...
```

### Python file ops

We open `f.txt` and write **1024 bytes** to it.
We go backwards **512 bytes**, read **256 bytes**, then truncate it to **256 bytes**.

Analysing the file offset and file size through the example we obtain:

```console
operation       |   offset  |   size    |
*---------------------------------------*
write 1024      |   1024    |   1024    |
lseek -512      |   512     |   1024    |
read 256        |   768     |   1024    |
ftruncate 256   |   768     |   256     |
```

**ftruncate** does not modify the file offset, so a future `write()` action would write at offset **768** creating a **sparse file**.

### C file ops

**Same as [Python file ops](#python-file-ops)**.

### open vs dup

We open a file twice using `open()` and duplicate the first descriptor using `dup()`.
We attempt to read some bytes from each of the three file descriptors.

The read on the first file descriptor only influenced the duplicated file_descriptor.
They use the same open file strcucture to keep track of the offset in file.

Follow the list of open files from the `proc` view:

```console
student@os:~/.../demo/file-interface$ watch -n 0.5 'ls -l /proc/$(pidof open-vs-dup)/fd | sort -nk 9'
```

Expected output:

```console
student@os:~/.../demo/file-interface$ ./open-vs-dup
...
 * Read 23 bytes from first file descriptor
 -- Press ENTER to continue ...

A wizard is never late,

 * Read 23 bytes from the second file descriptor
 -- Press ENTER to continue ...

A wizard is never late,

 * Read 23 bytes from the duplicated file descriptor
 -- Press ENTER to continue ...

 nor is he early.
```

### close stdout

We open a `my_stdout.txt`, close the `stdout` and then use `dup()` to duplicate the file descriptor.
As a result, the duplicated file descriptor will be assigned value **1 (value of STDOUT_FILENO)** as it is the first unused file descriptor.

Between the closing of `stdout` and call to `dup()`, the file descriptor 1 does not point to any **Open File Structure** so the message `Duplicate the file descriptor` will fail to print.
After the calling `dup()`, the output will be redirected to `my_stdout.txt`.

Follow the list of open files from the `proc` view:

```console
student@os:~/.../demo/file-interface$ watch -n 0.5 'ls -l /proc/$(pidof close-stdout)/fd | sort -nk 9'
```

Expected output:

```console
student@os:~/.../demo/file-interface$ ./close-stdout
* Open file
 -- Press ENTER to continue ...

 * Close stdout
 -- Press ENTER to continue ...

# Use cat to display the final output
student@os:~/.../demo/file-interface$ cat my_stdout.txt
This will go to stdout
 * Close the file descriptors
 -- Press ENTER to continue ...
```
