# I/O

We know that a compute system is a collection of hardware and software that modifies data.
This data has to come from _somewhere_.
This _somewhere_ is always outside the compute system:
files, network packets, radio signals, sensor data.

A compute system without output is nearly useless.
It will always run the same code on the same data and, thus, produce the same result.
This may be useful in some narrow cases, such as calculating the decimals of Pi.
However, for more real-world-facing applications such as web servers, operating systems and databases inputs and outputs are mandatory.

The most simplistic representation of a compute system is a black box that receives some input and delivers some output.

![Compute System - Oversimplified](../media/compute-system-oversimplified.svg)

In this session, we will look into how a compute system interacts with the outside world to get and produce these inputs and outputs.

1. [File Handlers](./file-handlers.md)
1. [File Descriptors](./file-descriptors.md)
1. [Redirections](./redirections.md)
1. [Pipes](./pipes.md)
1. [Local I/O in Action](./local-io-in-action.md)
1. [Remote I/O](./remote-io.md)
1. [Networking 101](./networking-101.md)
1. [Client-Server Model](./client-server-model.md)
1. [Beyond Network Sockets](./beyond-network-sockets.md)
1. [File Mappings](./file-mappings.md)
1. [IO Internals](./io-internals.md)
1. [Zero-copy](./zero-copy.md)
1. [Asynchronous I/O](./async-io.md)
1. [I/O Multiplexing](./io-multiplexing.md)
1. [Arena](./arena.md)
