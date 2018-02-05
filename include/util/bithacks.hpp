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
#include <type_traits>
#include "type/type_traits.hpp"

namespace zacc {
    /**
     * @brief count last zero bits
     * @see Hacker's delight SE [Henry S. Warren Jr]
     * @tparam T
     * @param value
     * @return
     */
    template<typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, size_t> ntz(T value)
    {
        size_t n = 0;

        value = ~value & (value - 1);

        n = 0;

        while(value != 0)
        {
            n++;
            value >>= 1;
        }

        return n;
    }

    template<typename T>
    union twiddler;

    template<>
    union twiddler<float>
    {
        using uint_t = uint32_t;
        float f;
        uint32_t i;
    };

    template<>
    union twiddler<double>
    {
        using uint_t = uint64_t;
        double f;

        uint64_t i;
    };

//    template<typename T>
//    auto &bitsof(T &value)
//    {
//        //return twiddler<T> { .f = value }.i;
//
//        //return /**(twiddler<T>::uint_t*)&*/value;
//
//        return *reinterpret_cast<resolve_uint_t<T>*>(&value);
//    }

    template<typename T>
    auto && bitsof(T& value)
    {
        //return twiddler<T> { .f = value }.i;
        //return /**(twiddler<T>::uint_t*)&*/std::forward<T>(value);

        return *reinterpret_cast<resolve_uint_t<T>*>(&value);
    }

    template<typename T>
    auto const& bitsof(T&& value)
    {


        //return twiddler<T> { .f = value }.i;
        //return /**(twiddler<T>::uint_t*)&*/value;

        return *reinterpret_cast<resolve_uint_t<T>*>(&value);
    }

//    template<typename T>
//    auto && bitsof(T &&t)// -> decltype(twiddler<T> { .f = std::forward<T>(t) }.i) {
//    {
//        return twiddler<std::remove_reference_t<T>> { .f = t }.i;
//    }
}