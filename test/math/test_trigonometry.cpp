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
#include "system/arch.hpp"
#include "math/trigonometry.hpp"

#include <cmath>
#include "util/testing/gtest_ext.hpp"

namespace zacc { namespace test {

    TEST(float32_trigonometry, sin) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        for (int i = -180; i <= 180; i++)
        {
            auto actual     = math::vsin(zfloat(i / 180.0f * M_PI));
            zfloat expected   = std::sin(i / 180.0f * M_PI);

            VASSERT_NEAR(actual, expected, 0.004);
        }
    }

    TEST(float32_trigonometry, cos) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        for (int i = -180; i <= 180; i++)
        {
            auto actual     = math::vcos(zfloat(i / 180.0f * M_PI));
            zfloat expected   = std::cos(i / 180.0f * M_PI);

            VASSERT_NEAR(actual, expected, 0.004);
        }
    }

    TEST(float32_trigonometry, tan) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        for (int i = -45; i <= 45; i++)
        {
            auto actual     = math::vtan(zfloat(i / 180.0f * M_PI));
            zfloat expected   = std::tan(i / 180.0f * M_PI);

            VASSERT_NEAR(actual, expected, 0.004);
        }
    }

    TEST(float64_trigonometry, sin) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        for (int i = -180; i <= 180; i++)
        {
            auto actual     = math::vsin(zdouble(i / 180.0 * M_PI));
            zdouble expected   = std::sin(i / 180.0 * M_PI);

            VASSERT_NEAR(actual, expected, 0.00000006);
        }
    }

    TEST(float64_trigonometry, cos) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        for (int i = -180; i <= 180; i++)
        {
            auto actual     = math::vcos(zdouble(i / 180.0 * M_PI));
            zdouble expected   = std::cos(i / 180.0 * M_PI);

            VASSERT_NEAR(actual, expected, 0.00000006);
        }
    }

    TEST(float64_trigonometry, tan) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
        for (int i = -44; i <= 44; i++)
        {
            auto actual     = math::vtan(zdouble(i / 180.0 * M_PI));
            zdouble expected   = std::tan(i / 180.0 * M_PI);

            VASSERT_NEAR(actual, expected, 0.00000006);
        }
    }
}}
