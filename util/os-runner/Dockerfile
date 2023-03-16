FROM ubuntu:20.04 AS ltrace-builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get -y update && apt-get install -y build-essential git automake autoconf libtool libelf-dev

RUN mkdir /build
RUN git clone https://gitlab.com/cespedes/ltrace.git /build/ltrace

WORKDIR /build/ltrace

RUN git checkout 5cffc0d2134f697fbac8627ec5b5f0085cd47c8a

RUN ./autogen.sh && ./configure --prefix=/usr --sysconfdir=/etc && make && make install


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

# Use python3
RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 10

# Create user student
RUN useradd -ms /bin/bash student && echo "student:student" | chpasswd && usermod -aG sudo student
USER student
WORKDIR /home/student

# Customize .bashrc
COPY config_terminal.sh /init-scripts/config_terminal.sh
RUN cat /init-scripts/config_terminal.sh >> ~/.bashrc

# Install our own compiled version of ltrace
COPY --from=ltrace-builder /usr/bin/ltrace /usr/bin/ltrace

ENTRYPOINT [ "bash" ]
