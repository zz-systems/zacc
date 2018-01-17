//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include "util/type/type_casts.hpp"
#include "util/type/type_traits.hpp"

namespace zacc { namespace math {

    template<typename _Vec>
    struct make_vec
    {
        template<typename... Args>
        static constexpr auto impl(Args&&... arg) {
            return _Vec {std::forward<Args>(arg)...};
        };
    };
    /*template<typename... Args>
    struct make_vec<std::tuple<Args...>>
    {
        template<typename... Args2 = Args...>
        static constexpr auto impl(Args2&&... arg) {
            return std::make_tuple(std::forward<Args2>(arg)...);
        };
    };
*/
    template<typename _Vec, typename T>
    constexpr auto reshape_i_xy(T index, T width) {
        return make_vec<_Vec>::impl(index % width, index / width);
    }

    template<typename _Vec, typename T>
    constexpr auto reshape_i_xyz(T index, T width, T height) {
        return make_vec<_Vec>::impl(index % width, (index / width) % height, index / (width * height));
    }

    template<typename T>
    constexpr auto reshape_xy_i(T x, T y, T width) {
        return x + width * y;
    }

    template<typename T>
    constexpr auto reshape_xyz_i(T x, T y, T z, T width, T height) {
        return x + width * y + width * height * z;
    }

    template<typename T, size_t _Rows, size_t _Cols>
    struct alignas(alignof(T)) __mat;
        
    template<typename T, size_t _Rows, size_t _Cols>
    struct alignas(alignof(T)) mat;

        // @struct mat
    /// @brief matrix
    template<typename T, size_t _Rows, size_t _Cols>
    struct alignas(alignof(T)) __mat
    {
        /// data container
        std::array<T, _Rows * _Cols> data;

        constexpr __mat() {};


        constexpr __mat(const __mat& rhs)
                : data(rhs.data)
        { }

        constexpr __mat(__mat&& rhs) noexcept
                : data(std::move(rhs.data))
        { }

        constexpr __mat& operator=(const __mat& rhs)
        {
            data = rhs.data;
            return *this;
        }

        constexpr __mat& operator=(__mat&& rhs) noexcept
        {
            data = std::move(rhs.data);
            return *this;
        }

        template<typename U>
        constexpr __mat(const __mat<U, _Rows, _Cols> &rhs)
                : data(array_cast<T>(rhs.data))
        { };

        constexpr __mat(std::initializer_list<T> init_list)
        {
            std::copy(std::begin(init_list), std::end(init_list), std::begin(data));
        }

        template<typename U = T>
        constexpr __mat(std::initializer_list<std::initializer_list<U>> init_list)
        {
            int index = 0;

            for(auto row : init_list)
            {
                for(auto col : row)
                {
                    data[index++] = static_cast<T>(col);
                }
            }
        }

        template<typename U = T>
        constexpr __mat(std::initializer_list<mat<U, _Cols, 1>> init_list)
        {
            int index = 0;

            for(auto row : init_list)
            {
                for(auto col : row.data)
                {
                    data[index++] = static_cast<T>(col);
                }
            }
        }

        constexpr T& operator()(size_t i)       { return data[i]; }
        constexpr const T& operator()(size_t i) const { return data[i]; }

        constexpr T& operator()(size_t y, size_t x)       { return data[reshape_xy_i(x, y, _Cols)]; }
        constexpr const T& operator()(size_t y, size_t x) const { return data[reshape_xy_i(x, y, _Cols)]; }

        constexpr T& at(size_t x, size_t y)
        {
            if (x >= _Cols || y >= _Rows)
                throw std::out_of_range("mat::at");

            return data[reshape_xy_i(x, y, _Cols)];
        }

        constexpr const T& at(size_t x, size_t y) const
        {
            if (x >= _Cols || y >= _Rows)
                throw std::out_of_range("mat::at");

            return data[reshape_xy_i(x, y, _Cols)];
        }

        inline auto get_row(size_t row) const
        {
            mat<T, _Cols, 1> result;

            for (size_t col = 0; col < _Cols; col++)
                result(col) = this->operator()(row, col);

            return result;
        }
    };

    // @struct mat
    /// @brief matrix
    template<typename T>
    struct alignas(alignof(T)) __mat<T, 1, 1>
    {
        /// data container
        union
        {
            std::array<T, 1> data;

            T value;
        };

        constexpr __mat() {};

