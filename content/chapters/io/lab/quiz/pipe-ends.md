# Pipe Ends

## Question Text

Which end of a pipe created by `pipe()` is for reading and which one is for writing?

## Question Answers

+ `pipefds[0]` is for reading;
`pipefds[1]` is for writing

- `pipefds[0]` is for writing;
`pipefds[1]` is for reading

- both heads are for reading and writing;

## Feedback

Running the binary first tells us which file descriptor is which:

```console
student@os:~/.../lab/support/pipes$ ./anonymous_pipes
pipedes[0] = 3; pipedes[1] = 4
 * pipe created
 -- Press ENTER to continue ...
```

Then `lsof` gives us the complete answer:

```console
student@os:~/.../lab/support/pipes$ lsof -w -p $(pidof anonymous_pipes)
anonymous 22474  teo  cwd    DIR    8,1      504  296964 /media/teo/2TB/Chestii/Poli/Asistent/SO/operating-systems-oer/content/chapters/io/lab/support/pipes
anonymous 22474  teo  rtd    DIR  259,6     4096       2 /
anonymous 22474  teo  txt    REG    8,1    26712  296968 /media/teo/2TB/Chestii/Poli/Asistent/SO/operating-systems-oer/content/chapters/io/lab/support/pipes/anonymous_pipes
anonymous 22474  teo  mem    REG  259,6  2029592 1857435 /usr/lib/x86_64-linux-gnu/libc-2.31.so
anonymous 22474  teo  mem    REG  259,6   191504 1835092 /usr/lib/x86_64-linux-gnu/ld-2.31.so
anonymous 22474  teo    0u   CHR  136,0      0t0       3 /dev/pts/0
anonymous 22474  teo    1u   CHR  136,0      0t0       3 /dev/pts/0
anonymous 22474  teo    2u   CHR  136,0      0t0       3 /dev/pts/0
anonymous 22474  teo    3r  FIFO   0,13      0t0  252007 pipe
anonymous 22474  teo    4w  FIFO   0,13      0t0  252007 pipe
```

The last 2 lines are the 2 ends of the pipe:
3 and 4.
Note each of these numbers is followed by a letter.
As you might have guessed:

- `r` means "read"
- `w` means "write"
- `u` means both "read" and "write"

Also, the [man page](https://man7.org/linux/man-pages/man2/pipe.2.html) is quite clear on this issue:

> `pipefd[0]` refers to the read end of the pipe.  `pipefd[1]` refers
> to the write end of the pipe.
