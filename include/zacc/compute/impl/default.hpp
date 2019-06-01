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

#include <zacc/compute/core/defs.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<typename Expr>
    struct identity_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::scalar>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return arg;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct plus_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar && expr_traits<RExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left + right;
        }
    };

    // =================================================================================================================

    template<typename Expr>
    struct promote_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::scalar>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return +arg;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct minus_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar && expr_traits<RExpr>::expr_tag == expr_tag::scalar>>
    {
        static_assert(expr_traits<LExpr>::expr_tag == expr_tag::scalar, "LExpr");
        static_assert(expr_traits<RExpr>::expr_tag == expr_tag::scalar, "RExpr");

        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left - right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct multiplies_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar && expr_traits<RExpr>::expr_tag == expr_tag::scalar>>
    {
        static_assert(expr_traits<LExpr>::expr_tag == expr_tag::scalar, "LExpr");
        static_assert(expr_traits<RExpr>::expr_tag == expr_tag::scalar, "RExpr");

        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left * right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct divides_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left / right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct modulus_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left % right;
        }
    };

    // =================================================================================================================

    template<typename Expr>
    struct negate_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::scalar>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return -arg;
        }
    };

    // =================================================================================================================

    template<typename AExpr, typename BExpr, typename CExpr>
    struct fmadd_impl<AExpr, BExpr, CExpr, std::enable_if_t<expr_traits<AExpr>::expr_tag == expr_tag::scalar>>
    {
        static_assert(expr_traits<AExpr>::expr_tag == expr_tag::scalar, "AExpr");
//        static_assert(expr_traits<BExpr>::expr_tag == expr_tag::scalar, "BExpr");
//        static_assert(expr_traits<CExpr>::expr_tag == expr_tag::scalar, "CExpr");

        template<typename AArg, typename BArg, typename CArg>
        static auto apply(AArg a, BArg b, CArg c)
        {
            return a * b + c;
        }
    };

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct equal_to_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left == right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct not_equal_to_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left != right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct greater_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left > right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct less_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left < right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct greater_equal_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left >= right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct less_equal_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
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
    struct logical_and_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left && right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct logical_or_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left || right;
        }
    };

    // =================================================================================================================

    template<typename Expr>
    struct logical_not_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::scalar>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return !arg;
        }
    };

    // =================================================================================================================
    // BITWISE OPERATIONS
    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_and_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left & right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_or_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left | right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_xor_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left ^ right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_shl_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left << right;
        }
    };

    // =================================================================================================================

    template<typename LExpr, typename RExpr>
    struct bit_shr_impl<LExpr, RExpr, std::enable_if_t<expr_traits<LExpr>::expr_tag == expr_tag::scalar>>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left >> right;
        }
    };

    // =================================================================================================================

    template<typename Expr>
    struct bit_not_impl<Expr, std::enable_if_t<expr_traits<Expr>::expr_tag == expr_tag::scalar>>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return ~arg;
        }
    };

    // =================================================================================================================
}}