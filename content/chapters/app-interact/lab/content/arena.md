## Arena

### D-Bus

Use the `dbus` python bindings to get the computer's battery level using a python script.
You can start from the documentation [here](https://dbus.freedesktop.org/doc/dbus-python/tutorial.html#).
You need to read the sections `Connecting to the Bus`, `Proxy objects`, and `Interfaces and methods`.

There's also a skeleton you can use in `support/dbus/get_battery_level.py`.

In summary, your script will start by connecting to the `System Bus`.
Then you'll use the `get_object` method to obtain a proxy object.
On this proxy object you can actually do the method call as explained [here](https://dbus.freedesktop.org/doc/dbus-python/tutorial.html#interfaces-and-methods):

```text
To call a method, call the method of the same name on the proxy object, passing in the interface name via the dbus_interface keyword argument
```

So, if you want to call the method `this.is.an.interface.method` with the arguments `A` and `B` you can do it like this:

```python
result = proxy.method(A, B, dbus_interface = "this.is.an.interface")
```
