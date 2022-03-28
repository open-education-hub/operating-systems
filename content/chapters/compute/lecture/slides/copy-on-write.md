---

## Copy-on-write

---

### Copy-on-write

When `fork` returns, the child duplicates the contents of the parent's page table.

![Copy-on-write after fork()](./media/copy-on-write-initial.svg)

----

#### Copy-on-write

* Writable pages are **copied and modified only** when written: `demo/copy-on-write/copy_on_write_overhead.c`
* [Quiz](../quiz/sections-always-shared.md)

![Copy-on-write after Write](./media/copy-on-write-final.svg)

----

#### Copy-on-write Overheard

* Writes cause minor page faults

```console
student@os:~/.../compute/lecture/demo/copy-on-write$ ./copy_on_write_overhead
 * Child process started
 -- Press ENTER to continue ...
Time for reading 131072 pages: 30 ms
 * Child process read pages
 -- Press ENTER to continue ...
Time for writing to 131072 pages: 222 ms
[...]
```

* The child process performs exactly 131072 **minor** page faults when writing data

```console
student@os:~$ cat /proc/`pidof copy_on_write_overhead`/stat | cut -d ' ' -f 10  # before writing
22
student@os:~$ cat /proc/`pidof copy_on_write_overhead`/stat | cut -d ' ' -f 10  # after writing
131094
```
