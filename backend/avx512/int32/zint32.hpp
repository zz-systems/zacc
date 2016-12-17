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


        struct __zint32 : public zval<__m512i, int, 8, 32> {
            typedef zval<__m512i, int, 4, 16> base_t;

            __zint32(__m512 value) : base_t(_mm512_cvtps_epi32(value)) {}

            __zint32(__m512d value) : base_t(_mm512_cvtpd_epi32(value)) {}

            __zint32(__m512i value) : base_t(value) {}

            __zint32(int value) : base_t(_mm512_set1_epi32(value)) {}

            __zint32(int *value) : base_t(_mm512_load_si512((__m512i *) value)) {}

            __zint32(int a, int b, int c, int d) : base_t(_mm512_set_epi32(d, b, c, a)) {}
        };

        struct zint32;

        namespace i32 {
            using arithmetic    = int32_policies::arithmetic<zint32>;
            using common        = int32_policies::common<zint32>;
            using conditional   = int32_policies::conditional<zint32>;
            using bitwise       = int32_policies::bitwise<zint32>;
            using logical       = int32_policies::logical<zint32>;
        }

        struct zint32 : public compose<
                i32::arithmetic::negate_policy,
                i32::arithmetic::add_policy,
                i32::arithmetic::sub_policy,
                i32::arithmetic::mul_policy,
                i32::arithmetic::div_policy,

                printable,
                iteratable,
                extractable,
                i32::common::io_policy,

                i32::conditional::if_policy,

                i32::logical::negate_policy,
                i32::logical::or_policy,
                i32::logical::and_policy,

                i32::logical::compare_eq_policy,
                i32::logical::compare_neq_policy,
                i32::logical::compare_gt_policy,
                i32::logical::compare_lt_policy,
                i32::logical::compare_ge_policy,
                i32::logical::compare_le_policy,

                i32::bitwise::negate_policy,
                i32::bitwise::or_policy,
                i32::bitwise::and_policy,
                i32::bitwise::xor_policy,
                i32::bitwise::shift_left_policy,
                i32::bitwise::shift_right_policy,

                converting_arithmetic<zint32>::template inject,
                composable<__zint32>::template type> {
            FORWARD2(zint32, compose);
        };
    }
}