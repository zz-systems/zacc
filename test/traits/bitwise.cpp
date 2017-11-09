//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------------

#include "gtest/gtest.h"
#include "system/branch.hpp"
#include "util/testing/gtest_ext.hpp"
#include <type_traits>

namespace zacc { namespace test {

        template <typename T>
        class bitwise_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(bitwise_test);

        template <typename T>
        class float_bitwise_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(float_bitwise_test);

        template <typename T>
        class double_bitwise_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(double_bitwise_test);


        TYPED_TEST_P(bitwise_test, negate)
        {
            TypeParam value = 5;
            TypeParam actual= ~value;

            VASSERT_EQ(actual, ~5);
        }

        TYPED_TEST_P(bitwise_test, or_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value | 10;

            VASSERT_EQ(actual, 5 | 10);
        }

        TYPED_TEST_P(bitwise_test, and_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value & 0;

            VASSERT_EQ(actual, 0);
        }

        TYPED_TEST_P(bitwise_test, xor_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value ^ 10;

            VASSERT_EQ(actual, 5 ^ 10);
        }

        TYPED_TEST_P(float_bitwise_test, negate)
        {
            TypeParam value = 5;
            TypeParam actual= ~value;

            twiddler<float> expected;
            expected.f = 5;
            expected.i = ~expected.i;

            VASSERT_EQ(actual, expected.f);
        }

        TYPED_TEST_P(float_bitwise_test, or_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value | 10;

            twiddler<float> expected;
            expected.f = 5;
            expected.i |= twiddler<float> { .f = 10 }.i;

            VASSERT_EQ(actual, expected.f);
        }

        TYPED_TEST_P(float_bitwise_test, and_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value & 0;

            twiddler<float> expected;
            expected.f = 5;
            expected.i &= twiddler<float> { .f = 0 }.i;

            VASSERT_EQ(actual, expected.f);
        }

        TYPED_TEST_P(float_bitwise_test, xor_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value ^ 121;

            std::cerr << "kebab: " << bitsof(10.0f) << std::endl;

            twiddler<float> expected;
            expected.f = 5;
            expected.i ^= twiddler<float> { .f = 121 }.i;

            VASSERT_EQ(actual, expected.f);
        }

        TYPED_TEST_P(double_bitwise_test, negate)
        {
            TypeParam value = 5;
            TypeParam actual= ~value;

            double expected;

            bitsof(expected) = ~bitsof(5.0);

            VASSERT_EQ(actual, expected);
        }

        TYPED_TEST_P(double_bitwise_test, or_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value | 10;

            twiddler<double> expected;
            expected.f = 5;

            std::cerr << "dürüm " << twiddler<float> { .i = (twiddler<float> { .f = 5 }.i | twiddler<float> { .f = 10 }.i) }.f << std::endl;
            std::cerr << "dürüm " << twiddler<double> { .i = (twiddler<double> { .f = 5 }.i | twiddler<double> { .f = 10 }.i) }.f << std::endl;

            expected.i |= twiddler<double> { .f = 10 }.i;

            std::cerr << 5 << " | " << 10 << " = " << expected.f << "; " << twiddler<double> { .f = 10 }.i  << std::endl;

            VASSERT_EQ(actual, expected.f);
        }

        TYPED_TEST_P(double_bitwise_test, and_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value & 0;

            twiddler<double> expected;
            expected.f = 5;
            expected.i &= twiddler<double> { .f = 0 }.i;

            VASSERT_EQ(actual, expected.f);
        }

        TYPED_TEST_P(double_bitwise_test, xor_operation)
        {
            TypeParam value = 5;
            TypeParam actual= value ^ 10;

            twiddler<double> expected;
            expected.f = 5;
            expected.i ^= twiddler<double> { .f = 10 }.i;

            VASSERT_EQ(actual, expected.f);
        }

        REGISTER_TYPED_TEST_CASE_P(bitwise_test,
                                   negate,
                                   or_operation,
                                   and_operation,
                                   xor_operation);

        typedef ::testing::Types<zint8, zint16, zint32> bitwise_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, bitwise_test, bitwise_test_types);

        REGISTER_TYPED_TEST_CASE_P(float_bitwise_test,
                                   negate,
                                   or_operation,
                                   and_operation,
                                   xor_operation);

        typedef ::testing::Types<zfloat> float_bitwise_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, float_bitwise_test, float_bitwise_test_types);

        REGISTER_TYPED_TEST_CASE_P(double_bitwise_test,
                                   negate,
                                   or_operation,
                                   and_operation,
                                   xor_operation);

        typedef ::testing::Types<zdouble> double_bitwise_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, double_bitwise_test, double_bitwise_test_types);

    }}