# Coarse vs Granular Critical Section

## Question Text

Why does code with the the larger (coarser) critical section run faster than the one with the smaller (more granular) critical section?

## Question Answers

+ Because the more granular code causes more context switches, which are expensive

- Because the coarser code can be better optimised by the compiler

- Because the loops in the more granular code run for more steps

## Feedback

The larger critical sections only require **2 context switches**.
The first thread that reaches the call to `lock()` acquires to the mutex and starts executing the whole of the `for` loop.
The second thread then finds the mutex _locked_ and enters the WAITING state.
When the first thread finishes its loop, it calls `unlock()` and wakes up the second thread, which acquires the lock and starts its loop.

In the more granular example, in the worst case, the holder of the mutex can change at every step of the loop.
This would mean 1 context switch per step per thread, i.e. **20 million context switches**.
