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

#define FORWARD2(name, base) \
    /** \
     * @brief forwarding constructor \
     */ \
    template<typename ...Args> \
    name(Args... args) : base(std::forward<Args>(args)...) {}

#define FORWARD(name) FORWARD2(name, base_t)

#define TRAIT2(provides, base_t) \
    static const long long traits =  base_t::traits | static_cast<long long>(provides)

#define TRAIT(provides) \
    TRAIT2(provides, base_t)

#define REQUIRE(requirement) \
    static_assert((base_t::traits & static_cast<long long>(requirement)) != 0, "Requirement not met: feature '" #requirement "' required.")

#define BASE() \
    base_t* base() { return static_cast<base_t*>(this); }


#define CONVERSION2(op, composed_t) \
    template<typename other_t> \
    friend composed_t operator op(const composed_t one, const enable_if_not_same<other_t, composed_t> other) { \
        return one op static_cast<composed_t>(other); \
    }; \
    template<typename other_t> \
    friend composed_t operator op (const enable_if_not_same<other_t, composed_t> one, const composed_t other) { \
        return static_cast<composed_t>(one) op other; \
    }

#define CONVERSION(op) CONVERSION2(op, composed_t)