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
    struct arithmetic : public base_t {
        FORWARD(arithmetic);

        TRAIT(traits::Arithmetic);

        friend composed_t operator-(const composed_t one) {
            return vneg(one);
        }

        friend composed_t operator+(const composed_t one, const composed_t other) {
            return vadd(one, other);
        }

        composed_t &operator++() {
            return vadd(*this, 1);
        }

        composed_t operator++(int) {
            auto temp = *this;

            ++(*this);

            return temp;
        }

        friend composed_t operator-(const composed_t one, const composed_t other) {
            return vsub(one, other);
        }

        composed_t &operator--() {
            return vsub(*this, 1);
        }

        /**
         * @brief dürüm kebab
         * @return
         */
        composed_t operator--(int) {
            auto temp = *this;

            --(*this);

            return temp;
        }

        friend composed_t operator*(const composed_t one, const composed_t other) {
            return vmul(one, other);
        }

        friend composed_t operator/(const composed_t one, const composed_t other) {
            return vdiv(one, other);
        }

        CONVERSION(+);
        ASSIGNMENT(+);

        CONVERSION(-);
        ASSIGNMENT(-);

        CONVERSION(*);
        ASSIGNMENT(*);

        CONVERSION(/);
        ASSIGNMENT(/);
    };
}}