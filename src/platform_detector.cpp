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


#include "system/platform.hpp"
#include "util/option_parser.hpp"
#include "util/algorithm.hpp"

using namespace zacc;

#if defined(_MSC_VER)
	#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#endif

int main(int argc, char** argv) {

    option_parser parser(argc, argv);
    platform platform;

    if(parser.has_option("CMAKE_OUTPUT"))
    {
        auto c = platform.enabled_capabilities();

        std::cout << join(std::begin(c), std::end(c), ";");
    }
    else
    {
        std::cout << platform;
    }

    return 0;
}