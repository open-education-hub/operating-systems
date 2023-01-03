# SPDX-License-Identifier: BSD-3-Clause

import socket  # Exposes the Berkely Sockets API
from os import getpid

IP = "127.0.0.1"  # Loopback IP address (localhost)
MAX_MESSAGE_LENGTH = 1024
PORT = 5000  # Port to listen for data data on (non-privileged ports are > 1023)


def main():
    # Create a socket. Do not mind the arguments for now.
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    # Bind the socket to the IP and port. This registers the current process as
    # "listening" for data on the port.
    sock.bind((IP, PORT))

    print(f"Server with PID {getpid()} is listening for data on port {PORT}...")

    while True:
        # Receive at most 1024 bytes data from the socket.
        message, (ip, port) = sock.recvfrom(MAX_MESSAGE_LENGTH)

        # The sender had to encode the message from string to bytes. Now decode
        # it back to a string.
        message = message.decode()

        # Print the message.
        print(f"Received from IP {ip} and port {port}: {message}")

        # If the message is "exit", break out of the loop.
        if message == "exit":
            break

    sock.close()


if __name__ == "__main__":
    main()
