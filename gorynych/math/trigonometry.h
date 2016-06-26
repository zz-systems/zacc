////---------------------------------------------------------------------------------
//// The MIT License (MIT)
////
//// Copyright (c) 2015-2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in all
//// copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//// SOFTWARE.
////---------------------------------------------------------------------------------
//
//#pragma once
//
//#include "../basic_functions.h"
//#include "../avx/avx.h"
//#include "../sse/sse.h"
//
//namespace zzsystems { namespace gorynych { namespace math {
//
//    VECTORIZED_F inline vreal vsin(vreal VREF a)
//    {
//        using vint = typename resolve_type<vreal>::vint;
//        //using vreal = _vreal;
//        //using vint = _vint;
//        // Algorithm taken from SLEEF 2.80
//
//        vreal PI4_A, PI4_B, PI4_C, PI4_D;
//
//        PI4_A = 0.78515625f;
//        PI4_B = 0.00024187564849853515625f;
//        PI4_C = 3.7747668102383613586e-08f;
//        PI4_D = 1.2816720341285448015e-12f;
//
//        vreal q = vtrunc(a * M_1_PI);
//        vint iq = q;
//
//#if !defined(COMPILE_FAST_FLOAT)
//        a = vfmadd(q, -PI4_A * 4, a);
//        a = vfmadd(q, -PI4_B * 4, a);
//        a = vfmadd(q, -PI4_C * 4, a);
//        a = vfmadd(q, -PI4_D * 4, a);
//#else
//        a = vfmadd(q, -M_PI, a);
//#endif
//
//        vreal s = a * a;
//
//        a = vsel(iq & cfl<vint, 1>::val(), -a, a);
//
//        vreal u = 2.6083159809786593541503e-06f;
//        u = vfmadd(u, s, static_cast<vreal>(-0.0001981069071916863322258f));
//        u = vfmadd(u, s, static_cast<vreal>(0.00833307858556509017944336f));
//        u = vfmadd(u, s, static_cast<vreal>(-0.166666597127914428710938f));
//
////        u = vfmadd(u, s, -0.0001981069071916863322258f);
////        u = vfmadd(u, s, 0.00833307858556509017944336f);
////        u = vfmadd(u, s, -0.166666597127914428710938f);
//
//        u = vfmadd(s, u * a, a);
//
//        u = vsel(visinf(a), ccl<vreal>::ones(), u);
//
//        return u;
//    }
//
//    VECTORIZED_F inline vreal vcos(vreal VREF a)
//    {
//        using vint = typename resolve_type<vreal>::vint;
//
//        // Algorithm taken from SLEEF 2.80
//
//        vreal PI4_A, PI4_B, PI4_C, PI4_D;
//
//        PI4_A = 0.78515625f;
//        PI4_B = 0.00024187564849853515625f;
//        PI4_C = 3.7747668102383613586e-08f;
//        PI4_D = 1.2816720341285448015e-12f;
//
//
//        vreal q = vfmadd(2.0, vtrunc(vfmadd(a, M_1_PI, -0.5)), 1.0);
//        vint iq = q;
//
//#if !defined(COMPILE_FAST_FLOAT)
//        a = vfmadd(q, -PI4_A * 2, a);
//        a = vfmadd(q, -PI4_B * 2, a);
//        a = vfmadd(q, -PI4_C * 2, a);
//        a = vfmadd(q, -PI4_D * 2, a);
//#else
//        a = vfmadd(q, -M_PI_2, a);
//#endif
//
//        vreal s = a * a;
//
//        a = vsel(iq & 2, a, -a);
//
//        vreal u = 2.6083159809786593541503e-06f;
//        u       = vfmadd(u, s, -0.0001981069071916863322258f);
//        u       = vfmadd(u, s, 0.00833307858556509017944336f);
//        u       = vfmadd(u, s, -0.166666597127914428710938f);
//
//        u = vfmadd(s, u * a, a);
//
//        u = vsel(visinf(a), ccl<vreal>::ones(), u);
//
//        return u;
//    }
//
//    VECTORIZED_F inline vreal vtan(const vreal a)
//    {
//        return 0;
//    }
//
//    VECTORIZED_F inline vreal vasin(const vreal a)
//    {
//        return 0;
//    }
//
//    VECTORIZED_F inline vreal vacos(const vreal a)
//    {
//        return 0;
//    }
//
//    VECTORIZED_F inline vreal vatan(const vreal a)
//    {
//        return 0;
//    }
//}}}