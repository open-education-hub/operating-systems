# SPDX-License-Identifier: BSD-3-Clause

import socket  # Exposes the Berkely Sockets API
from os import getpid

IP = "127.0.0.1"  # Loopback IP address (localhost)
PORT = 5000  # Port to listen for data data on (non-privileged ports are > 1023)
MAX_MESSAGE_LENGTH = 1024


def main():
    # Create a socket. Do not mind the arguments for now.
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Bind the socket to the IP and port. But this time, it is no longer
    # listening automatically.
    sock.bind((IP, PORT))

    # We must specifically tell the socket to start listening.
    # The argument specifies how many connections to queue up before refusing.
    sock.listen(socket.SOMAXCONN)

    print(f"Server with PID {getpid()} is listening for data on port {PORT}...")

    while True:
        # Create a new socket for the connection. Returns when a client calls
        # `connect()` to the server.
        connection_socket, (ip, port) = sock.accept()
        print(f"Connection established with IP {ip} and port {port}.")

        # Receive at most 1024 bytes data from the socket.
        message = connection_socket.recv(MAX_MESSAGE_LENGTH)

        # The sender had to encode the message from string to bytes. Now decode
        # it back to a string.
        message = message.decode()

        print(f"Received : {message}")

        # If the message is "exit", break out of the loop.
        if message == "exit":
            break

        # Otherwise, send a response back to the client.
        connection_socket.send("Message received.".encode())

        # Close the connection socket.
        connection_socket.close()

    sock.close()


if __name__ == "__main__":
    main()
