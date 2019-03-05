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

#include <gtest/gtest.h>
#include <zacc/system/dispatched_arch.hpp>
#include <gtest_extensions.hpp>
#include <type_traits>

namespace zacc { namespace test {

        template <typename T>
        class comparison_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(comparison_test);


        TYPED_TEST_P(comparison_test, equals)
        {
            TypeParam value = 5;

            VASSERT_EQ(value == 4, false);
            VASSERT_EQ(value == 5, true);
            VASSERT_EQ(value == 6, false);
        }

        TYPED_TEST_P(comparison_test, not_equals)
        {
            TypeParam value = 5;

            VASSERT_EQ(value != 4, true);
            VASSERT_EQ(value != 5, false);
            VASSERT_EQ(value != 6, true);
        }

        TYPED_TEST_P(comparison_test, greater_than)
        {
            TypeParam value = 5;

            VASSERT_EQ(value > 4, true);
            VASSERT_EQ(value > 5, false);
            VASSERT_EQ(value > 6, false);
        }

        TYPED_TEST_P(comparison_test, greater_than_equal)
        {
            TypeParam value = 5;

            VASSERT_EQ(value >= 4, true);
            VASSERT_EQ(value >= 5, true);
            VASSERT_EQ(value >= 6, false);
        }

        TYPED_TEST_P(comparison_test, less_than)
        {
            TypeParam value = 5;

            VASSERT_EQ(value < 4, false);
            VASSERT_EQ(value < 5, false);
            VASSERT_EQ(value < 6, true);
        }

        TYPED_TEST_P(comparison_test, less_than_equal)
        {
            TypeParam value = 5;

            VASSERT_EQ(value <= 4, false);
            VASSERT_EQ(value <= 5, true);
            VASSERT_EQ(value <= 6, true);
        }


        REGISTER_TYPED_TEST_CASE_P(comparison_test,
                                   equals,
                                   not_equals,
                                   greater_than,
                                   greater_than_equal,
                                   less_than,
                                   less_than_equal);

        typedef ::testing::Types<zfloat, zdouble, zint8, zint16, zint32> comparison_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, comparison_test, comparison_test_types);

    }}