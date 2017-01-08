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
#include "../impl/int16.impl.hpp"

namespace zacc { namespace None { namespace test {

// =====================================================================================================================
    TEST(None_int16_arithmetic, arithmetic_negate)
    {
        auto actual = -zint16(125);
        for(auto value : actual)
            EXPECT_EQ(value, (int)-125);
    }

    TEST(None_int16_arithmetic, arithmetic_add)
    {
        auto actual = zint16(12) + zint16(105);
        for(auto value : actual)
            EXPECT_EQ(value, (int)117);
    }

    TEST(None_int16_arithmetic, arithmetic_sub)
    {
        auto actual = zint16(124) - zint16(125);
        for(auto value : actual)
            EXPECT_EQ(value, (int)-1);
    }

    TEST(None_int16_arithmetic, arithmetic_mul)
    {
        auto actual = zint16(12) * zint16(9);
        for(auto value : actual)
            EXPECT_EQ(value, (int)108);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(None_int16_bitwise, bitwise_negate)
    {
        auto actual = ~zint16(255);
        for(auto value : actual)
            EXPECT_EQ(value, (int)-256);
    }

    TEST(None_int16_bitwise, bitwise_and)
    {
        auto actual = zint16(127) & zint16(64);
        for(auto value : actual)
            EXPECT_EQ(value, (int)64);
    }

    TEST(None_int16_bitwise, bitwise_or)
    {
        auto actual = zint16(127) | zint16(64);
        for(auto value : actual)
            EXPECT_EQ(value, (int)127);
    }

    TEST(None_int16_bitwise, bitwise_xor)
    {
        auto actual = zint16(127) ^ zint16(64);
        for(auto value : actual)
            EXPECT_EQ(value, (int)63);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(None_int16_logical, logical_negate)
    {
        auto actual = !zint16(1);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(None_int16_logical, logical_or)
    {
        auto actual = zint16(0) || zint16(8);
        for(auto value : actual)
            EXPECT_EQ(value, (int)8);
    }

    TEST(None_int16_logical, logical_and)
    {
        auto actual = zint16(0) && zint16(8);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(None_int16_comparison, comparison_eq)
    {
        auto actual = zint16(0) == zint16(8);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(None_int16_comparison, comparison_neq)
    {
        auto actual = zint16(0) != zint16(0);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(None_int16_comparison, comparison_gt)
    {
        auto actual = zint16(0) > zint16(8);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(None_int16_comparison, comparison_lt)
    {
        auto actual = zint16(8) < zint16(0);
        for(auto value : actual)
            EXPECT_EQ(value, (int)0);
    }

    TEST(None_int16_comparison, comparison_ge)
    {
        auto actual = zint16(0) >= zint16(0);
        for(auto value : actual)
            EXPECT_EQ(value, (int)1);
    }

    TEST(None_int16_comparison, comparison_le)
    {
        auto actual = zint16(0) <= zint16(0);
        for(auto value : actual)
            EXPECT_EQ(value, (int)1);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(None_int16_conditional, vsel)
    {
        auto actual = vsel(zint16(1 == 1), zint16(2), zint16(3));
        for(auto value : actual)
            EXPECT_EQ(value, (int)2);
    }

// =====================================================================================================================

}}}