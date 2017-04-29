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

#include "backend/avx/types.hpp"
#include "backend/avx2/int8.impl.hpp"
#include "backend/avx2/int16.impl.hpp"
#include "backend/avx2/int32.impl.hpp"

namespace zacc { namespace avx2 {

    template<typename _capability>
    struct types
    {
        using capability = _capability;

        using zfloat32  = ::zacc::avx::zfloat32<capability::value>;
        using zfloat64  = ::zacc::avx::zfloat64<capability::value>;

        using zint8     = ::zacc::avx2::zint8<capability::value>;
        using zint16    = ::zacc::avx2::zint16<capability::value>;
        using zint32    = ::zacc::avx2::zint32<capability::value>;

        using bfloat32  = ::zacc::avx::bfloat32<capability::value>;
        using bfloat64  = ::zacc::avx::bfloat64<capability::value>;
        using bint8     = ::zacc::avx2::bint8<capability::value>;
        using bint16    = ::zacc::avx2::bint16<capability::value>;
        using bint32    = ::zacc::avx2::bint32<capability::value>;

        static constexpr const size_t alignment = zint32::alignment;

        static const std::string major_branch_name() { return "AVX2"; }
    };
}}