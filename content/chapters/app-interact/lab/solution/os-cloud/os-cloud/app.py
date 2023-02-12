# SPDX-License-Identifier: BSD-3-Clause

import logging
import os

import db
import errors
import humanfriendly
import network
import vm
from flask import Flask, jsonify, request

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("os-cloud")

app = Flask(__name__)


@app.route("/vm_create", methods=["POST"])
def api_vm_create():
    vm_create_args = request.json

    name = vm_create_args.get("name", None)
    image = vm_create_args.get("image", None)
    network_name = vm_create_args.get("network", None)
    mem_size = vm_create_args.get("mem_size", None)
    disk_size = vm_create_args.get("disk_size", None)
    ssh_pub_key = vm_create_args.get("ssh_key", None)

    if not name:
        return jsonify({"status": "error", "error_msg": "VM name not provided"})
    elif not image:
        return jsonify({"status": "error", "error_msg": "VM image not provided"})
    elif not network_name:
        return jsonify({"status": "error", "error_msg": "VM network not provided"})
    elif not mem_size:
        return jsonify({"status": "error", "error_msg": "VM mem_size not provided"})
    elif not disk_size:
        return jsonify({"status": "error", "error_msg": "VM disk_size not provided"})

    try:
        mem_size = humanfriendly.parse_size(mem_size, binary=True)
    except Exception:
        return f"Invalid mem_size: {mem_size}"

    try:
        disk_size = humanfriendly.parse_size(disk_size, binary=True)
    except Exception:
        return f"Invalid disk_size: {disk_size}"

    try:
        error_str = ""
        vm_id = vm.vm_create(
            name, image, network_name, mem_size, disk_size, ssh_pub_key
        )
        return jsonify({"status": "ok", "id": vm_id})
    except errors.VMAlreadyExistsException:
        error_str = f'vm "{name}" already exists'
    except errors.NetworkNotFoundException as ex:
        error_str = f'network "{ex}" not found'
    except errors.DiskTemplateNotFound as ex:
        error_str = f'disk template "{ex}" not found'
    except errors.CreateDiskFromTemplateException as ex:
        error_str = f"create disk failed: {ex}"
    except Exception as ex:
        app.logger.error(f"vm_create error: {ex}")

    app.logger.error(f"vm_create error: {error_str}")

    return jsonify({"status": "error", "error_msg": error_str})


@app.route("/vm_stop", methods=["POST"])
def api_vm_stop():
    vm_info_args = request.json

    id_ = vm_info_args.get("id", None)
    if not id_:
        return jsonify({"status": "error", "error_msg": "VM id not provided"})

    try:
        error_str = ""
        v = vm.vm_get(id_)
        vm.vm_stop(v)

        return jsonify({"status": "ok"})
    except errors.VMNotFoundException as ex:
        error_str = f"vm '{ex}' not found"
    except Exception as ex:
        app.logger.error(f"vm_stop error: {ex}")

    return jsonify({"status": "error", "error_msg": error_str})


@app.route("/vm_start", methods=["POST"])
def api_vm_start():
    vm_info_args = request.json

    id_ = vm_info_args.get("id", None)
    if not id_:
        return jsonify({"status": "error", "error_msg": "VM id not provided"})

    try:
        error_str = ""
        v = vm.vm_get(id_)
        vm.vm_start(v)

        return jsonify({"status": "ok"})
    except errors.VMNotFoundException as ex:
        error_str = f"vm '{ex}' not found"
    except Exception as ex:
        app.logger.error(f"vm_start error: {ex}")

    return jsonify({"status": "error", "error_msg": error_str})


@app.route("/vm_list", methods=["GET"])
def api_vm_list():
    vms = db.get_all_vms()
    return jsonify([{"id": v[0], "name": v[1]} for v in vms])


@app.route("/vm_info", methods=["POST"])
def api_vm_info():
    vm_info_args = request.json

    id_ = vm_info_args.get("id", None)
    if not id_:
        return jsonify({"status": "error", "error_msg": "VM id not provided"})

    try:
        error_str = ""
        v = vm.vm_get(id_)
        return jsonify(
            {
                "id": v.id,
                "name": v.name,
                "mem_size": v.mem_size,
                "disk_size": v.vm_disk.size,
                "os": v.vm_disk.template_name,
                "network": v.net.name,
                "state": vm.state_to_str(v.state),
                "ip": v.ip_str,
            }
        )
    except errors.VMNotFoundException as ex:
        error_str = f'vm "{ex}" not found'
    except Exception as ex:
        app.logger.error(f"vm_info error: {ex}")

    return jsonify({"status": "error", "error_msg": error_str})


@app.route("/")
def hello():
    return "Welcome to OS Cloud!\n"


def prereq_checks():
    if not os.path.exists("/dev/nbd0"):
        logger.error("Make sure the nbd kernel module is loaded")
        exit(1)

    if not os.path.exists("/dev/kvm"):
        logger.error("No KVM support found. VM running will be SLOW")


if __name__ == "__main__":
    prereq_checks()

    try:
        db.wait_db_ready()
        network.create_networks()
        vm.start_all_vms()
    except errors.NetworkCreateException as ex:
        logger.error(f"Couldn't create network: {ex}")
        exit(1)

    app.run(host="0.0.0.0")
