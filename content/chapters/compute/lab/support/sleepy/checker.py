# SPDX-License-Identifier: BSD-3-Clause

from os import system
from subprocess import PIPE, Popen
from sys import exit

NUM_SLEEPS = 10


def cleanup():
    system("killall python3")
    system("killall sleep")


def main():
    cleanup()
    system("python3 sleepy_creator.py &")

    p = Popen(["ps", "-e", "-H", "-o", "pid,ppid,cmd"], stdout=PIPE)
    output, _ = p.communicate()
    output = output.decode("utf-8")

    # print(output)
    output_lines = output.split("\n")
    output_lines = [line for line in output_lines if "sleepy" in line]
    print(output_lines)

if __name__ == "__main__":
    exit(main())
