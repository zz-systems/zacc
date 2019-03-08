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

#include <string>

#if defined(__clang__) || defined(__GNUC__)
#include <cxxabi.h>
#endif

namespace zacc {

    template<typename T>
    struct type_of
    {
        type_of(const type_of&) = delete;
        type_of(type_of&&) = delete;

        static std::string name()
        {
            auto name = full_name();

            size_t colon = name.find_last_of(':');
            if(colon != std::string::npos)
            {
                return name.substr().substr(colon + 1);
            }

            return name;
        }

        static std::string full_name()
        {
            std::string name = typeid(T).name();

#if defined(__clang__) || defined(__GNUC__)
            int status;
            name = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
#endif

            return name;
        }
    };
}