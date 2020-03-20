//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include <zacc/compute/compute.hpp>

namespace zacc { namespace compute {

    template<typename>
    struct variable;

    template<typename, size_t>
    struct batch;

    template<typename>
    struct literal;

    template<typename T>
    struct type;

    template<typename T>
    struct initializer;

    class __renderer;

    template<typename Expression>
    class renderer;


    template<typename T, size_t Size>
    class renderer<type<batch<T, Size>>> : public __renderer
    {
        using __renderer::__renderer;
    public:
        void visit(type<batch<T, Size>>)
        {
            _program << "batch<";
            next(type<literal<T>>{});
            _program << ", " << Size << ">";
        }
    };

    template<typename T, size_t Size>
    class renderer<initializer<batch<T, Size>>> : public __renderer
    {
        using __renderer::__renderer;
    public:
        void visit(initializer<batch<T, Size>> const& initializer)
        {
            _program << "{ ";
            for(auto i : initializer.data)
            {
                _program << i << " ";
            }
            _program << "}";
        }
    };

    template<typename T, size_t Size>
    class renderer<batch<T, Size>> : public __renderer
    {
        using __renderer::__renderer;
    public:
        void visit(batch<T, Size> const& value)
        {
            _program << "b_" << _symbols[value.id()];
        }
    };
}}