# OS-runner

This is an isolated environment to run the examples and tasks from laboratories and lectures.

## Windows Prerequisites

1. [WSL2](https://learn.microsoft.com/en-us/windows/wsl/about)

    ```shell
    # Enable the Windows Subsystem for Linux
    dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart

    # Enable Virtual Machine feature
    dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart

    # Install wsl
    wsl --install -d Ubuntu

    # Ensure you are using wsl 2
    wsl --set-default-version 2
    ```

1. [Install Docker Desktop](https://www.docker.com/products/docker-desktop/)

## Setup

1. Open WSL and clone the repository inside it

    ```shell
    # Clone to homepath
    student@wsl: cd && git clone https://github.com/open-education-hub/operating-systems.git
    ```

1. Install docker

    ```shell
    student@wsl: curl -fsSL https://get.docker.com -o get-docker.sh && bash get-docker.sh
    ```

1. Build docker image

    ```shell
    student@wsl: cd operating-systems/util/os-runner/ && make docker-image
    ```

## Usage

- `make start` - Start `OS-runner` container

- `make attach` - Attach a new session to `OS-runner` container, this is useful for tasks requiring multiple terminals

- `make clean` - Stop `OS-runner` container and delete it

- `make help` - Print usable Makefile commands
