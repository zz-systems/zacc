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
    template<typename Vector, typename MaskVector, size_t Size, size_t Alignment, uint64_t Features>
    struct bval : zval_base<Vector, MaskVector, bool, bval_tag, Size, Alignment, Features>
    {
        /**
         * default constructor
         */
        constexpr bval() noexcept
                : _last_op(last_operation::undefined)
        {}

        /**
         * copy constructor
         * @tparam T any type convertable to Vector
         * @param other
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr bval(const T& other) noexcept
                : _value (other), _last_op(other.last_op())
        {}

        /**
         * 'fake' copy constructor with last operation
         * @tparam T any type convertable to Vector
         * @param other
         * @param last_op last operation
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr bval(const T& other, last_operation last_op) noexcept
                : _value (other), _last_op(last_op)
        {}

        /**
         * move constructor
         * @tparam T any type convertable to Vector
         * @param other
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr bval(T&& other) noexcept
                : _value(std::forward<T>(other)),
                  _last_op(last_operation::undefined)
        {}

        constexpr bval(const bval& other) noexcept
                : _value (other._value), _last_op(other.last_op())
        {}

        constexpr bval(const bval& other, last_operation last_op) noexcept
                : _value (other._value), _last_op(last_op)
        {}

        constexpr bval(bval&& other) noexcept
                : _value(std::move(other._value)), _last_op(other.last_op())
        {}

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr bval& operator=(const T& other) noexcept
        {
            _value = other.value();
            _last_op = other.last_op();

            return *this;
        };

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Vector>::value>>
        constexpr bval& operator=(T&& other) noexcept
        {
            _value = std::move(other.value());
            _last_op = std::move(other.last_op());

            return *this;
        };


        constexpr bval& operator=(const bval& other) noexcept
        {
            _value = other.value();
            _last_op = other.last_op();

            return *this;
        };


        constexpr bval& operator=(bval&& other) noexcept
        {
            _value = std::move(other.value());
            _last_op = std::move(other.last_op());

            return *this;
        };

        void swap(bval& other) noexcept
        {
            std::swap(_value, other._value);
            std::swap(_last_op, other._last_op);
        }

        /**
         * @brief
         * @return
         */
        template <typename size = std::integral_constant<size_t, Size>, typename enable = typename std::enable_if<(size::value > 1), MaskVector>::type>
        constexpr operator MaskVector() const {
            return value();
        }

        constexpr const MaskVector value() const {
            return _value;
        }

        constexpr last_operation last_op() const {
            return _last_op;
        }

    private:
        alignas(Alignment) MaskVector _value;
        last_operation _last_op;
    };


    template<typename T>
    constexpr std::enable_if_t<is_zval<T>::value, typename zval_traits<T>::bval_t> make_bval(T value, last_operation last_op = last_operation::undefined)
    {
        return typename zval_traits<T>::bval_t {value, last_op};
    }


    template<typename T>
    constexpr std::enable_if_t<!is_zval<T>::value, typename zval_traits<T>::bval_t> make_bval(T value, last_operation)
    {
        return static_cast<typename zval_traits<T>::bval_t>(value);
    }

    template<typename _ZVal>
    constexpr auto make_boolean(const _ZVal& value)
    {
        return typename _ZVal::bval_t(value);
    }
}