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

namespace zacc { namespace interface {

    template<typename base_t, typename composed_t>
    struct fused_multiplication;

    template<typename base_t, typename composed_t>
    struct arithmetic : public base_t {
        FORWARD(arithmetic);

        TRAIT(traits::Arithmetic);

        friend composed_t operator-(const composed_t one) { return arithmetic_negate(one); }

        friend composed_t operator+(const composed_t one, const composed_t other) {
            return arithmetic_add(one, other);
        }

        friend composed_t operator-(const composed_t one, const composed_t other) {
            return arithmetic_sub(one, other);
        }

        friend composed_t operator*(const composed_t one, const composed_t other) {
            return arithmetic_mul(one, other);
        }

        friend composed_t operator/(const composed_t one, const composed_t other) {
            return arithmetic_div(one, other);
        }

        friend composed_t &operator+=(composed_t &one, const composed_t other) {
            return one = one + other;
        }

        friend composed_t &operator-=(composed_t &one, const composed_t other) {
            return one = one - other;
        }

        friend composed_t &operator*=(composed_t &one, const composed_t other) {
            return one = one * other;
        }

        friend composed_t &operator/=(composed_t &one, const composed_t other) {
            return one = one / other;
        }


        CONVERSION(+);

        CONVERSION(-);

        CONVERSION(*);

        CONVERSION(/);
    };

    template<typename base_t, typename composed_t>
    struct fused_multiplication : public base_t {
        FORWARD(fused_multiplication);

        TRAIT(traits::Fused_Multiplication);

        friend composed_t operator+(const fused_multiplication one, const composed_t other) {
            return vfmadd(one._initial_multiplicand, one._initial_multiplier, other);
        }

        friend composed_t operator-(const fused_multiplication one, const composed_t other) {
            return vfmsub(one._initial_multiplicand, one._initial_multiplier, other);
        }

        operator composed_t() {
            return mul(_initial_multiplicand, _initial_multiplier);
        }

    private:

        composed_t _initial_multiplicand;
        composed_t _initial_multiplier;
    };
}}