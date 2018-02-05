from unittest import TestCase
from unittest.mock import patch
import yaml
import pprint

from codegen.lexer import LexerV1
from codegen.parser import Parser

class TestParser(TestCase):
    def test_lex(self):
        with open("int32.hpp.yml", 'r') as stream:
            try:
                pprint.pprint(Parser(LexerV1()).parse(yaml.load(stream)))
            except yaml.YAMLError as exc:
                print(exc)
