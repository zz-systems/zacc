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

#include <functional>
#include <string>
#include <iostream>
#include "util/zacc_exports.hpp"

ZACC_DLL_API void*              zacc_dlopen(const char* path);
ZACC_DLL_API const char* const  zacc_dlerror();
ZACC_DLL_API void*              zacc_dlsym(void* handle, const char* member);
ZACC_DLL_API bool               zacc_dlclose(void* handle);


namespace zacc {

    class runtime_loader
    {
    public:
        runtime_loader(const std::string& library_path)
                : _library_name(library_path)
        {
            zacc_dlerror();

            _handle = zacc_dlopen(library_path.c_str());

            auto error = zacc_dlerror();
            if (!_handle)
            {
                throw std::logic_error("can't load library named \"" + library_path + "\": " + error);
            }
        }

        ~runtime_loader()
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

        template<typename Signature>
        std::function<Signature> resolve(std::string const &function_name)
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
}