# Process Memory

## Memory Regions

To better manage a program's memory, the operating systems creates an address space for each process.
The address space is compartmentalized in multiple areas, each with its own role.
Memory addresses use different permissions to decide what actions are allowed.

Let's investigate the memory areas of a given process.
We use `pmap` to see the memory layout of a running process.
The command below shows the memory layout of the current shell process:

```console
student@os:~$ pmap -p $$
1127:   /bin/bash
000055fb4d77d000   1040K r-x-- /bin/bash
000055fb4da80000     16K r---- /bin/bash
000055fb4da84000     36K rw--- /bin/bash
000055fb4da8d000     40K rw---   [ anon ]
000055fb4e9bb000   1604K rw---   [ anon ]
00007f8fcf670000   4480K r---- /usr/lib/locale/locale-archive
00007f8fcfad0000     44K r-x-- /lib/x86_64-linux-gnu/libnss_files-2.27.so
00007f8fcfadb000   2044K ----- /lib/x86_64-linux-gnu/libnss_files-2.27.so
00007f8fcfcda000      4K r---- /lib/x86_64-linux-gnu/libnss_files-2.27.so
00007f8fcfcdb000      4K rw--- /lib/x86_64-linux-gnu/libnss_files-2.27.so
00007f8fcfcdc000     24K rw---   [ anon ]
00007f8fcfce2000     92K r-x-- /lib/x86_64-linux-gnu/libnsl-2.27.so
00007f8fcfcf9000   2044K ----- /lib/x86_64-linux-gnu/libnsl-2.27.so
00007f8fcfef8000      4K r---- /lib/x86_64-linux-gnu/libnsl-2.27.so
00007f8fcfef9000      4K rw--- /lib/x86_64-linux-gnu/libnsl-2.27.so
00007f8fcfefa000      8K rw---   [ anon ]
00007f8fcfefc000     44K r-x-- /lib/x86_64-linux-gnu/libnss_nis-2.27.so
00007f8fcff07000   2044K ----- /lib/x86_64-linux-gnu/libnss_nis-2.27.so
00007f8fd0106000      4K r---- /lib/x86_64-linux-gnu/libnss_nis-2.27.so
00007f8fd0107000      4K rw--- /lib/x86_64-linux-gnu/libnss_nis-2.27.so
00007f8fd0108000     32K r-x-- /lib/x86_64-linux-gnu/libnss_compat-2.27.so
00007f8fd0110000   2048K ----- /lib/x86_64-linux-gnu/libnss_compat-2.27.so
00007f8fd0310000      4K r---- /lib/x86_64-linux-gnu/libnss_compat-2.27.so
00007f8fd0311000      4K rw--- /lib/x86_64-linux-gnu/libnss_compat-2.27.so
00007f8fd0312000   1948K r-x-- /lib/x86_64-linux-gnu/libc-2.27.so
00007f8fd04f9000   2048K ----- /lib/x86_64-linux-gnu/libc-2.27.so
00007f8fd06f9000     16K r---- /lib/x86_64-linux-gnu/libc-2.27.so
00007f8fd06fd000      8K rw--- /lib/x86_64-linux-gnu/libc-2.27.so
00007f8fd06ff000     16K rw---   [ anon ]
00007f8fd0703000     12K r-x-- /lib/x86_64-linux-gnu/libdl-2.27.so
00007f8fd0706000   2044K ----- /lib/x86_64-linux-gnu/libdl-2.27.so
00007f8fd0905000      4K r---- /lib/x86_64-linux-gnu/libdl-2.27.so
00007f8fd0906000      4K rw--- /lib/x86_64-linux-gnu/libdl-2.27.so
00007f8fd0907000    148K r-x-- /lib/x86_64-linux-gnu/libtinfo.so.5.9
00007f8fd092c000   2048K ----- /lib/x86_64-linux-gnu/libtinfo.so.5.9
00007f8fd0b2c000     16K r---- /lib/x86_64-linux-gnu/libtinfo.so.5.9
00007f8fd0b30000      4K rw--- /lib/x86_64-linux-gnu/libtinfo.so.5.9
00007f8fd0b31000    164K r-x-- /lib/x86_64-linux-gnu/ld-2.27.so
00007f8fd0d24000     20K rw---   [ anon ]
00007f8fd0d53000     28K r--s- /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache
00007f8fd0d5a000      4K r---- /lib/x86_64-linux-gnu/ld-2.27.so
00007f8fd0d5b000      4K rw--- /lib/x86_64-linux-gnu/ld-2.27.so
00007f8fd0d5c000      4K rw---   [ anon ]
00007ffff002f000    132K rw---   [ stack ]
00007ffff00c5000     12K r----   [ anon ]
00007ffff00c8000      4K r-x--   [ anon ]
ffffffffff600000      4K --x--   [ anon ]
 total            24364K
```

