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

#include <zacc/compute/core/traits.hpp>
#include <zacc/util/string_view.hpp>

namespace zacc {namespace compute {

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<typename Expr, typename Enable = void>
    struct identity_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct plus_impl;

    template<typename Expr, typename Enable = void>
    struct promote_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct minus_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct multiplies_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct divides_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct modulus_impl;

    template<typename Expr, typename Enable = void>
    struct negate_impl;

    template<typename AExpr, typename BExpr, typename CExpr, typename Enable = void>
    struct fmadd_impl;

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct equal_to_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct not_equal_to_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct greater_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct less_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct greater_equal_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct less_equal_impl;

    // =================================================================================================================
    // BOOLEAN
    // =================================================================================================================

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct logical_and_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct logical_or_impl;

    template<typename Expr, typename Enable = void>
    struct logical_not_impl;

    // =================================================================================================================
    // BITWISE
    // =================================================================================================================

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_and_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_or_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_xor_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_shl_impl;

    template<typename LExpr, typename RExpr, typename Enable = void>
    struct bit_shr_impl;

    template<typename Expr, typename Enable = void>
    struct bit_not_impl;

    // =================================================================================================================

}}