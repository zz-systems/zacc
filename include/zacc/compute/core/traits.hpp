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
#include "expressions.hpp"

namespace zacc { namespace compute {

    // =================================================================================================================



//    template<template<typename> class Op, typename Head>
//    struct require_expr<Op<Head>>
//    {
//        using type = std::enable_if_t<std::is_base_of<expr, Op<Head>>::value, Op<Head>>;
//    };

    struct __expr;

    template<typename T>
    struct expr;

    template<typename T>
    struct lit;

    template<typename T, typename Expr>
    struct assign_expr;

    template<typename T>
    struct declare_expr;

    template<typename FuncOp, typename AExpr, typename BExpr, typename CExpr>
    struct func_expr;

    template<typename TriOp, typename AExpr, typename BExpr, typename CExpr>
    struct tri_expr;

    template<typename BinOp, typename Left, typename Right>
    struct bin_expr;

    template<typename UnOp, typename Expr>
    struct un_expr;

    template<typename T, size_t Size>
    struct batch;

//    enum class expr_tag;

    template<typename Expr, typename = void>
    struct expr_type
    {
        constexpr static Tokens value = Tokens::None;
    };

    template<typename Expr>
    struct expr_type<Expr, void_t<decltype(Expr::type())>>
    {
        constexpr static Tokens value = Expr::type();
    };

    template<typename Expr>
    constexpr bool is_pipe_expr = expr_type<Expr>::value == Tokens::PipeExpr;

    template<typename Expr>
    constexpr bool is_declare_expr = expr_type<Expr>::value == Tokens::Declare;

    template<typename Expr>
    constexpr bool is_assign_expr = expr_type<Expr>::value == Tokens::Assign;

    template<typename Expr>
    constexpr bool is_term_expr = expr_type<Expr>::value == Tokens::Term;

    template<typename Expr>
    constexpr bool is_lit_expr = expr_type<Expr>::value == Tokens::Literal;

    template<typename Expr>
    constexpr bool is_arg_expr = expr_type<Expr>::value == Tokens::Arg;

    template<typename Expr>
    constexpr bool is_func_expr = expr_type<Expr>::value == Tokens::CallExpr;

    template<typename Expr>
    constexpr bool is_tri_expr = expr_type<Expr>::value == Tokens::TriExpr;

    template<typename Expr>
    constexpr bool is_bin_expr = expr_type<Expr>::value == Tokens::BinExpr;

    template<typename Expr>
    constexpr bool is_un_expr = expr_type<Expr>::value == Tokens::UnExpr;



    template<typename, typename = void_t<> >
    struct has_leaf : std::false_type { };

    template<typename T>
    struct has_leaf<T, void_t<typename T::leaf_t>> : std::true_type { };

    template<typename... Args>
    struct expr_leaf;

    template<typename Expr, typename... Next>
    struct expr_leaf<Expr, Next...>
    {
        template<typename T, typename = void>
        struct vv
        {
            using type = void;
        };

        template<typename T>
        struct vv<T, void_t<typename T::op_t::leaf_t>>
        {
            using type = typename T::op_t::leaf_t;
        };

        template<typename T>
        struct vv<T, void_t<typename T::leaf_t>>
        {
            using type = typename T::leaf_t;
        };

        using type = typename expr_leaf<
            void,
            typename vv<Expr>::type,
            typename vv<Next>::type...,
            Expr>::type;
    };

    template<typename... Tail>
    struct expr_leaf<void, Tail...>
    {
        using type = typename expr_leaf<Tail...>::type;
    };

    template<typename Expr>
    struct expr_leaf<void, Expr>
    {
        using type = Expr;
    };

    template<typename Expr, typename... Next>
    using expr_leaf_t = typename expr_leaf<Expr, Next...>::type;

