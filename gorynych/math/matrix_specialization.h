//
// Created by szuyev on 17.06.16.
//

#pragma once

namespace zzsystems { namespace gorynych {

    /// special vec 3 impl
    template<typename T>
    struct mat<T, 3, 1>
    {
        union
        {
            array<T, 3> data;

            struct
            {
                T x, y, z;
            };
        };

        mat() = default;
        //vec3(const T* rhs) { v = rhs; };

        mat(const mat &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { };

        template<typename U = T>
        mat(const mat<U, 3, 1> &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { };

        mat(const T &all) : x(all), y(all), z(all) { };

        mat(const T &x, const T &y, const T &z) : x(x), y(y), z(z) { };

        static constexpr size_t get_rows()     { return 3; }
        static constexpr size_t get_cols()     { return 1; }
        static constexpr size_t get_length()   { return 3; }

        T &operator()(int row, int col)
        {
            return data[row];
        }

        T &operator()(int i)
        {
            return data[i];
        }

        const T &operator()(int row, int col) const
        {
            return data[row];
        }

        const T &operator()(int i) const
        {
            return data[i];
        }

        T magnitude() const
        {
            return vsqrt(sqr_magnitude());
        }

        T sqr_magnitude() const
        {
            return dot(*this);
        }

        T dot(const mat &other) const
        {
            return x * other.x + y * other.y + z * other.z;
        }

        inline const T &get_row(int row) const
        {
            return data[row];
        };

        explicit operator bool() const
        {
            return is_set(x) && is_set(y) && is_set(z);
        }
    };

    template<typename T, typename U>
    inline auto operator <(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x < b.x, a.y < b.y, a.z < b.z);
    }

    template<typename T, typename U>
    inline auto	operator <=(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x <= b.x, a.y <= b.y, a.z <= b.z);
    }

    template<typename T, typename U>
    inline auto	operator >(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x > b.x, a.y > b.y, a.z > b.z);
    }

    template<typename T, typename U>
    inline auto	operator >=(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x >= b.x, a.y >= b.y, a.z >= b.z);
    }

    template<typename T, typename U>
    inline auto	operator ==(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x == b.x, a.y == b.y, a.z == b.z);
    }

    template<typename T, typename U>
    inline auto	operator !=(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x != b.x, a.y != b.y, a.z != b.z);
    }
    /// @brief add
    /// @relates mat
    template<typename T, typename U>
    auto operator+(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
    };

    /// @brief sub
    /// @relates mat
    template<typename T, typename U, size_t rows, size_t cols>
    auto operator-(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
    };

    /// @brief add scalar
    /// @relates mat
    template<typename T>
    auto operator+(const vec3<T>& a, const T& b)
    {
        return vec3<T>(a.x + b, a.y + b, a.z + b);
    };

    /// @brief sub scalar
    /// @relates mat
    template<typename T>
    auto operator-(const vec3<T>& a, const T& b)
    {
        return vec3<T>(a.x - b, a.y - b, a.z - b);
    };

    /// @brief mul scalar
    /// @relates mat
    template<typename T>
    auto operator*(const vec3<T>& a, const T& b)
    {
        return vec3<T>(a.x * b, a.y * b, a.z * b);
    };

    /// @brief div scalar
    /// @relates mat
    template<typename T, size_t rows, size_t cols>
    auto operator/(const vec3<T>& a, const T& b)
    {
        return vec3<T>(a.x / b, a.y / b, a.z / b);
    };



    /// @brief scale (mul)
    /// @relates mat
    template<typename T, typename U>
    auto operator*(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x * b.x, a.y * b.x, a.z * b.z);
    };


    /// @brief scale (div)
    /// @relates mat
    template<typename T, typename U>
    auto operator/(const vec3<T>& a, const vec3<U>& b)
    {
        return vec3<T>(a.x / b.x, a.y / b.x, a.z / b.z);
    };

    /// special matrix 2x3 impl
    template<typename T>
    struct mat<T, 2, 3>
    {
        union
        {
            array<vec3<T>, 2>   data;
            array<T, 6>         flat_data;
            struct { vec3<T> row0, row1; };
        };

        mat() = default;
        //vec3(const T* rhs) { v = rhs; };

        mat(const mat &rhs) : row0(rhs.row0), row1(rhs.row1) { };

        template<typename U = T>
        mat(const mat<U, 2, 3> &rhs) : row0(rhs.row0), row1(rhs.row1) { };

        mat(const T &all) : row0(all), row1(all) { };

        mat(const vec3<T> &row0, const vec3<T> &row1) : row0(row0), row1(row1) { };

        static constexpr size_t get_rows()     { return 2; }
        static constexpr size_t get_cols()     { return 3; }
        static constexpr size_t get_length()   { return 6; }

        T &operator()(int row, int col)
        {
            return data[row](col);
        }

        T &operator()(int i)
        {
            return flat_data[i];
        }

        const T &operator()(int row, int col) const
        {
            return data[row](col);
        }

        const T &operator()(int i) const
        {
            return flat_data[i];
        }

        T magnitude() const
        {
            return vsqrt(sqr_magnitude());
        }

        T sqr_magnitude() const
        {
            return dot(*this);
        }

        T dot(const mat &other) const
        {
            return data[0].dot(other.get_row(0)) + data[1].dot(other.get_row(1));
        }

        inline const vec3<T> &get_row(int row) const
        {
            return data[row];
        };

        explicit operator bool() const
        {
            return static_cast<bool>(data[0]) && static_cast<bool>(data[1]);
        }
    };

    /// special matrix 3x3 impl
    template<typename T>
    struct mat<T, 3, 3>
    {
        union
        {
            array<vec3<T>, 2>   data;
            array<T, 9>         flat_data;
            struct { vec3<T> row0, row1, row2; };
        };

        mat() = default;
        //vec3(const T* rhs) { v = rhs; };

        mat(const mat &rhs) : row0(rhs.row0), row1(rhs.row1), row2(rhs.row2) { };

        template<typename U = T>
        mat(const mat<U, 3, 3> &rhs) : row0(rhs.row0), row1(rhs.row1), row2(rhs.row2) { };

        mat(const T &all) : row0(all), row1(all), row2(all) { };

        mat(const vec3<T> &row0, const vec3<T> &row1, const vec3<T> &row2) : row0(row0), row1(row1), row2(row2) { };

        static constexpr size_t get_rows()     { return 3; }
        static constexpr size_t get_cols()     { return 3; }
        static constexpr size_t get_length()   { return 9; }

        T &operator()(int row, int col)
        {
            return data[row](col);
        }

        T &operator()(int i)
        {
            return flat_data[i];
        }

        const T &operator()(int row, int col) const
        {
            return data[row](col);
        }

        const T &operator()(int i) const
        {
            return data[i];
        }

        T magnitude() const
        {
            return vsqrt(sqr_magnitude());
        }

        T sqr_magnitude() const
        {
            return dot(*this);
        }

        T dot(const mat &other) const
        {
            return data[0].dot(other.get_row(0)) + data[1].dot(other.get_row(1)) + data[2].dot(other.get_row(2));
        }

        inline const vec3<T> &get_row(int row) const
        {
            return data[row];
        };

        explicit operator bool() const
        {
            return static_cast<bool>(data[0]) && static_cast<bool>(data[1]) && static_cast<bool>(data[2]);
        }
    };

    template<typename T>
    inline auto operator *(const mat3x3<T>& a, const vec3<T>& b)
    {
        return vec3<T>(a.row0.dot(b), a.row1.dot(b), a.row2.dot(b));
    }
}}