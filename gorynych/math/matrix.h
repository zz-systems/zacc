//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

/**
 * @file matrix.h
 *
 * @brief experimental matrix implementation
 *
 * Provides dimension-aware matrix support.
 *
 * @remark Don't use it yet. Untested.
 */

#include <array>

namespace zzsystems { namespace gorynych {

        template<typename T>
        using Unqualified = typename std::remove_cv<
                typename std::remove_reference<T>::type
        >::type;

        template <typename ... Types>
        struct template_all; // UNDEFINED

        template <>
        struct template_all<>
                : std::true_type {};

        template <typename ... Types>
        struct template_all<std::false_type, Types...>
                : std::false_type {};

        template <typename ... Types>
        struct template_all<std::true_type, Types...>
                : template_all<Types...>::type {};

        template< typename... CONDITIONS >
        struct all_true;

        template<>
        struct all_true<>
        {
            const static bool value = true;
        };

        template< typename CONDITION, typename... CONDITIONS >
        struct all_true< CONDITION, CONDITIONS... >
        {
            const static bool value = CONDITION::value && all_true<CONDITIONS...>::value;
        };

    /// @struct mat
    /// @brief matrix
    template<typename T, size_t rows, size_t cols>
    struct alignas(alignof(T)) mat
    {
        static_assert(rows * cols > 0, "Wrong dimensions for a matrix");

        template<typename allowed_type, typename... types >
        using restrict_args =
        typename std::enable_if<
                all_true< std::is_convertible<types, allowed_type>... >::value, int
        >::type;


        typedef mat<T, rows, cols> self_t;

        /// data container
        std::array<T, rows * cols> data;


        constexpr size_t get_rows()     const   { return rows; }
        constexpr size_t get_cols()     const   { return cols; }
        constexpr size_t get_length()   const   { return rows * cols; }

        /// default constructor
        mat() = default;

        // typename... Args

        template<typename... Args, restrict_args<T, Args...>* = nullptr>
        mat(Args&&... args) noexcept
            : data{{static_cast<T>(std::forward<Args>(args))...}}
        {}

        /*template<typename... Args, restrict_args<mat<T, 1, cols>, Args...>* = nullptr>
        mat(mat<T,1, cols>&& first, Args&&... args) noexcept
                : mat{first, std::forward<Args>(args)...}
        {}*/

        mat(std::initializer_list<T> init_list) noexcept
        {
            std::copy(init_list.begin(), init_list.end(), data.begin());
        }

        mat(std::initializer_list<std::initializer_list<T>> init_list) noexcept
        {
            int index = 0;

            for(auto row : init_list)
            {
                for(auto col : row)
                {
                    at(index++) = col;
                }
            }
        }

//        mat(std::initializer_list<mat<T, 1, cols>> init_list)
//        {
//            int index = 0;
//
//            for(auto row : init_list)
//            {
//                for(auto col : row.data)
//                {
//                    at(index++) = col;
//                }
//            }
//        }

        template<typename U = T>
        mat(std::initializer_list<mat<U, 1, cols>> init_list) noexcept
        {
            int index = 0;

            for(auto row : init_list)
            {
                for(auto col : row.data)
                {
                    at(index++) = col;
                }
            }
        }

        /// memory location constructor
        mat(const T* data) noexcept : data(data)
        {}

        /// matrix move constructor
        mat(const mat& rhs) noexcept
        {
            //std::move(rhs.data.begin(), rhs.data.end(), data.begin());
            data = rhs.data;
        }

        template<typename U = T>
        mat(const mat<U, rows, cols>& rhs) noexcept
        {
            std::copy(rhs.data.begin(), rhs.data.end(), data.begin());
        }

        /// @brief access
        /// @{

        inline T &operator()(int row, int col)
        {
            return at(row, col);
        }

        inline T &operator()(int i)
        {
            return at(i);
        }

        inline T &at(int row, int col)
        {
            return data[col + row * cols];
        }

        inline T &at (int i)
        {
            return data[i];
        }

        inline T operator()(int row, int col) const
        {
            return at(row, col);
        }

