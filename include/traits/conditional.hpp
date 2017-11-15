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
     * @brief provides conditional functionality
     * @tparam base_t base type (e.g previous trait)
     * @tparam composed_t final composed type (e.g zfloat32)
     */
    template<typename base_t, typename composed_t>
    struct conditional : public base_t {
        FORWARD(conditional);

        struct else_branch {
            composed_t otherwise(const composed_t& else_value) const { return vsel(_condition, _if_value, else_value); }

        private:
            else_branch(const composed_t& condition, const composed_t& if_value)
                    : _if_value(if_value), _condition(condition) {}

            composed_t _if_value;
            composed_t _condition;

            friend struct conditional<base_t, composed_t>;
        };


        else_branch when(const composed_t& condition) const {
            return else_branch(condition, *this);
        }
    };

}}