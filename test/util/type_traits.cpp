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
#include "util/algorithm.hpp"

#include <cmath>
#include "util/testing/gtest_ext.hpp"

namespace zacc { namespace test {

        TEST(type_traits_test, is_iterable_trait) {
            REQUIRES(ZACC_ARCH);

                EXPECT_TRUE((is<measurable, std::array<int, 10>>));
                EXPECT_FALSE((is<measurable, int>));

                EXPECT_TRUE((is<iterable, std::array<int, 10>>));
                EXPECT_FALSE((is<iterable, int>));

                EXPECT_FALSE((is<resizable, std::array<int, 10>>));
                EXPECT_FALSE((is<resizable, int>));
                EXPECT_TRUE((is<resizable, std::vector<int>>));

                EXPECT_FALSE((all<measurable, std::array<int, 10>, std::vector<float>, double>));
                EXPECT_TRUE((all<measurable, std::array<int, 10>, std::vector<float>>));

                EXPECT_TRUE((any<measurable, std::array<int, 10>, std::vector<float>, double>));

                EXPECT_TRUE((is<swappable, std::tuple<int, float>>));
        }




}}
