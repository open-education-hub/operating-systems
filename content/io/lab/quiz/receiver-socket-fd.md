# Receiver Socked File Descriptor

## Question Text

What is the type of the file descriptor that corresponds to the socket created by `support/send-receive/receiver.py`?

## Question Answers

- only file descriptors that are linked to files have types

- `DIR`

- `REG`

- `CHR`

+ `IPv4`

## Feedback

Running `lsof` yields the following output:

```console
student@os:~$ lsof -p 59681
COMMAND   PID USER   FD   TYPE DEVICE SIZE/OFF    NODE NAME
python3 59681  student  cwd    DIR    8,1        0  559322 /home/student/operating-systems-oer/content/chapters/io/lab/support/send-receive
python3 59681  student  rtd    DIR  259,6     4096       2 /
python3 59681  student  txt    REG  259,6  5502744 1835857 /usr/bin/python3.8
python3 59681  student  mem    REG  259,6  8631488 1835827 /usr/lib/locale/locale-archive
python3 59681  student  mem    REG  259,6   108936 1835887 /usr/lib/x86_64-linux-gnu/libz.so.1.2.11
python3 59681  student  mem    REG  259,6   182560 1836149 /usr/lib/x86_64-linux-gnu/libexpat.so.1.6.11
python3 59681  student  mem    REG  259,6  1369384 1857443 /usr/lib/x86_64-linux-gnu/libm-2.31.so
python3 59681  student  mem    REG  259,6    14880 1857476 /usr/lib/x86_64-linux-gnu/libutil-2.31.so
python3 59681  student  mem    REG  259,6    18848 1857439 /usr/lib/x86_64-linux-gnu/libdl-2.31.so
python3 59681  student  mem    REG  259,6   157224 1857471 /usr/lib/x86_64-linux-gnu/libpthread-2.31.so
python3 59681  student  mem    REG  259,6  2029592 1857435 /usr/lib/x86_64-linux-gnu/libc-2.31.so
python3 59681  student  mem    REG  259,6    27002 2506848 /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache
python3 59681  student  mem    REG  259,6   191504 1835092 /usr/lib/x86_64-linux-gnu/ld-2.31.so
python3 59681  student    0u   CHR  136,1      0t0       4 /dev/pts/1
python3 59681  student    1u   CHR  136,1      0t0       4 /dev/pts/1
python3 59681  student    2u   CHR  136,1      0t0       4 /dev/pts/1
python3 59681  student    3u  IPv4 588386      0t0     UDP localhost:5000
```

The last line displays the socket:

```console
python3 59681  student    3u  IPv4 588386      0t0     UDP localhost:5000
```

Its type is written on the the 5th column: `IPv4` because it's a network socket.
