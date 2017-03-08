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

#include "platform.hpp"
#include "capabilities.hpp"
#include ZACC_MAJOR_BRANCH_INC

namespace zacc {

    struct dispatcher
    {
        static const constexpr uint64_t capability = capability::fill_up_to(capabilities::ZACC_MAX_CAPABILITY);
        static const constexpr bool use_fast_float = ZACC_FAST_FLOAT;

        using capability_t =  std::integral_constant<uint64_t, capability>;

        using types = ZACC_MAJOR_BRANCH::types<capability>;

        using zfloat32  = typename types::zfloat32;
        using zfloat64  = typename types::zfloat64;
        using zint8     = typename types::zint8;
        using zint16    = typename types::zint16;
        using zint32    = typename types::zint32;

        using zfloat    = zfloat32;
        using zdouble   = zfloat64;
        using zbyte     = zint8;
        using zshort    = zint16;
        using zint      = zint32;
    };


    using zfloat = dispatcher::zfloat;
    using zdouble = dispatcher::zdouble;
    using zbyte = dispatcher::zbyte;
    using zshort = dispatcher::zshort;
    using zint = dispatcher::zint;

    using zfloat32 = dispatcher::zfloat32;
    using zfloat64 = dispatcher::zfloat64;
    using zint8 = dispatcher::zint8;
    using zint16 = dispatcher::zint16;
    using zint32 = dispatcher::zint32;

}