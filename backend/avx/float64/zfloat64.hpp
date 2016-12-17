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


#pragma once

#include "arithmetic.hpp"
#include "bitwise.hpp"
#include "conditional.hpp"
#include "common.hpp"
#include "logical.hpp"

namespace zacc {
    namespace avx {


        struct __zfloat64 : public zval<__m256d, double, 4, 32> {
            typedef zval<__m256d, double, 2, 16> base_t;

            __zfloat64(__m256 value) : base_t(_mm256_cvtps_pd(value)) {}

            __zfloat64(__m256d value) : base_t(value) {}

            __zfloat64(__m256i value) : base_t(_mm256_cvtepi32_pd(value)) {}

            __zfloat64(double value) : base_t(_mm256_set1_pd(value)) {}

            __zfloat64(double *value) : base_t(_mm256_load_pd(value)) {}

            __zfloat64(double a, double b) : base_t(_mm256_set_pd(a, b)) {}
        };

        struct zfloat64;

        namespace f64 {
            using arithmetic    = float64_policies::arithmetic<zfloat64>;
            using common        = float64_policies::common<zfloat64>;
            using conditional   = float64_policies::conditional<zfloat64>;
            using bitwise       = float64_policies::bitwise<zfloat64>;
            using logical       = float64_policies::logical<zfloat64>;
        }

        struct zfloat64 : public compose<
                f64::arithmetic::negate_policy,
                f64::arithmetic::add_policy,
                f64::arithmetic::sub_policy,
                f64::arithmetic::mul_policy,
                f64::arithmetic::div_policy,

                printable,
                iteratable,
                extractable,
                f64::common::io_policy,

                f64::conditional::if_policy,

                f64::logical::negate_policy,
                f64::logical::or_policy,
                f64::logical::and_policy,

                f64::logical::compare_eq_policy,
                f64::logical::compare_neq_policy,
                f64::logical::compare_gt_policy,
                f64::logical::compare_lt_policy,
                f64::logical::compare_ge_policy,
                f64::logical::compare_le_policy,

                f64::bitwise::negate_policy,
                f64::bitwise::or_policy,
                f64::bitwise::and_policy,
                f64::bitwise::xor_policy,

                converting_arithmetic<zfloat64>::template inject,
                composable<__zfloat64>::template type> {
            FORWARD2(zfloat64, compose);
        };
    }
}