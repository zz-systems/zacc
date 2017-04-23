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

namespace zacc { namespace math {
    // @struct mat
    /// @brief matrix
    template<typename T, size_t rows, size_t cols>
    struct alignas(alignof(T)) mat
    {
        static_assert(rows * cols > 0, "Wrong dimensions for a matrix");


        typedef mat<T, rows, cols> self_t;

        /// data container
        std::array<T, rows * cols> data;

        static constexpr size_t get_rows()     { return rows; }
        static constexpr size_t get_cols()     { return cols; }
        static constexpr size_t get_length()   { return rows * cols; }

        /// default constructor
        //mat() = default; <- MSVC HATES this

        mat() {}

        // Unusable in MSVC.
        //template<typename... Args, restrict_args<T, Args...>* = nullptr>
        //mat(Args&&... args) noexcept
        //        : data{static_cast<T>(std::forward<Args>(args))...}
        //{}

        /// MEMO: NEVER use greedy Args&&... in combination with copy constructor
        template<typename... Args, typename = std::enable_if_t<all_true<std::is_convertible<Args, T>::value...>::value>>
        mat(Args... args) noexcept
                : data{static_cast<T>(std::forward<Args>(args))...}
        {}

        //__attribute__((optimize("unroll-loops")))
        template<typename U = T>
        mat(std::initializer_list<U> init_list) noexcept
                //: data(init_list)
        {
            std::copy(init_list.begin(), init_list.end(), data.begin());
        }

        //__attribute__((optimize("unroll-loops")))
        template<typename U = T>
        mat(std::initializer_list<std::initializer_list<U>> init_list) noexcept
        {
            int index = 0;

            for(auto row : init_list)
            {
                for(auto col : row)
                {
                    at(index++) = static_cast<T>(col);
                }
            }
        }

        template<typename U = T>
        //__attribute__((optimize("unroll-loops")))
        mat(std::initializer_list<mat<U, cols, 1>> init_list) noexcept
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


        /// matrix copy constructor
        mat(const mat& rhs) noexcept : data(rhs.data)
        { }

        template<typename U = T>
        mat(const mat<U, rows, cols>& rhs) noexcept
        {
            this->data = array_cast<T>(rhs.data);
        }

        /// @brief access
        /// @{

        inline T &operator()(int row, int col)
        {
            return data[col + row * cols];
        }

        inline T &operator()(int i)
        {
            return data[i];
        }

        inline T &at(int row, int col)
        {
            if(col >= cols || row >= rows)
                throw std::out_of_range("matrix 2D index out of range");

            return (*this)(row, col);
        }

        inline T &at (int i)
        {
            if(i > data.size())
                throw std::out_of_range("matrix 1D index out of range");

            return data[i];
        }

        inline const T &operator()(int row, int col) const
        {
            return data[col + row * cols];
        }

        inline const T &at(int row, int col) const
        {
            if(col >= cols || row >= rows)
                throw std::out_of_range("matrix 2D index out of range");

            return (*this)(row, col);
        }

        inline const T &operator()(int i) const
        {
            return data[i];
        }

        inline const T &at (int i) const
        {
            if(i > data.size())
                throw std::out_of_range("matrix 1D index out of range");

            return (*this)(i);
        }

        //__attribute__((optimize("unroll-loops")))
        inline auto get_row(int row) const
        {
            mat<T, cols, 1> result;

            for (int i = 0; i < cols; i++)
                result(i) = (*this)(row, i);

            return result;
        }

        /// @}

        //__attribute__((optimize("unroll-loops")))
        explicit operator bool() const
        {
            //return is_set(x) && is_set(y) && is_set(z);

            for(int i = 0; i < get_length(); i++)
                if(!is_set(data[i]))
                    return false;

            return true;
        }

        template<typename U = T>
        operator typename std::enable_if<rows == 1 && cols == 1, U >::type () const
        {
            return data[0];
        }

        //__attribute__((optimize("unroll-loops")))
        inline const mat<T, cols, rows> &transpose() const
        {
            mat<T, cols, rows> result;

            for(int n = 0; n < rows; n++)
            {
                for(int m = 0; m < cols; m++)
                {
                    result(m, n) = (*this)(n, m);
                }
            }

            return result;
        };

