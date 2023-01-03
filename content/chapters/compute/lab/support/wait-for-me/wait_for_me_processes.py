# SPDX-License-Identifier: BSD-3-Clause

from multiprocessing import Process
from sys import argv
from time import sleep


def write_message_to_file(filename):
    sleep(1)
    open(filename, "w").write("Now you see me, now you don't")


def main():
    if len(argv) < 2:
        print(f"Usage: {argv[0]} <file_name>")
        return 1

    file_name = argv[1]
    child = Process(target=write_message_to_file, args=(file_name,))
    child.start()

    # TODO: Fix the `FileNotFoundError` raised below.

    file_content = open(file_name).readline()
    print(f"File content is: '{file_content}'")


if __name__ == "__main__":
    exit(main())
