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

#include <zacc/expressions/expression.hpp>
#include <zacc/expressions/pipe.hpp>

namespace zacc {

    // =================================================================================================================


//    template<template<typename> class Op, typename Head>
//    struct require_expr<Op<Head>>
//    {
//        using type = std::enable_if_t<std::is_base_of<expr, Op<Head>>::value, Op<Head>>;
//    };

    template<typename T>
    using is_expr = std::integral_constant<bool, std::is_base_of<expr, T>::value && !is_pipe<T>::value>;

    template<typename Expr>
    using expr_t = std::enable_if_t<is_expr<Expr>::value, Expr>;

    template<template<class> class Expr, typename Right>
    using un_expr_t = std::enable_if_t<is_expr<Right>::value, Expr<Right>>;

    template<typename Left, typename Right>
    using is_bin_expr = std::integral_constant<bool, is_expr<Left>::value && is_expr<Right>::value>;

    template<typename Left, typename Right>
    using is_lr_cast = std::integral_constant<bool, std::is_arithmetic<Left>::value && is_expr<Right>::value>;

    template<typename Left, typename Right>
    using is_rl_cast = std::integral_constant<bool, is_expr<Left>::value && std::is_arithmetic<Right>::value>;

    template<template<class, class> class Expr, template<class> class Cast, typename Left, typename Right>
    using bin_expr_t = select_t<
        when<is_bin_expr<Left, Right>::value, Expr<Left, Right>>, //Expr<std::decay<Left>, std::decay<Right>>>,
        when<is_lr_cast<Left, Right>::value, Expr<Cast<Left>, Right>>,
        when<is_rl_cast<Left, Right>::value, Expr<Left, Cast<Right>>>>;

//    template<template<class, class> class Expr, typename Left, typename Right>
//    using bin_expr_t = std::enable_if_t<is_bin_expr<Left, Right>::value, Expr<Left, Right>>;
//
//    template<template<class, class> class Expr, template<class> class Cast, typename Left, typename Right>
//    using lr_cast_expr_t = std::enable_if_t<is_lr_cast<Left, Right>::value, Expr<Cast<Left>, Right>>;
//
//    template<template<class, class> class Expr, template<class> class Cast, typename Left, typename Right>
//    using rl_cast_expr_t = std::enable_if_t<is_rl_cast<Left, Right>::value, Expr<Left, Cast<Right>>>;


//    template<typename Expr, typename A, typename B, typename C>
//    struct require_expr
//    {
//        using type = std::enable_if_t<
//            std::is_base_of<expr, A>::value
//            && std::is_base_of<expr, B>::value
//            && std::is_base_of<expr, C>::value,
//            Expr>;
//    };
//
//    template<class Expr, typename A, typename B>
//    struct require_expr<Expr, A, B, void>
//    {
//        using type = std::enable_if_t<
//            std::is_base_of<expr, A>::value
//            && std::is_base_of<expr, B>::value,
//            Expr>;
//    };
//
//    template<typename Expr, typename A>
//    struct require_expr<Expr, A, void, void>
//    {
//        using type = std::enable_if_t<std::is_base_of<expr, A>::value, Expr>;
//    };
//
//
//    template<typename Expr>
//    struct require_expr<Expr, void, void, void>
//    {
//        using type = std::enable_if_t<std::is_base_of<expr, Expr>::value, Expr>;
//    };
//
//    template<typename... Expr>
//    using require_expr_t = typename require_expr<Expr...>::type;

}