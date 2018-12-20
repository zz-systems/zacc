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

/**
 * @brief https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Hierarchy_Generation
 */

#pragma once

#include <utility>
#include "util/macros.hpp"

namespace zacc {

    template<template<class> class Head, template<class> class... Tail>
    struct compose
    {
        using type = Head<typename compose<Tail...>::type>;
    };

    template<template<class> class Tail>
    struct compose<Tail>
    {
        struct terminator
        {};

        using type = Tail<terminator>;
    };

    template<template<class> class Head, template<class> class... Tail>
    using compose_t = typename compose<Head, Tail...>::type;

    template<typename Base>
    struct composable
    {
        template<typename Terminator>
        struct type :
                public Base,
                public Terminator
        {

            FORWARD(type);
        };
    };
}