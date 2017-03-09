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
     * @brief  Sine function. Algorithm taken from SLEEF 2.80 and vecmathlib
     * @tparam type [zfloat, zdouble]
     * @param val [-1; 1] rad
     * @return [-1; 1]
     */
    template<typename vreal_t>
    std::enable_if_t<is_floating_point<vreal_t>::value, vreal_t> vsin(vreal_t val)
    {
        vreal_t q = (val * constants<vreal_t>::M_1_PI).floor();
        zint iq = q;

        // when performance > precision
        if(dispatcher::use_fast_float)
        {
            val -= q * constants<vreal_t>::M_PI;
        }
        else
        {
            val -= q * constants<vreal_t>::PI4_A * 4;
            val -= q * constants<vreal_t>::PI4_B * 4;
            val -= q * constants<vreal_t>::PI4_C * 4;
            val -= q * constants<vreal_t>::PI4_D * 4;
        }

        vreal_t s = val * val;

        val = (-val)
                .when(iq & 1)
                .otherwise(val);

        vreal_t u;

        // for single precision
        if(is_float<vreal_t>::value)
        {
            u =         2.6083159809786593541503e-06f;
            u = u * s - 0.0001981069071916863322258f;
            u = u * s + 0.00833307858556509017944336f;
            u = u * s - 0.166666597127914428710938f;
        }
        // for double precision
        else if(is_double<vreal_t>::value)
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

        u = vreal_t::quiet_NaN()
                .when(val.is_infinite())
                .otherwise(u);

        return u;
    }

    /**
     * @brief  Cosine function. Algorithm taken from SLEEF 2.80 and vecmathlib
     * @tparam type [zfloat, zdouble]
     * @param val [-1; 1] rad
     * @return [-1; 1]
     */
    template<typename vreal_t>
    std::enable_if_t<is_floating_point<vreal_t>::value, vreal_t> vcos(vreal_t val)
    {
        vreal_t q = 2.0 * (val * constants<vreal_t>::M_1_PI - 0.5).floor() + 1;
        zint iq = q;

        // when performance > precision
        if(dispatcher::use_fast_float)
        {
            val -= q * constants<vreal_t>::M_PI_2;
        }
        else
        {
            val -= q * constants<vreal_t>::PI4_A * 2;
            val -= q * constants<vreal_t>::PI4_B * 2;
            val -= q * constants<vreal_t>::PI4_C * 2;
            val -= q * constants<vreal_t>::PI4_D * 2;
        }

        vreal_t s = val * val;

        val = (val)
                .when(iq & 2)
                .otherwise(-val);

        vreal_t u;

        // for single precision
        if(is_float<vreal_t>::value)
        {
            u =         2.6083159809786593541503e-06f;
            u = u * s - 0.0001981069071916863322258f;
            u = u * s + 0.00833307858556509017944336f;
            u = u * s - 0.166666597127914428710938f;
        }
        // for double precision
        else if(is_double<vreal_t>::value)
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

        u = vreal_t::quiet_NaN()
                .when(val.is_infinite())
                .otherwise(u);

        return u;
    }

    /**
     * @brief  Tangens function. Algorithm taken from SLEEF 2.80 and vecmathlib
     * @tparam type [zfloat, zdouble]
     * @param val [-1; 1] rad
     * @return [-1; 1]
     */
    template <typename vreal_t>
    std::enable_if_t<is_floating_point<vreal_t>::value, vreal_t> vtan(vreal_t val)
    {
        vreal_t q = (val * 2 * constants<vreal_t>::M_1_PI).round();
        zint iq = q;

        // when performance > precision
        if(dispatcher::use_fast_float)
        {
            val -= q * constants<vreal_t>::M_PI_2;
        }
        else
        {
            val -= q * constants<vreal_t>::PI4_A * 2;
            val -= q * constants<vreal_t>::PI4_B * 2;
            val -= q * constants<vreal_t>::PI4_C * 2;
            val -= q * constants<vreal_t>::PI4_D * 2;
        }

        auto x = val;
        auto s = x * x;

        x = (-x)
                .when(iq & 1)
                .otherwise(x);

        vreal_t u;

        // for single precision
        if(is_float<vreal_t>::value)
        {
            u =         0.00927245803177356719970703f;
            u = u * s + 0.00331984995864331722259521f;
            u = u * s + 0.0242998078465461730957031f;
            u = u * s + 0.0534495301544666290283203f;
            u = u * s + 0.133383005857467651367188f;
            u = u * s + 0.333331853151321411132812f;
        }
        // for double precision
        else if(is_double<vreal_t>::value)
        {
            u =         1.01419718511083373224408e-05;
            u = u * s - 2.59519791585924697698614e-05;
            u = u * s + 5.23388081915899855325186e-05;
            u = u * s - 3.05033014433946488225616e-05;
            u = u * s + 7.14707504084242744267497e-05;
            u = u * s + 8.09674518280159187045078e-05;
            u = u * s + 0.000244884931879331847054404;
            u = u * s + 0.000588505168743587154904506;
            u = u * s + 0.00145612788922812427978848;
            u = u * s + 0.00359208743836906619142924;
            u = u * s + 0.00886323944362401618113356;
            u = u * s + 0.0218694882853846389592078;
            u = u * s + 0.0539682539781298417636002;
            u = u * s + 0.133333333333125941821962;
            u = u * s + 0.333333333333334980164153;
        }

        u = s * u * x + x;

        u = x.rcp()
                .when(iq & 1)
                .otherwise(u);

        u = vreal_t::quiet_NaN()
                .when(val.is_infinite())
                .otherwise(u);

        return u;
    }

    /*template <typename vreal_t>
    std::enable_if_t<is_floating_point<vreal_t>::value, vreal_t> vtan(vreal_t val)
    {
        return vsin(val) / vcos(val);
    };*/

}}