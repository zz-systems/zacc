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
#include <random>

namespace zacc { namespace test {

// =====================================================================================================================
    TEST(avx_float64_arithmetic, vneg_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (-a[i]);
        }

        VASSERT_EQ((-zfloat64(a)), zfloat64(expected));
    }

    TEST(avx_float64_arithmetic, vadd_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (a[i] + b[i]);
        }

        VASSERT_EQ((zfloat64(a) + zfloat64(b)), zfloat64(expected));
    }

    TEST(avx_float64_arithmetic, vsub_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (a[i] - b[i]);
        }

        VASSERT_EQ((zfloat64(a) - zfloat64(b)), zfloat64(expected));
    }

    TEST(avx_float64_arithmetic, vmul_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (a[i] * b[i]);
        }

        VASSERT_EQ((zfloat64(a) * zfloat64(b)), zfloat64(expected));
    }

    TEST(avx_float64_arithmetic, vdiv_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (1);
        }

        VASSERT_EQ((zfloat64(a) / zfloat64(a)), zfloat64(expected));
    }

// =====================================================================================================================
// =====================================================================================================================
// =====================================================================================================================
// =====================================================================================================================
    TEST(avx_float64_logical, vlneg_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (false);
        }

        VASSERT_EQ(((!zfloat64(a)).as_bool()), zfloat64(expected));
    }

    TEST(avx_float64_logical, vlor_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (true);
        }

        VASSERT_EQ(((zfloat64(0) || zfloat64(a)).as_bool()), zfloat64(expected));
    }

    TEST(avx_float64_logical, vland_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (false);
        }

        VASSERT_EQ(((zfloat64(0) && zfloat64(a)).as_bool()), zfloat64(expected));
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(avx_float64_comparison, veq_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (0);
        }

        VASSERT_EQ((zfloat64(0) == zfloat64(a)), zfloat64(expected));
    }

    TEST(avx_float64_comparison, vneq_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (0);
        }

        VASSERT_EQ((zfloat64(a) != zfloat64(a)), zfloat64(expected));
    }

    TEST(avx_float64_comparison, vgt_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (0);
        }

        VASSERT_EQ((zfloat64(0) > zfloat64(a)), zfloat64(expected));
    }

    TEST(avx_float64_comparison, vlt_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (0);
        }

        VASSERT_EQ((zfloat64(a) < zfloat64(0)), zfloat64(expected));
    }

    TEST(avx_float64_comparison, vge_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (true);
        }

        VASSERT_EQ(((zfloat64(b) >= zfloat64(b)).as_bool()), zfloat64(expected));
    }

    TEST(avx_float64_comparison, vle_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (true);
        }

        VASSERT_EQ(((zfloat64(b) <= zfloat64(b)).as_bool()), zfloat64(expected));
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(avx_float64_conditional, vsel_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        std::array<double, 4> a, b, expected;
        for(int i = 0; i < 4; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);

            expected[i] = (double) (2);
        }

        VASSERT_EQ((vsel(zfloat64(1) == zfloat64(1), zfloat64(2), zfloat64(3))), zfloat64(expected));
    }

// =====================================================================================================================

}}