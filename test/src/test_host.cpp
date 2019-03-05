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


#include <iostream>

#include <zacc/system/sysinfo.hpp>
#include <zacc/hosting/main_host.hpp>
#include <test.hpp>

int main(int argc, char** argv)
{
    using namespace zacc::testing;
    using namespace zacc::hosting;

    zacc::option_parser options(argc, argv);
    zacc::sysinfo sysinfo;

    options >> zacc::get_sysinfo(sysinfo);

    std::cout << zacc::put_sysinfo(sysinfo) << std::endl;

    std::cout << "Your system supports: " << std::endl;
    std::cout << zacc::sysinfo() << std::endl;

    return main_host<test>(sysinfo)
        .run(argc, argv);
}