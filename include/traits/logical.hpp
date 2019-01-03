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
     * @brief provides logical operator definitions
     * @tparam Base base type (e.g previous trait)
     * @tparam Composed final composed type (e.g zfloat32)
     */
    template<typename Interface, typename Composed, typename Boolean>
    struct logical
            : inherit<ops_meta<Composed, Interface>, logical_and, logical_or>
    {
        friend op_proxy<Boolean, last_op::boolean> operator!(param_t<Composed> self) {
            return { vlneg(self), last_op::boolean }; // return vlneg(self);
        }

        friend op_proxy<Boolean, last_op::boolean> operator||(param_t<Composed> self, param_t<Composed> other) {
            return { vlor(self, other), last_op::boolean };//  return vlor(self, other);
        }

        friend op_proxy<Boolean, last_op::boolean> operator&&(param_t<Composed> self, param_t<Composed> other) {
            return { vland(self, other), last_op::boolean }; // return vland(self, other);
        }
    };
}}