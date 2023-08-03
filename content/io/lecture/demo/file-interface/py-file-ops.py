#!/usr/bin/env python

# SPDX-License-Identifier: BSD-3-Clause

import sys


def wait_for_input(msg):
    print(f" * {msg}")
    print(" -- Press ENTER to continue ...")
    sys.stdout.flush()
    sys.stdin.readline()


def main():
    wait_for_input("Open file f.txt")
    f = open("f.txt", "w+b")

    wait_for_input("Write 1024 bytes")
    for _ in range(64):
        f.write(bytes("0123456789012345", "ascii"))
    f.flush()

    wait_for_input("Go backwards 512 bytes")
    f.seek(-512, 2)

    wait_for_input("Read 256 bytes")
    _ = f.read(256)

    wait_for_input("Truncate file to 256 bytes")
    f.truncate(256)

    wait_for_input("Close file")
    f.close()


if __name__ == "__main__":
    sys.exit(main())
