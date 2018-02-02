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

#include "util/type/type_casts.hpp"

namespace zacc {
    struct cpuid
    {
        using reg_t         = std::bitset<32>;
        using data_entry_t  = std::array<reg_t, 4>;
        using data_t        = std::vector<data_entry_t>;

        /**
         * @brief
         */
        enum class vendors
        {
            UNKNOWN,
            VIRTUAL,
            AMD,
            INTEL
        };

        /**
         * @brief
         */
        enum regs
        {
            EAX,
            EBX,
            ECX,
            EDX
        };

        /**
         * @brief cpuid wrapper
         * @param flag cpuid flag
         * @return register values
         */
        static std::array<int, 4> get_cpuid_raw(int function_id, int sub_function_id = 0);

        /**
         * @brief cpuid wrapper
         * @param flag cpuid flag
         * @return register values
         */
        static data_entry_t get_cpuid(int function_id, int sub_function_id = 0);

        /**
         * @brief
         */
        cpuid();

        /**
         * @brief
         * @return
         */
        vendors vendor()                            const;

        /**
         * @brief
         * @return
         */
        const std::string &vendor_str()             const;

        /**
         * @brief
         * @return
         */
        const std::string &brand_str()              const;

        /**
         * @brief
         * @return
         */
        const data_t &data()                        const;

        /**
         * @brief
         * @return
         */
        const data_t &ext_data()                    const;

        /**
         * @brief
         * @param index
         * @return
         */
        const data_entry_t &reg(size_t index)       const;

        /**
         * @brief
         * @param index
         * @return
         */
        const data_entry_t &ext_reg(size_t index)   const;

    private:

        /**
         * @brief
         * @param target
         * @param reg
         */
        void append(std::string &target, const reg_t& reg);

        /**
         * @brief
         * @tparam dim
         * @param target
         * @param data_entry
         */
        template<size_t dim>
        void append(std::string &target, const std::array<reg_t, dim>& data_entry){
            for(auto reg : data_entry)
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