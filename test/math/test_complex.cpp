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
#include "system/branch.hpp"
#include "math/complex.hpp"

#include <cmath>
#include "util/testing/gtest_ext.hpp"
namespace zacc { namespace test {

    using namespace math;

    TEST(zfloat32_complex, add) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        math::zcomplex<zfloat> a { 1, 2 };
        math::zcomplex<zfloat> b { 3, 4 };

        auto actual1 = a + b;
        math::zcomplex<zfloat> expected1 { 4, 6 };

        VASSERT_EQ(actual1.real(), expected1.real());
        VASSERT_EQ(actual1.imag(), expected1.imag());

        auto c = 3 + 4if;
        auto d = 5 + 6if;

        auto actual2 = c + d;
        math::zcomplex<zfloat> expected2 { 8, 10 };

        VASSERT_EQ(actual2.real(), expected2.real()) << "kebab";
        VASSERT_EQ(actual2.imag(), expected2.imag());
    }

    TEST(zfloat32_complex, sub) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        math::zcomplex<zfloat> a { 1, 2 };
        math::zcomplex<zfloat> b { 3, 4 };

        auto actual1 = a - b;
        math::zcomplex<zfloat> expected1 { -2, -2 };

        VASSERT_EQ(actual1.real(), expected1.real());
        VASSERT_EQ(actual1.imag(), expected1.imag());

        auto c = 3 + 4if;
        auto d = 5 + 6if;

        auto actual2 = c - d;
        math::zcomplex<zfloat>  expected2 { -2, -2 };

        VASSERT_EQ(actual2.real(), expected2.real());
        VASSERT_EQ(actual2.imag(), expected2.imag());
    }

    TEST(zfloat32_complex, mul) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        math::zcomplex<zfloat> a { 1, 2 };
        math::zcomplex<zfloat> b { 3, 4 };

        auto actual1 = a * b;
        math::zcomplex<zfloat> expected1 { -5, 10 };

        VASSERT_EQ(actual1.real(), expected1.real());
        VASSERT_EQ(actual1.imag(), expected1.imag());

        auto c = 3 + 4if;
        auto d = 5 + 6if;

        auto actual2 = c * d;
        math::zcomplex<zfloat>  expected2 { -9, 38 };

        VASSERT_EQ(actual2.real(), expected2.real());
        VASSERT_EQ(actual2.imag(), expected2.imag());
    }

    TEST(zfloat32_complex, div) {
        REQUIRES(ZACC_ARCH);
        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);

        math::zcomplex<zfloat> a { 1, 2 };
        math::zcomplex<zfloat> b { 3, 4 };

        auto actual1 = a / b;
        math::zcomplex<zfloat> expected1 { 0.44, 0.08 };

        VASSERT_EQ(actual1.real(), expected1.real());
        VASSERT_EQ(actual1.imag(), expected1.imag());

        auto c = 3 + 4if;
        auto d = 5 + 6if;

        auto actual2 = c / d;
        math::zcomplex<zfloat>  expected2 { (39.0 / 61), (2.0/61) };

        VASSERT_EQ(actual2.real(), expected2.real());
        VASSERT_EQ(actual2.imag(), expected2.imag());
    }

//    TEST(float64_complex, sin) {
//        REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//        for (int i = -180; i <= 180; i++)
//        {
//            auto actual     = math::vsin(zdouble(i / 180.0 * M_PI));
//            zdouble expected   = std::sin(i / 180.0 * M_PI);
//
//            VEXPECT_NEAR(actual, expected, 0.00000006);
//        }
//    }
//
//    TEST(float64_complex, cos) {
//        REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//        for (int i = -180; i <= 180; i++)
//        {
//            auto actual     = math::vcos(zdouble(i / 180.0 * M_PI));
//            zdouble expected   = std::cos(i / 180.0 * M_PI);
//
//            VEXPECT_NEAR(actual, expected, 0.00000006);
//        }
//    }
//
//    TEST(float64_complex, tan) {
//        REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//        for (int i = -44; i <= 44; i++)
//        {
//            auto actual     = math::vtan(zdouble(i / 180.0 * M_PI));
//            zdouble expected   = std::tan(i / 180.0 * M_PI);
//
//            VEXPECT_NEAR(actual, expected, 0.00000006);
//        }
//    }
}}