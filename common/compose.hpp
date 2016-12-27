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

/**
 * @brief https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Hierarchy_Generation
 */

#pragma once

#include <utility>

namespace zacc {
    template<template<class> class ... policies>
    struct compose;

    template<template<class> class head,
            template<class> class ... tail>
    struct compose<head, tail...> : head<compose<tail...>> {
        template<typename... Args>
        compose(Args &&...args) : head<compose<tail...>>(std::forward<Args>(args)...) {}
    };

    template<>
    struct compose<> {
    };
/*

    template<template<class> class terminator, template<class> class ... policies>
    struct compose_incomplete;

    template<template<class> class terminator, template<class> class head, template<class> class ... tail>
    struct compose_incomplete<terminator, head, tail...> : head<compose_incomplete<terminator, tail...>>
    {
        template<typename... Args>
        compose_incomplete(Args &&...args) : head<compose_incomplete<terminator, tail...>>(std::forward<Args>(args)...)
        {}
    };

    template<>
    template<template<class> class terminator>
    struct compose_incomplete <terminator> :
            terminator {};*/

#define FORWARD2(name, base) \
    template<typename ...Args> \
    name(Args... args) : base(std::forward<Args>(args)...) {}

#define FORWARD(name) FORWARD2(name, base_t)

#define FEATURE2(provides, base_t) \
    static const long long feature =  base_t::feature | static_cast<long long>(provides)

#define FEATURE(provides) FEATURE2(provides, base_t)
//
//#define REQUIRE2(requirement, base_t) \
//
//#define __REQUIRE_OR(requirement, ...) (static_cast<long long>(requirement) | __REQUIRE_OR(__VA_ARGS__))
//
//#define REQUIRE(requirement, ...) \
//    static_assert((base_t::feature & __REQUIRE_OR(requirement, __VA_ARGS__)) != 0, "Requirement not met: feature '" #requirement "' required.")


#define REQUIRE(requirement, ...) \
    static_assert((base_t::feature & static_cast<long long>(requirement)) != 0, "Requirement not met: feature '" #requirement "' required.")

}