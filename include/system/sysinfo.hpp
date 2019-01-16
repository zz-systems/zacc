#include <utility>

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
#include <iomanip>
#include "util/option_parser.hpp"
#include "system/feature.hpp"
#include "system/arch.hpp"
#include "system/cpuid.hpp"

namespace zacc {

    struct sysinfo : feature
    {
        using feature::feature;

        sysinfo() noexcept
            : feature()
        {
            cpuid cpuid;

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
    };

    class put_sysinfo
    {
        sysinfo _sysinfo;
    public:
        explicit put_sysinfo(sysinfo sysinfo)
            : _sysinfo {std::move(sysinfo)}
        {}

        friend std::ostream& operator<<(std::ostream& os, put_sysinfo)
        {
            for(auto feature : sysinfo::available())
            {
                os << " -mno-" << std::left << std::setw(15) <<  tolower(feature.to_string()) << " Disable " << toupper(feature.to_string()) << " feature" << std::endl;
            }

            return os;
        }
    };

    class get_sysinfo
    {
        sysinfo& _sysinfo;
    public:
        explicit get_sysinfo(sysinfo& sysinfo)
            : _sysinfo {sysinfo}
        {}

        friend option_parser& operator>>(option_parser& parser, get_sysinfo sysinfo)
        {
            for(auto feature : sysinfo::available())
            {
                if(parser.has_option("-mno-" + tolower(feature.to_string())))
                {
                    sysinfo._sysinfo.reset(feature);
                }
            }

            return parser;
        }
    };
}