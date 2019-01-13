//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2015-2018 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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
#include "system/dispatched_arch.hpp"
#include "util/testing/gtest_ext.hpp"
#include <type_traits>

namespace zacc { namespace test {

    template <typename T>
    class arithmetic_test : public ::testing::Test { };
    TYPED_TEST_CASE_P(arithmetic_test);

    template <typename T>
    class integer_arithmetic_test : public ::testing::Test { };
    TYPED_TEST_CASE_P(integer_arithmetic_test);


    TYPED_TEST_P(arithmetic_test, negate)
    {
        TypeParam value = 5;
        TypeParam actual= -value;

        VASSERT_EQ(actual, -5);
    }

    TYPED_TEST_P(arithmetic_test, add)
    {
        TypeParam value = 5;
        TypeParam actual= value + 10;

        VASSERT_EQ(actual, 15);
    }

    TYPED_TEST_P(arithmetic_test, subtract)
    {
        TypeParam value = 5;
        TypeParam actual= value - 10.0;

        VASSERT_EQ(actual, -5);
    }

    TYPED_TEST_P(arithmetic_test, multiply)
    {
        TypeParam value = 5;
        TypeParam actual= value * 10;

        VASSERT_EQ(actual, 50);
    }

    TYPED_TEST_P(arithmetic_test, divide)
    {
        TypeParam value = 50;
        TypeParam actual= value / 10;

        VASSERT_EQ(actual, 5);
    }

    TYPED_TEST_P(integer_arithmetic_test, modulo)
    {
        TypeParam value = 50;
        TypeParam actual= value % 7;

        VASSERT_EQ(actual, 1);
    }

    REGISTER_TYPED_TEST_CASE_P(arithmetic_test,
                               negate,
                               add,
                               subtract,
                               multiply,
                               divide);

    typedef ::testing::Types<zfloat, zdouble, zint8, zint16, zint32> arithmetic_test_types;

    INSTANTIATE_TYPED_TEST_CASE_P(zacc, arithmetic_test, arithmetic_test_types);


    REGISTER_TYPED_TEST_CASE_P(integer_arithmetic_test, modulo);

    typedef ::testing::Types<zint8, zint16, zint32> integer_arithmetic_test_types;

    INSTANTIATE_TYPED_TEST_CASE_P(zacc, integer_arithmetic_test, integer_arithmetic_test_types);

}}