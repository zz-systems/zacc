//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------------


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
