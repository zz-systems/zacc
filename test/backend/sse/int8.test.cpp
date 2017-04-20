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
#include "util/gtest_ext.hpp"
#include "system/dispatcher.hpp"

namespace zacc { namespace test {

// =====================================================================================================================
    TEST(sse_int8_arithmetic, vneg_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = -zint8(125);
        auto expected = (uint8_t) -125;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_arithmetic, vadd_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(12) + zint8(105);
        auto expected = (uint8_t) 117;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_arithmetic, vsub_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(124) - zint8(125);
        auto expected = (uint8_t) -1;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_arithmetic, vmul_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(12) * zint8(9);
        auto expected = (uint8_t) 108;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int8_bitwise, vbneg_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = ~zint8(100);
        auto expected = (uint8_t) ~100;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_bitwise, vbor_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(127) | zint8(64);
        auto expected = (uint8_t) (127 | 64);

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_bitwise, vband_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(127) & zint8(64);
        auto expected = (uint8_t) (127 & 64);

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_bitwise, vbxor_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(127) ^ zint8(64);
        auto expected = (uint8_t) (127 ^ 64);

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int8_logical, vlor_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(0) || zint8(8);
        auto expected = (uint8_t) 8;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_logical, vland_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(0) && zint8(8);
        auto expected = (uint8_t) 0;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int8_comparison, veq_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(0) == zint8(8);
        auto expected = (uint8_t) 0;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_comparison, vneq_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(0) != zint8(0);
        auto expected = (uint8_t) 0;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_comparison, vgt_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(0) > zint8(8);
        auto expected = (uint8_t) 0;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_comparison, vlt_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint8(8) < zint8(0);
        auto expected = (uint8_t) 0;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_comparison, vge_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = (zint8(0) >= zint8(0)).as_bool();
        auto expected = (uint8_t) true;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(sse_int8_comparison, vle_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = (zint8(0) <= zint8(0)).as_bool();
        auto expected = (uint8_t) true;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(sse_int8_conditional, vsel_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = vsel(zint8(1) == zint8(1), zint8(2), zint8(3));
        auto expected = (uint8_t) 2;

        for(uint8_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================

}}