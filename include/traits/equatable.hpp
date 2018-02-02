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

#include "common.hpp"

namespace zacc { namespace traits {

    /**
     * @brief provides logical comparison operator definitions
     * @tparam base_t base type (e.g previous trait)
     * @tparam composed_t final composed type (e.g zfloat32)
     */
    template<typename base_t, typename composed_t>
    struct equatable : public base_t {
        FORWARD(equatable);

        using zval_t = typename base_t::zval_t;
        using bval_t = typename base_t::bval_t;

        friend bval_t operator==(const composed_t one, const composed_t other) {
            return bval_t(veq(one, other), last_operation::comparison);
        }

        friend bval_t operator!=(const composed_t one, const composed_t other) {
            return bval_t(vneq(one, other), last_operation::comparison);
        }

//        bval_t operator==(const bval_t other) {
//            return bval_t(veq(*this, other), last_operation::comparison);
//        }
//
//        bval_t operator!=(const bval_t other) {
//            return bval_t(vneq(*this, other), last_operation::comparison);
//        }

        //CONVERSION(==);

        //CONVERSION(!=);
    };
}}