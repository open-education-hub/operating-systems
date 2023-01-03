# SPDX-License-Identifier: BSD-3-Clause

import subprocess
from sys import exit

NUM_SLEEPS = 10


def main():
    # TODO 1: Create 10 `sleep 1000` processes using `subprocess.Popen`
    # Use the documentation: https://docs.python.org/3/library/subprocess.html#subprocess.Popen
    procs = []
    for _ in range(NUM_SLEEPS):
        # Create new process and add it to the list of processes.
        p = subprocess.Popen(["sleep", "1000"])
        procs.append(p)

    # TODO 2: Make the current process wait for its child processes.
    for p in procs:
        p.wait()


if __name__ == "__main__":
    exit(main())
