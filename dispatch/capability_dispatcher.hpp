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

namespace zacc {
    template<uint64_t capability = 0>
    struct capability_dispatcher {

        using flag_t = std::make_unsigned_t<capabilities>;
        using self_t = capability_dispatcher;

        static constexpr bool is_set(capabilities flag)
        {
            return 0 != (flags & static_cast<flag_t>(flag));
        }

        /// current capabilities
        static constexpr flag_t flags = capability;

        /// sse 2 available?
        static constexpr bool has_SSE2 = is_set(capabilities::SSE2);
        /// sse 3 available?
        static constexpr bool has_SSE3 = is_set(capabilities::SSE3);
        /// ssse 3 available?
        static constexpr bool has_SSSE3 = is_set(capabilities::SSSE3);

        // fma4 available?
        static constexpr bool has_FMA3 = is_set(capabilities::FMA3);
        /// fma4 available?
        static constexpr bool has_FMA4 = is_set(capabilities::FMA4);
        /// fma available?
        static constexpr bool has_FMA = has_FMA3 || has_FMA4;

        /// sse 4.1 available?
        static constexpr bool has_SSE41 = is_set(capabilities::SSE41);
        /// sse 4.2 available?
        static constexpr bool has_SSE42 = is_set(capabilities::SSE42);
        /// sse 4 available?
        static constexpr bool has_SSE4 = has_SSE41 || has_SSE42;

        /// generic sse available?
        static constexpr bool has_SSE = has_SSE2 || has_SSE3 || has_SSSE3 || has_SSE4;

        /// avx 1 available?
        static constexpr bool has_AVX = is_set(capabilities::AVX1);
        /// avx 2 available?
        static constexpr bool has_AVX2 = is_set(capabilities::AVX2);
        /// avx 512 available?
        static constexpr bool has_AVX512 = is_set(capabilities::AVX512);

        /// openCL available?
        static constexpr bool has_OPENCL = is_set(capabilities::OPENCL);

        /// fast (lower precision) float enabled?
        static constexpr bool use_fast_float = is_set(capabilities::FASTFLOAT);
    };

    #define use_fast_float capability_dispatcher<capability>::use_fast_float
}