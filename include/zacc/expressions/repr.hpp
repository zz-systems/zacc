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
#include <sstream>
#include <zacc/expressions/arithmetic.hpp>
#include <zacc/expressions/comparisons.hpp>
#include <zacc/expressions/logical_operations.hpp>
#include <zacc/expressions/bitwise_operations.hpp>
#include <zacc/expressions/expression.hpp>

namespace zacc { namespace expressions {

    // =================================================================================================================

    template<typename T>
    constexpr string_view name_of = type_of<T>::name();

    // =================================================================================================================

    template<>
    constexpr string_view name_of<identity<>> = "";

    template<>
    constexpr string_view name_of<plus<>> = "+";

    template<>
    constexpr string_view name_of<minus<>> = "-";

    template<>
    constexpr string_view name_of<multiplies<>> = "*";

    template<>
    constexpr string_view name_of<divides<>> = "/";

    template<>
    constexpr string_view name_of<modulus<>> = "%";

    template<>
    constexpr string_view name_of<negate<>> = "-";

    template<>
    constexpr string_view name_of<promote<>> = "+";

    template<>
    constexpr string_view name_of<fmadd<>> = "fmadd";

    // =================================================================================================================

    template<>
    constexpr string_view name_of<equal_to<>> = "==";

    template<>
    constexpr string_view name_of<not_equal_to<>> = "!=";

    template<>
    constexpr string_view name_of<greater<>> = ">";

    template<>
    constexpr string_view name_of<less<>> = "<";

    template<>
    constexpr string_view name_of<greater_equal<>> = ">=";

    template<>
    constexpr string_view name_of<less_equal<>> = "<=";

    // =================================================================================================================

    template<>
    constexpr string_view name_of<logical_and<>> = "&&";

    template<>
    constexpr string_view name_of<logical_or<>> = "||";

    template<>
    constexpr string_view name_of<logical_not<>> = "!";

    // =================================================================================================================

    template<>
    constexpr string_view name_of<bit_and<>> = "&";

    template<>
    constexpr string_view name_of<bit_or<>> = "|";

    template<>
    constexpr string_view name_of<bit_xor<>> = "^";

    template<>
    constexpr string_view name_of<bit_shl<>> = "<<";

    template<>
    constexpr string_view name_of<bit_shr<>> = ">>";

    template<>
    constexpr string_view name_of<bit_not<>> = "~";

    // =================================================================================================================
}}