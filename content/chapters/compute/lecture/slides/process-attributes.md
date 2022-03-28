---

### Process Attributes

---

#### Process Attributes - from User Space

```console
student@os:~$ ps -e --forest -o pid,ppid,rss,vsz,etime,stat,comm
  PID  PPID   RSS    VSZ     ELAPSED STAT COMMAND
    1     0   600    988  2-02:44:02 Sl   init
  914     1    88    900  2-02:14:06 S    init
 2582   914  3376  82956  1-04:15:56 Ss    \_ gpg-agent
19812     1   176    988    09:03:34 Ss   init
19813 19812   176    988    09:03:34 S     \_ init
19814 19813  6420  11256    09:03:34 Ss        \_ bash
21713 19814  3132  10696       00:00 R+            \_ ps
20650     1   176    988    05:43:41 Ss   init
20651 20650   176    988    05:43:41 S     \_ init
20652 20651   604   2612    05:43:41 Ss+       \_ sh
20653 20652   536   2612    05:43:41 S+            \_ sh
20658 20653   604   2612    05:43:41 S+                \_ sh
20661 20658 74072 931768    05:43:41 Sl+                   \_ node
20681 20661 44316 614424    05:43:40 Sl+                       \_ node
20722 20661 39804 828152    05:43:40 Sl+                       \_ node
20733 20661 147004 845832   05:43:40 Sl+                       \_ node
20796 20733 119336 959952   05:43:38 Sl+                           \_ node
21149 20733 41080 581504    04:31:20 Sl+                           \_ node
20672     1   176    988    05:43:40 Ss   init
20673 20672   176    988    05:43:40 S     \_ init
20674 20673 41556 585172    05:43:40 Ssl+      \_ node
20701     1   176    988    05:43:40 Ss   init
20702 20701   176    988    05:43:40 S     \_ init
20703 20702 48060 590308    05:43:40 Ssl+      \_ node
20915     1   176    988    05:24:46 Ss   init
20916 20915   176    988    05:24:46 S     \_ init
20917 20916  5268  10188    05:24:46 Ss        \_ bash
20964 20917 19840 516296    05:24:32 S+            \_ python3
20981     1   176    988    05:22:54 Ss   init
20982 20981   176    988    05:22:54 S     \_ init
20983 20982  5100  10056    05:22:54 Ss+       \_ bash
```

----

#### Process Attributes - from Kernel Space

* Process Control Block (PCB):
  * Data structure in the kernel
    * [`task_struct`](https://elixir.bootlin.com/linux/v5.19.6/source/include/linux/sched.h#L726) in Linux
    * [`EPROCESS`](https://www.nirsoft.net/kernel_struct/vista/KPROCESS.html) in Windows
    * [`proc`](https://github.com/apple/darwin-xnu/blob/main/bsd/sys/proc_internal.h#L182) on XNU, the Apple iOS / macOS kernel
  * All information about the process (from `ps`, `/proc`)
  * Threads use a **Thread Control Block (TCB)**
    * the [execution context](https://linux.die.net/man/2/setcontext) is a **thread**

----

#### Process Attributes - from Kernel Space

The most important fields in `task_struct`:

```c [2 | 4 | 6 | 8 - 9 | 11 - 13 | 15 - 16 | 18 - 19 | 21 | 23 | 25 - 26 | 28 - 29]
struct task_struct {
        unsigned int                    __state;

        void                           *stack;

        unsigned int                    flags;

        int                             on_cpu;
        int                             prio;

        /* Scheduler information */
        struct sched_entity             se;
        const struct sched_class        *sched_class;

        /* The VAS: memory mappings */
        struct mm_struct                *mm;

        int                             exit_state;
        int                             exit_code;

        pid_t                           pid;

        struct task_struct __rcu        *parent;

        /* Child processes */
        struct list_head                children;

        /* Open file information */
        struct files_struct             *files;
};
```
