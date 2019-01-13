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


#pragma once

#include <iostream>
#include "util/io.hpp"
#include "util/type/type_casts.hpp"
#include "util/bithacks.hpp"
#include "util/algorithm.hpp"
#include "system/features.hpp"
#include "system/cpuid.hpp"
#include <bitset>
#include <functional>
#include <algorithm>

namespace zacc {

    struct sysinfo
    {
        constexpr operator uint64_t() { return _mask; }

        constexpr sysinfo() noexcept
            : _mask {0}
        {}

        constexpr explicit sysinfo(uint64_t mask) noexcept
                : _mask(mask)
        {}

        sysinfo(cpuid cpuid) noexcept
            : sysinfo()
        {
            // Generic info and features
            auto cpuInfo = cpuid.reg(1);

            set(feature::sse2(), cpuInfo[cpuid::EDX][26]);

            set(feature::sse3(), cpuInfo[cpuid::ECX][0]);
            set(feature::ssse3(), cpuInfo[cpuid::ECX][9]);

            set(feature::sse41(), cpuInfo[cpuid::ECX][19]);
            set(feature::sse42(), cpuInfo[cpuid::ECX][20]);

            set(feature::fma3(), cpuInfo[cpuid::ECX][12]);


            set(feature::avx1(), cpuInfo[cpuid::ECX][28]); // <- TODO: XRESTORE

            // Extended features
            cpuInfo = cpuid.reg(7);

            set(feature::avx2(), cpuInfo[cpuid::EBX][5]);
            set(feature::avx512(), cpuInfo[cpuid::EBX][16]);

            // Extended CPU info and features
            cpuInfo = cpuid.ext_reg(1);

            set(feature::fma4(), cpuInfo[cpuid::ECX][16]);
        }

        template <typename... Args>
        constexpr explicit sysinfo(feature f, Args&& ...args ) noexcept
                : _mask{or_reduce(f, std::forward<Args>(args)...)}
        {}

        constexpr sysinfo(const sysinfo&) = default;
        constexpr sysinfo(sysinfo&& other) = default;
        sysinfo& operator=(const sysinfo& other) = default;

        constexpr sysinfo& set() noexcept
        {
            _mask = ~0ul;

            return *this;
        }

        constexpr sysinfo& set( feature feature, bool value = true ) noexcept
        {
            if(value)
                _mask |= feature.mask();
            else
                _mask &= ~feature.mask();

            return *this;
        }

        sysinfo& set( std::initializer_list<feature> features, bool value = true ) noexcept
        {
            std::for_each(std::begin(features), std::end(features), [this, value](auto feature) {
                this->set(feature, value);
            });

            return *this;
        }

        constexpr sysinfo& reset() noexcept
        {
            _mask = 0;

            return *this;
        }

        constexpr sysinfo& reset( feature feature ) noexcept
        {
            set(feature, false);

            return *this;
        }

        sysinfo& reset( std::initializer_list<feature> features ) noexcept
        {
            std::for_each(std::begin(features), std::end(features), [this](auto feature) {
                this->reset(feature);
            });

            return *this;
        }

        constexpr bool test( feature feature ) const
        {
            return (_mask & feature.mask()) != 0;
        }

        bool test( std::initializer_list<feature> features ) const
        {
            return std::accumulate(std::begin(features), std::end(features), false, [this](bool acc, auto feature) {
                return acc && this->test(feature);
            });
        }

        constexpr uint64_t mask() const
        {
            return _mask;
        }

        auto active() const
        {
            std::vector<feature> result;
            auto features = available();

            transform_if(std::begin(features), std::end(features),
                         std::back_inserter(result),
                         [](auto i) { return i; },
                         [this](auto i) { return this->test(i); });

            return result;
        }

        auto match(feature required) const
        {
            feature diff { (this->_mask ^ required.mask()) & required.mask() };

            return diff.active();
        }

        // TODO: size
        constexpr std::array<feature, 13> available() const
        {
            return {{
                            feature::scalar(), feature::sse2(), feature::sse3(),
                            feature::ssse3(), feature::sse41(), feature::sse42(),
                            feature::fma3(), feature::fma4(), feature::avx1(),
                            feature::avx2(), feature::avx512(), feature::opencl(), feature::fpga()
                    }};
        }

        friend std::ostream &operator<<(std::ostream &os, const sysinfo& data) {
            using namespace std;

            for(auto feature : data.available())
                os << left << setw(15) << zacc::toupper(feature.to_string()) << boolcolor(data.test(feature)) << endl;

            os << endl;

            return os;
        }
    private:
        uint64_t _mask;
    };
}