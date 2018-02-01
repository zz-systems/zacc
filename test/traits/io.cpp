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
#include "system/arch.hpp"
#include "util/testing/gtest_ext.hpp"
#include <type_traits>

namespace zacc { namespace test {

        template <typename T>
        class io_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(io_test);

        template <typename T>
        class gather_test : public ::testing::Test { };
        TYPED_TEST_CASE_P(gather_test);


        TYPED_TEST_P(io_test, store)
        {
            std::array<typename TypeParam::element_t, TypeParam::size()> test_data;
            for(size_t i = 0; i < TypeParam::size(); i++)
                test_data[i] = i;

            TypeParam actual(test_data);

            auto data = actual.data();

            for(size_t i = 0; i < TypeParam::size(); i++)
                VASSERT_EQ(data[i], test_data[i]);
        }

        TYPED_TEST_P(gather_test, gather)
        {

            typename TypeParam::extracted_t data;
            for(size_t i = 0; i < TypeParam::size(); i++)
                data[i] = 10 + i;

            TypeParam actual = TypeParam::gather(std::begin(data), zint32(0));

            VASSERT_EQ(actual, 10);
        }


        REGISTER_TYPED_TEST_CASE_P(io_test,
                                   store);

        typedef ::testing::Types<zfloat, zdouble, zint8, zint16, zint32> io_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, io_test, io_test_types);

        REGISTER_TYPED_TEST_CASE_P(gather_test,
                                   gather);

        typedef ::testing::Types<zfloat, zdouble, zint32> gather_test_types;

        INSTANTIATE_TYPED_TEST_CASE_P(zacc, gather_test, gather_test_types);

    }}