    template<typename Expr, typename = void>
    struct expr_traits;



    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_assign_expr<Expr>>>
    {
        using leaf_t = expr_leaf_t<Expr>;

        constexpr static size_t size = expr_traits<leaf_t>::size;
        constexpr static uint64_t mask = expr_traits<leaf_t>::mask;
        constexpr static expr_tag expr_tag = expr_traits<leaf_t>::expr_tag;
    };

    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_term_expr<Expr>>>
    {
        using leaf_t = Expr;

        constexpr static size_t size = Expr::size;
        constexpr static uint64_t mask = Expr::mask;
        constexpr static expr_tag expr_tag = Expr::expr_tag;
    };

    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_lit_expr<Expr>>>
    {
        using leaf_t = Expr;

//        constexpr static size_t size = Expr::size;
//        constexpr static uint64_t mask = Expr::mask;
        constexpr static expr_tag expr_tag = Expr::expr_tag;
    };

    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_arg_expr<Expr>>>
    {
        using leaf_t = Expr;

        constexpr static size_t size = Expr::size;
        constexpr static uint64_t mask = Expr::mask;
        constexpr static expr_tag expr_tag = Expr::expr_tag;
    };

    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_pipe_expr<Expr>>>
    {
        using leaf_t = expr_leaf_t<Expr, expr_traits<decltype(Expr::_right)>>;

        constexpr static size_t size = expr_traits<leaf_t>::size;
        constexpr static uint64_t mask = expr_traits<leaf_t>::mask;
        constexpr static expr_tag expr_tag = expr_traits<leaf_t>::expr_tag;
    };

    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_func_expr<Expr>>>
    {
        using leaf_t = expr_leaf_t<Expr, expr_traits<decltype(Expr::_a)>>;

        constexpr static size_t size = expr_traits<leaf_t>::size;
        constexpr static uint64_t mask = expr_traits<leaf_t>::mask;
        constexpr static expr_tag expr_tag = expr_traits<leaf_t>::expr_tag;
    };

    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_tri_expr<Expr>>>
    {
        using leaf_t = expr_leaf_t<Expr, expr_traits<decltype(Expr::_a)>>;

        constexpr static size_t size = expr_traits<leaf_t>::size;
        constexpr static uint64_t mask = expr_traits<leaf_t>::mask;
        constexpr static expr_tag expr_tag = expr_traits<leaf_t>::expr_tag;
    };

    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_bin_expr<Expr>>>
    {
        using leaf_t = expr_leaf_t<Expr, expr_traits<decltype(Expr::_left)>>;

        constexpr static size_t size = expr_traits<leaf_t>::size;
        constexpr static uint64_t mask = expr_traits<leaf_t>::mask;
        constexpr static expr_tag expr_tag = expr_traits<leaf_t>::expr_tag;
    };

    template<typename Expr>
    struct expr_traits<Expr, std::enable_if_t<is_un_expr<Expr>>>
    {
        using leaf_t = expr_leaf_t<Expr, expr_traits<decltype(Expr::_expr)>>;

        constexpr static size_t size = expr_traits<leaf_t>::size;
        constexpr static uint64_t mask = expr_traits<leaf_t>::mask;
        constexpr static expr_tag expr_tag = expr_traits<leaf_t>::expr_tag;
    };

//    template<typename T>
//    using wrapped_type_t = typename expr_traits<T>::wrapped_type;

//    template<typename T>
//    constexpr static uint64_t mask_v = expr_traits<T>::mask;
//
//    template<typename T>
//    constexpr static expr_tag expr_tag_v = expr_traits<T>::expr_tag;
//
//
//
//    template<typename T>
//    constexpr static bool is_invalid_expr_v = expr_tag_v<T> == expr_tag::invalid;
//
//    template<typename T>
//    constexpr static bool is_scalar_expr_v = expr_tag_v<T> == expr_tag::scalar;
//
//    template<typename T>
//    constexpr static bool is_vector_expr_v = expr_tag_v<T> == expr_tag::vector;
//
//    template<typename T>
//    constexpr static bool is_matrix_expr_v = expr_tag_v<T> == expr_tag::matrix;
//
//    template<typename T>
//    constexpr static bool is_complex_expr_v = expr_tag_v<T> == expr_tag::complex;


