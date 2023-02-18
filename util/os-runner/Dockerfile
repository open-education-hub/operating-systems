FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

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

# Configure bash
RUN echo "PS1='🐳 ${debian_chroot:+($debian_chroot)}\[\033[01;36m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '" >> ~/.bashrc
RUN echo "PROMPT_DIRTRIM=3" >> ~/.bashrc
RUN echo "alias python=python3" >> ~/.bashrc

# Add aliases for labs
RUN echo 'alias go_ss="cd ~/operating-systems/content/chapters/software-stack/lab/"' >> ~/.bashrc
RUN echo 'alias go_data="cd ~/operating-systems/content/chapters/data/lab/"' >> ~/.bashrc
RUN echo 'alias go_compute="cd ~/operating-systems/content/chapters/compute/lab/"' >> ~/.bashrc
RUN echo 'alias go_io="cd ~/operating-systems/content/chapters/io/lab/"' >> ~/.bashrc
RUN echo 'alias go_appInt="cd ~/operating-systems/content/chapters/app-interact/lab/"' >> ~/.bashrc

ENTRYPOINT [ "bash" ]
