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

    struct bval_base {};

    /**
     * last operation
     */
    enum class last_operation
    {
        undefined,  ///< last operation is unknown (e.g initialization or arithmetic)
        comparison, ///< last operation has been a comparison. Assume all-set mask of ones
        logic,      ///< last operation has been a logic operation. Assume all-set mask of ones
        bitwise     ///< last operation has been a comparison. Assume user knows what to do
    };

    /**
     * Base type for boolean vector types
     * @tparam Vector vector type, like __m128i for sse 4x integer vector
     * @tparam MaskVector mask type for boolean operations
     * @tparam Size ector size (1 - scalar, 4, 8, 16, ...)
     * @tparam Alignment memory alignment
     * @tparam Features capabilities
     */
    template<typename Interface>
    struct bval : Interface
    {
        USING_ZTYPE(Interface);

        /**
         * default constructor
         */
        constexpr bval() noexcept
                : _last_op(last_operation::undefined)
        {}

        template<typename T, typename std::enable_if<(size > 1) && std::is_convertible<T, vector_type>::value, void**>::type = nullptr>
        constexpr bval(T value, last_operation last_op = last_operation::undefined) noexcept
            : _value(value), _last_op(last_op)
        {}

        template<typename T, typename std::enable_if<(size == 1) && std::is_convertible<T, bool>::value, void**>::type = nullptr>
        constexpr bval(T value, last_operation last_op = last_operation::undefined) noexcept
                : _value {{ static_cast<bool>(value) }}, _last_op(last_op)
        {}

        template<typename T, typename std::enable_if<(size == 1) && is_zval<T>::value, void**>::type = nullptr>
        constexpr bval(T value, last_operation last_op = last_operation::undefined) noexcept
                : bval(value.value(), last_op)
        {}

        /**
         * copy constructor
         * @param other
         */
        constexpr bval(const bval& other) noexcept
                : _value (other._value), _last_op(other.last_op())
        {}

        /**
         * 'fake' copy constructor with last operation
         * @param other
         * @param last_op last operation
        */
        constexpr bval(const bval& other, last_operation last_op) noexcept
                : _value (other._value), _last_op(last_op)
        {}

        /**
         * move constructor
         * @param other
         */
        constexpr bval(bval&& other) noexcept
                : _value(std::move(other._value)), _last_op(other.last_op())
        {}

        /**
         * assignment operator
         * @tparam T any type convertable to MaskVector
         * @param other
         * @return self
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, vector_type>::value>>
        constexpr bval& operator=(const T& other) noexcept
        {
            _value = other._value;
            _last_op = other._last_op;

            return *this;
        };

        /**
         * moving assignment operator
         * @tparam T any type convertable to MaskVector
         * @param other
         * @return self
         */
        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, vector_type>::value>>
        constexpr bval& operator=(T&& other) noexcept
        {
            _value = std::move(other._value);
            _last_op = std::move(other._last_op);

            return *this;
        };

        /**
         * assignment operator
         * @param other
         * @return self
         */
        constexpr bval& operator=(const bval& other) noexcept
        {
            _value = other._value;
            _last_op = other._last_op;

            return *this;
        };

        /**
         * moving assignment operator
         * @param other
         * @return self
         */
        constexpr bval& operator=(bval&& other) noexcept
        {
            _value = std::move(other._value);
            _last_op = std::move(other._last_op);

            return *this;
        };

        /**
         * swaps values
         * @param other
         */
        void swap(bval& other) noexcept
        {
            std::swap(_value, other._value);
            std::swap(_last_op, other._last_op);
        }

        constexpr operator vector_type() const {
            return value();
        }

        /**
        * underlying vector
        * @return raw value
        */
        template <bool Cond = (size > 1), typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr vector_type value() const {
            return _value;
        }

        template <bool Cond = (size == 1), typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr bool value() const {
            return _value[0];
        }

        /**
        * last operation
        * @return last operation
        */
        constexpr last_operation last_op() const {
            return _last_op;
        }

    private:
        alignas(alignment) std::conditional_t<is_vector, vector_type, std::array<bool, 1>> _value;
        last_operation _last_op;
    };


    /**
     * construct a bval from arguments
     * @tparam T any zval
     * @param value
     * @param last_op
     * @return bval
     */
    template<typename T>
    constexpr std::enable_if_t<is_zval<T>::value, typename ztraits<T>::bval_t> make_bval(T value, last_operation last_op = last_operation::undefined)
    {
        return typename ztraits<T>::bval_t {value, last_op};
    }


    /**
     * construct a bval from arguments
     * @tparam T any type not equal to zval
     * @param value
     * @param last_op
     * @return bval
     */
    template<typename T>
    constexpr std::enable_if_t<!is_zval<T>::value, typename ztraits<T>::bval_t> make_bval(T value)
    {
        return static_cast<typename ztraits<T>::bval_t>(value);
    }

    /**
     * construct a bval from arguments
     * @tparam T any zval
     * @param value
     * @param last_op
     * @return bval
     */
    template<typename T>
    constexpr std::enable_if_t<is_zval<T>::value, typename T::bval_t> make_bval(T value, last_operation last_op = last_operation::undefined)
    {
        return typename ztraits<T>::bval_t {value, last_op};
    }


    /**
     * construct a bval from arguments
     * @tparam T any type not equal to zval
     * @param value
     * @param last_op
     * @return bval
     */
    template<typename T>
    constexpr std::enable_if_t<!is_zval<T>::value, typename T::bval_t> make_bval(T value)
    {
        return static_cast<typename T::bval_t>(value);
    }
}