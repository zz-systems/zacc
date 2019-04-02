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
    struct logical_and : bin_expr<logical_and<>, LExpr, RExpr>
    {
        using bin_expr<logical_and<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct logical_and<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left && right;
        }
    };

    // =================================================================================================================

    template<typename LExpr = void, typename RExpr = void>
    struct logical_or : bin_expr<logical_or<>, LExpr, RExpr>
    {
        using bin_expr<logical_or<>, LExpr, RExpr>::bin_expr;
    };

    template<>
    struct logical_or<void, void>
    {
        template<typename LArg, typename RArg>
        static auto apply(LArg left, RArg right)
        {
            return left || right;
        }
    };

    // =================================================================================================================

    template<typename RExpr = void>
    struct logical_not : un_expr<logical_not<>, RExpr>
    {
        using un_expr<logical_not<>, RExpr>::un_expr;
    };

    template<>
    struct logical_not<void>
    {
        template<typename RArg>
        static auto apply(RArg right)
        {
            return !right;
        }
    };

    // =================================================================================================================
}}