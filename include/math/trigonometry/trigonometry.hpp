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

#include "math/common.hpp"
#include "system/dispatcher.hpp"

namespace zacc { namespace math {

    /**
     * @brief  Sine function. Algorithm taken from SLEEF 2.80 and vecmathlib
     * @tparam type [zfloat, zdouble]
     * @param val [-pi; pi] rad
     * @return [-1; 1]
     */
    template<typename vreal_t>
    std::enable_if_t<is_floating_point<vreal_t>::value && vreal_t::dispatcher::has_integer_types, vreal_t> vsin(vreal_t val)
    {
        vreal_t q = (val * constants<vreal_t>::Z_1_PI).floor();
        zint iq = q;

        // when performance > precision
        if(dispatcher::use_fast_float)
        {
            val = vfmadd(q, -constants<vreal_t>::Z_PI, val);
        }
        else
        {
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_A * 4, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_B * 4, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_C * 4, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_D * 4, val);
        }

        vreal_t s = val * val;

        val = (-val)
                .when(iq & 1)
                .otherwise(val);

        vreal_t u;

        // for single precision
        if(is_float<vreal_t>::value)
        {
            u =              2.6083159809786593541503e-06f;
            u = vfmsub(u, s, 0.0001981069071916863322258f);
            u = vfmadd(u, s, 0.00833307858556509017944336f);
            u = vfmsub(u, s, 0.166666597127914428710938f);
        }
        // for double precision
        else if(is_double<vreal_t>::value)
        {
            u =            - 7.97255955009037868891952e-18;
            u = vfmadd(u, s, 2.81009972710863200091251e-15);
            u = vfmsub(u, s, 7.64712219118158833288484e-13);
            u = vfmadd(u, s, 1.60590430605664501629054e-10);
            u = vfmsub(u, s, 2.50521083763502045810755e-08);
            u = vfmadd(u, s, 2.75573192239198747630416e-06);
            u = vfmsub(u, s, 0.000198412698412696162806809);
            u = vfmadd(u, s, 0.00833333333333332974823815);
            u = vfmsub(u, s, 0.166666666666666657414808);
        }

//        u = s * u * val + val;
        u = vfmadd(s, u * val, val);

        u = vreal_t::quiet_NaN()
                .when(val.is_infinite())
                .otherwise(u);

        return u;
    }

    /**
     * @brief  Cosine function. Algorithm taken from SLEEF 2.80 and vecmathlib
     * @tparam type [zfloat, zdouble]
     * @param val [-pi; pi] rad
     * @return [-1; 1]
     */
    template<typename vreal_t>
    std::enable_if_t<is_floating_point<vreal_t>::value && vreal_t::dispatcher::has_integer_types, vreal_t> vcos(vreal_t val)
    {
        vreal_t q = 2.0 * (val * constants<vreal_t>::Z_1_PI - 0.5).floor() + 1;
        zint iq = q;

        // when performance > precision
        if(dispatcher::use_fast_float)
        {
            val -= q * constants<vreal_t>::Z_PI_2;
        }
        else
        {
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_A * 2, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_B * 2, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_C * 2, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_D * 2, val);
        }

        vreal_t s = val * val;

        val = (val)
                .when(iq & 2)
                .otherwise(-val);

        vreal_t u;

        // for single precision
        if(is_float<vreal_t>::value)
        {
            u =              2.6083159809786593541503e-06f;
            u = vfmsub(u, s, 0.0001981069071916863322258f);
            u = vfmadd(u, s, 0.00833307858556509017944336f);
            u = vfmsub(u, s, 0.166666597127914428710938f);
        }
        // for double precision
        else if(is_double<vreal_t>::value)
        {
            u =            - 7.97255955009037868891952e-18;
            u = vfmadd(u, s, 2.81009972710863200091251e-15);
            u = vfmsub(u, s, 7.64712219118158833288484e-13);
            u = vfmadd(u, s, 1.60590430605664501629054e-10);
            u = vfmsub(u, s, 2.50521083763502045810755e-08);
            u = vfmadd(u, s, 2.75573192239198747630416e-06);
            u = vfmsub(u, s, 0.000198412698412696162806809);
            u = vfmadd(u, s, 0.00833333333333332974823815);
            u = vfmsub(u, s, 0.166666666666666657414808);
        }

        //u = s * u * val + val;
        u = vfmadd(s, u * val, val);

        u = vreal_t::quiet_NaN()
                .when(val.is_infinite())
                .otherwise(u);