Information will differ among different systems.

See the different regions:

* the first region, with `r-x` permissions is the `.text` (code) area
* the second region, with `r--` premissions is the `.rodata` area
* the third region, with `rw-` permissions is the `.data` area, for initialized global variables
* the fourth region, with `rw-` permissions is the `.bss` area
* the fifth region, with the `rw-` permissions is the dynamic data memory area, also known as heap
* there are multiple dynamic libraries mapped in the virtual address space of the process, each library with their own regions
* there is a `[stack]` memory region, with `rw-` permissions

`pmap` also shows the total amount of virtual memory available to the process (`24364K`), as a total of the sizes of the regions.
Note that this is virtual memory, not actual physical memory used by the process.
For the process investigated above (with the `1127` pid) we could use the command below to show the total virtual size and physical size (also called _resident set size_):

```console
student@os:~$ ps -o pid,rss,vsz -p $$
  PID   RSS    VSZ
 1127  1968  24364
```

The resident size is `1968K`, much smaller than the virtual size.

Note how each region has a size multiple of `4K`, this has to do with the memory granularity.
The operating system allocates memory in chunks of a predefined size (in our case `4K`) called pages.

[Quiz](../quiz/half-page.md)

### Practice

Enter the `support/memory-areas/` directory.
We investigate other programs.

1. The `hello.c` program prints out a message and then sleeps.
   Build it:

   ```console
   student@os:~/.../lab/support/memory-areas$ make
   ```

   then run it (it will block):

   ```console
   student@os:~/.../lab/support/memory-areas$ ./hello
   Hello, world!
   ```

   In another terminal, use the command below to show the memory areas of the process:

   ```console
   student@os:~/.../lab/support/memory-areas$ pmap $(pidof hello)
   8220:   ./hello
   000055c0bef4b000      8K r-x-- hello
   000055c0bf14c000      4K r---- hello
   000055c0bf14d000      4K rw--- hello
   000055c0bf454000    132K rw---   [ anon ]
   00007f2a9e4a5000   1948K r-x-- libc-2.27.so
   00007f2a9e68c000   2048K ----- libc-2.27.so
   00007f2a9e88c000     16K r---- libc-2.27.so
   00007f2a9e890000      8K rw--- libc-2.27.so
   00007f2a9e892000     16K rw---   [ anon ]
   00007f2a9e896000    164K r-x-- ld-2.27.so
   00007f2a9ea8c000      8K rw---   [ anon ]
   00007f2a9eabf000      4K r---- ld-2.27.so
   00007f2a9eac0000      4K rw--- ld-2.27.so
   00007f2a9eac1000      4K rw---   [ anon ]
   00007ffee6471000    132K rw---   [ stack ]
   00007ffee6596000     12K r----   [ anon ]
   00007ffee6599000      4K r-x--   [ anon ]
   ffffffffff600000      4K --x--   [ anon ]
    total             4520K
   ```

   The output is similar, but with fewer dynamic libraries than `bash`, since they are not used by the program.

