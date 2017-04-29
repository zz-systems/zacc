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


#if defined(ZACC_AVX)
    #include "backend/avx/types.hpp"
#elif defined(ZACC_AVX2)
    #include "backend/avx2/types.hpp"
#elif defined(ZACC_AVX512)
    #include "backend/avx512/types.hpp"
#elif defined(ZACC_SCALAR)
    #include "backend/scalar/types.hpp"
#elif defined(ZACC_SSE)
    #include "backend/sse/types.hpp"
#endif

namespace zacc {

    /**
     * @brief provides all necessary types for the current branch at compile time
     */
    struct dispatcher
    {
        /// max capability
        //static const constexpr uint64_t capability = branches::ZACC_CAPABILITIES::value;

        /// fast float enabled? used for faster and less precise computations
        static const constexpr bool use_fast_float = ZACC_FAST_FLOAT;

        /// capability type made from integral capability value
        //using capability_t =  std::integral_constant<uint64_t, capability>;

        /// type provider alias
        using types = ZACC_MAJOR_BRANCH::types<branches::ZACC_CAPABILITIES>;

        /// float32 type alias
        //using zfloat32  = typename types::zfloat32;
        /// float64 type alias
       // using zfloat64  = typename types::zfloat64;
        /// int8 type alias
        //using zint8     = typename types::zint8;
        /// int16 type alias
       // using zint16    = typename types::zint16;
        /// int32 type alias
        //using zint32    = typename types::zint32;

        /// float32 type alias
        //using zfloat    = zfloat32;
        /// float64 type alias
        //using zdouble   = zfloat64;
        /// int8 type alias
        //using zbyte     = zint8;
        /// int16 type alias
        //using zshort    = zint16;
        /// int32 type alias
        //using zint      = zint32;
    };

    /// float32 type alias
    //using zfloat    = dispatcher::zfloat;
    /// float64 type alias
    //using zdouble   = dispatcher::zdouble;
    /// int8 type alias
    //using zbyte     = dispatcher::zbyte;
    /// int16 type alias
    //using zshort    = dispatcher::zshort;
    /// int32 type alias
    //using zint      = dispatcher::zint;

    /// float32 type
    //using zfloat32  = dispatcher::zfloat32;
    /// float64 type
    //using zfloat64  = dispatcher::zfloat64;
    /// int8 type
    //using zint8     = dispatcher::zint8;
    /// int16 type
    //using zint16    = dispatcher::zint16;
    /// int32 type
    //using zint32    = dispatcher::zint32;


}