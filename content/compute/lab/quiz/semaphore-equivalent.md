# Semaphore Equivalent

## Question Text

From running and inspecting the code in `support/apache2-simulator/apache2_simulator_semaphore.py`, which of the following is an an equivalent to the value of the semaphore `sem`?

## Question Answers

- The value of `msg_mutex`

- The time a worker thread has to wait before running

+ The length of the `messages` list

- The number of worker threads

## Feedback

`sem` is incremented (`release()`) upon adding a message to the `messages` list and decremented (`acquire()`) when removing a message from said list.
So it's a rough equivalent to the length of this list.
