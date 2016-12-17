//
// Created by Sergej Zuyev on 12/13/2016.
//

#ifndef ZACC_BITWISE_IMPL_HPP
#define ZACC_BITWISE_IMPL_HPP

#include "../../common/compose.hpp"

namespace zacc {
    namespace scalar {

        template<typename aggregate_t>
        struct bitwise_policies {
            template<typename base_t>
            struct negate_policy : public base_t {
                FORWARD(negate_policy);

                friend aggregate_t operator~(const aggregate_t one) { return ~one.get_value(); }
            };

            template<typename base_t>
            struct or_policy : public base_t {
                FORWARD(or_policy);

                friend aggregate_t operator|(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() | other._value;
                }
            };

            template<typename base_t>
            struct and_policy : public base_t {
                FORWARD(and_policy);

                friend aggregate_t operator&(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() & other._value;
                }
            };

            template<typename base_t>
            struct xor_policy : public base_t {
                FORWARD(xor_policy);

                friend aggregate_t operator^(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() ^ other._value;
                }
            };

            template<typename base_t>
            struct shift_left_policy : public base_t {
                FORWARD(shift_left_policy);

                friend aggregate_t operator<<(const aggregate_t one, const size_t shift_amount) {
                    return one.get_value() << shift_amount;
                }
            };

            template<typename base_t>
            struct shift_right_policy : public base_t {
                FORWARD(shift_right_policy);

                friend aggregate_t operator>>(const aggregate_t one, const size_t shift_amount) {
                    return one.get_value() >> shift_amount;
                }
            };
        };
    }
}
#endif //ZACC_BITWISE_IMPL_HPP
