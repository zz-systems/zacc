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
        class conditional_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(conditional_test);


        TYPED_TEST_P(conditional_test, if_then_else_0)
        {
            TypeParam a = 10;
            TypeParam b = 20;

            auto actual0 = a.when(false).otherwise(b);
            VASSERT_EQ(actual0, b);

            auto actual1 = a.when(true).otherwise(b);
            VASSERT_EQ(actual1, a);
        }

        TYPED_TEST_P(conditional_test, if_then_else_1)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<typename TypeParam::element_type, size>;

            data_t  _one        {{  1,  2,  3,  4,  5,  6,  7,  8 }},
                    _other      {{ 10, 11, 12, 13, 14, 15, 16, 17 }};

            data_t  _condition  {{  1,  1,  0,  3,  4,  0,  5,  6 }},
                    _expected   {{  1,  2, 12,  4,  5, 15,  7,  8 }};

            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __one, __other, __condition, __expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(__expected) + i);

                std::copy(std::begin(_one), std::begin(_one) + max_size, std::begin(__one) + i);
                std::copy(std::begin(_other), std::begin(_other) + max_size, std::begin(__other) + i);
            }

            TypeParam one(__one), other(__other), condition(__condition), expected(__expected);

            auto actual0 = vsel(make_mask(condition), one, other);
            VASSERT_EQ(actual0, expected);

            auto actual1 = one.when(condition).otherwise(other);
            VASSERT_EQ(actual1, expected);
        }

        TYPED_TEST_P(conditional_test, if_then_else_2)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<typename TypeParam::element_type, size>;

            data_t  _one        {{  1,  2,  3,  4,  5,  6,  7,  8 }},
                    _other      {{ 10, 11, 12, 13, 14, 15, 16, 17 }};

            data_t  _condition  {{  0,  1,  0,  3,  4,  0,  0,  6 }},
                    _expected   {{ 10,  2, 12,  4,  5, 15, 16,  8 }};

            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __one, __other, __condition, __expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(__expected) + i);

                std::copy(std::begin(_one), std::begin(_one) + max_size, std::begin(__one) + i);
                std::copy(std::begin(_other), std::begin(_other) + max_size, std::begin(__other) + i);
            }

            TypeParam one(__one), other(__other), condition(__condition), expected(__expected);

            std::cout << "CONDITION: " << condition << " MASK: " << make_mask(condition) << std::endl;

            auto actual0 = vsel(make_mask(condition), one, other);
            VASSERT_EQ(actual0, expected);

            auto actual1 = one.when(condition).otherwise(other);
            VASSERT_EQ(actual1, expected);
        }

        TYPED_TEST_P(conditional_test, if_then_else_3)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<typename TypeParam::element_type, size>;

            data_t  _one        {{  1,  2,  3,  4,  5,  6,  7,  8 }},
                    _other      {{ 10, 11, 12, 13, 14, 15, 16, 17 }};

            data_t  _condition  {{  0,  0,  0,  0,  0,  0,  0,  0 }},
                    _expected   {{ 10, 11, 12, 13, 14, 15, 16, 17 }};

            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __one, __other, __condition, __expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(__expected) + i);

                std::copy(std::begin(_one), std::begin(_one) + max_size, std::begin(__one) + i);
                std::copy(std::begin(_other), std::begin(_other) + max_size, std::begin(__other) + i);
            }

            TypeParam one(__one), other(__other), condition(__condition), expected(__expected);

            auto actual0 = vsel(make_mask(condition), one, other);
            VASSERT_EQ(actual0, expected);

            auto actual1 = one.when(condition).otherwise(other);
            VASSERT_EQ(actual1, expected);
        }

        TYPED_TEST_P(conditional_test, if_then_else_4)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<typename TypeParam::element_type, size>;

            data_t  _one        {{  1,  2,  3,  4,  5,  6,  7,  8 }},
                    _other      {{ 10, 11, 12, 13, 14, 15, 16, 17 }};

            data_t  _condition  {{  0,  0,  1,  0,  0,  0,  1,  0 }},
                    _expected   {{ 10, 11,  3, 13, 14, 15,  7, 17 }};

            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __one, __other, __condition, __expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(__expected) + i);

                std::copy(std::begin(_one), std::begin(_one) + max_size, std::begin(__one) + i);
                std::copy(std::begin(_other), std::begin(_other) + max_size, std::begin(__other) + i);
            }

            TypeParam one(__one), other(__other), condition(__condition), expected(__expected);

            auto actual0 = vsel(make_mask(condition), one, other);
            VASSERT_EQ(actual0, expected);

            auto actual1 = one.when(condition).otherwise(other);
            VASSERT_EQ(actual1, expected);
        }

        TYPED_TEST_P(conditional_test, if_then_else_5)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<typename TypeParam::element_type, size>;

            data_t  _one        {{  1,  2,  3,  4,  5,  6,  7,  8 }},
                    _other      {{ 10, 11, 12, 13, 14, 15, 16, 17 }};

            data_t  _condition  {{  1,  1,  1,  1,  1,  1,  1,  1 }},
                    _expected   {{  1,  2,  3,  4,  5,  6,  7,  8 }};

            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __one, __other, __condition, __expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(__expected) + i);

                std::copy(std::begin(_one), std::begin(_one) + max_size, std::begin(__one) + i);
                std::copy(std::begin(_other), std::begin(_other) + max_size, std::begin(__other) + i);
            }

            TypeParam one(__one), other(__other), condition(__condition), expected(__expected);

            auto actual0 = vsel(make_mask(condition), one, other);
            VASSERT_EQ(actual0, expected);

            auto actual1 = one.when(condition).otherwise(other);
            VASSERT_EQ(actual1, expected);
        }


        REGISTER_TYPED_TEST_CASE_P(conditional_test,
                                   if_then_else_0,
                                   if_then_else_1,
                                   if_then_else_2,
                                   if_then_else_3,
                                   if_then_else_4,
                                   if_then_else_5);

        typedef ::testing::Types<zfloat, zdouble, zint8, zint16, zint32> conditional_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, conditional_test, conditional_test_types);

    }}