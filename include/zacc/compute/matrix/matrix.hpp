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

    struct matrix_transpose_op ;

    struct matrix_conjugate_op;

    struct matrix_dot_op;

    // =================================================================================================================

    template<typename T, size_t Rows, size_t Cols>
    struct mat : variable<mat<T, Rows, Cols>>
    {
        using value_type = T;
        constexpr static auto dim = std::make_tuple(Rows, Cols);

        static_assert(Rows * Cols > 0, "Invalid dimensions");


        // =============================================================================================================

        constexpr mat()
            : variable<mat>()
        {}

        constexpr mat(std::initializer_list<T> init_list)
            : variable<mat>()
        {
            std::copy(std::begin(init_list), std::end(init_list), std::begin(_data));
        }

        using variable<mat<T, Rows, Cols>>::variable;

        // =============================================================================================================

        constexpr auto transpose() const
        {
            return expression<matrix_transpose_op, mat>(*this);
        };

        constexpr T dot(mat<T, Rows, Cols> const &other) const
        {
            return 0;
            //return zacc::accumulate(data.begin(), data.end(), other.begin(), static_cast<T>(0), [](auto sum, auto i, auto o) { return sum + i * o; });
        }

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

        // =============================================================================================================

        constexpr auto begin() { return _data.begin(); }
        constexpr auto begin() const { return _data.begin(); }

        constexpr auto end() { return _data.end(); }
        constexpr auto end() const { return _data.end(); }

    private:
        alignas(T) typename container<T, Rows * Cols>::type _data;
    };

    // =================================================================================================================
    // Tags
    // =================================================================================================================

    struct matrix_op : operator_base
    {};

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    struct matrix_identity_op : matrix_op, identity_op
    {};

    struct matrix_add_op : matrix_op, add_op
    {};

    struct matrix_promote_op : matrix_op, promote_op
    {};

    struct matrix_sub_op : matrix_op, sub_op
    {};

    struct matrix_mul_op : matrix_op, mul_op
    {};

    struct matrix_scalar_mul_op : matrix_op, mul_op
    {};

    struct matrix_div_op : matrix_op, div_op
    {};

    struct matrix_scalar_div_op : matrix_op, div_op
    {};

    struct matrix_neg_op : matrix_op, neg_op
    {};

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    struct matrix_equal_to_op : matrix_op, equal_to_op
    {};

    struct matrix_not_equal_to_op : matrix_op, not_equal_to_op
    {};

    // =================================================================================================================
    // SPECIAL
    // =================================================================================================================

    struct matrix_transpose_op : matrix_op
    {};

    struct matrix_conjugate_op : matrix_op
    {};

    struct matrix_dot_op : matrix_op
    {};
}}