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

#if !defined(MSVCVER)
//  GCC Intrinsics
#include <cpuid.h>
#endif

#include <bitset>
#include <map>
#include <vector>
#include <string>

#include "util/type_casts.hpp"

namespace zacc {
    struct cpuid
    {
        enum class vendors
        {
            UNKNOWN,
            VIRTUAL,
            AMD,
            INTEL
        };

        enum regs
        {
            EAX,
            EBX,
            ECX,
            EDX
        };

        using reg_t = std::bitset<32>;
        using data_entry_t = std::array<reg_t, 4>;

        /**
         * @brief cpuid wrapper
         * @param flag cpuid flag
         * @return register values
         */
        static std::array<int, 4> get_cpuid_raw(int function_id, int subfunction_id = 0)
        {
            std::array<int, 4> regs;

#ifdef MSVCVER
            /// MSVC CPUID
            __cpuidex(regs.data(), function_id, subfunction_id)

#else
            /// gcc / clang CPUID
            __cpuid_count(function_id, subfunction_id, regs[0], regs[1], regs[2], regs[3]);
#endif

            return regs;
        }

        /**
         * @brief cpuid wrapper
         * @param flag cpuid flag
         * @return register values
         */
        static data_entry_t get_cpuid(int function_id, int subfunction_id = 0)
        {
            return array_cast<reg_t>(get_cpuid_raw(function_id, subfunction_id));
        }

        cpuid()
        {
            _vendor_str = "";
            _brand_str = "";

            _vendor_str.reserve(0x20);
            _brand_str.reserve(0x40);

            _vendor_mapping = {
                { "AuthenticAMD",   vendors::AMD },
                { "GenuineIntel",   vendors::INTEL },

                { "KVMKVMKVM",      vendors::VIRTUAL },
                { "Microsoft Hv",   vendors::VIRTUAL },
                { " lrpepyh vr",    vendors::VIRTUAL },
                { "VMwareVMware",   vendors::VIRTUAL },
                { "XenVMMXenVMM",   vendors::VIRTUAL }
            };

            auto highestId = get_cpuid(0)[0].to_ulong();

            for(auto i = 0; i < highestId; i++)
                _data.push_back(get_cpuid(i, 0));

            highestId = get_cpuid(0x80000000)[0].to_ulong();

            for(auto i = 0x80000000; i < highestId; i++)
                _ext_data.push_back(get_cpuid(i, 0));

            append(_vendor_str, std::array<reg_t, 3>{_data[0][EBX], _data[0][EDX], _data[0][ECX]});

            _vendor = _vendor_mapping[_vendor_str];

            if (highestId >= 0x80000004)
            {
                for(auto i = 2; i <= 4; i++)
                    append(_brand_str, _ext_data[i]);
            }
        }

        const vendors get_vendor()                  const { return _vendor; }
        const std::string &get_vendor_str()         const { return _vendor_str; }
        const std::string &get_brand_str()          const { return _brand_str; }

        const reg_t &get_reg(int set, int reg)      const { return _data[set][reg]; }
        const reg_t &get_ext_reg(int set, int reg)  const { return _ext_data[set][reg]; }

    private:

        void append(std::string &target, const reg_t& reg)
        {
            char temp[4];

            *reinterpret_cast<ulong*>(temp) = reg.to_ulong();

            target += temp;
        }

        template<size_t dim>
        void append(std::string &target, const std::array<reg_t, dim>& data_entry)
        {
            for(auto reg : data_entry)
                append(target, reg);
        }


        std::vector<data_entry_t> _data;
        std::vector<data_entry_t> _ext_data;

        std::string _brand_str;

        std::map<std::string, vendors> _vendor_mapping;
        std::string _vendor_str;
        vendors _vendor;
    };
}