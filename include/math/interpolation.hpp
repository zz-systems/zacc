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

#include "fundamental.hpp"

namespace zacc { namespace math {
    // Cubic ===================================================================================================

    template<typename vreal_t>
    inline vreal_t cerp(vreal_t n0, vreal_t n1, vreal_t n2, vreal_t n3, vreal_t a)
    {
        auto n0_n1 = n0 - n1;

        auto p = (n3 - n2) - n0_n1;
        auto q = n0_n1 - p;
        auto r = n2 - n0;

        auto a2 = a * a;
        auto a3 = a2 * a;

        auto qa2 = q * a2;

        return vfmadd(p, a3, qa2) + vfmadd(r, a, n1);
    }

    // Linear ==================================================================================================

    template<typename vreal_t>
    inline vreal_t lerp(vreal_t n0, vreal_t n1, vreal_t a)
    {
        // = n0 - a * n0 => -a * n0 + n0;
        auto n = (1 - a) * n0;
        //auto n = fmadd(-a, n0, n0);
        return vfmadd(a, n1, n);
        //return (1 - a) * n0 + a * n1;
    }
    // SCurve3 =================================================================================================

    template<typename vreal_t>
    inline vreal_t scurve3(vreal_t a)
    {
        // 3a� - 2a�
        return (a * a * 3 - 2 * a);
    }

    // SCurve5 =================================================================================================

    template<typename vreal_t>
    inline vreal_t scurve5(vreal_t a)
    {
        auto a3 = a * a * a;
        auto a4 = a3 * a;
        auto a5 = a4 * a;

        auto q = 10 * a3;
        auto p = vfmadd(15, a4, q);

        //return (6 * a5) - (15 * a4) + (10 * a3);
        return vfmsub(6, a5, p);
    }
}}