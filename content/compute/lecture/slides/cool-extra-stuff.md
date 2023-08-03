---

## Cool Extra Stuff

---

### Recap - `exec()`

* Replaces the VAS of a process with that of another one
* Path to the binary file from which to start the second process given as argument
* The file descriptors of the original process are maintained
* Only returns in case of error
  * Otherwise, the new process takes over

----

#### Create a new process - `fork()` + `exec()`

* [Quiz](../quiz/exec-without-fork.md)
* "Save" the shell before calling `exec("/bin/ls")`
* Use `fork()` and only the child calls `exec()`

![Fork and Exec Diagram](media/fork-exec.svg)

----

#### Linux Syscalls

```console
student@os:~/.../compute/lecture/demo/create-process$ strace ./fork_exec
[...]
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7f7e83aa4810) = 5279
[...]
```

* `fork()` and `pthread_create()` are `libc` wrappers to the same syscall: `clone()`

---

### Libc vs Linux vs Windows

* Libc approach - `system`:

```console [1 | 2 | 3 | 5 | 7 | 9]
student@os:~/.../compute/lecture/demo/create-process$ strace -ff -e clone,execve ./system
execve("./system", ["./system"], 0x7ffff3f20008 /* 60 vars */) = 0
clone(child_stack=0x7f3fa624aff0, flags=CLONE_VM|CLONE_VFORK|SIGCHLDstrace: Process 117770 attached
 <unfinished ...>
[pid 117770] execve("/bin/sh", ["sh", "-c", "ls -la"], 0x7ffdac7acfe8 /* 60 vars */
[...]
[pid 117770] clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7f9292b28850) = 117771
strace: Process 117771 attached
[pid 117771] execve("/usr/bin/ls", ["ls", "-la"], 0x55c700084048 /* 60 vars */) = 0
[...]
```

----

#### Libc vs Linux vs Windows

* `system` first creates a new shell (`execve("/bin/sh"`)
* This shell now spawns `ls -la` (`execve("/usr/bin/ls", ["ls", "-la"]`)

----

#### Libc vs Linux vs Windows

* Linux approach - `posix_spawn()` and `fork()` + `exec()`:

```console [1 | 2 | 3 | 5 | 7 | 8 | 9 | 11 | 13]
student@os:~/.../compute/lecture/demo/create-process$ strace -ff -e clone,execve ./posix_spawn
execve("./posix_spawn", ["./posix_spawn"], 0x7ffcfed53928 /* 60 vars */) = 0
clone(child_stack=0x7f842691eff0, flags=CLONE_VM|CLONE_VFORK|SIGCHLDstrace: Process 118949 attached
 <unfinished ...>
[pid 118949] execve("/bin/ls", ["-la"], 0x7ffc97832878 /* 60 vars */ <unfinished ...>

student@os:~/.../compute/lecture/demo/create-process$ strace -ff -e clone,execve ./fork_exec
execve("./fork_exec", ["./fork_exec"], 0x7ffdb2c85028 /* 60 vars */) = 0
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLDstrace: Process 119051 attached
[...]
[pid 119051] execve("/home/student/.local/bin/ls", ["-la"], 0x7ffee90fee78 /* 60 vars */) = -1
[...]
[pid 119051] execve("/usr/bin/ls", ["-la"], 0x7ffee90fee78 /* 60 vars */) = 0
```

* The "manual" method (`fork()` + `exec()`) tries all `$PATH` entries before finding `"/usr/bin/ls"`

----

#### Libc vs Linux vs Windows

* Windows approach: `CreateProcess`

```console
PS C:\...\lecture\demo\create-process> .\create_process.exe
[parent] PID = 11876; child PID = 10376; Waiting...
[...]
```

* The command given to `CreateProcess` must specify the interpreter: `cmd`

---

### `fork()` vs `pthread_create()`

```console [1 - 2 | 3 - 4]
student@os:~/.../compute/lecture/demo/create-process$ strace -e clone ./fork_exec
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7f7e83aa4810) = 5302
student@os:~/.../compute/lecture/demo/create-thread$ strace -e clone ./create_thread
clone(child_stack=0x7f9ea7df0fb0, flags=CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|CLONE_CHILD_CLEARTID, tls=0x7f9ea7df1700, child_tidptr=0x7f9ea7df19d0) = 5389
```

* From the flags, the parent and the child **thread** share:
  * `CLONE_VM`: VAS (no copy-on-write)
  * `CLONE_FS`: FS information (root, umask, cwd)
  * `CLONE_FILES`: File descriptor table
  * `CLONE_SIGHAND`: Signal handlers

---

### The Suspended States

![Extended Thread Diagram](./media/thread-states-extended.svg)

----

#### The Suspended States

* **SUSPENDED READY / WAITING:** placed on secondary storage (**swap area**) due to lack of RAM
  * Brought back to READY / WAITING when more RAM is available
* Threads can move from SUSPENDED WAITING to SUSPENDED READY when I/O completes
* Impossible to move from SUSPENDED READY to SUSPENDED WAITING (threads cannot perform I/O calls without running)

---

### Kernel Level Threads

* Advantages:
  * blocking actions only stall current thread
  * hardware (SMP) support
* Disadvantages:
  * slow context switch
  * difficult to implement and maintain
  * kernel space scheduler (more complex)
  * Partial solution: **user level threads**

----

#### Thread Implementations

| User level                       | Kernel level                               |
| :------------------------------: | :----------------------------------------: |
| implemented by libraries         | implemented by the kernel                  |
| blocking actions stall process   | blocking actions only stall current thread |
| more mapped on one kernel thread | provide support for user level threads     |
| Java, Python                     | Linux KThreads, Windows threads            |
