# Usage of Processes and Threads in `apache2`

We'll take a look at how a real-world application - the `apache2` HTTP server - makes use of processes and threads.
Since the server must be able to handle multiple clients at the same time, it must therefore use some form of concurrency.
When a new client arrives, the server offloads the work of interacting with that client to another process or thread.

The choice of whether to use multiple processes or threads is not baked into the code.
Instead, `apache2` provides a couple of modules called MPMs (Multi-Processing Modules).
Each module implements a different concurrency model, and the users can pick whatever module best fits their needs by editing the server configuration files.

The most common MPMs are

- `prefork`: there are multiple worker processes, each process is single-threaded and handles one client request at a time
- `worker`: there are multiple worker processes, each process is multi-threaded, and each thread handles one client request at a time
- `event`: same as `worker` but designed to better handle some particular use cases

In principle, `prefork` provides more stability and backwards compatibility, but it has a bigger overhead.
On the other hand, `worker` and `event` are more scalable, and thus able to handle more simultaneous connections, due to the usage of threads.
On modern systems, `event` is almost always the default.

## `apache2` Live Action

Let's run an actual instance of `apache2` and see how everything works.
Go to `support/apache2` and run `make run`.
This will start a container with `apache2` running inside.

Check that the server runs as expected:

```console
student@os:~$ curl localhost:8080
<html><body><h1>It works!</h1></body></html>
```

Now go inside the container and take a look at running processes:

```console
student@os:~/.../lab/support/apache2$ docker exec -it apache2-test bash

root@56b9a761d598:/usr/local/apache2# ps -ef
UID          PID    PPID  C STIME TTY          TIME CMD
root           1       0  0 20:38 pts/0    00:00:00 httpd -DFOREGROUND
www-data       9       1  0 20:38 pts/0    00:00:00 httpd -DFOREGROUND
www-data      10       1  0 20:38 pts/0    00:00:00 httpd -DFOREGROUND
root          25       0  0 20:40 pts/1    00:00:00 bash
root          31      25  0 20:40 pts/1    00:00:00 ps -ef
```

We see 3 `httpd` processes.
The first one, running as root, is the main process, while the other 2 are the workers.

Let's confirm that we are using the `event` mpm:

```console
root@56b9a761d598:/usr/local/apache2# grep mod_mpm conf/httpd.conf
LoadModule mpm_event_module modules/mod_mpm_event.so
LoadModule mpm_prefork_module modules/mod_mpm_prefork.so
LoadModule mpm_worker_module modules/mod_mpm_worker.so
```

The `event` mpm is enabled, so we expect each worker to be multithreaded.
Let's check:

```console
root@56b9a761d598:/usr/local/apache2# ps -efL
UID          PID    PPID     LWP  C NLWP STIME TTY          TIME CMD
root           1       0       1  0    1 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       8       1       8  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       8       1      11  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       8       1      12  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       8       1      16  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       8       1      17  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       8       1      18  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       8       1      19  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       9       1       9  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       9       1      14  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       9       1      15  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       9       1      20  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       9       1      21  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       9       1      22  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data       9       1      23  0    7 20:56 pts/0    00:00:00 httpd -DFOREGROUND
root          24       0      24  1    1 20:56 pts/1    00:00:00 bash
root          30      24      30  0    1 20:56 pts/1    00:00:00 ps -efL
```

Indeed, each worker has 7 threads.
In fact, the number of threads per worker is configurable, as well as the number of initial workers.

When a new connection is created, it will be handled by whatever thread is available from any worker.
If all the threads are busy, then the server will spawn more worker processes (and therefore more threads), as long as the total number of threads is below some threshold, which is also configurable.

Let's see this dynamic scaling in action.
We need to create a number of simultaneous connections that is larger than the current number of threads.
There is a simple script in `support/apache2/make_conn.py` to do this:

```console
student@os:~/.../lab/support/apache2$ python3 make_conn.py localhost 8080
Press ENTER to exit
```

The script has created 100 connections and will keep them open until we press Enter.

Now, in another terminal, let's check the situation inside the container:

```console
student@os:~/.../lab/support/apache2$ docker exec -it apache2-test bash

root@56b9a761d598:/usr/local/apache2# ps -efL
UID          PID    PPID     LWP  C NLWP STIME TTY          TIME CMD
root           1       0       1  0    1 20:56 pts/0    00:00:00 httpd -DFOREGROUND
www-data      40       1      40  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      40       1      45  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      40       1      46  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      40       1      51  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      40       1      52  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      40       1      53  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      40       1      54  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      55       1      55  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      55       1      58  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      55       1      60  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      55       1      62  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      55       1      63  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      55       1      65  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data      55       1      66  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
[...]
www-data     109       1     109  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data     109       1     115  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data     109       1     116  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data     109       1     121  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data     109       1     122  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data     109       1     123  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
www-data     109       1     124  0    7 21:07 pts/0    00:00:00 httpd -DFOREGROUND
root         146       0     146  0    1 21:10 pts/1    00:00:00 bash
root         152     146     152  0    1 21:10 pts/1    00:00:00 ps -efL
```

We see a much larger number of threads, as expected.

## Practice: Investigate `apache2` Using `strace`

Use `strace` to discover the server document root.
The document root is the path in the filesystem from where `httpd` serves all the files requested by the clients.

First, you will have to stop the running container using `make stop`, then restart it with `make run-privileged`.

Then you will use `strace` inside the container to attach to the worker processes (use the `-p` option for this).
You will also have to use the `-f` flag with `strace`, so that it will follow all the threads inside the processes.

After you have attached successfully to all worker processes, use the `curl` command to send a request, like the one in the beginning of this section.

Then check the `strace` output to see what files were opened by the server.

[Quiz](../quiz/apache2-strace.md)

## Conclusion

So far, you've probably seen that spawning a process can "use" a different program (hence the path in the args of `system` or `Popen`), but some languages such as Python allow you to spawn a process that executes a function from the same script.
A thread, however, can only start from a certain entry point **within the current address space**, as it is bound to the same process.
Concretely, a process is but a group of threads.
For this reason, when we talk about scheduling or synchronization, we talk about threads.
A thread is, thus, an abstraction of a task running on a CPU core.
A process is a logical group of such tasks.

We can sum up what we've learned so far by saying that processes are better used for separate, independent work, such as the different connections handled by a server.
Conversely, threads are better suited for replicated work: when the same task has to be performed on multiple cores.
However, replicated work can also be suited for processes.
Distributed applications, however, leverage different processes as this allows them to run on multiple physical machines at once.
This is required by the very large workloads such applications are commonly required to process.

These rules are not set in stone, though.
Like we saw in the `apache2` example, the server uses multiple threads as well as multiple processes.
This provides a degree of stability - if one worker thread crashes, it will only crash the other threads belonging to the same process - while still taking advantage of the light resource usage inherent to threads.

These kinds of trade-offs are a normal part of the development of real-world applications.
