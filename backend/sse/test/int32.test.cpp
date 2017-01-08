//---------------------------------------------------------------------------------
//
//  This is an autogenerated file. Do not edit!
//
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
#include "../impl/int32.impl.hpp"

namespace zacc { namespace sse { namespace test {

// =====================================================================================================================
    TEST(sse_int32_arithmetic, arithmetic_negate)
    {
        auto actual = -zint32(125);
        for(auto value : actual)
            EXPECT_EQ(value, (int)-125);
    }

    TEST(sse_int32_arithmetic, arithmetic_add)
    {
        auto actual = zint32(12) + zint32(105);
        for(auto value : actual)
            EXPECT_EQ(value, (int)117);
    }

    TEST(sse_int32_arithmetic, arithmetic_sub)
    {
        auto actual = zint32(124) - zint32(125);
        for(auto value : actual)
            EXPECT_EQ(value, (int)-1);
    }

    TEST(sse_int32_arithmetic, arithmetic_mul)
    {
        auto actual = zint32(12) * zint32(9);
        for(auto value : actual)
            EXPECT_EQ(value, (int)108);
    }

    TEST(sse_int32_arithmetic, arithmetic_div)
    {
        auto actual = zint32(124) / zint32(124);
        for(auto value : actual)
            EXPECT_EQ(value, (int)1);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_bitwise, bitwise_negate)
    {
        auto actual = ~zint32(255);
        for(auto value : actual)
            EXPECT_EQ(value, (int)-256);
    }

    TEST(sse_int32_bitwise, bitwise_and)
    {
        auto actual = zint32(127) & zint32(64);
        for(auto value : actual)
            EXPECT_EQ(value, (int)64);
    }

    TEST(sse_int32_bitwise, bitwise_or)
    {
        auto actual = zint32(127) | zint32(64);
        for(auto value : actual)
            EXPECT_EQ(value, (int)127);
    }

    TEST(sse_int32_bitwise, bitwise_xor)
    {
        auto actual = zint32(127) ^ zint32(64);
        for(auto value : actual)
            EXPECT_EQ(value, (int)63);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_bitwise_shift, bitwise_shift_sll)
    {
        auto actual = zint32(1) << zint32(4);
        for(auto value : actual)
            EXPECT_EQ(value, (int)16);
    }

    TEST(sse_int32_bitwise_shift, bitwise_shift_srl)
    {
        auto actual = zint32(109) >> zint32(3);
        for(auto value : actual)
            EXPECT_EQ(value, (int)13);
    }

    TEST(sse_int32_bitwise_shift, bitwise_shift_slli)
    {
        auto actual = zint32(1) << (4);
        for(auto value : actual)
            EXPECT_EQ(value, (int)16);
    }

    TEST(sse_int32_bitwise_shift, bitwise_shift_srli)
    {
        auto actual = zint32(109) >> (3);
        for(auto value : actual)
            EXPECT_EQ(value, (int)13);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_logical, logical_negate)
    {
        auto actual = !zint32(1);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(sse_int32_logical, logical_or)
    {
        auto actual = zint32(0) || zint32(8);
        for(auto value : actual)
            EXPECT_EQ(value, (int)8);
    }

    TEST(sse_int32_logical, logical_and)
    {
        auto actual = zint32(0) && zint32(8);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_comparison, comparison_eq)
    {
        auto actual = zint32(0) == zint32(8);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(sse_int32_comparison, comparison_neq)
    {
        auto actual = zint32(0) != zint32(0);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(sse_int32_comparison, comparison_gt)
    {
        auto actual = zint32(0) > zint32(8);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(sse_int32_comparison, comparison_lt)
    {
        auto actual = zint32(8) < zint32(0);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(sse_int32_comparison, comparison_ge)
    {
        auto actual = zint32(0) >= zint32(0);
        for(auto value : actual)
            EXPECT_EQ(value, (int)1);
    }

    TEST(sse_int32_comparison, comparison_le)
    {
        auto actual = zint32(0) <= zint32(0);
        for(auto value : actual)
            EXPECT_EQ(value, (int)1);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_conditional, vsel)
    {
        auto actual = vsel(zint32(1 == 1), zint32(2), zint32(3));
        for(auto value : actual)
            EXPECT_EQ(value, (int)2);
    }

// =====================================================================================================================

}}}