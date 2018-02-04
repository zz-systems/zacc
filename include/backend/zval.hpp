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
#include <array>

#include "system/capabilities.hpp"

#include "util/type/type_traits.hpp"
#include "util/type/type_casts.hpp"

#include "util/macros.hpp"
#include "util/collections.hpp"


namespace zacc {

    /// @cond
    template<typename Vector, typename MaskVector, size_t Size, size_t Alignment, uint64_t Features = 0xFFFF'FFFF'FFFF'FFFF>
    struct bval;
    /// @endcond

    /**
     * @brief base type for all zacc computation types
     * @tparam Vector vector type, like __m128i for sse 4x integer vector
     * @tparam MaskVector mask type for boolean operations
     * @tparam Element scalar type, like int for sse 4x integer vector
     * @tparam Tag zval type tag
     * @tparam Size vector size (1 - scalar, 4, 8, 16, ...)
     * @tparam Alignment memory alignment
     * @tparam Features capabilities
     */
    template<typename Vector, typename MaskVector, typename Element, typename Tag, size_t Size, size_t Alignment, uint64_t Features = 0xFFFF'FFFF'FFFF'FFFF>
    struct zval : zval_base<Vector, MaskVector, Element, Tag, Size, Alignment, Features>
    {
        /**
         * default constructor
         */
        constexpr zval() noexcept = default;

        /**
         * copy constructor
         * @tparam T any type convertable to Vector
         * @param other
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr zval(const T& other) noexcept
                : _value (other)
        {}

        /**
         * move constructor
         * @tparam T any type convertable to Vector
         * @param other
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr zval(T&& other) noexcept
                : _value(std::forward<T>(other))
        {}

        /**
         * copy constructor
         * @param other
         */
        constexpr zval(const zval& other) noexcept
                : _value (other._value)
        {}

        /**
         * move constructor
         * @param other
         */
        constexpr zval(zval&& other) noexcept
                : _value(std::move(other._value))
        {}

         /**
          * assignment operator
          * @tparam T any type convertable to Vector
          * @param other
          * @returns self
          */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr zval& operator=(const T& other) noexcept
        {
            _value = other;
            return *this;
        }

        /**
         * moving assignment operator
         * @tparam T any type convertable to Vector
         * @param other
         * @returns self
         */
        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr zval& operator=(T&& other) noexcept
        {
            swap(other);
            return *this;
        }

        /**
         * assignment operator
         * @param other
         * @returns self
         */
        constexpr zval& operator=(const zval& other) noexcept
        {
            _value = other._value;
            return *this;
        }

        /**
         * moving assignment operator
         * @param other
         * @returns self
         */
        constexpr zval& operator=(zval&& other) noexcept
        {
            swap(other);
            return *this;
        }

        /**
         * swaps values
         * @param other
         */
        void swap(zval& other) noexcept
        {
            std::swap(_value, other._value);
        }

        /**
         * implicit cast operator to wrapped raw type (Vector)
         * @remark valid only for vectors, not scalars (size has to be > 1, otherwise default C++ operators will apply for wrapped scalars)
         * @tparam size current vector size as type
         * @return raw value
         */
        template <typename size = std::integral_constant<size_t, Size>, typename = std::enable_if_t<(size::value > 1), Vector>>
        constexpr operator Vector() const {
            return value();
        }

        /**
         * @brief cast to underlying vector type
         * @return raw value
         */
        constexpr Vector value() const {
            return _value;
        }

    private:
        alignas(Alignment) Vector _value;
    };

    /**
     * swaps contents of zval instances
     * @tparam Args zval parametrization
     * @param one
     * @param other
     */
    template<typename... Args>
    void swap(zval<Args...>& one, zval<Args...>& other)
    {
        one.swap(other);
    }
}