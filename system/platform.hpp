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

#include <vector>
#include <map>
#include <algorithm>

#include "cpuid.hpp"
#include "capabilities.hpp"

#include "common/type_traits.hpp"
#include "util/algorithm.hpp"
#include "util/bithacks.hpp"

namespace zacc {

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
            _flags = 0;

            auto cpuInfo = cpuid::get_cpuid_raw(1);

            set(capabilities::SSE2, cpuInfo[3] & (1 << 26));

            set(capabilities::SSE3, cpuInfo[2] & (1 << 0));
            set(capabilities::SSSE3, cpuInfo[2] & (1 << 9));

            set(capabilities::SSE41, cpuInfo[2] & (1 << 19));
            set(capabilities::SSE42, cpuInfo[2] & (1 << 20));

            set(capabilities::FMA3, cpuInfo[2] & (1 << 12));

            set(capabilities::AVX1, cpuInfo[2] & (1 << 28)); // <- TODO: XRESTORE

            // Extended CPU info
            cpuInfo = cpuid::get_cpuid_raw(7);

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
            register_capability(capabilities::FPGA, "FPGA");

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
         * @brief sets all capabilities to enabled until the given one and returns the raw value
         * @param capability highest capability (inclusive)
         * @return raw value
         */
        static constexpr raw_t fill_capabilities_up_to(const capabilities capability)
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
                : _flags(0) {
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

        /// pretty-prints the currently supported features
        inline friend std::ostream& operator<<(std::ostream& os, const platform& cap)
        {
            using namespace std;

            os << cap._cpuid.get_brand_str() << endl << endl;

            for(auto capability : cap.get_capabilities())
                os << capability;

            os << endl;

            return os;
        }

        static thread_local cpuid _cpuid;
    };

    thread_local cpuid platform::_cpuid;

}