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

namespace zacc { namespace expressions {

    template<typename Expr = void>
    struct identity : un_expr<identity<>, Expr>
    {
        using un_expr<identity<>, Expr>::un_expr;
    };

    template<>
    struct identity<void>
    {
        template<typename Arg>
        static auto apply(Arg arg)
        {
            return arg;
        }
    };


    template<typename LExpr = void, typename RExpr = void>
    struct plus : bin_expr<plus<>, LExpr, RExpr>
    {
        using bin_expr<plus<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct plus<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left + right;
        }
    };

    template<typename RExpr = void>
    struct promote : un_expr<promote<>, RExpr>
    {
        using un_expr<promote<>, RExpr>::un_expr;
    };

    template<>
    struct promote<void>
    {
        template<typename RArg>
        static auto apply(RArg right)
        {
            return +right;
        }
    };

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct minus : bin_expr<minus<>, LExpr, RExpr>
    {
        using bin_expr<minus<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct minus<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left - right;
        }
    };

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct multiplies : bin_expr<multiplies<>, LExpr, RExpr>
    {
        using bin_expr<multiplies<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct multiplies<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left * right;
        }
    };

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct divides : bin_expr<divides<>, LExpr, RExpr>
    {
        using bin_expr<divides<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct divides<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left / right;
        }
    };

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct modulus : bin_expr<modulus<>, LExpr, RExpr>
    {
        using bin_expr<modulus<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct modulus<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left % right;
        }
    };

    // =================================================================================================================

    template<typename RExpr = void>
    struct negate : un_expr<negate<>, RExpr>
    {
        using un_expr<negate<>, RExpr>::un_expr;
    };

    template<>
    struct negate<void>
    {
        template<typename RArg>
        static auto apply(RArg right)
        {
            return -right;
        }
    };

    template<typename Expr>
    struct negate<negate<Expr>> : identity<Expr>
    {
        negate(negate<Expr> expr)
            : identity<Expr>(expr._expr)
        {}
    };

    // =================================================================================================================

    /*
     * TODO:
     * Fused multiply–add can usually be relied on to give more accurate results.
     * However, William Kahan has pointed out that it can give problems if used unthinkingly.[3]
     * If x2 − y2 is evaluated as ((x×x) − y×y) using fused multiply–add, then the result may
     * be negative even when x = y due to the first multiplication discarding low significance
     * bits. This could then lead to an error if, for instance, the square root of the result
     * is then evaluated.
     */
    template<typename AExpr = void, typename BExpr = void, typename CExpr = void>
    struct fmadd : func_expr<fmadd<>, AExpr, BExpr, CExpr>
    {
        using func_expr<fmadd<>, AExpr, BExpr, CExpr>::func_expr;
    };

    template<>
    struct fmadd<void, void, void>
    {
        template<typename AArg, typename BArg, typename CArg>
        static auto apply(AArg a, BArg b, CArg c)
        {
            //std::cout << "fma" << std::endl;
            return a * b + c;
        }
    };

    template<typename AExpr, typename BExpr, typename CExpr>
    struct plus<AExpr, multiplies<BExpr, CExpr>> : fmadd<AExpr, BExpr, CExpr>
    {
        plus(AExpr left, multiplies<BExpr, CExpr> right)
            : fmadd<AExpr, BExpr, CExpr>(left, right._left, right._right)
        {}
    };

    template<typename AExpr, typename BExpr, typename CExpr>
    struct plus<multiplies<AExpr, BExpr>, CExpr> : fmadd<AExpr, BExpr, CExpr>
    {
        plus(multiplies<AExpr, BExpr> left, CExpr right)
            : fmadd<AExpr, BExpr, CExpr>(left._left, left._right, right)
        {}
    };

    /*
     * cover cases such as y = a * a + b * b;
     */
    template<typename AExpr, typename BExpr, typename CExpr, typename DExpr>
    struct plus<multiplies<AExpr, BExpr>, multiplies<CExpr, DExpr>> : fmadd<AExpr, BExpr, multiplies<CExpr, DExpr>>
    {
        plus(multiplies<AExpr, BExpr> left, multiplies<CExpr, DExpr> right)
            : fmadd<AExpr, BExpr, multiplies<CExpr, DExpr>>(left._left, left._right, right)
        {}
    };

    // =================================================================================================================

    template<typename Left, typename Right>
    bin_expr_t<plus, lit, Left, Right>
    operator+(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<minus, lit, Left, Right>
    operator-(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<multiplies, lit, Left, Right>
    operator*(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<divides, lit, Left, Right>
    operator/(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<modulus, lit, Left, Right>
    operator%(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Right>
    un_expr_t<negate, Right>
    operator-(const Right& right)
    {
        return { right };
    }

    template<typename Right>
    un_expr_t<promote, Right>
    operator+(const Right& right)
    {
        return { right };
    }

    // =================================================================================================================
}}