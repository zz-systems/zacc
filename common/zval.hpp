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


namespace zacc {

    struct zval_base {
    };

    // TODO: capability
    template<typename _type, typename _shim_type = _type, size_t _dim = 1, size_t alignment = 16, int _capability = 0>
    class zval : zval_base {
    public:
        static const unsigned dim = _dim;
        static const int capability = _capability;

        static const bool is_vector = dim > 1;

        using type = _type;
        using shim_type = _shim_type;

        using extracted_type = alignas(alignment) std::array<shim_type, dim>;

        template<typename T>
        zval(T value) : _value(value) {}

        _type get_value() const { return _value; }

    protected:
        _type _value;
    };

    template<typename T>
    struct composable {
        template<typename terminator>
        struct type :
                public /*std::conditional_t<
                        std::is_void<_parent>::value,*/
                T,
                /*_parent>,*/
                public terminator {

            template<typename ...Args>
            type(Args... args) : T(std::forward<Args>(args)...) {}
        };
    };

}