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

namespace zacc { namespace test {

// =====================================================================================================================
    TEST(sse_int32_arithmetic, vneg_default)
    {
        auto actual = -zint32(125);
        auto expected = (int32_t) -125;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_arithmetic, vadd_default)
    {
        auto actual = zint32(12) + zint32(105);
        auto expected = (int32_t) 117;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_arithmetic, vsub_default)
    {
        auto actual = zint32(124) - zint32(125);
        auto expected = (int32_t) -1;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_arithmetic, vmul_sse4)
    {
        auto actual = zint32(12) * zint32(9);
        auto expected = (int32_t) 108;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_arithmetic, vmul_default)
    {
        auto actual = zint32(12) * zint32(9);
        auto expected = (int32_t) 108;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_arithmetic, vdiv_default)
    {
        auto actual = zint32(124) / zint32(124);
        auto expected = (int32_t) 1;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_bitwise, vbneg_default)
    {
        auto actual = ~zint32(100);
        auto expected = (int32_t) ~100;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_bitwise, vbor_default)
    {
        auto actual = zint32(127) | zint32(64);
        auto expected = (int32_t) (127 | 64);

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_bitwise, vband_default)
    {
        auto actual = zint32(127) & zint32(64);
        auto expected = (int32_t) (127 & 64);

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_bitwise, vbxor_default)
    {
        auto actual = zint32(127) ^ zint32(64);
        auto expected = (int32_t) (127 ^ 64);

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_bitwise_shift, vbslli_default)
    {
        auto actual = zint32(1) << (4);
        auto expected = (int32_t) (1) << (4);

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_bitwise_shift, vbsrli_default)
    {
        auto actual = zint32(109) >> (3);
        auto expected = (int32_t) (109) >> (3);

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_logical, vlneg_default)
    {
        auto actual = (!zint32(1)).as_bool();
        auto expected = (int32_t) false;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_logical, vlor_default)
    {
        auto actual = zint32(0) || zint32(8);
        auto expected = (int32_t) 8;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_logical, vland_default)
    {
        auto actual = zint32(0) && zint32(8);
        auto expected = (int32_t) 0;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_comparison, veq_default)
    {
        auto actual = zint32(0) == zint32(8);
        auto expected = (int32_t) 0;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_comparison, vneq_default)
    {
        auto actual = zint32(0) != zint32(0);
        auto expected = (int32_t) 0;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_comparison, vgt_default)
    {
        auto actual = zint32(0) > zint32(8);
        auto expected = (int32_t) 0;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_comparison, vlt_default)
    {
        auto actual = zint32(8) < zint32(0);
        auto expected = (int32_t) 0;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_comparison, vge_default)
    {
        auto actual = (zint32(0) >= zint32(0)).as_bool();
        auto expected = (int32_t) true;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_comparison, vle_default)
    {
        auto actual = (zint32(0) <= zint32(0)).as_bool();
        auto expected = (int32_t) true;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int32_conditional, vsel_sse4)
    {
        auto actual = vsel(zint32(1) == zint32(1), zint32(2), zint32(3));
        auto expected = (int32_t) 2;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int32_conditional, vsel_default)
    {
        auto actual = vsel(zint32(1) == zint32(1), zint32(2), zint32(3));
        auto expected = (int32_t) 2;

        for(int32_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================

}}