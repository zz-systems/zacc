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

#include <zacc/compute/core/core.hpp>
#include <zacc/math/matrix.hpp>


namespace zacc { namespace compute {

    // =================================================================================================================

    struct __mat_expr {};

    template<typename T>
    struct mat_expr : expr<mat_expr<T>>, __mat_expr
    {
        static_assert(T::rows() * T::cols() > 0, "Invalid dimensions");

        static constexpr size_t rows = T::rows;
        static constexpr size_t cols = T::cols;
        static constexpr size_t size = rows * cols;
    };

    template<typename T>
    struct mat_term : mat_expr<mat_term<T>>
    {
        mat_term& _self;

        constexpr mat_term()
            : _self(*this)
        {}

        size_t id() const {
            //return std::hash<std::string>()(std::to_string(reinterpret_cast<std::uintptr_t>(&_self)));
            return std::hash<std::uintptr_t>()(reinterpret_cast<std::uintptr_t>(&_self));
        }
    };

    template<typename BinOp, typename Left, typename Right>
    struct mat_bin_expr : mat_expr<mat_bin_expr<BinOp, Left, Right>>
    {
        Left _left;
        Right _right;

        constexpr mat_bin_expr(Left left, Right right)
            : _left(left), _right(right)
        {}

        auto eval(size_t i, size_t j) const
        {
            return BinOp::apply(_left(i, j), _right(i, j));
        }
    };

    template<typename UnOp, typename Expr>
    struct mat_un_expr : mat_expr<mat_un_expr<UnOp, Expr>>
    {
        Expr _expr;

        mat_un_expr(Expr expr)
            : _expr(expr)
        {}

        auto operator()(size_t i, size_t j)
        {
            return UnOp::apply(_expr(i, j));
        }
    };

    template<typename BinOp, typename Left, typename Right>
    struct mat_mul_expr : mat_expr<mat_mul_expr<BinOp, Left, Right>>
    {
        Left _left;
        Right _right;

        mat_mul_expr(Left left, Right right)
            : _left(left), _right(right)
        {}

        auto eval(size_t i, size_t k) const
        {
            auto result = _left(i, 0) * _right(0, k);

            for(int j = 1; j < Right::rows(); j++)
            {
                result += _left(i, j) * _right(j, k);
            }

            return result;
        }
    };

    template<typename T, typename Enable = void>
    struct mat_traits
    {
        static constexpr size_t rows = 0;
        static constexpr size_t cols = 0;
        static constexpr size_t size = 0;

        static constexpr bool is_mat    = false;
        static constexpr bool is_vec    = false;
        static constexpr bool is_scalar = true;
    };

    template<typename T>
    struct mat_traits<T, std::enable_if_t<std::is_base_of<__mat_expr, T>::value>>
    {
        static constexpr size_t rows = T::rows;
        static constexpr size_t cols = T::cols;
        static constexpr size_t size = T::size;

        static constexpr bool is_mat    = rows > 1 && cols > 1;
        static constexpr bool is_vec    = rows > 1 && cols == 1;
        static constexpr bool is_scalar = rows == 1 && cols == 1;
    };

    template<typename T>
    struct is_mat_expr : std::integral_constant<bool, mat_traits<T>::is_mat>
    {};

    template<typename T>
    struct is_vec_expr : std::integral_constant<bool, mat_traits<T>::is_vec>
    {};

    template<typename T>
    struct is_scalar_expr : std::integral_constant<bool, mat_traits<T>::is_scalar>
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

//    template<typename Expr>
//    struct identity<std::enable_if_t<is_mat_expr<Expr>::value, Expr>>
//        : mat_un_expr<identity<std::enable_if_t<is_mat_expr<Expr>::value, Expr>>, Expr>
//    {
//
//    };
//
//    template<typename LExpr, typename RExpr>
//    struct plus<LExpr, RExpr, std::enable_if_t<is_mat_mat<LExpr, RExpr>::value>>
//    {
//
//    };
}}