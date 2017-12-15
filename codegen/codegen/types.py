import copy
from multipledispatch import dispatch
from typing import Union
from itertools import chain

from codegen.functions import *
from codegen.arguments import *
from codegen.modules import *


class Type:
    def __init__(self, type, traits : Traits, modules : Modules):
        self._traits = traits
        self._modules = modules
        self._type = type

    @property
    def includes(self):
        return list(set(self._traits.all().values()))

    @property
    def composition_types(self):
        return [["{}::impl".format(module) for module in self._traits.external] +
                [module.composition_type for module in self._modules[self._type]] +
                [module.composition_type for module in self._modules.initializer]]


class GeneratedType:
    def __init__(self, config : dict, test_config : dict):

        self._type_info = TypeInfo(config.get("type"))
        self._traits = Traits(self, config.get("type").get("traits"))
        self._modules = Modules(self, config.get("type").get("traits"))

        self._types = [Type(type_, self._traits, self._modules) for type_ in types if any(self._traits[type_])]
