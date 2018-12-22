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
#include "system/arch.hpp"
#include "util/testing/gtest_ext.hpp"
#include <type_traits>

namespace zacc { namespace test {

        template <typename T>
        class conditional_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(conditional_test);


        TYPED_TEST_P(conditional_test, if_then_else_simple)
        {
            TypeParam a = 10;
            TypeParam b = 20;

            TypeParam c0 = 0;
            auto actual0 = a.when(c0).otherwise(b);
            VASSERT_EQ(actual0, b);

            TypeParam c1 = 1;
            auto actual1 = a.when(c1).otherwise(b);
            VASSERT_EQ(actual1, a);
        }

//        TYPED_TEST_P(conditional_test, if_then_else)
//        {
//            const size_t size   = 8;
//            auto max_size       = std::min(TypeParam::size(), size);
//
//            using data_t = typename std::array<typename TypeParam::element_type, size>;
//
//            data_t  _one        {{  1,  2,  3,  4,  5,  6,  7,  8 }},
//                    _other      {{ 10, 11, 12, 13, 14, 15, 16, 17 }};
//
//            data_t  _condition  {{ 1, 1,  0, 3, 4,  0, 5, 6 }},
//                    _expected   {{ 1, 2, 12, 4, 5, 15, 7, 8 }};
//
//            typename TypeParam::extracted_t __one, __other, __condition, __expected;
//
//            for (size_t i = 0; i < TypeParam::size(); i += size)
//            {
//                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
//                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(__expected) + i);
//
//                std::copy(std::begin(_one), std::begin(_one) + max_size, std::begin(__one) + i);
//                std::copy(std::begin(_other), std::begin(_other) + max_size, std::begin(__other) + i);
//            }
//
//            TypeParam one(__one), other(__other), condition(__condition), expected(__expected);
//            VASSERT_EQ(one.when(condition).otherwise(other), expected);
//
//            TypeParam a = 10;
//            TypeParam b = 20;
//
//            TypeParam c0 = 0;
//            auto actual0 = a.when(c0).otherwise(b);
//            VASSERT_EQ(actual0, b);
//
//            TypeParam c1 = 1;
//            auto actual1 = a.when(c1).otherwise(b);
//            VASSERT_EQ(actual1, a);
//        }


        REGISTER_TYPED_TEST_CASE_P(conditional_test,
                                   if_then_else_simple/*,
                                   if_then_else*/);

        typedef ::testing::Types<zfloat, zdouble, zint8, zint16, zint32> conditional_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, conditional_test, conditional_test_types);

    }}