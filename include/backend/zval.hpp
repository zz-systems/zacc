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

#include "backend/ztype.hpp"

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
        boolean,    ///< last operation is boolean (skip mask generation)
        bitwise     ///< last operation is bitwise. (skip mask generation)
    };

    template<typename Interface, typename enable = void>
    struct zval;

    template<typename Interface>
    struct zval<Interface, std::enable_if_t<is_zval<Interface>::value>>
            : Interface
    {
        USING_ZTYPE(Interface);

        constexpr zval() = default;

        // =============================================================================================================

        constexpr zval(const zval& other) noexcept
            : _value { other._value }
        {}

        constexpr zval(zval&& other) noexcept
            : zval()
        {
            swap(*this, other);
        }

        constexpr zval& operator=(zval other) noexcept
        {
            swap(*this, other);
            return *this;
        }

        // =============================================================================================================


//        template<typename T, typename std::enable_if<std::is_convertible<T, vector_type>::value, void**>::type = nullptr>
//        constexpr zval(const T& other) noexcept
//                : _value { other }
//        {}

        constexpr zval(const vector_type& other) noexcept
                : _value { other }
        {}

//        explicit constexpr zval(const bval_t<Interface>& other) noexcept
//                : _value { other.value() }
//        {}

        // =============================================================================================================

        friend void swap(zval& one, zval& other) // nothrow
        {
            // enable ADL (not necessary in our case, but good practice)
            using std::swap;

            // by swapping the members of two objects,
            // the two objects are effectively swapped
            swap(one._value, other._value);
        }

        // =============================================================================================================

        template <bool Cond = is_vector, typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr vector_type value() const {
            return this->_value;
        }

        template <bool Cond = !is_vector, typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr element_type value() const {
            return _value[0];
        }

        constexpr operator vector_type() const {
            return this->_value;
        }
        
    protected:
        alignas(alignment) vector_type _value;
    };

    template<typename Interface>
    struct zval<Interface, std::enable_if_t<is_bval<Interface>::value>>
            : Interface
    {
        USING_ZTYPE(Interface);

        constexpr zval() noexcept
            : _last_op(last_operation::undefined)
        {}

        // =============================================================================================================

        constexpr zval(const zval& other) noexcept
            : _value (other._value), _last_op { other.last_op() }
        {}

        constexpr zval(const zval& other, last_operation last_op) noexcept
            : _value (other._value), _last_op { last_op }
        {}

        constexpr zval(zval&& other) noexcept
            : zval()
        {
            swap(*this, other);
        }

//        constexpr zval(zval&& other, last_operation last_op) noexcept
//            : zval()
//        {
//            std::swap(_last_op, last_op);
//            swap(*this, other);
//        }

        constexpr zval& operator=(zval other) noexcept
        {
            swap(*this, other);
            return *this;
        }

        // =============================================================================================================

//        template<typename T, typename std::enable_if<is_vector && std::is_convertible<T, vector_type>::value, void**>::type = nullptr>
//        constexpr zval(T&& other, last_operation last_op = last_operation::undefined) noexcept
//            : _value { std::forward<vector_type>(other) }, _last_op { last_op }
//        {}
//
//        template<typename T, typename std::enable_if<is_vector && std::is_convertible<T, bool>::value, void**>::type = nullptr>
//        constexpr zval(T&& other) noexcept
//                : _value {{ std::forward<bool>(other)  }}, _last_op { last_operation::boolean }
//        {}

//        template<typename T, typename std::enable_if<std::is_convertible<T, vector_type>::value, void**>::type = nullptr>
//        constexpr zval(const T& other) noexcept
//                : _value { other }
//        {}

        constexpr zval(const std::conditional_t<is_vector, vector_type, std::array<bool, 1>>& other) noexcept
                : _value { other }
        {}

//        template<typename T, typename std::enable_if<std::is_convertible<T, vector_type>::value, void**>::type = nullptr>
//        constexpr zval(const vector_type& other) noexcept
//                : _value { other }
//        {}

//        constexpr zval(const std::conditional_t<is_vector, vector_type, std::array<bool, 1>>& value) noexcept
//            : _value { value }
//        {}

//        constexpr zval(bool value) noexcept
//                : _value {{ value }}
//        {}

//        constexpr zval(const zval_t<Interface>& other) noexcept
//            : _value { other.value() }
//        {}


        // =============================================================================================================

//        constexpr zval(bool value, last_operation last_op = last_operation::boolean) noexcept
//            : _value {{ value }}, _last_op { last_op }
//        {}
//
//        template<typename T, typename std::enable_if<!is_vector && std::is_convertible<decltype(std::declval<T>().value()), bool>::value, void**>::type = nullptr>
//        constexpr zval(T&& other, last_operation last_op = last_operation::boolean) noexcept
//            : _value {{ std::forward<bool>(other.value()) }}, _last_op { last_op }
//        {}

        // =============================================================================================================

        friend void swap(zval& one, zval& other) // nothrow
        {
            // enable ADL (not necessary in our case, but good practice)
            using std::swap;

            // by swapping the members of two objects,
            // the two objects are effectively swapped
            swap(one._value, other._value);
            swap(one._last_op, other._last_op);
        }

        // =============================================================================================================

        template <bool Cond = is_vector, typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr vector_type value() const {
            return this->_value;
        }

        template <bool Cond = !is_vector, typename std::enable_if<Cond, void**>::type = nullptr>
        constexpr bool value() const {
            return this->_value[0];
        }

        constexpr operator vector_type() const {
            return this->_value;
        }

        //template <bool Cond = !is_vector, typename std::enable_if<Cond, void**>::type = nullptr>
        explicit constexpr operator bool() const {
            return static_cast<const bval_t<Interface>*>(this)->is_set();
        }

        constexpr last_operation last_op() const {
            return _last_op;
        }
    protected:
        alignas(alignment) std::conditional_t<is_vector, vector_type, std::array<bool, 1>> _value;
        last_operation _last_op;
    };
}