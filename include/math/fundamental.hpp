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
#include <algorithm>
#include <numeric>

namespace zacc { namespace math {

    /**
     * @brief
     * @tparam T
     * @param v
     * @param lo
     * @param hi
     * @return
     */
    template<class T>
    constexpr const std::enable_if_t<std::is_fundamental<T>::value, T> vclamp( const T& v, const T& lo, const T& hi )
    {
        return std::min(hi, std::max(lo, v));
    }

    /**
     * @brief
     * @tparam T
     * @param value
     * @return
     */
    template<class T>
    constexpr const T clamp_int32(const T& value)
    {
        return vclamp(value, -1073741824.0, 1073741824.0);
    }

    /**
     * @brief
     * @tparam T
     * @param a
     * @param b
     * @param c
     * @return
     */
    template<class T>
    constexpr std::enable_if_t<std::is_fundamental<T>::value, T> vfmadd( const T& a, const T& b, const T& c )
    {
        return a * b + c;
    }

    /**
     * @brief
     * @tparam T
     * @param a
     * @param b
     * @param c
     * @return
     */
    template<class T>
    constexpr std::enable_if_t<std::is_fundamental<T>::value, T> vfmsub( const T& a, const T& b, const T& c )
    {
        return a * b - c;
    }

}}