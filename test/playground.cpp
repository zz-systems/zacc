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


#include "system/dispatched_arch.hpp"

#include <iostream>
#include "math/trigonometry/trigonometry.hpp"
#include <cmath>
using namespace zacc;

int main() {

    zfloat32 fv(12, 13, 14, 15);

    std::cout << fv;

    std::cout << -((fv + 24) * 123.0f) * 0 + 42;

    std::cout << "conditional:" << fv.when(0).otherwise({1, 2, 3, 4});

    std::cout << "{ ";

    for (auto i : fv)
        std::cout << i << " ";

    std::cout << "}";

    zfloat a = 2;
    zfloat b = 3;
    zfloat c = 4;

    ZTRACE("fused mul*");
    std::cout << std::endl << "fused muladd:" << vfmadd(a, b, c) << std::endl;
    std::cout << std::endl << "fused mulsub:" << vfmsub(a, b, c) << std::endl;

    ZTRACE("fused mul* via op");
    std::cout << std::endl << "fused muladd via op:" << a * b + c << std::endl;
    std::cout << std::endl << "fused mulsub via op:" << a * b - c << std::endl;

    ZTRACE("fused mul via op");
    std::cout << std::endl << "fused mul via op:" << static_cast<zfloat>(a * b) << std::endl;

    /*for (int i = -9; i <= 9; i++)
    {
        std::cout << std::endl << "sin(" << std::right << std::setw(3) <<  i * 10 << "): " << std::left << std::setw(10) << sin(i * 10 / 180.0 * M_PI) << math::vsin(zfloat(i * 10 / 180.0 * M_PI)) << std::endl;
    }

    for (int i = -18; i <= 18; i++)
    {
        std::cout << std::endl << "cos(" << std::right << std::setw(3) <<  i * 10 << "): " << std::left << std::setw(10) << cos(i * 10 / 180.0 * M_PI) << math::vcos(zfloat(i * 10 / 180.0 * M_PI)) << std::endl;
    }

    for (int i = -18; i <= 18; i++)
    {
        std::cout << std::endl << "tan(" << std::right << std::setw(3) <<  i * 10 << "): " << std::left << std::setw(10) << tan(i * 10 / 180.0 * M_PI) << math::vtan(zfloat(i * 10 / 180.0 * M_PI)) << std::endl;
    }*/

    return 0;
}