    template<typename T, typename = void>
    struct is_expr : std::false_type {};

    template<typename T>
    struct is_expr<T, std::enable_if_t<std::is_base_of<__expr, T>::value && !is_pipe_expr<T>>>
        : std::true_type
    {};

//    template<typename T>
//    using is_expr<T> = is_expr_t<T>::value;

    template<typename Expr>
    using expr_t = std::enable_if_t<is_expr<Expr>::value, Expr>;

    template<typename Expr>
    using expr_value_t = typename expr_leaf_t<Expr>::value_type;

    template<template<class> class Expr, typename Right>
    using un_expr_t = std::enable_if_t<is_expr<Right>::value, Expr<Right>>;

//    template<typename Left, typename Right>
//    using is_bin_expr = std::integral_constant<bool, is_expr<Left>::value && is_expr<Right>::value>;

    template<typename Left, typename Right>
    using is_lr_cast = std::integral_constant<bool, std::is_arithmetic<Left>::value && is_expr<Right>::value>;

    template<typename Left, typename Right>
    using is_rl_cast = std::integral_constant<bool, is_expr<Left>::value && std::is_arithmetic<Right>::value>;

//    template<template<class, class> class Expr, template<class> class Cast, typename Left, typename Right>
//    using bin_expr_t = select_t<
//        when<is_bin_expr<Left, Right>::value, Expr<Left, Right>>, //Expr<std::decay<Left>, std::decay<Right>>>,
//        when<is_lr_cast<Left, Right>::value, Expr<Cast<Left>, Right>>,
//        when<is_rl_cast<Left, Right>::value, Expr<Left, Cast<Right>>>>;

    template<typename T>
    using expr_cast_t = select_t<
        when<is_expr<T>::value, T>,
        when<std::is_arithmetic<T>::value, lit<T>>>;

    template<template<class, class...> class Expr, typename T, typename... Ts>
    using make_expr_t = Expr<expr_cast_t<T>, expr_cast_t<Ts>...>;

    template<typename Expr, typename = void>
    struct mat_traits
    {
        using leaf_t = expr_leaf_t<Expr, expr_traits<Expr>>;

        static constexpr size_t rows = is_lit_expr<Expr> ? 1 : 0;
        static constexpr size_t cols = is_lit_expr<Expr> ? 1 : 0;
        static constexpr size_t size = is_lit_expr<Expr> ? 1 : 0;

        static constexpr bool is_mat    = false;
        static constexpr bool is_vec    = false;
        static constexpr bool is_scalar = is_lit_expr<Expr>;
    };

    template<typename Expr>
    struct mat_traits<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::matrix>>
    {
        using leaf_t = expr_leaf_t<Expr, expr_traits<Expr>>;

        static constexpr size_t rows = leaf_t::rows;
        static constexpr size_t cols = leaf_t::cols;
        static constexpr size_t size = leaf_t::size;

        static constexpr bool is_mat    = rows > 1 && cols > 1;
        static constexpr bool is_vec    = (rows > 1 && cols == 1) || (rows == 1 && cols > 1);
        static constexpr bool is_scalar = rows == 1 && cols == 1;
    };

    template<typename T>
    constexpr static size_t rows_v = mat_traits<T>::rows;

    template<typename T>
    constexpr static size_t cols_v = mat_traits<T>::cols;

    template<typename T>
    constexpr static size_t size_v = mat_traits<T>::size;

    template<typename... Ts>
    struct is_mat_expr : std::integral_constant<bool, all_true<mat_traits<Ts>::is_mat...>::value>
    {};

    template<typename... Ts>
    struct is_vec_expr : std::integral_constant<bool, all_true<mat_traits<Ts>::is_vec...>::value>
    {};

