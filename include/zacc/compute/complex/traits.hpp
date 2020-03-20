//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename>
    struct complex;

    template<typename, typename...>
    struct __expression;

    template<typename, typename...>
    struct expression;

    template<typename>
    struct expression_result;

    template<typename>
    struct literal;

    template<typename>
    struct is_expression;

    template<typename>
    struct is_literal;

    template<typename...>
    struct conjunction;

    template<typename...>
    struct disjunction;

    template<typename...>
    struct common_type;

    template<typename>
    struct rank;

    template<typename, std::size_t>
    struct extent;

    // =================================================================================================================

    template<typename T>
    struct is_complex;

    // =================================================================================================================

    template<typename T>
    struct expression<complex<T>>
        : __expression<complex<T>>
    {
        using __expression<complex<T>>::operator_type;
        using __expression<complex<T>>::operands_type;
        using __expression<complex<T>>::__expression;

        using return_type = complex<T>;
    };

    template<typename T>
    struct __is_expression<complex<T>>
        : std::true_type
    {};

    template<typename T, typename = void>
    struct __is_complex
        : std::false_type
    {};

    template<typename T>
    struct __is_complex<complex<T>>
        : std::true_type
    {};

//    template<typename T>
//    struct __is_complex<T, std::enable_if_t<is_expression<T>::value>>
//        : __is_complex<typename expression_result<T>::type>
//    {};

    template<typename T>
    struct is_complex
        : __is_complex<std::remove_reference_t<T>>
    {};

    template<typename T>
    constexpr bool is_complex_v = is_complex<T>::value;

    // =================================================================================================================

    template<typename T>
    struct __rank<complex<T>>
        : std::integral_constant<size_t, 1>
    {};

    // =================================================================================================================

    template<typename T, std::size_t N>
    struct __extent<complex<T>, N>
        : std::integral_constant<size_t, 2>
    {};

    // =================================================================================================================

    template<typename... Ts>
    struct __common_type<void, complex<Ts>...>
    {
        using type = common_type<Ts...>;
    };

    // =================================================================================================================

    template<typename Left, typename Right>
    struct __is_scalar_complex_expr
        : std::integral_constant<bool,
            is_literal<Left>::value
            && is_complex<Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_scalar_complex_expr
        : __is_scalar_complex_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_complex_scalar_expr
        : std::integral_constant<bool,
            is_complex<Left>::value
            && is_literal<Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_complex_scalar_expr
        : __is_complex_scalar_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_complex_complex_expr
        : std::integral_constant<bool,
            is_complex<Left>::value
            && is_complex<Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_complex_complex_expr
        : __is_complex_complex_expr<std::remove_reference_t<Left>, std::remove_reference_t<Right>>
    {};

    // =================================================================================================================
}}