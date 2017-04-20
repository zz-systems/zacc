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
    TEST(scalar_int16_arithmetic, vneg_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = -zint16(125);
        auto expected = (int16_t) -125;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_arithmetic, vadd_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(12) + zint16(105);
        auto expected = (int16_t) 117;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_arithmetic, vsub_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(124) - zint16(125);
        auto expected = (int16_t) -1;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_arithmetic, vmul_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(12) * zint16(9);
        auto expected = (int16_t) 108;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_arithmetic, vdiv_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(124) / zint16(124);
        auto expected = (int16_t) 1;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(scalar_int16_bitwise, vbneg_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = ~zint16(100);
        auto expected = (int16_t) ~100;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_bitwise, vband_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(127) & zint16(64);
        auto expected = (int16_t) (127 & 64);

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_bitwise, vbor_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(127) | zint16(64);
        auto expected = (int16_t) (127 | 64);

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_bitwise, vbxor_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(127) ^ zint16(64);
        auto expected = (int16_t) (127 ^ 64);

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(scalar_int16_logical, vlor_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(0) || zint16(8);
        auto expected = (int16_t) 8;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_logical, vland_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(0) && zint16(8);
        auto expected = (int16_t) 0;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(scalar_int16_comparison, veq_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(0) == zint16(8);
        auto expected = (int16_t) 0;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_comparison, vneq_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(0) != zint16(0);
        auto expected = (int16_t) 0;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_comparison, vgt_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(0) > zint16(8);
        auto expected = (int16_t) 0;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_comparison, vlt_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = zint16(8) < zint16(0);
        auto expected = (int16_t) 0;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_comparison, vge_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = (zint16(0) >= zint16(0)).as_bool();
        auto expected = (int16_t) true;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

    TEST(scalar_int16_comparison, vle_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = (zint16(0) <= zint16(0)).as_bool();
        auto expected = (int16_t) true;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(scalar_int16_conditional, vsel_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        auto actual = vsel(zint16(1) == zint16(1), zint16(2), zint16(3));
        auto expected = (int16_t) 2;

        for(int16_t value : actual)
        {
            ASSERT_EQ(value, expected);
        }
    }

// =====================================================================================================================

}}