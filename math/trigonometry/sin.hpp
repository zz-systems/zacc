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

#include "common.hpp"
#include "../../dispatch/dispatcher.hpp"

namespace zacc { namespace math {

    /**
     * @brief  Sine function. Algorithm taken from SLEEF 2.80
     * @tparam capability
     * @param val
     * @return
     */
    template<typename capability>
    zfloat vsin(zfloat val)
    {
        zfloat q = (val * magic::M_1_PI).trunc();
        zint iq = q;

        if(use_fast_float)
        {
            val -= q * magic::M_PI;
        }
        else
        {
            val -= q * magic::PI4_A * 4;
            val -= q * magic::PI4_B * 4;
            val -= q * magic::PI4_C * 4;
            val -= q * magic::PI4_D * 4;
        }

        zfloat s = val * val;

        val = (-val)
                .when(iq & 1)
                .otherwise(val);

        zfloat u = 2.6083159809786593541503e-06f;

        u = u * s + -0.0001981069071916863322258f;
        u = u * s + 0.00833307858556509017944336f;
        u = u * s + -0.166666597127914428710938f;

        u = s * u * val + val;

        u = zfloat::quiet_NaN()
                .when(val.is_infinite())
                .otherwise(u);

        return u;
    }
}}