    template<typename... Ts>
    struct is_scalar_expr : std::integral_constant<bool, all_true<mat_traits<Ts>::is_scalar...>::value>
    {};

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct is_same : std::false_type
    {};

    template<typename LExpr, typename RExpr>
    struct is_same<LExpr, RExpr, std::enable_if_t<
        is_mat_expr<LExpr, RExpr>::value
        && rows_v<LExpr> == rows_v<RExpr>
        && cols_v<LExpr> == cols_v<RExpr>>> : std::true_type
    {};

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct can_add : std::false_type
    {};

    template<typename LExpr, typename RExpr>
    struct can_add<LExpr, RExpr, std::enable_if_t<
        is_same<LExpr, RExpr>::value
        || ((is_vec_expr<LExpr>::value || is_mat_expr<LExpr>::value) && is_scalar_expr<RExpr>::value)
           || (is_scalar_expr<LExpr>::value && (is_vec_expr<LExpr>::value || is_mat_expr<RExpr>::value))>>
        : std::true_type
    {};

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct can_subtract : std::false_type
    {};

    template<typename LExpr, typename RExpr>
    struct can_subtract<LExpr, RExpr, std::enable_if_t<
        is_same<LExpr, RExpr>::value
        || ((is_vec_expr<LExpr>::value || is_mat_expr<LExpr>::value) && is_scalar_expr<RExpr>::value)
           || (is_scalar_expr<LExpr>::value && (is_vec_expr<LExpr>::value || is_mat_expr<RExpr>::value))>>
        : std::true_type
    {};

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct can_multiply : std::false_type
    {};

    template<typename LExpr, typename RExpr>
    struct can_multiply<LExpr, RExpr, std::enable_if_t<
        ((is_mat_expr<LExpr, RExpr>::value
            || is_vec_expr<LExpr, RExpr>::value
            || (is_mat_expr<LExpr>::value && is_vec_expr<RExpr>::value)
            || (is_vec_expr<LExpr>::value && is_mat_expr<RExpr>::value))
            && cols_v<LExpr> == rows_v<RExpr>)>>
        : std::true_type
    {};

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct can_scale : std::false_type
    {};

    template<typename LExpr, typename RExpr>
    struct can_scale<LExpr, RExpr, std::enable_if_t<
        ((is_vec_expr<LExpr>::value || is_mat_expr<LExpr>::value) && is_scalar_expr<RExpr>::value)
            || (is_scalar_expr<LExpr>::value && (is_vec_expr<LExpr>::value || is_mat_expr<RExpr>::value))>>
        : std::true_type
    {};


    template<typename LExpr, typename RExpr, typename Enable = void>
    struct can_divide : std::false_type
    {};

    template<typename LExpr, typename RExpr>
    struct can_divide<LExpr, RExpr, std::enable_if_t<
        (is_mat_expr<LExpr>::value && is_scalar_expr<RExpr>::value)
        || (is_scalar_expr<LExpr>::value && is_mat_expr<RExpr>::value)>>
        : std::true_type
    {};

    template<typename LExpr, typename RExpr>
    struct is_mat_mat : std::integral_constant<bool,
        is_mat_expr<LExpr>::value && is_mat_expr<RExpr>::value
        && mat_traits<LExpr>::rows == mat_traits<RExpr>::rows
        && mat_traits<LExpr>::cols == mat_traits<RExpr>::cols>
    {};

    template<typename LExpr, typename RExpr>
    struct is_mat_vec : std::integral_constant<bool,
        is_mat_expr<LExpr>::value && is_vec_expr<RExpr>::value
        && mat_traits<LExpr>::rows == mat_traits<RExpr>::rows>
    {};

    template<typename LExpr, typename RExpr>
    struct is_mat_scalar : std::integral_constant<bool,
        is_mat_expr<LExpr>::value && is_scalar_expr<RExpr>::value>
    {};
}}