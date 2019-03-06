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

#include <bitset>
#include <map>
#include <vector>
#include <string>

#include <zacc/util/type/cast.hpp>

#if !defined(_MSC_VER)
//  GCC Intrinsics
#include <cpuid.h>
#else 
#include <intrin.h>
#endif

namespace zacc 
{
    struct cpuid
    {
        using reg_t         = std::bitset<32>;
        using data_entry_t  = std::array<reg_t, 4>;
        using data_t        = std::vector<data_entry_t>;

        /**
         * Processor vendors
         */
        enum class vendors
        {
            UNKNOWN,    ///< unknown processor
            VIRTUAL,    ///< virtual machine (hypervisor)
            AMD,        ///< AMD CPU
            INTEL       ///< Intel CPU
        };

        /**
         * @brief x86 registers
         */
        enum regs
        {
            EAX,    ///< EAX
            EBX,    ///< EBX
            ECX,    ///< ECX
            EDX     ///< EDX
        };

        /**
         * @brief cpuid wrapper
         * @param flag cpuid flag
         * @return register values
         */
        std::array<int, 4> get_cpuid_raw(int function_id, int sub_function_id = 0)
        {
            std::array<int, 4> regs {{ 0 }};

        #ifdef _MSC_VER
            // MSVC CPUID
            __cpuidex(regs.data(), function_id, sub_function_id);
        #else
            // gcc / clang CPUID
            __cpuid_count(function_id, sub_function_id, regs[0], regs[1], regs[2], regs[3]);
        #endif

            return regs;
        }

        /**
         * @brief cpuid wrapper
         * @param flag cpuid flag
         * @return register values
         */
        data_entry_t get_cpuid(int function_id, int sub_function_id = 0)
        {
            return array_cast<reg_t>(get_cpuid_raw(function_id, sub_function_id));
        }

        /**
         * constructor
         */
        cpuid()
        {
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

            for (u_long i = 0; i < highestId; i++)
                _data.push_back(get_cpuid(i, 0));


            append(_vendor_str, std::array<reg_t, 3>{{_data[0][EBX], _data[0][EDX], _data[0][ECX]}});

            _vendor = _vendor_mapping[_vendor_str];

            highestId = get_cpuid(0x80000000)[0].to_ulong();

            // EAX=80000000h: Get Highest Extended Function Supported
            highestId = get_cpuid(0x80000000)[0].to_ulong();
            _ext_data.push_back(get_cpuid(0x80000000, 0));

            // EAX=80000001h: Extended Processor Info and Feature Bits
            _ext_data.push_back(get_cpuid(0x80000001, 0));

            //EAX=80000002h,80000003h,80000004h: Processor Brand String
            if (highestId >= 0x80000004) {
                for (auto i = 0x80000002; i <= 0x80000004; i++) {
                    auto data = get_cpuid(i, 0);

                    _ext_data.push_back(data);
                    append(_brand_str, data);
                }
            }
        }

        /**
         * Returns the vendor
         */
        vendors vendor() const 
        {
            return _vendor; 
        }

        /**
         * Returns the vendor name
         */
        const std::string &vendor_str() const
        {
            return _vendor_str;
        }

        /**
         * Returns the brand string
         */
        const std::string &brand_str() const
        {
            return _brand_str; 
        }

        /**
         * Returns CPUID data
         */
        const data_t &data() const
        {
            return _data; 
        }

        /**
         * Returns CPUID extended data
         */
        const data_t &ext_data() const
        {
            return _ext_data; 
        }

        /**
         * @brief gets register at index
         * @param index
         */
        const data_entry_t &reg(size_t index) const
        {
            return _data[index]; 
        }

        /**
         * @brief gets extended register at index
         * @param index
         */
        const data_entry_t &ext_reg(size_t index) const
        {
            return _ext_data[index]; 
        }

    private:

        /**
         * @brief Appends string value in register to string
         * @param target target string
         * @param reg source register
         */
        void append(std::string &target, const reg_t& reg)
        {
            char temp[5];

            *reinterpret_cast<uint32_t *>(temp) = reg.to_ulong();

            temp[4] = '\0';

            target += temp;
        }

        /**
         * @brief Appends string value in registers to string
         * @tparam dim register count
         * @param target target string
         * @param regs source registers
         */
        template<size_t dim>
        void append(std::string &target, const std::array<reg_t, dim>& regs){
            for(auto reg : regs)
                append(target, reg);
        }


        data_t _data;
        data_t _ext_data;

        std::string _brand_str;

        std::map<std::string, vendors> _vendor_mapping;
        std::string _vendor_str;
        vendors _vendor;
    };
}