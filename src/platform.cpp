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

#include "system/platform.hpp"

namespace zacc {
    platform &platform::enable(const capabilities capability) {

        set_capability_if_registered(capability, true);

        _flags |= to_underlying(capability);

        return *this;
    }

    platform &platform::disable(const capabilities capability) {

        set_capability_if_registered(capability, false);

        _flags &= ~to_underlying(capability);

        return *this;
    }

    platform &platform::set(const capabilities capability, bool enabled) {

        return enabled
               ? enable(capability)
               : disable(capability);
    }

    platform &platform::set(uint64_t raw_value) {
        _flags = raw_value;

        return *this;
    }

    bool platform::is_set(const capabilities capability) const {
        return 0 != (_flags & to_underlying(capability));
    }

    platform::raw_t platform::raw() {
        return _flags;
    }

    std::vector<capability> platform::enabled_capabilities() {
        std::vector<capability> result;

        transform_if(_capabilities.begin(), _capabilities.end(),
                     std::back_inserter(result),
                     [this](auto &kv) { return kv.second; },
                     [this](auto &kv) { return is_set(kv.first); });

        return result;
    }

    std::vector<capability> platform::all_capabilities() const {
        std::vector<capability> result;

        transform(_capabilities.begin(), _capabilities.end(),
                  std::back_inserter(result),
                  [this](auto &kv) { return kv.second; });

        return result;
    }

    platform &platform::reload() {
        _flags = 0;

        auto cpuInfo = _cpuid.reg(1);

        set(capabilities::SSE2, cpuInfo[cpuid::EDX][26]);

        set(capabilities::SSE3, cpuInfo[cpuid::ECX][0]);
        set(capabilities::SSSE3, cpuInfo[cpuid::ECX][9]);

        set(capabilities::SSE41, cpuInfo[cpuid::ECX][19]);
        set(capabilities::SSE42, cpuInfo[cpuid::ECX][20]);

        set(capabilities::FMA3, cpuInfo[cpuid::ECX][12]);

        set(capabilities::AVX1, cpuInfo[cpuid::ECX][28]); // <- TODO: XRESTORE

        // Extended CPU info
        cpuInfo = _cpuid.reg(7);

        set(capabilities::AVX2, cpuInfo[cpuid::EBX][5]);
        set(capabilities::AVX512, cpuInfo[cpuid::EBX][16]);

        // TODO: OPENCL

        return *this;
    }

    platform &platform::register_capabilities() {
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

    platform &platform::register_capability(const enum capabilities cap, const char *str) {
        if (_capabilities.find(cap) == _capabilities.end())
            _capabilities.insert(capability_map_t::value_type(cap, capability(cap, str, is_set(cap))));

        return *this;
    }

    platform &platform::instance() {
        static platform instance;

        return instance;
    }

    constexpr platform::raw_t platform::fill_capabilities_up_to(const capabilities capability) {
        auto value = to_underlying(capability);
        uint64_t result = 0;

        for(size_t i = 0; i < ntz(value); i++)
        {
            result |= 1;
            result <<= 1;
        }

        return result;
    }

    platform::platform()
            : _flags(0) {
        reload();
        register_capabilities();
    }

    platform &platform::set_capability_if_registered(const capabilities cap, bool enabled) {
        if (_capabilities.find(cap) != _capabilities.end() ) {
            _capabilities.at(cap).set(enabled);
        }

        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const platform &cap) {
        using namespace std;

        os << cap._cpuid.vendor_str() << ", " << cap._cpuid.brand_str() << endl << endl;

        for(auto capability : cap.all_capabilities())
            os << capability;

        os << endl;

        return os;
    }

    thread_local cpuid platform::_cpuid;
}
