
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
     * @brief provides bitwise shift operator definitions
     * @tparam Base base type (e.g previous trait)
     * @tparam Composed final composed type (e.g zint32)
     */
    template<typename Base, typename Composed>
    struct bitwise_shift : public Base {
        FORWARD(bitwise_shift);

        using zval_t = typename Base::zval_t;
        using bval_t = typename Base::bval_t;

        friend Composed operator<<(const Composed one, const size_t immediate) {
            return vbslli(one, immediate);
        }

        friend Composed operator>>(const Composed one, const size_t immediate) {
            return vbsrli(one, immediate);
        }
// TODO: Disabled for now.
        /*friend Composed operator<<(const Composed one, const Composed other) {
            return vbsll(one, other);
        }

        friend Composed operator>>(const Composed one, const Composed other) {
            return vbsrl(one, other);
        }*/

        /**
        * @brief merged << - assignment operator
        */
        friend Composed &operator <<=(Composed &one, const size_t immediate) {
            return one = one << immediate;
        }

        /**
        * @brief merged >> - assignment operator
        */
        friend Composed &operator >>=(Composed &one, const size_t immediate) {
            return one = one >> immediate;
        }

        CONVERSION(<<);
        ASSIGNMENT(<<);

        CONVERSION(>>);
        ASSIGNMENT(>>);
    };
}}