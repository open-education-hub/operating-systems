#!/usr/bin/env python3

# SPDX-License-Identifier: BSD-3-Clause

import logging
import socket
import sys


def fibonacci(num):
    if num in (0, 1):
        return 1
    return fibonacci(num - 1) + fibonacci(num - 2)


def handle(connection, address):
    logging.info("Received connection from %s", address)
    response = ""
    try:
        msg = connection.recv(256).decode("utf-8")
        logging.debug("Message: %s", msg)
        num = int(msg)
        if num < 0 or num > 34:
            response = "out of range"
        response = str(fibonacci(num))
    except ValueError:
        response = "error"

    connection.send(response.encode("utf-8"))

    connection.close()


LISTEN_BACKLOG = 10


def run_server(port, hostname="0.0.0.0"):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((hostname, port))
    sock.listen(LISTEN_BACKLOG)

    while True:
        conn, address = sock.accept()
        handle(conn, address)


def main():
    logging.basicConfig(level=logging.DEBUG, format="%(name)s: %(message)s")

    if len(sys.argv) != 2:
        print("Usage: {} port".format(sys.argv[0]), file=sys.stderr)
        sys.exit(1)

    port = int(sys.argv[1])
    logging.info("Starting server on port {:d}".format(port))
    run_server(port)


if __name__ == "__main__":
    sys.exit(main())
