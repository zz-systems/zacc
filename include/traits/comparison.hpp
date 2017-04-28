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
     * @brief provides logical comparison operator definitions
     * @tparam base_t base type (e.g previous trait)
     * @tparam composed_t final composed type (e.g zfloat32)
     */
    template<typename base_t, typename composed_t>
    struct comparison : public base_t {
        FORWARD(comparison);

        friend composed_t operator==(const composed_t one, const composed_t other) {
            return veq(one, other);
        }

        friend composed_t operator!=(const composed_t one, const composed_t other) {
            return vneq(one, other);
        }

        friend composed_t operator>(const composed_t one, const composed_t other) {
            return vgt(one, other);
        }

        friend composed_t operator>=(const composed_t one, const composed_t other) {
            return vge(one, other);
        }

        friend composed_t operator<(const composed_t one, const composed_t other) {
            return vlt(one, other);
        }

        friend composed_t operator<=(const composed_t one, const composed_t other) {
            return vle(one, other);
        }

        CONVERSION(==);

        CONVERSION(!=);

        CONVERSION(>);

        CONVERSION(>=);

        CONVERSION(<);

        CONVERSION(<=);
    };
}}