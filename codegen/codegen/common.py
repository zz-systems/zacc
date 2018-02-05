
class IllegalArgumentError(ValueError):
    pass

def wrap(arg):
    return arg if isinstance(arg, list) else [arg]

def cleanup(strings) :
    return [str.strip(s) for s in wrap(strings)]

def remove_prefix(string, prefix):
    return string[len(prefix):] if string.startswith(prefix) else string
