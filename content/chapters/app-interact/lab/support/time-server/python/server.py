# SPDX-License-Identifier: BSD-3-Clause

import socket
import struct
import sys
import time


def create_socket(addr, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    sock.bind((addr, port))
    sock.listen(10)

    return sock


def main():
    addr = "0.0.0.0"
    port = 2000

    try:
        sock = create_socket(addr, port)
    except Exception as ex:
        print(f"Couldn't create socket: {ex}", file=sys.stderr)
        return

    while True:
        try:
            cl_sock, remote_addr = sock.accept()
            print(f"Got connection from {remote_addr[0]}:{remote_addr[1]}")

            current_time = int(time.time())

            cl_sock.sendall(struct.pack(">I", 8))
            cl_sock.sendall(struct.pack(">Q", current_time))

            cl_sock.close()
        except Exception as ex:
            print(f"Client handling failed: {ex}", file=sys.stderr)


if __name__ == "__main__":
    main()
