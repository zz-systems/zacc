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
     * @brief provides bitwise operator definitions
     * @tparam base_t base type (e.g previous trait)
     * @tparam composed_t final composed type (e.g zint32)
     */
    template<typename base_t, typename composed_t>
    struct bitwise : public base_t {
        FORWARD(bitwise);

        using zval_t = typename base_t::zval_t;
        using bval_t = typename base_t::bval_t;

        friend composed_t operator~(const composed_t one) { return vbneg(one); }

        friend composed_t operator|(const composed_t one, const composed_t other) {
            return vbor(one, other);
        }

        friend composed_t operator&(const composed_t one, const composed_t other) {
            return vband(one, other);
        }

        friend composed_t operator^(const composed_t one, const composed_t other) {
            return vbxor(one, other);
        }

//        template<typename U = bool>
//        explicit constexpr operator std::enable_if_t<is_bval<composed_t>::value, U >() const
//        {
//            return is_set(*this);
//        }

        CONVERSION(|);
        ASSIGNMENT(|);

        CONVERSION(&);
        ASSIGNMENT(&);

        CONVERSION(^);
        ASSIGNMENT(^);
    };
}}