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

#include <zacc/compute/core/operators.hpp>
#include <zacc/compute/core/traits.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename Expr>
    struct identity_impl<Expr, std::enable_if_t<is_complex_expr<Expr>::value>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return arg;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct plus_impl<LExpr, RExpr, std::enable_if_t<is_complex_expr<LExpr, RExpr>::value>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left + right;
        }
    };

    template<typename LExpr, typename RExpr>
    struct plus_impl<LExpr, RExpr, std::enable_if_t<is_complex_expr<LExpr>::value && !is_complex_expr<RExpr>::value>>
    {
        using leaf_t = complex<decltype(std::declval<expr_value_t<LExpr>>() + std::declval<expr_value_t<RExpr>>())>;

        static auto apply(LExpr left, RExpr right, std::integral_constant<size_t, 0> idx)
        {
            return left(idx) + right(idx);
        }

        static auto apply(LExpr left, RExpr, std::integral_constant<size_t, 1> idx)
        {
            return left(idx);
        }
    };

    template<typename LExpr, typename RExpr>
    struct plus_impl<LExpr, RExpr, std::enable_if_t<!is_complex_expr<LExpr>::value && is_complex_expr<RExpr>::value>>
    {
        using leaf_t = complex<decltype(std::declval<expr_value_t<LExpr>>() + std::declval<expr_value_t<RExpr>>())>;

        static auto apply(LExpr left, RExpr right, std::integral_constant<size_t, 0> idx)
        {
            return left(idx) + right(idx);
        }

        static auto apply(LExpr, RExpr right, std::integral_constant<size_t, 1> idx)
        {
            return right(idx);
        }
    };

    // =================================================================================================================

    template<typename Expr>
    struct promote_impl<Expr, std::enable_if_t<is_complex_expr<Expr>::value>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return +arg;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct minus_impl<LExpr, RExpr, std::enable_if_t<is_complex_expr<LExpr, RExpr>::value>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left - right;
        }
    };

    template<typename LExpr, typename RExpr>
    struct minus_impl<LExpr, RExpr, std::enable_if_t<is_complex_expr<LExpr>::value && !is_complex_expr<RExpr>::value>>
    {
        using leaf_t = complex<decltype(std::declval<expr_value_t<LExpr>>() - std::declval<expr_value_t<RExpr>>())>;

        template<typename Idx>
        static auto apply(LExpr left, RExpr right, Idx idx)
        {
            if(idx == 0)
                return left(idx) - right(idx);
            else
                return left(idx);
        }
    };

    template<typename LExpr, typename RExpr>
    struct minus_impl<LExpr, RExpr, std::enable_if_t<!is_complex_expr<LExpr>::value && is_complex_expr<RExpr>::value>>
    {
        using leaf_t = complex<decltype(std::declval<expr_value_t<LExpr>>() - std::declval<expr_value_t<RExpr>>())>;

        template<typename Idx>
        static auto apply(LExpr left, RExpr right, Idx idx)
        {
            if(idx == 0)
                return left(idx) - right(idx);
            else
                return right(idx);
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct multiplies_impl<LExpr, RExpr, std::enable_if_t<is_complex_expr<LExpr, RExpr>::value>>
    {
        using leaf_t = complex<decltype(std::declval<expr_value_t<LExpr>>() * std::declval<expr_value_t<RExpr>>())>;

        template<typename Idx>
        static auto apply(LExpr left, RExpr right, Idx idx)
        {
            if(idx == 0)
                return left(0) * right(0) - left(1) * right(1);
            else
                return left(1) * right(0) + left(0) * right(1);
        }
    };

    template<typename LExpr, typename RExpr>
    struct multiplies_impl<LExpr, RExpr, std::enable_if_t<
        (is_complex_expr<LExpr>::value && !is_complex_expr<RExpr>::value)
        || (!is_complex_expr<LExpr>::value && is_complex_expr<RExpr>::value)>>
    {
        using leaf_t = complex<decltype(std::declval<expr_value_t<LExpr>>() * std::declval<expr_value_t<RExpr>>())>;

        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left * right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct divides_impl<LExpr, RExpr, std::enable_if_t<is_complex_expr<LExpr, RExpr>::value>>
    {
        using leaf_t = complex<decltype(std::declval<expr_value_t<LExpr>>() / std::declval<expr_value_t<RExpr>>())>;

        template<typename Idx>
        static auto apply(LExpr left, RExpr right, Idx idx)
        {
            auto div = (right(0) * right(0) + right(1) * right(1));

            if(idx == 0)
                return (left(0) * right(0) + left(1) * right(1)) / div;
            else
                return (left(1) * right(0) - left(0) * right(1)) / div;
        }
    };

    template<typename LExpr, typename RExpr>
    struct divides_impl<LExpr, RExpr, std::enable_if_t<
        (is_complex_expr<LExpr>::value && !is_complex_expr<RExpr>::value)
        || (!is_complex_expr<LExpr>::value && is_complex_expr<RExpr>::value)>>
    {
        using leaf_t = complex<decltype(std::declval<expr_value_t<LExpr>>() / std::declval<expr_value_t<RExpr>>())>;

        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left / right;
        }
    };
    // =================================================================================================================

    template<typename Expr>
    struct negate_impl<Expr, std::enable_if_t<is_complex_expr<Expr>::value>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return -arg;
        }
    };

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct equal_to_impl<LExpr, RExpr, std::enable_if_t<is_complex_expr<LExpr>::value || is_complex_expr<RExpr>::value>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left == right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct not_equal_to_impl<LExpr, RExpr, std::enable_if_t<is_complex_expr<LExpr>::value || is_complex_expr<RExpr>::value>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left != right;
        }
    };

    // =================================================================================================================
}}