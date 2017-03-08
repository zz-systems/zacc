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
#include "type_traits.hpp"
#include "common.hpp"

#include "system/capabilities.hpp"
#include "util/type_casts.hpp"

namespace zacc {

    struct zval_base {
    };

    template<typename zval_t>
    struct bval;

    template<typename _vector_t, typename _scalar_t = _vector_t, size_t _dim = 1, size_t _alignment = 16, uint64_t _capability = 0xFFFF'FFFF'FFFF'FFFF>
    class zval : zval_base {
    public:
        static const unsigned dim = _dim;
        static const uint64_t capability = _capability;

        static const bool is_vector = dim > 1;
		static const int alignment = _alignment;

        using vector_t = _vector_t;
        using scalar_t = _scalar_t;
        using extracted_t = std::array<scalar_t, dim>;

        // TODO
        using mask_t = bool;

        using dispatcher = capability::dispatcher<capability>;

        zval() {}

        template<typename T, typename enable = std::enable_if_t<!std::is_base_of<zval, T>::value, T>>
        zval(T value) : _value(value) {}

        template<typename T, typename enable = std::enable_if_t<std::is_base_of<zval, T>::value, T>>
        zval(const T& value) : _value(value.get_value()) {}

        zval(const bval<zval>& value) : _value(value.get_value()) {}

        const operator vector_t() const
        {
            return _value;
        }

        const vector_t &get_value() const { return _value; }

        static const long traits = 0;
    protected:
        vector_t _value;
    };

    template<typename zval_t>
    struct bval {
    public:
        static const unsigned dim = zval_t::dim;
        static const int capability = zval_t::capability;

        static const bool is_vector = zval_t::is_vector;
        static const int alignment = zval_t::alignment;

        using vector_t = typename zval_t::vector_t;
        using scalar_t = bool;

        using extracted_t = typename std::array<scalar_t, dim>;
        using iterator    = typename extracted_t::iterator;

        /**
         * @brief Converting constructor
         * @see C++11 4.12/1: A zero value, null pointer value,
         * or null member pointer value is converted to false; any other value is converted to true.
         * @param value
         */
        bval(const zval_t& value) :
                _value(value.get_value()),
                _extracted(array_cast<bool>((value).data()))
        {}

        vector_t get_value() const { return _value; }

        const extracted_t data() const {
            return _extracted;
        }

        extracted_t data() {
            return _extracted;
        }

        iterator begin() { return _extracted.begin(); }

        iterator end() { return _extracted.end(); }
    protected:
        vector_t _value;
        extracted_t _extracted;
    };


    template<typename base_t>
    struct composable {
        template<typename terminator>
        struct type :
                public base_t,
                /*_parent>,*/
                public terminator {

            FORWARD(type);
        };
    };
}