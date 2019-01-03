//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2015-2018 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include "util/operators.hpp"

namespace zacc { namespace traits {

    /**
     * @brief provides arithmetic operator definitions
     * @tparam Base base type (e.g previous trait)
     * @tparam Composed final composed type (e.g zfloat32)
     */
    template<typename Interface, typename Composed, typename Boolean>
    struct arithmetic : inherit<ops_meta<Composed, Interface>, plus, minus, multiplies, divides, modulus, increment, decrement>
    {
        /**
         * @brief promotion operator for symmetry sake
         * @param one
         * @return a copy of the argument
         */
        friend Composed operator+(param_t<Composed> self) {
            return self;
        }

        /**
         * @brief negation operator
         * @param one
         * @return negated value
         */
        friend Composed operator-(param_t<Composed> self) {
            return vneg(self);
        }

        /**
         * @brief addition operator
         * @param one
         * @param other
         * @return one + other
         */
        friend Composed operator+(param_t<Composed> one, param_t<Composed> other) {
            return vadd(one, other);
        }

        /**
         * @brief subtration operator
         * @param one
         * @param other
         * @return one - other
         */
        friend Composed operator-(param_t<Composed> one, param_t<Composed> other) {
            return vsub(one, other);
        }

        /**
         * @brief multiplication operator
         * @param one
         * @param other
         * @return one * other
         */
        friend Composed operator*(param_t<Composed> one, param_t<Composed> other) {
            return vmul(one, other);
        }

        /**
         * @brief division operator
         * @param one
         * @param other
         * @return one / other
         */
        friend Composed operator/(param_t<Composed> one, param_t<Composed> other) {
            return vdiv(one, other);
        }

        /**
         * @brief modulus operator
         * @param one
         * @param other
         * @return one % other
         */
        friend Composed operator%(param_t<Composed> one, param_t<Composed> other) {
            return vmod(one, other);
        }

        /**
         * @brief prefix increment
         * @return self + 1
         */
        friend Composed& operator++(Composed& self) {
            return vadd(self, 1);
        }

        /**
         * @brief prefix decrement
         * @return self - 1
         */
        friend Composed& operator--(Composed& self) {
            return vsub(self, 1);
        }
    };
}}