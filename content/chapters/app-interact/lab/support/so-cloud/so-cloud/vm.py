import ipaddress
import logging
import os
import socket
import subprocess
import time
from typing import Optional

import db
import disk
import errors
import network
import pexpect
import utils

logger = logging.getLogger(__name__)

VM_STATE_RUNNING = 0
VM_STATE_STOPPED = 1
VM_STATE_PAUSED = 2


def state_to_str(state: int) -> str:
    if state == VM_STATE_RUNNING:
        return "RUNNING"
    elif state == VM_STATE_STOPPED:
        return "STOPPED"
    elif state == VM_STATE_PAUSED:
        return "PAUSED"
    else:
        return "UNKNOWN"


class VM(object):
    def __init__(
        self,
        name: str,
        mem_size: int,
        ip: int,
        net: network.Net,
        tap_iface_idx: int,
        vm_disk: disk.Disk,
        qemu_monitor_port: int,
        qemu_serial_port: int,
        qemu_pid: int,
        state: int,
    ):
        self.id = -1
        self.name = name
        self.mem_size = mem_size
        self.mem_size_mb = mem_size // (1024 * 1024)
        self.ip = ip
        self.net = net
        self.ip_str = str(ipaddress.ip_address(self.ip))
        self.netmask_str = str(ipaddress.ip_address(self.net.mask))
        self.tap_iface_idx = tap_iface_idx
        self.macaddr = f"52:54:00:12:34:{tap_iface_idx:02x}"
        self.vm_disk = vm_disk
        self.qemu_monitor_port = qemu_monitor_port
        self.qemu_serial_port = qemu_serial_port
        self.qemu_pid = qemu_pid
        self.state = state


def start_qemu_for_vm(vm: VM):
    mem_size_mb = vm.mem_size // (1024 * 1024)

    has_kvm = os.path.exists("/dev/kvm")

    qemu_cmd = [
        "qemu-system-x86_64",
        "-m",
        f"{mem_size_mb}",
        "-hda",
        f"/vm-disks/{vm.vm_disk.id}/disk.qcow2",
        "-net",
        f"nic,macaddr={vm.macaddr}",
        "-net",
        f"tap,ifname=tap{vm.tap_iface_idx},script=no",
        "-monitor",
        f"telnet::{vm.qemu_monitor_port},server,nowait",
        "-serial",
        f"telnet::{vm.qemu_serial_port},server,nowait",
        "-nographic",
    ]

    if has_kvm:
        qemu_cmd.append("-enable-kvm")

    logger.info(f"qemu_cmd is {qemu_cmd}")

    vm.qemu_pid = subprocess.Popen(qemu_cmd).pid

    # Wait for qemu to open the serial port.
    while True:
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.connect(("127.0.0.1", vm.qemu_serial_port))
            s.close()
        except ConnectionRefusedError:
            time.sleep(0.5)

        break


def stop_qemu_for_vm(vm: VM):
    e = pexpect.spawn(f"telnet localhost {vm.qemu_monitor_port}")
    e.expect_exact("(qemu) ")
    e.sendline("quit")
    e.expect_exact("Connection closed by foreign host.")
    e.close()

    os.waitpid(vm.qemu_pid, 0)


def ubuntu_22_04_vm_prepare(vm: VM, ssh_pub_key: Optional[str] = None):
    logger.info(f"Preparing ubuntu 22.04 for vm {vm.name}")

    logger.info("Starting vm")
    start_qemu_for_vm(vm)

    e = pexpect.spawn(f"telnet localhost {vm.qemu_serial_port}", timeout=None)

    e.expect_exact("login: ")
    e.sendline("root")
    e.expect_exact("Password: ")
    e.sendline(utils.DISK_TMP_PASSWORD)

    # The disk was resized by qemu-img in the create_disk_from_template.sh script,
    # but the existing partition and filesystem still have the original size from the template.
    # Here we extend them to occupy the entire disk.
    logger.info("Resizing root partition and filesystem")
    e.expect_exact("root@ubuntu:~# ")
    e.sendline(
        'echo ", +" | sfdisk --force -N 1 /dev/sda && partprobe && resize2fs -f /dev/sda1'
    )

    # The ubuntu 22.04 template does not have server keys for the ssh server
    # and because of that the ssh server is not able to start:
    #
    # [FAILED] Failed to start OpenBSD Secure Shell server.
    #
    # Here we generate them by running ssh-keygen -A.
    logger.info("Setting up ssh server keys")
    e.expect_exact("root@ubuntu:~# ")
    e.sendline("ssh-keygen -A")

    # Setup ssh config: allow root login with password.
    e.expect_exact("root@ubuntu:~# ")
    e.sendline(
        "sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config"
    )

    e.expect_exact("root@ubuntu:~# ")
    e.sendline(
        "sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config"
    )

    # Setup the ssh key, if present.
    if ssh_pub_key:
        # TODO: create the /root/.ssh directory
        # TODO: write ssh_pub_key to /root/.ssh/authorized_keys
        pass

    # Setup network config.
    logger.info("Setting up network config")
    iface_ip = ipaddress.ip_interface(f"{vm.ip_str}/{vm.netmask_str}").with_prefixlen
    gateway_ip = ipaddress.ip_address(vm.net.ip + 1)

    e.expect_exact("root@ubuntu:~# ")
    e.sendline(
        (
            "cat > /etc/systemd/network/config.network <<EOF\n"
            "[Match]\n"
            "Name=ens3\n"
            "\n"
            "[Network]\n"
            f"Address={iface_ip}\n"
            f"Gateway={gateway_ip}\n"
            "DNS=8.8.8.8\n"
            "EOF\n"
        )
    )

    # Stop snapd.
    logger.info("Stopping snapd")
    e.expect_exact("root@ubuntu:~# ")
    e.sendline("systemctl stop snapd")

    # Stop vm.
    logger.info("Stopping vm")
    e.expect_exact("root@ubuntu:~# ")
    e.sendline("halt")

    e.expect_exact("reboot: System halted", timeout=None)

    e.close()

    # Stop qemu.
    logger.info("Stopping qemu")
    stop_qemu_for_vm(vm)


