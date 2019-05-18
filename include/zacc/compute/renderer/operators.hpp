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

#include <zacc/compute/core/core.hpp>

#include <sstream>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename T, typename...>
    constexpr string_view name_of = type_of<T>::name();

    // =================================================================================================================

    template<typename... Expr>
    constexpr string_view name_of<identity_impl<Expr...>> = "";

    template<typename... Expr>
    constexpr string_view name_of<plus_impl<Expr...>> = "+";

    template<typename... Expr>
    constexpr string_view name_of<minus_impl<Expr...>> = "-";

    template<typename... Expr>
    constexpr string_view name_of<multiplies_impl<Expr...>> = "*";

    template<typename... Expr>
    constexpr string_view name_of<divides_impl<Expr...>> = "/";

    template<typename... Expr>
    constexpr string_view name_of<modulus_impl<Expr...>> = "%";

    template<typename... Expr>
    constexpr string_view name_of<negate_impl<Expr...>> = "-";

    template<typename... Expr>
    constexpr string_view name_of<promote_impl<Expr...>> = "+";

    template<typename... Expr>
    constexpr string_view name_of<fmadd_impl<Expr...>> = "fmadd";

    // =================================================================================================================

    template<typename... Expr>
    constexpr string_view name_of<equal_to_impl<Expr...>> = "==";

    template<typename... Expr>
    constexpr string_view name_of<not_equal_to_impl<Expr...>> = "!=";

    template<typename... Expr>
    constexpr string_view name_of<greater_impl<Expr...>> = ">";

    template<typename... Expr>
    constexpr string_view name_of<less_impl<Expr...>> = "<";

    template<typename... Expr>
    constexpr string_view name_of<greater_equal_impl<Expr...>> = ">=";

    template<typename... Expr>
    constexpr string_view name_of<less_equal_impl<Expr...>> = "<=";

    // =================================================================================================================

    template<typename... Expr>
    constexpr string_view name_of<logical_and_impl<Expr...>> = "&&";

    template<typename... Expr>
    constexpr string_view name_of<logical_or_impl<Expr...>> = "||";

    template<typename... Expr>
    constexpr string_view name_of<logical_not_impl<Expr...>> = "!";

    // =================================================================================================================

    template<typename... Expr>
    constexpr string_view name_of<bit_and_impl<Expr...>> = "&";

    template<typename... Expr>
    constexpr string_view name_of<bit_or_impl<Expr...>> = "|";

    template<typename... Expr>
    constexpr string_view name_of<bit_xor_impl<Expr...>> = "^";

    template<typename... Expr>
    constexpr string_view name_of<bit_shl_impl<Expr...>> = "<<";

    template<typename... Expr>
    constexpr string_view name_of<bit_shr_impl<Expr...>> = ">>";

    template<typename... Expr>
    constexpr string_view name_of<bit_not_impl<Expr...>> = "~";

    // =================================================================================================================
}}