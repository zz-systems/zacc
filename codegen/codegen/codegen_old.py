import yasha
import copy


from itertools import chain
from multipledispatch import dispatch

class Struct:
    def __init__(self, entries):
        self.__dict__.update(entries)


class Util:
    bval_prefix = "boolean_"

    @staticmethod
    def is_bval(string):
        return string.startswith(Util.bval_prefix)

    @staticmethod
    def remove_prefix(string, prefix = bval_prefix):
        return string[len(prefix):] if string.startswith(prefix) else string

    type_prefix = { True:"b", False:"z" }

class TypeInfo:
    def __init__(self, data):
        self.arch           = data.get("arch")            or data.get("branch")
        self.type           = data.get("type")
        self.vector_t       = data.get("vector_t")
        self.mask_t         = data.get("mask_vector_t")   or data.get("mask_t", self.vector_t)
        self.scalar_t       = data.get("element_t")       or data.get("scalar_t")
        self.vec_size       = data.get("size")            or data.get("scalar_t")
        self.alignment      = data.get("alignment")

        
class NameMangler:
    def __init__(self, parent, name, prefix, data):
        self._name      = name
        self._prefix    = prefix
        self._mangling  = data.get("mangling", parent.mangling)

    @property
    def mangled_name(self):
        if self._mangling:
            return "{}_{}".format(self._prefix, self._name)

        return self._name

    # @property
    # def name(self):
    #     return self._name

    @property
    def prefix(self):
        return self._prefix

    @property
    def mangling(self):
        return self._mangling


class ResourcePart:
    def __init__(self, expression, condition = None):
        self._expression = expression
        self._condition = condition

    def __call__(self, *args, **kwargs):
        return self._condition is None or self._condition(*args)

    def __str__(self):
        return self._expression

    def __repr__(self):
        return self._expression

class Resource:
    def __init__(self, parent, data):
        self._parent   = parent
        self._data     = data if isinstance(data, list) else [data]


    @property
    def data(self):
        return list(filter(lambda x: (not isinstance(x, tuple)) or not x[1] or x[1](self._parent), self._data))

    def __call__(self, *args, **kwargs):
        return list(filter(lambda x: (not isinstance(x, tuple)) or not x[1] or x[1](*args), self._data))

    def __str__(self):
        return " ".join(self.data)

    def __repr__(self):
        return " ".join(self.data)


class Resources:
    def __init__(self, parent):
        self._parent = parent

    @property
    def function_prefix(self):
        return Resource(self._parent, [("template<typename T = {type}>", lambda x: not x.is_dispatched),
                                       "inline",
                                       "constexpr",
                                       ("friend", lambda x: not x.is_constructor)])

    @property
    def function_suffix(self):
        return Resource(self._parent, [("const", lambda x: not x.is_member), "noexcept"])

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




class Module(NameMangler, Resources):
    def __init__(self, parent, name, data, type_prefix = "z", module_prefix = ""):
        super(Module, self).__init__(parent, self.type, name, data)
        super(Module, self).__init__(self)

        self._parent = parent

        self._type_prefix, self._module_prefix = type_prefix, module_prefix
        attributes = [ "mangling" ]

        # Module stuff
        self._name          = name
        self._functions     = [Function(self, k, v) for k,v in data.items() if k not in attributes]

    @property
    def type(self):
        return self._parent.type

    @property
    def type_prefix(self):
        return self._type_prefix

    @property
    def module_prefix(self):
        return self._module_prefix

    @property
    def return_type(self):
        return self.type_template.format(self.type_prefix, self.type)

    @property
    def name(self):
        return Util.remove_prefix(self._name, self.module_prefix)

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



class ZValModule(Module):
    def __init__(self, parent, name, data):
        super(ZValModule, self).__init__(parent, name, data)

    @property
    def type_prefix(self):
        return "z"

class ZValInitializer(ZValModule, InitializerModule):
    def __init__(self, parent, name, data):
        super(ZValInitializer, self).__init__(parent, name, data)
        pass



class BValModule(Module):
    def __init__(self, parent, name, data):
        super(BValModule, self).__init__(parent, name, data)


    @property
    def type_prefix(self):
        return "b"

    @property
    def module_prefix(self):
        return "boolean_"


class BValInitializer(BValModule, InitializerModule):
    def __init__(self, parent, name, data):
        super(BValInitializer, self).__init__(parent, name, data)
        pass





