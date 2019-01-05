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

#include "util/type/ztraits.hpp"
#include "util/type/type_traits.hpp"
#include "util/type/type_casts.hpp"

#include "util/macros.hpp"
#include "util/collections.hpp"


namespace zacc {

    template<typename Interface>
    struct zval : Interface
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

        constexpr zval(const storage_t<Interface>& other) noexcept
            : _value { other }
        {}

        // =============================================================================================================

        friend void swap(zval& one, zval& other) // nothrow
        {
            std::swap(one._value, other._value);
        }

        // =============================================================================================================

        constexpr const storage_t<Interface>& value() const& {
            return this->_value;
        }

        constexpr storage_t<Interface>& value() &{
            return this->_value;
        }

        constexpr storage_t<Interface>&& value() &&{
            return this->_value;
        }

        // =============================================================================================================

        constexpr operator vector_type() const {
            return this->_value;
        }

        explicit constexpr operator bool() const {
            return static_cast<const bval_t<Interface>*>(this)->is_set();
        }
        
    protected:
        alignas(alignment) storage_t<Interface> _value;
    };
}