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

    template<typename, size_t>
    struct batch;

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

    template<typename, typename...>
    struct common_type;

    template<typename>
    struct rank;

    template<typename, std::size_t, typename>
    struct extent;

    // =================================================================================================================


    template<typename>
    struct is_batch;

    // =================================================================================================================

//    template<typename T, std::size_t Size>
//    struct expression<batch<T, Size>>
//        : __expression<batch<T, Size>>
//    {
//        using __expression<batch<T, Size>>::operator_type;
//        using __expression<batch<T, Size>>::operands_type;
//        using __expression<batch<T, Size>>::__expression;
//
//        using return_type = batch<T, Size>;
//    };
//
//    template<typename T, size_t Size>
//    struct __is_expression<batch<T, Size>>
//        : std::true_type
//    {};


    template<typename>
    struct is_batch;

    template<typename>
    struct __is_batch
        : std::false_type
    {};

    template<typename T, size_t Size>
    struct __is_batch<batch<T, Size>>
        : std::true_type
    {};

    template<typename T>
    struct is_batch
        : __is_batch<std::decay_t<T>>
    {};

    template<typename T>
    constexpr bool is_batch_v = is_batch<T>::value;

    static_assert(!is_expression_v<batch<int, 2>>, "is_expression_v<batch<int, 2>> != false");
    static_assert(!is_literal_v<batch<int, 2>>, "is_literal_v<batch<int, 2>> != false");
    static_assert(!is_variable_v<batch<int, 2>>, "is_variable_v<batch<int, 2>> != false");

    static_assert(is_batch_v<batch<int, 2>>, "is_batch_v<batch<int, 2>> == false");
    static_assert(is_batch_v<batch<int, 2>&>, "is_batch_v<batch<int, 2>&> == false");
    static_assert(is_batch_v<batch<int, 2>&&>, "is_batch_v<batch<int, 2>&&> == false");

    template<typename T>
    struct terminal_of<T, std::enable_if_t<is_batch_v<T>>>
    {
        using type = std::tuple<std::decay_t<T>>;
    };

    template<typename T>
    struct result_of<T, std::enable_if_t<is_batch_v<T>>>
    {
        using type = std::decay_t<T>;
    };

    template<typename T, size_t Size>
    struct dim<batch<T, Size>>
    {
        constexpr static auto value = std::make_tuple(Size);
    };

    template<typename T>
    struct extent<T, 0, std::enable_if_t<is_batch_v<T>>>
        : std::integral_constant<std::size_t, std::get<0>(dim_v<T>)>
    {};
    // =================================================================================================================

    template<typename T, std::size_t... Is>
    struct __rank<batch<T, Is...>>
        : std::integral_constant<std::size_t, sizeof...(Is)>
    {};

    // =================================================================================================================

    static_assert(std::tuple_size<terminal_of_t<batch<int, 2>>>::value == 1, "std::tuple_size<terminal_of_t<batch<int, 2>>> != 1");
    //static_assert(is_batch_v<std::tuple_element<0, terminal_of_t<batch<int, 2>>>>, "is_batch_v<std::tuple_element<0, terminal_of_t<batch<int, 2>>>> != true");
    //static_assert(std::is_same<std::tuple_element<0, terminal_of_t<batch<int, 2>>>, batch<int, 2>>::value, "");
    static_assert(std::is_same<terminal_of_t<batch<int, 2>>, std::tuple<batch<int, 2>>>::value, "terminal_of_t<batch<int, 2>> != batch<int, 2>");
    static_assert(contains<is_batch, terminal_of_t<batch<int, 2>>>::value, "");
    static_assert(extent<batch<int, 2>, 0>::value == 2, "extent<batch<int, 2>, 0> != 2");
    static_assert(extent<batch<int, 4>, 0>::value == 4, "extent<batch<int, 4>, 0> != 4");
    static_assert(extent<batch<int, 4>, 1>::value == 0, "extent<batch<int, 4>, 1> != 0");


    // =================================================================================================================

    template<typename Left, typename Right>
    struct __is_scalar_batch_expr
        : std::integral_constant<bool,
            std::is_arithmetic<Left>::value
            && (is_batch<Right>::value || is_batch_v<result_of_t<Right>>)
        >
    {};

    template<typename Left, typename Right>
    struct is_scalar_batch_expr
        : __is_scalar_batch_expr<std::decay_t<Left>, std::decay_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_batch_scalar_expr
        : std::integral_constant<bool,
            (is_batch<Left>::value || is_batch_v<result_of_t<Left>>)
            && std::is_arithmetic<Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_batch_scalar_expr
        : __is_batch_scalar_expr<std::decay_t<Left>, std::decay_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_batch_batch_expr
        : std::integral_constant<bool,
               (is_batch<Left>::value || is_batch_v<result_of_t<Left>>)
            && (is_batch<Right>::value || is_batch_v<result_of_t<Right>>)
        >
    {};

    template<typename Left, typename Right>
    struct is_batch_batch_expr
        : __is_batch_batch_expr<std::decay_t<Left>, std::decay_t<Right>>
    {};

    template<typename Left, typename Right>
    struct __is_batch_expr
        : std::integral_constant<bool,
            is_batch_batch_expr<Left, Right>::value
            || is_scalar_batch_expr<Left, Right>::value
            || is_batch_scalar_expr<Left, Right>::value
        >
    {};

    template<typename Left, typename Right>
    struct is_batch_expr
        : __is_batch_expr<std::decay_t<Left>, std::decay_t<Right>>
    {};

    // =================================================================================================================


    // =================================================================================================================


    // =================================================================================================================

}}