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
    template<typename capability>
    struct dispatcher {
        /// current capabilities
        static constexpr int flags = capability();

        /// sse 2 available?
        static constexpr bool has_sse2 = 0 != (capability() & capabilities::SSE2);
        /// sse 3 available?
        static constexpr bool has_sse3 = 0 != (capability() & capabilities::SSE3);
        /// ssse 3 available?
        static constexpr bool has_ssse3 = 0 != (capability() & capabilities::SSSE3);

        // fma4 available?
        static constexpr bool has_fma3 = 0 != (capability() & capabilities::FMA3);
        /// fma4 available?
        static constexpr bool has_fma4 = 0 != (capability() & capabilities::FMA4);
        /// fma available?
        static constexpr bool has_fma = has_fma3 || has_fma4;

        /// sse 4.1 available?
        static constexpr bool has_sse41 = 0 != (capability() & capabilities::SSE41);
        /// sse 4.2 available?
        static constexpr bool has_sse42 = 0 != (capability() & capabilities::SSE42);
        /// sse 4 available?
        static constexpr bool has_sse4 = has_sse41 || has_sse42;

        /// avx 1 available?
        static constexpr bool has_avx = 0 != (capability() & capabilities::AVX1);
        /// avx 2 available?
        static constexpr bool has_avx2 = 0 != (capability() & capabilities::AVX2);
        /// avx 512 available?
        static constexpr bool has_avx512 = 0 != (capability() & capabilities::AVX512);

        /// openCL available?
        static constexpr bool has_openCL = 0 != (capability() & capabilities::OPENCL);

        /// fast (lower precision) float enabled?
        static constexpr bool use_fast_float = 0 != (capability() & capabilities::FASTFLOAT);
    };

    template<typename type_t, int ...capabilities>
    struct accept_if : public std::enable_if<is_any_set(dispatcher<typename type_t::capability>::flags,
                                                        capabilities...), type_t> {
    };

    template<typename type_t, int ...capabilities>
    struct reject_if : public std::enable_if<!is_any_set(dispatcher<typename type_t::capability>::flags,
                                                         capabilities...), type_t> {
    };

    template<typename type_t, int... capabilities>
    using accept_if_t = typename accept_if<type_t, capabilities...>::type;

    template<typename type_t, int... capabilities>
    using reject_if_t = typename reject_if<type_t, capabilities...>::type;
}

#endif //ZACC_DISPATCHER_HPP