class Traits:
    DEFAULT = "internal"
    BOOLEAN = "boolean"
    UNSIGNED = "unsigned"
    EXTERNAL = "external"

    CATEGORIES = ["internal","boolean","unsigned","external"]
    def __init__(self, parent, data):
        self._parent        = parent

        self._initializer   = {'construction' :{}, 'boolean_construction' :{}}

        #self._modules = { c:data.get(c, {}) for c in Traits.CATEGORIES }
        self._internal      = data.get("internal", {})
        self._boolean       = data.get("boolean", {})
        self._unsigned      = data.get("unsigned", {})
        self._external      = data.get("external", {})

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
    def internal(self):
        return self._internal

    @internal.setter
    def internal(self, modules):
        self._internal = modules

    @property
    def external(self):
        return self._external

    @external.setter
    def external(self, modules):
        self._external = modules

    @property
    def all(self):
        #return self.initializer.items() + self.boolean.items() + self.internal.items() + self.external
        return dict(chain.from_iterable(d.items() for d in (self.initializer, self.boolean, self.internal, self.external)))


class Modules(Traits):
    def __init__(self, parent, data):
        super(Modules, self).__init__(parent, data)
        self._parent        = parent

        self._initializer   = {n:InitializerModule(self, n, d) for n,d in self.initializer}

        self._internal      = {n:Module(self, n, d) for n,d in self.internal}
        self._boolean       = {n:Module(self, n, d, "b", "boolean") for n,d in self.boolean}
        self._unsigned      = {n:Module(self, n, d, "u", "unsigned") for n,d in self.unsigned}
        self._external      = {n:Module(self, n, d) for n,d in self.external}

class Function(NameMangler, Resources):
    def __init__(self, parent, name, data):
        super(Function, self).__init__(self, name, parent.name, data)
        super(Function, self).__init__(data)

        self._parent        = parent
        self._name          = name


        self._body          = data.get("body", data)

        self._default_target      = "default"


        self._requires      = data.get("requires", [])
        self._is_member     = data.get("member", False)

        self._prefix     = data.get("prefix", self.function_prefix())

        self._suffix     = data.get("suffix", self.function_suffix())

        #returntype = parent.returntype #("b" if (self.parent.name in ["equatable", "comparable", "logical"]) else "z") + self.parent.parent.type
        self._returns    = data.get("returns", "{}<base_t::features>".format(parent.return_type))


        assert not self.is_dispatched or self._default_target in self._body, "default target required"

        self._arguments     = ArgumentList(self, data.get("args", ["one", "other"]))



        test       = parent.test_config and parent.test_config.get(self.name)

        if isinstance(test, list) and len(test) == 2:
            self.actual     = test[0].format(type = "z"+parent.parent.type)#+"<>")
            self.expected   = test[1]
            self.test = [self.actual, self.expected]
        else:
            self.test = None


    @property
    def name(self):
        return self._name

    @property
    def is_constructor(self):
        return self._is_member and self._name == ""

    @property
    def is_member(self):
        return self._is_member and self._name != ""


    @property
    def signature(self):
        assert self._name != "", "Function must have a name"

        return self.function_template.format(prefix     = self._prefix,
                                             returns    = self._returns,
                                             name       = self.mangled_name,
                                             args       = self._arguments,
                                             suffix     = self._suffix).strip()
    @property
    def has_tests(self):
        return self.test is not None

    @property
    def instructions(self):
        return FunctionBody(self, self._body).instructions

    @property
    def is_dispatched(self):
        return isinstance(self._body, dict)

    @property
    def target_definitions(self):
        if not self.is_dispatched:
            yield self._default_target, self._body
        else:
            return iter(self._body)

    @property
    def targets(self):
        if not self.is_dispatched:
            yield self
        else:
            for (target, body) in self._body:
                yield self.dispatch(target, body)


    def dispatch(self, target, body):

        pp = copy.deepcopy(self)
        pp.branch_name = target

        #dispatch_if = "{0}base_t::dispatcher::has_{1}"
        dispatch_if = "{0}is_eligible_v<base_t, capabilities::{1}>"
        returns = "std::enable_if_t<{condition}, T>"

        def map_requirement(requirement):
            requirement = cleanup(requirement)[0]
            if requirement.startswith("not"):
                requirement = requirement.replace("not", "", 1).strip()
                return dispatch_if.format("!", requirement)
            else:
                return dispatch_if.format("", requirement)

        if isinstance(body, dict): # specific config
            pp.body      = body.get("body", "")
            pp.requires  = body.get("requires", [])
        else:
            pp.body = body
            pp.requires = []

        condition = " && ".join([map_requirement(req) for req in pp.requires])

        pp._prefix = "template<typename T = {type}> {prefix}".format(type=pp.returns, prefix =pp.prefix)
        pp.returns   = returns.format(condition = condition)

        return pp #Function(self._parent, pp.name, pp.__dict__)

    def __str__(self):
        return self.signature

