# SPDX-License-Identifier: BSD-3-Clause

from random import randint
from threading import Lock, Semaphore, Thread
from time import sleep
from typing import List

NUM_WORKERS = 3
messages: List[str] = []
msg_mutex = Lock()


def worker(sem, id):
    msg = ""

    while True:
        sem.acquire()

        print(f"Worker {id} started handling message...")
        sleep(randint(1, 5))

        with msg_mutex:
            msg = messages[0]
            messages.pop(0)

        print(f"Worker {id} handling message: {msg}")
        sleep(randint(1, 5))

        print(f"Worker {id} done!")

        # Notice we don't call `sem.release()`. The main thread does that.


def main():
    sem = Semaphore(0)

    # Create and start the worker threads.
    thread_pool = [Thread(target=worker, args=(sem, i)) for i in range(NUM_WORKERS)]
    for t in thread_pool:
        t.daemon = True
        t.start()

    print(
        "Type a message and press Enter to simulate one connection. "
        + "Type 'exit' and then wait a bit to quit."
    )

    while True:
        msg = input("> ")
        if msg == "exit":
            break

        # Equivalent to:
        #   msg_mutex.acquire()
        #   messages.append(msg)
        #   msg_mutex.release()
        with msg_mutex:
            messages.append(msg)

        sem.release()


if __name__ == "__main__":
    exit(main())
