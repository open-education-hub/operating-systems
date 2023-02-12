# SPDX-License-Identifier: BSD-3-Clause

import logging
import os
import subprocess

import db
import errors
import utils

logger = logging.getLogger(__name__)


class Disk(object):
    def __init__(self, id: int, size: int, template_name: str):
        self.id = id
        self.size = size
        self.template_name = template_name


def cleanup_disk(dsk: Disk):
    try:
        db.delete_disk(dsk.id)
        os.system(f"rm -rf /vm-disks/{dsk.id}")
    except Exception:
        pass


def create_disk_from_template(template_name: str, size: int):
    try:
        with open(f"/disk-templates/{template_name}/{template_name}.qcow2", "rb"):
            pass
    except Exception:
        raise errors.DiskTemplateNotFound(f"{template_name}")

    disk_id = db.create_disk(size, template_name)

    try:
        res = subprocess.run(
            [
                f"/disk-templates/{template_name}/create_disk_from_template.sh",
                f"/disk-templates/{template_name}/{template_name}.qcow2",
                f"/vm-disks/{disk_id}/disk.qcow2",
                f"{size}",
            ],
            cwd=f"/disk-templates/{template_name}",
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

        if res.returncode != 0:
            raise errors.CreateDiskFromTemplateException(
                f"create_disk_from_template.sh error: {res.stdout}"
            )

        res = subprocess.run(
            [
                f"/disk-templates/{template_name}/setup_root_password.sh",
                f"/vm-disks/{disk_id}/disk.qcow2",
                utils.DISK_TMP_PASSWORD,
            ],
            cwd=f"/disk-templates/{template_name}",
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )

        if res.returncode != 0:
            raise errors.CreateDiskFromTemplateException(
                f"setup_root_password.sh error: {res.stdout}"
            )

        res = subprocess.run(
            [
                f"/disk-templates/{template_name}/copy_files.sh",
                f"/vm-disks/{disk_id}/disk.qcow2",
            ],
            cwd=f"/disk-templates/{template_name}",
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
        )
        if res.returncode != 0:
            raise errors.CreateDiskFromTemplateException(
                f"copy_files.sh error: {res.stdout}"
            )
    except Exception:
        cleanup_disk(disk_id)
        raise

    return Disk(disk_id, size, template_name)
