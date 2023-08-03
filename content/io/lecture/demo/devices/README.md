# Devices

These are some examples on IO devices interaction.

## Build

To build the C examples on Linux, run `make`.

## Running

### hwaddr ioctl

We use `ioctl()` to read the `MAC` address for a network interface.
We create a socket and call `ioctl()` using `SIOCGIFHWADDR` as argument to populate the `ifreq structure`.

```c
// From https://elixir.bootlin.com/linux/latest/source/include/uapi/linux/sockios.h#L80
#define SIOCGIFHWADDR	0x8927		/* Get hardware address		*/
```

Expected output:

```console
student@os:~/.../demo/devices$ # interface name might be different according to personal systems
student@os:~/.../demo/devices$ ./hwaddr-ioctl eth0
Hardware address for interface eth0 is 00:00:5e:00:53:af
```

### Filesystem Size

We open the filesystem block file from `/dev` and call `ioctl()` using `BLKGETSIZE64` as argument to return the total number of bytes from the filesystem.

```c
// https://elixir.bootlin.com/linux/v4.7/source/include/uapi/linux/fs.h#L211
#define BLKGETSIZE64 _IOR(0x12,114,size_t)	/* return device size in bytes (u64 *arg) */
```

Expected output:

```console
student@os:~/.../demo/devices$ # partition name might be different according to personal systems
student@os:~/.../demo/devices$ ./filesystem-size /dev/sda2
Total space 300.132 GB
```

### Read from device

We will analyze how the output of a device changes based on its type.
We will be using `read-from-device.sh` bash script to read `100 bytes` from a given device with `dd`.

Block devices guarantee persistance of data and therefore return the same bytes.

```console
student@os:~/.../demo/devices$ sudo ./read-from-device.sh /dev/sda
Read 100 bytes from /dev/sda:
0000000 63eb d090 00bc 8e7c 8ec0 bed8 7c00 00bf
0000010 b906 0200 f3fc 50a4 1c68 cb06 b9fb 0004
0000020 bebd 8007 007e 7c00 0f0b 0e85 8301 10c5
0000030 f1e2 18cd 5688 5500 46c6 0511 46c6 0010
0000040 41b4 aabb cd55 5d13 0f72 fb81 aa55 0975
0000050 c1f7 0001 0374 46fe 6610 8000 0001 0000
0000060 0000 0000
0000064

student@os:~/.../demo/devices$ sudo ./read-from-device.sh /dev/sda
Read 100 bytes from /dev/sda:
0000000 63eb d090 00bc 8e7c 8ec0 bed8 7c00 00bf
0000010 b906 0200 f3fc 50a4 1c68 cb06 b9fb 0004
0000020 bebd 8007 007e 7c00 0f0b 0e85 8301 10c5
0000030 f1e2 18cd 5688 5500 46c6 0511 46c6 0010
0000040 41b4 aabb cd55 5d13 0f72 fb81 aa55 0975
0000050 c1f7 0001 0374 46fe 6610 8000 0001 0000
0000060 0000 0000
0000064
```

Char devices provide information in real-time so we expect a different output if the environment of the device changes.
Data from char devices are also used by the OS to collect randomness.

```console
student@os:~/.../demo/devices$ ./read-from-device.sh /dev/urandom
Read 100 bytes from /dev/urandom:
0000000 9672 15fc 6631 e9f7 6c6f 99c7 5504 e748
0000010 6a18 6fa0 ffc1 fded b468 b5e9 8121 1187
0000020 19f8 e78c 3a34 b051 de0d d0fa b913 0943
0000030 6bb5 5c77 b763 153e 79d3 b2ca 0715 6fec
0000040 dc27 4acd bf69 1cf8 695e 3c1d a1e2 8234
0000050 de59 9535 c344 9caa 55e3 a104 6d17 7e47
0000060 65f3 3ad8
0000064

student@os:~/.../demo/devices$ ./read-from-device.sh /dev/urandom
Read 100 bytes from /dev/urandom:
0000000 773c e9ff ba84 b7e8 9f76 bba9 6394 4023
0000010 ddc3 4bd5 8777 5a8e 53a5 6532 1fbd 772a
0000020 a8fe 4c76 a1f4 a71e bb0e f525 71bb e8c0
0000030 a6f6 f92f a906 929d e51d 3b8d 5cbf 2101
0000040 fe00 6b07 0d6e 5739 32c0 c586 c289 eb27
0000050 2a4e c817 497a 88c2 d128 9256 8880 4200
0000060 9e8e 8710
0000064
```