def vm_create(
    name: str,
    image: str,
    network_name: str,
    mem_size: int,
    disk_size: int,
    ssh_pub_key: str,
):

    if len(db.get_vm_by_name(name)) > 0:
        raise errors.VMAlreadyExistsException(name)

    net = network.get_network_info(network_name)

    vm_ip = network.find_unused_ip(net)
    vm_ip_str = str(ipaddress.ip_address(vm_ip))

    tap_iface_idx = network.find_unused_tap_interface()
    network.create_interface_in_network(vm_ip, tap_iface_idx, net)

    qemu_monitor_port = network.find_unused_qemu_monitor_port()
    qemu_serial_port = network.find_unused_qemu_serial_port()

    logger.info(f"vm {name} ip is {vm_ip_str}")
    logger.info(f"vm {name} interface is tap{tap_iface_idx}")
    logger.info(f"vm {name} qemu monitor port is {qemu_monitor_port}")
    logger.info(f"vm {name} qemu serial port is {qemu_serial_port}")

    vm_disk = disk.create_disk_from_template(image, disk_size)

    logger.info(f"created disk with id {vm_disk.id}, template {vm_disk.template_name}")

    vm = VM(
        name,
        mem_size,
        vm_ip,
        net,
        tap_iface_idx,
        vm_disk,
        qemu_monitor_port,
        qemu_serial_port,
        -1,
        -1,
    )

    vm.id = db.create_vm(
        name,
        vm_disk.id,
        vm.mem_size,
        vm.net.id,
        vm.tap_iface_idx,
        vm.ip,
        vm.qemu_pid,
        vm.qemu_monitor_port,
        vm.qemu_serial_port,
        VM_STATE_RUNNING,
    )

    try:
        if image == "ubuntu_22.04":
            ubuntu_22_04_vm_prepare(vm, ssh_pub_key)

        logger.info(f"Starting vm {vm.name} with id {vm.id}")
        start_qemu_for_vm(vm)
        db.update_vm_qemu_pid(vm.id, vm.qemu_pid)
    except Exception:
        disk.cleanup_disk(vm_disk)
        db.delete_vm(vm.id)

        raise

    return vm.id


def vm_stop(vm: VM):
    # TODO: Call stop_qemu_for_vm

    # TODO: Change the vm pid in the database to -1

    # TODO: Change the vm state in the database to VM_STATE_STOPPED
    pass


def vm_start(vm: VM):
    start_qemu_for_vm(vm)
    db.update_vm_qemu_pid(vm.id, vm.qemu_pid)
    db.update_vm_state(vm.id, VM_STATE_RUNNING)


def vm_get(id_: str):
    info = db.get_vm_info(id_)

    if len(info) == 0:
        raise errors.VMNotFoundException(id_)

    info = info[0]

    vm_id = info[0]
    vm_name = info[1]
    vm_diskid = info[2]
    vm_mem_size = info[3]
    vm_networkid = info[4]
    vm_tap_interface_idx = info[5]
    vm_ip = info[6]
    vm_qemu_pid = info[7]
    vm_qemu_monitor_port = info[8]
    vm_qemu_serial_port = info[9]
    vm_state = info[10]
    disk_template_name = info[11]
    disk_size = info[12]
    network_name = info[13]
    network_bridge_interface_idx = info[14]
    network_ip = info[15]
    network_mask = info[16]

    vm_disk = disk.Disk(vm_diskid, disk_size, disk_template_name)
    vm_net = network.Net(
        vm_networkid,
        network_name,
        network_bridge_interface_idx,
        network_ip,
        network_mask,
    )

    vm = VM(
        vm_name,
        vm_mem_size,
        vm_ip,
        vm_net,
        vm_tap_interface_idx,
        vm_disk,
        vm_qemu_monitor_port,
        vm_qemu_serial_port,
        vm_qemu_pid,
        vm_state,
    )
    vm.id = vm_id

    return vm


def start_all_vms():
    all_vms = db.get_all_vms()

    for id_, _ in all_vms:
        vm = vm_get(id_)

        if vm.state == VM_STATE_RUNNING:
            logger.info(f"Creating tap interface for vm {vm.name}")
            network.create_interface_in_network(vm.ip, vm.tap_iface_idx, vm.net)

            logger.info(f"Starting vm {vm.name} with id {vm.id}")
            vm_start(vm)
