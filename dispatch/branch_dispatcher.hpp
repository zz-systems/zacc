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
#include <type_traits>

#if defined(ZACC_SCALAR)
    #include "backend/scalar/types.hpp"
#elif defined(ZACC_SSE2) || defined(ZACC_SSE3) || defined(ZACC_SSE4) || defined(ZACC_SSE4FMA)
    #include "backend/sse/types.hpp"
#elif defined(ZACC_AVX)
    #include "backend/avx/types.hpp"
#elif defined(ZACC_AVX2)
    #include "backend/avx2/types.hpp"
#elif defined(ZACC_AVX512)
    #include "backend/avx512/types.hpp"
#endif


namespace zacc {

    using capability_AVX512		= std::integral_constant<uint64_t, fill_capabilities_up_to(capabilities::AVX512)>;
    using capability_AVX2		= std::integral_constant<uint64_t, fill_capabilities_up_to(capabilities::AVX2) >;
    using capability_AVX1		= std::integral_constant<uint64_t, fill_capabilities_up_to(capabilities::AVX1) >;
    using capability_SSE4FMA	= std::integral_constant<uint64_t, fill_capabilities_up_to(capabilities::FMA4)>;
    using capability_SSE4		= std::integral_constant<uint64_t, fill_capabilities_up_to(capabilities::SSE42)>;
    using capability_SSSE3		= std::integral_constant<uint64_t, fill_capabilities_up_to(capabilities::SSSE3)>;
    using capability_SSE3		= std::integral_constant<uint64_t, fill_capabilities_up_to(capabilities::SSE3)>;
    using capability_SSE2		= std::integral_constant<uint64_t, fill_capabilities_up_to(capabilities::SSE2)>;
    using capability_SCALAR		= std::integral_constant<uint64_t, 0>;
    
    
    struct branch_dispatcher {
#if defined(ZACC_SCALAR)
        using capability = capability_SCALAR;
        using types = scalar::types<capability::value>;

#elif defined(ZACC_SSE2) // ============================================================================================
        using capability = capability_SSE2;
        using types = sse::types<capability::value>;
#elif defined(ZACC_SSE3)
        using capability = capability_SSE3;
        using types = sse::types<capability::value>;
#elif defined(ZACC_SSSE3)
        using capability = capability_SSSE3;
        using types = sse::types<capability::value>;
#elif defined(capability_SSE4)
        using capability = capability_SSE4;
        using types = sse::types<capability::value>;
#elif defined(ZACC_SSE4FMA)
        using capability = capability_SSE4FMA;
        using types = sse::types<capability::value>;

#elif defined(ZACC_AVX) // =============================================================================================
        using capability = capability_AVX1;
        using types = avx::types<capability::value>;
#elif defined(ZACC_AVX2)
        using capability = capability_AVX2;
        using types = avx2::types<capability::value>;
#elif defined(ZACC_AVX512)
        using capability = std::integral_constant<uint64_t, capabilities::AVX512>;
        using types = avx512::types<capability::value>;
#else
        static_assert(false, "invalid branch definition! Check your cmake definitions");
#endif
    };
}