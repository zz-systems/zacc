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

#include <thread>

#include "system/platform.hpp"

#if defined(_OPENMP)
    #include <omp>
#endif


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

    platform &platform::set(raw_t raw_value) {
        _flags = raw_value;

        return *this;
    }

    bool platform::is_set(const capabilities capability) const {
        return 0 != (_flags & to_underlying(capability));
    }

    platform::raw_t platform::raw() {
        return _flags;
    }

    std::vector<capability> platform::enabled_capabilities() const {
        std::vector<capability> result;

        transform_if(_capabilities.begin(), _capabilities.end(),
                     std::back_inserter(result),
                     [this](auto &kv) { return kv.second; },
                     [this](auto &kv) { return this->is_set(kv.first); });

        return result;
    }

    std::vector<capability> platform::all_capabilities() const {
        std::vector<capability> result;

        transform(_capabilities.begin(), _capabilities.end(),
                  std::back_inserter(result),
                  [this](auto &kv) { return kv.second; });

        return result;
    }

    std::vector<capability> platform::match_capabilities(std::initializer_list<capabilities> required) const {
        std::vector<capability> result;

        transform_if(required.begin(), required.end(),
                     std::back_inserter(result),
                     [this](auto &item) { return _capabilities.at(item); },
                     [this](auto &item) { return !this->is_set(item); });

        return result;
    }

    std::vector<capability> platform::match_capabilities(raw_t raw_value) const {
        std::vector<capability> result;

        transform_if(_capabilities.begin(), _capabilities.end(),
                     std::back_inserter(result),
                     [this](auto &kv) { return kv.second; },
                     [this, raw_value](auto &kv) { return !this->is_set(kv.first) && (to_underlying(kv.first) & raw_value) != 0; });

        return result;
    }

    std::vector<capability> platform::make_capabilities(platform::raw_t value) const {
        std::vector<capability> result;

        transform_if(_capabilities.begin(), _capabilities.end(),
                     std::back_inserter(result),
                     [this](auto &item) { return item.second; },
                     [this, value](auto &item) { return (value & static_cast<raw_t>(item.first)) != 0; });

        return result;
    }

    platform &platform::reload() {
        _flags = 0;

        // Generic info and features
        auto cpuInfo = _cpuid.reg(1);

        set(capabilities::SSE2, cpuInfo[cpuid::EDX][26]);

        set(capabilities::SSE3, cpuInfo[cpuid::ECX][0]);
        set(capabilities::SSSE3, cpuInfo[cpuid::ECX][9]);

        set(capabilities::SSE41, cpuInfo[cpuid::ECX][19]);
        set(capabilities::SSE42, cpuInfo[cpuid::ECX][20]);

        set(capabilities::FMA3, cpuInfo[cpuid::ECX][12]);


        set(capabilities::AVX1, cpuInfo[cpuid::ECX][28]); // <- TODO: XRESTORE

        // Extended features
        cpuInfo = _cpuid.reg(7);

        set(capabilities::AVX2, cpuInfo[cpuid::EBX][5]);
        set(capabilities::AVX512, cpuInfo[cpuid::EBX][16]);


        // Extended CPU info and features
        cpuInfo = _cpuid.ext_reg(1);

        set(capabilities::FMA4, cpuInfo[cpuid::ECX][16]);

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

    platform &platform::register_capability(const capabilities cap, const char *str) {
        if (_capabilities.find(cap) == _capabilities.end())
            _capabilities.insert(capability_map_t::value_type(cap, capability(cap, str, is_set(cap))));

        return *this;
    }

    platform &platform::global() {
        static platform instance;

        return instance;
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

    size_t platform::num_threads() {
        #if defined(_OPENMP)
        return omp_num_threads();
        #else
        return std::thread::hardware_concurrency();
        #endif
    }

    thread_local cpuid platform::_cpuid;
}