class Constructor(Function):
    def __init__(self, parent, data):
        super(Constructor, self).__init__(parent, "__impl", data)

        self._cons_template       = "{name}({args}) {suffix}"
        self._cons_template_init  = "{prefix} {name}({args}) : {initializer} {suffix}"


        self._initializer   = InitializerList(self, data.get("init", ""))


    @property
    def signature(self):
        assert self.name == "", "constructor must not have a name"

        if self._initializer:
            return self._cons_template_init.format(  prefix     = self._prefix,
                                                    name          = "constexpr __impl",
                                                    args          = self._arguments,
                                                    initializer   = self._initializer,
                                                    suffix        = self._suffix).strip()
        else:
            return self._cons_template.format(   prefix     = self._prefix,
                                                name   = "constexpr __impl",
                                                args   = self._arguments,
                                                suffix = self._suffix).strip()



# class Init:
#     def __init__(self, parent, value):
#         self.parent = parent
#
#         args = value.get("args")
#         body = value.get("body")
#
#         self.value =
#         if type(value) is dict:
#             args = Args(self, value.get("args"))
#             body = value.get("body")
#
#             self.value = "{}({})".format(body, args.invocation())
#         else:
#             self.value = value
#
#     def __repr__(self):
#         return self.value

class InitializerList:
    def __init__(self, parent, data):
        self._parent = parent
        self._initializer = [Initializer(self, i) for i in data]

    def __str__(self):
        return ", ".join(map(str, self._initializer))

class Initializer:
    @dispatch(object, object, dict)
    def __init__(self, parent, data):
        self._parent = parent

        arguments       = ArgumentList(parent, data.get("args", ''))
        body            = data.get("body")

        self._value     = "{}({})".format(body, arguments.invocation)

    @dispatch(object, object, object)
    def __init__(self, parent, data):
        self._parent = parent

        self._value     = data

    def __str__(self):
        return self._value
#
# class Args:
#     def __init__(self, parent, args):
#         self.parent = parent
#
#         if type(args) == dict:
#             raw = args.get("raw")
#             if raw:
#                 self.args = [Arg.raw(self, raw)]
#             else:
#                 _from = args.get("from")
#                 _to = args.get("to")
#                 _type = args.get("type", Arg.default_type)
#
#                 if _from < _to:
#                     ids = range(_from, _to)
#                 else:
#                     ids = reversed(range(_to, _from))
#
#                 self.args = [Arg(self, _type, "arg" + str(a)) for a in ids]
#         else:
#             self.args = [Arg.unpack(self, a) for a in to_list(args)]
#
#     def declaration(self):
#         return ", ".join([a.declaration() for a in self.args])
#
#     def invocation(self):
#         return ", ".join([a.invocation() for a in self.args])
#
#     def __repr__(self):
#         return self.declaration()

class ArgumentList:
    @dispatch(object, object, dict)
    def __init__(self, parent, data):
        self._parent = parent

        raw         = data.get("raw")
        from_, to   = data.get("from"), data.get("to")
        type_       = data.get("type")

        if raw:
            self._args = [Argument(self, type_, raw)]
        elif to < from_ or from_ < 0:
            raise IllegalArgumentError(f"Invalid argument index range from: {from_}, to: {to}. Please check the configuration file.")
        else:
            self._args = [Argument(self, type_, "arg" + str(a)) for a in range(from_, to)]

    @dispatch(object, object, object)
    def __init__(self, parent, data):
        self._parent = parent

        self._args = [Argument(self, "", a) for a in to_list(data)]

    def declaration(self):
        return ", ".join([a.declaration for a in self._args])

    def invocation(self):
        return ", ".join([a.invocation for a in self._args])

    def __repr__(self):
        return self.declaration()

