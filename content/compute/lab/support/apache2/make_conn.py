# SPDX-License-Identifier: BSD-3-Clause

import socket
import sys

NUM_CONNS = 100

if len(sys.argv) != 3:
    print("Usage: make_conn.py host port")
    exit()

host = sys.argv[1]
port = int(sys.argv[2])

conns = []

for i in range(NUM_CONNS):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    s.connect((host, port))

    s.send(b"A")

    conns.append(s)

input("Press ENTER to exit")
