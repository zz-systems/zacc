from pprint import pprint
from unittest import TestCase
from unittest.mock import patch

from codegen.functions import *

class TestFunctionBody(TestCase):
    @patch("codegen.modules.Module")
    def test_declaration(self, m):
        pass

    @patch("codegen.modules.Module")
    def test_invocation(self, m):
       pass

class TestFunction(TestCase):
    @patch("codegen.modules.Module")
    def test_creation(self, m):
        m.name = "test"

        with self.assertRaises(IllegalArgumentError):
           obj = Function(m, "testfunc", { "body": { "test": "_mm512_and_epi32" } })

        obj = Function(m, "testfunc", { "body": { "default": "_mm512_and_epi32" } })
        self.assertFalse(obj.is_constructor)

    @patch("codegen.modules.Module")
    def test_name(self, m):
        m.name = "test"
        m.mangling = False

        obj = Function(m, "testfunc", "_mm512_and_epi32")
        self.assertEqual(obj.name, "testfunc")
        self.assertEqual(obj.mangled_name, "testfunc")

        obj = Function(m, "testfunc", { "mangling":True, "body": "_mm512_and_epi32" })
        self.assertEqual(obj.name, "testfunc")
        self.assertEqual(obj.mangled_name, "test_testfunc")

    @patch("codegen.modules.Module")
    def test_membership(self, m):
        m.name = "test"
        m.mangling = False

        obj = Function(m, "testfunc", {"member": False, "body": "_mm512_and_epi32"})
        self.assertFalse(obj.is_member)

        obj = Function(m, "testfunc", {"member": True, "body": "_mm512_and_epi32"})
        self.assertTrue(obj.is_member)

    @patch("codegen.modules.Module")
    def test_arguments(self, m):
        m.name = "test"

        obj = Function(m, "testfunc", "_mm512_and_epi32")
        self.assertEqual(obj._arguments.declaration, "Composed one, Composed other")

        obj = Function(m, "testfunc", { "args":["multiplicand", "multiplier", "addendum"], "body": "_mm512_and_epi32" })
        self.assertEqual(obj._arguments.declaration, "Composed multiplicand, Composed multiplier, Composed addendum")

    @patch("codegen.modules.Module")
    def test_instructions(self, m):
        m.name = "test"

        obj = Function(m, "testfunc", "_mm512_and_epi32")
        self.assertEqual(obj.instructions, ["return _mm512_and_epi32(one, other);"])

        obj = Function(m, "testfunc", "_mm_cmpeq_epi32(one, _mm_setzero_si128());")
        self.assertEqual(obj.instructions, ["return _mm_cmpeq_epi32(one, _mm_setzero_si128());"])

        obj = Function(m, "testfunc", { "body" : [

            "auto zero = _mm_setzero_si128();",
            "auto _1  = _mm_srli_epi32(_mm_cmpeq_epi32(zero, zero), 31);",
            "auto fi = vtrunc(one);",
            "vsel(vgt(fi, one), vsub(fi, _1), fi);"

        ]})

        self.assertEqual(obj.instructions, [

            "auto zero = _mm_setzero_si128();",
            "auto _1  = _mm_srli_epi32(_mm_cmpeq_epi32(zero, zero), 31);",
            "auto fi = vtrunc(one);",
            "return vsel(vgt(fi, one), vsub(fi, _1), fi);"

        ])

    @patch("codegen.modules.Module")
    def test_dispatch(self, m):
        m.name = "test"

        obj = Function(m, "testfunc",
                       {
                           "args": ["multiplicand", "multiplier", "addendum"],
                           "body": {
                               "fma": {
                                   "requires": ["FMA3"],
                                    "body": "_mm_fmsub_ps(multiplicand, multiplier, addendum)" },
                                "default": {
                                    "requires": ["not FMA3"],
                                    "body": "vsub(vmul(multiplicand, multiplier), addendum)"
                                 }
                            }
                       })

        self.assertTrue(obj.is_dispatched)
        self.assertGreater(len(list(obj.target_definitions)), 1)

        self.assertEqual([target.instructions for target in obj.targets],
                         [["return _mm_fmsub_ps(multiplicand, multiplier, addendum);"], ["return vsub(vmul(multiplicand, multiplier), addendum);"]])

        self.assertEqual(obj.arguments.declaration,
                         "Composed multiplicand, Composed multiplier, Composed addendum")



class TestConstructor(TestCase):
    @patch("codegen.modules.Module")
    def test_creation(self, m):
        m.name = "test"

        #with self.assertRaises(IllegalArgumentError):
        #    obj = Constructor(m, {"args": "value", "inits" : "value"})

        obj = Constructor(m, {"args": "value", "init" : "value"})
        self.assertTrue(obj.is_constructor)


    @patch("codegen.functions.Function")
    def test_invocation(self, m):
        obj = Constructor(m, {"args": "value", "init": "value"})
        self.assertEquals(obj.initializer.invocation, "base_t(value)")

        obj = Constructor(m, {"args": "", "init": ""})
        self.assertEquals(obj.initializer.invocation, "base_t()")
