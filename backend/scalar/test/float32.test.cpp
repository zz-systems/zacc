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
#include "../impl/float32.impl.hpp"

namespace zacc { namespace scalar { namespace test {

// =====================================================================================================================
    TEST(scalar_float32_arithmetic, arithmetic_negate)
    {
        auto actual = -zfloat32(125);
        for(auto value : actual)
            EXPECT_EQ(value, (float)-125);
    }

    TEST(scalar_float32_arithmetic, arithmetic_add)
    {
        auto actual = zfloat32(12) + zfloat32(105);
        for(auto value : actual)
            EXPECT_EQ(value, (float)117);
    }

    TEST(scalar_float32_arithmetic, arithmetic_sub)
    {
        auto actual = zfloat32(124) - zfloat32(125);
        for(auto value : actual)
            EXPECT_EQ(value, (float)-1);
    }

    TEST(scalar_float32_arithmetic, arithmetic_mul)
    {
        auto actual = zfloat32(12) * zfloat32(9);
        for(auto value : actual)
            EXPECT_EQ(value, (float)108);
    }

    TEST(scalar_float32_arithmetic, arithmetic_div)
    {
        auto actual = zfloat32(124) / zfloat32(124);
        for(auto value : actual)
            EXPECT_EQ(value, (float)1);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(scalar_float32_comparison, comparison_eq)
    {
        auto actual = zfloat32(0) == zfloat32(8);
        for(auto value : actual)
            EXPECT_EQ(value, (float)0);
    }

    TEST(scalar_float32_comparison, comparison_neq)
    {
        auto actual = zfloat32(0) != zfloat32(0);
        for(auto value : actual)
            EXPECT_EQ(value, (float)0);
    }

    TEST(scalar_float32_comparison, comparison_gt)
    {
        auto actual = zfloat32(0) > zfloat32(8);
        for(auto value : actual)
            EXPECT_EQ(value, (float)0);
    }

    TEST(scalar_float32_comparison, comparison_lt)
    {
        auto actual = zfloat32(8) < zfloat32(0);
        for(auto value : actual)
            EXPECT_EQ(value, (float)0);
    }

    TEST(scalar_float32_comparison, comparison_ge)
    {
        auto actual = zfloat32(0) >= zfloat32(0);
        for(auto value : actual)
            EXPECT_EQ(value, (float)1);
    }

    TEST(scalar_float32_comparison, comparison_le)
    {
        auto actual = zfloat32(0) <= zfloat32(0);
        for(auto value : actual)
            EXPECT_EQ(value, (float)1);
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(scalar_float32_conditional, vsel)
    {
        auto actual = vsel(zfloat32(1 == 1), zfloat32(2), zfloat32(3));
        for(auto value : actual)
            EXPECT_EQ(value, (float)2);
    }

// =====================================================================================================================

}}}