1. Make a program in another language of your choice that prints `Hello, world!` and sleeps and investigate it with `pmap`.
   Note that in the case of interpreted languages (Python, Lua, Perl, Ruby, PHP, JavaScript etc.) you have to investigate the interpreter process.

## Memory Layout of Statically-Linked and Dynamically-Linked Executables

We want to see the difference in memory layout between the statically-linked and dynamically-linked executables.

Enter the `support/static-dynamic/` directory and build the statically-linked and dynamically-linked executables `hello-static` and `hello-dynamic`:

```console
student@os:~/.../lab/support/static-dynamic$ make
```

Now, by running the two programs and inspecting them with `pmap` on another terminal, we get the output:

```console
student@os:~/.../lab/support/static-dynamic$ pmap $(pidof hello-static)
9714:   ./hello-static
0000000000400000    876K r-x-- hello-static
00000000006db000     24K rw--- hello-static
00000000006e1000      4K rw---   [ anon ]
00000000017b5000    140K rw---   [ anon ]
00007ffc6f1d6000    132K rw---   [ stack ]
00007ffc6f1f9000     12K r----   [ anon ]
00007ffc6f1fc000      4K r-x--   [ anon ]
ffffffffff600000      4K --x--   [ anon ]
 total             1196K

student@os:~/.../lab/support/static-dynamic$ pmap $(pidof hello-dynamic)
9753:   ./hello-dynamic
00005566e757f000      8K r-x-- hello-dynamic
00005566e7780000      4K r---- hello-dynamic
00005566e7781000      4K rw--- hello-dynamic
00005566e8894000    132K rw---   [ anon ]
00007fd434eb8000   1948K r-x-- libc-2.27.so
00007fd43509f000   2048K ----- libc-2.27.so
00007fd43529f000     16K r---- libc-2.27.so
00007fd4352a3000      8K rw--- libc-2.27.so
00007fd4352a5000     16K rw---   [ anon ]
00007fd4352a9000    164K r-x-- ld-2.27.so
00007fd43549f000      8K rw---   [ anon ]
00007fd4354d2000      4K r---- ld-2.27.so
00007fd4354d3000      4K rw--- ld-2.27.so
00007fd4354d4000      4K rw---   [ anon ]
00007ffe497ba000    132K rw---   [ stack ]
00007ffe497e3000     12K r----   [ anon ]
00007ffe497e6000      4K r-x--   [ anon ]
ffffffffff600000      4K --x--   [ anon ]
 total             4520K
```

For the static executable, we can see there are no areas for dynamic libraries.
And the `.rodata` section has been coalesced in the `.text` area.

We can see the size of each section in the two executables by using the `size` command:

```console
student@os:~/.../lab/support/static-dynamic$ size hello-static
text    data     bss     dec     hex filename
893333   20996    7128  921457   e0f71 hello-static

student@os:~/.../lab/support/static-dynamic$ size hello-dynamic
text    data     bss     dec     hex filename
4598     736     824    6158    180e hello-dynamic
```

### Quiz

Based on the information above, answer [this quiz](../quiz/memory-granularity.md).

### Practice

1. Let's investigate another static executable / process.

   If not already installed, install the `busybox-static` package on your system.
   On Debian/Ubuntu systems, use:

   ```console
   student@os:~$ sudo apt install busybox-static
   ```

   Start a process using:

   ```console
   student@os:~$ busybox sleep 1000
   ```

   Investigate the process using `pmap` and the executable using `size`.

## Memory Layout of Multi-threaded Programs

When a new thread is created, a new stack is allocated for a thread.
The default stack size if `8 MB` / `8192 KB`:

```console
student@os:~$ ulimit -s
8192
```

Enter the `support/multithreaded/` directory to observe the update of the memory layout when creating new threads.

Build the `multithreaded` executable:

```console
student@os:~/.../lab/support/multithreaded$ make
```

Start the program:

```console
student@os:~/.../lab/support/multithreaded$ ./multithreaded
Press key to start creating threads ...
[...]
```

And investigate it with `pmap` on another console, while pressing a key to create new threads.

As you can see, there is a new `8192 KB` area created for every thread, also increasing the total virtual size.

**We will discuss more about threads in the future.
For now, we want to point out how threads affect the process memory layout.**

### Practice

1. Build the multithreaded program as a static executable.
   Run it.
   Notice the same effect of the thread creation on the process memory layout: the creation of a new stack of `8192 KB`.

1. Make a program in another language of your choice that creates threads.
   Investigate it with `pmap`.

[Quiz](../quiz/thread-memory.md)

## Modifying Memory Region Size

We want to observe the update in size of memory regions for different instructions used in a program.

Enter the `support/modify-areas/` directory.
Browse the contents of the `hello.c` file;
it is an update to the `hello.c` file in the `memory-areas/` directory.
Build the executable:

```console
student@os:~/.../lab/support/modify-areas$ make
```

Use `size` to view the difference between the new executable and the one in the `memory-areas/` directory:

```console
student@os:~/.../lab/support/modify-areas$ size hello
   text    data     bss     dec     hex filename
  13131   17128   33592   63851    f96b hello

student@os:~/.../lab/support/modify-areas$ size ../memory-areas/hello
   text    data     bss     dec     hex filename
   4598     736     824    6158    180e ../memory-areas/hello
```

Explain the differences.

Then use the `pmap` to watch the memory areas of the resulting processes from the two different executables.
We will see something like this for the new executable:

```console
student@os:~/.../lab/support/modify-areas$ pmap $(pidof hello)
18254:   ./hello
000055beff4d0000     16K r-x-- hello
000055beff6d3000      4K r---- hello
000055beff6d4000     20K rw--- hello
000055beff6d9000     32K rw---   [ anon ]
000055beffb99000    324K rw---   [ anon ]
00007f7b6c2e6000   1948K r-x-- libc-2.27.so
00007f7b6c4cd000   2048K ----- libc-2.27.so
00007f7b6c6cd000     16K r---- libc-2.27.so
00007f7b6c6d1000      8K rw--- libc-2.27.so
00007f7b6c6d3000     16K rw---   [ anon ]
00007f7b6c6d7000    164K r-x-- ld-2.27.so
00007f7b6c8cd000      8K rw---   [ anon ]
00007f7b6c900000      4K r---- ld-2.27.so
00007f7b6c901000      4K rw--- ld-2.27.so
00007f7b6c902000      4K rw---   [ anon ]
00007ffe2b196000    204K rw---   [ stack ]
00007ffe2b1d8000     12K r----   [ anon ]
00007ffe2b1db000      4K r-x--   [ anon ]
ffffffffff600000      4K --x--   [ anon ]
 total             4840K
```

We notice the size increase of text, data, bss, heap and stack sections.

### Practice

1. Comment out different parts of the `hello.c` program to notice differences in only specific areas (text, data, bss, heap, stack).

1. Use a different argument (`order`) for the call to the `alloc_stack()` function.
   See how it affects the stack size during runtime (investigate with `pmap`).

1. Do a static build of `hello.c` and check the size of the memory areas, both statically and dynamically.

1. The `extend_mem_area.py` Python script allocates a new string at each step by merging the two previous versions.
   Start the program and investigate the resulting process at each allocation step.
   Notice which memory area is updated and explain why.

[Quiz](../quiz/page-allocation.md)

## Allocating and Deallocating Memory

Memory areas in a process address space are static or dynamic.
Static memory areas are known at the beginning of process lifetime (i.e. at load-time), while dynamic memory areas are managed at runtime.

`.text`, `.rodata`, `.data`, `.bss` are allocated at load-time and have a predefined size.
The stack and the heap and memory mappings are allocated at runtime and have a variable size.
For those, we say we use runtime allocation and deallocation.

