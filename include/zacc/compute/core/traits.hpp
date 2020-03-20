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

#include <zacc/util/type/type_traits.hpp>
#include <type_traits>
#include <tuple>

namespace zacc { namespace compute {

    // =================================================================================================================

    struct expression_base;

    template<typename Operator, typename... Operands>
    struct expression;

    template<typename T>
    struct literal;

    template<typename T = void>
    struct variable;

    template<typename T>
    struct function;

    template<typename... Ts>
    struct conjunction;

    template<typename... Ts>
    struct disjunction;

        template<typename T>
        struct type;

        template<typename T>
        struct initializer;

    // =================================================================================================================

    template<typename T>
    struct is_expression;

    template<typename T>
    struct is_literal;

    template<typename T>
    struct is_variable;

    template<typename T>
    struct is_function;


    template<typename T>
    struct expression_result;

    template<typename T>
    struct rank;


    template<class F, class A0>
    constexpr auto fold(F&&, A0&& a0) {
        return std::forward<A0>(a0);
    }

    template<class F, class A0, class...As>
    constexpr auto fold(F&& f, A0&&a0, As&&...as) {
        return f(std::forward<A0>(a0), fold(f, std::forward<As>(as)...));
    }


        template<typename T, std::size_t N, typename = void>
        struct extent
            : std::integral_constant<std::size_t, 0>
        {};

//        template<template<class> class Predicate, typename... Ts>
//        constexpr bool contains(std::tuple<Ts...>&& = {}) {
//            return fold(std::logical_or<>{}, Predicate<Ts>::value...);
//        }

        template<template<typename> class Predicate, typename Tuple>
        struct contains;

        template<template<typename> class Predicate, template<typename...> class Tuple, typename... Ts>
        struct contains<Predicate, Tuple<Ts...>>
            : std::integral_constant<bool, fold(std::logical_or<>{}, Predicate<Ts>::value...)>
        {};

    template<typename T, typename = void>
    struct dim;


    template<typename T>
    constexpr auto dim_v = dim<T>::value;

    // =================================================================================================================

    template<typename T, typename = void>
    struct __rank
        : std::rank<T>
    {};

    template<typename T>
    struct __rank<T, std::enable_if_t<is_expression<T>::value>>
        : rank<typename expression_result<T>::type>
    {};

    template<typename T>
    struct rank
        : __rank<std::decay_t<T>>
    {};

    template<typename T>
    constexpr size_t rank_v = rank<T>::value;
    // =================================================================================================================

    template<typename...>
    struct __is_expression
        : std::false_type
    {};

    template<typename Op, typename... Ts>
    struct __is_expression<expression<Op, Ts...>>
        : std::true_type
    {};

    template<template<typename...> class Expression, typename Op, typename... Ts>
    struct __is_expression<Expression<Op, Ts...>>
        : std::is_base_of<expression<Op, Ts...>, Expression<Op, Ts...>>
    {};

    template<typename T>
    struct is_expression
        : __is_expression<std::decay_t<T>>
    {};

    template<typename T>
    constexpr bool is_expression_v = is_expression<T>::value;

    static_assert(is_expression_v<expression<int, int, int>>, "is_expression_v<expression<int, int, int>> != true");
    static_assert(is_expression_v<expression<int, int, int>&>, "is_expression_v<expression<int, int, int>&> != true");
    static_assert(is_expression_v<expression<int, int, int>&&>, "is_expression_v<expression<int, int, int>&&> != true");

    template<typename>
    struct __is_literal
        : std::false_type
    {};

    template<typename T>
    struct __is_literal<literal<T>>
        : std::true_type
    {};

    template<typename T>
    struct is_literal
        : __is_literal<std::decay_t<T>>
    {};

    template<typename T>
    constexpr bool is_literal_v = is_literal<T>::value;

    static_assert(is_literal_v<literal<int>>, "is_literal_v<literal<int>> != true");
    static_assert(is_literal_v<literal<int>&>, "is_literal_v<literal<int>&> != true");
    static_assert(is_literal_v<literal<int>&&>, "is_literal_v<literal<int>&&> != true");

    template<typename>
    struct __is_variable
        : std::false_type
    {};

    template<typename T>
    struct __is_variable<variable<T>>
        : std::true_type
    {};

    template<typename T>
    struct is_variable
        : __is_variable<std::decay_t<T>>
    {};

    template<typename T>
    constexpr bool is_variable_v = is_variable<T>::value;

