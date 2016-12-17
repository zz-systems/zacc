//
// Created by Sergej Zuyev on 12/13/2016.
//

#pragma once

#include <immintrin.h>
//#include "../../../dispatch/dispatcher.hpp"
//#include "../../common/compose.hpp"

namespace zacc {
    namespace avx2 {
        namespace int8_policies {

            template<typename aggregate_t>
            struct bitwise {

                template<typename base_t>
                struct negate_policy : public base_t {
                    FORWARD(negate_policy);

                    friend aggregate_t operator~(const aggregate_t one) {
                        auto zero = _mm256_setzero_si256();
                        auto ones = _mm256_cmpeq_epi32(zero, zero);

                        return _mm256_xor_si256(one.get_value(), ones);
                    }
                };

                template<typename base_t>
                struct or_policy : public base_t {
                    FORWARD(or_policy);

                    friend aggregate_t operator|(const aggregate_t one, const aggregate_t other) {
                        return _mm256_or_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct and_policy : public base_t {
                    FORWARD(and_policy);

                    friend aggregate_t operator&(const aggregate_t one, const aggregate_t other) {
                        return _mm256_and_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct xor_policy : public base_t {
                    FORWARD(xor_policy);

                    friend aggregate_t operator^(const aggregate_t one, const aggregate_t other) {
                        return _mm256_xor_epi32(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct shift_left_policy : public base_t {
                    FORWARD(shift_left_policy);

                    friend aggregate_t operator<<(const aggregate_t one, const size_t shift_amount) {
                        return _mm256_slli_epi32(one.get_value(), shift_amount);
                    }

                    friend aggregate_t operator<<(const aggregate_t one, const aggregate_t shift_amount) {
                        return _mm256_sll_epi32(one.get_value(), shift_amount.get_value());
                    }
                };

                template<typename base_t>
                struct shift_right_policy : public base_t {
                    FORWARD(shift_right_policy);

                    friend aggregate_t operator>>(const aggregate_t one, const size_t shift_amount) {
                        return _mm256_srli_epi32(one.get_value(), shift_amount);
                    }

                    friend aggregate_t operator>>(const aggregate_t one, const aggregate_t shift_amount) {
                        return _mm256_srl_epi32(one.get_value(), shift_amount.get_value());
                    }
                };
            };
        }
    }
}