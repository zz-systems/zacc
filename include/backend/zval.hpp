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

    struct zval_base {};

    /// @cond
    template<typename Interface>
    struct bval;
    /// @endcond

    /**
     * @struct zval
     * @brief base type for all zacc computation types
     * @tparam Vector vector type, like __m128i for sse 4x integer vector
     * @tparam MaskVector mask type for boolean operations
     * @tparam Element scalar type, like int for sse 4x integer vector
     * @tparam Tag zval type tag
     * @tparam Size vector size (1 - scalar, 4, 8, 16, ...)
     * @tparam Alignment memory alignment
     * @tparam Features capabilities
     */
    template<typename Interface>
    struct zval : Interface
    {
        USING_ZTYPE(Interface);

        /**
         * default constructor
         */
        constexpr zval() noexcept = default;


        template<typename T, typename std::enable_if<(size > 1) && std::is_convertible<T, vector_type>::value, void**>::type = nullptr>
        constexpr zval(T value) noexcept
            : _value(value)
        {}

        template<typename T, typename std::enable_if<(size == 1) && std::is_convertible<T, element_type>::value, void**>::type = nullptr>
        constexpr zval(T value) noexcept
            : _value {{ static_cast<element_type>(value) }}
        {}

        template<typename T, typename std::enable_if<(size == 1) && is_bval<T>::value, void**>::type = nullptr>
        constexpr zval(T value) noexcept
            : zval(value.value())
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
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, vector_type>::value>>
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
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, vector_type>::value>>
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
         * @return raw value
         */
        //template <bool Cond = (Size > 1), typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr operator vector_type() const {
            return value();
        }

//        template<typename T = zval>
//        constexpr operator std::enable_if_t<T::is_vector, Vector>() const {
//            return value();
//        }

        /**
         * @brief underlying vector
         * @return raw value
         */
        template <bool Cond = (size > 1), typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr vector_type value() const {
            return _value;
        }

        template <bool Cond = (size == 1), typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr element_type value() const {
            return _value[0];
        }

    private:
        alignas(alignment) vector_type _value;
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