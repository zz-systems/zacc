////---------------------------------------------------------------------------------
//// The MIT License (MIT)
////
//// Copyright (c) 2015-2018 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in all
//// copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//// SOFTWARE.
////---------------------------------------------------------------------------------
//
//#include "gtest/gtest.h"
//#include "system/arch.hpp"
//#include "math/complex.hpp"
//
//#include <cmath>
//#include "util/testing/gtest_ext.hpp"
//namespace zacc { namespace test {
//
//    using namespace math;
//
//    TEST(zfloat32_complex, add) {
//            REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//
//        math::zcomplex<zfloat> a { 1, 2 };
//        math::zcomplex<zfloat> b { 3, 4 };
//
//        auto actual1 = a + b;
//        math::zcomplex<zfloat> expected1 { 4, 6 };
//
//        VASSERT_EQ(actual1.real(), expected1.real());
//        VASSERT_EQ(actual1.imag(), expected1.imag());
///*
//        auto c = 3 + 4if;
//        auto d = 5 + 6if;
//
//        auto actual2 = c + d;
//        math::zcomplex<zfloat> expected2 { 8, 10 };
//
//        VASSERT_EQ(actual2.real(), expected2.real()) << "kebab";
//        VASSERT_EQ(actual2.imag(), expected2.imag());*/
//    }
//
//    TEST(zfloat32_complex, add2)
//    {
//        REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//
//        math::zcomplex<zfloat> a { make_index<zfloat>(1), make_index<zfloat>(2) };
//        math::zcomplex<zfloat> b { 3, 4 };
//
//        auto actual1 = a + b;
//        math::zcomplex<zfloat> expected1 { make_index<zfloat>(4), make_index<zfloat>(6) };
//
//        VASSERT_EQ(actual1.real(), expected1.real());
//        VASSERT_EQ(actual1.imag(), expected1.imag());
///*
//    auto c = 3 + 4if;
//    auto d = 5 + 6if;
//
//    auto actual2 = c + d;
//    math::zcomplex<zfloat> expected2 { 8, 10 };
//
//    VASSERT_EQ(actual2.real(), expected2.real()) << "kebab";
//    VASSERT_EQ(actual2.imag(), expected2.imag());*/
//    }
//    TEST(zfloat32_complex, sub) {
//            REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//
//        math::zcomplex<zfloat> a { 1, 2 };
//        math::zcomplex<zfloat> b { 3, 4 };
//
//        auto actual1 = a - b;
//        math::zcomplex<zfloat> expected1 { -2, -2 };
//
//        VASSERT_EQ(actual1.real(), expected1.real());
//        VASSERT_EQ(actual1.imag(), expected1.imag());
///*
//        auto c = 3 + 4if;
//        auto d = 5 + 6if;
//
//        auto actual2 = c - d;
//        math::zcomplex<zfloat>  expected2 { -2, -2 };
//
//        VASSERT_EQ(actual2.real(), expected2.real());
//        VASSERT_EQ(actual2.imag(), expected2.imag());
//    }
//
//    TEST(zfloat32_complex, mul) {
//        REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//
//        math::zcomplex<zfloat> a { 1, 2 };
//        math::zcomplex<zfloat> b { 3, 4 };
//
//        auto actual1 = a * b;
//        math::zcomplex<zfloat> expected1 { -5, 10 };
//
//        VASSERT_EQ(actual1.real(), expected1.real());
//        VASSERT_EQ(actual1.imag(), expected1.imag());
//
//        auto c = 3 + 4if;
//        auto d = 5 + 6if;
//
//        auto actual2 = c * d;
//        math::zcomplex<zfloat>  expected2 { -9, 38 };
//
//        VASSERT_EQ(actual2.real(), expected2.real());
//        VASSERT_EQ(actual2.imag(), expected2.imag());*/
//    }
//
//    TEST(zfloat32_complex, div) {
//            REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//
//        math::zcomplex<zfloat> a { 1, 2 };
//        math::zcomplex<zfloat> b { 3, 4 };
//
//        auto actual1 = a / b;
//        math::zcomplex<zfloat> expected1 { 0.44, 0.08 };
//
//        VASSERT_EQ(actual1.real(), expected1.real());
//        VASSERT_EQ(actual1.imag(), expected1.imag());
///*
//        auto c = 3 + 4if;
//        auto d = 5 + 6if;
//
//        auto actual2 = c / d;
//        math::zcomplex<zfloat>  expected2 { (39.0 / 61), (2.0/61) };
//
//        VASSERT_EQ(actual2.real(), expected2.real());
//        VASSERT_EQ(actual2.imag(), expected2.imag());*/
//    }
//
//    TEST(zfloat32_complex, init) {
//            REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//
//
//        vec2<zfloat> avec = 123;
//        vec2<float> bvec = 123;
//
//        math::zcomplex<zfloat> a = avec;
//
//        math::zcomplex<zfloat> b = static_cast<vec2<zfloat>>(bvec);
//
//        math::zcomplex<zfloat> c = 123;
//
//        math::zcomplex<zfloat> d = c;
//
////        math::zcomplex<zfloat> d = 123 + 456_i;
//
//
//        VASSERT_EQ(a.real(), 123);
//        VASSERT_EQ(a.imag(), 123);
//
//        VASSERT_EQ(b.real(), 123);
//        VASSERT_EQ(b.imag(), 123);
//
//        VASSERT_EQ(c.real(), 123);
//        VASSERT_EQ(c.imag(), 0);
//
//        VASSERT_EQ(d.real(), 123);
//        VASSERT_EQ(d.imag(), 0);
//
////        VASSERT_EQ(d.real(), 123);
////        VASSERT_EQ(d.imag(), 456);
//    /*
//        auto c = 3 + 4if;
//        auto d = 5 + 6if;
//
//        auto actual2 = c / d;
//        math::zcomplex<zfloat>  expected2 { (39.0 / 61), (2.0/61) };
//
//        VASSERT_EQ(actual2.real(), expected2.real());
//        VASSERT_EQ(actual2.imag(), expected2.imag());*/
//    }
//
//    TEST(zfloat32_complex, condition) {
//            REQUIRES(ZACC_ARCH);
//        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
//        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
//
//        math::zcomplex<zfloat> a { 1, 2 };
//        math::zcomplex<zfloat> b { 3, 4 };
//
//        math::zcomplex<zfloat> c00 {0, 0};
//        static_assert(is_cval<math::zcomplex<zfloat>>::value, "is_cval failed for math::zcomplex<zfloat>");
//        auto actual00 = a.when(c00).otherwise(b);
//
//        VASSERT_EQ(actual00.real(), b.real());
//        VASSERT_EQ(actual00.imag(), b.imag());
//
//        math::zcomplex<zfloat> c01 {0, 1};
//        auto actual01 = a.when(c01).otherwise(b);
//
//        VASSERT_EQ(actual01.real(), b.real());
//        VASSERT_EQ(actual01.imag(), a.imag());
//
//        math::zcomplex<zfloat> c10 {1, 0};
//        auto actual10 = a.when(c10).otherwise(b);
//
//        VASSERT_EQ(actual10.real(), a.real());
//        VASSERT_EQ(actual10.imag(), b.imag());
//
//        math::zcomplex<zfloat> c11 {1, 1};
//        auto actual11 = a.when(c11).otherwise(b);
//
//        VASSERT_EQ(actual11.real(), a.real());
//        VASSERT_EQ(actual11.imag(), a.imag());
//    }
//
//
////    TEST(float64_complex, sin) {
////        REQUIRES(ZACC_ARCH);
////        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
////        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
////        for (int i = -180; i <= 180; i++)
////        {
////            auto actual     = math::vsin(zdouble(i / 180.0 * M_PI));
////            zdouble expected   = std::sin(i / 180.0 * M_PI);
////
////            VEXPECT_NEAR(actual, expected, 0.00000006);
////        }
////    }
////
////    TEST(float64_complex, cos) {
////        REQUIRES(ZACC_ARCH);
////        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
////        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
////        for (int i = -180; i <= 180; i++)
////        {
////            auto actual     = math::vcos(zdouble(i / 180.0 * M_PI));
////            zdouble expected   = std::cos(i / 180.0 * M_PI);
////
////            VEXPECT_NEAR(actual, expected, 0.00000006);
////        }
////    }
////
////    TEST(float64_complex, tan) {
////        REQUIRES(ZACC_ARCH);
////        _MM_SET_ROUNDING_MODE(_MM_ROUND_TOWARD_ZERO);
////        _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
////        for (int i = -44; i <= 44; i++)
////        {
////            auto actual     = math::vtan(zdouble(i / 180.0 * M_PI));
////            zdouble expected   = std::tan(i / 180.0 * M_PI);
////
////            VEXPECT_NEAR(actual, expected, 0.00000006);
////        }
////    }
//}}