Memory allocation is implicit for the stack and explicit for the heap.
That is, we don't make a particular call to allocate data on the stack;
the compiler generates the code that the operating system uses to increase the stack when required.
For the heap, we use the `malloc()` and `free()` calls to explicitly allocate and deallocate memory.

Omitting to deallocate memory results in memory leaks that hurt the resource use in the system.
Because of this, some language runtimes employ a garbage collector that automatically frees unused memory areas.
More than that, some languages (think of Python) provide no explicit means to allocate memory: you just define and use data.

Let's enter the `support/alloc_size/` directory.
Browse the `alloc_size.c` file.
Build it:

```console
student@os:~/.../lab/support/alloc_size$ make
```

Now see the update in the process layout, by running the program in one console:

```console
student@os:~/.../lab/support/alloc_size$ ./alloc_size
Press key to allocate ...
[...]
```

And investigating it with `pmap` on another console:

```console
student@os:~/.../lab/support/alloc_size$ pmap $(pidof alloc_size)
21107:   ./alloc_size
000055de9d173000      8K r-x-- alloc_size
000055de9d374000      4K r---- alloc_size
000055de9d375000      4K rw--- alloc_size
000055de9deea000    132K rw---   [ anon ]
00007f1ea4fd4000   1948K r-x-- libc-2.27.so
00007f1ea51bb000   2048K ----- libc-2.27.so
00007f1ea53bb000     16K r---- libc-2.27.so
00007f1ea53bf000      8K rw--- libc-2.27.so
00007f1ea53c1000     16K rw---   [ anon ]
00007f1ea53c5000    164K r-x-- ld-2.27.so
00007f1ea55bb000      8K rw---   [ anon ]
00007f1ea55ee000      4K r---- ld-2.27.so
00007f1ea55ef000      4K rw--- ld-2.27.so
00007f1ea55f0000      4K rw---   [ anon ]
00007ffcf28e9000    132K rw---   [ stack ]
00007ffcf29be000     12K r----   [ anon ]
00007ffcf29c1000      4K r-x--   [ anon ]
ffffffffff600000      4K --x--   [ anon ]
 total             4520K

student@os:~/.../lab/support/alloc_size$ pmap $(pidof alloc_size)
21107:   ./alloc_size
000055de9d173000      8K r-x-- alloc_size
000055de9d374000      4K r---- alloc_size
000055de9d375000      4K rw--- alloc_size
000055de9deea000    452K rw---   [ anon ]
00007f1ea4fd4000   1948K r-x-- libc-2.27.so
00007f1ea51bb000   2048K ----- libc-2.27.so
00007f1ea53bb000     16K r---- libc-2.27.so
00007f1ea53bf000      8K rw--- libc-2.27.so
00007f1ea53c1000     16K rw---   [ anon ]
00007f1ea53c5000    164K r-x-- ld-2.27.so
00007f1ea55bb000      8K rw---   [ anon ]
00007f1ea55ee000      4K r---- ld-2.27.so
00007f1ea55ef000      4K rw--- ld-2.27.so
00007f1ea55f0000      4K rw---   [ anon ]
00007ffcf28e9000    132K rw---   [ stack ]
00007ffcf29be000     12K r----   [ anon ]
00007ffcf29c1000      4K r-x--   [ anon ]
ffffffffff600000      4K --x--   [ anon ]
 total             4840K

student@os:~/.../lab/support/alloc_size$ pmap $(pidof alloc_size)
21107:   ./alloc_size
000055de9d173000      8K r-x-- alloc_size
000055de9d374000      4K r---- alloc_size
000055de9d375000      4K rw--- alloc_size
000055de9deea000    420K rw---   [ anon ]
00007f1ea4fd4000   1948K r-x-- libc-2.27.so
00007f1ea51bb000   2048K ----- libc-2.27.so
00007f1ea53bb000     16K r---- libc-2.27.so
00007f1ea53bf000      8K rw--- libc-2.27.so
00007f1ea53c1000     16K rw---   [ anon ]
00007f1ea53c5000    164K r-x-- ld-2.27.so
00007f1ea55bb000      8K rw---   [ anon ]
00007f1ea55ee000      4K r---- ld-2.27.so
00007f1ea55ef000      4K rw--- ld-2.27.so
00007f1ea55f0000      4K rw---   [ anon ]
00007ffcf28e9000    132K rw---   [ stack ]
00007ffcf29be000     12K r----   [ anon ]
00007ffcf29c1000      4K r-x--   [ anon ]
ffffffffff600000      4K --x--   [ anon ]
 total             4808K
```

