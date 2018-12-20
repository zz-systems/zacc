from abc import ABC, abstractmethod
from typing import Union
import pprint

import copy

from codegen.ast import *

def typename(obj):
    return f"{type(obj)}"

def to_list(arg):
    if not arg or isinstance(arg, list):
        return arg
    else:
        return [arg]

def cleanup(strings) :
    return [str.strip(s) for s in to_list(strings)]

class Renderer:
    def __init__(self, mapping = None):
        self._mapping = mapping

    def render(self, node, params=None):
        #try:
        return self._mapping[type(node)].render(self, node, params)
    #except KeyError:
    #    print(">> MAPPING: ", self._mapping, "key: ", type(node))


class Renderable(ABC):
    @abstractmethod
    def render(self, renderer: Renderer, node: AstNode, params):
        pass


def make_typename(node, ast):
    prefixes = {
        ModuleTypes.DEFAULT: "z",
        ModuleTypes.BOOLEAN: "b",
        ModuleTypes.UNSIGNED: "u",
        ModuleTypes.SHARED: ""
    }

    return f"{prefixes[node.type]}{ast.type.name}"

def remapArgType(module, ast, arg):
    prefixes = {
        ModuleTypes.DEFAULT: "z",
        ModuleTypes.BOOLEAN: "b",
        ModuleTypes.UNSIGNED: "u",
        ModuleTypes.SHARED: ""
    }

    def format(moduleType, typeName):
        return f"{prefixes[moduleType]}{typeName}<Interface::features>"

    arg_map = {
        "Composed": format(module.type, ast.type.name),
        "bval_t": format(ModuleTypes.BOOLEAN, ast.type.name),
        "zval_t": format(ModuleTypes.DEFAULT, ast.type.name),
    }
    print(arg_map.get(arg.type) + "\n")
    return arg_map.get(arg.type) or arg.type


class ModuleMangledNameRenderer(Renderable):
    def render(self, renderer: Renderer, node: ModuleNode, ast):
        return f"{make_typename(node, ast)}_{node.name}"

class UniqueModuleNamesRenderer(Renderable):
    def render(self, renderer: Renderer, node: ModulesNode, params):
        return set([item.name for item in node.modules])

class TraitCompositionRenderer(Renderable):
    def render(self, renderer: Renderer, node: AstRoot, type):

        traits = {
            ModuleTypes.DEFAULT: node.traits.default,
            ModuleTypes.BOOLEAN: node.traits.boolean,
            ModuleTypes.UNSIGNED: node.traits.unsigned,
            ModuleTypes.SHARED: node.traits.shared
        }

        shared_traits   = node.traits.shared
        initializers    = { m.name:renderer.render(m, node) for m in node.modules.initializers if m.type == type }
        modules         = { m.name:renderer.render(m, node) for m in node.modules.modules if m.type == type }

        return [f"{trait}" for trait in shared_traits] + \
               [f"{modules[trait]}::template impl" for trait in traits[type]]# +\
        #[f"{initializer}" for initializer in initializers.values()]

class FunctionSignatureRenderer(Renderable):
    def render(self, renderer, node: FunctionSignatureNode, params):
        module, ast, body = copy.deepcopy(params)
        # type overrides

        args = ", ".join([f"{remapArgType(module, ast, arg)} {arg.name}" for arg in node.arguments])

        overrides = {
            "logical": ModuleTypes.BOOLEAN,
            "equatable": ModuleTypes.BOOLEAN,
            "comparable": ModuleTypes.BOOLEAN
        }

        module.type = overrides.get(module.name, module.type)

        # basic
        prefix = node.prefix or "friend"
        suffix = node.suffix or "const" if prefix.strip().find('friend') == -1 else ""
        return_type = node.return_type or f"{make_typename(module, ast)}<Interface::features>"

        # dispatching
        dispatcher = "{0}has_feature_v<Interface, capabilities::{1}>"

        def map_requirement(requirement):
            requirement = cleanup(requirement)[0]
            if requirement.startswith("not"):
                requirement = requirement.replace("not", "", 1).strip()
                return dispatcher.format("!", requirement)
            else:
                return dispatcher.format("", requirement)

        if body.selector:
            condition = " && ".join([map_requirement(req) for req in body.selector])
            prefix = f"template<typename T = {return_type}> {prefix}"
            return_type = f"std::enable_if_t<{condition}, T>"

        return "{prefix} {returns} {name}({args}) {suffix}".format(
            prefix=prefix,
            returns=return_type,
            name=node.name,
            args=args,
            suffix=suffix)

def render_args_signature(node: FunctionSignatureNode):
    return ", ".join([f"{arg.type}" for arg in node.arguments])

class InitializerBodyRenderer(Renderable):
    def render(self, renderer, node: FunctionBodyNode, params):
        return ""

class FunctionBodyRenderer(Renderable):
    def render(self, renderer, node: FunctionBodyNode, params):
        return renderer.render(node.instructions)

class InstructionsRenderer(Renderable):
    def render(self, renderer, node: InstructionsNode, params):
        body = cleanup(node.body)
        arguments = ", ".join([arg.name for arg in node.arguments])
        is_initializer = (params or {}).get("is_initializer", False)

        if len(body) == 1 and body[0].find('(') == -1 and (not is_initializer or body[0].find(arguments) == -1):
            body[0] = f"{body[0]}({arguments})"

        if len(body) == 0:
            body = ['']

        if is_initializer:
            return body[0]

        if body[-1].find("return") == -1 \
                and (node.return_type or "").find("void") == -1:
            body[-1] = "return " + body[-1]

        return [b + ';' if not b.rstrip().endswith(';') else b for b in body]



class InitializerSignatureRenderer(Renderable):
    def render(self, renderer, node: InitializerSignatureNode, params):
        module, ast, body = copy.deepcopy(params)

        args = ", ".join([f"{remapArgType(module, ast, arg)} {arg.name}" for arg in node.arguments])

        return "{prefix} {name}({args}) : {initializer} {suffix}".format(
            prefix=node.prefix or "constexpr",
            name=f"impl",
            args=args,
            initializer=f"Interface({renderer.render(node.initializer, { 'is_initializer' : True })})",
            suffix=node.suffix or "")

class FloatVerificationRenderer(Renderable):
    def render(self, renderer: Renderer, node: AstRoot, params):
        return "" if node.type.scalar_type == 'float' else "!"

class DoubleVerificationRenderer(Renderable):
    def render(self, renderer: Renderer, node: AstRoot, params):
        return "" if node.type.scalar_type == 'double' else "!"

class FpVerificationRenderer(Renderable):
    def render(self, renderer: Renderer, node: AstRoot, params):
        return "" if node.type.scalar_type == 'double' or node.type.scalar_type == 'float' else "!"

class IntVerificationRenderer(Renderable):
    def render(self, renderer: Renderer, node: AstRoot, params):
        return "!" if node.type.scalar_type == 'double' or node.type.scalar_type == 'float' else ""