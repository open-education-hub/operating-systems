# Running the operating-systems VM on macOS

## Prerequisites

Make sure `qemu` is installed on your system:

```console
brew install qemu
```

## Running the VM

First, download the `so-ubuntu-20-04.img` image from [here](https://repository.grid.pub.ro/cs/so/linux-2024/).
This may take some time (total size of the image is around 8.8GB).

Then, use the `qemu_run.sh` script to run the VM:

```console
sudo ./qemu_run.sh <path_to_vm_image> <number_of_cores> <number_of_GB_for_the_VM_RAM> <host_interface>
```

Here is the description of the mandatory arguments:

- `path_to_vm_image`: path where you downloaded the `so-ubuntu-20-04.img` file.
- `number_of_cores`: the number of cores you want the VM to use (we suggest at least 2 cores)
- `number_of_GB_for_the_VM_RAM`: how many GB of RAM memory you want to have on your VM (we suggest at least 2GB)
- `host_interface`: the host interface used to provide the VM with internet access

In order to find the value for `host_interface`, you can use the following command on your macOS host.

```console
networksetup -listallhardwareports
```

The value of `host_interface` will be the device name of one of your Wi-Fi or ethernet ports, according to your type of connection.
As an example, for a macOS host connected to Wi-Fi, we could get the following `networksetup` output:

```console
Hardware Port: Ethernet Adapter (en6)
Device: en6
Ethernet Address: b6:e0:14:1e:65:8e

Hardware Port: Thunderbolt Bridge
Device: bridge0
Ethernet Address: 36:a1:9b:9f:e8:80

Hardware Port: Wi-Fi
Device: en0
Ethernet Address: bc:d0:74:ad:8a:b1
```

Therefore, we choose `en0` as the value of the `host_interface` parameter.

Using the above recommendations, the command to start the VM will look like this:

```console
sudo ./qemu_run.sh so-ubuntu-20-04.img 2 2 en0
```
