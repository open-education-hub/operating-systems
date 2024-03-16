# Benchmarking Application

## Scenario

We aim to implement a web application benchmarking solution.
This application will perform web client actions towards a remote web application to obtain metrics such as response time, scalability (how response time degrades with the number of simultaneous connections to the application), with variations for request or response size.

Answer the following questions with "True" or "False" and justify the answer.
Justification should be simple, 2-3 sentences for each answer.

## Questions

1. The benchmarking application uses network sockets.
Answer: True

1. The benchmarking application is required to be multi-threaded.
Answer: False

1. The benchmarking application has more voluntary context switches than involuntary ones.
Answer: True

1. The benchmarking application must run as a privileged user.
Answer: False

1. Two benchmarking applications can run simultaneously on the same system.
Answer: True

1. The benchmarking application heavily uses the system's disk/storage.
Answer: False

1. The benchmarking application must be implemented in a compiled language, not an interpreted one.
Answer: False

1. The benchmarking application can be implemented as a static executable.
Answer: True

1. Running the benchmarking application on the same station as the web application provides better results than remote testing.
Answer: True

1. With the necessary modifications, the application can handle both HTTP and HTTPS connections.
Answer: True

1. The benchmarking application can only measure open-source web applications + open-source web servers (with available sources).
Answer: False
