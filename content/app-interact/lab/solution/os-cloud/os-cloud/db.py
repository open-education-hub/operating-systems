# SPDX-License-Identifier: BSD-3-Clause
import logging
import os
import time
from typing import List, Optional, Tuple

import errors
import mysql.connector

logger = logging.getLogger(__name__)

host = os.environ.get("MYSQL_HOST", None)
if not host:
    raise Exception("MYSQL_HOST environment variable not set")

user = os.environ.get("MYSQL_USER", None)
if not user:
    raise Exception("MYSQL_USER environment variable not set")

password = os.environ.get("MYSQL_PASSWORD", None)
if not password:
    raise Exception("MYSQL_PASSWORD environment variable not set")

db = os.environ.get("MYSQL_DATABASE", None)
if not db:
    raise Exception("MYSQL_DATABASE environment variable not set")


# Executes query with arguments, returns all values.
def simple_query(query: str, args: Optional[Tuple] = None) -> List:
    conn = mysql.connector.connect(host=host, user=user, password=password, database=db)

    cursor = conn.cursor(prepared=True)

    cursor.execute(query, args)

    res = list(cursor.fetchall())

    conn.commit()

    cursor.close()
    conn.close()

    return res


# Executes an insert of only one row, returns the id.
def simple_insert_query(query: str, args: Optional[Tuple] = None) -> int:
    conn = mysql.connector.connect(host=host, user=user, password=password, database=db)

    cursor = conn.cursor(prepared=True)

    cursor.execute(query, args)

    new_id = cursor.lastrowid

    conn.commit()

    cursor.close()
    conn.close()

    return new_id


def get_all_field_values(field: str, table: str):
    conn = mysql.connector.connect(host=host, user=user, password=password, database=db)

    cursor = conn.cursor()

    cursor.execute(f"SELECT {field} FROM {table}")

    res = set([x[0] for x in cursor.fetchall()])

    cursor.close()
    conn.close()

    return res


def get_used_ips():
    return get_all_field_values("ip", "vm")


def get_used_tap_interfaces():
    return get_all_field_values("tap_interface_idx", "vm")


def get_used_qemu_monitor_ports():
    return get_all_field_values("qemu_monitor_port", "vm")


def get_used_qemu_serial_ports():
    return get_all_field_values("qemu_serial_port", "vm")


# ------------------- Disk ------------------------
def create_disk(size: int, template_name: str):
    return simple_insert_query(
        ("INSERT INTO disk (size, template_name) " "VALUES (%s, %s)"),
        (size, template_name),
    )


def delete_disk(disk_id: int):
    return simple_query("DELETE FROM disk WHERE id = %s", (disk_id,))


# ----------------- VM -------------------
def create_vm(
    name: str,
    disk_id: str,
    mem_size: int,
    network_id: int,
    tap_interface_idx: int,
    ip: int,
    qemu_pid: int,
    qemu_monitor_port: int,
    qemu_serial_port: int,
    state: int,
) -> int:
    return simple_insert_query(
        (
            "INSERT INTO vm ("
            "name, "
            "disk_id, "
            "mem_size, "
            "network_id, "
            "tap_interface_idx, "
            "ip, "
            "qemu_pid, "
            "qemu_monitor_port, "
            "qemu_serial_port, "
            "state) "
            "VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"
        ),
        (
            name,
            disk_id,
            mem_size,
            network_id,
            tap_interface_idx,
            ip,
            qemu_pid,
            qemu_monitor_port,
            qemu_serial_port,
            state,
        ),
    )


def delete_vm(id_: int):
    simple_query("DELETE FROM vm WHERE id = %s", (id_,))


def get_vm_by_name(name: str):
    return simple_query("SELECT id FROM vm WHERE name = %s", (name,))


def get_vm_info(id_: str):
    return simple_query(
        (
            "SELECT v.id, v.name, v.disk_id, v.mem_size, v.network_id, v.tap_interface_idx, "
            "v.ip, v.qemu_pid, v.qemu_monitor_port, v.qemu_serial_port, v.state, "
            "d.template_name, d.size, n.name, n.bridge_interface_idx, n.ip, n.mask "
            "FROM vm v "
            "INNER JOIN disk d ON v.disk_id = d.id "
            "INNER JOIN network n ON v.network_id = n.id "
            "WHERE v.id = %s"
        ),
        (id_,),
    )


def get_all_vms():
    return simple_query("SELECT id, name FROM vm")


def update_vm_qemu_pid(id_: int, pid: int):
    simple_query("UPDATE vm SET qemu_pid = %s WHERE id = %s", (pid, id_))


def update_vm_state(id_: int, state: int):
    simple_query("UPDATE vm SET state = %s WHERE id = %s", (state, id_))


# -------------- Network -------------------
def get_all_networks() -> List[Tuple[str, str, str, str, str]]:
    return simple_query("SELECT id, name, bridge_interface_idx, ip, mask FROM network")


def get_network_info(network_name: str) -> Tuple[int, int, int, int]:
    conn = mysql.connector.connect(host=host, user=user, password=password, database=db)

    cursor = conn.cursor()

    cursor.execute(
        "SELECT id, bridge_interface_idx, ip, mask FROM network WHERE name = %s",
        (network_name,),
    )

    info = list(cursor.fetchall())

    if len(info) == 0:
        raise errors.NetworkNotFoundException(f"{network_name}")

    if len(info) > 1:
        raise errors.DatabaseError(f"Too many entries for network {network_name}")

    cursor.close()
    conn.close()

    return info[0]


def wait_db_ready():
    logger.info("Waiting for db to start")

    while True:
        try:
            conn = mysql.connector.connect(
                host=host, user=user, password=password, database=db
            )
            conn.close()
            break
        except mysql.connector.errors.DatabaseError:
            time.sleep(1)
