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
    TEST(avx_float32_arithmetic, vneg_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (-zfloat32(a)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (-a[i]);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_arithmetic, vadd_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (zfloat32(a) + zfloat32(b)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (a[i] + b[i]);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_arithmetic, vsub_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (zfloat32(a) - zfloat32(b)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (a[i] - b[i]);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_arithmetic, vmul_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (zfloat32(a) * zfloat32(b)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (a[i] * b[i]);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_arithmetic, vdiv_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (zfloat32(a) / zfloat32(a)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (1);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
// =====================================================================================================================
// =====================================================================================================================
    TEST(avx_float32_logical, vlneg_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = ((!zfloat32(a)).as_bool()).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (false);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_logical, vlor_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = ((zfloat32(0) || zfloat32(a)).as_bool()).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (true);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_logical, vland_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = ((zfloat32(0) && zfloat32(a)).as_bool()).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (false);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(avx_float32_comparison, veq_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (zfloat32(0) == zfloat32(a)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (0);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_comparison, vneq_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (zfloat32(a) != zfloat32(a)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (0);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_comparison, vgt_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (zfloat32(0) > zfloat32(a)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (0);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_comparison, vlt_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (zfloat32(a) < zfloat32(0)).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (0);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_comparison, vge_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = ((zfloat32(b) >= zfloat32(b)).as_bool()).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (true);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

    TEST(avx_float32_comparison, vle_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = ((zfloat32(b) <= zfloat32(b)).as_bool()).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (true);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

// =====================================================================================================================
// =====================================================================================================================
    TEST(avx_float32_conditional, vsel_default)
    {
        REQUIRES(ZACC_CAPABILITIES);

        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution1(1, 3);
        std::uniform_int_distribution<int> distribution2(3, 60);

        float a[8], b[8];
        for(int i = 0; i < 8; i++)
        {
            a[i] = distribution2(generator);
            b[i] = distribution1(generator);
        }

        auto actual = (vsel(zfloat32(1) == zfloat32(1), zfloat32(2), zfloat32(3))).data();


        for(int i = 0; i < 8; i++)
        {
            auto value = actual[i];
            auto expected = (float) (2);

            ASSERT_FLOAT_EQ(value, expected);
        }
    }

// =====================================================================================================================

}}