        inline T at(int row, int col) const
        {
            return data[col + row * cols];
        }

        inline T operator()(int i) const
        {
            return at(i);
        }

        inline T at (int i) const
        {
            return data[i];
        }


        inline mat<T, 1, cols> get_row(int row) const
        {
            return at(row, 0);
        };

        inline mat<T, 1, cols> &get_row(int row)
        {
            return at(row, 0);
        };

        /// @}

        explicit operator bool() const
        {
            for(int i = 0; i < get_length(); i++)
                if(!is_set(at(i)))
                    return false;

            return true;
        }

        template<typename U = T>
        const enable_if_t<rows == 1 && cols >= 2, U> x() const { return data[0]; }
        template<typename U = T>
        const enable_if_t<rows == 1 && cols >= 2, U> y() const { return data[1]; }
        template<typename U = T>
        const enable_if_t<rows == 1 && cols >= 3, U> z() const { return data[2]; }

        template<typename U = T>
        enable_if_t<rows == 1 && cols >= 2, U> &x() { return data[0]; }
        template<typename U = T>
        enable_if_t<rows == 1 && cols >= 2, U> &y() { return data[1]; }
        template<typename U = T>
        enable_if_t<rows == 1 && cols >= 3, U> &z() { return data[2]; }

        template<typename U = T>
        operator typename std::enable_if<rows == 1 && cols == 1, U >::type () const
        {
            return data[0];
        }

        inline mat<T, cols, rows> transpose() const
        {
            mat<T, cols, rows> result;

            for(int n = 0; n < rows; n++)
            {
                for(int m = 0; m < cols; m++)
                {
                    result(m, n) = at(n, m);
                }
            }

            return result;
        };

        inline self_t normalize() const
        {
            return *this / magnitude();
        }

        inline T magnitude() const
        {
            return vsqrt(sqr_magnitude());
        }

        inline T sqr_magnitude() const
        {
            T sum = at(0) * at(0);

            for(int i = 1; i < get_length(); i++)
                sum = sum + at(i) * at(i);

            return sum;
        }

        inline T dot(const self_t &other)
        {
            T result = at(0) * other(0);

            for(int i = 1; i < get_length(); i++)
                result = result + at(i) * other(i);

            return result;
        }

        inline self_t cross(const self_t &other)
        {
            //enable_if_t<rows * cols == 3, self_t>
            static_assert(rows * cols == 3, "cross product only for 3-D vector");

            return self_t
                    (
                            at(1) * other(2) - at(2) * other(1),
                            at(2) * other(0) - at(0) * other(2),
                            at(0) * other(1) - at(1) * other(0)
                    );
        };
        //DEFINE_ARITHMETIC_CVT_OPS_ANY(self_t)
    };

    /// @}

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
    using vec = mat<T, 1, N>;

    /// 2x1 matrix = 2-row vector alias
    template<typename T>
    using vec2 = vec<T, 2>;

    /// 3x1 matrix = 3-row vector alias
    template<typename T>
    using vec3 = vec<T, 3>;

    /// 1x1 matrix = scalar
    template<typename T>
    using scalar = mat<T, 1, 1>;

    /// @}

    /// @name operations
    /// @{

    template<typename T, typename U, size_t N, size_t M>
        inline mat<T, N, M> &operator +=(mat<T, N, M>& a, const U& b) { return a = (a + b); }

    template<typename T, typename U, size_t N, size_t M>
        inline mat<T, N, M> &operator -=(mat<T, N, M>& a, const U& b) { return a = (a - b); }

    template<typename T, typename U, size_t N, size_t M>
        inline mat<T, N, M> &operator *=(mat<T, N, M>& a, const U& b) { return a = (a * b); }

    template<typename T, typename U, size_t N, size_t M>
        inline mat<T, N, M> &operator /=(mat<T, N, M>& a, const U& b) { return a = (a / b); }

