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
#include <zacc/compute/eval/matrix2d.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename Vec>
    struct make_vec
    {
        template<typename... Args>
        static constexpr auto impl(Args&&... arg) {
            return Vec {std::forward<Args>(arg)...};
        };
    };

    template<typename Vec, typename T>
    constexpr auto reshape_i_xy(T index, T width) {
        return make_vec<Vec>::impl(index % width, index / width);
    }

    template<typename T>
    constexpr std::tuple<T, T> reshape_i_xy(T index, T width) {
        return make_vec<std::tuple<T, T>>::impl(index % width, index / width);
    }

    template<typename _Vec, typename T>
    constexpr auto reshape_i_xyz(T index, T width, T height) {
        return make_vec<_Vec>::impl(index % width, (index / width) % height, index / (width * height));
    }

    template<typename T>
    constexpr std::tuple<T, T> reshape_i_xyz(T index, T width, T height) {
        return make_vec<std::tuple<T, T>>::impl(index % width, (index / width) % height, index / (width * height));
    }

    template<typename T>
    constexpr auto reshape_xy_i(T x, T y, T width) {
        return x + width * y;
    }

    template<typename T>
    constexpr auto reshape_xyz_i(T x, T y, T z, T width, T height) {
        return x + width * y + width * height * z;
    }

    // =================================================================================================================

    template<typename T, size_t Rows, size_t Cols>
    struct mat;

    /// @name specializations
    /// @{

    /// 2x2 matrix alias
    template<typename T>
    using mat2x2 = mat<T, 2, 2>;

    /// 3x2 matrix alias
    template<typename T>
    using mat3x2 = mat<T, 3, 2>;

    /// 2x3 matrix alias
    template<typename T>
    using mat2x3 = mat<T, 2, 3>;

    /// 3x3 matrix alias
    template<typename T>
    using mat3x3 = mat<T, 3, 3>;

    /// Nx1 matrix = N-row vector
    template<typename T, size_t N>
    using vec = mat<T, N, 1>;

    /// 2x1 matrix = 2-row vector alias
    template<typename T>
    using vec2 = vec<T, 2>;

    /// 3x1 matrix = 3-row vector alias
    template<typename T>
    using vec3 = vec<T, 3>;

    /// 1x1 matrix = scalar
    template<typename T>
    using scalar = mat<T, 1, 1>;

    // =================================================================================================================

    template<typename Expr, typename = void>
    struct transpose_impl;

    template<typename Expr>
    struct transpose : un_expr<quote<transpose_impl>, Expr>
    {
        using leaf_t = mat<expr_value_t<Expr>, cols_v<Expr>, rows_v<Expr>>;

        using un_expr<quote<transpose_impl>, Expr>::un_expr;
    };

    // =================================================================================================================

    template<typename T, size_t Rows, size_t Cols>
    struct mat : term<mat<T, Rows, Cols>>
    {
        static_assert(Rows * Cols > 0, "Invalid dimensions");

        static constexpr size_t rows = Rows;
        static constexpr size_t cols = Cols;
        static constexpr size_t size = Rows * Cols;

        using value_type = T;
        using eval_type = matrix2d_evaluator;


        constexpr static uint64_t mask = 0;
        constexpr static expr_tag expr_tag = expr_tag::matrix;

        // =============================================================================================================

        constexpr mat() = default;

        constexpr mat(const mat& other) = default;
        constexpr mat& operator=(mat const& other) = default;

        constexpr mat(mat&& other) noexcept = default;
        constexpr mat& operator=(mat&& other) noexcept = default;

        // =============================================================================================================

        constexpr mat(std::initializer_list<T> init_list)
        {
            recorder::current() << declare_expr<mat>(*this);

            std::copy(std::begin(init_list), std::end(init_list), std::begin(_data));
        }

        template<typename Expr>
        constexpr mat(Expr expr) noexcept
        {
            auto d = declare_expr<mat>(*this);
            auto e = assign_expr<mat, Expr>(*this, expr);

            recorder::current() << d << e;
            matrix2d_evaluator::current() << e;
        }

        template<typename Expr>
        constexpr mat& operator=(Expr const& expr) noexcept
        {
            auto e = assign_expr<mat, Expr>(*this, expr);

            recorder::current() << e;
            matrix2d_evaluator::current() << e;

            return *this;
        }

        // =============================================================================================================

        constexpr auto transpose() const
        {
            return zacc::compute::transpose<mat> { *this };
        };

        constexpr mat<T, Rows, Cols> normalize() const
        {
            return 1;
        }

        constexpr T magnitude() const
        {
            return 1;
        }

        constexpr T sqr_magnitude() const
        {
            return 1;
        }

        constexpr auto begin() { return _data.begin(); }
        constexpr auto begin() const { return _data.begin(); }

        constexpr auto end() { return _data.end(); }
        constexpr auto end() const { return _data.end(); }

        // =============================================================================================================

        constexpr value_type& eval(size_t i)
        {
            return _data[i];
        }

        constexpr value_type const& eval(size_t i) const
        {
            return _data[i];
        }

        constexpr value_type& eval(size_t y, size_t x)
        {
            return _data[reshape_xy_i(x, y, Cols)];
        }

        constexpr value_type const& eval(size_t y, size_t x) const
        {
            return _data[reshape_xy_i(x, y, Cols)];
        }

        // =============================================================================================================

        constexpr T dot(const mat<T, Rows, Cols> &other) const
        {
            return 0;
            //return zacc::accumulate(data.begin(), data.end(), other.begin(), static_cast<T>(0), [](auto sum, auto i, auto o) { return sum + i * o; });
        }

    private:
        alignas(T) typename container<T, size>::type _data;
    };

    // =================================================================================================================

    template<template<class, size_t, size_t> class Expr, typename T, size_t Rows, size_t Cols>
    struct expr_traits<Expr<T, Rows, Cols>, std::is_base_of<mat<T, Rows, Cols>, Expr<T, Rows, Cols>>>
    {
        constexpr static size_t size = T::size;
        constexpr static uint64_t mask = T::mask;
        constexpr static expr_tag expr_tag = T::expr_tag;
    };

    // =================================================================================================================

    static_assert(is_mat_expr<mat<int, 2, 2>>::value, "mat<int, 2, 2> should be a matrix expression.");
    static_assert(!is_mat_expr<mat<int, 1, 2>>::value, "mat<int, 1, 2> should not be a matrix expression.");
    static_assert(!is_mat_expr<mat<int, 2, 1>>::value, "mat<int, 1, 2> should not be a matrix expression.");
    static_assert(!is_mat_expr<mat<int, 1, 1>>::value, "mat<int, 1, 1> should not be a matrix expression.");

    static_assert(is_vec_expr<mat<int, 1, 2>>::value, "mat<int, 1, 2> should be a vector expression.");
    static_assert(is_vec_expr<mat<int, 2, 1>>::value, "mat<int, 2, 1> should be a vector expression.");
    static_assert(!is_vec_expr<mat<int, 2, 2>>::value, "mat<int, 2, 2> should not be a vector expression.");
    static_assert(!is_vec_expr<mat<int, 1, 1>>::value, "mat<int, 1, 1> should not be a vector expression.");

    static_assert(is_scalar_expr<mat<int, 1, 1>>::value, "mat<int, 1, 1> should be a scalar expression.");
    static_assert(!is_scalar_expr<mat<int, 2, 1>>::value, "mat<int, 2, 1> should not be a scalar expression.");
    static_assert(!is_scalar_expr<mat<int, 1, 2>>::value, "mat<int, 1, 2> should not be a scalar expression.");
    static_assert(!is_scalar_expr<mat<int, 2, 2>>::value, "mat<int, 2, 2> should not be a scalar expression.");


    static_assert(can_multiply<mat<int, 2, 2>, mat<int, 2, 2>>::value, "");


}}