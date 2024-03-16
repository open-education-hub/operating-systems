# Nightly Builds System

## Scenario

We are designing and implementing a nightly builds system, where different components and versions are compiled.
The system receives build requests in the form of build files (e.g., Makefiles).
The reception is done by a dispatcher component, which then forwards the requests to worker components to be executed.
The worker components can (and it's recommended) run on other systems
In this case, the sources for building are located on a shared storage space (network file system).
Dispatcher components collect the build results and, in case of system errors, transmit them to another component.
In case of runs without system errors, they transmit them back to the build requester.

Answer the following questions with "True" or "False" and justify your answer.
The justification should be simple, 2-3 sentences for each answer.

## Questions

1. The dispatcher component is a CPU-intensive process.
Answer: False

1. The connection between the dispatcher component and the worker components can be established through network sockets.
Answer: True

1. To utilize all available resources, worker components should use all system cores.
For this, we prefer a multi-threaded implementation over a multiprocess one.
Answer: False

1. The dispatcher component can run on a Windows system.
Answer: True

1. The dispatcher component can be implemented in an interpreted language (such as Python, Lua, Ruby).
Answer: True

1. Build systems (where workers run) need to have processors specific to the targets they obtain (if we want to compile ARM targets, we need ARM processors).
Answer: False

1. If we measure the time spent by the worker components, we will see that most of the time is spent in user space (user time) compared to kernel space (system time).
Answer: True

1. The storage space requirement is higher for a worker component than for the dispatcher component.
Answer: True

1. The system can function with just one worker component.
Answer: True

1. The dispatcher component does not cause page faults.
Answer: False

1. The dispatcher system can function as both a statically compiled and a dynamically compiled application.
Answer: True
