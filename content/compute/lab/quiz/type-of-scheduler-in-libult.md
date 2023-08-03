# Type of Scheduler in `libult.so`

## Question Text

Inspect the code in `support/libult/threads.c` further.
Which type of scheduler does `libult.so` use?

## Question Answers

+ It uses a preemptive scheduler

- It uses a cooperative scheduler

- It uses both a cooperative and a preemptive scheduler

## Feedback

`libult.so` uses a preemptive scheduler.
Its timer is initialised in the `init_profiling_timer()` function.
The context switch is performed in the `handle_sigprof()` function.
