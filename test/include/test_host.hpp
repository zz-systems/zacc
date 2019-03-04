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

#include <zacc/system/sysinfo.hpp>
#include <zacc/system/kernel_dispatcher.hpp>

namespace zacc { namespace testing {

    template<typename Kernel, typename... ReferenceKernels>
    class host
    {  
        host(const sysinfo& sysinfo)
            : _sysinfo(sysinfo)
        {}

        virtual ~host() {}

        virtual void run(int argc, char** argv)
        {
            _dispatcher.features() = _sysinfo;
            _dispatcher.dispatch_some(argc, argv);

            _dispatcher.dispatch_one();
        }

    protected:

        system::dispatcher<system::kernel_dispatcher<Kernel>> _dispatcher;

        sysinfo _sysinfo;
    };

}}