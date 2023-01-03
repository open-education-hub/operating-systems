#!/usr/bin/env python3

# SPDX-License-Identifier: BSD-3-Clause

import logging
import random
import socket
import sys


def handle(connection, num):
    if num == -1:
        num = random.randrange(35)

    logging.info("Sending %d", num)
    connection.send(str(num).encode("utf-8"))
    response = connection.recv(256).decode("utf-8")
    print("function({:d}): {}".format(num, response))

    connection.close()


def run_client(server_name, server_port, num=-1):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((server_name, server_port))

    logging.info("Connected to %s:%d", server_name, server_port)
    handle(sock, num)


def main():
    logging.basicConfig(level=logging.INFO, format="%(name)s: %(message)s")
    random.seed()

    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print(
            "Usage: {} server_name server_port [num]".format(sys.argv[0]),
            file=sys.stderr,
        )
        print("  0 <= num <= 34", file=sys.stderr)
        sys.exit(1)

    server_name = sys.argv[1]
    server_port = int(sys.argv[2])
    if len(sys.argv) == 4:
        num = int(sys.argv[3])
        run_client(server_name, server_port, num)
    else:
        run_client(server_name, server_port)


if __name__ == "__main__":
    sys.exit(main())