    template<typename T, typename U, size_t N, size_t M>
        inline mat<T, N, M> &operator +=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a + b); }

    template<typename T, typename U, size_t N, size_t M>
        inline mat<T, N, M> &operator -=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a - b); }

    template<typename T, typename U, size_t N, size_t M>
        inline mat<T, N, M> &operator *=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a * b); }

    template<typename T, typename U, size_t N, size_t M>
        inline mat<T, N, M> &operator /=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a / b); }

    template<typename T>
    struct is_scalar
    {
        static constexpr const bool value = is_arithmetic<T>::value || is_vreal<T>::value || is_vint<T>::value;
    };
        // enable_if_t<is_arithmetic<U>::value, mat<T, N, M>>
        
	template<typename T, typename U, size_t N, size_t M> 
        inline enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator +(const mat<T, N, M> &a, const U &b) { return a + static_cast<mat<T, N, M>>(b); }
	
    template<typename T, typename U, size_t N, size_t M>
        inline enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator +(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) + b; }
	
    template<typename T, typename U, size_t N, size_t M>
        inline enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator -(const mat<T, N, M> &a, const U &b) { return a - static_cast<mat<T, N, M>>(b); }
	
    template<typename T, typename U, size_t N, size_t M>
        inline enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator -(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) - b; }
	
    template<typename T, typename U, size_t N, size_t M>
        inline enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator *(const mat<T, N, M> &a, const U &b) { return a * static_cast<mat<T, N, M>>(b); }
	
    template<typename T, typename U, size_t N, size_t M>
        inline enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator *(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) * b; }
	
    template<typename T, typename U, size_t N, size_t M>
        inline enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator /(const mat<T, N, M> &a, const U &b) { return a / static_cast<mat<T, N, M>>(b); }
	
    template<typename T, typename U, size_t N, size_t M>
        inline enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator /(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) / b; }

    template<typename T, typename U, size_t N, size_t M>
	    inline mat<T, N, M>	operator <(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) < b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
	    inline mat<T, N, M>	operator <=(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) <= b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
	    inline mat<T, N, M>	operator >(const mat<T, N, M>& a, const mat<U, N, M>& b) 
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) > b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
	    inline mat<T, N, M>	operator >=(const mat<T, N, M>& a, const mat<U, N, M>& b) 
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) >= b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
	    inline mat<T, N, M>	operator ==(const mat<T, N, M>& a, const mat<U, N, M>& b) 
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) == b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
	    inline mat<T, N, M>	operator !=(const mat<T, N, M>& a, const mat<U, N, M>& b) 
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) != b(i);

        return result;
    }
    /// @brief add
    /// @relates mat
    template<typename T, typename U, size_t rows, size_t cols>
    mat<T, rows, cols> operator+(const mat<T, rows, cols>& a, const mat<U, rows, cols>& b)
    {
        mat<T, rows, cols> result;

        for(int i = 0; i < rows * cols; i++)
            result(i) = a(i) + b(i);

        return result;
    };

    /// @brief sub
    /// @relates mat
    template<typename T, typename U, size_t rows, size_t cols>
    mat<T, rows, cols> operator-(const mat<T, rows, cols>& a, const mat<U, rows, cols>& b)
    {
        mat<T, rows, cols> result;

        for(int i = 0; i < rows * cols; i++)
            result(i) = a(i) - b(i);

        return result;
    };

    /// @brief add scalar
    /// @relates mat
    template<typename T, typename U, size_t rows, size_t cols>
    mat<T, rows, cols> operator+(const mat<T, rows, cols>& a, const scalar<U>& b)
    {
        mat<T, rows, cols> result;

        for(int i = 0; i < rows * cols; i++)
            result(i) = a(i) + b;

        return result;
    };

    /// @brief sub scalar
    /// @relates mat
    template<typename T, size_t rows, size_t cols>
    mat<T, rows, cols> operator-(const mat<T, rows, cols>& a, const T& b)
    {
        mat<T, rows, cols> result;

        for(int i = 0; i < rows * cols; i++)
            result(i) = a(i) - b;

        return result;
    };

    /// @brief mul scalar
    /// @relates mat
    template<typename T, size_t rows, size_t cols>
    mat<T, rows, cols> operator*(const mat<T, rows, cols>& a, const T& b)
    {
        mat<T, rows, cols> result;

        for(int i = 0; i < rows * cols; i++)
            result(i) = a(i) * b;

        return result;
    };

    /// @brief div scalar
    /// @relates mat
    template<typename T, size_t rows, size_t cols>
    mat<T, rows, cols> operator/(const mat<T, rows, cols>& a, const T& b)
    {
        mat<T, rows, cols> result;

        for(int i = 0; i < rows * cols; i++)
            result(i) = a(i) / b;

        return result;
    };


    /// @brief scale (mul)
    /// @relates mat
    template<typename T, typename U, size_t rows>
    auto operator*(const vec<T, rows>& a, const vec<U, rows>& b)
    {
        vec<T, rows> result;

        for(int i = 0; i < rows; i++)
            result(i) = a(i) * b(i);

        return result;
    };

    /// @brief scale (div)
    /// @relates mat
    template<typename T, typename U, size_t rows>
    auto operator/(const vec<T, rows>& a, const vec<U, rows>& b)
    {
        vec<T, rows> result;

        for(int i = 0; i < rows; i++)
            result(i) = a(i) / b(i);

        return result;
    };

    /// @brief gegneric matrix mul
    /// @relates mat
    template<typename T, typename U, size_t N, size_t cols, size_t M>
    mat<T, N, M> operator*(const mat<T, N, cols>& a, const mat<U, cols, M>& b)
    {
        mat<T, N, M> result;

        for (int n = 0; n < N; n++)
        {
            for (int m = 0; m < M; m++)
            {
                T temp = a(n, 0) * b(0, m);

                for (int c = 1; c < cols; c++)
                {
                    temp = temp + a(n, c) * b(c, m);
                }

                result(n, m) = temp;
            }
        }

        return result;
    };

    /// @brief special case: row-vector * column-vector
    /// @relates mat
    template<typename T, typename U, size_t n>
    scalar<T> operator*(const mat<T, 1, n>& a, const mat<U, n, 1>& b)
    {
        scalar<T> result;

        for(int i = 0; i < n; i++)
            result(0) = result(0) + a(i) * b(i);

        return result;
    };

    /// @brief special case: column-vector * row-vector
    /// @relates mat
