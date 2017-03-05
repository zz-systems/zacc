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

#include "system/cpuid.hpp"

namespace zacc {
    std::array<int, 4> cpuid::get_cpuid_raw(int function_id, int sub_function_id) {
        std::array<int, 4> regs;

#ifdef MSVCVER
        // MSVC CPUID
        __cpuidex(regs.data(), function_id, sub_function_id)

#else
        // gcc / clang CPUID
        __cpuid_count(function_id, sub_function_id, regs[0], regs[1], regs[2], regs[3]);
#endif

        return regs;
    }

    cpuid::data_entry_t cpuid::get_cpuid(int function_id, int sub_function_id) {
        return array_cast<reg_t>(get_cpuid_raw(function_id, sub_function_id));
    }

    cpuid::cpuid() {
        _vendor_str = "";
        _brand_str = "";

        _vendor_str.reserve(0x20);
        _brand_str.reserve(0x40);

        _vendor_mapping = {
                {"AuthenticAMD", vendors::AMD},
                {"GenuineIntel", vendors::INTEL},

                {"KVMKVMKVM",    vendors::VIRTUAL},
                {"Microsoft Hv", vendors::VIRTUAL},
                {" lrpepyh vr",  vendors::VIRTUAL},
                {"VMwareVMware", vendors::VIRTUAL},
                {"XenVMMXenVMM", vendors::VIRTUAL}
        };

        auto highestId = get_cpuid(0)[0].to_ulong();

        for (auto i = 0; i < highestId; i++)
            _data.push_back(get_cpuid(i, 0));

        highestId = get_cpuid(0x80000000)[0].to_ulong();

        for (auto i = 0x80000000; i < highestId; i++)
            _ext_data.push_back(get_cpuid(i, 0));

        append(_vendor_str, std::array<reg_t, 3>{_data[0][EBX], _data[0][EDX], _data[0][ECX]});

        _vendor = _vendor_mapping[_vendor_str];

        if (highestId >= 0x80000004) {
            for (auto i = 2; i <= 4; i++)
                append(_brand_str, _ext_data[i]);
        }
    }

    void cpuid::append(std::string &target, const cpuid::reg_t &reg) {
        char temp[4];

        *reinterpret_cast<ulong *>(temp) = reg.to_ulong();

        target += temp;
    }

    const cpuid::vendors cpuid::vendor() const { return _vendor; }

    const std::string &cpuid::vendor_str() const { return _vendor_str; }

    const std::string &cpuid::brand_str() const { return _brand_str; }

    const cpuid::data_t &cpuid::data() const { return _data; }

    const cpuid::data_t &cpuid::ext_data() const { return _ext_data; }

    const cpuid::data_entry_t &cpuid::reg(size_t index) const { return _data[index]; }

    const cpuid::data_entry_t &cpuid::ext_reg(size_t index) const { return _ext_data[index]; }
}
