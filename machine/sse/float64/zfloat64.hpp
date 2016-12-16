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
    namespace sse {


        struct __zfloat64 : public zval<__m128d, double, 2, 16> {
            typedef zval<__m128d, double, 2, 16> base_t;

            __zfloat64(__m128 value) : base_t(_mm_cvtps_pd(value)) {}

            __zfloat64(__m128d value) : base_t(value) {}

            __zfloat64(__m128i value) : base_t(_mm_cvtepi32_pd(value)) {}

            __zfloat64(double value) : base_t(_mm_set1_pd(value)) {}

            __zfloat64(double *value) : base_t(_mm_load_pd(value)) {}

            __zfloat64(double a, double b) : base_t(_mm_set_pd(a, b)) {}
        };

        struct zfloat64;

        namespace f64 {
            using arithmetic    = float64_policies::arithmetic<zfloat64>;
            using commonf64     = float64_policies::common<zfloat64>;
            using common        = common_policies::common<zfloat64>;
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

                f64::common::print_policy,
                f64::commonf64::extract_policy,

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