//    template<typename T, typename U, size_t N, size_t M>
//    /*enable_if<col == 1, mat<T, N, M>>*/ mat<T, N, M> operator*(const mat<T, N, 1>& a, const mat<U, 1, M>& b)
//    {
//        mat<T, N, M> result;
//
//        for(int n = 0; n < N; n++)
//        {
//            for(int m = 0; m < M; m++)
//            {
//                result(n, m) = a(n) * b(m);
//            }
//        }
//
//        return result;
//    };

    /// @brief special case: matrix * vector
    /// @relates mat
    template<typename T, typename U, size_t N, size_t M>
    mat<T, 1, N> operator*(const mat<T, N, M> &a, const vec<U, N> &vec)
    {
        mat<T, 1, N> result;

        for(int n = 0; n < N; n++)
        {
            T temp = a(n, 0) * vec(0);

            for(int m = 1; m < M; m++)
            {
                temp = temp + a(n, m) * vec(m);
            }

            result(n) = temp;
        }

        return result;
    };

	template<typename T, size_t N, size_t M>
	auto clamp_int32(const mat<T, N, M> &a)
	{
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = clamp_int32<T>(a(i));

        return result;
	}

    template<typename mask, typename data, size_t N>
	inline auto vsel(const vec<mask, N> &condition, const vec<data, N> &choice1, const vec<data, N> &choice2)
	{
        vec<data, N> result;

        for(int i = 0; i < N; i++)
            result(i) = vsel<mask, data>(condition(i), choice1(i), choice2(i));

        return result;
	}


    template<typename T, typename U, size_t N>
    auto clamp_int32(const vec<T, N> &a)
	{
        vec<T, N> result;

        for(int i = 0; i < N; i++)
            result(i) = vtrunc<T, U>(a(i));

        return result;
	}

}}