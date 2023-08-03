# VM Creation

## Question Text

How do you create a new virtual machine with a memory of 3GB and disk size of 100 GB?

## Question Answers

+ By running `curl -H "Content-Type: application/json" -d '{ "name": "my_vm", "image": "ubuntu_22.04", "network": "default", "mem_size": "3G", "disk_size": "100G"}' localhost:5000/vm_create`

- By running `curl -H "Content-Type: application/json" -d '{ "name": "my_vm", "image": "ubuntu_22.04", "network": "default", "mem_size": "3G", "disk_size": "100G"}' localhost:5000/vm_delete`

- By running `curl -H "Content-Type: application/json" -d '{ "name": "my_vm", "image": "ubuntu_22.04", "network": "default", "mem_size": "3G", "disk_size": "101G"}' localhost:5000/vm_create`

- By running `curl -H "Content-Type: application/json" -d '{ "name": "my_vm", "image": "ubuntu_22.04", "network": "default", "mem_size": "6G", "disk_size": "1000G"}' localhost:5000/vm_delete`

## Feedback

We need to uso `curl` with the right path `localhost:5000/vm_create`, specifying the right data `{ "name": "my_vm", "image": "ubuntu_22.04", "network": "default", "mem_size": "3G", "disk_size": "100G"}`.