        constexpr __mat(const __mat& rhs)
                : data(rhs.data)
        { }

        constexpr __mat(__mat&& rhs) noexcept
                : data(std::move(rhs.data))
        { }

        constexpr __mat(const T &all)
                : value(all)
        { }

        template<typename U>
        constexpr __mat(const __mat<U, 1, 1> &rhs)
                : data(array_cast<T>(rhs.data))
        { }

        constexpr __mat(std::initializer_list<T> init_list)
        {
            std::copy(std::begin(init_list), std::end(init_list), std::begin(data));
        }

        constexpr __mat& operator=(const __mat& rhs)
        {
            data = rhs.data;
            return *this;
        }

        constexpr __mat& operator=(__mat&& rhs) noexcept
        {
            data = std::move(rhs.data);
            return *this;
        }


        constexpr T& operator()(size_t)       { return data[0]; }
        constexpr const T& operator()(size_t) const { return data[0]; }

        constexpr T& operator()(size_t, size_t)       { return data[0]; }
        constexpr const T& operator()(size_t, size_t) const { return data[0]; }

        constexpr T& at(size_t i)
        {
            if (i >= 1)
                throw std::out_of_range("mat::at");

            return data[i];
        }

        constexpr const T& at(size_t i) const
        {
            if (i >= 1)
                throw std::out_of_range("mat::at");

            return data[i];
        }
    };

    // @struct mat
    /// @brief matrix
    template<typename T>
    struct alignas(alignof(T)) __mat<T, 2, 1>
    {
        /// data container
        union
        {
            std::array<T, 2> data;

            struct
            {
                T x, y;
            };
        };
        constexpr __mat() {};

        constexpr __mat(const __mat& rhs)
                : data(rhs.data)
        { }

        constexpr __mat(__mat&& rhs) noexcept
                : data(std::move(rhs.data))
        { }

        constexpr __mat& operator=(const __mat& rhs)
        {
            data = rhs.data;
            return *this;
        }

        constexpr __mat& operator=(__mat&& rhs) noexcept
        {
            data = std::move(rhs.data);
            return *this;
        }

        constexpr __mat(const T &all)
                : x(all), y(all)
        { };

        constexpr __mat(const T &x, const T &y)
                : x(x), y(y)
        { };

        template<typename U>
        constexpr __mat(const __mat<U, 2, 1> &rhs)
                : data(array_cast<T>(rhs.data))
        { }

        constexpr __mat(std::initializer_list<T> init_list)
        {
            std::copy(std::begin(init_list), std::end(init_list), std::begin(data));
        }


        constexpr T& operator()(size_t i)       { return data[i]; }
        constexpr const T& operator()(size_t i) const { return data[i]; }

        constexpr T& operator()(size_t y, size_t)       { return data[y]; }
        constexpr const T& operator()(size_t y, size_t) const { return data[y]; }

        constexpr T& at(size_t i)
        {
            if (i >= 3)
                throw std::out_of_range("mat::at");

            return data[i];
        }

        constexpr const T& at(size_t i) const
        {
            if (i >= 3)
                throw std::out_of_range("mat::at");

            return data[i];
        }
    };

    // @struct mat
    /// @brief matrix
    template<typename T>
    struct alignas(alignof(T)) __mat<T, 3, 1>
    {
        /// data container
        union
        {
            std::array<T, 3> data;

            struct
            {
                T x, y, z;
            };
        };

        constexpr __mat() {};

        constexpr __mat(const __mat& rhs)
                : data(rhs.data)
        { }

        constexpr __mat& operator=(const __mat& rhs)
        {
            data = rhs.data;
            return *this;
        }

        constexpr __mat& operator=(__mat&& rhs) noexcept
        {
            data = std::move(rhs.data);
            return *this;
        }

        constexpr __mat(__mat&& rhs) noexcept
                : data(std::move(rhs.data))
        { }

        constexpr __mat(const T &all)
                : x(all), y(all), z(all)
        { };

        constexpr __mat(const T &x, const T &y, const T &z)
                : x(x), y(y), z(z)
        { };
        template<typename U>
        constexpr __mat(const __mat<U, 3, 1> &rhs)
                : data(array_cast<T>(rhs.data))
        { };

        constexpr __mat(std::initializer_list<T> init_list)
        {
            std::copy(std::begin(init_list), std::end(init_list), std::begin(data));
        }

