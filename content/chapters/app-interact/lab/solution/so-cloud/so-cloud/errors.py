class VMNotFoundException(Exception):
    pass


class NetworkNotFoundException(Exception):
    pass


class NetworkCreateException(Exception):
    pass


class InterfaceCreateException(Exception):
    pass


class VMAlreadyExistsException(Exception):
    pass


class VMWithIPNotFoundException(Exception):
    pass


class VMWithIfaceNotFoundException(Exception):
    pass


class NetworkFullException(Exception):
    pass


class DatabaseError(Exception):
    pass


class DiskTemplateNotFound(Exception):
    pass


class CreateDiskFromTemplateException(Exception):
    pass
