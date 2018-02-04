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
     * @tparam _vector_t vector type, like __m128i for sse 4x integer vector
     * @tparam _mask_t mask type for boolean operations
     * @tparam _scalar_t scalar type, like int for sse 4x integer vector
     * @tparam _dim vector size (1 - scalar, 4, 8, 16, ...)
     * @tparam _alignment memory alignment
     * @tparam Arch capabilities
     */
    template<typename Vector, typename MaskVector, typename Element, typename Tag, size_t Size, size_t Alignment, uint64_t Features = 0xFFFF'FFFF'FFFF'FFFF>
    struct zval : zval_base<Vector, MaskVector, Element, Tag, Size, Alignment, Features>
    {
        /// default constructor
        constexpr zval() = default;

        /// copy constructor
        /// @requres T shall be convertable to Vector
        /// @tparam T any type
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr zval(const T& other)
                : _value (other)
        {}

        /// move constructor
        /// @requres T shall be convertable to Vector
        /// @tparam T any type
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr zval(T&& value)
                : _value(std::move(value))
        {}

        /// copy constructor
        constexpr zval(const zval& other)
                : _value (other._value)
        {}

        /// move constructor
        constexpr zval(zval&& other) noexcept
                : _value(std::move(other._value))
        {}

        /// assignment operator
        /// @requres T shall be convertable to Vector
        /// @tparam T any type
        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr zval& operator=(const T& other)
        {
            _value = other;
            return *this;
        }

        /// moving assignment operator
        /// @requres T shall be convertable to Vector
        /// @tparam T any type
        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr zval& operator=(T&& other) noexcept
        {
            _value = std::move(other);
            return *this;
        }

        /// assignment operator
        constexpr zval& operator=(const zval& other)
        {
            _value = other._value;
            return *this;
        }

        /// moving assignment operator
        constexpr zval& operator=(zval&& other) noexcept
        {
            _value = std::move(other._value);
            return *this;
        }

        void swap(zval& other) noexcept
        {
            std::swap(_value, other._value);
        }

        template <typename size = std::integral_constant<size_t, Size>, typename enable = typename std::enable_if<(size::value > 1), Vector>::type>
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

    template<typename... Args>
    void swap(zval<Args...>& one, zval<Args...>& other)
    {
        one.swap(other);
    }

    enum class last_operation
    {
        undefined,
        comparison,
        logic,
        bitwise
    };

    template<typename base_t>
    struct composable {
        template<typename terminator>
        struct type :
                public base_t,
                public terminator
        {
            using zval_t = typename base_t::zval_t;
            using bval_t = typename base_t::bval_t;

            FORWARD(type);
        };
    };

    template<typename T>
    constexpr size_t dim() { return T::dim; }

}