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
    class casting_test : public ::testing::Test { };
    TYPED_TEST_CASE_P(casting_test);

    TYPED_TEST_P(casting_test, make_mask_0)
    {

        const size_t size   = 8;
        auto max_size       = std::min(size_v<TypeParam>, size);

        using data_t = typename std::array<element_t<TypeParam>, size>;
        data_t _condition   {{ 1, 1, 0, 3, 4, 0, 5, 6 }};
        data_t _expected    {{ 1, 1, 0, 1, 1, 0, 1, 1 }};


        alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

        for (size_t i = 0; i < size_v<TypeParam>; i += size)
        {
            std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
            std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
        }

        TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

        auto actual = make_mask(condition);
        auto data = actual.data();

        for(int i = 0; i < size_v<TypeParam>; i++)
        {
            VASSERT_EQ(data[i], expected[i]);
        }
    }

    TYPED_TEST_P(casting_test, make_mask_1)
    {

        const size_t size   = 8;
        auto max_size       = std::min(size_v<TypeParam>, size);

        using data_t = typename std::array<element_t<TypeParam>, size>;
        data_t _condition   {{ 0, 1, 0, 3, 4, 0, 0, 6 }};
        data_t _expected    {{ 0, 1, 0, 1, 1, 0, 0, 1 }};


        alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

        for (size_t i = 0; i < size_v<TypeParam>; i += size)
        {
            std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
            std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
        }

        TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

        auto actual = make_mask(condition);
        auto data = actual.data();

        for(int i = 0; i < size_v<TypeParam>; i++)
        {
            VASSERT_EQ(data[i], expected[i]);
        }
    }

    TYPED_TEST_P(casting_test, make_mask_2)
    {
        const size_t size   = 8;
        auto max_size       = std::min(size_v<TypeParam>, size);

        using data_t = typename std::array<element_t<TypeParam>, size>;
        data_t _condition   {{ 0, 0, 0, 0, 0, 0, 0, 0 }};
        data_t _expected    {{ 0, 0, 0, 0, 0, 0, 0, 0 }};


        alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

        for (size_t i = 0; i < size_v<TypeParam>; i += size)
        {
            std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
            std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
        }

        TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

        auto actual = make_mask(condition);
        auto data = actual.data();

        for(int i = 0; i < size_v<TypeParam>; i++)
        {
            VASSERT_EQ(data[i], expected[i]);
        }
    }

    TYPED_TEST_P(casting_test, make_mask_3)
    {
        const size_t size   = 8;
        auto max_size       = std::min(size_v<TypeParam>, size);

        using data_t = typename std::array<element_t<TypeParam>, size>;
        data_t _condition   {{ 0, 0, 1, 0, 0, 0, 1, 0 }};
        data_t _expected    {{ 0, 0, 1, 0, 0, 0, 1, 0 }};


        alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

        for (size_t i = 0; i < size_v<TypeParam>; i += size)
        {
            std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
            std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
        }

        TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

        auto actual = make_mask(condition);
        auto data = actual.data();

        for(int i = 0; i < size_v<TypeParam>; i++)
        {
            VASSERT_EQ(data[i], expected[i]);
        }
    }

    TYPED_TEST_P(casting_test, make_mask_4)
    {
        const size_t size   = 8;
        auto max_size       = std::min(size_v<TypeParam>, size);

        using data_t = typename std::array<element_t<TypeParam>, size>;
        data_t _condition   {{ 1, 1, 1, 1, 1, 1, 1, 1 }};
        data_t _expected    {{ 1, 1, 1, 1, 1, 1, 1, 1 }};


        alignas(alignment_v<TypeParam>) extracted_t<TypeParam> __condition, expected;

        for (size_t i = 0; i < size_v<TypeParam>; i += size)
        {
            std::copy(std::begin(_condition), std::begin(_condition) + max_size, std::begin(__condition) + i);
            std::copy(std::begin(_expected), std::begin(_expected) + max_size, std::begin(expected) + i);
        }

        TypeParam condition(static_cast<zval_t<TypeParam>>(__condition));

        auto actual = make_mask(condition);
        auto data = actual.data();

        for(int i = 0; i < size_v<TypeParam>; i++)
        {
            VASSERT_EQ(data[i], expected[i]);
        }
    }

    REGISTER_TYPED_TEST_CASE_P(casting_test,
                               make_mask_0,
                               make_mask_1,
                               make_mask_2,
                               make_mask_3,
                               make_mask_4);

    typedef ::testing::Types<zfloat, zdouble, zint8, zint16, zint32, bfloat, bdouble, bint8, bint16, bint32> casting_test_types;

    INSTANTIATE_TYPED_TEST_CASE_P(zacc, casting_test, casting_test_types);
}}