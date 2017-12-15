from codegen.arguments import *


class FunctionResources(Context):

    @property
    def prefix(self):
        return filter2(self.context, [("template<typename T = {type}>", lambda x: x.is_dispatched),
                                       "inline",
                                       "constexpr",
                                       ("friend", lambda x: not x.is_constructor)])

    @property
    def suffix(self):
        return filter2(self.context, [("const", lambda x: not x.is_member), "noexcept"])

    @property
    def function_template(self):
        return "{prefix} {returns} {name}({args}) {suffix}"

    def function_declaration(self, **kwargs):
        return "{prefix} {returns} {name}({args}) {suffix}".format(**kwargs)

    @property
    def constructor_name(self):
        return "__impl"


class Function(NameMangler):
    def __init__(self, context, name, data):

        if isinstance(data, str):
            data = { "body" : data }

        super().__init__(context=context, name=name, prefix=context.name, data=data)


        self._resources = FunctionResources(context=self)

        self._body                  = data.get("body", "")
        self._default_target        = "default"


        self._requires      = data.get("requires", [])
        self._is_member     = data.get("member", False)

        self._prefix     = data.get("prefix", " ".join(self._resources.prefix))
        self._suffix     = data.get("suffix", " ".join(self._resources.suffix))

        self._returns    = data.get("returns", "{}<base_t::features>".format(context.return_type))


        if self.is_dispatched and self._default_target not in self._body:
            raise IllegalArgumentError("Default target required")

        self._arguments     = ArgumentList(self, data.get("args", ["one", "other"]))



        test       = context.test_config and context.test_config.get(self.name)

        if isinstance(test, list) and len(test) == 2:
            self.actual     = test[0].format(type = "z"+context.context.type)#+"<>")
            self.expected   = test[1]
            self.test = [self.actual, self.expected]
        else:
            self.test = None


    @property
    def name(self):
        return self._name

    @property
    def preamble(self):
        return self._prefix

    @property
    def body(self):
        return self._body

    @property
    def is_constructor(self):
        return self._is_member and self.name == ""

    @property
    def is_member(self):
        return self._is_member and self.name and self.name != ""

    @property
    def is_dispatched(self):
        return isinstance(self._body, dict)


    @property
    def signature(self):
        assert self._name != "", "Function must have a name"

        return self._resources.function_declaration(prefix     = self._prefix,
                                             returns    = self._returns,
                                             name       = self.mangled_name,
                                             args       = self.arguments,
                                             suffix     = self._suffix).strip()
    @property
    def arguments(self):
        return self._arguments

    @property
    def return_statement(self):
        return self._returns

    @return_statement.setter
    def return_statement(self, value):
        self._returns = value

    @property
    def has_tests(self):
        return self.test is not None

    @property
    def instructions(self):
        return FunctionBody(self, self._body).instructions


    @property
    def target_definitions(self):
        if not self.is_dispatched:
            yield self._default_target, self._body
        else:
            yield from self._body

    @property
    def targets(self):
        if not self.is_dispatched:
            yield self
        else:
            for (target, body) in self._body.items():
                yield self.dispatch(target, body)


    def dispatch(self, target, body):
        #dispatch_if = "{0}base_t::dispatcher::has_{1}"
        dispatch_if = "{0}is_eligible_v<base_t, capabilities::{1}>"


        def map_requirement(requirement):
            requirement = cleanup(requirement)[0]
            if requirement.startswith("not"):
                requirement = requirement.replace("not", "", 1).strip()
                return dispatch_if.format("!", requirement)
            else:
                return dispatch_if.format("", requirement)

        if isinstance(body, dict): # specific config
            new_body      = body.get("body", "")
            requires  = body.get("requires", [])
        else:
            new_body = body
            requires = []

        condition = " && ".join([map_requirement(req) for req in requires])

        prefix = "template<typename T = {type}> {prefix}".format(type=self.return_statement, prefix =self.preamble)
        returns = "std::enable_if_t<{condition}, T>".format(condition = condition)

        return Function(context=self.context, name=self.name, data={"args": self.data.get("args"), "prefix": prefix, "returns":returns, "body" : new_body })

    def __str__(self):
        return self.signature

class Constructor(Function):
    def __init__(self, context, data):
        super().__init__(context, "", data)

        self._is_member             = True
        self._cons_template       = "{name}({args}) {suffix}"
        self._cons_template_init  = "{prefix} {name}({args}) : {initializer} {suffix}"


        self._initializer   = InitializerList(self, data.get("init", ""))

    @property
    def initializer(self):
        return self._initializer

    @property
    def signature(self):
        assert self.name == "", "constructor must not have a name"

        if self._initializer:
            return self._cons_template_init.format(  prefix     = self._prefix,
                                                    name          = "__impl",
                                                    args          = self._arguments,
                                                    initializer   = self._initializer,
                                                    suffix        = self._suffix).strip()
        else:
            return self._cons_template.format(   prefix     = self._prefix,
                                                name   = "__impl",
                                                args   = self._arguments,
                                                suffix = self._suffix).strip()


class FunctionBody(Context):
    @dispatch(Function, dict)
    def __init__(self, context : Function, data):
        super().__init__(context, data)

        self._instructions = { k: cleanup(v) for (k, v) in data.items() }

    @dispatch(Function, object)
    def __init__(self, context, data):
        super().__init__(context, data)

        self._instructions = cleanup(data)

    @property
    def instructions(self):
        body = self._instructions

        if len(body) == 1 and body[0].find('(') == -1:
            body[0] = "{}({})".format(body[0], self._context.arguments.invocation)

        # print(self.parent.name, body)
        if not self._context.is_constructor and body[-1].find("return") == -1\
                and self._context.return_statement.find("void") == -1:
            body[-1] = "return " + body[-1]

        return [b + ';' if not b.rstrip().endswith(';') else b for b in body]

    def __str__(self):
        return "\n".join(self.instructions)