        inline const self_t &normalize() const
        {
            return *this / magnitude();
        }

        inline T magnitude() const
        {
            return vsqrt(sqr_magnitude());
        }

        //__attribute__((optimize("unroll-loops")))
        inline T sqr_magnitude() const
        {
            T sum = data[0] * data[0];

            for(int i = 1; i < get_length(); i++)
                sum = sum + data[i] * data[i];

            return sum;
        }

        //__attribute__((optimize("unroll-loops")))
        inline T dot(const self_t &other) const
        {
            T result = data[0] * other(0);

            for(int i = 1; i < get_length(); i++)
                result = result + data[i] * other(i);

            return result;
        }

        inline const self_t &cross(const self_t &other)
        {
            static_assert(rows * cols == 3, "cross product only for 3-D vector");

            return self_t
                    (
                            data[1] * other(2) - data[2] * other(1),
                            data[2] * other(0) - data[0] * other(2),
                            data[0] * other(1) - data[1] * other(0)
                    );
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
    inline mat<T, N, M>	operator <(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) < b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<T, N, M>	operator <=(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) <= b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<T, N, M>	operator >(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) > b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<T, N, M>	operator >=(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) >= b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    inline mat<T, N, M>	operator ==(const mat<T, N, M>& a, const mat<U, N, M>& b)
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i) == b(i);

        return result;
    }

    template<typename T, typename U, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
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
    //__attribute__((optimize("unroll-loops")))
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
    //__attribute__((optimize("unroll-loops")))
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
    //__attribute__((optimize("unroll-loops")))
    mat<T, rows, cols> operator+(const mat<T, rows, cols>& a, const scalar<U>& b)
    {
        mat<T, rows, cols> result;

#pragma unroll
        for(int i = 0; i < rows * cols; i++)
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

#pragma unroll
        for(int i = 0; i < rows * cols; i++)
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

#pragma unroll
        for(int i = 0; i < rows * cols; i++)
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

#pragma unroll
        for(int i = 0; i < rows * cols; i++)
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

#pragma unroll
        for(int i = 0; i < rows; i++)
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

#pragma unroll
        for(int i = 0; i < rows; i++)
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
    //__attribute__((optimize("unroll-loops")))
    scalar<T> operator*(const mat<T, 1, n>& a, const mat<U, n, 1>& b)
    {
        //scalar<T> result;

        auto result = a(0) * b(0);

        //result(0) = a(0) * b(0);

        for(int i = 1; i < n; i++)
            result = result + a(i) * b(i);

        return result;
    };

    template<typename T, size_t N, size_t M>
    //__attribute__((optimize("unroll-loops")))
    auto clamp_int32(const mat<T, N, M> &a)
    {
        mat<T, N, M> result;

        for(int i = 0; i < N * M; i++)
            result(i) = a(i).trunc();

        return result;
    }

    template<typename mask, typename data, size_t N>
    //__attribute__((optimize("unroll-loops")))
    inline auto vsel(const vec<mask, N> &condition, const vec<data, N> &choice1, const vec<data, N> &choice2)
    {
        vec<data, N> result;

        for(int i = 0; i < N; i++)
            result(i) = vsel<mask, data>(condition(i), choice1(i), choice2(i));

        return result;
    }


    template<typename T, typename U, size_t N>
    //__attribute__((optimize("unroll-loops")))
    inline auto clamp_int32(const vec<T, N> &a)
    {
        vec<T, N> result;

        for(int i = 0; i < N; i++)
            result(i) = a(i).trunc();

        return result;
    }

    template<typename T, size_t elems>
    inline std::ostream& operator<<(std::ostream& out, const vec<T, elems> &other)
    {
        auto print_row = [&](auto rowi)
        {
            for(auto coli = 0; coli < elems; coli++)
                out << other(coli) << " ";
        };

        out << "[ ";
        print_row(0);
        out << "]";

        return out;
    }

    template<typename T, size_t rows, size_t cols>
    inline std::ostream& operator<<(std::ostream& out, const mat<T, rows, cols> &other)
    {
        auto print_row = [&](auto rowi)
        {
            for(auto coli = 0; coli < cols; coli++)
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
            for(auto rowi = 0; rowi < rows; rowi++)
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