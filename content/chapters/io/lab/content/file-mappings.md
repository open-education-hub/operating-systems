# File Mappings

Mapping a file to the VAS of a process is similar to how shared libraries are loaded into the same VAS.
It's a fancier way of saying that the contents of a file are copied from a given offset within that file to a given address.
What's nice about this is that the OS handles all offsets, addresses and memory allocations on its own, with a single highly versatile syscall: `mmap()`.

## The Return of `mmap()`

Remember that the `.text`, `.rodata` and `.data` sections of libraries are present in the VAS of any Linux process:

```console
student@os:~$ sleep 1000 &  # start a `sleep` process in the background
[1] 17579

student@os:~$ cat /proc/$(pidof sleep)/maps
55b7b646f000-55b7b6471000 r--p 00000000 103:07 6423964                   /usr/bin/sleep
55b7b6471000-55b7b6475000 r-xp 00002000 103:07 6423964                   /usr/bin/sleep
55b7b6475000-55b7b6477000 r--p 00006000 103:07 6423964                   /usr/bin/sleep
55b7b6478000-55b7b6479000 r--p 00008000 103:07 6423964                   /usr/bin/sleep
55b7b6479000-55b7b647a000 rw-p 00009000 103:07 6423964                   /usr/bin/sleep
55b7b677c000-55b7b679d000 rw-p 00000000 00:00 0                          [heap]
7fe442f61000-7fe44379d000 r--p 00000000 103:07 6423902                   /usr/lib/locale/locale-archive
7fe44379d000-7fe4437bf000 r--p 00000000 103:07 6432810                   /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fe4437bf000-7fe443937000 r-xp 00022000 103:07 6432810                   /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fe443937000-7fe443985000 r--p 0019a000 103:07 6432810                   /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fe443985000-7fe443989000 r--p 001e7000 103:07 6432810                   /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fe443989000-7fe44398b000 rw-p 001eb000 103:07 6432810                   /usr/lib/x86_64-linux-gnu/libc-2.31.so
7fe44398b000-7fe443991000 rw-p 00000000 00:00 0
7fe4439ad000-7fe4439ae000 r--p 00000000 103:07 6429709                   /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fe4439ae000-7fe4439d1000 r-xp 00001000 103:07 6429709                   /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fe4439d1000-7fe4439d9000 r--p 00024000 103:07 6429709                   /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fe4439da000-7fe4439db000 r--p 0002c000 103:07 6429709                   /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fe4439db000-7fe4439dc000 rw-p 0002d000 103:07 6429709                   /usr/lib/x86_64-linux-gnu/ld-2.31.so
7fe4439dc000-7fe4439dd000 rw-p 00000000 00:00 0
7ffd07aeb000-7ffd07b0c000 rw-p 00000000 00:00 0                          [stack]
7ffd07b8b000-7ffd07b8e000 r--p 00000000 00:00 0                          [vvar]
7ffd07b8e000-7ffd07b8f000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
```

How does the content of those files get there?
Below you can see how libc is loaded, i.e. mapped into the VAS of an `ls` process.

```console
student@os:~$ strace ls
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
[...]
mmap(NULL, 2037344, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fb313c9c000
mmap(0x7fb313cbe000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7fb313cbe000
mmap(0x7fb313e36000, 319488, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19a000) = 0x7fb313e36000
mmap(0x7fb313e84000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7fb313e84000
```

For a quick reminder about `mmap()`, its 5th argument is the file descriptor from where we want to copy the data to the RAM.
The 6th argument is the offset within the file from where to start copying.

### Practice: Copy a File

If `mmap()` is good for copying files, let's use it like this.
Navigate to `support/file-mappings/mmap_cp.c`.
It copies the contents of a file to another by `mmap()`-ing each of them to its VAS and then simply copying the bytes from one mapping to another as if copying the contents of 2 arrays.

1. Fill in the `TODO`s so that the program correctly copies the contents of the input file to the output file.
Use `make test-file` to generate a 1MB file with random data.
You can use this for debugging and `diff` to test whether the input and output files differ (they shouldn't):

```console
student@os:/.../support/file-mappings$ ./mmap_cp test-file.txt output.txt

student@os:/.../support/file-mappings$ diff test-file.txt output.txt

student@os:/.../support/file-mappings$
```

<!-- markdownlint-disable MD029 -->

2. Uncomment the calls to `wait_for_input()` and rerun the program.
While the program is waiting, open another terminal and run `cat /proc/$(pidof mmap_cp)/maps` and see the mapped files.

<!-- markdownlint-enable MD029 -->

### Practice: I Am Speed

Now we can copy files using `mmap()`.
The code is rather short and convenient to write.
It's disadvantage is that we have to `mmap()` the 2 files entirely of the VAS of the process.
While this may be alright for small files, for larger ones we simply may not have enough RAM.
What if we had to copy a 500GB file?

Let's look at what the `cp` tool uses for copying.

[Quiz 1](../quiz/syscalls-cp.md)

OK, so we have a competition: our `mmap_cp` versus `cp`.
Run the script `benchmark_cp.sh` to measure which of the 2 implementations is faster.

[Quiz 2](../quiz/mmap-read-write-benchmark.md)

Now take a look at the `benchmark_cp.sh` script.
You might get a little confused about the following command: `echo 3 > /proc/sys/vm/drop_caches`.
Head over to [this section in the Arena](./arena.md#to-drop-or-not-to-drop) to find out what it's about.

## Conclusion

So by using `mmap()`, we pay the price for loading the file into memory **once**, but then all `read()`s, `write()`s and especially `seek()`s will be faster.
This is akin to treating the file as a regular byte array.
So file mappings are especially useful for randomly accessing file data.
Accessing the i-th byte in a file becomes the same as `mapping[i]`, which is obviously more efficient than calling `lseek()`.
File mappings are also useful when we have to overwrite existing data multiple times or when we read certain chunks multiple times.
