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

/// @see https://stackoverflow.com/a/22291538/1261537
#if defined(_MSC_VER)
/* Microsoft C/C++-compatible compiler */
#include <intrin.h>
#include <smmintrin.h>
#elif (defined(__GNUC__)) && (defined(__x86_64__) || defined(__i386__))
/* GCC-compatible compiler, targeting x86/x86-64 */
#include <x86intrin.h>
#elif defined(__GNUC__) && defined(__ARM_NEON__)
/* GCC-compatible compiler, targeting ARM with NEON */
#include <arm_neon.h>
#elif defined(__GNUC__) && defined(__IWMMXT__)
/* GCC-compatible compiler, targeting ARM with WMMX */
#include <mmintrin.h>
#elif (defined(__GNUC__) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
/* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
#include <altivec.h>
#elif defined(__GNUC__) && defined(__SPE__)
/* GCC-compatible compiler, targeting PowerPC with SPE */
#include <spe.h>
#endif

#if defined(__clang__)

#elif defined(__GNUC__) || defined(__GNUG__)

#if defined(ZACC_AVX) || defined(ZACC_AVX2)
inline __m256 _mm256_set_m128(__m128 hi, __m128 lo)
{
	return _mm256_insertf128_ps(_mm256_castps128_ps256(hi), (lo), 1);
}


inline __m256 _mm256_set_m128d(__m128 hi, __m128 lo)
{
	return _mm256_insertf128_pd(_mm256_castpd128_pd256(hi), (lo), 1);
}
#endif

#elif defined(_MSC_VER)

#endif

#if !defined(_MSC_VER) && (defined(ZACC_AVX) || defined(ZACC_AVX2))

inline bool _mm256_test_all_ones(__m256 val)
{
	auto ival = _mm256_castps_si256(val);
	return _mm256_testc_si256(ival, _mm256_cmpeq_epi32(ival, ival));
}

inline bool _mm256_test_all_ones(__m256i val)
{
	return _mm256_testc_si256(val, _mm256_cmpeq_epi32(val, val));
}

#endif