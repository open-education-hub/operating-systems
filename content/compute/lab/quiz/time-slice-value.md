# Time Slice Value

## Question Text

Using the [man page](https://man7.org/linux/man-pages/man2/setitimer.2.html), what is the time slice used by the scheduler in `libult.so`?

## Question Answers

- 100 milliseconds

- 10 microseconds

- 100 microseconds

+ 10 milliseconds

## Feedback

The code we're interested in lies in the function `init_profiling_timer()`:

```C
const struct itimerval timer = {
	{ 0, 10000 },
	{ 0, 1 }  // arms the timer as soon as possible
};
```

The [man page](https://man7.org/linux/man-pages/man2/setitimer.2.html) gives the following definition the `struct itimerval`:

```C
struct itimerval {
	struct timeval it_interval; /* Interval for periodic timer */
	struct timeval it_value;    /* Time until next expiration */
};

struct timeval {
	time_t      tv_sec;         /* seconds */
	suseconds_t tv_usec;        /* microseconds */
};
```

So when constructing the `timer` variable, `{ 0, 10000 }` means 0 seconds and 10000 microseconds, i.e. 0 seconds and 10 milliseconds.
