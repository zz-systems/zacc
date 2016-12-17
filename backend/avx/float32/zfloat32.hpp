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


        struct __zfloat32 : public zval<__m256, float, 8, 32> {
            __zfloat32(__m256 value)
                    : zval(value) {}

            __zfloat32(__m256d value)
                    : zval(_mm256_cvtpd_ps(value)) {}

            __zfloat32(__m256i value)
                    : zval(_mm256_cvtepi32_ps(value)) {}

            __zfloat32(float value)
                    : zval(_mm256_set1_ps(value)) {}

            __zfloat32(float *value)
                    : zval(_mm256_load_ps(value)) {}

            __zfloat32(float a, float b, float c, float d)
                    : zval(_mm256_set_ps(d, c, b, a)) {}
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