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
#include <memory>
#include <functional>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

//#include <zacc/system/features.hpp"
#include <zacc/system/dl.hpp>

namespace zacc { namespace system {

    /**
     * Wrapper around a dynamically loaded library with controlled lifetime
     */
    struct managed_library
    {
        /**
         * Construct from path with set retry policy
         * @param library_path
         * @param retry_policy
         */
        explicit managed_library(const std::string& library_path, size_t retry_policy = 3)
                : _handle(nullptr), _library_name(library_path)
        {
            zacc_dlerror();

            for(size_t retry = 0; retry < retry_policy && _handle == nullptr; retry++)
            {
                _handle = zacc_dlopen(library_path.c_str());

                if(_handle == nullptr)
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }

            auto error = zacc_dlerror();
            if (!_handle)
            {
                throw std::logic_error("can't load library named \"" + library_path + "\": " + error);
            }

            std::clog << "[MANAGED LIBRARY][LOAD] " << _library_name << std::endl;
        }

        /**
         * Unload library, if possible
         */
        ~managed_library()
        {
            if(_handle != nullptr)
            {
                if(!zacc_dlclose(_handle))
                {
                    std::clog << zacc_dlerror() << std::endl;
                    //throw std::logic_error("can't unload library named \"" + _library_name + "\": " + error);
                }
                _handle = nullptr;
            }
        }

        /**
         * Resolves a symbol by its signature and function name
         * @tparam Signature
         * @param function_name
         * @return
         */
        template<typename Signature>
        std::function<Signature> resolve_symbol(const std::string& function_name) const
        {
            zacc_dlerror();
            auto result = zacc_dlsym(_handle, function_name.c_str());
            if (!result)
            {
                auto error = zacc_dlerror();
                if (error)
                {
                    throw std::logic_error("can't find symbol named \"" + function_name + "\": " + error);
                }
            }

            return reinterpret_cast<Signature*>(result);
        }

    private:
        void* _handle;
        std::string _library_name;
    };
}}