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
#include "../common/printable.hpp"

namespace zacc {
    namespace sse {


        struct __zint8 : public zval<__m128i, char, 16, 16> {
            typedef zval<__m128i, char, 16, 16> base_t;

            __zint8(__m128i value) : base_t(value) {}

            __zint8(char value) : base_t(_mm_set1_epi8(value)) {}

            __zint8(char *value) : base_t(_mm_load_si128((__m128i *) value)) {}

            __zint16(char... args) : base_t(_mm_set_epi8(std::forward<char>(args)...)) {}
        };

        struct zint8;

        namespace i8 {
            using arithmetic    = int8_policies::arithmetic<zint8>;
            using common        = int8_policies::common<zint8>;
            using conditional   = int8_policies::conditional<zint8>;
            using bitwise       = int8_policies::bitwise<zint8>;
            using logical       = int8_policies::logical<zint8>;
        }

        struct zint8 : public compose<
                i8::arithmetic::negate_policy,
                i8::arithmetic::add_policy,
                i8::arithmetic::sub_policy,
                i8::arithmetic::mul_policy,
                i8::arithmetic::div_policy,

                printable,
                iteratable,
                extractable,
                i8::common::io_policy,

                i8::conditional::if_policy,

                i8::logical::negate_policy,
                i8::logical::or_policy,
                i8::logical::and_policy,

                i8::logical::compare_eq_policy,
                i8::logical::compare_neq_policy,
                i8::logical::compare_gt_policy,
                i8::logical::compare_lt_policy,
                i8::logical::compare_ge_policy,
                i8::logical::compare_le_policy,

                i8::bitwise::negate_policy,
                i8::bitwise::or_policy,
                i8::bitwise::and_policy,
                i8::bitwise::xor_policy,
                i8::bitwise::shift_left_policy,
                i8::bitwise::shift_right_policy,

                converting_arithmetic<zint8>::template inject,
                composable<__zint8>::template type> {
            FORWARD2(zint8, compose);
        };
    }
}