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
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <zacc/util/algorithm.hpp>

namespace zacc {
    struct option 
    {
        std::string key;
        std::string value;
    };

    inline std::ostream& operator<<(std::ostream& os, const option& option)
    {
        os << option.key << ":" << option.value;

        return os;
    }
    
    template<typename T>
    inline const option& operator>>(const option& option, T& target)
    {
        if(!option.key.empty() && !option.value.empty())        
        {
            std::stringstream ss;
            ss << option.value;
            ss >> target;    
        }

        return option;
    }

    template<>
    inline const option& operator>>(const option& option, bool& target)
    { 
        if(option.key.empty())
        {
            target = false;
        }
        else if(option.value.empty())
        {
            // assume flag
            target = true;
        }
        else
        {
            // parse boolean
            std::stringstream ss;
            ss << zacc::tolower(option.value);
            ss >> target;
        }

        return option;
    }

    /**
     * @brief Simple commandline option parser
     * @authors iain, s.zuyev
     * @remark taken from http://stackoverflow.com/a/868894/1261537 and adapted
     */
    class option_parser
    {
        bool is_param(const std::string& str)
        {
            return str.find_first_of("-/\\") == 0;
        }
    public:
        /**
         * @brief accepts main() args
         * @param argc argument count
         * @param argv argument array
         */
        option_parser(const int argc, char** argv)
        {
            std::vector<std::string> options(argv + 1, argv + argc);

            for(auto iter = options.begin(); iter != options.end(); ++iter)
            {                
                if(!is_param(*iter))
                {
                    // not a param 
                    continue;
                }     

                std::string key, value;

                auto key_pos = iter->find_first_not_of("-/\\");
                if (key_pos == std::string::npos)
                {
                    // invalid key
                    continue;
                }                

                auto value_pos = iter->find_first_of("=", key_pos);
                if (value_pos == std::string::npos)
                {
                    key = iter->substr(key_pos);

                    // check next item
                    if((iter + 1) != options.end() && !is_param(*(iter + 1)))
                    {
                        value = *(++iter);
                    }
                }
                else
                {
                    key = iter->substr(key_pos, value_pos - key_pos);
                    value = iter->substr(value_pos + 1);
                }

                key = trim(key);
                value = trim(value);

                _options[key] = { key, value };
            }
        }
        
        const option& operator[] (const std::string& key) const
        {
            auto iter = _options.find(key);

            if(iter != _options.end())
                return iter->second;

            return _empty;
        }

        /**
         * @brief checks if an option is set
         * @param option option name
         * @return true if the option exists, false otherwise
         */
        bool has_option(const std::string& key) const
        {
            return _options.find(key) != _options.end();
        }

        /**
         * @brief gets the option value
         * @param option
         * @return option value if option exists, otherwise an empty string
         */
        const std::string& get_option(const std::string& key) const
        {
            return this->operator[](key).value;
        }

    private:
        std::map<std::string, option> _options;
        option _empty;
    };
}