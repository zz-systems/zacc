//---------------------------------------------------------------------------------
// The MIT License (MIT)
// 
// Copyright (c) 2015-2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

namespace zzsystems { namespace gorynych {

    using namespace std;

    class cl_builder 
    {
    public:
        static inline void register_mapping(const string &key, const string &value)
        {
            _replace_mapping[key] = value;
        }
        static void find_and_replace(string& source, string const& find, string const& replace)
        {
            for(string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
            {
                source.replace(i, find.length(), replace);
                i += replace.length();
            }
        }
        static inline void register_function(const string &ret_type, const string &func_name, const string &params, 
            const map<string, string> &captured, const string &body)
        {
            auto b = body;

            for(const auto &kv : captured)
            {
                find_and_replace(b, kv.first, kv.second);
            }

            for(const auto &kv : _replace_mapping)
            {
                find_and_replace(b, kv.first, kv.second);
            }            

            auto signature = ret_type + " " + func_name + params;

            _functions[signature] = signature + b;

            cout << "signature: " << signature << endl << "body: " << _functions[signature] << endl;
        }

        static inline string get_function(const string& signature)
        {
            return _functions[signature];
        }

        static inline void register_type(const string& type, const string& name, const string& members)
        {
            _types[name] = "typedef " + type + " " + members + " " + name + ";";

            cout << "type: " << _types[name] << endl;
        }

        //static inline string invoke_function(const string& signature, )
    private:
        static map<string, string> _replace_mapping;
        static map<string, string> _functions;
        static map<string, string> _types;
    };

    map<string, string> cl_builder::_replace_mapping;
    map<string, string> cl_builder::_functions;
    map<string, string> cl_builder::_types;

     #ifdef COMPILE_OPENCL
        #define STRINGIFY_CL_FUNC(...) #__VA_ARGS__
        #define REGISTER_CL_FUNC(ret_type, func_name, params, captures, ...) \
            cl_builder::register_function(#ret_type, #func_name, #params, captures, #__VA_ARGS__);


        #define REGISTER_CL_TYPE(type, name, ...) \
            cl_builder::register_type(#type, #name, #__VA_ARGS__)

        #define NV(var) { #var, to_string(var) } 
        #define CAPTURE_CL_PARAMS(...) std::map<std::string, std::string>({__VA_ARGS__})
    #else 
        #define STRINGIFY_CL_FUNC(...) __VA_ARGS__
        #define REGISTER_CL_FUNC(ret_type, func_name, params, captures, ...) __VA_ARGS__

        #define NV(var)
        #define CAPTURE_CL_PARAMS(...)
    #endif

    
}}