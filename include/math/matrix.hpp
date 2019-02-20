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

    template<typename _Vec, typename T>
    constexpr auto reshape_i_xy(T index, T width) {
        return make_vec<_Vec>::impl(index % width, index / width);
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



    template<typename T, size_t Rows, size_t Cols>
    struct alignas(alignof(T)) mat;

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

    // @struct mat
    /// @brief matrix
    template<typename T, size_t Rows, size_t Cols>
    struct alignas(alignof(T)) __mat
            : inherit<ops_meta<mat<T, Rows, Cols>, T, true>, plus, minus, multiplies, divides, modulus, increment, decrement>
            //: compose_t<plus, minus, multiplies, divides, composable<mat<T, Rows, Cols>>::template type>
    {
        static_assert(Rows * Cols > 0, "Wrong dimensions for a matrix");

        static constexpr size_t rows()     { return Rows; }
        static constexpr size_t cols()     { return Cols; }
        static constexpr size_t size()     { return Rows * Cols; }

        /// data container
        std::array<T, Rows * Cols> data;

        // =============================================================================================================

        constexpr __mat()
            : data {}
        {}

        constexpr __mat(const __mat& other) noexcept
            : data { other.data }
        {}

        constexpr __mat(__mat&& other) noexcept
            : __mat()
        {
            swap(*this, other);
        }

        constexpr __mat& operator=(__mat other) noexcept
        {
            swap(*this, other);
            return *this;
        }

        // =============================================================================================================

        template<typename U>
        constexpr __mat(const __mat<U, Rows, Cols>& other)
            : data { array_cast<T>(other.data) }
        {}


        template<typename U, typename std::enable_if<std::is_convertible<U, T>::value, void**>::type = nullptr>
        constexpr __mat(std::initializer_list<U> init_list)
        {
            std::transform(init_list.begin(), init_list.end(), data.begin(), [](U i) { return static_cast<T> (i); });
        }

        template<typename U>
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

        template<typename U>
        constexpr __mat(std::initializer_list<__mat<U, Cols, 1>> init_list)
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

        // =============================================================================================================

        friend void swap(__mat& one, __mat& other) // nothrow
        {
            // enable ADL (not necessary in our case, but good practice)
            using std::swap;

            // by swapping the members of two objects,
            // the two objects are effectively swapped
            swap(one.data, other.data);
        }

        // =============================================================================================================

        constexpr auto transpose() const
        {
            mat<T, Rows, Cols> result;

            for(int n = 0; n < Rows; n++)
            {
                for(int m = 0; m < Cols; m++)
                {
                    result(m, n) = (*this)(n, m);
                }
            }

            return result;
        };

        constexpr mat<T, Rows, Cols> normalize() const
        {
            return *static_cast<const mat<T, Rows, Cols>*>(this) / magnitude();
        }

        constexpr T magnitude() const
        {
            return vsqrt(sqr_magnitude());
        }

        constexpr T sqr_magnitude() const
        {
            return std::accumulate(begin(), end(), static_cast<T>(0), [](auto sum, auto i) { return sum + i * i; });
        }



        constexpr auto begin() { return data.begin(); }
        constexpr auto begin() const { return data.begin(); }

        constexpr auto end() { return data.end(); }
        constexpr auto end() const { return data.end(); }

        // =============================================================================================================

        constexpr T&        operator()(size_t i) &
        {
            return data[i];
        }

        constexpr T&&       operator()(size_t i) &&
        {
            return std::move(data[i]);
        }

        constexpr T const&  operator()(size_t i) const&
        {
            return data[i];
        }

        constexpr T& at(size_t i) &
        {
            if (i >= size())
                throw std::out_of_range("mat::at");

            return (*this)(i);
        }

        constexpr T&& at(size_t i) &&
        {
            if (i >= size())
                throw std::out_of_range("mat::at");

            return std::move((*this)(i));
        }

        constexpr T const& at(size_t i) const&
        {
            if (i >= size())
                throw std::out_of_range("mat::at");

            return (*this)(i);
        }

        // =============================================================================================================

        // Row - Major
        constexpr T& operator()(size_t y, size_t x) &
        {
            return data[reshape_xy_i(x, y, Cols)];
        }

        constexpr T&& operator()(size_t y, size_t x) &&
        {
            return std::move(data[reshape_xy_i(x, y, Cols)]);
        }

        constexpr T const& operator()(size_t y, size_t x) const&
        {
            return data[reshape_xy_i(x, y, Cols)];
        }

        constexpr T& at(size_t y, size_t x) &
        {
            if (x >= Cols || y >= Rows)
                throw std::out_of_range("mat::at");

            return (*this)(y, x);
        }

        constexpr T&& at(size_t y, size_t x) &&
        {
            if (x >= Cols || y >= Rows)
                throw std::out_of_range("mat::at");

            return std::move((*this)(y, y));
        }

        constexpr T const& at(size_t y, size_t x) const&
        {
            if (x >= Cols || y >= Rows)
                throw std::out_of_range("mat::at");

            return (*this)(y, x);
        }

//        inline mat<T, Cols, 1> get_row(size_t row) const
//        {
//            return row_overlay[row];
//        }
//
//        inline mat<T, 1, Rows> get_col(size_t col) const
//        {
//            return col_overlay[col];
//        }

        // =============================================================================================================

        constexpr T dot(const mat<T, Rows, Cols> &other) const
        {
            return zacc::accumulate(data.begin(), data.end(), other.begin(), static_cast<T>(0), [](auto sum, auto i, auto o) { return sum + i * o; });
        }
    };

    template<typename T, size_t Rows, size_t Cols>
    struct alignas(alignof(T)) mat : public __mat<T, Rows, Cols>
    {
        using __mat<T, Rows, Cols>::data;
        using __mat<T, Rows, Cols>::__mat;

        template<typename U, typename std::enable_if<std::is_convertible<U, T>::value, void**>::type = nullptr>
        constexpr mat(const U& all) noexcept
        {
            std::fill(data.begin(), data.end(), static_cast<T>(all));
        }
    };

    // @struct mat
    /// @brief matrix
    template<typename T>
    struct alignas(alignof(T)) mat<T, 1, 1> : public __mat<T, 1, 1>
    {
        using __mat<T, 1, 1>::data;
        using __mat<T, 1, 1>::__mat;

        template<typename U, typename std::enable_if<std::is_convertible<U, T>::value, void**>::type = nullptr>
        constexpr mat(const U& all) noexcept
            : __mat<T, 1, 1> {{ static_cast<T>(all) }}
        {}
    };

    // @struct mat
    /// @brief matrix
    template<typename T>
    struct alignas(alignof(T)) mat<T, 2, 1> : public __mat<T, 2, 1>
    {
        using __mat<T, 2, 1>::data;
        using __mat<T, 2, 1>::__mat;

        auto& x() const { return data[0]; }
        auto& x()       { return data[0]; }

        auto& y() const { return data[1]; }
        auto& y()       { return data[1]; }

        template<typename U, typename std::enable_if<std::is_convertible<U, T>::value, void**>::type = nullptr>
        constexpr mat(const U& all)
            : __mat<T, 2, 1> {{ static_cast<T>(all), static_cast<T>(all) }}
        {}

        template<typename U, typename V>
        constexpr mat(const U& x, const V& y)
            : __mat<T, 2, 1> {{ static_cast<T>(x), static_cast<T>(y) }}
        {}
    };

    // @struct mat
    /// @brief matrix
    template<typename T>
    struct alignas(alignof(T)) mat<T, 3, 1> : public __mat<T, 3, 1>
    {
        using __mat<T, 3, 1>::data;
        using __mat<T, 3, 1>::__mat;

        auto& x() const { return data[0]; }
        auto& x()       { return data[0]; }

        auto& y() const { return data[1]; }
        auto& y()       { return data[1]; }

        auto& z() const { return data[2]; }
        auto& z()       { return data[2]; }

        template<typename U, typename std::enable_if<std::is_convertible<U, T>::value, void**>::type = nullptr>
        constexpr mat(const U& all)
                : __mat<T, 3, 1> {{ static_cast<T>(all), static_cast<T>(all), static_cast<T>(all) }}
        {}

        template<typename U, typename V, typename W>//, typename std::enable_if<std::is_convertible<U, T>::value, void**>::type = nullptr>
        constexpr mat(const U& x, const V& y,  const W& z)
                : __mat<T, 3, 1> {{ static_cast<T>(x), static_cast<T>(y), static_cast<T>(z) }}
        {}

        constexpr mat cross(const mat &other)
        {
            return {
                    data[1] * other(2) - data[2] * other(1),
                    data[2] * other(0) - data[0] * other(2),
                    data[0] * other(1) - data[1] * other(0)
            };
        };
    };



        // =============================================================================================================

        template<typename T, size_t Rows, size_t Cols>
        bval_t<T> operator ==(const mat<T, Rows, Cols>& a, const mat<T, Rows, Cols>& b)
        {
            for(size_t i = 0; i < Rows * Cols; i++)
            {
                if(a(i) != b(i))
                    return false;
            }

            return true;
        }

        template<typename T, size_t Rows, size_t Cols>
        bval_t<T> operator !=(const mat<T, Rows, Cols>& a, const mat<T, Rows, Cols>& b)
        {
            return !(a == b);
        }

        template<typename Container, typename UnaryOperation>
        Container apply(const Container& m, UnaryOperation op)
        {
            Container result;

            std::transform(m.begin(), m.end(), result.begin(), op);

            return result;
        }

        template<typename Container, typename BinaryOperation>
        Container apply(const Container& one, const Container& other, BinaryOperation op)
        {
            Container result;

            std::transform(one.begin(), one.end(), other.begin(), result.begin(), op);

            return result;
        }


//        template<typename T, typename U, size_t N, size_t M>
//        inline mat<T, N, M> &operator +=(mat<T, N, M>& a, const U& b) { return a = (a + b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline mat<T, N, M> &operator -=(mat<T, N, M>& a, const U& b) { return a = (a - b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline mat<T, N, M> &operator *=(mat<T, N, M>& a, const U& b) { return a = (a * b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline mat<T, N, M> &operator /=(mat<T, N, M>& a, const U& b) { return a = (a / b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline mat<T, N, M> &operator +=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a + b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline mat<T, N, M> &operator -=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a - b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline mat<T, N, M> &operator *=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a * b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline mat<T, N, M> &operator /=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a / b); }


        template<typename T>
        struct is_scalar
        {
            static constexpr const bool value = is_zval<T>::value || std::is_floating_point<T>::value || std::is_integral<T>::value || std::is_convertible<T, scalar<T>>::value;
        };


//        template<typename T, typename U, size_t N, size_t M, typename std::enable_if<std::is_convertible<U, T>::value, void**>::type = nullptr>
//        inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator +(const mat<T, N, M> &a, const U &b) { return a + static_cast<mat<T, N, M>>(b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator +(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) + b; }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator -(const mat<T, N, M> &a, const U &b) { return a - static_cast<mat<T, N, M>>(b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator -(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) - b; }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator *(const mat<T, N, M> &a, const U &b) { return a * static_cast<mat<T, N, M>>(b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator *(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) * b; }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator /(const mat<T, N, M> &a, const U &b) { return a / static_cast<mat<T, N, M>>(b); }
//
//        template<typename T, typename U, size_t N, size_t M>
//        inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator /(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) / b; }

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> operator-(const mat<T, Rows, Cols>& a)
        {
            return apply(a, std::negate<T>());
        };

        // Vector + Scalar ================================================================================================

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> operator+(const mat<T, Rows, Cols>& one, param_t<T> other)
        {
            return apply(one, [&other](auto i) { return i + static_cast<T>(other); });
        };

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> operator-(const mat<T, Rows, Cols>& one, param_t<T> other)
        {
            return apply(one, [&other](auto i) { return i - static_cast<T>(other); });
        };

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> operator*(const mat<T, Rows, Cols>& one, param_t<T> other)
        {
            return apply(one, [&other](auto i) { return i * static_cast<T>(other); });
        };

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> operator/(const mat<T, Rows, Cols>& one, param_t<T> other)
        {
            return apply(one, [&other](auto i) { return i / static_cast<T>(other); });
        };


        /// @brief special case: row-vector * column-vector
        /// @relates mat
        template<typename T, size_t Rows>
        scalar<T> operator*(const __mat<T, 1, Rows>& a, const __mat<T, Rows, 1>& b)
        {
            return zacc::accumulate(a.begin(), a.end(), b.begin(), static_cast<T>(0), [](auto acc, auto a, auto b) { return acc + a * b; });
        };

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> operator+(const mat<T, Rows, Cols>& one, const mat<T, Rows, Cols>& other)
        {
            return apply(one, other, std::plus<T>());
        };

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> operator-(const mat<T, Rows, Cols>& one, const mat<T, Rows, Cols>& other)
        {
            return apply(one, other, std::minus<T>());
        };

        template<typename T, size_t Rows, size_t Cols, size_t N>
        mat<T, Rows, Cols> operator*(const mat<T, Rows, N>& a, const mat<T, N, Cols>& b)
        {
            mat<T, Rows, Cols> result;

            for (size_t r = 0; r < Rows; r++)
            {
                for (size_t c = 0; c < Cols; c++)
                {
                    T temp = a(r, 0) * b(0, c);

                    for (size_t n = 1; n < N; n++)
                    {
                        temp = temp + a(r, n) * b(n, c);
                    }

                    result(r, c) = temp;
                }
            }

            return result;
        };

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> clamp_int32(const mat<T, Rows, Cols> &one)
        {
            return apply(one, [](auto i) { return i.trunc(); });
        }

//        friend mat clamp_int32(const mat &one)
//        {
//            return apply(one, clamp_int32);
//        }

        template<typename T, size_t Rows, size_t Cols>
        mat<T, Rows, Cols> vsel(const bval_t<T> &condition, const mat<T, Rows, Cols> &if_value, const mat<T, Rows, Cols> &else_value)
        {
            return apply(if_value, else_value, [&condition](auto i, auto e) { return i.when(condition).otherwise(e); });
        }




    /// @}



    /// @name reshape specializations
    /// @{

    template<typename _Vec, typename T>
    constexpr auto reshape(T index, vec2<T> dim) {
        return reshape_i_xy<_Vec>(index, dim.x());
    }

    template<typename _Vec, typename T>
    constexpr auto reshape(T index, vec3<T> dim) {
        return reshape_i_xyz<_Vec>(index, dim.x(), dim.y());
    }

    template<typename T>
    constexpr auto reshape(vec2<T> pos, vec2<T> dim) {
        return reshape_xy_i(pos.x(), pos.y(), dim.x());
    }

    template<typename T>
    constexpr auto reshape(vec3<T> pos, vec3<T> dim) {
        return reshape_xyz_i(pos.x(), pos.y(), pos.z(), dim.x(), dim.y());
    }

    /// @}

//    /// @name operations
//    /// @{
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline mat<T, N, M> &operator +=(mat<T, N, M>& a, const U& b) { return a = (a + b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline mat<T, N, M> &operator -=(mat<T, N, M>& a, const U& b) { return a = (a - b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline mat<T, N, M> &operator *=(mat<T, N, M>& a, const U& b) { return a = (a * b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline mat<T, N, M> &operator /=(mat<T, N, M>& a, const U& b) { return a = (a / b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline mat<T, N, M> &operator +=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a + b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline mat<T, N, M> &operator -=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a - b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline mat<T, N, M> &operator *=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a * b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline mat<T, N, M> &operator /=(mat<T, N, M>& a, const mat<U, N, M>& b) { return a = (a / b); }
//
//    template<typename T>
//    struct is_scalar
//    {
//        static constexpr const bool value = is_zval<T>::value || std::is_floating_point<T>::value || std::is_integral<T>::value || std::is_convertible<T, scalar<T>>::value;
//    };
//
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator +(const mat<T, N, M> &a, const U &b) { return a + static_cast<mat<T, N, M>>(b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator +(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) + b; }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator -(const mat<T, N, M> &a, const U &b) { return a - static_cast<mat<T, N, M>>(b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator -(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) - b; }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator *(const mat<T, N, M> &a, const U &b) { return a * static_cast<mat<T, N, M>>(b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator *(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) * b; }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator /(const mat<T, N, M> &a, const U &b) { return a / static_cast<mat<T, N, M>>(b); }
//
//    template<typename T, typename U, size_t N, size_t M>
//    inline std::enable_if_t<is_scalar<U>::value, mat<T, N, M>> operator /(const U &a, const mat<T, N, M> &b) { return static_cast<mat<T, N, M>>(a) / b; }
//
//
//
//
//
//
//    /// @brief scale (mul)
//    /// @relates mat
//    template<typename T, typename U, size_t rows>
//    auto operator*(const vec<T, rows>& a, const vec<U, rows>& b)
//    {
//        vec<T, rows> result;
//
//        std::transform(a.begin(), a.end(), b.begin(), result.begin(), std::multiplies<T>());
//
//        return result;
//    };
//
//    /// @brief scale (div)
//    /// @relates mat
//    template<typename T, typename U, size_t rows>
//    auto operator/(const vec<T, rows>& a, const vec<U, rows>& b)
//    {
//        vec<T, rows> result;
//
//        std::transform(a.begin(), a.end(), b.begin(), result.begin(), std::divides<T>());
//
//        return result;
//    };



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