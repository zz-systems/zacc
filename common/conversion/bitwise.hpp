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

namespace zacc {
    template<typename T>
    struct can_negate_bitwise : public T {
        T operator~() const;
    };

    template<typename T>
    struct can_or_bitwise : public T {
        T operator|(const T other) const;
    };

    template<typename T>
    struct can_and_bitwise : public T {
        T operator&(const T other) const;
    };

    template<typename T>
    struct can_xor_bitwise : public T {
        T operator^(const T other) const;
    };

    template<typename T, typename U = size_t>
    struct can_shift_left_bitwise : public T {
        T operator<<(const U shift_amount) const;
    };

    template<typename T, typename U = size_t>
    struct can_shift_right_bitwise : public T {
        T operator>>(const U shift_amount) const;
    };
}
