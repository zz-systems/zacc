//
// Created by Sergej Zuyev on 12/16/2016.
//

#pragma once

namespace zacc {
    namespace avx {
        namespace float64_policies {

            template<typename aggregate_t>
            struct arithmetic {

                template<typename base_t>
                struct negate_policy : public base_t {

                    FORWARD(negate_policy);

                    friend aggregate_t operator-(const aggregate_t one) {
                        return _mm256_sub_ps(_mm256_setzero_ps(), one.get_value());
                    }
                };

                template<typename base_t>
                struct add_policy : public base_t {

                    FORWARD(add_policy);

                    friend aggregate_t operator+(const aggregate_t one, const aggregate_t other) {
                        return _mm256_add_ps(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct sub_policy : public base_t {

                    FORWARD(sub_policy);

                    friend aggregate_t operator-(const aggregate_t one, const aggregate_t other) {
                        return _mm256_sub_ps(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct mul_policy : public base_t {
                    FORWARD(mul_policy);

                    friend aggregate_t operator*(const aggregate_t one, const aggregate_t other) {
                        return _mm256_mul_ps(one.get_value(), other.get_value());
                    }
                };

                template<typename base_t>
                struct div_policy : public base_t {

                    FORWARD(div_policy);

                    friend aggregate_t operator/(const aggregate_t one, const aggregate_t other) {
                        return _mm256_div_ps(one.get_value(), other.get_value());
                    }
                };
            };
        }
    }
}