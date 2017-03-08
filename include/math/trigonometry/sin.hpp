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
#include "system/dispatcher.hpp"

namespace zacc { namespace math {

    /**
     * @brief  Sine function. Algorithm taken from SLEEF 2.80
     * @tparam capability
     * @param val [-1; 1] rad
     * @return [-1; 1]
     */
    template<typename fval_t>
    std::enable_if_t<std::is_floating_point<typename fval_t::scalar_t>::value, fval_t> vsin(fval_t val)
    {
        fval_t q = (val * magic::M_1_PI).round();
        zint iq = q;

        if(dispatcher::use_fast_float)
        {
            val -= q * magic::M_PI;
        }
        else if(std::is_same<fval_t, zfloat>::value)
        {
            val -= q * magic::PI4_Af * 4;
            val -= q * magic::PI4_Bf * 4;
            val -= q * magic::PI4_Cf * 4;
            val -= q * magic::PI4_Df * 4;
        }
        else if(std::is_same<fval_t, zdouble>::value)
        {
            val -= q * magic::PI4_A * 4;
            val -= q * magic::PI4_B * 4;
            val -= q * magic::PI4_C * 4;
            val -= q * magic::PI4_D * 4;
        }

        fval_t s = val * val;

        val = (-val)
                .when(iq & 1)
                .otherwise(val);

        fval_t u;

        if(std::is_same<fval_t, zfloat>::value)
        {
            u =         2.6083159809786593541503e-06f;
            u = u * s - 0.0001981069071916863322258f;
            u = u * s + 0.00833307858556509017944336f;
            u = u * s - 0.166666597127914428710938f;
        }
        else if(std::is_same<fval_t, zdouble>::value)
        {
            u =       - 7.97255955009037868891952e-18;
            u = u * s + 2.81009972710863200091251e-15;
            u = u * s - 7.64712219118158833288484e-13;
            u = u * s + 1.60590430605664501629054e-10;
            u = u * s - 2.50521083763502045810755e-08;
            u = u * s + 2.75573192239198747630416e-06;
            u = u * s - 0.000198412698412696162806809;
            u = u * s + 0.00833333333333332974823815;
            u = u * s - 0.166666666666666657414808;
        }

        u = s * u * val + val;

        u = fval_t::quiet_NaN()
                .when(val.is_infinite())
                .otherwise(u);

        return u;
    }
}}