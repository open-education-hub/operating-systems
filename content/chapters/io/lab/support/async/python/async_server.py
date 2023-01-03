#!/usr/bin/env python3

# SPDX-License-Identifier: BSD-3-Clause

# https://docs.python.org/3/library/asyncio-stream.html

import asyncio
import logging
import sys


def fibonacci(num):
    if num in (0, 1):
        return 1
    return fibonacci(num - 1) + fibonacci(num - 2)


async def handle(reader, writer):
    logging.info("Received connection from %s", writer.get_extra_info("peername"))
    response = ""
    try:
        data = await reader.read(256)
        msg = data.decode("utf-8")
        logging.debug("Message: %s", msg)
        num = int(msg)
        if num < 0 or num > 34:
            response = "out of range"
        response = str(fibonacci(num))
    except ValueError:
        response = "error"

    writer.write(response.encode("utf-8"))
    await writer.drain()

    writer.close()


LISTEN_BACKLOG = 10


async def run_server(port, hostname="0.0.0.0"):
    server = await asyncio.start_server(handle, hostname, port)

    async with server:
        await server.serve_forever()


def main():
    logging.basicConfig(level=logging.DEBUG, format="%(name)s: %(message)s")

    if len(sys.argv) != 2:
        print("Usage: {} port".format(sys.argv[0]), file=sys.stderr)
        sys.exit(1)

    port = int(sys.argv[1])
    logging.info("Starting server on port {:d}".format(port))

    asyncio.run(run_server(port))


if __name__ == "__main__":
    sys.exit(main())
