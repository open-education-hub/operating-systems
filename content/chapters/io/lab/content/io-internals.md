# I/O Intenals

Now we will take a short look at how the file descriptors you've just learnt about are handled in libc.
The Software Stack chapter has taught us that applications generally interact with libraries which expose wrappers on top of syscalls.
The most important library in a POSIX system (such as Linux) is libc.
Among many others, it provides higher-level abstractions over I/O-related syscalls.

**Musl** (read just like "muscle") is a lightweight implementation of libc, which exposes the same API that you have used so far, while also being fit for embedded and OS development.
For example, [Unikraft](https://unikraft.org/) [unikernels](https://unikraft.org/docs/concepts/) may [use musl](https://github.com/unikraft/lib-musl).

First, it provides a `struct` that groups together multiple data that is necessary when handling files.
We know from the example in `support/simple-file-operations/file_operations.c` that the file handler employed by libc is `FILE *`.
`FILE` is just a `typedef` for [`struct _IO_FILE`](https://elixir.bootlin.com/musl/v1.2.3/source/src/internal/stdio_impl.h#L28).
Here are the most important fields in `struct _IO_FILE`:

```c
struct _IO_FILE {
        int fd;         /* File descriptor */      
        
        unsigned flags; /* Flags with which `open()` was called */

        int mode;       /* File permissions; passed to `open()` */

        off_t off;      /* File offset from where to read / write */

        /**
         * Internal buffer used to make fewer costly `read()`/`write()`
         * syscalls.
         */
        unsigned char *buf;
        size_t buf_size;

        /* Pointers for reading and writing from/to the buffer defined above. */
        unsigned char *rpos, *rend;
        unsigned char *wend, *wpos;

        /* Function pointers to syscalls. */
        size_t (*read)(FILE *, unsigned char *, size_t);
        size_t (*write)(FILE *, const unsigned char *, size_t);
        off_t (*seek)(FILE *, off_t, int);
        int (*close)(FILE *);

        /* Lock for concurrent file access. */
        volatile int lock;
};
```

## I/O Buffering

### Practice

Implement simple buffering on your own.
Measure time.