The three runs above of the `pmap` command occur before the allocation, after allocation and before deallocation and after deallocation.
Notice the update toe the 4th section, the heap.

Now, let's see what happens behind the scenes.
Run the executable under `ltrace` and `strace`:

```console
student@os:~/.../lab/support/alloc_size$ ltrace ./alloc_size
malloc(32768)                                                                                                    = 0x55e33f490b10
printf("New allocation at %p\n", 0x55e33f490b10New allocation at 0x55e33f490b10
)                                                                 = 33
[...]
free(0x55e33f490b10)                                                                                             = <void>
[...]

student@os:~/.../lab/support/alloc_size$ strace ./alloc_size
[...]
write(1, "New allocation at 0x55ab98acfaf0"..., 33New allocation at 0x55ab98acfaf0
) = 33
write(1, "New allocation at 0x55ab98ad7b00"..., 33New allocation at 0x55ab98ad7b00
) = 33
brk(0x55ab98b08000)                     = 0x55ab98b08000
write(1, "New allocation at 0x55ab98adfb10"..., 33New allocation at 0x55ab98adfb10
) = 33
write(1, "Press key to deallocate ...", 27Press key to deallocate ...) = 27
read(0,
"\n", 1024)                     = 1
brk(0x55ab98b00000)                     = 0x55ab98b00000
[...]
```

The resulting output above shows us the following:

