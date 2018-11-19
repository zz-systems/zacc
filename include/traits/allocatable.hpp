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


#include <sstream>
#include "util/memory.hpp"

namespace zacc {

    template<template<class...> class T, typename Arch, typename Alloc = aligned_allocator<T<Arch>, Arch::alignment>>
    struct allocatable
    {
        static Alloc& alloc()
        {
            static Alloc _alloc;

            return _alloc;
        }

        static void *operator new(size_t nbytes)
        {
            auto ptr = alloc().allocate(nbytes);

            if(ptr != nullptr)
                return ::new(ptr) T<Arch>();

            throw std::bad_alloc();
        }

        static void operator delete(void *p)
        {
            if(p != nullptr)
            {
                alloc().destroy(static_cast<T<Arch>*>(p));
                alloc().deallocate(static_cast<T<Arch>*>(p), 0);
            }
        }
    };
}