class Argument:
    default_type = "composed_t"
    default_type_invocation = ""  # "".get_value()"

    @dispatch(object, str)
    def __init__(self, parent, value):
        self._parent = parent

        if not value: raise IllegalArgumentError("Value must not be empty or None. Please check the configuration file.")

        # allow patterns like ('typename test::test', 'variable')
        parts = [self.default_type] + value.split()

        # set offset to ignore default_type
        offset = len(parts) > 2
        self._type = " ".join(parts[offset:-1])
        self._name = parts[-1]

    @property
    def declaration(self):
        return " ".join([self._type, self._name])

    @property
    def invocation(self):
        if self._type == self.default_type:
            return self._name + self.default_type_invocation

        return self._name

    def __repr__(self):
        return self.declaration

# class Argument:
#     default_type = "composed_t"
#     #defaul_type = "z{}<base_t::features>"
#     default_type_invocation = ""#"".get_value()"
#
#     def __init__(self, parent, type, name):
#         self.name   = name
#         self.parent = parent
#         self.type   = type
#         #override if in logical module
#         #module = self.parent.parent.parent
#
#         #if isinstance(module, Module) and type == self.default_type:
#         #   if module.name not in ["construction"]:
#         #        self.type = "z{}<base_t::features>".format(module.parent.type)
#
#         #if module.name == "logical":
#         #self.type = "bval<composed_t, mask_t>"
#         #self.type = "b{}<base_t::features>".format(module.parent.type)
#
#
#     def declaration(self):
#         return self.type + " " + self.name if self.type else self.name
#
#     def invocation(self):
#         if self.type == self.default_type:
#             return self.name + self.default_type_invocation
#
#         return self.name
#
#     @classmethod
#     def unpack(cls, parent, value):
#         if type(value) == str:
#             value = value.split()
#
#         # allow patterns like ('typename test::test', 'variable')
#         (t, n) = (" ".join(value[0:-1]), value[-1]) if len(value) > 1 \
#             else (Arg.default_type, value[0])
#
#         return cls(parent, t, n)
#
#     @classmethod
#     def raw(cls, parent, value):
#         return cls(parent, "", value)
#
#     def __repr__(self):
#         return self.declaration()


class FunctionBody:
    @dispatch(Function, dict)
    def __init__(self, parent, data):
        self._parent = parent

        self._instructions = { k: cleanup(v) for (k, v) in data.items() }

    @dispatch(Function, object)
    def __init__(self, parent, data):
        self._parent = parent

        self._instructions = cleanup(data)

    @property
    def instructions(self):
        body = self.instructions

        if len(body) == 1 and body[0].find('(') == -1:
            body[0] = "{}({})".format(body[0], self._parent.args.invocation())

        # print(self.parent.name, body)
        if not self._parent.is_constructor() and body[-1].find("return") == -1\
                and self._parent.returns.find("void") == -1:
            body[-1] = "return " + body[-1]

        return [b + ';' if not b.rstrip().endswith(';') else b for b in body]

    def __repr__(self):
        return "\n".join(self.instructions)

class ValFactory:
    pass


