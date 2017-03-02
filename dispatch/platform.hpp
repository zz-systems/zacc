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

#include "common/type_traits.hpp"
#include "util/io.hpp"
#include "util/algorithm.hpp"

#include <vector>
#include <map>
#include <algorithm>

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
    enum class capabilities : uint64_t {
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

    /**
     * @brief count last zero bits
     * @see Hacker's delight SE [Henry S. Warren Jr]
     * @tparam T
     * @param value
     * @return
     */
    template<typename T>
    constexpr std::enable_if_t<std::is_integral<T>::value, size_t> ntz(T value)
    {
        size_t n = 0;

        value = ~value & (value - 1);

        n = 0;

        while(value != 0)
        {
            n++;
            value >>= 1;
        }

        return n;
    }

    /**
     * @brief
     * @param capability
     * @return
     */
    constexpr uint64_t fill_capabilities_up_to(const capabilities capability)
    {
        auto value = to_underlying(capability);
        uint64_t result = 0;

        for(size_t i = 0; i < ntz(value); i++)
        {
            result |= 1;
            result <<= 1;
        }

        return result;
    }

    class capability
    {
        typedef const char* c_str_t;
        typedef std::underlying_type_t<capabilities> raw_t;

    public:
        //constexpr capability(capabilities capability, const char* str)
        //        : _capability(capability), _c_str(str)
        //{}

        capability(const capabilities capability, const char* str)
                : _capability(capability), _c_str(str)
        {}

        constexpr operator const char*() const { return c_str(); };
        constexpr operator capabilities() const { return value(); };
        constexpr operator raw_t() const { return raw_value(); };

        //operator std::string() const { return str(); }


        constexpr raw_t raw_value() const { return static_cast<raw_t>(_capability); }
        constexpr capabilities value() const { return _capability; }
        constexpr const char* c_str() const { return _c_str; }
        std::string str() const { return _c_str; }

        inline constexpr uint64_t set_capabilities_until()
        {
            auto value = to_underlying(_capability);
            uint64_t result = 0;

            for(size_t i = 0; i < ntz(value); i++)
            {
                result |= 1;
                result <<= 1;
            }

            return result;
        }

    private:
        const capabilities _capability;
        const char* _c_str;
    };

    /**
     * @brief
     */
    struct platform {

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

        platform &set(uint64_t raw_value) {
            _flags = raw_value;

            return *this;
        }

        bool is_set(const capabilities capability) const {
            return 0 != (_flags & to_underlying(capability));
        }

        uint64_t get_capability()
        {
            return _flags;
        }

        std::vector<capability> get_capabilities()
        {
            std::vector<capability> result;

            transform_if(_capabilities.begin(), _capabilities.end(),
                         std::back_inserter(result),
                         [this](auto &kv) { return kv.second; },
                         [this](auto &kv) { return is_set(kv.first); });

            return result;
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

        void register_capabilities()
        {
            register_capability(zacc::capabilities::None, "DEFAULT");

            register_capability(capabilities::SSE2, "SSE2");
            register_capability(capabilities::SSE3, "SSE3");
            register_capability(capabilities::SSSE3, "SSSE3");
            register_capability(capabilities::SSE41, "SSE41");
            register_capability(capabilities::SSE42, "SSE42");

            register_capability(capabilities::FMA3, "FMA3");
            register_capability(capabilities::FMA4, "FMA4");

            register_capability(capabilities::AVX1, "AVX1");
            register_capability(capabilities::AVX2, "AVX2");
            register_capability(capabilities::AVX512, "AVX512");

            register_capability(capabilities::FASTFLOAT, "FASTFLOAT");

            register_capability(capabilities::OPENCL, "OPENCL");
            register_capability(capabilities::None, "FPGA");
        }

        void register_capability(const enum capabilities cap, const char* str)
        {
            _capabilities.insert(capability_map_t::value_type(cap, capability(cap, str)));
        }

        static platform& get_instance()
        {
            static platform instance;

            return instance;
        }

        platform(platform const&)        = delete;
        void operator=(platform const&)  = delete;
    private:
        typedef std::map<const enum capabilities, capability> capability_map_t;

        uint64_t _flags;

        capability_map_t _capabilities;

        platform()
                : _flags(to_underlying(capabilities::None)) {
            reload();
            register_capabilities();
        }
    };

    /// pretty-prints the currently supperted features
    inline std::ostream& operator<<(std::ostream& os, const platform& cap)
    {
        using namespace std;

        int w = 15;

        os << left << setw(w) << "SSE2:"	        << boolcolor(cap.is_set(capabilities::SSE2)) << endl;
        os << left << setw(w) << "SSE3:"	        << boolcolor(cap.is_set(capabilities::SSE3))  << endl;
        os << left << setw(w) << "SSSE3:"	        << boolcolor(cap.is_set(capabilities::SSSE3)) << endl;

        os << left << setw(w) << "SSE4.1:"	        << boolcolor(cap.is_set(capabilities::SSE41)) << endl;
        os << left << setw(w) << "SSE4.2:"	        << boolcolor(cap.is_set(capabilities::SSE42)) << endl;

        os << left << setw(w) << "FMA3:"	        << boolcolor(cap.is_set(capabilities::FMA3)) << endl;
        os << left << setw(w) << "FMA4:"	        << boolcolor(cap.is_set(capabilities::FMA4)) << endl;

        //os << "Uses XRSTORE: "	<< cap.use_xrstore << endl;

        os << left << setw(w) << "AVX1:"	        << boolcolor(cap.is_set(capabilities::AVX1)) << endl;
        os << left << setw(w) << "AVX2:"	        << boolcolor(cap.is_set(capabilities::AVX2)) << endl;
        os << left << setw(w) << "AVX512:"	        << boolcolor(cap.is_set(capabilities::AVX512)) << endl;

        os << left << setw(w) << "OpenCL(GPU):" 	<< boolcolor(cap.is_set(capabilities::OPENCL)) << endl;
        os << endl;

        return os;
    }
}
#endif //ZACC_PLATFORM_HPP
