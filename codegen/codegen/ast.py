import inspect
from enum import *


class IndentingRepr:
    _level = -1

    @property
    def level(self):
        return type(self)._level

    @level.setter
    def level(self, val):
        type(self)._level = val

    def render(self, obj):
        def indent(level = 0):
            return "\t" * (self.level + level)

        def render(val):
            if isinstance(val, list):
                items = "".join([f"\n{indent(2)}{v}" for v in val])
                return f"[{items}\n{indent(1)}]"

            if isinstance(val, dict):
                items = "".join([f"\n{indent(2)}{k} = {v}" for k,v in val])
                return f"{{{items}\n{indent(1)}}}"

            return f"{val}"

        all_attributes = inspect.getmembers(obj, lambda a:not(inspect.isroutine(a)))
        attributes = [ (k,v) for k,v in all_attributes if not(k.startswith('__') and k.endswith('__')) ]
        try:
            self.level += 1
            attributes = "\n".join([ f"{indent(1)}{k} = {render(v)}" for k,v in attributes])
        except:
            attributes = "Error"
        finally:
            result = f"{obj.__class__.__name__}:\n{attributes}"
            self.level -= 1

        return result

class AstNode:
    def __repr__(self):
        return IndentingRepr().render(self)

class AstRoot(AstNode):
    def __init__(self, type, traits, modules):
        self.type = type
        self.traits = traits
        self.modules = modules


class TypeDescriptorNode(AstNode):
    def __init__(self, name, target, vector_type, mask_type, scalar_type, size, alignment, traits):

        self.name = name
        self.target = target
        self.vector_type = vector_type
        self.mask_type = mask_type
        self.scalar_type = scalar_type
        self.size = size
        self.alignment = alignment
        self.traits = traits



class TraitsNode(AstNode):
    def __init__(self, shared, default, boolean, unsigned):

        self.shared = shared
        self.default = default
        self.boolean = boolean
        self.unsigned = unsigned

        self.all = default + boolean + unsigned

class ModulesNode(AstNode):
    def __init__(self, initializers, modules):
        self.initializers = initializers
        self.modules = modules


class ModuleTypes(Enum):
    DEFAULT = auto()
    BOOLEAN = auto()
    UNSIGNED = auto()
    SHARED = auto()

class ModuleNode(AstNode):
    def __init__(self, name, mangling, type, functions):
        self.name = name
        self.mangling = mangling
        self.type = type
        self.functions = functions

class InitializerNode(AstNode):
    def __init__(self, signature, initializer, body):
        self.signature      = signature
        self.initializer    = initializer
        self.bodies         = [body]

class InitializerSignatureNode(AstNode):
    def __init__(self, prefix, suffix, arguments, initializer):
        self.prefix         = prefix
        self.suffix         = suffix
        self.arguments      = arguments
        self.initializer    = initializer

class InitializerBodyNode(AstNode):
    def __init__(self, arguments, instructions):
        self.arguments      = arguments
        self.instructions   = instructions

class FunctionNode(AstNode):
    def __init__(self, signature, bodies):
        self.signature  = signature
        self.bodies     = bodies

    def render(self):
        pass

class FunctionSignatureNode(AstNode):
    def __init__(self, name, mangling, prefix, suffix, return_type, arguments):
        self.name = name
        self.mangling = mangling
        self.prefix = prefix
        self.suffix = suffix
        self.return_type = return_type
        self.arguments = arguments

class FunctionBodyNode(AstNode):
    def __init__(self, target, selector, return_type, instructions):
        self.target         = target
        self.selector       = selector
        self.return_type    = return_type
        self.instructions   = instructions

class InstructionsNode(AstNode):
    def __init__(self, return_type, arguments, body):
        self.return_type = return_type
        self.arguments = arguments
        self.body = body

class ArgumentNode(AstNode):
    def __init__(self, name, type):

        if isinstance(name, list) and len(name) == 2:
            self.type = name[0]
            self.name = name[1]
        else:
            # allow patterns like ('typename test::test', 'variable')
            parts = [type] + name.split()

            # set offset to ignore default_type
            offset = len(parts) > 2
            self.type = " ".join(parts[offset:-1])
            self.name = parts[-1]