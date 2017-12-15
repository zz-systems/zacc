from multipledispatch import dispatch
from typing import Union
from collections import Iterable

from codegen.common import *


class InitializerList(Context):
    """
    InitializerList(dict)      -> InitializerList object
    InitializerList(list)      -> InitializerList object
    InitializerList(string)    -> InitializerList object

    Returns an object which represents a C++ initialization list:

        constexpr cons(int a, int b) : value(a + b) {}
        -------------------------------^

    """

    @dispatch(object, (dict, str))
    def __init__(self, context, data):
        super().__init__(context, data)
        self._initializers = Initializer(self, data)

    @dispatch(object, Iterable)
    def __init__(self, context, data):
        super().__init__(context, data)
        self._initializers = [Initializer(self, i) for i in data]

    @property
    def invocation(self):
        if isinstance(self._initializers, Iterable):
            return ", ".join(map(str, self._initializers))

        return "base_t({})".format(self._initializers)

    def __str__(self):
        return self.invocation

class Initializer(Context):
    """
    Initializer(dict)      -> Initializer object
    Initializer(list)      -> Initializer object
    Initializer(string)    -> Initializer object

    Returns an object which represents a C++ initialization:

        auto i = value(a)
        ---------^

    """
    @dispatch(object, dict)
    def __init__(self, context: InitializerList, data: dict):
        super().__init__(context)

        arguments       = ArgumentList(self, data.get("args", ''))
        body            = data.get("body")

        self._data      = data
        self._initializer = "{}({})".format(body, arguments.invocation)

    @dispatch(object, object)
    def __init__(self, context, data):
        super().__init__(context)

        self._data = self._initializer  = data

    @property
    def invocation(self):
        return self._initializer

    def __str__(self):
        return self.invocation


class ArgumentList(Context):
    """
    ArgumentList(dict)      -> ArgumentList object
    ArgumentList(list)      -> ArgumentList object
    ArgumentList(string)    -> ArgumentList object

    Returns an object which represents a list of C++ function arguments:

        void func(int a, float b)
        ----------^

    """

    @dispatch(object, dict)
    def __init__(self, context : Union[object, Initializer], data : dict):
        """
        Constructs an ArgumentList object from incoming dictionary.
        There are two mutually exclusive cases:

        1)  { raw: string }
            Wraps incoming string as one single "argument". No processing happens so far.
        2)  { from: int, to: int, type: str }
            Generates an argument range, type is optional.
            Example: AVX512 int8x64: { from: 64, to: 0, type: int8 } -> arg63, arg62, ...
        :param context: Executing parent context
        :param data: Input data
        """
        super().__init__(context)
        self._data = data

        raw         = data.get("raw")
        prefix      = data.get("prefix", "arg")
        from_, to   = data.get("from"), data.get("to")
        type_       = data.get("type", "composed_t")

        if raw:
            self._arguments = [Argument(self, str(raw), type_)]
        elif None in [from_, to] or from_ < 0 or to < 0:
            raise IllegalArgumentError(f"Invalid argument index range from: {from_}, to: {to}.")
        else:
            ids = range(from_, to) if from_ < to else reversed(range(to, from_))
            self._arguments = [Argument(self, prefix + str(a), type_) for a in ids]


    @dispatch(object, object)
    def __init__(self, parent : Union[object, Initializer], data : Union[str, list]):
        """
         Constructs an ArgumentList object from incoming string or list.

        :param parent: Executing parent context
        :param data: Input data
        """

        super().__init__(parent)
        self._data      = data
        self._arguments = [Argument(self, a) for a in wrap(data)]

    @property
    def declaration(self):
        """ returns an argument declaration (int a, int b, int c) """
        return ", ".join([a.declaration for a in self._arguments])

    @property
    def invocation(self):
        """ return an argument invocation/passthrough (a, b, c) """
        return ", ".join([a.invocation for a in self._arguments])

    def __str__(self):
        return self.declaration

class Argument(Context):
    """
    Argument(value[, type]) -> Argument object

    Returns an object which represents a C++ function argument.
    Adds a type if necessary

    """

    def __init__(self, context : ArgumentList, value : str, type_ : str = "composed_t"):
        super().__init__(context)

#        if not value: raise IllegalArgumentError("Value must not be empty.")

        # allow patterns like ('typename test::test', 'variable')
        parts = [type_] + value.split()

        # set offset to ignore default_type
        offset = len(parts) > 2
        self._type = " ".join(parts[offset:-1])
        self._name = parts[-1]

    @property
    def declaration(self):
        """ returns an argument declaration (int a)"""
        return " ".join([self._type, self._name])

    @property
    def invocation(self):
        """ return an argument invocation/passthrough (a) """
        return self._name

    def __str__(self):
        return self.declaration