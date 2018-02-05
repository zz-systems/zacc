from unittest import TestCase
from unittest.mock import patch

from codegen.arguments import *

class TestArgumentList(TestCase):
    @patch("codegen.arguments.Initializer")
    def test_creation(self, m):
        with self.assertRaises(IllegalArgumentError):
            obj = ArgumentList(object(), {})

        with self.assertRaises(IllegalArgumentError):
            obj = ArgumentList(object(), { "from" : -1, "to" : -1})


    @patch("codegen.arguments.Initializer")
    def test_declaration(self, m):
        obj = ArgumentList(m, ["a a b", "c d"])
        self.assertEqual(obj.declaration, "a a b, c d")

        obj = ArgumentList(m, { "from" : 0, "to" : 2})
        self.assertEqual(obj.declaration, "Composed arg0, Composed arg1")

        obj = ArgumentList(m, {"from": 0, "to": 2, "type" : "test"})
        self.assertEqual(obj.declaration, "test arg0, test arg1")

        obj = ArgumentList(m, {"from": 0, "to": 2, "type": "test", "prefix" : "asd"})
        self.assertEqual(obj.declaration, "test asd0, test asd1")


    @patch("codegen.arguments.Initializer")
    def test_invocation(self, m):
        obj = ArgumentList(m, "a")
        self.assertEqual(obj.invocation, "a")

        obj = ArgumentList(m, "value")
        self.assertEqual(obj.invocation, "value")

        obj = ArgumentList(m, ["a a b", "c d"])
        self.assertEqual(obj.invocation, "b, d")

        obj = ArgumentList(m, {"from": 0, "to": 2})
        self.assertEqual(obj.invocation, "arg0, arg1")

        obj = ArgumentList(m, {"from": 0, "to": 2, "type": "test"})
        self.assertEqual(obj.invocation, "arg0, arg1")

        obj = ArgumentList(m, {"from": 0, "to": 2, "type": "test", "prefix": "asd"})
        self.assertEqual(obj.invocation, "asd0, asd1")


class TestArgument(TestCase):

    @patch("codegen.arguments.ArgumentList")
    def test_creation(self, m):
        with self.assertRaises(IllegalArgumentError):
            obj = Argument(m, "")

    @patch("codegen.arguments.ArgumentList")
    def test_declaration(self, m):
        obj = Argument(m, "a")
        self.assertEqual(obj.declaration, "Composed a")

        obj = Argument(m, "a", "asdf")
        self.assertEqual(obj.declaration, "asdf a")

        obj = Argument(m, "std::array<typename zval_traits<base_t>::element_t, zval_traits<base_t>::size> value")
        self.assertEqual(obj.declaration, "std::array<typename zval_traits<base_t>::element_t, zval_traits<base_t>::size> value")

    @patch("codegen.arguments.ArgumentList")
    def test_invocation(self, m):
        obj = Argument(m, "a")
        self.assertEqual(obj.invocation, "a")

        obj = Argument(m, "a", "asdf")
        self.assertEqual(obj.invocation, "a")

        obj = Argument(m, "value")
        self.assertEqual(obj.invocation, "value")

class TestInitializerList(TestCase):

    @patch("codegen.functions.Constructor")
    def test_invocation(self, m):
        obj = InitializerList(m, "_mm512_set1_epi8(value)")
        self.assertEqual(obj.invocation, "base_t(_mm512_set1_epi8(value))")

        obj = InitializerList(m, { "args": { "from": 0, "to": 4, "type": "int" }, "body": "_mm_set_epi32" })
        self.assertEqual(obj.invocation, "base_t(_mm_set_epi32(arg0, arg1, arg2, arg3))")

        obj = InitializerList(m, ["_mm512_set1_epi8(value)", { "args": { "from": 0, "to": 4, "type": "int" }, "body": "_mm_set_epi32" }])
        self.assertEqual(obj.invocation, "_mm512_set1_epi8(value), _mm_set_epi32(arg0, arg1, arg2, arg3)")


class TestInitializer(TestCase):
    @patch("codegen.arguments.InitializerList")
    def test_invocation(self, m):
        obj = Initializer(m, "_mm512_set1_epi8(value)")
        self.assertEqual(obj.invocation, "_mm512_set1_epi8(value)")

        obj = Initializer(m, {"args": {"from": 0, "to": 4, "type": "int"}, "body": "_mm_set_epi32"})
        self.assertEqual(obj.invocation, "_mm_set_epi32(arg0, arg1, arg2, arg3)")
