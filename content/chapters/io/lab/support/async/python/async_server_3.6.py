#!/usr/bin/env python3

# SPDX-License-Identifier: BSD-3-Clause

# https://docs.python.org/3.6/library/asyncio-stream.html#asyncio.start_server

import asyncio
import logging
import sys


def fibonacci(num):
    if num in (0, 1):
        return 1
    return fibonacci(num - 1) + fibonacci(num - 2)


@asyncio.coroutine
def handle(reader, writer):
    logging.info("Received connection from %s", writer.get_extra_info("peername"))
    response = ""
    try:
        data = yield from reader.read(256)
        msg = data.decode("utf-8")
        logging.debug("Message: %s", msg)
        num = int(msg)
        if num < 0 or num > 34:
            response = "out of range"
        response = str(fibonacci(num))
    except ValueError:
        response = "error"

    writer.write(response.encode("utf-8"))
    yield from writer.drain()

    writer.close()


LISTEN_BACKLOG = 10


def run_server(port, hostname="0.0.0.0"):
    loop = asyncio.get_event_loop()
    coro = asyncio.start_server(handle, hostname, port, loop=loop)
    server = loop.run_until_complete(coro)

    try:
        loop.run_forever()
    except KeyboardInterrupt:
        pass

    server.close()
    loop.run_until_complete(server.wait_closed())
    loop.close()


def main():
    logging.basicConfig(level=logging.DEBUG, format="%(name)s: %(message)s")

    if len(sys.argv) != 2:
        print("Usage: {} port".format(sys.argv[0]), file=sys.stderr)
        sys.exit(1)

    port = int(sys.argv[1])
    logging.info("Starting server on port {:d}".format(port))
    run_server(port)


if __name__ == "__main__":
    sys.exit(main())
