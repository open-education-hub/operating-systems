# SPDX-License-Identifier: BSD-3-Clause

import socket
from threading import Thread

IP = "127.0.0.1"
READ_SEND_PORT = 8081
SENDFILE_PORT = 8082
FILE_NAME = "large-file.txt"


def read_send_server():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((IP, READ_SEND_PORT))
    sock.listen(socket.SOMAXCONN)

    while True:
        connection_socket, _ = sock.accept()

        with open(FILE_NAME, "rb") as f:
            file = f.read()
            connection_socket.sendall(file)

        connection_socket.close()


def sendfile_server():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((IP, SENDFILE_PORT))
    sock.listen(socket.SOMAXCONN)

    while True:
        connection_socket, _ = sock.accept()

        with open(FILE_NAME, "rb") as f:
            connection_socket.sendfile(f)

        connection_socket.close()


def main():
    read_send_thread = Thread(target=read_send_server)
    read_send_thread.start()

    sendfile_thread = Thread(target=sendfile_server)
    sendfile_thread.start()

    read_send_thread.join()
    sendfile_thread.join()


if __name__ == "__main__":
    main()
