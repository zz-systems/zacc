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
#include <array>

#include "system/capabilities.hpp"

#include "util/type/type_traits.hpp"
#include "util/type/type_casts.hpp"

#include "util/macros.hpp"
#include "util/collections.hpp"


namespace zacc {


    template<typename _Vector, typename _MaskVector, size_t _Size, size_t _Alignment, uint64_t _Features = 0xFFFF'FFFF'FFFF'FFFF>
    struct bval;



    /**
     * @brief base type for all zacc computation types
     * @tparam _vector_t vector type, like __m128i for sse 4x integer vector
     * @tparam _mask_t mask type for boolean operations
     * @tparam _scalar_t scalar type, like int for sse 4x integer vector
     * @tparam _dim vector size (1 - scalar, 4, 8, 16, ...)
     * @tparam _alignment memory alignment
     * @tparam _capability capabilities
     */
    template<typename _Vector, typename _MaskVector, typename _Element, typename _Tag, size_t _Size, size_t _Alignment, uint64_t _Features = 0xFFFF'FFFF'FFFF'FFFF>
    struct zval : zval_base<_Vector, _MaskVector, _Element, _Tag, _Size, _Alignment, _Features>
    {
        constexpr zval() = default;

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr zval(const T& other)
                : _value (other)
        {}

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr zval(T&& value)
                : _value(std::forward<T>(value))
        {}

        constexpr zval(const zval& other)
                : _value (other._value)
        {}

        constexpr zval(zval&& other) noexcept
                : _value(std::move(other._value))
        {}

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr zval& operator=(const T& other)
        {
            _value = other;
            return *this;
        }

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr zval& operator=(T&& other) noexcept
        {
            _value = std::move(other);
            return *this;
        }

        constexpr zval& operator=(const zval& other)
        {
            _value = other._value;
            return *this;
        }

        constexpr zval& operator=(zval&& other) noexcept
        {
            _value = std::move(other._value);
            return *this;
        }

        void swap(zval& other) noexcept
        {
            std::swap(_value, other._value);
        }

        template <typename size = std::integral_constant<size_t, _Size>, typename enable = typename std::enable_if<(size::value > 1), _Vector>::type>
        constexpr operator _Vector() const {
            return value();
        }

        /**
         * @brief cast to underlying vector type
         * @return raw value
         */
        constexpr _Vector value() const {
            return _value;
        }

    private:
        alignas(_Alignment) _Vector _value;
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

    /// TODO: separate file, impl traits.
    template<typename _Vector, typename _MaskVector, size_t _Size, size_t _Alignment, uint64_t _Features>
    struct bval : zval_base<_Vector, _MaskVector, bool, bval_tag, _Size, _Alignment, _Features>
    {
        constexpr bval() : _last_op(last_operation::undefined)
        {
        }

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr bval(const T& other)
                : _value (other), _last_op(other.last_op())
        {
        }

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr bval(const T& other, last_operation last_op)
                : _value (other), _last_op(last_op)
        {
        }

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr bval(T&& other)
                : _value(std::move(other)), _last_op(last_operation::undefined)
        {
        }

        constexpr bval(const bval& other)
                : _value (other._value), _last_op(other.last_op())
        {
        }

        constexpr bval(const bval& other, last_operation last_op)
                : _value (other._value), _last_op(last_op)
        {
        }

        constexpr bval(bval&& other) noexcept
                : _value(std::move(other._value)), _last_op(other.last_op())
        {
        }

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
        constexpr bval& operator=(const T& other) noexcept
        {
            _value = other.value();
            _last_op = other.last_op();

            return *this;
        };

        template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, _Vector>::value>>
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
        template <typename size = std::integral_constant<size_t, _Size>, typename enable = typename std::enable_if<(size::value > 1), _MaskVector>::type>
        constexpr operator _MaskVector() const {
            return value();
        }

        constexpr const _MaskVector value() const {
            return _value;
        }

        constexpr last_operation last_op() const {
            return _last_op;
        }

    private:
        alignas(_Alignment) _MaskVector _value;
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