    static_assert(is_variable_v<variable<int>>, "is_literal_v<variable<int>> != true");
    static_assert(is_variable_v<variable<int>&>, "is_literal_v<variable<int>&> != true");
    static_assert(is_variable_v<variable<int>&&>, "is_literal_v<variable<int>&&> != true");

    template<typename>
    struct __is_function
        : std::false_type
    {};

    template<typename T>
    struct __is_function<function<T>>
        : std::true_type
    {};

    template<typename T>
    struct is_function
        : __is_function<std::decay_t<T>>
    {};

    template<typename T>
    constexpr bool is_function_v = is_function<T>::value;

    // =================================================================================================================

        template<typename>
        struct is_batch;

    template<typename T, typename U = std::decay_t<T>>
    using expression_cast = std::conditional_t<
        (is_expression_v<U> || is_batch<U>::value || is_literal_v<U>), U,
        literal<U>>;


    template<typename Expression, typename = void>
    struct expression_type
    {
        using type = Expression;
    };

    template<typename Expression>
    struct expression_type<Expression, void_t<typename Expression::operator_type>>
    {
        using type = typename Expression::operator_type;
    };

    template<typename Expression>
    using expression_type_t = typename expression_type<Expression>::type;

    template<typename T>
    struct value_type
    {
        using type = typename std::decay_t<T>::value_type;
    };

    template<typename T>
    using value_type_t = typename value_type<std::decay_t<T>>::type;

    template<typename T>
    struct operator_type
    {
        using type = typename std::decay_t<T>::operator_type;
    };

    template<typename T>
    using operator_type_t = typename operator_type<std::decay_t<T>>::type;

    template<std::size_t Idx, typename Expression>
    struct operand_type
    {
        using type = std::tuple_element_t<Idx, typename std::decay_t<Expression>::operands_type>;
    };

    template<size_t Idx, typename Expression>
    using operand_type_t = typename operand_type<Idx, std::decay_t<Expression>>::type;


    template<typename Tuple>
    using tuple_size = std::tuple_size<std::decay_t<Tuple>>;

    template<typename Tuple>
    using make_tuple_index = std::make_integer_sequence<size_t, tuple_size<Tuple>::value>;

    // =================================================================================================================

    template<typename Expression, typename = void>
    struct terminal_of;

    template<typename T>
    struct terminal_of<T, std::enable_if_t<is_literal_v<T>>>
    {
        using type = std::tuple<std::decay_t<T>>;
    };

    template<typename T>
    struct terminal_of<type < T>>
    {
        using type = std::tuple<>;
    };

    template<typename T>
    struct terminal_of<initializer<T>>
    {
        using type = std::tuple<>;
    };

    template<typename T>
    struct __terminal_of;

    template<typename... Operands>
    struct __terminal_of<std::tuple<Operands...>>
    {
        using type = decltype(std::tuple_cat(typename terminal_of<Operands>::type{}...));
    };

    template<typename T>
    struct terminal_of<T, std::enable_if_t<is_expression_v<T>>>
    {
        using type = typename __terminal_of<typename std::decay_t<T>::operands_type>::type;
    };

    template<typename T>
    using terminal_of_t = typename terminal_of<std::decay_t<T>>::type;

    // =================================================================================================================


    // =================================================================================================================

    template<typename T, typename = void>
    struct result_of
    {
        using type = std::decay_t<T>;
    };

    template<typename T>
    struct result_of<T, std::enable_if_t<is_literal_v<T>>>
    {
        using type = std::decay_t<T>;
    };

    template<typename T>
    struct result_of<T, std::enable_if_t<is_expression_v<T>>>
    {
        using type = typename std::decay_t<T>::return_type;
    };

    template<typename T>
    using result_of_t = typename result_of<std::decay_t<T>>::type;

    // =================================================================================================================

    template<typename T, std::size_t N>
    struct __extent;

    template<typename... Operands, std::size_t N>
    struct __extent<std::tuple<Operands...>, N>
    {
        constexpr static auto max(size_t a, size_t b)
        {
            return (a < b) ? b : a;
        }

        constexpr static size_t value = fold(max, extent<std::decay_t<Operands>, N>::value...);
    };

    template<typename T>
    struct extent<T, 0, std::enable_if_t<is_literal_v<T>>>
        : std::integral_constant<std::size_t, 1>
    {};

    template<typename T, std::size_t N>
    struct extent<T, N, std::enable_if_t<is_expression_v<T>>>
        : std::integral_constant<std::size_t, __extent<terminal_of_t<T>, N>::value>
    {};

    template<typename T, std::size_t N>
    constexpr size_t extent_v = extent<std::decay_t<T>, N>::value;


    // =================================================================================================================


}}