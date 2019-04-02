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

#include <zacc/expressions/expression.hpp>
#include <zacc/expressions/repr.hpp>
#include <vector>

namespace zacc { namespace expressions {

    template<typename T>
    struct scope : T
    {
        T _previous;

//        constexpr scope()
//            : _previous()
//        {
//            std::swap(_previous, T::current());
//        }
//
//        ~scope()
//        {
//            std::swap(_previous, T::current());
//        }

        constexpr scope()
            : _previous(T::current())
        {
            T::current() = T();
        }

        ~scope()
        {
            T::current() = _previous;
        }

        friend std::ostream& operator<<(std::ostream& os, const scope<T>&)
        {
            os << T::current();

            return os;
        }
    };


    // =================================================================================================================
}}