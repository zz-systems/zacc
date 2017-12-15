from multipledispatch import dispatch


class IllegalArgumentError(ValueError):
    pass


class Context:
    def __init__(self, context, data = None):
        self._context   = context
        self._data      = data

    @property
    def context(self):
        return self._context

    @property
    def data(self):
        return self._data

    def __repr__(self):
        return f"{self.__class__.__name__}({self.context!r}, {self.data!r})"



def wrap(arg):
    return arg if isinstance(arg, list) else [arg]

def cleanup(strings) :
    return [str.strip(s) for s in wrap(strings)]

def remove_prefix(string, prefix):
    return string[len(prefix):] if string.startswith(prefix) else string

types = ("default", "boolean", "unsigned")

class NameMangler(Context):
    def __init__(self, name, prefix, **kwds):
        super().__init__(**kwds)

        self._name      = name
        self._name_prefix    = prefix
        self._mangling  = self.data.get("mangling", self._context.mangling)

    @property
    def mangled_name(self):
        if self._mangling:
            return "{}_{}".format(self._name_prefix, self._name)

        return self._name

def filter2(context, data):
    def validate(elem):
        return (not isinstance(elem, tuple)) or not elem[1] or elem[1](context)

    def select(elem):
        return elem[0] if isinstance(elem, tuple) else elem

    return list(map(select, filter(validate, data)))

class Resource:
    def __init__(self, parent, data):
        self._parent   = parent
        self._data     =  wrap(data)

    @property
    def data(self):
        def validate(elem):
            return (not isinstance(elem, tuple)) or not elem[1] or elem[1](self._parent)

        def select(elem):
            return elem[0] if isinstance(elem, tuple) else elem

        return list(map(select, filter(validate, self._data)))

    def __call__(self, *args, **kwargs):
        return self.data #list(filter(lambda x:  x(self._parent), self._data))

    def __str__(self):
        return " ".join(self.data)

    def __repr__(self):
        return " ".join(self.data)


class Resources(Context):
    def __init__(self, **kwds):
        super().__init__(**kwds)

    @property
    def function_prefix(self):
        return filter2(self.context, [("template<typename T = {type}>", lambda x: x.is_dispatched),
                                       "inline",
                                       "constexpr",
                                       ("friend", lambda x: not x.is_constructor)])

    @property
    def function_suffix(self):
        return filter2(self.context, [("const", lambda x: not x.is_member), "noexcept"])

    @property
    def type_template(self):
        return "{}{}"

    @property
    def simple_composition(self):
        return "{}::impl"

    @property
    def complex_composition(self):
        return "{}<impl>::template {}impl"

    @property
    def function_template(self):
        return "{prefix} {returns} {name}({args}) {suffix}"
    #
    # @property
    # def simple_composition(self):
    #     return "{}::impl"
    #
    # @property
    # def complex_composition(self):
    #     return "{}<impl>::template {}impl"

class TypeInfo:
    def __init__(self, data):
        self.arch           = data.get("arch")            or data.get("branch")
        self.type           = data.get("type")
        self.vector_t       = data.get("vector_t")
        self.mask_t         = data.get("mask_vector_t")   or data.get("mask_t", self.vector_t)
        self.scalar_t       = data.get("element_t")       or data.get("scalar_t")
        self.vec_size       = data.get("size")            or data.get("scalar_t")
        self.alignment      = data.get("alignment")
