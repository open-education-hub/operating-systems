# Sleeping on a Fiber

## Question Text

What happens if a fiber calls `sleep()`?

## Question Answers

+ the whole kernel-level thread is blocked

- only that fiber is blocked, and is scheduled out

- nothing, a fiber can't sleep

- the whole process sleeps - regardless of how many threads there are

## Feedback

The whole thread on which the fiber runs is blocked until the `sleep()` call is finished.
For this reason, the fibers are best used with asynchronous operations, which you will explore in the following weeks.
