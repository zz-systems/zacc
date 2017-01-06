import yasha
from enum import Enum

class Struct:
    def __init__(self, entries):
        self.__dict__.update(entries)

class Type:
    def __init__(self, config):
        tconfig                 = config.get("type")
        self.type               = tconfig.get("type")
        self.branch             = tconfig.get("branch")
        self.vector_t           = tconfig.get("vector_t")
        self.scalar_t           = tconfig.get("scalar_t")
        self.vec_size           = tconfig.get("vec_size")
        self.alignment          = tconfig.get("alignment")

        self.traits             = Struct(tconfig.get("traits"))

        self.construction       = [Module.make_construction(self, config["modules"], "construction") ]
        self.modules            = { m.name:m for m in [Module.make_module(self, k, v) for (k, v) in config["modules"].items() if k != "construction" ]}

    def get_modules(self):
        return self.construction + list(self.modules.values())

    def get_traits(self):
        return self.traits.external \
               + [ "{}<z{}>".format(self.modules[module].mangled_name(), self.type) for module in self.traits.internal ] \
               + [ "{}<z{}>".format(self.construction[0].mangled_name(), self.type) ]

class Module:
    def __init__(self, parent, name, functions):
        self.parent     = parent
        self.type       = parent.type
        self.functions  = functions
        self.name       = name

        #print("Building module", self.name)

    @classmethod
    def make_module(cls, parent, name, entries):
        result =  cls(parent, name, [])
        result.functions = [Func(result, k, v) for k,v in entries.items()]

        return result

    @classmethod
    def make_construction(cls, parent, modules, sector):
        result =  cls(parent, sector, [])
        result.functions = [Func.make_constructor(result, entry) for entry in modules.get(sector, []) or []]

        return result

    def mangled_name(self):
        return "{}_{}".format(self.parent.type, self.name)

class Func:

    func_template       = "{prefix} {returns} {name}({args}) {suffix}"
    cons_template       = "{name}({args}) {suffix}"
    cons_template_init  = "{name}({args}) : {initializer} {suffix}"

    default_branch      = "default"

    def __init__(self, parent, name, entries):
        if type(entries) is str:
            entries = { "body": entries }

        self.args       = Args(entries.get("args", ["one", "other"]))

        self.body       = entries.get("body", "")
        self.is_branched= type(self.body) is dict

        assert not self.is_branched or self.default_branch in self.body, "default branch required"

        self.inits      = Inits(entries.get("init", ""))
        self.requires   = entries.get("requires", [])
        self.parent     = parent
        self.name       = name

        self.mangling   = entries.get("mangling", bool(1))

        is_member = entries.get("member")

        self.prefix     = "friend" if not is_member else ""
        self.suffix     = entries.get("suffix", "const" if is_member else "")
        self.returns    = entries.get("returns", "composed_t")

    def signature(self):
        name = self.name

        if self.mangling:
            name = "{}_{}".format(self.parent.name, name)

        if self.name:
            return self.func_template.format(prefix     = self.prefix,
                                            returns    = self.returns,
                                            name       = name,
                                            args       = self.args,
                                            suffix     = self.suffix).strip()
        elif self.inits:
            return self.cons_template_init.format(  name          = "__impl",
                                                    args          = self.args,
                                                    initializer   = self.inits,
                                                    suffix        = self.suffix).strip()
        else:
            return self.cons_template.format(   name   = "__impl",
                                                args   = self.args,
                                                suffix = self.suffix).strip()

    def get_instructions(self):
        return Body(self, self.body).get_instructions();

    def branch_defs(self):
        if not self.is_branched:
            yield self.default_branch, self.body
        else:
            return iter(self.body)

    def branches(self):
        if not self.is_branched:
            yield self
        else:
            for (branch, body) in self.body.items():
                yield Func.__make_branch(self, branch, body)

    def __repr__(self):
        return self.signature()

    def is_constructor(self):
        return not self.name

    @classmethod
    def make_constructor(cls, parent, entries):
        return cls(parent, "", entries)

    @classmethod
    def make_func(cls, parent, name, entries):
        return cls(parent, name, entries)

    @classmethod
    def __make_branch(cls, prototype, branch, body):
        dispatch_if = "{0}dispatcher::has_{1}"
        returns = "std::enable_if_t<{condition}, {type}>"

        def map_requirement(requirement):
            requirement = cleanup(requirement)
            if requirement.startswith("not"):
                requirement = requirement.replace("not", "", 1).strip()
                return dispatch_if.format("!", requirement)
            else:
                return dispatch_if.format("", requirement)

        prototype.body      = body
        prototype.requires  = body.get("requires", [])

        condition = " && ".join([map_requirement(req) for req in prototype.requires])

        prototype.returns   = returns.format(condition, type=prototype.returns)

        return cls(prototype.parent, prototype.name, prototype)

