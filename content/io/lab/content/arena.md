# Arena

## Open File Structure in the Kernel

The "open file" `struct` in the Linux kernel is called [`struct file`](https://elixir.bootlin.com/linux/v6.0.9/source/include/linux/fs.h#L940)
Its most important fields are:

```c
struct file {
        struct path                     f_path;
        /* Identifier within the filesystem. */
        struct inode                    *f_inode;

        /**
         * Contains pointers to functions that implement operations that
         * correspond to syscalls, such as `read()`, `write()`, `lseek()` etc.
         */
        const struct file_operations    *f_op;

        /**
         * Reference count. A `struct file` is deallocated when this reaches 0,
         * i.e. nobody uses it anymore.
         */
        atomic_long_t                   f_count;

        /* Those passed to `open()`. */
        unsigned int                    f_flags;
        fmode_t                         f_mode;

        /* Cursor from where reads/writes are made */
        loff_t                          f_pos;
        /* To allow `f_pos` to be modified atomically. */
        struct mutex                    f_pos_lock;
}
```

As mentioned above, [`struct file_operations`](https://elixir.bootlin.com/linux/v6.0.9/source/include/linux/fs.h#L2093) contains function pointers that well-known syscalls such as `read()` end up calling.
Each filesystem needs to define its own implementations of these functions.
Some of the most widely known `file_operations` are listed below.
By now, you should recognise most of them:

```c
struct file_operations {
        loff_t (*llseek) (struct file *, loff_t, int);
        ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
        ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
        int (*mmap) (struct file *, struct vm_area_struct *);
        unsigned long mmap_supported_flags;
        int (*open) (struct inode *, struct file *);
        int (*flush) (struct file *, fl_owner_t id);
        int (*fsync) (struct file *, loff_t, loff_t, int datasync);
        int (*fasync) (int, struct file *, int);
}
```

## Mini-shell with Blackjack and Pipes

OK, there will be no Blackjack...
for now at least.
But there **will** be pipes.
Navigate back to `support/mini-shell/mini_shell.c` and add support for piping 2 commands together like this:

```console
> cat bosses.txt | head -n 5
Darkeater Midir
Slave Knight Gael
Nameless King
Dancer Of The Boreal Valley
Ancient Dragon
```

## To Drop or Not to Drop?

Remember `support/buffering/benchmark_buffering.sh` or `support/file-mappings/benchmark_cp.sh`.
They both used this line:

```bash
sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"
```

Note that `sync` has a [man page](https://linux.die.net/man/8/sync) and it partially explains what's going on:

> The kernel keeps data in memory to avoid doing (relatively slow) disk reads and writes. This improves performance

So the kernel does **even more [buffering](./io-internals.md#io-buffering)!**
But this time, it's not at the syscall level, like with `read()` and `write()`.
And it's used a bit differently.

While buffering is a means of either receiving data in advance (for reading) or committing it retroactively (for writing) to speed up subsequent syscalls that use the **next data**, caching is a means of speeding up calls that use the **same data**.
Just like your browser caches the pages you visit so you refresh them faster or your CPU caches your most recently accessed addresses, so does your OS **with your files**.

Some files are read more often than others: logs, some configs etc.
Upon encountering a first request (read / write) to a file, the kernel stores chunks of them in its memory so that subsequent requests can receive / modify the data in the RAM rather than waiting for the slow disk.
This makes I/O faster.

The line from which this discussion started invalidates those caches and forces the OS to perform I/O operations "the slow way" by interrogating the disk.
The scripts use it to benchmark only the C code, not the OS.

To see just how much faster this type of caching is, navigate to `support/buffering/benchmark_buffering.sh` once again and comment-out the line with `sudo sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"`.
Now run the script **a few times** and compare the results.
You should see some drastic improvements in the running times, such as:

```console
student@os:/.../support/file-mappings$ ./benchmark_cp.sh
make: Nothing to be done for 'all'.
Benchmarking mmap_cp on a 1 GB file...

real    0m13,299s
user    0m0,522s
sys     0m1,695s
Benchmarking cp on a 1 GB file...

real    0m10,921s
user    0m0,013s
sys     0m1,301s


student@os:/.../support/file-mappings$ ./benchmark_cp.sh
make: Nothing to be done for 'all'.
Benchmarking mmap_cp on a 1 GB file...

real    0m1,286s
user    0m0,174s
sys     0m0,763s
Benchmarking cp on a 1 GB file...

real    0m5,411s
user    0m0,012s
sys     0m1,201s
```

Each subsequent benchmark actually reads the data from the caches populated or refreshed by the previous one.

You can use `free -h` to view how much data your kernel is caching.
Look at the `buff/cache` column.
One possible output is shown below.
It says the OS is caching 7 GB of data.

```console
student@os:~$ free -h
              total        used        free      shared  buff/cache   available
Mem:           15Gi       8,1Gi       503Mi       691Mi       7,0Gi       6,5Gi
Swap:         7,6Gi       234Mi       7,4Gi
```
