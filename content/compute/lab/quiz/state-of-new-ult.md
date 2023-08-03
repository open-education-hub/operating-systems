# State of new ULT

## Question Text

What is the first state that is assigned to a newly created ULT?

## Question Answers

- RUNNING
- READY
- COMPLETED

## Feedback

Inside the function `threads_create()`, we can see the following snippet `queue_enqueue(ready, new)`.
Each new thread is thus added to the READY queue.
