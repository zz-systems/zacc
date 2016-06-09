//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include <x86intrin.h>

// memory alignment
#if defined(_MSC_VER) && _MSC_VER < 1900
#define ALIGN(bytes) __declspec(align(bytes))
#else
#define ALIGN(bytes) alignas(bytes)
#endif


#ifdef _MSC_VER
#else

#define _mm256_set_m128(hi, lo) _mm256_insertf128_ps(_mm256_castps128_ps256(hi),(lo),1)

inline bool _mm256_test_all_ones(__m256 val)
{
    auto ival = _mm256_castps_si256(val);
    return _mm256_testc_si256(ival, _mm256_cmpeq_epi32(ival,ival));
}

inline bool _mm256_test_all_ones(__m256i val)
{
    return _mm256_testc_si256(val, _mm256_cmpeq_epi32(val,val));
}
#endif


#if defined(COMPILE_AVX2) || defined(COMPILE_AVX1)
    #define SIMD_ALIGN alignas(32)
#elif defined(COMPILE_SSE2) || defined(COMPILE_SSE3) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE4) || defined(COMPILE_SSE4FMA)
    #define SIMD_ALIGN alignas(16)
#else
    #define SIMD_ALIGN
#endif

