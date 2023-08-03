# SPDX-License-Identifier: BSD-3-Clause

import socket  # Exposes the Berkely Sockets API

IP = "127.0.0.1"  # Loopback IP address (localhost)
PORT = 5000  # Port to send data to (non-privileged ports are > 1023)


def main():
    # Create a socket. Do not mind the arguments for now.
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    while True:
        # Get user input as a string.
        message = input("Message for receiver (type 'exit' to quit): ")

        # Send the message to the server. The message must be encoded to bytes.
        sock.sendto(message.encode(), (IP, PORT))

        # If the message is "exit", break out of the loop.
        if message == "exit":
            break

    sock.close()


if __name__ == "__main__":
    main()
