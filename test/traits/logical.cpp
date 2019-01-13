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
        class logical_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(logical_test);


        TYPED_TEST_P(logical_test, negate_0)
        {
            TypeParam true_val = true;
            TypeParam false_val = false;

            VASSERT_EQ(!true_val, false);
            VASSERT_EQ(!false_val, true);
        }

        TYPED_TEST_P(logical_test, negate_1)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<element_t<TypeParam>, size>;
            data_t _condition   {{ 1, 1, 0, 3, 4, 0, 5, 6 }};
            data_t _expected    {{ 0, 0, 1, 0, 0, 1, 0, 0 }};


            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
            }

            TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

            auto actual = !condition;
            auto data = actual.data();

            for(int i = 0; i < size_v<TypeParam>; i++)
            {
                VASSERT_EQ(data[i], expected[i]);
            }
        }

        TYPED_TEST_P(logical_test, negate_2)
        {

            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<element_t<TypeParam>, size>;
            data_t _condition   {{ 0, 1, 0, 3, 4, 0, 0, 6 }};
            data_t _expected    {{ 1, 0, 1, 0, 0, 1, 1, 0 }};


            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
            }

            TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

            auto actual = !condition;
            auto data = actual.data();

            for(int i = 0; i < size_v<TypeParam>; i++)
            {
                VASSERT_EQ(data[i], expected[i]);
            }
        }

        TYPED_TEST_P(logical_test, negate_3)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<element_t<TypeParam>, size>;
            data_t _condition   {{ 0, 0, 0, 0, 0, 0, 0, 0 }};
            data_t _expected    {{ 1, 1, 1, 1, 1, 1, 1, 1 }};


            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;
            
            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
            }

            TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

            auto actual = !condition;
            auto data = actual.data();

            for(int i = 0; i < size_v<TypeParam>; i++)
            {
                VASSERT_EQ(data[i], expected[i]);
            }
        }

        TYPED_TEST_P(logical_test, negate_4)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<element_t<TypeParam>, size>;
            data_t _condition   {{ 0, 0, 1, 0, 0, 0, 1, 0 }};
            data_t _expected    {{ 1, 1, 0, 1, 1, 1, 0, 1 }};


            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
            }

            TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

            auto actual = !condition;
            auto data = actual.data();

            for(int i = 0; i < size_v<TypeParam>; i++)
            {
                VASSERT_EQ(data[i], expected[i]);
            }
        }

        TYPED_TEST_P(logical_test, negate_5)
        {
            const size_t size   = 8;
            auto max_size       = std::min(size_v<TypeParam>, size);

            using data_t = typename std::array<element_t<TypeParam>, size>;
            data_t _condition   {{ 1, 1, 1, 1, 1, 1, 1, 1 }};
            data_t _expected    {{ 0, 0, 0, 0, 0, 0, 0, 0 }};


            alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

            for (size_t i = 0; i < size_v<TypeParam>; i += size)
            {
                std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
                std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
            }

            TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

            auto actual = !condition;
            auto data = actual.data();


            for(int i = 0; i < size_v<TypeParam>; i++)
            {
                VASSERT_EQ(data[i], expected[i]);
            }
        }

        TYPED_TEST_P(logical_test, or_operation)
        {
            TypeParam true_val = true;
            TypeParam false_val = false;

            VASSERT_EQ(true_val || true_val, true);
            VASSERT_EQ(true_val || false_val, true);
            VASSERT_EQ(false_val || true_val, true);
            VASSERT_EQ(false_val || false_val, false);
        }

        TYPED_TEST_P(logical_test, and_operation)
        {
            TypeParam true_val = true;
            TypeParam false_val = false;

            VASSERT_EQ(true_val && true_val, true);
            VASSERT_EQ(true_val && false_val, false);
            VASSERT_EQ(false_val && true_val, false);
            VASSERT_EQ(false_val && false_val, false);
        }

        REGISTER_TYPED_TEST_CASE_P(logical_test,
                                   negate_0,
                                   negate_1,
                                   negate_2,
                                   negate_3,
                                   negate_4,
                                   negate_5,
                                   or_operation,
                                   and_operation);

        typedef ::testing::Types<bfloat, bdouble, bint8, bint16, bint32> logical_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, logical_test, logical_test_types);

    }}