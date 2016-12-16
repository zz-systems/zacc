//
// Created by Sergej Zuyev on 12/13/2016.
//

#ifndef ZACC_LOGICAL_IMPL_HPP
#define ZACC_LOGICAL_IMPL_HPP

#include "../../common/compose.hpp"

namespace zacc {
    namespace scalar {
        template<typename aggregate_t>
        struct logical_policies {
            template<typename base_t>
            struct negate_policy : public base_t {
                FORWARD(negate_policy);

                friend aggregate_t operator!(const aggregate_t one) { return !one.get_value(); }
            };

            template<typename base_t>
            struct or_policy : public base_t {
                FORWARD(or_policy);

                friend aggregate_t operator||(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() || other._value;
                }
            };

            template<typename base_t>
            struct and_policy : public base_t {
                FORWARD(and_policy);

                friend aggregate_t operator&&(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() && other._value;
                }
            };

            template<typename base_t>
            struct compare_eq_policy : public base_t {
                FORWARD(compare_eq_policy);

                friend bool operator==(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() == other._value;
                }
            };

            template<typename base_t>
            struct compare_neq_policy : public base_t {
                FORWARD(compare_neq_policy);

                friend bool operator!=(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() != other._value;
                }
            };

            template<typename base_t>
            struct compare_gt_policy : public base_t {
                FORWARD(compare_gt_policy);

                friend bool operator>(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() > other._value;
                }
            };

            template<typename base_t>
            struct compare_lt_policy : public base_t {
                FORWARD(compare_lt_policy);

                friend bool operator<(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() < other._value;
                }
            };

            template<typename base_t>
            struct compare_ge_policy : public base_t {
                FORWARD(compare_ge_policy);

                friend bool operator>=(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() >= other._value;
                }
            };

            template<typename base_t>
            struct compare_le_policy : public base_t {
                FORWARD(compare_le_policy);

                friend bool operator<=(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() <= other._value;
                }
            };
        };
    }
}

#endif //ZACC_LOGICAL_IMPL_HPP
