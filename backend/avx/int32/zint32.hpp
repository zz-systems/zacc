//
// Created by Sergej Zuyev on 12/16/2016.
//

#pragma once

#include "arithmetic.hpp"
#include "bitwise.hpp"
#include "conditional.hpp"
#include "common.hpp"
#include "logical.hpp"

namespace zacc {
    namespace avx {


        struct __zint32 : public zval<__m256i, int, 8, 32> {
            typedef zval<__m256i, int, 4, 16> base_t;

            __zint32(__m256 value) : base_t(_mm256_cvtps_epi32(value)) {}

            __zint32(__m256d value) : base_t(_mm256_cvtpd_epi32(value)) {}

            __zint32(__m256i value) : base_t(value) {}

            __zint32(int value) : base_t(_mm256_set1_epi32(value)) {}

            __zint32(int *value) : base_t(_mm256_load_si256((__m256i *) value)) {}

            __zint32(int a, int b, int c, int d) : base_t(_mm256_set_epi32(d, b, c, a)) {}
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