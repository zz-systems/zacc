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

#include "generated/float32.gen.hpp"

namespace zacc {
    namespace sse {

        struct __zfloat32 : public zval<__m128, float, 4, 16> {
            __zfloat32(__m128 value)
                    : zval(value) {}

            __zfloat32(__m128d value)
                    : zval(_mm_cvtpd_ps(value)) {}

            __zfloat32(__m128i value)
                    : zval(_mm_cvtepi32_ps(value)) {}

            __zfloat32(float value)
                    : zval(_mm_set1_ps(value)) {}

            __zfloat32(float *value)
                    : zval(_mm_load_ps(value)) {}

            __zfloat32(float a, float b, float c, float d)
                    : zval(_mm_set_ps(d, c, b, a)) {}
        };


        struct zfloat32;

        struct zfloat32 : public compose<
                printable,
                iteratable,
                extractable,


                gen_float32::arithmetic<zfloat32>::impl,
                gen_float32::io<zfloat32>::impl,
                gen_float32::conditional<zfloat32>::impl,
                gen_float32::logical<zfloat32>::impl,
                gen_float32::comparison<zfloat32>::impl,
                gen_float32::bitwise<zfloat32>::impl,

                composable<__zfloat32>::template type> {
            FORWARD2(zfloat32, compose);
        };
    }
}