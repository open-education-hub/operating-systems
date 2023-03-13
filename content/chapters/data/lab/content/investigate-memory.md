# Investigate Memory Actions

Memory actions generally mean:

* memory access: read, write or execute
* memory allocation
* memory deallocation

By far, the most important actions are allocation and deallocation.
Because, if not done right, these can get to memory loss and poor memory use.

Memory loss generally happens in the form of memory leaks.

## Memory Leaks

A memory leak occurs when we lose reference to a memory area.
That is, a pointer used to point to a memory area.
And then it's pointing to a new memory area and the old memory area is lost.

Enter the `support/memory-leak/` folder.
It stores two files showing memory leaks:

* one in C++: `memory_leak.cpp`
* one in C: `memory_leak_malloc`

Let's build and run the two executables:

```console
student@os:~/.../lab/support/memory-leak$ make
g++    -c -o memory_leak.o memory_leak.cpp
cc   memory_leak.o  -lstdc++ -o memory_leak
cc    -c -o memory_leak_malloc.o memory_leak_malloc.c
cc   memory_leak_malloc.o  -lstdc++ -o memory_leak_malloc
```

Running them yields similar output:

```console
student@os:~/.../lab/support/memory-leak$ ./memory_leak
Andrei Popescu is 22 years old and likes Linux
Ioana David is 23 years old and likes macOS
student@os:~/.../lab/support/memory-leak$ ./memory_leak_malloc
Andrei Popescu is 22 years old and likes Linux
Ioana David is 23 years old and likes macOS
```

