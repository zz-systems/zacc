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

#include "system/dispatcher.hpp"

namespace zacc { namespace math {

    //template<typename vreal_t, typename enable = void>
    template<typename vreal_t>
    struct constants {

    };

    //template<typename vreal_t>
    //struct constants<vreal_t, std::enable_if_t<is_double<vreal_t>::value>>
    template<>
    struct constants<zfloat64>
    {
        static const constexpr double  Z_PI = 3.14159265358979323846;
        static const constexpr double  Z_PI_2 = Z_PI / 2;

        static const constexpr double  Z_1_PI = 0.318309886183790671538;
        static const constexpr double  Z_4_PI = 1.273239544735162542821171882678754627704620361328125;
        
        static const constexpr double  Z_PI4_A = 0.78539816290140151978;
        static const constexpr double  Z_PI4_B = 4.9604678871439933374e-10;
        static const constexpr double  Z_PI4_C = 1.1258708853173288931e-18;
        static const constexpr double  Z_PI4_D = 1.7607799325916000908e-27;

        static const constexpr double  Z_L2U = .69314718055966295651160180568695068359375;
        static const constexpr double  Z_L2L = .28235290563031577122588448175013436025525412068e-12;
        static const constexpr double  Z_R_LN2 = 1.442695040888963407359924681001892137426645954152985934135449406931;

        static const constexpr double  Z_SQRT_3 = 1.73205080756887729353;
    };

    //template<typename vreal_t>
    //struct constants<vreal_t, std::enable_if_t<is_float<vreal_t>::value>>
    template<>
    struct constants<zfloat32>
    {
        static const constexpr float  Z_PI = 3.14159265358979323846f;
        static const constexpr float  Z_PI_2 = Z_PI / 2;

        static const constexpr float  Z_1_PI = 0.318309886183790671538f;
        static const constexpr float  Z_4_PI = 1.273239544735162542821171882678754627704620361328125f;

        static const constexpr float  Z_PI4_A = 0.78515625f;
        static const constexpr float  Z_PI4_B = 0.00024187564849853515625f;
        static const constexpr float  Z_PI4_C = 3.7747668102383613586e-08f;
        static const constexpr float  Z_PI4_D = 1.2816720341285448015e-12f;

        static const constexpr float  Z_L2U = 0.693145751953125f;
        static const constexpr float  Z_L2L = 1.428606765330187045e-06f;
        static const constexpr float  Z_R_LN2 = 1.442695040888963407359924681001892137426645954152985934135449406931f;

        static const constexpr float  Z_SQRT_3 = 1.73205080756887729353;
    };
}}