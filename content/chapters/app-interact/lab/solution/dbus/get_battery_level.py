# SPDX-License-Identifier: BSD-3-Clause

import dbus

system_bus = dbus.SystemBus()

proxy = system_bus.get_object(
    "org.freedesktop.UPower", "/org/freedesktop/UPower/devices/DisplayDevice"
)

level = proxy.Get(
    "org.freedesktop.UPower.Device",
    "Percentage",
    dbus_interface="org.freedesktop.DBus.Properties",
)

print(level)
