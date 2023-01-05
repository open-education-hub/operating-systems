FROM ubuntu:22.04

# hadolint ignore=DL3008
RUN apt-get -y update && DEBIAN_FRONTEND=noninteractive apt-get -y install --no-install-recommends \
    python3 \
    python3-pip \
    udev \
    iproute2 \
    iptables \
    whois \
    telnet \
    qemu-system \
    qemu-utils \
    parted \
    e2fsprogs \
    cloud-guest-utils \
    openssh-client && rm -rf /var/lib/apt/lists/*

# hadolint ignore=DL3013
RUN pip3 install --no-cache-dir flask mysql-connector-python humanfriendly pexpect psutil

WORKDIR /app
RUN mkdir /app/scripts

COPY app.py /app
COPY vm.py /app
COPY db.py /app
COPY network.py /app
COPY disk.py /app
COPY utils.py /app
COPY errors.py /app

COPY scripts/create_bridge.sh /app/scripts
COPY scripts/create_tap_interface.sh /app/scripts

CMD ["python3", "-u", "app.py"]
