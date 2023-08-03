# Arena

## Oneko

An alternative to `xeyes` which allows us to observe Unix sockets is `oneko`.
Going through the same steps, we see that the application also create a Unix socket, then connects to the path `@"/tmp/.X11-unix/X0"`.

```console
student@os:~$ strace -e trace=socket,connect oneko
socket(AF_UNIX, SOCK_STREAM|SOCK_CLOEXEC, 0) = 3
connect(3, {sa_family=AF_UNIX, sun_path=@"/tmp/.X11-unix/X1"}, 20) = 0
--- SIGALRM {si_signo=SIGALRM, si_code=SI_KERNEL} ---
```

When running `oneko`, what differs from `xeyes` is the `SIGALRM` signal.
This means that `oneko` uses a timer, which is periodically set, and then it expires only to be reset again.
The purpose of this timer is to slow down the cat.

Verifying the communication between the X server and `oneko` is easy.
We see that the cat follows our mouse cursor, behaving similarly to `xeyes`.
After running `oneko` under `strace`, we see the communication uses the UNIX socket created at the beginning:

```console
strace -e 'trace=!poll' -e trace='socket,connect,recvmsg' oneko |& grep -v '\-1 EAGAIN'
```

[Quiz](../quiz/timer.md)

## D-Bus

Use the `dbus` python bindings to get the computer's battery level using a python script.
You can start from the documentation [here](https://dbus.freedesktop.org/doc/dbus-python/tutorial.html#).
You need to read the sections `Connecting to the Bus`, `Proxy objects`, and `Interfaces and methods`.

There's also a skeleton you can use in `support/dbus/get_battery_level.py`.

In summary, your script will start by connecting to the `System Bus`.
Then you'll use the `get_object` method to obtain a proxy object.
On this proxy object, you can actually do the method call as explained [here](https://dbus.freedesktop.org/doc/dbus-python/tutorial.html#interfaces-and-methods):

```text
To call a method, call the method of the same name on the proxy object, passing in the interface name via the dbus_interface keyword argument
```

So, if you want to call the method `this.is.an.interface.method` with the arguments `A` and `B` you can do it like this:

```python
result = proxy.method(A, B, dbus_interface = "this.is.an.interface")
```

## OS-Cloud: More Disk Customization

You might have probably noticed that there are 2 types of disk customizations:

- One type is for things that can be done without running the virtual machine.
If we only want to modify some files inside the disk filesystem, we can do so by mounting the disk.
This is done, for example, in the `disk-templates/ubuntu_22.04/setup_root_password.sh` script.
There we use `nbd_connect_qcow2` + `mount` to mount the disk, then we modify the `/etc/shadow` file to change the root password.

- The second case is for operations that must be done with the virtual machine running.
These are handled in the `ubuntu_22_04_vm_prepare` function: the virtual machine is first started (`start_qemu_for_vm`), then `pexpect` is used to interact with the virtual machine via the `qemu` serial console.
Here we do things like running `ssh-keygen` - a binary that is part of the disk filesystem, which depends on other parts of the operating system from the disk to be running.
Note that in `ubuntu_22_04_vm_prepare`, for convenience, we also do some customizations that fall into the first category (like modifying `/etc/ssh/sshd_config`).

### Copy Additional Files to the Newly Created Disk

This is a customization from the first category.
In `disk-templates/ubuntu_22.04/files` there is a file called `99-os-cloud-welcome` (a script that prints a greeting message).
We want to copy this file to `/etc/update-motd.d` in our newly created disk, so that it will run whenever a user logs in.

To do this, you will create a script called `copy_files.sh` in `disk-templates/ubuntu_22.04`.
This script will receive a path to a `qcow2` disk file as an argument, it will mount the disk, and then copy the file to the necessary location.
Then, in the `create_disk_from_template` function in `disk.py` you will call this script, similar with how the other scripts are called.

You can use `disk-templates/ubuntu_22.04/setup_root_password.sh` as an example.

### SSH Key Setup

We want to be able to log into the virtual machine using an ssh key, instead of the password `123456`.
Notice that the `vm_create` API also accepts an `ssh_key` parameter.
Here, the user can provide an ssh public key, which the system will install in `/root/.ssh/authorized_keys` in the newly created virtual machine.

Your task is to implement this feature, as a customization from the second category (that is, implemented in the `ubuntu_22_04_vm_prepare` function).
The key will be accessible to the function as the `ssh_pub_key` parameter.
Then it's only a matter of writing the key to the appropriate place, using a command like `echo key > /root/.ssh/authorized_keys`.
Note that the `/root/.ssh` directory might not exist, so you need to create it as well.

After the feature is complete, you can test it using the keys in the `support/os-cloud/keys` directory.
This directory contains a pair of public-private keys.
The directory will also be mounted inside the `os-cloud` container in `/keys`.

You will create another virtual machine, passing the public key to `vm_create`:

```console
student@os:~/.../support/os-cloud$ curl -H "Content-Type: application/json" \
	-d '{ "name": "my_vm2", "image": "ubuntu_22.04", "network": "default", "mem_size": "2G", "disk_size": "10G", "ssh_key": "ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC8CDHgeE4NIIIih3wSz58GDkfPLUk2m9gmbZB1f6o8Lzawzb3HVFpslAUWK0f/Ymw9cloInpMo50gWMYFSyJ7ZrOWWak54BedpHDkFAxxy+JCE9b+pkKsrAT7wiir7gn2LHlhj55FLZkC9PpM9cBcrMfzlcP9Bf+2cnpDdINybSLmOUmrI23ANteM4lEVaa2yEbCaJk6dFB8+atz5zPjvVI0Hd+kJK7yJ0xV6Zc2ADle7TKW3dyiXOE9qFKe9933Rj7ocqNXCAO1cxUoJCVuVS7lh+1pSSPXLWLTOhVp/XiLGWVP6KRYmmn710MWKm9Kj1tPiGUphUraL20SJiRT6/ os-cloud-user"}' \
	localhost:5000/vm_create
{"id":2,"status":"ok"}
```

Obtain the IP address that was allocated to the new vm:

```console
student@os:~/.../support/os-cloud$ curl -s -H "Content-Type: application/json" -d '{ "id": 2 }' localhost:5000/vm_info | jq .
{
  "disk_size": 10737418240,
  "id": 2,
  "ip": "192.168.0.3",
  "mem_size": 2147483648,
  "name": "my_vm2",
  "network": "default",
  "os": "ubuntu_22.04",
  "state": "RUNNING"
}
```

Then go inside the `os-cloud` container and ssh to the vm using the private key in `/keys`.
It should work without prompting for the password:

```console
student@os:~/.../support/os-cloud$ docker-compose exec os-cloud bash
root@ac93d3d6cab2:/app# ssh -i /keys/ssh_key root@192.168.0.3
Welcome to Ubuntu 22.04.1 LTS (GNU/Linux 5.15.0-56-generic x86_64)
[...]
Powered by OS Cloud
Last login: Mon Jan  2 19:34:53 2023 from 192.168.0.1
root@ubuntu:~#
```

<!-- textlint-disable terminology -->

## OS-Cloud: Internet Access

<!-- textlint-enable -->

Notice that our virtual machines don't have internet access:

```console
Powered by OS Cloud
Last login: Mon Jan  2 19:52:47 UTC 2023 on ttyS0
root@ubuntu:~# curl google.com
curl: (6) Could not resolve host: google.com
```

In this task, we want to fix this problem.
To do this, we must first understand how the networking for the virtual machines is done.

First, there is the concept of a `network`, which you saw in the previous section.
There is a network called `default`, with the address of `192.168.0.0/24`.
All virtual machines are part of this network, that's why they were allocated ip addresses like `192.168.0.2`.

Let's go inside the `os-cloud` container and take a look at the network interfaces:

```console
$ docker-compose exec os-cloud bash
root@8333e5cefb0d:/app# ip a
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
2: br0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 8a:68:b7:5b:6b:45 brd ff:ff:ff:ff:ff:ff
    inet 192.168.0.1/16 scope global br0
       valid_lft forever preferred_lft forever
3: tap0: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast master br0 state UP group default qlen 1000
    link/ether 8a:68:b7:5b:6b:45 brd ff:ff:ff:ff:ff:ff
4: tap1: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc pfifo_fast master br0 state UP group default qlen 1000
    link/ether fa:f8:7f:83:50:8f brd ff:ff:ff:ff:ff:ff
77: eth0@if78: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default
    link/ether 02:42:ac:16:00:03 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 172.22.0.3/16 brd 172.22.255.255 scope global eth0
       valid_lft forever preferred_lft forever

root@8333e5cefb0d:/app# ps -ef | grep qemu
root          19       8 29 09:15 ?        00:01:26 qemu-system-x86_64 -m 2048 -hda /vm-disks/1/disk.qcow2 -net nic,macaddr=52:54:00:12:34:00 -net tap,ifname=tap0,script=no -monitor telnet::10001,server,nowait -serial telnet::10002,server,nowait -nographic -enable-kvm
root          29       8 28 09:15 ?        00:01:24 qemu-system-x86_64 -m 2048 -hda /vm-disks/2/disk.qcow2 -net nic,macaddr=52:54:00:12:34:01 -net tap,ifname=tap1,script=no -monitor telnet::10003,server,nowait -serial telnet::10004,server,nowait -nographic -enable-kvm
```

Here we have 2 virtual machines running.
Each virtual machine uses a `tap` interface (the `-net tap,ifname=tap0,script=no` parameter for `qemu`).
This means that the `ens0` interface inside the virtual machine corresponds to the `tap0` interface outside the virtual machine.
All the tap interfaces are bridged together into the `br0` bridge, which has the ip address `192.168.0.1`.
Also, each virtual machine has the default gateway configured to be `192.168.0.1`.

In summary, it looks something like this:

![os-cloud](../media/os_cloud_networking.svg)

All the traffic coming from the virtual machines passes through the `br0` interface.
So, in order to make the internet work, all we have to do is a simple `NAT`, with a command like:

```console
root@8333e5cefb0d:/app# iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -j MASQUERADE
```

Now, the virtual machines should have internet access:

```console
root@8333e5cefb0d:/app# ssh root@192.168.0.2
[...]
root@ubuntu:~# curl google.com
<HTML><HEAD><meta http-equiv="content-type" content="text/html;charset=utf-8">
<TITLE>301 Moved</TITLE></HEAD><BODY>
<H1>301 Moved</H1>
The document has moved
<A HREF="http://www.google.com/">here</A>.
</BODY></HTML>
```

Now your task is to run the `iptables` command above automatically when the system starts, so that it's not necessary to run it manually like we did in the above example.

A good place to do this is in the `create_one_network` function in `network.py`.
There you can add another `subprocess.run` call to run `iptables`.
The `192.168.0.0/24` value should not be hardcoded, but you can take it from the `ip_with_prefixlen` member of the `Net` object.
