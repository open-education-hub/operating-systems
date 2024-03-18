# Supervisor-type Service

## Scenario

A supervisor-type service is one used to start, stop, restart, and control other processes/services.
Based on a configuration, the supervisor can start, stop, restart, or report the status of other services it controls.
Additionally, the supervisor can monitor the status of a process and restart it if it terminates erroneously (e.g., due to a segmentation fault or other exception, or forced termination with a signal).

We aim to implement a supervisor-type service.
It will have one or more configuration files and a control program that users will use to send commands to the service: `start`, `stop`, `restart`, `status`, `read_conf`, `list`.

Answer the following questions with "True" or "False" and justify your answer.
The justification should be simple, 2-3 sentences for each answer.

## Questions

1. The service can be implemented and run only on POSIX/UNIX systems.
Answer: False

1. The service starts/restarts other processes through `fork()`/`exec()` calls (or equivalents).
Answer: True

1. Communication between the control program and the supervisor-type service can be done via UNIX sockets.
Answer: True

1. The service must run in privileged mode (with root privileges).
Answer: False

1. The service will be able to stop processes started through commands transmitted via pipes.
Answer: False

1. The service will be able to detect the erroneous termination of started processes through a `wait()`/`waitpid()` call.
Answer: True

1. Two or more supervisor-type services can coexist on the same system.
Answer: True

1. The service is a CPU-intensive process.
Answer: False

1. The services started by the supervisor service can coexist as threads of the supervisor process.
Answer: False

1. The service can configure the started processes to have standard descriptors redirected to a `/dev/null`-like input.
Answer: True

1. The service can memory-map the configuration file.
Answer: True
