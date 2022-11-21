FROM ubuntu:22.04

RUN apt-get -y update && DEBIAN_FRONTEND=noninteractive apt-get -y install \
    python3 \
    python3-pip \
    udev \
    iproute2 \
    iptables \
    whois \
    telnet \
    qemu-system \
    parted \
    e2fsprogs \
    cloud-guest-utils \
    openssh-client

RUN pip3 install flask mysql-connector-python humanfriendly pexpect psutil

RUN sed -i 's/nbd\*|//' /lib/udev/rules.d/60-block.rules

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
