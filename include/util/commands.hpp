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
#include <string>
#include <algorithm>
#include <vector>

namespace zacc {
    /**
     * @brief Simple commandline option parser
     * @authors iain, s.zuyev
     * @remark taken from http://stackoverflow.com/a/868894/1261537 and adapted
     */
    class option_parser
    {
    public:
        /**
         * @brief accepts main() args
         * @param argc argument count
         * @param argv argument array
         */
        option_parser(const char argc, char** argv)
            : _options(argv + 1, argv + argc)
        { }

        /**
         * @brief checks if an option is set
         * @param option option name
         * @return true if the option exists, false otherwise
         */
        bool has_option(const std::string& option)
        {
            return std::find(_options.begin(), _options.end(), option) != _options.end();
        }

        /**
         * @brief gets the option value
         * @param option
         * @return option value if option exists, otherwise an empty string
         */
        const std::string& get_option(const std::string& option)
        {
            auto iter = std::find(_options.begin(), _options.end(), option);

            if(iter != _options.end() && ++ iter != _options.end())
                return *iter;

            return _empty;
        }

    private:
        std::vector<std::string> _options;
        const std::string _empty;
    };
}