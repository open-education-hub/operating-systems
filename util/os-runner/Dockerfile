FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# hadolint ignore=DL3008
RUN apt-get update &&   \
    apt-get install -y sudo man vim git tmux wget curl  \
    linux-tools-5.15.0-60-generic   \
    build-essential \
    golang  \
    nasm    \
    strace  \
    ltrace  \
    gawk    \
    gdc \
    busybox-static  \
    valgrind    \
    libjemalloc-dev \
    default-jre \
    lsof    \
    bind9-host  \
    net-tools   \
    netcat  \
    libssl-dev

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

COPY install-dmd.sh /init-scripts/install-dmd.sh
RUN /init-scripts/install-dmd.sh

# Create user student
RUN useradd -ms /bin/bash student && echo "student:student" | chpasswd && usermod -aG sudo student
USER student
WORKDIR /home/student

# Customize .bashrc
COPY config_terminal.sh /init-scripts/config_terminal.sh
RUN cat /init-scripts/config_terminal.sh >> ~/.bashrc

ENTRYPOINT [ "bash" ]
