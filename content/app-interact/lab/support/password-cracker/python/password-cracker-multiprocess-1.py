# SPDX-License-Identifier: BSD-3-Clause

import hashlib
import itertools
from multiprocessing import Pipe, Process

password_hash = (
    "59a5abc2a99b95be73c31ea272ab0f2f2fe42fec30367155cb73f6f6cef1f4e6"
    "ee37f586cbd02cc738a87a5d6add3ba31dbeaf39ec77cad910837c94c65837fb"
)

password_len = 4

charset = "abcdefghijklmnopqrstuvwxyz"


def worker_proc(pipe):
    first_char = pipe.recv()

    for p in itertools.product(charset, repeat=password_len - 1):
        password = first_char + "".join(p)

        if hashlib.sha512(password.encode()).hexdigest() == password_hash:
            pipe.send(password)
            return

    pipe.send(None)


if __name__ == "__main__":
    pipes = []
    procs = []

    for i in range(len(charset)):
        parent_pipe, child_pipe = Pipe(True)
        pipes.append(parent_pipe)

        p = Process(target=worker_proc, args=(child_pipe,))
        p.start()

        procs.append(p)

    for i in range(len(charset)):
        pipes[i].send(charset[i])

    for i in range(len(charset)):
        result = pipes[i].recv()

        if result:
            print(f"worker {i} found {result}")

    for p in procs:
        p.join()
