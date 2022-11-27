# Both Condition and Mutex

## Question Text

Can we only use a mutex when signalling an event from one thread to another in?

## Question Answers

+ No, because this would imply that the signalling thread would `unlock()` the mutex, that the signalled thread attempts to `lock()`, which is an undefined behaviour

- No, because it will result in a deadlock where the both threads will be waiting for each other

- Yes, because only one thread can modify the shared variables in order to maintain their integrity

- Yes and this would yield better performance because the threads would only wait for one object: the mutex

## Feedback

In some implementations, such as [POSIX threads (pthreads)](https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_lock.html), calling `unlock()` from another thread than that which called `lock()` can result in an undefined behaviour.
For this reason, it is unsafe to only use a mutex as a notification mechanism.
In addition, a mutex cannot notify more than one thread at once, if we so desire.
Mutexes are only meant to be used to isolate a critical section within the same thread.
