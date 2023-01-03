# SPDX-License-Identifier: BSD-3-Clause

import socket
import sys
from timeit import default_timer as timer

SERVER_IP = "127.0.0.1"

READ_SEND_PORT = 8081
TEST_OUTPUT_FILE = "test-output.txt"

SENDFILE_PORT = 8082
BENCH_NUM_ITERATIONS = 10

FILE_SIZE = 1024 * 1024 * 1024


def bench_server(port):
    start = timer()
    for _ in range(BENCH_NUM_ITERATIONS):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((SERVER_IP, port))

        received = 0
        while received < FILE_SIZE:
            chunk = sock.recv(FILE_SIZE - received)
            received += len(chunk)

        sock.close()
    end = timer()

    print(f"Time taken: {end - start} seconds")


def main(argv):
    if len(argv) != 2 or argv[1] not in ["read-send", "sendfile"]:
        print("Usage: python3 test_client.py [read-send|sendfile]")
        exit(1)

    if argv[1] == "read-send":
        bench_server(READ_SEND_PORT)
    else:
        bench_server(SENDFILE_PORT)


if __name__ == "__main__":
    main(sys.argv)