        constexpr T& operator()(size_t i)       { return data[i]; }
        constexpr const T& operator()(size_t i) const { return data[i]; }

        constexpr T& operator()(size_t y, size_t)       { return data[y]; }
        constexpr const T& operator()(size_t y, size_t) const { return data[y]; }

        constexpr T& at(size_t i)
        {
            if (i >= 3)
                throw std::out_of_range("mat::at");

            return data[i];
        }

        constexpr const T& at(size_t i) const
        {
            if (i >= 3)
                throw std::out_of_range("mat::at");

            return data[i];
        }
    };



    // @struct mat
    /// @brief matrix
    template<typename T, size_t _Rows, size_t _Cols>
    struct alignas(alignof(T)) mat : __mat<T, _Rows, _Cols>
    {
        static_assert(_Rows * _Cols > 0, "Wrong dimensions for a matrix");


        using self_t = mat<T, _Rows, _Cols>;
        using base_t = __mat<T, _Rows, _Cols>;
        
        using base_t::data;

        static constexpr size_t rows()     { return _Rows; }
        static constexpr size_t cols()     { return _Cols; }
        static constexpr size_t size()     { return _Rows * _Cols; }

        /// default constructor
        constexpr mat() : base_t()
        {}

        // Unusable in MSVC.
        //template<typename... Args, restrict_args<T, Args...>* = nullptr>
        //mat(Args&&... args) noexcept
        //        : data{static_cast<T>(std::forward<Args>(args))...}
        //{}

        /// MEMO: NEVER use greedy Args&&... in combination with copy constructor
        template<typename... Args>
        constexpr  mat(Args&&... arg) noexcept
                : base_t(std::forward<Args>(arg)...)
        {}

        constexpr mat(std::initializer_list<T> init_list)
                : base_t(init_list)
        {}

        template<typename U = T>
        constexpr mat(std::initializer_list<std::initializer_list<U>> init_list)
                : base_t(init_list)
        {}

        template<typename U = T>
        constexpr mat(std::initializer_list<mat<U, _Cols, 1>> init_list)
                : base_t(init_list)
        {}

        /// @brief access
        /// @{        

        

        /// @}

        //__attribute__((optimize("unroll-loops")))
        constexpr explicit operator bool() const
        {
            for(size_t i = 0; i < size(); i++)
                if(!is_set(base_t::operator()(i)))
                    return false;

            return true;
        }

        template<typename U = T>
        constexpr operator typename std::enable_if<_Rows == 1 && _Cols == 1, U >::type () const
        {
            return base_t::operator()(0);
        }

        //__attribute__((optimize("unroll-loops")))
        constexpr auto transpose() const
        {
            mat<T, _Cols, _Rows> result;

            for(int n = 0; n < _Rows; n++)
            {
                for(int m = 0; m < _Cols; m++)
                {
                    result(m, n) = (*this)(n, m);
                }
            }

            return result;
        };

        constexpr auto normalize() const
        {
            return *this / magnitude();
        }

        constexpr auto magnitude() const
        {
            return vsqrt(sqr_magnitude());
        }

        //__attribute__((optimize("unroll-loops")))
        constexpr auto sqr_magnitude() const
        {
            T sum = base_t::data[0] * base_t::data[0];

            for(size_t i = 1; i < size(); i++)
                sum = sum + data[i] * data[i];

            return sum;
        }

        //__attribute__((optimize("unroll-loops")))
        constexpr auto dot(const self_t &other) const
        {
            T result = data[0] * other(0);

            for(size_t i = 1; i < size(); i++)
                result = result + data[i] * other(i);

            return result;
        }

        constexpr auto cross(const self_t &other)
        {
            static_assert(_Rows * _Cols == 3, "cross product only for 3-D vector");

            return self_t
                    {
                            data[1] * other(2) - data[2] * other(1),
                            data[2] * other(0) - data[0] * other(2),
                            data[0] * other(1) - data[1] * other(0)
                    };
        };
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
        static constexpr const bool value = is_zval<T>::value || std::is_floating_point<T>::value || std::is_integral<T>::value;
    };


    template<typename T, typename U, size_t N, size_t M>
    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator +(const mat<T, N, M> &a, const U &b) { return a + static_cast<mat<T, N, M>>(b); }

    template<typename T, typename U, size_t N, size_t M>
    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator +(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) + b; }

