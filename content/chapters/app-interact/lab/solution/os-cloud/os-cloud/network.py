# SPDX-License-Identifier: BSD-3-Clause

import ipaddress
import logging
import socket
import subprocess

import db
import errors

logger = logging.getLogger(__name__)


class Net(object):
    def __init__(self, id: int, name: str, bridge_iface_idx: int, ip: int, mask: int):
        self.name = name
        self.id = id
        self.bridge_iface_idx = bridge_iface_idx
        self.ip = ip
        self.ip_str = socket.inet_ntoa(self.ip.to_bytes(4, "big"))
        self.mask = mask
        self.mask_str = socket.inet_ntoa(self.mask.to_bytes(4, "big"))
        self.ip_with_prefixlen = ipaddress.ip_interface(
            f"{self.ip_str}/{self.mask_str}"
        ).with_prefixlen


def create_one_network(net: Net):
    bridge_ip = net.ip + 1
    bridge_ip_str = socket.inet_ntoa(bridge_ip.to_bytes(4, "big"))

    bridge_netmask_str = net.mask_str

    try:
        res = subprocess.run(
            [
                "/app/scripts/create_bridge.sh",
                f"br{net.bridge_iface_idx}",
                bridge_ip_str,
                bridge_netmask_str,
            ],
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        if res.returncode != 0:
            raise errors.NetworkCreateException(res.stdout)

        res = subprocess.run(
            [
                "iptables",
                "-t",
                "nat",
                "-A",
                "POSTROUTING",
                "-s",
                f"{net.ip_with_prefixlen}",
                "-j",
                "MASQUERADE",
            ],
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

        if res.returncode != 0:
            raise errors.NetworkCreateException(res.stdout)
    except Exception:
        raise


def create_networks():
    all_networks_info = db.get_all_networks()

    networks = []

    for id, name, bridge_iface_idx, ip, mask in all_networks_info:
        networks.append(Net(name, id, bridge_iface_idx, ip, mask))

    for net in networks:
        create_one_network(net)


def create_interface_in_network(ip: int, iface_idx: int, net: Net):
    ip_str = str(ipaddress.ip_address(ip))

    netmask_str = str(ipaddress.ip_address(net.mask))

    bridge_iface_name = f"br{net.bridge_iface_idx}"
    tap_iface_name = f"tap{iface_idx}"

    try:
        res = subprocess.run(
            [
                "/app/scripts/create_tap_interface.sh",
                tap_iface_name,
                ip_str,
                netmask_str,
                bridge_iface_name,
            ],
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        if res.returncode != 0:
            raise errors.InterfaceCreateException(res.stdout)
    except Exception:
        raise


def get_network_info(name: str) -> Net:
    info = db.get_network_info(name)

    return Net(info[0], name, info[1], info[2], info[3])


def find_unused_ip(net: Net) -> int:
    first_ip = net.ip + 2
    last_ip = (net.ip | ~net.mask) & 0xFFFFFFFF

    all_ips = db.get_used_ips()

    for ip in range(first_ip, last_ip):
        if ip not in all_ips:
            return ip

    raise errors.NetworkFullException(f"{net.name}")


def find_unused_tap_interface() -> int:
    all_tap_interfaces = db.get_used_tap_interfaces()

    idx = 0
    while True:
        if idx not in all_tap_interfaces:
            return idx
        idx += 1


def find_unused_qemu_monitor_port() -> int:
    all_qemu_monitor_ports = db.get_used_qemu_monitor_ports()

    port = 10001
    while True:
        if port not in all_qemu_monitor_ports:
            return port
        port += 2


def find_unused_qemu_serial_port() -> int:
    all_qemu_serial_ports = db.get_used_qemu_serial_ports()

    port = 10002
    while True:
        if port not in all_qemu_serial_ports:
            return port
        port += 2
