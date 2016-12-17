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
    namespace sse {


        struct __zfloat32 : public zval<__m128, float, 4, 16> {
            __zfloat32(__m128 value)
                    : zval(value) {}

            __zfloat32(__m128d value)
                    : zval(_mm_cvtpd_ps(value)) {}

            __zfloat32(__m128i value)
                    : zval(_mm_cvtepi32_ps(value)) {}

            __zfloat32(float value)
                    : zval(_mm_set1_ps(value)) {}

            __zfloat32(float *value)
                    : zval(_mm_load_ps(value)) {}

            __zfloat32(float a, float b, float c, float d)
                    : zval(_mm_set_ps(d, c, b, a)) {}
        };


        struct zfloat32;

        namespace f32 {
            using arithmetic    = float32_policies::arithmetic<zfloat32>;
            using common        = float32_policies::common<zfloat32>;
            using conditional   = float32_policies::conditional<zfloat32>;
            using bitwise       = float32_policies::bitwise<zfloat32>;
            using logical       = float32_policies::logical<zfloat32>;
        }

        struct zfloat32 : public compose<
                f32::arithmetic::negate_policy,
                f32::arithmetic::add_policy,
                f32::arithmetic::sub_policy,
                f32::arithmetic::mul_policy,
                f32::arithmetic::div_policy,

                printable,
                iteratable,
                extractable,
                f32::common::io_policy,

                f32::conditional::if_policy,

                f32::logical::negate_policy,
                f32::logical::or_policy,
                f32::logical::and_policy,

                f32::logical::compare_eq_policy,
                f32::logical::compare_neq_policy,
                f32::logical::compare_gt_policy,
                f32::logical::compare_lt_policy,
                f32::logical::compare_ge_policy,
                f32::logical::compare_le_policy,

                f32::bitwise::negate_policy,
                f32::bitwise::or_policy,
                f32::bitwise::and_policy,
                f32::bitwise::xor_policy,

                converting_arithmetic<zfloat32>::template inject,
                composable<__zfloat32>::template type> {
            FORWARD2(zfloat32, compose);
        };
    }
}