    template<typename T, typename U, size_t N, size_t M>
    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator -(const mat<T, N, M> &a, const U &b) { return a - static_cast<mat<T, N, M>>(b); }

    template<typename T, typename U, size_t N, size_t M>
    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator -(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) - b; }

    template<typename T, typename U, size_t N, size_t M>
    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator *(const mat<T, N, M> &a, const U &b) { return a * static_cast<mat<T, N, M>>(b); }

    template<typename T, typename U, size_t N, size_t M>
    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator *(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) * b; }

    template<typename T, typename U, size_t N, size_t M>
    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator /(const mat<T, N, M> &a, const U &b) { return a / static_cast<mat<T, N, M>>(b); }

    template<typename T, typename U, size_t N, size_t M>
    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator /(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) / b; }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<typename zval_traits<T>::bval_t, N, M>	operator <(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<typename zval_traits<T>::bval_t, N, M> result;

        for(size_t i = 0; i < N * M; i++)
            result(i) = a(i) < b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<typename zval_traits<T>::bval_t, N, M>	operator <=(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<typename zval_traits<T>::bval_t, N, M> result;

        for(size_t i = 0; i < N * M; i++)
            result(i) = a(i) <= b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<typename zval_traits<T>::bval_t, N, M>	operator >(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<typename zval_traits<T>::bval_t, N, M> result;

        for(size_t i = 0; i < N * M; i++)
            result(i) = a(i) > b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<typename zval_traits<T>::bval_t, N, M>	operator >=(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<typename zval_traits<T>::bval_t, N, M> result;

        for(size_t i = 0; i < N * M; i++)
            result(i) = a(i) >= b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<typename zval_traits<T>::bval_t, N, M>	operator ==(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<typename zval_traits<T>::bval_t, N, M> result;

        for(size_t i = 0; i < N * M; i++)
            result(i) = a(i) == b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<typename zval_traits<T>::bval_t, N, M>	operator !=(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<typename zval_traits<T>::bval_t, N, M> result;

        for(size_t i = 0; i < N * M; i++)
            result(i) = a(i) != b(i);

        return result;
    }
    /// @brief add
    /// @relates mat
    template<typename T, typename U, size_t rows, size_t cols>
    //__attribute__((optimize("unroll-loops")))
    mat<T, rows, cols> operator+(const mat<T, rows, cols>& a, const mat<U, rows, cols>& b)
    {
        mat<T, rows, cols> result;

        for(size_t i = 0; i < rows * cols; i++)
            result(i) = a(i) + b(i);

        return result;
    };

    /// @brief sub
    /// @relates mat
    template<typename T, typename U, size_t rows, size_t cols>
    //__attribute__((optimize("unroll-loops")))
    mat<T, rows, cols> operator-(const mat<T, rows, cols>& a, const mat<U, rows, cols>& b)
    {
        mat<T, rows, cols> result;

        for(size_t i = 0; i < rows * cols; i++)
            result(i) = a(i) - b(i);

        return result;
    };

    /// @brief add scalar
    /// @relates mat
    template<typename T, typename U, size_t rows, size_t cols>
    //__attribute__((optimize("unroll-loops")))
    mat<T, rows, cols> operator+(const mat<T, rows, cols>& a, const scalar<U>& b)
    {
        mat<T, rows, cols> result;

// #pragma unroll
        for(size_t i = 0; i < rows * cols; i++)
            result(i) = a(i) + b;

        return result;
    };

    /// @brief sub scalar
    /// @relates mat
    template<typename T, size_t rows, size_t cols>
    //__attribute__((optimize("unroll-loops")))
    mat<T, rows, cols> operator-(const mat<T, rows, cols>& a, const T& b)
    {
        mat<T, rows, cols> result;

// #pragma unroll
        for(size_t i = 0; i < rows * cols; i++)
            result(i) = a(i) - b;

        return result;
    };

    /// @brief mul scalar
    /// @relates mat
    template<typename T, size_t rows, size_t cols>
    //__attribute__((optimize("unroll-loops")))
    mat<T, rows, cols> operator*(const mat<T, rows, cols>& a, const T& b)
    {
        mat<T, rows, cols> result;

// #pragma unroll
        for(size_t i = 0; i < rows * cols; i++)
            result(i) = a(i) * b;

        return result;
    };

    /// @brief div scalar
    /// @relates mat
    template<typename T, size_t rows, size_t cols>
    //__attribute__((optimize("unroll-loops")))
    mat<T, rows, cols> operator/(const mat<T, rows, cols>& a, const T& b)
    {
        mat<T, rows, cols> result;

// #pragma unroll
        for(size_t i = 0; i < rows * cols; i++)
            result(i) = a(i) / b;

        return result;
    };


    /// @brief scale (mul)
    /// @relates mat
    template<typename T, typename U, size_t rows>
    //__attribute__((optimize("unroll-loops")))
    auto operator*(const vec<T, rows>& a, const vec<U, rows>& b)
    {
        vec<T, rows> result;

// #pragma unroll
        for(size_t i = 0; i < rows; i++)
            result(i) = a(i) * b(i);

        return result;
    };

    /// @brief scale (div)
    /// @relates mat
    template<typename T, typename U, size_t rows>
    //__attribute__((optimize("unroll-loops")))
    auto operator/(const vec<T, rows>& a, const vec<U, rows>& b)
    {
        vec<T, rows> result;

// #pragma unroll
        for(size_t i = 0; i < rows; i++)
            result(i) = a(i) / b(i);

        return result;
    };

    /// @brief gegneric matrix mul
    /// @relates mat
    template<typename T, typename U, size_t N, size_t cols, size_t M>
    //__attribute__((optimize("unroll-loops")))
    mat<T, N, M> operator*(const mat<T, N, cols>& a, const mat<U, cols, M>& b)
    {
        mat<T, N, M> result;

        for (size_t n = 0; n < N; n++)
        {
            for (size_t m = 0; m < M; m++)
            {
                T temp = a(n, 0) * b(0, m);

                for (size_t c = 1; c < cols; c++)
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
    //__attribute__((optimize("unroll-loops")))
    scalar<T> operator*(const mat<T, 1, n>& a, const mat<U, n, 1>& b)
    {
        //scalar<T> result;

        auto result = a(0) * b(0);

        //result(0) = a(0) * b(0);

        for(size_t i = 1; i < n; i++)
            result = result + a(i) * b(i);

        return result;
    };

    template<typename T, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    auto clamp_int32(const mat<T, N, M> &a)
    {
        mat<T, N, M> result;

        for(size_t i = 0; i < N * M; i++)
            result(i) = clamp_int32(a(i));

        return result;
    }

    template<typename mask, typename data, size_t N>
    //__attribute__((optimize("unroll-loops")))
    inline auto vsel(const vec<mask, N> &condition, const vec<data, N> &choice1, const vec<data, N> &choice2)
    {
        vec<data, N> result;

        for(size_t i = 0; i < N; i++)
            result(i) = vsel<mask, data>(condition(i), choice1(i), choice2(i));

        return result;
    }


    template<typename T, typename U, size_t N>
    //__attribute__((optimize("unroll-loops")))
    inline auto clamp_int32(const vec<T, N> &a)
    {
        vec<T, N> result;

        for(size_t i = 0; i < N; i++)
            result(i) = a(i).trunc();

        return result;
    }

    template<typename T, size_t elems>
    inline std::ostream& operator<<(std::ostream& out, const vec<T, elems> &other)
    {
        auto print_row = [&]()
        {
            for(size_t i = 0; i < elems; i++)
                out << other(i) << " ";
        };

        out << "[ ";
        print_row();
        out << "]";

        return out;
    }

    template<typename T, size_t rows, size_t cols>
    inline std::ostream& operator<<(std::ostream& out, const mat<T, rows, cols> &other)
    {
        auto print_row = [&](auto rowi)
        {
            for(size_t coli = 0; coli < cols; coli++)
                out << other(rowi, coli) << " ";
        };


        if(rows == 1)
        {
            out << "[ ";
            print_row(0);
            out << "]";
        }
        else
        {
            out << std::endl;
            // TODO: Proper box chars. ncurses?
            for(size_t rowi = 0; rowi < rows; rowi++)
            {
                switch(rowi)
                {
                    case 0:         out << (unsigned char)218 << " "; break;
                    case rows - 1:  out << (unsigned char)192 << " "; break;
                    default:        out << (unsigned char)189 << " "; break;
                }

                print_row(rowi);

                switch(rowi)
                {
                    case 0:         out << (unsigned char)191 << std::endl; break;
                    case rows - 1:  out << (unsigned char)217 << std::endl; break;
                    default:        out << (unsigned char)189 << std::endl; break;
                }
            }
        }

        return out;
    }
}}