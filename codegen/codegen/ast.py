
class AstNode:
    def __init__(self, indent_level):
        self._indent_level = indent_level

    def __repr__(self):
        indent = "\t" * self._indent_level
        return f"\n{indent}{self.__class__.__name__}"

class Ast:
    def __init__(self, type, modules):
        self.type = type
        self.modules = modules


class TypeDescriptorNode:
    def __init__(self, type, target, vector_type, mask_type, scalar_type, size, alignment, traits):
        self.type = type
        self.target = target
        self.vector_type = vector_type
        self.mask_type = mask_type
        self.scalar_type = scalar_type
        self.size = size
        self.alignment = alignment
        self.traits = traits

class TraitsNode:
    def __init__(self, shared, default, boolean, unsigned):

        self.shared = shared
        self.default = default
        self.boolean = boolean
        self.unsigned = unsigned

    def __repr__(self):
        return f"{self.__class__.__name__} shared: {self.shared} default: {self.default} boolean: {self.boolean} unsigned: {self.unsigned}"

class ModulesNode:
    def __init__(self, initializer, modules):
        self.initializer = initializer
        self.modules = modules

    def __repr__(self):
        return f"{self.__class__.__name__} initializer: {self.initializer} modules: {self.modules}"

class ModuleNode:
    def __init__(self, name, mangling, type_prefix, module_prefix, functions):
        self.name = name
        self.mangling = mangling
        self.type_prefix = type_prefix
        self.module_prefix = module_prefix
        self.functions = functions

    def __repr__(self):
        return f"\n\t{self.__class__.__name__} name: {self.name} mangling: {self.mangling} type_prefix: {self.type_prefix} module_prefix: {self.module_prefix} functions: {self.functions}"

class InitializerModuleNode:
    def __init__(self, name, type_prefix, module_prefix, functions):
        self.name = name
        self.type_prefix = type_prefix
        self.module_prefix = module_prefix
        self.functions = functions

    def __repr__(self):
        return f"\n\t{self.__class__.__name__} name: {self.name} type_prefix: {self.type_prefix} module_prefix: {self.module_prefix} functions: {self.functions}"

class InitializerNode:
    def __init__(self, signature, body):
        self.signature      = signature
        self.body           = body

class InitializerSignatureNode:
    def __init__(self, prefix, suffix, arguments, initializer):
        self.prefix         = prefix
        self.suffix         = suffix
        self.arguments      = arguments
        self.initializer    = initializer

    def render(self):
        return "{prefix} {name}({args}) : {initializer} {suffix}".format(prefix=self.prefix,
                                                                   name="__impl",
                                                                   args = ", ".format([f"{arg.type} {arg.name}" for arg in self.arguments]),
                                                                   initializer=f"base_t({self.initializer.render()})",
                                                                   suffix = self.suffix)

class InitializerBodyNode:
    def __init__(self, arguments, body):
        self.arguments      = arguments
        self.body           = body

    def render(self):
        return self.body.render()

class FunctionNode:
    def __init__(self, signature, bodies):
        self.signature  = signature
        self.bodies     = bodies

    def __repr__(self):
        return f"\n\t\t{self.__class__.__name__} signature: '{self.signature}' bodies: {self.bodies}"

    def render(self):
        pass

class FunctionSignatureNode:
    def __init__(self, name, mangling, prefix, suffix, return_type, arguments):
        self.name = name
        self.mangling = mangling
        self.prefix = prefix
        self.suffix = suffix
        self.return_type = return_type
        self.arguments = arguments

    def __repr__(self):
        return f"\n\t\t\t{self.__class__.__name__} name: '{self.name}' mangling: {self.mangling} prefix: '{self.prefix}' return_type: '{self.return_type}' arguments: {self.arguments}"

    def render(self):
        return "{prefix} {returns} {name}({args}) {suffix}".format(prefix=self.prefix,
                                                                   returns=self.return_type,
                                                                   name=self.name,
                                                                   args = ", ".format([f"{arg.type} {arg.name}" for arg in self.arguments]),
                                                                   suffix = self.suffix)

class FunctionBodyNode:
    def __init__(self, selector, return_type, instructions):
        self.selector       = selector
        self.return_type    = return_type
        self.instructions   = instructions

    def __repr__(self):
        return f"\n\t\t\t{self.__class__.__name__} selector: {self.selector} instructions: {self.instructions}"

    def render(self):
        body = self.instructions.render()

        if body[-1].find("return") == -1\
                and self.return_type.find("void") == -1:
            body[-1] = "return " + body[-1]

        return body

class InstructionsNode:
    def __init__(self, arguments, body):
        self.arguments = arguments
        self.body = body


    def __repr__(self):
        return f"\n\t\t\t\t{self.__class__.__name__} arguments: {self.arguments} body: {self.body}"

    def render(self):
        arguments   = ", ".join([arg.name for arg in self.arguments])
        body        = self.body

        if len(body) == 1 and body[0].find('(') == -1:
            body[0] = "{}({})".format(body[0], arguments)

        return [b + ';' if not b.rstrip().endswith(';') else b for b in body]

class ArgumentNode:
    default_type = "composed_t"
    def __init__(self, type, name):

        if isinstance(name, list) and len(name) == 2:
            self.type = name[0]
            self.name = name[1]
        else:
            # allow patterns like ('typename test::test', 'variable')
            parts = [type or self.default_type] + name.split()

            # set offset to ignore default_type
            offset = len(parts) > 2
            self.type = " ".join(parts[offset:-1])
            self.name = parts[-1]

    def __repr__(self):
        return f"\n\t\t\t\t{self.__class__.__name__} type: {self.type} name: {self.name}"
