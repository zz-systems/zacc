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

#include "common.hpp"

namespace zacc { namespace traits {

    /**
     * @brief provides arithmetic operator definitions
     * @tparam base_t base type (e.g previous trait)
     * @tparam composed_t final composed type (e.g zfloat32)
     */
    template<typename base_t, typename composed_t>
    struct arithmetic : public base_t {
        FORWARD(arithmetic);

        using zval_t = typename base_t::zval_t;
        using bval_t = typename base_t::bval_t;

        /**
         * @brief promotion operator for symmetry sake
         * @param one
         * @return a copy of the argument
         */
        composed_t operator+() {
            return *this;
        }

        /**
         * @brief negation operator
         * @param one
         * @return negated value
         */
        composed_t operator-() {
            return vneg(*this);
        }

        /**
         * @brief addition operator
         * @param one
         * @param other
         * @return one + other
         */
        composed_t operator+(const composed_t other) {
            return vadd(*this, other);
        }

        /**
         * @brief addition operator
         * @param one
         * @param other
         * @return one + other
         */
        composed_t &operator+=(const composed_t other) {
            return *this = *this + other;
        }

        /**
         * @brief addition operator
         * @param one
         * @param other
         * @return one + other
         */
        composed_t &operator-=(const composed_t other) {
            return *this = *this - other;
        }

        /**
         * @brief addition operator
         * @param one
         * @param other
         * @return one + other
         */
        composed_t &operator*=(const composed_t other) {
            return *this = *this * other;
        }

        /**
         * @brief addition operator
         * @param one
         * @param other
         * @return one + other
         */
        composed_t &operator/=(const composed_t other) {
            return *this = *this / other;
        }

        /**
         * @brief addition operator
         * @param one
         * @param other
         * @return one + other
         */
        composed_t &operator%=(const composed_t other) {
            return *this = *this % other;
        }

        /**
         * @brief subtration operator
         * @param one
         * @param other
         * @return one - other
         */
        composed_t operator-(const composed_t other) {
            return vsub(*this, other);
        }

        /**
         * @brief multiplication operator
         * @param one
         * @param other
         * @return one * other
         */
        composed_t operator*(const composed_t other) {
            return vmul(*this, other);
        }

        /**
         * @brief division operator
         * @param one
         * @param other
         * @return one / other
         */
        composed_t operator/(const composed_t other) {
            return vdiv(*this, other);
        }

        /**
         * @brief modulus operator
         * @param one
         * @param other
         * @return one % other
         */
        composed_t operator%(const composed_t other) {
            return vmod(*this, other);
        }


        /**
         * @brief prefix increment
         * @return self + 1
         */
        composed_t &operator++() {
            return vadd(*this, 1);
        }

        /**
         * @brief postfix increment
         * @return self
         */
        composed_t operator++(int) {
            auto temp = *this;

            ++(*this);

            return temp;
        }

        /**
         * @brief prefix decrement
         * @return self - 1
         */
        composed_t &operator--() {
            return vsub(*this, 1);
        }

        /**
         * @brief postfix decrement
         * @return self
         */
        composed_t operator--(int) {
            auto temp = *this;

            --(*this);

            return temp;
        }

        CONVERSION(+);
        //ASSIGNMENT(+);

        CONVERSION(-);
        //ASSIGNMENT(-);

        CONVERSION(*);
        //ASSIGNMENT(*);

        CONVERSION(/);
        //ASSIGNMENT(/);
    };
}}