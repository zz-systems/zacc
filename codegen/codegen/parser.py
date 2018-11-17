from codegen.lexer import Lexer, Tokens
from codegen.ast import *
from codegen.common import wrap, IllegalArgumentError

import pprint

class SyntaxError(ValueError):
    pass

def peek(data, token):
    return data and token in data

def expect(data, token):
    if not token in data:
        raise SyntaxError(f"Expected: {token}")

    return data[token]

def accept(data, token, default = None):
    return (data or {}).get(token, default)

def accept_except(data, tokens):
    return { k:v for k,v in data.items() if k not in wrap(tokens) }


class Parser():
    def __init__(self, lexer: Lexer):
        self._lexer = lexer

    def parse(self, data):
        data = self._lexer.lex(data)

        type_ = expect(data, Tokens.TYPE)
        traits = self.traits(expect(type_, Tokens.TRAITS))

        return AstRoot(
            type=   self.type_descriptor(type_),
            traits= traits,
            modules=self.modules(traits, expect(data, Tokens.MODULES))
        )


    def type_descriptor(self, data) -> TypeDescriptorNode:
        return TypeDescriptorNode(name=expect(data, Tokens.TYPE), target=expect(data, Tokens.TARGET),
                                  vector_type=expect(data, Tokens.VECTOR), mask_type=expect(data, Tokens.MASK),
                                  scalar_type=expect(data, Tokens.SCALAR), size=expect(data, Tokens.SIZE),
                                  alignment=expect(data, Tokens.ALIGN), traits=self.traits(expect(data, Tokens.TRAITS)))

    def traits(self, data) -> TraitsNode:
        return TraitsNode(shared=         accept(data, Tokens.SHARED, []),
                          default=        expect(data, Tokens.DEFAULT),
                          boolean=        accept(data, Tokens.BOOLEAN, []),
                          unsigned=       accept(data, Tokens.UNSIGNED, []))

    def modules(self, traits, data) -> ModulesNode:

        initializers = expect(data, Tokens.INIT)
        modules = accept_except(data, Tokens.INIT)

        def make_modules(func, data, traits, type=None):
            if isinstance(traits, list):
                return [func(name, type, data[name]) for name in traits]
            return \
                make_modules(func, data, traits.default, ModuleTypes.DEFAULT) + \
                make_modules(func, data, traits.boolean, ModuleTypes.BOOLEAN) + \
                make_modules(func, data, traits.unsigned, ModuleTypes.UNSIGNED)

        return ModulesNode(
            initializers=make_modules(self.initializer_module, initializers, self.traits({ k:[k] for k,v in initializers.items() })),
            modules=make_modules(self.module, modules, traits))

    def module(self, name, type, data) -> ModuleNode:
        return ModuleNode(name=name,
                          mangling=False,#accept(data, Tokens.MANGLING),
                          functions = [self.function(data, k, v) for k,v in accept_except(data, Tokens.MANGLING).items()],
                          type=type)

    def initializer_module(self, name, type, data) -> ModuleNode:
        # add default constructor
        initializers = [{Tokens.ARGS : { Tokens.RAW : "", Tokens.TYPE : " "}, Tokens.INIT : ""}] + data

        module = ModuleNode(name="constructable",#self._lexer.unlex(name),
                          mangling=False,#accept(data, Tokens.MANGLING),
                          functions=[self.initializer(entry) for entry in initializers],
                          type=type)

        #default_cons = [] if any(cons.signature.arguments == [] for cons in module.functions) else [self.initializer({'args': 'void ', 'init': ''})]
        #module.functions = default_cons + module.functions

        return module

    def initializer(self, data):
        data = self._lexer.lex(data)

        args = self.arguments(expect(data, Tokens.ARGS))
        body = expect(data, Tokens.INIT)

        init_data = {
            Tokens.BODY: body[Tokens.BODY] if isinstance(body, dict) else body,
            Tokens.ARGS: body[Tokens.ARGS] if isinstance(body, dict) else expect(data, Tokens.ARGS)
        }

        init = self.function(None, None, init_data).bodies[0].instructions
        body = self.instructions(None, args, accept(data, Tokens.BODY))

        prefix = accept(data, Tokens.PREFIX)
        suffix = accept(data, Tokens.SUFFIX)

        return InitializerNode(signature    = InitializerSignatureNode(prefix=prefix, suffix=suffix, arguments=args, initializer  = init),
                            initializer  = init,
                            body         = InitializerBodyNode(args, body))

    def function(self, module_data, name, data) -> FunctionNode:

        # convert non-verbose function definition to verbose
        # covers case:
        # - function_name: function_body            (for instance vadd: _mm_add_epi32)
        if not isinstance(data, dict):
            data = { Tokens.BODY: data }

        # convert non-verbose function definition to verbose
        # covers case:
        # - function_name: { body: function_body }  (for instance vbslli: { args: [one, other], body: _mm_slli_epi32(one, other) })
        if not isinstance(expect(data, Tokens.BODY), dict):
            data[Tokens.BODY] = { Tokens.DEFAULT : { Tokens.REQUIRES: [], Tokens.BODY : data[Tokens.BODY] } }

        # supply default arguments
        if not peek(data, Tokens.ARGS):
            data[Tokens.ARGS] = ["one", "other"]

        body        = expect(data, Tokens.BODY)
        _           = expect(body, Tokens.DEFAULT)

        # inject outer arguments and return type into bodies
        for k, v in body.items():
            body[k][Tokens.TARGET]  = self._lexer.unlex(k)
            body[k][Tokens.RETURNS] = accept(data, Tokens.RETURNS)
            body[k][Tokens.ARGS] = accept(data, Tokens.ARGS)

        signature   = self.function_signature(module_data, name, data)
        bodies      = [self.function_body(v) for k,v in body.items()]

        return FunctionNode(signature=signature, bodies=bodies)

    def function_signature(self, module_data, name, data):

        arguments   = self.arguments(expect(data, Tokens.ARGS))
        mangling    = accept(data, Tokens.MANGLING) or accept(module_data, Tokens.MANGLING)
        prefix      = accept(data, Tokens.PREFIX)
        suffix      = accept(data, Tokens.SUFFIX)
        return_type = accept(data, Tokens.RETURNS)

        return FunctionSignatureNode(name=name, mangling=mangling,
                                     prefix=prefix, suffix=suffix,
                                     return_type=return_type,
                                     arguments=arguments)

    def function_body(self, data):
        if isinstance(data, dict):
            arguments   = self.arguments(expect(data, Tokens.ARGS))
            target      = expect(data, Tokens.TARGET)
            selector    = expect(data, Tokens.REQUIRES)
            return_type = expect(data, Tokens.RETURNS)
            instructions= self.instructions(return_type, arguments, expect(data, Tokens.BODY))

            return FunctionBodyNode(target=target, selector=selector, return_type=return_type, instructions=instructions)

    def instructions(self, return_type, arguments, data):
        return InstructionsNode(return_type, arguments, data)


    def arguments(self, data):
        if isinstance(data, str):
            data = { Tokens.RAW : data }

        if isinstance(data, list):
            return [self.argument(name=arg) for arg in data]

        if isinstance(data, dict) and peek(data, Tokens.RAW):
            return [self.argument(name = expect(data, Tokens.RAW), type=accept(data, Tokens.TYPE))]

        if isinstance(data, dict):
            from_, to   = expect(data, Tokens.FROM), expect(data, Tokens.TO)

            prefix      = accept(data, Tokens.PREFIX) or "_"
            type_       = accept(data, Tokens.TYPE)

            if None in [from_, to] or from_ < 0 or to < 0:
                raise IllegalArgumentError(f"Invalid argument index range from: {from_}, to: {to}.")
            else:
                ids = range(from_, to) if from_ < to else reversed(range(to, from_))
                return [self.argument(name=prefix + str(id), type=type_) for id in ids]


    def argument(self, name, type=None):
        return ArgumentNode(name, type or "Composed")