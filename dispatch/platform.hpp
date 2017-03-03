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

#include "common/type_traits.hpp"
#include "util/io.hpp"
#include "util/algorithm.hpp"
#include "util/bithacks.hpp"

#include <vector>
#include <map>
#include <algorithm>

#if !defined(MSVCVER)
    //  GCC Intrinsics
    #include <cpuid.h>
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
     * @brief Provides metadata and typecasts to capabilities enum
     */
    class capability
    {
        typedef const char* c_str_t;
        typedef std::underlying_type_t<capabilities> raw_t;

    public:

        /**
         * @brief constructs metadata with capability and string representation
         * @param capability capability
         * @param str string representation
         * @param is_set availability flag
         */
        capability(const capabilities capability, const char* str, bool is_set = false)
                : _capability(capability), _c_str(str), _is_set(is_set)
        {}

        /**
         * @brief set the availability flag
         * @param is_set availability flag
         */
        void set(bool is_set)
        {
            _is_set = is_set;
        }

        /**
         * @brief returns capability's string representation
         * @return C-string representation
         */
        constexpr const char* c_str() const { return _c_str; }

        /**
         * @brief implicit cast to capability's string representation
         * @return C-string representation
         */
        constexpr operator const char*() const { return c_str(); };

        /**
         * @brief returns capability enum value
         * @return capability enum value
         */
        constexpr capabilities value() const { return _capability; }

        /**
         * @brief implicit cast to capability enum value
         * @return raw capability enum value
         */
        constexpr operator capabilities() const { return value(); };

        /**
         * @brief returns raw underlying value
         * @return raw underlying value
         */
        constexpr raw_t raw_value() const { return static_cast<raw_t>(_capability); }

        /**
         * @brief implicit cast to raw underlying value
         * @return raw underlying value
         */
        constexpr operator raw_t() const { return raw_value(); };

        /**
         * @brief implicit cast to capability's string representation
         * @return std::string representation
         */
        std::string str() const { return _c_str; }

        /**
         * @brief provides bitwise-or functionality
         * @param other other capability
         * @return result of bitwise-or as raw underlying value
         */
        constexpr raw_t operator |(const capability &other) { return raw_value() | other.raw_value(); }

        /**
         * @brief provides bitwise-and functionality
         * @param other other capability
         * @return result of bitwise-and as raw underlying value
         */
        constexpr raw_t operator &(const capability &other) { return raw_value() & other.raw_value(); }

        /**
         * @brief returns true if this capability is available
         * @return true if capability set, otherwise false
         */
        bool is_set() { return _is_set; }

        /**
         * @brief pretty-prints the current capability
         * @param os target output stream
         * @param cap capability object
         * @return modified target output stream
         */
        friend inline std::ostream& operator<<(std::ostream& os, const capability& cap) {
            using namespace std;

            const int w = 15;

            os << left << setw(w) << cap.c_str() << boolcolor(cap._is_set) << endl;

            return os;
        }
    private:
        const capabilities _capability;
        const char* _c_str;
        bool _is_set;
    };

    /**
     * @brief
     */
    struct platform {
    private:
        typedef std::underlying_type_t<capabilities> raw_t;
        typedef std::map<const enum capabilities, capability> capability_map_t;
    public:
        /**
         * @brief Enable capability, fluent interface
         * @param capability
         * @return self
         */
        platform &enable(const capabilities capability) {

            set_capability_if_registered(capability, true);

            _flags |= to_underlying(capability);

            return *this;
        }

        /**
         * @brief Disable capability, fluent interface
         * @param capability
         * @return self
         */
        platform &disable(const capabilities capability) {

            set_capability_if_registered(capability, false);

            _flags &= ~to_underlying(capability);

            return *this;
        }

        /**
         * @brief Set capability, fluent interface
         * @param capability
         * @param enabled
         * @return self
         */
        platform &set(const capabilities capability, bool enabled) {

            return enabled
                   ? enable(capability)
                   : disable(capability);
        }

        /**
         * @brief Set capabilities from raw value, fluent interface
         * @param raw_value
         * @return self
         */
        platform &set(uint64_t raw_value) {
            _flags = raw_value;

            return *this;
        }

        /**
         * @brief Checks if capability is set
         * @param capability
         * @return true if set, otherwise false
         */
        bool is_set(const capabilities capability) const {
            return 0 != (_flags & to_underlying(capability));
        }

        /**
         * @brief Get entire raw value with all capabilities
         * @return raw value
         */
        raw_t get_capability()
        {
            return _flags;
        }

        /**
         * @brief Get enabled capability objects from raw representation
         * @return array of capabilities for each enabled capability
         */
        std::vector<capability> get_enabled_capabilities()
        {
            std::vector<capability> result;

            transform_if(_capabilities.begin(), _capabilities.end(),
                         std::back_inserter(result),
                         [this](auto &kv) { return kv.second; },
                         [this](auto &kv) { return is_set(kv.first); });

            return result;
        }

        /**
         * @brief Get all capability objects from raw representation
         * @return array of capabilities for each enabled capability
         */
        std::vector<capability> get_capabilities() const
        {
            std::vector<capability> result;

            transform(_capabilities.begin(), _capabilities.end(),
                         std::back_inserter(result),
                         [this](auto &kv) { return kv.second; });

            return result;
        }

        /**
         * @brief Resolves platform information and populates capabilities, fluent interface
         * @return self
         */
        platform &reload() {
            _flags = to_underlying(capabilities::None);

            auto cpuInfo = cpuid(1);

            set(capabilities::SSE2, cpuInfo[3] & (1 << 26));

            set(capabilities::SSE3, cpuInfo[2] & (1 << 0));
            set(capabilities::SSSE3, cpuInfo[2] & (1 << 9));

            set(capabilities::SSE41, cpuInfo[2] & (1 << 19));
            set(capabilities::SSE42, cpuInfo[2] & (1 << 20));

            set(capabilities::FMA3, cpuInfo[2] & (1 << 12));

            set(capabilities::AVX1, cpuInfo[2] & (1 << 28)); // <- TODO: XRESTORE

            // Extended CPU info
            cpuInfo = cpuid(7);

            set(capabilities::AVX2, cpuInfo[1] & (1 << 5));
            set(capabilities::AVX512, cpuInfo[1] & (1 << 16));

            // TODO: OPENCL

            return *this;
        }

        /**
         * @brief registers main capabilitiy metadata, fluent interface
         * @return self
         */
        platform& register_capabilities()
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

            return *this;
        }

        /**
         * @brief registers a specified capability metadata, fluent interface
         * @param cap capability
         * @param str capabilitiy's string representation
         * @return self
         */
        platform & register_capability(const enum capabilities cap, const char* str)
        {
            if (_capabilities.find(cap) == _capabilities.end())
                _capabilities.insert(capability_map_t::value_type(cap, capability(cap, str, is_set(cap))));

            return *this;
        }

        /**
         * @brief returns the singleton instance
         * @return singleton instance
         */
        static platform& get_instance()
        {
            static platform instance;

            return instance;
        }

        /**
         * @brief
         * @param capability
         * @return
         */
        static constexpr uint64_t fill_capabilities_up_to(const capabilities capability)
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

        static std::array<int, 4> cpuid(int flag)
        {
            std::array<int, 4> regs;

#ifdef MSVCVER
            /// MSVC CPUID
            __cpuidex(regs.data(), flag, 0)

#else
            /// gcc / clang CPUID
            __cpuid_count(flag, 0, regs[0], regs[1], regs[2], regs[3]);
#endif

            return regs;
        }

        /**
         * @brief copy constructor not available
         */
        platform(platform const&)        = delete;

        /**
         * @brief assignment operator not available
         */
        void operator=(platform const&)  = delete;
    private:
        raw_t _flags;

        capability_map_t _capabilities;

        /**
         * @brief private constructor for singleton instantiation.
         * Fetches system information and populates main capabilities
         */
        platform()
                : _flags(to_underlying(capabilities::None)) {
            reload();
            register_capabilities();
        }

        /**
         * @brief if the capability is registered, set the availability flag, fluent interface
         * @param cap capability
         * @param enabled availability flag
         * @return self
         */
        platform & set_capability_if_registered(capabilities cap, bool enabled)
        {
            if (_capabilities.find(cap) != _capabilities.end() ) {
                _capabilities.at(cap).set(enabled);
            }

            return *this;
        }
    };

    /// pretty-prints the currently supported features
    inline std::ostream& operator<<(std::ostream& os, const platform& cap)
    {
        for(auto capability : cap.get_capabilities())
            os << capability;

        os << std::endl;

        return os;
    }
}