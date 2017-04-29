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

#include <numeric>
#include <algorithm>
#include <type_traits>

#include "type_traits.hpp"
#include "zval.hpp"
#include "common.hpp"
#include "util/algorithm.hpp"

#include "backend/all.hpp"

#define DISPATCHED template<typename dispatcher, \
    typename zint8      = typename dispatcher::zint8, \
    typename zint16     = typename dispatcher::zint16, \
    typename zint32     = typename dispatcher::zint32, \
    typename zfloat32   = typename dispatcher::zfloat32, \
    typename zfloat64   = typename dispatcher::zfloat64, \
    typename zbyte      = zint8, \
    typename zshort     = zint16, \
    typename zint       = zint32, \
    typename zfloat     = zfloat32, \
    typename zdouble    = zfloat64, \
    typename bint8      = typename dispatcher::bint8, \
    typename bint16     = typename dispatcher::bint16, \
    typename bint32     = typename dispatcher::bint32, \
    typename bfloat32   = typename dispatcher::bfloat32, \
    typename bfloat64   = typename dispatcher::bfloat64, \
    typename bbyte      = bint8, \
    typename bshort     = bint16, \
    typename bint       = bint32, \
    typename bfloat     = bfloat32, \
    typename bdouble    = bfloat64>

template<typename T>
std::enable_if_t<!zacc::is_zval<T>::value, bool> is_set(T value)
{
    return value != 0;
};