        return u;
    }

    /**
     * @brief  Tangens function. Algorithm taken from SLEEF 2.80 and vecmathlib
     * @tparam type [zfloat, zdouble]
     * @param val [-pi/2; pi/2] rad
     * @return [-1; 1]
     */
    template <typename vreal_t>
    std::enable_if_t<is_floating_point<vreal_t>::value && vreal_t::dispatcher::has_integer_types, vreal_t> vtan(vreal_t val)
    {
        vreal_t q = (val * 2 * constants<vreal_t>::Z_1_PI).round();
        zint iq = q;

        // when performance > precision
        if(dispatcher::use_fast_float)
        {
            val -= q * constants<vreal_t>::Z_PI_2;
        }
        else
        {
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_A * 2, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_B * 2, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_C * 2, val);
            val = vfmadd(q, -constants<vreal_t>::Z_PI4_D * 2, val);
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
            u =              0.00927245803177356719970703f;
            u = vfmadd(u, s, 0.00331984995864331722259521f);
            u = vfmadd(u, s, 0.0242998078465461730957031f);
            u = vfmadd(u, s, 0.0534495301544666290283203f);
            u = vfmadd(u, s, 0.133383005857467651367188f);
            u = vfmadd(u, s, 0.333331853151321411132812f);
        }
        // for double precision
        else if(is_double<vreal_t>::value)
        {
            u =              1.01419718511083373224408e-05;
            u = vfmsub(u, s, 2.59519791585924697698614e-05);
            u = vfmadd(u, s, 5.23388081915899855325186e-05);
            u = vfmsub(u, s, 3.05033014433946488225616e-05);
            u = vfmadd(u, s, 7.14707504084242744267497e-05);
            u = vfmadd(u, s, 8.09674518280159187045078e-05);
            u = vfmadd(u, s, 0.000244884931879331847054404);
            u = vfmadd(u, s, 0.000588505168743587154904506);
            u = vfmadd(u, s, 0.00145612788922812427978848);
            u = vfmadd(u, s, 0.00359208743836906619142924);
            u = vfmadd(u, s, 0.00886323944362401618113356);
            u = vfmadd(u, s, 0.0218694882853846389592078);
            u = vfmadd(u, s, 0.0539682539781298417636002);
            u = vfmadd(u, s, 0.133333333333125941821962);
            u = vfmadd(u, s, 0.333333333333334980164153);
        }

        //u = s * u * x + x;
        u = vfmadd(s, u * x, x);

        u = (1 / x)
                .when(iq & 1)
                .otherwise(u);

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
    std::enable_if_t<is_floating_point<vreal_t>::value && vreal_t::dispatcher::has_integer_types, vreal_t> vatan2(vreal_t y, vreal_t x)
    {
        auto q = vreal_t(2)
                .when(x < 0)
                .otherwise(0);

        x = x.abs();

        auto mask = y > x;
        auto x0 = x, y0 = y;

        x = y0.when(mask).otherwise(x0);
        y = (-x0).when(mask).otherwise(y0);
        q += vreal_t(1.0).when(mask).otherwise(0);

        auto s = y / x;
        auto t = s * s;

        vreal_t u;

        // for single precision
        if(is_float<vreal_t>::value)
        {
            u =              0.00282363896258175373077393f;
            u = vfmsub(u, t, 0.0159569028764963150024414f);
            u = vfmadd(u, t, 0.0425049886107444763183594f);
            u = vfmsub(u, t, 0.0748900920152664184570312f);
            u = vfmadd(u, t, 0.106347933411598205566406f);
            u = vfmsub(u, t, 0.142027363181114196777344f);
            u = vfmadd(u, t, 0.199926957488059997558594f);
            u = vfmsub(u, t, 0.333331018686294555664062f);
        }
        // for double precision
        else if(is_double<vreal_t>::value)
        {
            u =            - 1.88796008463073496563746e-05;
            u = vfmadd(u, t, 0.000209850076645816976906797);
            u = vfmsub(u, t, 0.00110611831486672482563471);
            u = vfmadd(u, t, 0.00370026744188713119232403);
            u = vfmsub(u, t, 0.00889896195887655491740809);
            u = vfmadd(u, t, 0.016599329773529201970117);
            u = vfmsub(u, t, 0.0254517624932312641616861);
            u = vfmadd(u, t, 0.0337852580001353069993897);
            u = vfmsub(u, t, 0.0407629191276836500001934);
            u = vfmadd(u, t, 0.0466667150077840625632675);
            u = vfmsub(u, t, 0.0523674852303482457616113);
            u = vfmadd(u, t, 0.0587666392926673580854313);
            u = vfmsub(u, t, 0.0666573579361080525984562);
            u = vfmadd(u, t, 0.0769219538311769618355029);
            u = vfmsub(u, t, 0.090908995008245008229153);
            u = vfmadd(u, t, 0.111111105648261418443745);
            u = vfmsub(u, t, 0.14285714266771329383765);
            u = vfmadd(u, t, 0.199999999996591265594148);
            u = vfmsub(u, t, 0.333333333333311110369124);
        }

        t = vfmadd(u, t * s, s);
        t = vfmadd(q, constants<vreal_t>::Z_PI_2, t);

        return t;
    }
}}