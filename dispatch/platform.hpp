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


#ifndef ZACC_PLATFORM_HPP
#define ZACC_PLATFORM_HPP

#include "../common/type_traits.hpp"

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
    enum class capabilities {
        None = 0,        ///< usuallly fallback to x87 FPU

        SSE2 = 1 << 0,    ///< SSE 2 support
        SSE3 = 1 << 1,    ///< SSE 3 support
        SSSE3 = 1 << 2,    ///< SSSE 3 support

        SSE41 = 1 << 3,    ///< SSE 4.1 support
        SSE42 = 1 << 4,    ///< SSE 4.2 support

        FMA3 = 1 << 5,    ///< FMA 3 support
        FMA4 = 1 << 6,    ///< FMA 4 support

        AVX1 = 1 << 7,    ///< AVX support
        AVX2 = 1 << 8,    ///< AVX 2 support
        AVX512 = 1 << 9,    ///< AVX 512 support

        FASTFLOAT = 1 << 10, ///< use faster float computations ( lower precision )

        OPENCL = 1 << 11,    ///< OPENCL support
        FPGA = 1 << 12    ///< FPGA synthesis support?
    };

    struct platform {
        platform()
                : _flags(to_underlying(capabilities::None)) {
            reload();
        }

        platform &enable(const capabilities capability) {
            _flags |= to_underlying(capability);

            return *this;
        }

        platform &disable(const capabilities capability) {
            _flags &= ~to_underlying(capability);

            return *this;
        }

        platform &set(const capabilities capability, bool enabled) {
            return enabled
                   ? enable(capability)
                   : disable(capability);
        }

        bool is_set(const capabilities capability) {
            return 0 != (_flags & to_underlying(capability));
        }


        platform &reload() {
            _flags = to_underlying(capabilities::None);

            int cpuInfo[4];
            cpuid(cpuInfo, 1);

            set(capabilities::SSE2, cpuInfo[3] & (1 << 26));

            set(capabilities::SSE3, cpuInfo[2] & (1 << 0));
            set(capabilities::SSSE3, cpuInfo[2] & (1 << 9));

            set(capabilities::SSE41, cpuInfo[2] & (1 << 19));
            set(capabilities::SSE42, cpuInfo[2] & (1 << 20));

            set(capabilities::FMA3, cpuInfo[2] & (1 << 12));

            set(capabilities::AVX1, cpuInfo[2] & (1 << 28)); // <- TODO: XRESTORE

            // Extended CPU info
            cpuid(cpuInfo, 7);

            set(capabilities::AVX2, cpuInfo[1] & (1 << 5));
            set(capabilities::AVX512, cpuInfo[1] & (1 << 16));

            // TODO: OPENCL

            return *this;
        }

    private:
        int _flags;
    };
}
#endif //ZACC_PLATFORM_HPP
