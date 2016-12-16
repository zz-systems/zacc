//
// Created by Sergej Zuyev on 12/13/2016.
//

#ifndef ZACC_DISPATCHER_HPP
#define ZACC_DISPATCHER_HPP

#include "platform.hpp"
#include <type_traits>

namespace zacc {
    template<typename capability>
    struct dispatcher {
        /// current capabilities
        static constexpr int flags = capability();

        /// sse 2 available?
        static constexpr bool has_sse2 = 0 != (capability() & CAPABILITY_SSE2);
        /// sse 3 available?
        static constexpr bool has_sse3 = 0 != (capability() & CAPABILITY_SSE3);
        /// ssse 3 available?
        static constexpr bool has_ssse3 = 0 != (capability() & CAPABILITY_SSSE3);

        // fma4 available?
        static constexpr bool has_fma3 = 0 != (capability() & CAPABILITY_FMA3);
        /// fma4 available?
        static constexpr bool has_fma4 = 0 != (capability() & CAPABILITY_FMA4);
        /// fma available?
        static constexpr bool has_fma = has_fma3 || has_fma4;

        /// sse 4.1 available?
        static constexpr bool has_sse41 = 0 != (capability() & CAPABILITY_SSE41);
        /// sse 4.2 available?
        static constexpr bool has_sse42 = 0 != (capability() & CAPABILITY_SSE42);
        /// sse 4 available?
        static constexpr bool has_sse4 = has_sse41 || has_sse42;

        /// avx 1 available?
        static constexpr bool has_avx = 0 != (capability() & CAPABILITY_AVX1);
        /// avx 2 available?
        static constexpr bool has_avx2 = 0 != (capability() & CAPABILITY_AVX2);
        /// avx 512 available?
        static constexpr bool has_avx512 = 0 != (capability() & CAPABILITY_AVX512);

        /// openCL available?
        static constexpr bool has_openCL = 0 != (capability() & CAPABILITY_OPENCL);

        /// fast (lower precision) float enabled?
        static constexpr bool use_fast_float = 0 != (capability() & CAPABILITY_FASTFLOAT);
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