We investigate the memory leaks of the two programs by using [Valgrind](https://valgrind.org/):

```console
student@os:~/.../lab/support/memory-leak$ valgrind ./memory_leak
==22362== Memcheck, a memory error detector
==22362== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==22362== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==22362== Command: ./memory_leak
==22362==
Andrei Popescu is 22 years old and likes Linux
Ioana David is 23 years old and likes macOS
==22362==
==22362== HEAP SUMMARY:
==22362==     in use at exit: 72 bytes in 1 blocks
==22362==   total heap usage: 4 allocs, 3 frees, 73,872 bytes allocated
==22362==
==22362== LEAK SUMMARY:
==22362==    definitely lost: 72 bytes in 1 blocks
==22362==    indirectly lost: 0 bytes in 0 blocks
==22362==      possibly lost: 0 bytes in 0 blocks
==22362==    still reachable: 0 bytes in 0 blocks
==22362==         suppressed: 0 bytes in 0 blocks
==22362== Rerun with --leak-check=full to see details of leaked memory
==22362==
==22362== For counts of detected and suppressed errors, rerun with: -v
==22362== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

student@os:~/.../lab/support/memory-leak$ valgrind ./memory_leak_malloc
==22369== Memcheck, a memory error detector
==22369== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==22369== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==22369== Command: ./memory_leak_malloc
==22369==
Andrei Popescu is 22 years old and likes Linux
Ioana David is 23 years old and likes macOS
==22369==
==22369== HEAP SUMMARY:
==22369==     in use at exit: 148 bytes in 1 blocks
==22369==   total heap usage: 3 allocs, 2 frees, 1,320 bytes allocated
==22369==
==22369== LEAK SUMMARY:
==22369==    definitely lost: 148 bytes in 1 blocks
==22369==    indirectly lost: 0 bytes in 0 blocks
==22369==      possibly lost: 0 bytes in 0 blocks
==22369==    still reachable: 0 bytes in 0 blocks
==22369==         suppressed: 0 bytes in 0 blocks
==22369== Rerun with --leak-check=full to see details of leaked memory
==22369==
==22369== For counts of detected and suppressed errors, rerun with: -v
==22369== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

As we are doing allocations that are not freed, this results in memory leaks.

For `malloc()`-based programs, we can use [`mtrace()` feature](https://man7.org/linux/man-pages/man3/mtrace.3.html) and [`mtrace` command](https://man7.org/linux/man-pages/man1/mtrace.1.html) to verify proper allocations with `malloc()` and deallocations with `free()`.
We call `mtrace()` in the program (in `memory_leak_malloc.c`) to enable `malloc()` and `free()` checking.

To use `mtrace()` we define the `MALLOC_TRACE` environment variable:

```console
student@os:~/.../lab/support/memory-leak$ MALLOC_TRACE=mem.trace ./memory_leak_malloc
Andrei Popescu is 22 years old and likes Linux
Ioana David is 23 years old and likes macOS
```

Subsequently, we use the `mtrace` tool to show information about the leaked data:

```console
student@os:~/.../lab/support/memory-leak$ mtrace ./memory_leak_malloc mem.trace

Memory not freed:
-----------------
           Address     Size     Caller
0x000056506d8be6a0     0x94  at 0x56506c3777ec
```

The size (`0x94`) is the same value shown by Valgrind (`148`).

`mtrace` provides an outcome similar to Valgrind.
Valgrind is however more powerful: it works on different types of memory (not only those allocated with `malloc()`) and it doesn't require access to the source code (and the compiler phase).

### Practice

1. Print the size of the `Student` class and the `struct student` structure to see if it equates to the leak shown by Valgrind.

1. Solve the memory leaks in both programs.
   Validate with Valgrind.

[Quiz](../quiz/valgrind-leaks.md)

## Memory Actions (and Leaks) in Existing Programs

We can use Valgrind to investigate existing programs in the system.
This tells us whether they possess memory leaks:

```console
student@os:~/.../lab/support/memory-leak$ valgrind ls
==24669== Memcheck, a memory error detector
==24669== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==24669== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==24669== Command: ls
==24669==
Makefile  memory_leak  memory_leak.cpp  memory_leak_malloc  memory_leak_malloc.c  memory_leak_malloc.o  memory_leak.o
==24669==
==24669== HEAP SUMMARY:
==24669==     in use at exit: 21,696 bytes in 14 blocks
==24669==   total heap usage: 51 allocs, 37 frees, 61,331 bytes allocated
==24669==
==24669== LEAK SUMMARY:
==24669==    definitely lost: 0 bytes in 0 blocks
==24669==    indirectly lost: 0 bytes in 0 blocks
==24669==      possibly lost: 0 bytes in 0 blocks
==24669==    still reachable: 21,696 bytes in 14 blocks
==24669==         suppressed: 0 bytes in 0 blocks
==24669== Rerun with --leak-check=full to see details of leaked memory
==24669==
==24669== For counts of detected and suppressed errors, rerun with: -v
==24669== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

student@os:~/.../lab/support/memory-leak$ valgrind ps
==24671== Memcheck, a memory error detector
==24671== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==24671== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==24671== Command: ps
==24671==
  PID TTY          TIME CMD
24671 pts/22   00:00:00 memcheck-amd64-
26732 pts/22   00:00:01 bash
==24671==
==24671== HEAP SUMMARY:
==24671==     in use at exit: 264,929 bytes in 25 blocks
==24671==   total heap usage: 692 allocs, 667 frees, 334,268 bytes allocated
==24671==
==24671== LEAK SUMMARY:
==24671==    definitely lost: 0 bytes in 0 blocks
==24671==    indirectly lost: 0 bytes in 0 blocks
==24671==      possibly lost: 0 bytes in 0 blocks
==24671==    still reachable: 264,929 bytes in 25 blocks
==24671==         suppressed: 0 bytes in 0 blocks
==24671== Rerun with --leak-check=full to see details of leaked memory
==24671==
==24671== For counts of detected and suppressed errors, rerun with: -v
==24671== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

student@os:~/.../lab/support/memory-leak$ valgrind bash -c 'echo "ha"'
==24675== Memcheck, a memory error detector
==24675== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==24675== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==24675== Command: bash -c echo\ "ha"
==24675==
ha
==24675==
==24675== HEAP SUMMARY:
==24675==     in use at exit: 43,056 bytes in 672 blocks
==24675==   total heap usage: 774 allocs, 102 frees, 51,405 bytes allocated
==24675==
==24675== LEAK SUMMARY:
==24675==    definitely lost: 12 bytes in 1 blocks
==24675==    indirectly lost: 0 bytes in 0 blocks
==24675==      possibly lost: 0 bytes in 0 blocks
==24675==    still reachable: 43,044 bytes in 671 blocks
==24675==         suppressed: 0 bytes in 0 blocks
==24675== Rerun with --leak-check=full to see details of leaked memory
==24675==
==24675== For counts of detected and suppressed errors, rerun with: -v
==24675== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

We can see that `ls` and `ps` don't have memory leaks.
However, the shell (Bash) shows a memory leak of 12 bytes (on the test system).
This may be a false positive or the subject of an actual investigation.

Note that the `still reachable` section of the output refers to memory that wasn't freed, but still has pointers referring to it.
A true memory leak occurs when no pointers refer any memory area.

### Practice

1. Investigate 2-3 other executables in the system using Valgrind.

1. Use `ltrace` to list `malloc()` and `free()` calls made by the investigated system executables.

Note that, as explained in the [Software Stack lab](https://open-education-hub.github.io/operating-systems/Lab/Software-Stack/Libcall-Syscall/content/libcall-syscall), on some systems, `ltrace` does not accurately show the output, due to _now binding_.
Fear not, you can always check the library calls with a more verbose and harder to parse `ltrace` command:

```console
student@os:~$ ltrace -x "*"
```

[Quiz](../quiz/memory-leaks.md)

## jemalloc

[jemalloc](http://jemalloc.net/) is a featureful allocator that is intended to replace the standard allocator in the standard C library (libc).
jemalloc provides replacements for the general `malloc()` and `free()` functions, and also provides a custom API targeted for performance tuning.

As [documented](https://github.com/jemalloc/jemalloc/wiki/Getting-Started), there are multiple ways to use `jemalloc`, the easiest of which is to use the `LD_PRELOAD` environment variable and preload the library and hook into `malloc()` and `free()` function calls.

First install `jemalloc` on our system.
On your typical Ubuntu / Debian-based system, use `apt`:

```console
student@os:~/.../data/lab/content$ sudo apt -y install libjemalloc-dev
```

Note that this installs the distribution package, not the latest one (that may provide more features).

With this in place, we can use `jemalloc` against our pre-built executables or system executables (such as `ls`, `ps`).
We can test it against the executable files from `support/memory-leak/`:

```console
student@os:~/.../lab/support/memory-leak$ LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so.1 ./memory_leak_malloc
Andrei Popescu is 22 years old and likes Linux
Ioana David is 23 years old and likes macOS
```

`jemalloc` can use the `MALLOC_CONF` environment variable for a [diverse set of configurations](https://www.freebsd.org/cgi/man.cgi?query=malloc.conf).
For example, by using `stats_print:true` we print out information regarding the use of the library functions:

```console
student@os:~/.../lab/support/memory-leak$ LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so.1 MALLOC_CONF="stats_print:true" ./memory_leak_malloc
Andrei Popescu is 22 years old and likes Linux
Ioana David is 23 years old and likes macOS
___ Begin jemalloc statistics ___
Version: 3.6.0-11
Assertions disabled
Run-time option settings:
  opt.abort: false
  opt.lg_chunk: 22
  opt.dss: "secondary"
  opt.narenas: 32
  opt.lg_dirty_mult: 3
  opt.stats_print: true
  opt.junk: false
  opt.quarantine: 0
  opt.redzone: false
[...]
dirty pages: 26:0 active:dirty, 0 sweeps, 0 madvises, 0 purged
            allocated      nmalloc      ndalloc    nrequests
small:          72672          114            0            3
large:          32768            1            0            1
total:         105440          115            0            4
active:        106496
mapped:       4194304
[...]
```

`jemalloc` doesn't work against system executables using preloading, likely because of security options disabling the use of the library:

```console
student@os:~/.../lab/support/memory-leak$ LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so.1 MALLOC_CONF="stats_print:true" /bin/ls
Makefile  memory_leak  memory_leak.cpp  memory_leak_malloc  memory_leak_malloc.c  memory_leak_malloc.o  memory_leak.o

student@os:~/.../lab/support/memory-leak$ LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libjemalloc.so.1 MALLOC_CONF="stats_print:true" /bin/ps
  PID TTY          TIME CMD
 1581 pts/22   00:00:00 ps
26732 pts/22   00:00:01 bash
```

## malloc in Musl

Each libc (or memory allocator such as `jemalloc`) uses their own implementation of `malloc()`, `free()` and other functions.
[Musl libc](https://musl.libc.org/) is a lightweight standard C library that provides compatible features with the more heavyweights [GNU libc](https://www.gnu.org/software/libc/).

Take a look through implementation of `malloc()` and `free()` in [Musl libc](https://elixir.bootlin.com/musl/v1.2.3/source/src/malloc).
See all three implementations for `malloc()`:

* the one in `lite_malloc.c`
* the one in `mallocng/malloc.c`
* the one in `oldmalloc/malloc`

See also [the implementation of `free()`](https://elixir.bootlin.com/musl/v1.2.3/source/src/malloc/mallocng/free.c#L101).
And [the implementation of `calloc()`](https://elixir.bootlin.com/musl/v1.2.3/source/src/malloc/calloc.c#L33).

You needn't spend too much time browsing the implementation of these functions, just having a broad understanding of how they work.

## App Investigation: Deluge

[Deluge](https://www.deluge-torrent.org/) is a Bittorrent client written in Python.

We want to locate places that allocate memory in Deluge (in Python).
This generally means locating instantiation of classes.

Let's clone the [source code](https://github.com/deluge-torrent/deluge):

```console
student@os:~/.../data/lab/support$ git clone https://github.com/deluge-torrent/deluge
Cloning into 'deluge'...
[...]

student@os:~/.../data/lab/support$ cd deluge/

student@os:~/.../lab/support/deluge$ ls
AUTHORS       deluge      docs             gen_web_gettext.py  MANIFEST.in       msgfmt.py  pyproject.toml  requirements-dev.txt    requirements.txt  setup.py  version.py
CHANGELOG.md  DEPENDS.md  generate_pot.py  LICENSE             minify_web_js.py  packaging  README.md       requirements-tests.txt  setup.cfg         tox.ini
```

And enter the `deluge/core/` subdirectory:

```console
student@os:~/.../lab/support/deluge$ cd deluge/core/

student@os:~/.../deluge/deluge/core$ ls
alertmanager.py  core.py          daemon.py        filtermanager.py  pluginmanager.py       rpcserver.py       torrent.py
authmanager.py   daemon_entry.py  eventmanager.py  __init__.py       preferencesmanager.py  torrentmanager.py
```

Most files in the subdirectory have a class defined.
We can search for instantiations of that class using `grep`:

```console
student@os:~/.../deluge/deluge/core$ grep -rn 'Torrent('
torrentmanager.py:644:        torrent = Torrent(handle, options, state, filename, magne

student@os:~/.../deluge/deluge/core$ grep -rn 'TorrentManager('
core.py:139:        self.torrentmanager = TorrentManager()
torrentmanager.py:135:class TorrentManager(component.Component):
```

This gives us an overview of when memory is allocated in Deluge / Python.

### Practice

1. Investigate the lines shown to contain instantiations of classes.
   Explore the source code and understand their placements in the source code.

1. Find out other classes and search for their instantiation in the source code.

## App Investigation: Servo

[Servo](https://servo.org/) is a browser engine written in Rust that provides reusable components to implement web standards.

We do not clone the repository, since it's very large.

We find information about allocator used, by accessing the `components/allocator/` in [its source code](https://github.com/servo/servo/tree/master/components/allocator).
In `Cargo.toml` we see that it requires `jemalloc` for non-Windows implementations and the standard Windows API (called `heapapi`) for Windows:

```text
[...]
[lib]
path = "lib.rs"

[target.'cfg(not(windows))'.dependencies]
jemalloc-sys = { version = "0.3.2" }

[target.'cfg(windows)'.dependencies]
winapi = { version = "0.3", features = ["heapapi"] }
ust: https://github.com/servo/servo
```

In `lib.rs`, in [`GlobalAlloc:alloc()`](https://github.com/servo/servo/blob/master/components/allocator/lib.rs#L70) we see it is using [the `mallocx` custom function from `jemalloc()`](https://jemalloc.net/jemalloc.3.html).
See [the initialization of `ffi`](https://github.com/servo/servo/blob/master/components/allocator/lib.rs#L17).

See the use of the allocator in the [`Cargo.toml` file in the `net` component](https://github.com/servo/servo/blob/master/components/net/Cargo.toml).
Search for the _alloc_ string.

### Practice

1. Look for uses of the allocator in other components of Servo.

## Investigation: Alocator in the D Programming Language

[Phobos](https://github.com/dlang/phobos) is the standard library that comes with the D programming language compiler.

Let's clone the source code:

```console
student@os:~/.../std/experimental/allocator$ git clone https://github.com/dlang/phobos
[...]

student@os:~/.../data/lab/support$ cd phobos/

student@os:~/.../lab/support/phobos$ ls
azure-pipelines.yml  changelog  CODEOWNERS  CONTRIBUTING.md  dub.sdl  etc  index.dd  LICENSE_1_0.txt  posix.mak  project.ddoc  README.md  std  test  unittest.d  win32.mak  win64.mak
```

And enter `std/experimental/allocator/` to browse information about the allocator:

```console
student@os:~/.../lab/support/phobos$ cd std/experimental/allocator/

student@os:~/.../std/experimental/allocator$ ls
building_blocks  common.d  gc_allocator.d  mallocator.d  mmap_allocator.d  package.d  showcase.d  typed.d
```

We then do a search of the `allocate(` string to find instances of allocation calls:

```console
student@os:~/.../std/experimental/allocator$ grep -r 'allocate('
[...]
```

We see that there are definitions of the function (as expected) as part of `...allocator` files: `mallocator.d`, `gc_allocator.d`, `mmap_allocator.d`.
Browse the functions and look for implementations of the `allocate()` function.

### Practice

1. Do a similar search and then source code browsing for the `deallocate()` function.

## App Investigation: Git

[Git](https://git-scm.com/) is among the most used source code management system, powering development infrastructures such as [GitHub](https://github.com/), [GitLab](https://about.gitlab.com/) and [Bitbucket](https://bitbucket.org/).

Let's clone [the repository](https://github.com/git/git).
Note that it is about 200MB large:

```console
student@os:~/.../data/lab/support$ git clone https://github.com/git/git
[...]

student@os:~/.../data/lab/support$ cd git/
```

We look of uses of `malloc()`:

```console
student@os:~/.../lab/support/git$ grep -r 'malloc(' .
```

We see there are multiple calls to the `xmalloc()` function, which is likely a wrapper for `malloc()`.
We search for the definition of `xmalloc()`:

```console
student@os:~/.../lab/support/git$ grep -rn 'xmalloc(' . | grep -v ';'
./commit.c:188:                 graft = xmalloc(st_add(sizeof(*graft),
./add-interactive.c:157:        list->sorted.items = xmalloc(st_mult(sizeof(*list->sorted.items),
./Documentation/RelNotes/2.24.0.txt:91: * xmalloc() used to have a mechanism to ditch memory and address
./Documentation/RelNotes/2.24.0.txt:210:   xmalloc() wrapper, as the rest of the system, for consistency.
./Documentation/RelNotes/2.34.0.txt:230: * mmap() imitation used to call xmalloc() that dies upon malloc()
./Documentation/RelNotes/2.33.1.txt:44: * mmap() imitation used to call xmalloc() that dies upon malloc()
./diffcore-delta.c:56:  new_spanhash = xmalloc(st_add(sizeof(*orig),
./diffcore-delta.c:135: hash = xmalloc(st_add(sizeof(*hash),
./kwset.c:41:/* adapter for `xmalloc()`, which takes `size_t`, not `long` */
./builtin/fast-import.c:461:    b = xmalloc(sizeof(struct object_entry_pool)
./hashmap.h:311: * your structure was allocated with xmalloc(), you can just free(3) it,
./xdiff/xdiff.h:122:#define xdl_malloc(x) xmalloc(x)
./wrapper.c:45:static void *do_xmalloc(size_t size, int gentle)
./wrapper.c:70:void *xmalloc(size_t size)
./contrib/credential/wincred/git-credential-wincred.c:26:static void *xmalloc(size_t size)
Binary file ./.git/objects/pack/pack-c587b9f11a82bc4d49848d74132e60ea4dbeb177.pack matches
./git-compat-util.h:1046:# define xalloca(size)      (xmalloc(size))
./git-compat-util.h:1086:#define ALLOC_ARRAY(x, alloc) (x) = xmalloc(st_mult(sizeof(*(x)), (alloc)))
./read-cache.c:3768:    ieot = xmalloc(sizeof(struct index_entry_offset_table)
```

Line `./wrapper.c:70` is the one with the definition of the `xmalloc()` function.
It makes a call of the [`do_xmalloc()` function](https://github.com/git/git/blob/master/wrapper.c#L45), that makes extra checks.
Also, if the `XMALLOC_POISON` macro is defined, all the allocated data is overwritten with a "poison" value (`0xA5`).
This is useful for early detection of memory-related issues, although, evidently, it adds overhead.

We can look for parts of the source code with the largest number of uses of `xmalloc()`:

```console
student@os:~/.../lab/support/git$ grep -rc 'xmalloc(' . | grep -v ':0' | sort -n -t ':' -k 20
[...]
./compat/mingw.c:6
./submodule-config.c:6
./merge-recursive.c:7
```

We can look into the [`merge-recursive.c` file](https://github.com/git/git/blob/master/merge-recursive.c) for uses of the `xmalloc()` function.

### Practice

1. Do the same actions as above for the `mmap()` and `xmmap()` function calls.

   Note that these are not memory allocation calls, since a valid `fd` file argument is passed.
   These are file mapping calls, that we will talk more as part of the I/O chapter.
