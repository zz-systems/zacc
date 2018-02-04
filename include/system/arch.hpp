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

#include "system/platform.hpp"
#include "system/capabilities.hpp"
#include "backend/all.hpp"

namespace zacc {

    /**
     * @brief provides all necessary types for the current branch at compile time
     */
    struct dispatched_arch
    {
        using arch = architectures::ZACC_ARCH;

        /// fast float enabled? used for faster and less precise computations
        static constexpr bool use_fast_float = ZACC_FAST_FLOAT;


        /// exposed dispatched implementation of zfloat32
        using zfloat32  = zacc::backend::ZACC_MAJOR_ARCH::zfloat32<arch::value>;
        /// exposed dispatched implementation of zfloat64
        using zfloat64  = zacc::backend::ZACC_MAJOR_ARCH::zfloat64<arch::value>;
        /// exposed dispatched implementation of zint8
        using zint8     = zacc::backend::ZACC_MAJOR_ARCH::zint8<arch::value>;
        /// exposed dispatched implementation of zint16
        using zint16    = zacc::backend::ZACC_MAJOR_ARCH::zint16<arch::value>;
        /// exposed dispatched implementation of zint32
        using zint32    = zacc::backend::ZACC_MAJOR_ARCH::zint32<arch::value>;

        /// exposed dispatched implementation of boolean vector for zfloat32
        using bfloat32  = zacc::backend::ZACC_MAJOR_ARCH::bfloat32<arch::value>;
        /// exposed dispatched implementation of boolean vector for zfloat64
        using bfloat64  = zacc::backend::ZACC_MAJOR_ARCH::bfloat64<arch::value>;
        /// exposed dispatched implementation of boolean vector for zint8
        using bint8     = zacc::backend::ZACC_MAJOR_ARCH::bint8<arch::value>;
        /// exposed dispatched implementation of boolean vector for zint16
        using bint16    = zacc::backend::ZACC_MAJOR_ARCH::bint16<arch::value>;
        /// exposed dispatched implementation of boolean vector for zint32
        using bint32    = zacc::backend::ZACC_MAJOR_ARCH::bint32<arch::value>;

        static const std::string name() { return arch::name(); }
    };

    /// exposed dispatched implementation of zfloat32
    using zfloat32   = typename dispatched_arch::zfloat32;
    /// exposed dispatched implementation of zfloat64
    using zfloat64   = typename dispatched_arch::zfloat64;
    /// exposed dispatched implementation of zint8
    using zint8      = typename dispatched_arch::zint8;
    /// exposed dispatched implementation of zint16
    using zint16     = typename dispatched_arch::zint16;
    /// exposed dispatched implementation of zint32
    using zint32     = typename dispatched_arch::zint32;

    /// alias for zfloat64
    using zdouble    = zfloat64;
    /// alias for zfloat32
    using zfloat     = zfloat32;
    /// alias for zint8
    using zbyte      = zint8;
    /// alias for zint16
    using zshort     = zint16;
    /// alias for zint32
    using zint       = zint32;

    /// exposed dispatched implementation of boolean vector for zfloat32
    using bfloat32   = typename dispatched_arch::bfloat32;
    /// exposed dispatched implementation of boolean vector for zfloat64
    using bfloat64   = typename dispatched_arch::bfloat64;
    /// exposed dispatched implementation of boolean vector for zint8
    using bint8      = typename dispatched_arch::bint8;
    /// exposed dispatched implementation of boolean vector for zint16
    using bint16     = typename dispatched_arch::bint16;
    /// exposed dispatched implementation of boolean vector for zint32
    using bint32     = typename dispatched_arch::bint32;

    /// alias for bfloat32
    using bfloat     = bfloat32;
    /// alias for bfloat64
    using bdouble    = bfloat64;
    /// alias for bint8
    using bbyte      = bint8;
    /// alias for bint16
    using bshort     = bint16;
    /// alias for bint32
    using bint       = bint32;
}
