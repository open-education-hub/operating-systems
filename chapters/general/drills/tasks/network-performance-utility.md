# Network Performance Utility

## Scenario

We aim to implement a utility to measure network performance similar to tools like iperf or speedtest.
This utility will present metrics such as bandwidth (download and upload), network latency/response time (also known as RTT - round trip time) for various sites.
Typically, the utility will establish multiple connections/transfers and display their average.

Respond to the following questions with "True" or "False" and justify the answer.
The justification should be simple, 2-3 sentences for each answer.

## Questions

1. The utility can use UNIX sockets for measurements.
Answer: False

1. The process started by the utility is I/O-intensive.
Answer: True

1. To function on systems with wireless connection, the utility needs to be started with privileged rights.
Answer: False

1. The process started by the utility will heavily use buffer cache.
Answer: False

1. The utility can be written in an interpreted language like Python.
Answer: True

1. For efficient operation of the utility's process, the limit of file descriptor table needs to be increased above 1024.
Answer: False

1. The process started by the utility will consume a lot of RAM.
Answer: False

1. To achieve the best results, the utility should be used at a time when other applications are using very little or no network.
Answer: True

1. Hardware interrupts will be generated during the use of the utility.
Answer: True

1. The process started by the utility will use shared memory mechanisms.
Answer: False

1. The process started by the utility is a component that requires additional security/isolation compared to other processes.
Answer: False
