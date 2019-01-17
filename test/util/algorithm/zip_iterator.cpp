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
#include "util/algorithm.hpp"

#include <cmath>
#include "util/testing/gtest_ext.hpp"
namespace zacc { namespace test {


    class zip_iterator_test : public ::testing::Test
    {
    public:
        using container_t = std::array<int, 10>;

    protected:
        // Per-test-case set-up.
        // Called before the first test in this test case.
        // Can be omitted if not needed.
        static void SetUpTestCase()
        {
            std::iota(a_items.begin(), a_items.end(), 0);
            std::iota(b_items.begin(), b_items.end(), 0);

            std::iota(a_expected.begin(), a_expected.end(), 0);
            std::iota(b_expected.begin(), b_expected.end(), 0);
        }

        // Per-test-case tear-down.
        // Called after the last test in this test case.
        // Can be omitted if not needed.
        static void TearDownTestCase()
        {}

        // You can define per-test set-up and tear-down logic as usual.
        void SetUp() override {  }

        void TearDown() override {  }


        static const size_t size = 10;

        // Some expensive resource shared by all tests.
        static container_t a_items;
        static container_t b_items;

        static container_t a_expected;
        static container_t b_expected;
    };

    zip_iterator_test::container_t a_items;
    zip_iterator_test::container_t b_items;

    zip_iterator_test::container_t a_expected;
    zip_iterator_test::container_t b_expected;


    TEST(zip_iterator_test, verify_data_not_cloned) {
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

    TEST(zip_iterator_test, distance) {
            REQUIRES(ZACC_ARCH);

        auto data = zip(a_items, b_items);

        auto begin = std::begin(data);
        auto end = std::end(data);

        auto begin_expected = std::begin(a_items);
        auto end_expected = std::end(a_items);

        ASSERT_EQ(std::distance(begin, end), std::distance(begin_expected, end_expected));
    }

    TEST(zip_iterator_test, increment_simple) {
            REQUIRES(ZACC_ARCH);

        auto data = zip(a_items, b_items);

        auto begin = std::begin(data);
        auto end = std::end(data);

        for(int i = data.size() - 1; i >= 0; --i)
        {
            ++begin;

            EXPECT_EQ(std::distance(begin, end), i);
        }
    }

    TEST(zip_iterator_test, increment) {
            REQUIRES(ZACC_ARCH);

        auto data = zip(a_items, b_items);

        auto begin = std::begin(data);
        auto end = std::end(data);

        EXPECT_EQ(std::distance(begin, end), 10);

        {
            auto begin_copy = begin++;

            EXPECT_EQ(std::distance(begin, end), 9);
            EXPECT_EQ(std::distance(begin_copy, end), 10);
        }

        {
            auto begin_copy = ++begin;

            EXPECT_EQ(std::distance(begin, end), 8);
            EXPECT_EQ(std::distance(begin_copy, end), 8);
        }

        EXPECT_TRUE(begin != end) << "with distance: " << std::distance(begin, end);

        begin += 4;

        EXPECT_TRUE(begin != end) << "with distance: " << std::distance(begin, end);

        begin += 4;

        EXPECT_TRUE(begin == end) << "with distance: " << std::distance(begin, end);
    }

    TEST(zip_iterator_test, zip_iterator) {
            REQUIRES(ZACC_ARCH);

        auto data = zip(a_items, b_items);

        auto begin = std::begin(data);
        auto end = std::end(data);

        EXPECT_TRUE(begin != end) << "with distance: " << std::distance(begin, end);

        begin += 5;

        EXPECT_TRUE(begin != end) << "with distance: " << std::distance(begin, end);

        begin += 5;

        EXPECT_TRUE(begin == end) << "with distance: " << std::distance(begin, end);
    }
}}
