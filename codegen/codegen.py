import yasha
from codegen.parser import Parsers
from codegen.renderer import *

class YamlParser(yasha.YamlParser):
    def parse(self, file):
        #print(">>>Parsing template:", file.name)
        #with open("codegen/config/type.test.yml", "rb") as f:
        #    test_functions = yasha.YamlParser().parse(f)

        data = yasha.YamlParser.parse(self, file)
        ast = Parsers.parse(data)

        return {
            "ast"           : Parsers.parse(data),
            "modules"       : Modules(),
            "Functions"     : Functions(),
            "Traits"        : Traits(),
            "Verifications" : Verifications()
        }