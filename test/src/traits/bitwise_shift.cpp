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
#include <gtest.extensions.hpp>
#include <type_traits>

namespace zacc { namespace test {

        template <typename T>
        class bitwise_shift_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(bitwise_shift_test);


        TYPED_TEST_P(bitwise_shift_test, shift_left_immediate)
        {
            TypeParam value = 5;
            TypeParam actual= value << 5;

            VASSERT_EQ(actual, 5 << 5);
        }

        TYPED_TEST_P(bitwise_shift_test, shift_right_immediate)
        {
            TypeParam value = 1024;
            TypeParam actual= value >> 3;

            VASSERT_EQ(actual, 1024 >> 3);
        }

        TYPED_TEST_P(bitwise_shift_test, shift_left_byval)
        {
        }

        TYPED_TEST_P(bitwise_shift_test, shift_right_byval)
        {
        }


        REGISTER_TYPED_TEST_CASE_P(bitwise_shift_test,
                                   shift_left_immediate,
                                   shift_right_immediate,
                                   shift_left_byval,
                                   shift_right_byval);

        typedef ::testing::Types<zint16, zint32> bitwise_shift_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, bitwise_shift_test, bitwise_shift_test_types);

    }}