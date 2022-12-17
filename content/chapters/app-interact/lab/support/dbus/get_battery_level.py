import dbus

# TODO: get the system bus
system_bus = TODO

# TODO: use "get_object" on the "org.freedesktop.UPower" connection to obtain a handle to the "/org/freedesktop/UPower/devices/DisplayDevice" object
proxy = system_bus.get_object(TODO)

# TODO: call the "Get" method on the interface "org.freedesktop.DBus.Properties"
# and the arguments "org.freedesktop.UPower.Device" and "Percentage"
level = proxy.Get(TODO)

print(level)
