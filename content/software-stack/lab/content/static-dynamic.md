# Statically-linked and Dynamically-linked Libraries

Libraries can be statically-linked or dynamically-linked, creating statically-linked executables and dynamically-linked executables.
Typically, the executables found in modern operating systems are dynamically-linked, given their reduced size and ability to share libraries at runtime.

The `support/static-dynamic/` folder stores the implementation of a simple "Hello, World!"-printing program that uses both static and dynamic linking of libraries.
Let's build and run the two executables:

```console
student@os:~/.../lab/support/static-dynamic$ ls
hello.c  Makefile

student@os:~/.../lab/support/static-dynamic$ make
cc -Wall   -c -o hello.o hello.c
cc   hello.o   -o hello
cc -static -o hello_static hello.o

student@os:~/.../lab/support/static-dynamic$ ls -lh
total 852K
-rwxrwxr-x 1 razvan razvan 8.2K Aug  2 15:53 hello
-rw-rw-r-- 1 razvan razvan   76 Aug  2 15:51 hello.c
-rw-rw-r-- 1 razvan razvan 1.6K Aug  2 15:53 hello.o
-rwxrwxr-x 1 razvan razvan 827K Aug  2 15:53 hello_static
-rw-rw-r-- 1 razvan razvan  237 Aug  2 15:53 Makefile

student@os:~/.../lab/support/static-dynamic$ ./hello
Hello, World!

student@os:~/.../lab/support/static-dynamic$ ./hello_static
Hello, World!
```

The two executables (`hello` and `hello_static`) behave similarly, despite having vastly different sizes (`8.2K` vs. `827K` - 100 times larger).

We use `nm` and `ldd` to catch differences between the two types of resulting executables:

```console
student@os:~/.../lab/support/static-dynamic$ ldd hello
        linux-vdso.so.1 (0x00007ffc8d9b2000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f10d1d88000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f10d237b000)

student@os:~/.../lab/support/static-dynamic$ ldd hello_static
        not a dynamic executable

student@os:~/.../lab/support/static-dynamic$ nm hello | wc -l
33

student@os:~/.../lab/support/static-dynamic$ nm hello_static | wc -l
1674
```

The dynamic executable references the dynamically-linked libc library (`/lib/x86_64-linux-gnu/libc.so.6`), while the statically-linked executable has no references.
Also, given the statically-linked executable integrated entire parts of statically-linked libraries, there are many more symbols than in the case of a dynamically-linked executable (`1674` vs. `33`).

We can use `strace` to see that there are differences in the preparatory system calls for each type of executables.
For the dynamically-linked executable, the dynamically-linked library (`/lib/x86_64-linux-gnu/libc.so.6`) is opened during runtime:

```console
student@os:~/.../lab/support/static-dynamic$ strace ./hello
execve("./hello", ["./hello"], 0x7ffc409c6640 /* 66 vars */) = 0
brk(NULL)                               = 0x55a72eda6000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=198014, ...}) = 0
mmap(NULL, 198014, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f3136a41000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\240\35\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2030928, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f3136a3f000
mmap(NULL, 4131552, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f3136458000
mprotect(0x7f313663f000, 2097152, PROT_NONE) = 0
mmap(0x7f313683f000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7f313683f000
mmap(0x7f3136845000, 15072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f3136845000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7f3136a404c0) = 0
mprotect(0x7f313683f000, 16384, PROT_READ) = 0
mprotect(0x55a72d1bb000, 4096, PROT_READ) = 0
mprotect(0x7f3136a72000, 4096, PROT_READ) = 0
munmap(0x7f3136a41000, 198014)          = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 18), ...}) = 0
brk(NULL)                               = 0x55a72eda6000
brk(0x55a72edc7000)                     = 0x55a72edc7000
write(1, "Hello, World!\n", 14Hello, World!
)         = 14
exit_group(0)                           = ?
+++ exited with 0 +++

student@os:~/.../lab/support/static-dynamic$ strace ./hello_static
execve("./hello_static", ["./hello_static"], 0x7ffc9fd45400 /* 66 vars */) = 0
brk(NULL)                               = 0xff8000
brk(0xff91c0)                           = 0xff91c0
arch_prctl(ARCH_SET_FS, 0xff8880)       = 0
uname({sysname="Linux", nodename="yggdrasil", ...}) = 0
readlink("/proc/self/exe", "/home/razvan/school/so/operating"..., 4096) = 116
brk(0x101a1c0)                          = 0x101a1c0
brk(0x101b000)                          = 0x101b000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 18), ...}) = 0
write(1, "Hello, World!\n", 14Hello, World!
)         = 14
exit_group(0)                           = ?
+++ exited with 0 +++
```

Similarly, we can investigate a system executable (`/bin/ls`) to see that indeed all referenced dynamically-linked libraries are opened (via the `openat` system call) at runtime:

```console
student@os:~/.../lab/support/static-dynamic$ ldd $(which ls)
	linux-vdso.so.1 (0x00007ffc3bdf3000)
	libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x00007f092bd88000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f092b997000)
	libpcre.so.3 => /lib/x86_64-linux-gnu/libpcre.so.3 (0x00007f092b726000)
	libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007f092b522000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f092c1d2000)
	libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f092b303000)

student@os:~/.../lab/support/static-dynamic$ strace -e openat ls
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpcre.so.3", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libdl.so.2", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpthread.so.0", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/proc/filesystems", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
openat(AT_FDCWD, ".", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
community  docs  _index.html  search.md
+++ exited with 0 +++
```

[Quiz](../quiz/libs.md)
