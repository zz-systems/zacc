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
#include "branch_dispatcher.hpp"

namespace zacc {
    template<uint64_t capability = 0>
    struct dispatcher
    {
        using zfloat32  = branch_dispatcher<capability>::types::zfloat32;
        using zfloat64  = branch_dispatcher<capability>::types::zfloat64;
        using zint8     = branch_dispatcher<capability>::types::zint8;
        using zint16    = branch_dispatcher<capability>::types::zint16;
        using zint32    = branch_dispatcher<capability>::types::zint32;

        using zfloat = zfloat32;
        using zdouble = zfloat64;
        using zbyte = zint8;
        using zshort = zint16;
        using zint = zint32;
    };

#define zfloat dispatcher<capability>::zfloat
#define zdouble dispatcher<capability>::zdouble
#define zbyte dispatcher<capability>::zbyte
#define zshort dispatcher<capability>::zshort
#define zint dispatcher<capability>::zint

}