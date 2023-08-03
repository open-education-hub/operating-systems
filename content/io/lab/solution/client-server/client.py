# SPDX-License-Identifier: BSD-3-Clause

import socket  # Exposes the Berkely Sockets API

IP = "127.0.0.1"  # Loopback IP address (localhost)
MAX_MESSAGE_LENGTH = 1024
PORT = 5000  # Port to send data to (non-privileged ports are > 1023)


def main():
    while True:
        # Get user input as a string.
        message = input("Message for receiver (type 'exit' to quit): ")

        # TODO: Create a TCP socket (SOCK_STREAM).
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # TODO: connect to the server.
        # `connect()` returns when the server `accept()`s the connection.
        sock.connect((IP, PORT))

        # TODO: send the message to the server. The message must be encoded to
        # bytes.
        sock.send(message.encode())

        # TODO: if the message is "exit", break out of the loop.
        if message == "exit":
            break

        # TODO: receive the response from the server.
        response = sock.recv(MAX_MESSAGE_LENGTH).decode()

        # Print the response.
        print(f"Received from server: {response}")

        # TODO: close the socket.
        sock.close()


if __name__ == "__main__":
    main()
