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
        class generic_math_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(generic_math_test);

        template <typename T>
        class _32bit_math_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(_32bit_math_test);

        template <typename T>
        class float_math_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(float_math_test);


        TYPED_TEST_P(generic_math_test, abs)
        {
            TypeParam value = 5;
            TypeParam actual= (-value).abs();

            VASSERT_EQ(actual, 5);
        }

        TYPED_TEST_P(generic_math_test, min)
        {
            TypeParam value = 5;
            TypeParam actual= value.min(2);

            VASSERT_EQ(actual, 2);
        }

        TYPED_TEST_P(generic_math_test, max)
        {
            TypeParam value = 5;
            TypeParam actual= value.max(2);

            VASSERT_EQ(actual, 5);
        }

        TYPED_TEST_P(generic_math_test, clamp)
        {
            TypeParam value = 5;
            TypeParam actual= value.clamp(2, 6);

            VASSERT_EQ(actual, 5);

            actual= value.clamp(2, 4);

            VASSERT_EQ(actual, 4);

            actual= value.clamp(6, 8);

            VASSERT_EQ(actual, 6);
        }

        TYPED_TEST_P(_32bit_math_test, sqrt)
        {
            TypeParam value = 25;
            TypeParam actual= value.sqrt();

            VASSERT_EQ(actual, 5);
        }

        TYPED_TEST_P(float_math_test, rcp)
        {
            TypeParam value = 5;
            TypeParam actual= value.rcp();

            VASSERT_EQ(actual, 0.2);
        }

        TYPED_TEST_P(float_math_test, trunc)
        {
            TypeParam value = 5.5;
            TypeParam actual= value.trunc();

            VASSERT_EQ(actual, 5);
        }

        TYPED_TEST_P(float_math_test, floor)
        {
            TypeParam value = 5.5;
            TypeParam actual= value.trunc();

            VASSERT_EQ(actual, 5);
        }

        TYPED_TEST_P(float_math_test, ceil)
        {
            TypeParam value = 5.5;
            TypeParam actual= value.trunc();

            VASSERT_EQ(actual, 6);
        }

        TYPED_TEST_P(float_math_test, round)
        {
            TypeParam value = 5.4;
            TypeParam actual= value.round();

            VASSERT_EQ(actual, 5);

            value = 5.6;
            actual= value.round();

            VASSERT_EQ(actual, 6);
        }


        REGISTER_TYPED_TEST_CASE_P(generic_math_test,
                                   abs,
                                   min,
                                   max,
                                   clamp);

        typedef ::testing::Types<zfloat, zdouble, zint8, zint16, zint32> generic_math_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, generic_math_test, generic_math_test_types);

        REGISTER_TYPED_TEST_CASE_P(_32bit_math_test,
                                   sqrt);

        typedef ::testing::Types<zfloat, zdouble, zint32> _32bit_math_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, _32bit_math_test, _32bit_math_test_types);


        REGISTER_TYPED_TEST_CASE_P(float_math_test,
                                   rcp,
                                   trunc,
                                   floor,
                                   ceil,
                                   round);

        typedef ::testing::Types<zfloat32, zfloat64> float_math_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, float_math_test, float_math_test_types);

    }}