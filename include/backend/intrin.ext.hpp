#pragma once 

#if defined(__clang__)

#elif defined(__GNUC__) || defined(__GNUG__)

#if defined(ZACC_AVX) || defined(ZACC_AVX2)
inline __m256 _mm256_set_m128(__m128 hi, __m128 lo)
{
	return _mm256_insertf128_ps(_mm256_castps128_ps256(hi), (lo), 1);
}


inline __m256d _mm256_set_m128d(__m128d hi, __m128d lo)
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