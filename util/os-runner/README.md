# OS-runner

This is an isolated environment to run the examples and tasks from laboratories and lectures.

## Prerequisites

- [Install docker](https://get.docker.com/)
- Change the `OS_HOME` variable from `Makefile` to the directory where you cloned the repository

## Usage

- `make start` - Start `OS-runner` container

- `make run`   - Attache a new session to `OS-runner` container, this is usefull for tasks requiring multiple terminals

- `make clean` - Stop `OS-runner` container and delete it
