---

## Firefox I/O

```console
$ lsof -p $(pidof firefox)
[...]
firefox 32100 student   64u     IPv4           38654330       0t0      TCP so:44750->lb-140-82-112-26-iad.github.com:https (ESTABLISHED)
firefox 32100 student   65u     IPv4           38659353       0t0      TCP so:37528->239.237.117.34.bc.googleusercontent.com:https (ESTABLISHED)
[...]
firefox 32100 student  176u     unix 0x0000000000000000       0t0 38640969 type=SEQPACKET
firefox 32100 student  178u     unix 0x0000000000000000       0t0 38650545 type=SEQPACKET
firefox 32100 student  179u     unix 0x0000000000000000       0t0 38648379 type=STREAM
firefox 32100 student  181r     FIFO               0,13       0t0 38640924 pipe
firefox 32100 student  185u  a_inode               0,14         0    11438 [eventfd]
firefox 32100 student  186uw     REG              259,5    131072 17040026 /home/student/.mozilla/firefox/inonjd9q.default-release/protections.sqlite
firefox 32100 student  188u     unix 0x0000000000000000       0t0 38635209 type=STREAM
[...]
firefox 32100 student  200r      REG                0,1      5196 14538955 /memfd:mozilla-ipc (deleted)
[...]
```

----

### Reminder: I/O: Perspective of the Process

- Communication / Interaction "outside" the process
- "Inside" the process: working with memory, CPU instructions
- "Outside" the process: I/O channels
  - File-like: data comes / goes from / to outside the system
  - Socket-like: data comes / goes from / to another process

---

## Why Do Applications Interact?

- What is the alternative?
  - An application does everything.
  - Lack of modularity
  - Security / Reliability issues
  - Issues of maintainability
- Modularity
- Integration with existing components
  - Software reuse, but without building / linking
