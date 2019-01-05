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
#include <algorithm>
#include <vector>

#include "util/algorithm.hpp"
#include "system/platform.hpp"
#include "util/option_parser.hpp"

namespace zacc {
    /**
     * @brief Platform settings
     */
    class platform_settings
    {
    public:

        /**
         * @brief accepts main() args
         * @param argc argument count
         * @param argv argument array
         */
        platform_settings(const option_parser& parser)
        {
            for(auto feature : _platform.all_capabilities())
            {
                if(parser.has_option("-mno-" + tolower(feature.str())))
                {
                    _platform.disable(feature);
                }
            }
        }

        /**
         * @brief accepts main() args
         * @param argc argument count
         * @param argv argument array
         */
        platform_settings(const int argc, char** argv)
        {
            option_parser parser(argc, argv);

            for(auto feature : _platform.all_capabilities())
            {
                if(parser.has_option("-mno-" + tolower(feature.str())))
                {
                    _platform.disable(feature);
                }
            }
        }

        /**
         * @brief prints current value to target stream
         * @param os target stream
         * @param data printable trait
         * @return target stream
         */
        inline friend std::ostream &operator<<(std::ostream &os, const platform_settings& data)
        {
            for(auto feature : data._platform.all_capabilities())
            {
                os << " -mno-" << std::left << std::setw(15) <<  tolower(feature.str()) << " Disable " << toupper(feature.str()) << " feature" << std::endl;
            }

            return os;
        }

        inline const zacc::platform& platform() const
        {
            return _platform;
        }

    private:
        zacc::platform _platform;
    };
}