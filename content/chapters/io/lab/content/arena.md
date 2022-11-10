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
