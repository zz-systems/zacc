//
// Created by Sergej Zuyev on 12/13/2016.
//

#ifndef ZACC_PLATFORM_HPP
#define ZACC_PLATFORM_HPP

//#include "../common/conversion/common.hpp"

#ifdef MSVCVER

/// MSVC CPUID
#define cpuid(info, x)    __cpuidex(info, x, 0)

#else
//  GCC Intrinsics
#include <cpuid.h>
/// gcc / clang CPUID
#define cpuid(info, x) __cpuid_count(x, 0, info[0], info[1], info[2], info[3])

#endif

namespace zacc {
    /// @enum capabilities
    /// @brief relevant system capabilities
    enum capabilities {
        CAPABILITY_NONE = 0,        ///< usuallly fallback to x87 FPU

        CAPABILITY_SSE2 = 1 << 0,    ///< SSE 2 support
        CAPABILITY_SSE3 = 1 << 1,    ///< SSE 3 support
        CAPABILITY_SSSE3 = 1 << 2,    ///< SSSE 3 support

        CAPABILITY_SSE41 = 1 << 3,    ///< SSE 4.1 support
        CAPABILITY_SSE42 = 1 << 4,    ///< SSE 4.2 support

        CAPABILITY_FMA3 = 1 << 5,    ///< FMA 3 support
        CAPABILITY_FMA4 = 1 << 6,    ///< FMA 4 support

        CAPABILITY_AVX1 = 1 << 7,    ///< AVX support
        CAPABILITY_AVX2 = 1 << 8,    ///< AVX 2 support
        CAPABILITY_AVX512 = 1 << 9,    ///< AVX 512 support

        CAPABILITY_FASTFLOAT = 1 << 10, ///< use faster float computations ( lower precision )

        CAPABILITY_OPENCL = 1 << 11,    ///< OPENCL support
        CAPABILITY_FPGA = 1 << 12    ///< FPGA synthesis support?
    };

    struct platform {
        platform()
                : _flags(CAPABILITY_NONE) {
            reload();
        }

        platform &enable(const capabilities capability) {
            _flags |= capability;

            return *this;
        }

        platform &disable(const capabilities capability) {
            _flags &= ~capability;

            return *this;
        }

        platform &set(const capabilities capability, bool enabled) {
            return enabled
                   ? enable(capability)
                   : disable(capability);
        }

        bool is_set(const capabilities capability) {
            return 0 != (_flags & capability);
        }


        platform &reload() {
            _flags = CAPABILITY_NONE;

            int cpuInfo[4];
            cpuid(cpuInfo, 1);

            set(CAPABILITY_SSE2, cpuInfo[3] & (1 << 26));

            set(CAPABILITY_SSE3, cpuInfo[2] & (1 << 0));
            set(CAPABILITY_SSSE3, cpuInfo[2] & (1 << 9));

            set(CAPABILITY_SSE41, cpuInfo[2] & (1 << 19));
            set(CAPABILITY_SSE42, cpuInfo[2] & (1 << 20));

            set(CAPABILITY_FMA3, cpuInfo[2] & (1 << 12));

            set(CAPABILITY_AVX1, cpuInfo[2] & (1 << 28)); // <- TODO: XRESTORE

            // Extended CPU info
            cpuid(cpuInfo, 7);

            set(CAPABILITY_AVX2, cpuInfo[1] & (1 << 5));
            set(CAPABILITY_AVX512, cpuInfo[1] & (1 << 16));

            // TODO: OPENCL

            return *this;
        }

    private:
        int _flags;
    };
}
#endif //ZACC_PLATFORM_HPP
