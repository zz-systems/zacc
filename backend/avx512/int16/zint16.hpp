//
// Created by Sergej Zuyev on 12/16/2016.
//

#pragma once

#include "arithmetic.hpp"
#include "bitwise.hpp"
#include "conditional.hpp"
#include "common.hpp"
#include "logical.hpp"
#include "../common/printable.hpp"

namespace zacc {
    namespace avx {


        struct __zint16 : public zval<__m512i, short, 16, 32> {
            typedef zval<__m512i, short, 8, 16> base_t;

            __zint16(__m512 value) : base_t(_mm512_cvtps_epi16(value)) {}

            __zint16(__m512d value) : base_t(_mm512_cvtpd_epi16(value)) {}

            __zint16(__m512i value) : base_t(value) {}

            __zint16(short value) : base_t(_mm512_set1_epi16(value)) {}

            __zint16(short *value) : base_t(_mm512_load_si512((__m512i *) value)) {}

            __zint16(short... args) : base_t(_mm512_set_epi16(std::forward<short>(args)...)) {}
        };

        struct zint16;

        namespace i16 {
            using arithmetic    = int16_policies::arithmetic<zint16>;
            using common        = int16_policies::common<zint16>;
            using conditional   = int16_policies::conditional<zint16>;
            using bitwise       = int16_policies::bitwise<zint16>;
            using logical       = int16_policies::logical<zint16>;
        }

        struct zint16 : public compose<
                i16::arithmetic::negate_policy,
                i16::arithmetic::add_policy,
                i16::arithmetic::sub_policy,
                i16::arithmetic::mul_policy,
                i16::arithmetic::div_policy,

                printable,
                iteratable,
                extractable,
                i16::common::io_policy,

                i16::conditional::if_policy,

                i16::logical::negate_policy,
                i16::logical::or_policy,
                i16::logical::and_policy,

                i16::logical::compare_eq_policy,
                i16::logical::compare_neq_policy,
                i16::logical::compare_gt_policy,
                i16::logical::compare_lt_policy,
                i16::logical::compare_ge_policy,
                i16::logical::compare_le_policy,

                i16::bitwise::negate_policy,
                i16::bitwise::or_policy,
                i16::bitwise::and_policy,
                i16::bitwise::xor_policy,
                i16::bitwise::shift_left_policy,
                i16::bitwise::shift_right_policy,

                converting_arithmetic<zint16>::template inject,
                composable<__zint16>::template type> {
            FORWARD2(zint16, compose);
        };
    }
}