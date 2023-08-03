# Fewer than Two Copies

## Question Text

Can zero-copy be implemented so as to copy the file fewer than 2 times?

![Zero-Copy](../media/server-copies-zero-copy.svg)

## Question Answers

- Yes, by copying the file straight from the disk to the network

+ No

- Yes, by sending the file straight from the kernel buffer to the network

- Yes, by copying the file directly from the storage to the NIC's buffer

## Feedback

The truth is that we can't have fewer copies while using a server with a common PC-like architecture.
The disk is not directly connected to the internet, so the file cannot be sent directly from there.
The only place from where we can send data to the Web is the NIC.
Then we need the intermediary storage in that kernel buffer because the disk and the NIC aren't dirrectly connected.
They are both connected to the CPU via the motherboard, so it's the CPU's job to do the transfer.
For this, it needs a "temporary buffer".
Then the NIC needs its own buffer because the speed of the network may be slower than the speed at which it receives data from the kernel, so it needs some memory where to place the "surplus" while waiting for the network to "clear".
