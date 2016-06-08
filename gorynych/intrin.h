//
// Created by szuyev on 10.05.16.
//

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

