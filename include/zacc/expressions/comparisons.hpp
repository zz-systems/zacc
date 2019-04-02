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

    template<typename LExpr = void, typename RExpr = void>
    struct equal_to : bin_expr<equal_to<>, LExpr, RExpr>
    {
        using bin_expr<equal_to<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct equal_to<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left == right;
        }
    };

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct not_equal_to : bin_expr<not_equal_to<>, LExpr, RExpr>
    {
        using bin_expr<not_equal_to<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct not_equal_to<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left != right;
        }
    };

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct greater : bin_expr<greater<>, LExpr, RExpr>
    {
        using bin_expr<greater<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct greater<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left > right;
        }
    };

    // =================================================================================================================


    template<typename LExpr = void, typename RExpr = void>
    struct less : bin_expr<less<>, LExpr, RExpr>
    {
        using bin_expr<less<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct less<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left < right;
        }
    };

    // =================================================================================================================


    template<typename LExpr = void, typename RExpr = void>
    struct greater_equal : bin_expr<greater_equal<>, LExpr, RExpr>
    {
        using bin_expr<greater_equal<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct greater_equal<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left >= right;
        }
    };

    // =================================================================================================================


    template<typename LExpr = void, typename RExpr = void>
    struct less_equal : bin_expr<less_equal<>, LExpr, RExpr>
    {
        using bin_expr<less_equal<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct less_equal<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left <= right;
        }
    };

    // =================================================================================================================

    template<typename Left, typename Right>
    bin_expr_t<equal_to, lit, Left, Right>
    operator==(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<not_equal_to, lit, Left, Right>
    operator!=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<greater, lit, Left, Right>
    operator>(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<less, lit, Left, Right>
    operator<(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<greater_equal, lit, Left, Right>
    operator>=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    template<typename Left, typename Right>
    bin_expr_t<less_equal, lit, Left, Right>
    operator<=(const Left& left, const Right& right)
    {
        return { left, right };
    }

    // =================================================================================================================
}}