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
#include "util/algorithm.hpp"

#include <cmath>
#include "util/testing/gtest_ext.hpp"
namespace zacc { namespace test {


    TEST(zip_test, verify_data_not_cloned) {
            REQUIRES(ZACC_ARCH);

        std::array<int, 10> a_items {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};
        std::array<int, 10> b_items {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

        std::array<int, 10> a_expected {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};
        std::array<int, 10> b_expected {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

        int a, b;
        size_t i = 0;

        auto data = zip(a_items, b_items);

        for(auto tp : data)
        {
            EXPECT_EQ(&std::get<0>(tp), &a_items[i]);
            EXPECT_EQ(&std::get<1>(tp), &b_items[i]);

            std::tie(a, b) = tp;

            EXPECT_EQ(a, a_expected[i]);
            EXPECT_EQ(b, b_expected[i]);

            ++i;
        }
    }

   TEST(zip_test, verify_data_cloned) {
            REQUIRES(ZACC_ARCH);

        std::array<int, 10> a_expected {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};
        std::array<int, 10> b_expected {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

        int a, b;
        size_t i = 0;

        auto data = zip(std::array<int, 10> {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }},
                        std::array<int, 10> {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }});

        for(auto elem : data)
        {
            std::tie(a, b) = elem;

            EXPECT_EQ(a, a_expected[i]) << "with index i: " << i;
            EXPECT_EQ(b, b_expected[i]) << "with index i: " << i;

            i++;
        }
    }

    TEST(zip_test, zip_1) {
            REQUIRES(ZACC_ARCH);

        std::array<int, 10> a_items {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};
        std::array<int, 10> b_items {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

        std::array<int, 10> a_expected {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};
        std::array<int, 10> b_expected {{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }};

        int a, b;
        size_t i = 0;

        for(auto elem : zip(a_items, b_items))
        {
            std::tie(a, b) = elem;

            EXPECT_EQ(a, a_expected[i]) << "with index i: " << i;
            EXPECT_EQ(b, b_expected[i]) << "with index i: " << i;

            i++;
        }

        //auto b = "abcdefghij";
    }
}}