* `malloc()` and `free()` library calls both map to the [`brk` syscall](https://man7.org/linux/man-pages/man2/sbrk.2.html), a syscall that updates the end of the heap (called **program break**).
* Multiple `malloc()` calls map to a single `brk` syscall for efficiency.
  `brk` is called to preallocate a larger chunk of memory that `malloc` will then use.

Update the `ALLOC_SIZE_KB` macro in the `alloc_size.c` file to `256`.
Rebuild the program and rerun it under `ltrace` and `strace`:

```console
student@os:~/.../lab/support/alloc_size$ ltrace ./alloc_size
[...]
malloc(262144)                                                                                                   = 0x7f4c016a9010
[...]
free(0x7f4c016a9010)                                                                                             = <void>
[...]

student@os:~/.../lab/support/alloc_size$ strace ./alloc_size
[...]
mmap(NULL, 266240, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7feee19f2000
write(1, "New allocation at 0x7feee19f2010"..., 33New allocation at 0x7feee19f2010
) = 33
mmap(NULL, 266240, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7feee19b1000
write(1, "New allocation at 0x7feee19b1010"..., 33New allocation at 0x7feee19b1010
) = 33
write(1, "Press key to deallocate ...", 27Press key to deallocate ...) = 27
read(0,
"\n", 1024)                     = 1
munmap(0x7feee19b1000, 266240)          = 0
[...]
```

For the new allocation size, notice that the remarks above don't hold:

* `malloc()` now invokes the `mmap` syscall, while `free()` invokes the `munmap` syscall.
* Each `malloc()` calls results in a separate `mmap` syscall.

This is a behavior of the `malloc()` in libc, documented in the [manual page](https://man7.org/linux/man-pages/man3/malloc.3.html#NOTES).
A variable `MALLOC_THRESHOLD` holds the size after which `mmap` is used, instead of `brk`.
This is based on a heuristic of using the heap or some other area in the process address space.

### Practice

1. Use `pmap` to analyze the process address space for `ALLOC_SIZE_KB` initialized to `256`.
   Notice the new memory areas and the difference between the use of `mmap` syscall and `brk` syscall.

1. Use `valgrind` on the resulting executable, and notice there are memory leaks.
   They are quite obvious due to the lack of proper freeing.
   Solve the leaks.

1. Use `valgrind` on different executables in the system (in `/bin/`, `/usr/bin/`) and see if they have memory leaks.

[Quiz](../quiz/malloc-brk.md)

[Quiz](../quiz/malloc-mmap.md)

## Memory Mapping

The `mmap` syscall is used to allocate memory as _anonymous mapping_, that is reserving memory in the process address space.
An alternate use is for mapping files in the memory address space.
Mapping of files is done by the loader for executables and libraries.
That is why, in the output of `pmap`, there is a column with a filename.

Mapping of a file results in getting a pointer to its contents and then using that pointer.
This way, reading and writing to a file is an exercise of pointer copying, instead of the use of `read` / `write`-like system calls.

In the `support/copy/` folder, there are two source code files and two scripts:

* `read_write_copy.c` implements copying with `read` / `write` syscalls
* `mmap_copy.c` implements copying using `mmap`
* `generate.sh` script generates the input file `in.dat`
* `benchmark_cp.sh` script runs the two executables `mmap_copy` and `read_write_copy`

Open the two source code files and investigate them.
You will notice that the `open()` system call has the following prototype `int open(const char *pathname, int flags)`.
The argument `flags` must include one of the following access modes: `O_RDONLY`, `O_WRONLY`, or `O_RDWR` - indicating that the file is opened in read-only, write-only, or read/write mode.
You can add an additional flag - `O_CREAT` - that will create a new file with `pathname` if the file does not already exist.
This is only the case when opening the file for writing (`O_WRONLY` or `O_RDWR`).
If `O_CREAT` is set, a third argument `mode_t mode` is required for the `open()` syscall.
The `mode` argument specifies the permissions of the newly created file.
For example:

```c
// If DST_FILENAME exists it will be open in read/write mode and truncated to length 0
// If DST_FILENAME does not exist, a file at the path DST_FILENAME will be create with 644 permissions
dst_fd = open(DST_FILENAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
```

Let's generate the input file:

```console
student@os:~/.../lab/support/copy$ ./generate.sh
```

and let's build the two executable files:

```console
student@os:~/.../lab/support/copy$ make
```

Run the `benchmark_cp.sh` script:

```console
student@os:~/.../lab/support/copy$ ./benchmark_cp.sh
Benchmarking mmap_copy on in.dat
time passed 54015 microseconds

Benchmarking read_write_copy on in.dat
time passed 42011 microseconds
```

Run the script a few more times.
As you can see, there isn't much of a difference between the two approaches.
Although we would have expected the use of multiple system calls to cause overhead, it's too little compared to the memory copying overhead.

If you inspect `benchmark_cp.sh`, you will notice a weird-looking command `sh -c "sync; echo 3 > /proc/sys/vm/drop_caches"`.
This is used to disable a memory optimization that the kernel does.
It's called "buffer cache" and it's a mechanism by which the kernel caches data blocks from recently accessed files in memory.
You will get more detailed information about this in the I/O chapter.

Browse the two source code files (`mmap_copy.c` and `read_write_copy.c`) for a glimpse on how the two types of copies are implemented.

[Quiz](../quiz/mmap-file.md)

### Practice

1. Use a different value for `BUFSIZE` and see if that affects the comparison between the two executables.

1. Add a `sleep()` call to the `mmap_copy.c` file **after** the files were mapped.
   Rebuild the program and run it.
   On a different console, use `pmap` to view the two new memory regions that were added to the process, by mapping the `in.dat` and `out.dat` files.
