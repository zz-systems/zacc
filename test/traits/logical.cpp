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
        class logical_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(logical_test);


        TYPED_TEST_P(logical_test, negate)
        {
            TypeParam value = 5;
            auto actual= !value;

            VASSERT_EQ(actual.as_bool(), TypeParam((typename TypeParam::element_type) false));

            actual = !actual;

            VASSERT_EQ(actual.as_bool(), TypeParam((typename TypeParam::element_type) true));
        }

        TYPED_TEST_P(logical_test, or_operation)
        {
            TypeParam value = 5;
            auto actual= value || (value >= 2);

            VASSERT_EQ(actual.as_bool(), TypeParam((typename TypeParam::element_type) true));

            actual = TypeParam(0) || (value >= 2);

            VASSERT_EQ(actual.as_bool(), TypeParam((typename TypeParam::element_type) true));

            actual = value || (value < 2);

            VASSERT_EQ(actual.as_bool(), TypeParam((typename TypeParam::element_type) true));

            actual = TypeParam(0) || (value <= 2);

            VASSERT_EQ(actual.as_bool(), TypeParam((typename TypeParam::element_type) false));
        }

        TYPED_TEST_P(logical_test, and_operation)
        {
            TypeParam value = 5;
            auto actual= value && (value >= 2);

            VASSERT_EQ(actual.as_bool(), TypeParam((typename TypeParam::element_type) true));

            actual = value && (value < 2);

            VASSERT_EQ(actual.as_bool(), TypeParam((typename TypeParam::element_type) false));
        }

        REGISTER_TYPED_TEST_CASE_P(logical_test,
                                   negate,
                                   or_operation,
                                   and_operation);

        typedef ::testing::Types<zfloat, zdouble, zint8, zint16, zint32> logical_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, logical_test, logical_test_types);

    }}