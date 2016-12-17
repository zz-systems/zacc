//
// Created by Sergej Zuyev on 12/13/2016.
//

#pragma once

#include <immintrin.h>
#include "../../../common/compose.hpp"

namespace zacc {
    namespace avx {
        namespace float64_policies {

            template<typename aggregate_t>
            struct logical {
                template<typename base_t>
                struct negate_policy : public base_t {
                    FORWARD(negate_policy);

                    friend
                    aggregate_t
                    operator!(const aggregate_t one) {
                        auto zero = _mm256_setzero_pd();
                        auto ones = _mm256_cmpeq_pd(zero, zero);

                        return _mm256_xor_pd(one.get_value(), ones);
                    }
                };

                template<typename base_t>
                struct or_policy : public base_t {
                    FORWARD(or_policy);

                    friend
                    aggregate_t
                    operator||(const aggregate_t one, const aggregate_t other) {
                        return _mm256_or_pd(one.get_value(), other._value);
                    }
                };

                template<typename base_t>
                struct and_policy : public base_t {
                    FORWARD(and_policy);

                    friend
                    aggregate_t
                    operator&&(const aggregate_t one, const aggregate_t other) {
                        return _mm256_and_pd(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_eq_policy : public base_t {
                    FORWARD(compare_eq_policy);

                    friend
                    aggregate_t
                    operator==(const aggregate_t one, const aggregate_t other) {
                        return _mm256_cmpeq_pd(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_neq_policy : public base_t {
                    FORWARD(compare_neq_policy);

                    friend
                    aggregate_t
                    operator!=(const aggregate_t one, const aggregate_t other) {
                        return _mm256_cmpneq_pd(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_gt_policy : public base_t {
                    FORWARD(compare_gt_policy);

                    friend
                    aggregate_t
                    operator>(const aggregate_t one, const aggregate_t other) {
                        return _mm256_cmpgt_pd(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_lt_policy : public base_t {
                    FORWARD(compare_lt_policy);

                    friend
                    aggregate_t
                    operator<(const aggregate_t one, const aggregate_t other) {
                        return _mm256_cmplt_pd(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_ge_policy : public base_t {
                    FORWARD(compare_ge_policy);

                    friend
                    aggregate_t
                    operator>=(const aggregate_t one, const aggregate_t other) {
                        return _mm256_cmpge_pd(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct compare_le_policy : public base_t {
                    FORWARD(compare_le_policy);

                    friend
                    aggregate_t
                    operator<=(const aggregate_t one, const aggregate_t other) {
                        return _mm256_cmple_pd(one.get_value(), other.get_value());
                    }
                };
            };
        }
    }
}