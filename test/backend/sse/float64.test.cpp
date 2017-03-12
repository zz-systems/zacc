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
#include "system/dispatcher.hpp"

//namespace zacc { namespace sse { namespace test {
namespace zacc { namespace test {

// =====================================================================================================================
    TEST(sse_float64_arithmetic, vneg_default)
    {
        auto actual = -zfloat64(125);
        auto expected = (double) -125;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_arithmetic, vadd_default)
    {
        auto actual = zfloat64(12) + zfloat64(105);
        auto expected = (double) 117;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_arithmetic, vsub_default)
    {
        auto actual = zfloat64(124) - zfloat64(125);
        auto expected = (double) -1;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_arithmetic, vmul_default)
    {
        auto actual = zfloat64(12) * zfloat64(9);
        auto expected = (double) 108;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_arithmetic, vdiv_default)
    {
        auto actual = zfloat64(124) / zfloat64(124);
        auto expected = (double) 1;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_float64_logical, vlneg_default)
    {
        auto actual = (!zfloat64(1)).as_bool();
        auto expected = (double) false;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_logical, vlor_default)
    {
        auto actual = zfloat64(0) || zfloat64(8);
        auto expected = (double) 8;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_logical, vland_default)
    {
        auto actual = zfloat64(0) && zfloat64(8);
        auto expected = (double) 0;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_float64_comparison, veq_default)
    {
        auto actual = zfloat64(0) == zfloat64(8);
        auto expected = (double) 0;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_comparison, vneq_default)
    {
        auto actual = zfloat64(0) != zfloat64(0);
        auto expected = (double) 0;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_comparison, vgt_default)
    {
        auto actual = zfloat64(0) > zfloat64(8);
        auto expected = (double) 0;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_comparison, vlt_default)
    {
        auto actual = zfloat64(8) < zfloat64(0);
        auto expected = (double) 0;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_comparison, vge_default)
    {
        auto actual = (zfloat64(0) >= zfloat64(0)).as_bool();
        auto expected = (double) true;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_comparison, vle_default)
    {
        auto actual = (zfloat64(0) <= zfloat64(0)).as_bool();
        auto expected = (double) true;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_float64_conditional, vsel_sse4)
    {
        auto actual = vsel(zfloat64(1) == zfloat64(1), zfloat64(2), zfloat64(3));
        auto expected = (double) 2;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

    TEST(sse_float64_conditional, vsel_default)
    {
        auto actual = vsel(zfloat64(1) == zfloat64(1), zfloat64(2), zfloat64(3));
        auto expected = (double) 2;

        for(double value : actual)
        {
            ASSERT_DOUBLE_EQ(value, expected);
        }
    }

// =====================================================================================================================

}}