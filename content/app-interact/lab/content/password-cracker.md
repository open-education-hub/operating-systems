# Password Cracker

In this example, we will solve the following problem: given the sha512 hash of a password, we want to obtain the password that generated the hash.

Since a hash function is not reversible, one way to solve this problem is by brute-force: generate all possible word combinations, compute the hash for each word, and compare it with our desired hash value.
This is not feasible for long passwords, so for our example we will consider only passwords containing lowercase letters and having the length of 4.

In order to speed up the entire process, we want to parallelize the solution.
Instead of one process checking all combinations, we'll split the work among multiple processes or threads.

## Multiprocess Version

The code for this version is in `support/password-cracker/password-cracker-multiprocess.c`.

The idea is the following: we create 26 worker processes, where each process will consider passwords that start with one particular letter (the first process will brute-force passwords starting with `a`, the second with `b`, and so on).

Since we are using processes, which are naturally isolated, we need a method of communication.
The main process should be able to send data to the workers and read back results from them.
For this purpose we will use pipes: a pair of 2 pipes between the main process and each worker, one pipe for each direction of communication.

In summary, the flow will look like this:

* main process

  * create worker processes, along with 2 pipes for each worker (one pipe for requests, one for results)

  * send the 'a' character to the first process request pipe, 'b' to the second, etc.

  * read the results from each result pipe

* worker process

  * read one character from the request pipe

  * generate all words of length 4 that begin with that character

  * for each generated word, compute the sha512 hash and compare it with the desired hash

  * if there is a match, write it to the result pipe

Let's build and run the program:

```console
student@os:~/.../support/password-cracker$ make
gcc -Wall -o password-cracker-multiprocess password-cracker-multiprocess.c -lcrypto
gcc -Wall -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -o password-cracker-multithread password-cracker-multithread.c -lcrypto -lpthread

student@os:~/.../support/password-cracker$ ./password-cracker-multiprocess
worker 7 found haxx
```

### Practice

Creating 26 processes is not very realistic, since it's unlikely that a usual machine has that many cores.

Modify the program so that it only creates 4 workers.
Each worker will receive 2 characters instead of one, defining an interval to search.
For example, the first worker will receive `a` and `f`, meaning it will brute-force passwords starting with `a`, `b`, `c`, `d`, `e`, or `f`, the second `g` - `l`, and so on.

## Multithreaded Version

Check out the code in `support/password-cracker/password-cracker-multithread.c`.

The core idea of the program is the same, but now we're using threads instead of processes.

This makes the communication easier: we'll use the thread function argument to send the first character of the password to each thread.
As for the result, each thread will return it as the return value of the thread function.

```console
student@os:~/.../support/password-cracker$ ./password-cracker-multithread
worker 7 found haxx
```

## Multiprocess Version in Python (1)

Code in `support/password-cracker/python/password-cracker-multiprocess-1.py`.

This is the Python equivalent of the previous multiprocess version. The program structure is the same, but Python has a few nice features that make our life easier:

* there is a `Process` object that takes a function argument and spawns a new process that begins execution from that function.
No need to call `fork` manually.

* the `Pipe` object in Python is already bidirectional, unlike the OS pipes, which are unidirectional.
So we don't need to create 2 pipes for each direction.

* we don't have to write the code that generates all the password combinations, `itertools.product` will do it for us

```console
student@os:~/.../support/password-cracker$ python3 python/password-cracker-multiprocess-1.py
worker 7 found haxx
```

## Multiprocess Version in Python (2)

Code in `support/password-cracker/python/password-cracker-multiprocess-2.py`.

In this case, the code looks different than in the previous examples.
Now we are taking advantage of some Python constructs, namely `process pools`, which are a collection of worker processes.

A `Pool` object has, among others, a function called `map`.
`map` takes a function, together with an array of values, and applies this function on each value from the array.
At first glance, it might look like the usual `map` function, but with the key difference that the function application is done by the processes from the pool.

In other words, the work is distributed to the worker processes from the pool, and all the communication that we had to handle in the previous examples is done behind the scenes, greatly simplifying the code.

```console
student@os:~/.../support/password-cracker$ python3 python/password-cracker-multiprocess-2.py
worker 7 found haxx
```

### Practice

Check that the `worker` function is indeed called from different worker processes.
One simple way to do this is to print out the current process ID at the beginning of the function.
To get the current process ID, use the `getpid` function from the `os` module.

## Multithreaded Version in Python

Code in `support/password-cracker/python/password-cracker-multithread.py`.

The Python equivalent of the previous multithreaded version.

```console
student@os:~/.../support/password-cracker$ python3 python/password-cracker-multithread.py
worker 7 found haxx
```

This example is given only to provide an idea of how a multithreaded program is written.
Remember that CPU-bound threads in python don't actually run in parallel, due to the Global Interpreter Lock.