class Inits:
    def __init__(self, value):
        if type(value) == list:
            self.inits = [Init(i) for i in value]
        else:
            self.inits = Init(value)


    def __repr__(self):
        if type(self.inits) == list:
            return ", ".join(map(str, self.inits))
        else:
            return "base_t({})".format(self.inits)

class Init:
    def __init__(self, value):
        if type(value) == dict:
            args = Args(value.get("args"))
            body = value.get("body")

            self.value = "{}({})".format(body, args.invocation())
        else:
            self.value = value

    def __repr__(self):
        return self.value

class Body:
    def __init__(self, parent, instructions):
        self.parent         = parent

        self.instructions   = cleanup(instructions) if not self.parent.is_branched \
            else {k: cleanup(v) for (k, v) in instructions.items()}

    def get_instructions(self):
        body = self.instructions

        if len(body) == 1 and body[0].find('(') == -1:
            body[0] = "{}({})".format(body[0], self.parent.args.invocation())
        #print(self.parent.name, body)
        if not self.parent.is_constructor() and body[-1].find("return") == -1:
            body[-1] = "return " + body[-1]

        return [b + ';' if not b.rstrip().endswith(';') else b for b in body]

    def __repr__(self):
        return "\n".join(self.get_instructions())

class Args:
    def __init__(self, args):
        if type(args) == dict:
            raw = args.get("raw")
            if raw:
                self.args = [Arg.raw(self, raw)]
            else:
                _from = args.get("from")
                _to = args.get("to")
                _type = args.get("type", Arg.default_type)

                if _from < _to:
                    ids = range(_from, _to)
                else:
                    ids = reversed(range(_to, _from))

                self.args = [Arg(self, _type, "arg" + str(a)) for a in ids]
        else:
            self.args = [Arg.unpack(self, a) for a in to_list(args)]

    def declaration(self):
        return ", ".join([a.declaration() for a in self.args])

    def invocation(self):
        return ", ".join([a.invocation() for a in self.args])

    def __repr__(self):
        return self.declaration()

class Arg:
    default_type = "composed_t"
    default_type_invocation = ".get_value()"

    def __init__(self, parent, type, name):
        self.type   = type
        self.name   = name
        self.parent = parent


    def declaration(self):
        return self.type + " " + self.name if self.type else self.name

    def invocation(self):
        if self.type == self.default_type:
            return self.name + self.default_type_invocation

        return self.name

    @classmethod
    def unpack(cls, parent, value):
        if type(value) == str:
            value = value.split()

        (t, n) = (value[0], value[1]) if len(value) > 1 \
            else (Arg.default_type, value[0])

        return cls(parent, t, n)

    @classmethod
    def raw(cls, parent, value):
        return cls(parent, "", value)

    def __repr__(self):
        return self.declaration()

def to_list(arg):
    if not arg or type(arg) is list:
        return arg
    else:
        return [arg]

def cleanup(strings) :
    return [str.strip(s) for s in to_list(strings)]


class YamlParser(yasha.YamlParser):
    def parse(self, file):
        #print(">>>Parsing template:", file.name)
        variables = yasha.YamlParser.parse(self, file)
        return { "type": Type(variables)    }