class Type:
    def __init__(self, config, test_config):
        #tconfig                 = config.get("type", {})
        # self.type               = tconfig.get("type")
        # self.branch             = tconfig.get("branch")
        # self.vector_t           = tconfig.get("vector_t")
        # self.mask_t             = tconfig.get("mask_t", self.vector_t)
        # self.scalar_t           = tconfig.get("scalar_t")
        # self.vec_size           = tconfig.get("vec_size")
        # self.alignment          = tconfig.get("alignment")


        #categories = tconfig.get("traits").items() + [('initializer', ['construction', 'boolean_construction'])]

        # self.traits             = Struct(({ category : [ Trait( Util.remove_prefix(name),
        #                                                         is_bval,
        #                                                         Util.type_prefix[is_bval] + self.type,
        #                                                         name,
        #                                                         config["modules"][name])
        #                                                  for (name, is_bval) in [ (name, Util.is_bval(name)) for name in names] ]
        #                                     for (category,names) in categories}))
        #
        # self.initializer    = { (trait.name, trait.is_bval) : Module.make_initializer(self, trait) for trait in traits.initializer }
        # self.modules        = { }
        ##self.test_config        = test_config.get("modules")

        #self.construction       = [Module.make_construction(self, config["modules"], 0, "construction") ]
        #self.booleanconstruction= [Module.make_construction(self, config["modules"], 1, "boolean_construction") ]


        #self.booleanmodules     = { m.name:m for m in [Module.make_module(self, trait, 1, config["modules"][trait]) for trait in self.traits.boolean] }
        #self.internalmodules    = { m.name:m for m in [Module.make_module(self, trait, 0, config["modules"][trait]) for trait in self.traits.internal] }
        #self.modules           =  { m.name:m for m in (list(self.booleanmodules.values()) + list(self.internalmodules.values())) }

        # self.modules           =  { (m.name, m.is_bval):m for m in [Module.make_module(self, trait, config["modules"][trait]) for (trait, is_bval) in
        #                             self.traits.boolean + self.traits.internal }

        
        #self.trait_modules        = [ config["modules"][trait] for (trait, 0) in self.traits.internal + (trait, 1) in self.traits.boolean]
        #self.modules            = { m.name:m for m in [Module.make_module(self, k, v) for (k, v) in config["modules"].items() if k != "construction" and k != "boolean_construction"]}

        self.traits = Traits(self, config.get("type", {}))

        self.modules = { m.name:m for m in [Module(self, name, data) for (name, data) in self.traits.all.items()]}#.boolean + self.traits.internal + self.traits.external]}

    def get_modules(self):
        return list(self.modules.values()) #list(self.traits.initializer) +

    def get_traits(self):
        return [ "{}::impl".format(module) for module in self.traits.external] \
               + [ "{}<impl>::template zimpl".format(self.modules[module, False].mangled_name) for module in self.traits.internal ] \
               + [ "{}<impl>::template zimpl".format(self.modules[module, False].mangled_name) for module in self.traits.initializer ]

    def get_boolean_traits(self):
        print(self.modules)
        return [ "{}::impl".format(module) for module in self.traits.external] \
               + [ "{}<impl>::template bimpl".format(self.modules[module, True].mangled_name) for module in self.traits.boolean ] \
               + [ "{}<impl>::template bimpl".format(self.modules[module, True].mangled_name) for module in self.traits.initializer ]

