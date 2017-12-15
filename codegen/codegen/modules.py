import copy
from multipledispatch import dispatch
from typing import Union
from itertools import chain

from codegen.functions import *
from codegen.arguments import *



class Module(NameMangler):
    def __init__(self, context, name, data, type_prefix = "z", module_prefix = ""):
        super(Module, self).__init__(context=context, prefix=context.type, name=name, data=data)

        self._type_prefix, self._module_prefix = type_prefix, module_prefix
        attributes = [ "mangling" ]

        # Module stuff
        self._name          = name
        self._functions     = [Function(self, k, v) for k,v in data.items() if k not in attributes]

    @property
    def type(self):
        return self._context.type

    @property
    def type_prefix(self):
        return self._type_prefix

    @property
    def module_prefix(self):
        return self._module_prefix

    @property
    def composition_type(self):
        return "{}<impl>::template {}impl".format(self.mangled_name, self.type_prefix)

    @property
    def return_type(self):
        return self.type_template.format(self.type_prefix, self.type)

    @property
    def name(self):
        return remove_prefix(self._name, self.module_prefix)

    @name.setter
    def name(self, name):
        self._name = name

    @property
    def functions(self):
        return self._functions

    @functions.setter
    def functions(self, functions):
        self._functions = functions

    @property
    def test_config(self):
        return self._parent.test_config

    @property
    def has_tests(self):
        return any(func.has_tests for func in self._functions)


class InitializerModule(Module):
    def __init__(self, parent, name, data, type_prefix = "z", module_prefix = ""):
        super(InitializerModule, self).__init__(parent, name, data, type_prefix, module_prefix)

        self._parent = parent
        constructors = data.get(name, [])

        # add default constructor if necessary
        default_cons = [] if any(cons.get('args') == '' for cons in constructors) else [ {'args':'','init':''} ]
        constructors = default_cons + constructors

        # build constructors
        self.functions = [Constructor(self, entry) for entry in constructors]

class Traits(Context):

    def __init__(self, context, data):
        super().__init__(context, data)

        self._default       = data.get("internal", {})
        self._boolean       = data.get("boolean", {})
        self._unsigned      = data.get("unsigned", {})
        self._external      = data.get("external", {})

        self._initializer = { t + "_construction" : {} for t in types}

    @property
    def initializer(self):
        return self._initializer

    @initializer.setter
    def initializer(self, modules):
        self._initializer = modules

    @property
    def boolean(self):
        return self._boolean

    @boolean.setter
    def boolean(self, modules):
        self._boolean = modules

    @property
    def unsigned(self):
        return self._unsigned

    @unsigned.setter
    def unsigned(self, modules):
        self._unsigned = modules

    @property
    def default(self):
        return self._default

    @default.setter
    def default(self, modules):
        self._default = modules

    @property
    def external(self):
        return self._external

    @external.setter
    def external(self, modules):
        self._external = modules

    @property
    def all(self):
        #return self.initializer.items() + self.boolean.items() + self.internal.items() + self.external
        return dict(chain.from_iterable(d.items() for d in (self.initializer, self.boolean, self.unsigned, self.default, self.external)))

    def __getitem__(self, item):
        return dict(initializer=self.initializer, boolean=self.boolean, unsigned=self.unsigned, default=self.default,
             external=self.external)[item]


class Modules(Traits):
    def __init__(self, context, data):
        super(Modules, self).__init__(context, data)

        traits = Traits(context, data)

        def make_module(name, data):
            if name in traits._initializer:
                return InitializerModule(self, name, data)

            if name in traits._boolean:
                return Module(self, name, data, "b", "boolean")

            if name in traits._unsigned:
                return Module(self, name, data, "u", "unsigned")

            return Module(self, name, data)

        self._initializer   = {n:make_module(n, d) for n,d in traits.initializer}

        self._default       = {n:make_module(n, d) for n,d in traits.default}
        self._boolean       = {n:make_module(n, d) for n,d in traits.boolean}
        self._unsigned      = {n:make_module(n, d) for n,d in traits.unsigned}
        self._external      = {n:make_module(n, d) for n,d in traits.external}


