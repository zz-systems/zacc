import yasha
import os, sys


print(">>>Current PATH:", os.getcwd())
sys.path.append("codegen")
from codegen.lexer import LexerV1
from codegen.parser import *
from codegen.renderer import *
from codegen.ast import ModuleTypes

class Modules:
    _renderer = Renderer({
        ModuleNode : ModuleMangledNameRenderer()
    })

    def render(cls, node, params=None):
        return Modules._renderer.render(node, params)


class Functions:
    _renderer = Renderer({
        FunctionSignatureNode : FunctionSignatureRenderer(),
        FunctionBodyNode : FunctionBodyRenderer(),
        InitializerSignatureNode: InitializerSignatureRenderer(),
        InitializerBodyNode: InitializerBodyRenderer(),
        InstructionsNode: InstructionsRenderer()
    })

    def render(cls, node, params=None):
        return Functions._renderer.render(node, params)


class Traits:
    _renderer = Renderer({
        AstRoot : TraitCompositionRenderer(),
        ModuleNode: ModuleMangledNameRenderer(),
        ModulesNode: UniqueModuleNamesRenderer()
    })

    def render(cls, node, params=None):
        return Traits._renderer.render(node, params)


class Verifications:

    def render_float_condition(cls, node):
        return FloatVerificationRenderer().render(None, node, None)

    def render_double_condition(cls, node):
        return DoubleVerificationRenderer().render(None, node, None)

    def render_fp_condition(cls, node):
        return FpVerificationRenderer().render(None, node, None)

    def render_int_condition(cls, node):
        return IntVerificationRenderer().render(None, node, None)

class Parsers:
    @classmethod
    def parse(cls, data):
        return Parser(LexerV1()).parse(data)

class YamlParser(yasha.YamlParser):
    def parse(self, file):
        #print(">>>Parsing template:", file.name)
        #with open("codegen/config/type.test.yml", "rb") as f:
        #    test_functions = yasha.YamlParser().parse(f)

        data = yasha.YamlParser.parse(self, file)
        ast = Parsers.parse(data)

        return {
            "ast"           : Parsers.parse(data),
            "Modules"       : Modules(),
            "Functions"     : Functions(),
            "Traits"        : Traits(),
            "Verifications" : Verifications(),
            "ModuleTypes"   : ModuleTypes
        }