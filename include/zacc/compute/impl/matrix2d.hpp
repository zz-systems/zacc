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
    struct identity_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::matrix>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return arg;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct plus_impl<LExpr, RExpr, std::enable_if_t<can_add<LExpr, RExpr>::value>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left + right;
        }
    };

    // =================================================================================================================

    template<typename Expr>
    struct promote_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::matrix>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return +arg;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct minus_impl<LExpr, RExpr, std::enable_if_t<can_subtract<LExpr, RExpr>::value>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left - right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct multiplies_impl<LExpr, RExpr, std::enable_if_t<can_multiply<LExpr, RExpr>::value>>
    {
        using leaf_t = mat<expr_value_t<LExpr>, rows_v<LExpr>, cols_v<RExpr>>;

        template<typename Row, typename Col>
        static auto apply(LExpr left, RExpr right, Row i, Col k)
        {
            auto result = left(i, 0) * right(0, k);

            for(size_t j = 1; j < rows_v<RExpr>; j++)
            {
                result += left(i, j) * right(j, k);
            }

            return result;
        }
    };

    template<typename LExpr, typename RExpr>
    struct multiplies_impl<LExpr, RExpr, std::enable_if_t<can_scale<LExpr, RExpr>::value>>
    {
        using leaf_t = mat<expr_value_t<LExpr>,
            (is_scalar_expr<LExpr>::value ? rows_v<RExpr> : rows_v<LExpr>),
            (is_scalar_expr<LExpr>::value ? cols_v<RExpr> : cols_v<LExpr>)>;

        template<typename Row, typename Col>
        static auto apply(LExpr left, RExpr right, Row i, Col j)
        {
            return left(i, j) * right(i, j);
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct divides_impl<LExpr, RExpr, std::enable_if_t<can_divide<LExpr, RExpr>::value>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left / right;
        }
    };

    // =================================================================================================================

    template<typename Expr>
    struct negate_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::matrix>>
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
    struct equal_to_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::matrix>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left == right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct not_equal_to_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::matrix>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left != right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct greater_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::matrix>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left > right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct less_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::matrix>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left < right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct greater_equal_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::matrix>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left >= right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct less_equal_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::matrix>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left <= right;
        }
    };

    // =================================================================================================================
    // BOOLEAN
    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct logical_and_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::matrix>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left && right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct logical_or_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::matrix>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left || right;
        }
    };

    // =================================================================================================================

    template<typename Expr>
    struct logical_not_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::matrix>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return !arg;
        }
    };

    // =================================================================================================================


    template<typename Expr>
    struct transpose_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::matrix>>
    {
        template<typename Rows, typename Cols>
        static auto apply(Expr expr, Rows rows, Cols cols)
        {
            return expr(cols, rows);
        }
    };

    template<typename... Expr>
    constexpr string_view name_of<transpose_impl<Expr...>> = "ᵀ";
}}