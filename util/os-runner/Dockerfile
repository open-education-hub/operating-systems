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

# Ensure correct perf
# If a "perf not found" error happens, then we need to copy the perf installed
# above to the correct directory. This directory changes based on the CPU.
# This trick might not work for major versions (5->6, or 5->4).
RUN  \
    perf_kernel_version=$(perf 2>&1 | grep "WARNING: perf not found for kernel" | awk -F' ' '{printf $7}');  \
    if [ -n "${perf_kernel_version}" ]; then cp -r "/usr/lib/linux-tools/5.15.0-60-generic" "/usr/lib/linux-tools/${perf_kernel_version}-generic"; fi

# Create user student
RUN useradd -ms /bin/bash student && echo "student:student" | chpasswd && usermod -aG sudo student
USER student
WORKDIR /home/student

# Customize .bashrc
COPY config_terminal.sh /init-scripts/config_terminal.sh
RUN cat /init-scripts/config_terminal.sh >> ~/.bashrc

ENTRYPOINT [ "bash" ]
