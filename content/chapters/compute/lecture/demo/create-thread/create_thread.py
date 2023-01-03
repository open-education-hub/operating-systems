#!/usr/bin/env python

# SPDX-License-Identifier: BSD-3-Clause

from os import getpid, getppid
from threading import Thread
from time import sleep


def thread(msg):
    print(f"[thread] PID = {getpid()}; PPID = {getppid()}")
    print(f"[thread] Message from main thread: {msg}")

    sleep(5)


def main():
    print(f"[main] PID = {getpid()}; PPID = {getppid()}")

    # Create a Thread object.
    t = Thread(target=thread, args=("OS Rullz!",))
    # Start the thread.
    t.start()

    # Wait until thread finishes.
    # We can't kill a thread. Why?
    t.join()


if __name__ == "__main__":
    main()
