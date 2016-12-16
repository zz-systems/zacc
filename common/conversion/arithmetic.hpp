//
// Created by Sergej Zuyev on 12/12/2016.
//

#ifndef ZACC_CONVERSION_ARITHMETIC_HPP
#define ZACC_CONVERSION_ARITHMETIC_HPP

#include "../compose.hpp"
#include "../zval.hpp"
#include "../type_traits.hpp"

namespace zacc {
    template<typename aggregate_t>
    struct converting_arithmetic {

        template<typename base_t>
        struct inject : base_t {

            FORWARD(inject);

            template<typename other_t>
            friend aggregate_t operator+(const aggregate_t one, const enable_if_not_same<other_t, aggregate_t> other) {
                return one + static_cast<aggregate_t>(other);
            };

            template<typename other_t>
            friend aggregate_t operator+(const enable_if_not_same<other_t, aggregate_t> one, const aggregate_t other) {
                return static_cast<aggregate_t>(one) + other;
            };

            template<typename other_t>
            friend aggregate_t operator-(const aggregate_t one, const enable_if_not_same<other_t, aggregate_t> other) {
                return one - static_cast<aggregate_t>(other);
            };

            template<typename other_t>
            friend aggregate_t operator-(const enable_if_not_same<other_t, aggregate_t> one, const aggregate_t other) {
                return static_cast<aggregate_t>(one) - other;
            };


            template<typename other_t>
            friend aggregate_t operator*(const aggregate_t one, const enable_if_not_same<other_t, aggregate_t> other) {
                return one * static_cast<aggregate_t>(other);
            };

            template<typename other_t>
            friend aggregate_t operator*(const enable_if_not_same<other_t, aggregate_t> one, const aggregate_t other) {
                return static_cast<aggregate_t>(one) * other;
            };


            template<typename other_t>
            friend aggregate_t operator/(const zval_base one, const enable_if_not_same<other_t, aggregate_t> other) {
                return one / static_cast<aggregate_t>(other);
            };

            template<typename other_t>
            friend aggregate_t operator/(const enable_if_not_same<other_t, aggregate_t> one, const zval_base other) {
                return static_cast<aggregate_t>(one) / other;
            };
        };
    };
}

#endif //ZACC_CONVERSION_ARITHMETIC_HPP
