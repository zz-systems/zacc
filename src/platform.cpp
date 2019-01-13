//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2015-2018 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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
//    platform &platform::enable(const features feature) {
//
//        set_capability_if_registered(feature, true);
//
//        _flags |= to_underlying(feature);
//
//        return *this;
//    }
//
//    platform &platform::disable(const features feature) {
//
//        set_capability_if_registered(feature, false);
//
//        _flags &= ~to_underlying(feature);
//
//        return *this;
//    }
//
//    platform &platform::set(const features feature, bool enabled) {
//
//        return enabled
//               ? enable(feature)
//               : disable(feature);
//    }
//
//    platform &platform::set(raw_t raw_value) {
//        _flags = raw_value;
//
//        return *this;
//    }
//
//    bool platform::is_set(const features feature) const {
//        return 0 != (_flags & to_underlying(feature));
//    }
//
//    platform::raw_t platform::raw() const {
//        return _flags;
//    }
//
//    std::vector<feature> platform::active() const {
//        std::vector<feature> result;
//
//        transform_if(_capabilities.begin(), _capabilities.end(),
//                     std::back_inserter(result),
//                     [this](auto &kv) { return kv.second; },
//                     [this](auto &kv) { return this->is_set(kv.first); });
//
//        return result;
//    }
//
//    std::vector<feature> platform::all() const {
//        std::vector<feature> result;
//
//        transform(_capabilities.begin(), _capabilities.end(),
//                  std::back_inserter(result),
//                  [this](auto &kv) { return kv.second; });
//
//        return result;
//    }
//
//    std::vector<feature> platform::match(std::initializer_list<features> required) const {
//        std::vector<feature> result;
//
//        transform_if(required.begin(), required.end(),
//                     std::back_inserter(result),
//                     [this](auto &item) { return _capabilities.at(item); },
//                     [this](auto &item) { return !this->is_set(item); });
//
//        return result;
//    }
//
//    std::vector<feature> platform::match(raw_t required) const {
//        std::vector<feature> result;
//
//        transform_if(_capabilities.begin(), _capabilities.end(),
//                     std::back_inserter(result),
//                     [this](auto &kv) { return kv.second; },
//                     [this, required](auto &kv) { return !this->is_set(kv.first) && (to_underlying(kv.first) & required) != 0; });
//
//        return result;
//    }
//
//    std::vector<feature> platform::make_capabilities(platform::raw_t value) const {
//        std::vector<feature> result;
//
//        transform_if(_capabilities.begin(), _capabilities.end(),
//                     std::back_inserter(result),
//                     [this](auto &item) { return item.second; },
//                     [this, value](auto &item) { return (value & static_cast<raw_t>(item.first)) != 0; });
//
//        return result;
//    }

    platform &platform::reload() {
        _features.reset();

        // Generic info and features
        auto cpuInfo = _cpuid.reg(1);

        _features.set(feature::sse2(), cpuInfo[cpuid::EDX][26]);

        _features.set(feature::sse3(), cpuInfo[cpuid::ECX][0]);
        _features.set(feature::ssse3(), cpuInfo[cpuid::ECX][9]);

        _features.set(feature::sse41(), cpuInfo[cpuid::ECX][19]);
        _features.set(feature::sse42(), cpuInfo[cpuid::ECX][20]);

        _features.set(feature::fma3(), cpuInfo[cpuid::ECX][12]);


        _features.set(feature::avx1(), cpuInfo[cpuid::ECX][28]); // <- TODO: XRESTORE

        // Extended features
        cpuInfo = _cpuid.reg(7);

        _features.set(feature::avx2(), cpuInfo[cpuid::EBX][5]);
        _features.set(feature::avx512(), cpuInfo[cpuid::EBX][16]);


        // Extended CPU info and features
        cpuInfo = _cpuid.ext_reg(1);

        _features.set(feature::fma4(), cpuInfo[cpuid::ECX][16]);

        // TODO: OPENCL

        return *this;
    }

//    platform &platform::register_features() {
//        register_feature(features::SSE2, "SSE2");
//        register_feature(features::SSE3, "SSE3");
//        register_feature(features::SSSE3, "SSSE3");
//        register_feature(features::SSE41, "SSE41");
//        register_feature(features::SSE42, "SSE42");
//
//        register_feature(features::FMA3, "FMA3");
//        register_feature(features::FMA4, "FMA4");
//
//        register_feature(features::AVX1, "AVX1");
//        register_feature(features::AVX2, "AVX2");
//        register_feature(features::AVX512, "AVX512");
//
//        register_feature(features::FASTFLOAT, "FASTFLOAT");
//
//        register_feature(features::OPENCL, "OPENCL");
//        register_feature(features::FPGA, "FPGA");
//
//        return *this;
//    }
//
//    platform &platform::register_feature(features feature, const char *str) {
//        if (_capabilities.find(feature) == _capabilities.end())
//            _capabilities.insert(std::make_pair(feature, zacc::feature(feature, str, is_set(feature))));
//
//        return *this;
//    }
//
//    platform::platform()
//            : _flags(0)
//    {
//        reload();
//        register_features();
//    }
//
//    platform &platform::set_capability_if_registered(const features cap, bool enabled) {
//        if (_capabilities.find(cap) != _capabilities.end() ) {
//            _capabilities.at(cap).set(enabled);
//        }
//
//        return *this;
//    }

    std::ostream &operator<<(std::ostream &os, const platform &cap) {
        using namespace std;

        os << cap._cpuid.vendor_str() << ", " << cap._cpuid.brand_str() << endl << endl;

            os << cap._features;

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
