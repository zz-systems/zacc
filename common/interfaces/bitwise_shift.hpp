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

#include "../traits.hpp"
#include "../common.hpp"

namespace zacc { namespace interface {

    template<typename base_t, typename composed_t>
    struct bitwise_shift : public base_t {
        FORWARD(bitwise_shift);

        TRAIT(traits::Bitwise_Shift);


        friend composed_t operator<<(const composed_t one, const size_t immediate) {
            return bitwise_shift_slli(one, immediate);
        }

        friend composed_t operator>>(const composed_t one, const size_t immediate) {
            return bitwise_shift_srli(one, immediate);
        }

        friend composed_t operator<<(const composed_t one, const composed_t other) {
            return bitwise_shift_sll(one, other);
        }

        friend composed_t operator>>(const composed_t one, const composed_t other) {
            return bitwise_shift_srl(one, other);
        }


        CONVERSION(<<);

        CONVERSION(>>);
    };
}}