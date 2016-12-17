//
// Created by Sergej Zuyev on 12/13/2016.
//

#pragma once

#include <immintrin.h>
//#include "../../../dispatch/dispatcher.hpp"
//#include "../../common/compose.hpp"

namespace zacc {
    namespace avx {
        namespace float32_policies {

            template<typename aggregate_t>
            struct bitwise {

                template<typename base_t>
                struct negate_policy : public base_t {
                    FORWARD(negate_policy);

                    friend aggregate_t operator~(const aggregate_t one) {
                        auto zero = _mm256_setzero_ps();
                        auto ones = _mm256_cmpeq_ps(zero, zero);

                        return _mm256_xor_ps(one.get_value(), ones);
                    }
                };

                template<typename base_t>
                struct or_policy : public base_t {
                    FORWARD(or_policy);

                    friend aggregate_t operator|(const aggregate_t one, const aggregate_t other) {
                        return _mm256_or_ps(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct and_policy : public base_t {
                    FORWARD(and_policy);

                    friend aggregate_t operator&(const aggregate_t one, const aggregate_t other) {
                        return _mm256_and_ps(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct xor_policy : public base_t {
                    FORWARD(xor_policy);

                    friend aggregate_t operator^(const aggregate_t one, const aggregate_t other) {
                        return _mm256_xor_ps(one.get_value(), other.get_value());
                    }
                };
            };
        }
    }
}