from unittest import TestCase
from unittest.mock import patch
import yaml
import pprint

from codegen.lexer import LexerV1

class TestLexer(TestCase):
    def test_lex(self):
        with open("int32.hpp.yml", 'r') as stream:
            try:
                pprint.pprint(dict(LexerV1().lex(yaml.load(stream))))
            except yaml.YAMLError as exc:
                print(exc)