# class Module:
#     def __init__(self, parent, trait, functions):
#         self.parent         = parent
#         self.is_bval, self.type, self.name, original_name = trait
#         self.functions      = functions
#
#         self.test_config    = parent.test_config and parent.test_config.get(original_name)
#         self.mangling       = bool(0)
#         #print("Building module", self.name)
#
#     @classmethod
#     def make_module(cls, parent, trait):
#         result =  cls(parent, trait, [])
#         result.mangling  = trait.module.get("mangling", bool(0))
#         result.functions = [Func(result, k, v) for k,v in trait.module.items() if k != "mangling"]
#
#         return result
#
#     @classmethod
#     def make_construction(cls, parent, sector):
#         result =  cls(parent, sector, is_bval, [])
#
#         constructors = modules.get(sector, []) or []
#
#
#         #try to add default constructor
#         needs_default_cons = not [i for i,x in enumerate(constructors) if x.get('args') == '' or not x.get('args')]
#         constructors = [ {'args':'','init':''} ] + constructors if needs_default_cons else constructors
#
#         # add implicit copy constructor
#         #constructors += [{ 'args': 'const composed_t& rhs', 'init': 'rhs.value()'}]
#
#         # build constructors
#         result.functions = [Func.make_constructor(result, entry) for entry in constructors]
#
#         return result
#
#     def mangled_name(self):
#         return "{}_{}".format(self.type, self.name)
#
#     def has_tests(self):
#         return any(func.has_tests() for func in self.functions)
#
# class Func:
#
#     func_template       = "{prefix} {returns} {name}({args}) {suffix} noexcept"
#     cons_template       = "{name}({args}) {suffix}"
#     cons_template_init  = "{prefix} {name}({args}) : {initializer} {suffix}"
#
#     default_branch      = "default"
#
#     def __init__(self, parent, name, entries):
#         if type(entries) is str:
#             entries = { "body": entries }
#
#         is_copy = type(entries) is Func # Prototype copy
#
#         self.requires   = entries.requires if is_copy else entries.get("requires", [])
#         self.parent     = entries.parent if is_copy else parent
#         self.name       = entries.name if is_copy else name
#
#         self.mangling   = entries.mangling if is_copy else entries.get("mangling", parent.mangling)
#
#         self.is_member = entries.is_member if is_copy else entries.get("member")
#
#         self.prefix     = entries.prefix if is_copy else entries.get("prefix", "friend") if not self.is_member and not self.name == "" else entries.get("prefix", "")
#         self.suffix     = entries.suffix if is_copy else entries.get("suffix", "const" if self.is_member else "")
#
#         returntype = ("b" if (self.parent.name in ["equatable", "comparable", "logical"]) else "z") + self.parent.parent.type
#         self.returns    = entries.returns if is_copy else entries.get("returns", "{}<base_t::features>".format(returntype))
#
#         self.body = entries.body if is_copy else entries.get("body", "")
#
#         self.branch_name = entries.branch_name if is_copy else "default"
#         self.is_branched= type(self.body) is dict
#
#         assert not self.is_branched or self.default_branch in self.body, "default branch required"
#
#         self.args = entries.args if is_copy else Args(self, entries.get("args", ["one", "other"]))
#         self.inits      = entries.inits if is_copy else Inits(self, entries.get("init", ""))
#
#
#         #override if in comparison or  logical module
#         #if (self.parent.name == "comparison" or self.parent.name == "logical"):
#             #self.returns = "bval<composed_t, mask_t>"
#             #self.returns = "b{}<base_t::features>".format(self.parent.parent.type)
#
#         test       = parent.test_config and parent.test_config.get(self.name)
#
#         if test and type(test) == list and len(test) == 2:
#             self.actual     = test[0].format(type = "z"+parent.parent.type)#+"<>")
#             self.expected   = test[1]
#             self.test = [self.actual, self.expected]
#         else:
#             self.test = None
#
#     def summarized_args(self):
#         args = self.args.declaration()
#         #return textwrap.shorten(self.args, width = 20)
#         return args[:32] + (args[32:] and '..')
#
#     def signature(self):
#         name = self.mangled_name()
#
#         if self.name:
#             return self.func_template.format(prefix     = self.prefix,
#                                              returns    = self.returns,
#                                              name       = name,
#                                              args       = self.args,
#                                              suffix     = self.suffix).strip()
#         elif self.inits:
#             return self.cons_template_init.format(  prefix     = self.prefix,
#                                                     name          = "constexpr __impl",
#                                                     args          = self.args,
#                                                     initializer   = self.inits,
#                                                     suffix        = self.suffix).strip()
#         else:
#             return self.cons_template.format(   prefix     = self.prefix,
#                                                 name   = "constexpr __impl",
#                                                 args   = self.args,
#                                                 suffix = self.suffix).strip()
#
#     def mangled_name(self):
#         if self.mangling:
#             return "{}_{}".format(self.parent.name, self.name)
#
#         return self.name
#
#     def has_tests(self):
#         return self.test != None
#
#     def get_instructions(self):
#         return Body(self, self.body).get_instructions()
#
#     def branch_defs(self):
#         if not self.is_branched:
#             yield self.default_branch, self.body
#         else:
#             return iter(self.body)
#
#     def branches(self):
#         if not self.is_branched:
#             yield self
#         else:
#             for (branch, body) in self.body.items():
#                 yield Func.__make_branch(self, branch, body)
#
#
#     def __repr__(self):
#         return self.signature()
#
#     def is_constructor(self):
#         return not self.name
#
#     @classmethod
#     def make_constructor(cls, parent, entries):
#         return cls(parent, "", entries)
#
#     @classmethod
#     def make_func(cls, parent, name, entries):
#         return cls(parent, name, entries)
#
#     @classmethod
#     def __make_branch(cls, prototype, branch, body):
#
#         pp = copy.deepcopy(prototype)
#         pp.branch_name = branch
#
#         #dispatch_if = "{0}base_t::dispatcher::has_{1}"
#         dispatch_if = "{0}is_eligible_v<base_t, capabilities::{1}>"
#         returns = "std::enable_if_t<{condition}, T>"
#
#         def map_requirement(requirement):
#             requirement = cleanup(requirement)[0]
#             if requirement.startswith("not"):
#                 requirement = requirement.replace("not", "", 1).strip()
#                 return dispatch_if.format("!", requirement)
#             else:
#                 return dispatch_if.format("", requirement)
#
#         if type(body) is dict: # specific config
#             pp.body      = body.get("body", "")
#             pp.requires  = body.get("requires", [])
#         else:
#             pp.body = body
#             pp.requires = []
#
#         condition = " && ".join([map_requirement(req) for req in pp.requires])
#
#         pp.prefix = "template<typename T = {type}> {prefix}".format(type=pp.returns, prefix =pp.prefix)
#         pp.returns   = returns.format(condition = condition)
#
#         return cls(prototype.parent, pp.name, pp)
#
# class Inits:
#     def __init__(self, parent, value):
#         self.parent = parent
#
#         if type(value) == list:
#             self.inits = [Init(self, i) for i in value]
#         else:
#             self.inits = Init(self, value)
#
#
#     def __repr__(self):
#         if type(self.inits) == list:
#             return ", ".join(map(str, self.inits))
#         else:
#             return "base_t({})".format(self.inits)
#
# class Init:
#     def __init__(self, parent, value):
#         self.parent = parent
#
#         if type(value) == dict:
#             args = Args(self, value.get("args"))
#             body = value.get("body")
#
#             self.value = "{}({})".format(body, args.invocation())
#         else:
#             self.value = value
#
#     def __repr__(self):
#         return self.value
#
# class Body:
#     def __init__(self, parent, instructions):
#         self.parent         = parent
#
#         self.instructions   = cleanup(instructions) if not self.parent.is_branched \
#             else {k: cleanup(v) for (k, v) in instructions.items()}
#
#     def get_instructions(self):
#         body = self.instructions
#
#         if len(body) == 1 and body[0].find('(') == -1:
#             body[0] = "{}({})".format(body[0], self.parent.args.invocation())
#         #print(self.parent.name, body)
#         if not self.parent.is_constructor() and body[-1].find("return") == -1 and self.parent.returns.find("void") == -1:
#             body[-1] = "return " + body[-1]
#
#         return [b + ';' if not b.rstrip().endswith(';') else b for b in body]
#
#     def __repr__(self):
#         return "\n".join(self.get_instructions())
#
# class Args:
#     def __init__(self, parent, args):
#         self.parent = parent
#
#         if type(args) == dict:
#             raw = args.get("raw")
#             if raw:
#                 self.args = [Arg.raw(self, raw)]
#             else:
#                 _from = args.get("from")
#                 _to = args.get("to")
#                 _type = args.get("type", Arg.default_type)
#
#                 if _from < _to:
#                     ids = range(_from, _to)
#                 else:
#                     ids = reversed(range(_to, _from))
#
#                 self.args = [Arg(self, _type, "arg" + str(a)) for a in ids]
#         else:
#             self.args = [Arg.unpack(self, a) for a in to_list(args)]
#
#     def declaration(self):
#         return ", ".join([a.declaration() for a in self.args])
#
#     def invocation(self):
#         return ", ".join([a.invocation() for a in self.args])
#
#     def __repr__(self):
#         return self.declaration()
#
# class Arg:
#     default_type = "composed_t"
#     #defaul_type = "z{}<base_t::features>"
#     default_type_invocation = ""#"".get_value()"
#
#     def __init__(self, parent, type, name):
#         self.name   = name
#         self.parent = parent
#         self.type   = type
#         #override if in logical module
#         module = self.parent.parent.parent
#
#         #if isinstance(module, Module) and type == self.default_type:
#         #   if module.name not in ["construction"]:
#         #        self.type = "z{}<base_t::features>".format(module.parent.type)
#
#             #if module.name == "logical":
#                 #self.type = "bval<composed_t, mask_t>"
#                 #self.type = "b{}<base_t::features>".format(module.parent.type)
#
#
#
#     def declaration(self):
#         return self.type + " " + self.name if self.type else self.name
#
#     def invocation(self):
#         if self.type == self.default_type:
#             return self.name + self.default_type_invocation
#
#         return self.name
#
#     @classmethod
#     def unpack(cls, parent, value):
#         if type(value) == str:
#             value = value.split()
#
#         # allow patterns like ('typename test::test', 'variable')
#         (t, n) = (" ".join(value[0:-1]), value[-1]) if len(value) > 1 \
#             else (Arg.default_type, value[0])
#
#         return cls(parent, t, n)
#
#     @classmethod
#     def raw(cls, parent, value):
#         return cls(parent, "", value)
#
#     def __repr__(self):
#         return self.declaration()

def to_list(arg):
    if not arg or isinstance(arg, list):
        return arg
    else:
        return [arg]

def cleanup(strings) :
    return [str.strip(s) for s in to_list(strings)]


class YamlParser(yasha.YamlParser):
    def parse(self, file):
        #print(">>>Parsing template:", file.name)
        with open("codegen/config/type.test.yml", "rb") as f:
            test_functions = yasha.YamlParser().parse(f)

        variables = yasha.YamlParser.parse(self, file)
        return { "type": Type(variables, test_functions)    }