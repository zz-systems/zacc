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


#pragma once

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