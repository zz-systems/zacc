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
#include "backend/all.hpp"

namespace zacc {

    /**
     * @brief provides all necessary types for the current branch at compile time
     */
    struct arch
    {
        /// fast float enabled? used for faster and less precise computations
        static const constexpr bool use_fast_float = ZACC_FAST_FLOAT;

        /// type provider alias
        using types = ZACC_MAJOR_ARCH::types<branches::ZACC_ARCH>;
    };

    using zint8      = typename arch::types::zint8;
    using zint16     = typename arch::types::zint16;
    using zint32     = typename arch::types::zint32;
    using zfloat32   = typename arch::types::zfloat32;
    using zfloat64   = typename arch::types::zfloat64;
    using zbyte      = zint8;
    using zshort     = zint16;
    using zint       = zint32;
    using zfloat     = zfloat32;
    using zdouble    = zfloat64;

    using bint8      = typename arch::types::bint8;
    using bint16     = typename arch::types::bint16;
    using bint32     = typename arch::types::bint32;
    using bfloat32   = typename arch::types::bfloat32;
    using bfloat64   = typename arch::types::bfloat64;
    using bbyte      = bint8;
    using bshort     = bint16;
    using bint       = bint32;
    using bfloat     = bfloat32;
    using bdouble    = bfloat64;
}
