//
// Created by Sergej Zuyev on 12/13/2016.
//

#ifndef ZACC_ARITHMETIC_IMPL_HPP
#define ZACC_ARITHMETIC_IMPL_HPP

#include "../../common/compose.hpp"
#include "../../common/type_traits.hpp"

namespace zacc {


    namespace scalar {

        template<typename aggregate_t>
        struct arithmetic_policies {
            template<typename base_t>
            struct negate_policy : public base_t {

                FORWARD(negate_policy);

                friend aggregate_t operator-(const aggregate_t one) { return -one.get_value(); }
            };

            template<typename base_t>
            struct add_policy : public base_t {

                FORWARD(add_policy);

                friend aggregate_t operator+(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() + other.get_value();
                }
            };

            template<typename base_t>
            struct sub_policy : public base_t {

                FORWARD(sub_policy);

                friend aggregate_t operator-(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() - other.get_value();
                }
            };

            template<typename base_t>
            struct mul_policy : public base_t {
                FORWARD(mul_policy);

                friend aggregate_t operator*(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() * other.get_value();
                }
            };

            template<typename base_t>
            struct div_policy : public base_t {

                FORWARD(div_policy);

                friend aggregate_t operator/(const aggregate_t one, const aggregate_t other) {
                    return one.get_value() / other.get_value();
                }
            };
        };
    }
}
#endif //ZACC_ARITHMETIC_IMPL_HPP
