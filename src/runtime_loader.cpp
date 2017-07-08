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

#include "system/runtime_loader.hpp"

#ifdef WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


void* zacc_dlopen(const char* path)
{
#ifdef WIN32
    return (void*)LoadLibrary(path);
#else
    return dlopen(path, RTLD_LAZY);
#endif
}

const char* const zacc_dlerror()
{
#ifdef WIN32
    return "";
#else
    return dlerror();
#endif
}

void* zacc_dlsym(void* handle, const char* symbol)
{
#ifdef WIN32
    return (void*)GetProcAddress((HMODULE)handle, symbol);
#else
    return dlsym(handle, symbol);
#endif
}

bool zacc_dlclose(void* handle)
{
#ifdef WIN32
    return FreeLibrary((HMODULE)handle);
#elif defined(__APPLE__)
    // currently calling dlclose causes a segfault on application exit
    return true;
#else
    return dlclose(handle) == 0;
#endif
}