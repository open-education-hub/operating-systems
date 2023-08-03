# SPDX-License-Identifier: BSD-3-Clause

from random import randint
from threading import Condition, Thread
from time import sleep
from typing import List

NUM_WORKERS = 3
messages: List[str] = []


def worker(event, id):
    msg = ""

    while True:
        event.acquire()
        while len(messages) == 0:
            event.wait()

        print(f"Worker {id} started handling message...")
        sleep(randint(1, 5))

        msg = messages[0]
        messages.pop(0)
        event.release()

        print(f"Worker {id} handling message: {msg}")
        sleep(randint(1, 5))

        print(f"Worker {id} done!")


def main():
    event = Condition()

    # Create and start the worker threads.
    thread_pool = [Thread(target=worker, args=(event, i)) for i in range(NUM_WORKERS)]
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

        event.acquire()
        messages.append(msg)
        event.notify()
        event.release()


if __name__ == "__main__":
    exit(main())
