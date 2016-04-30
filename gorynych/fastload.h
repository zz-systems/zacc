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

// Theoretically constant generation (up to a sane limit) instead of loading from memory is faster.
// This is yet to be tested / benchmarked.

#include "dependencies.h"
#include "gorynych.h"

namespace zzsystems { namespace gorynych
{	
	
	// Shorcut for "constant" declaration
#define CONSTDEF(TType, name, body) static TType name() { return static_cast<TType>(body); }

	ANY(TType)
	struct consts
	{
		CONSTDEF(TType, pi,		3.14159265358979323846);
		CONSTDEF(TType, deg2rad, 0.01745329251994329577);
		CONSTDEF(TType, sqrt3,	1.73205080756887729353);
	};

	ANY(TType)
	struct cfl
	{
		CONSTDEF(TType, ones,	-1);
		CONSTDEF(TType, intmin, numeric_limits<int>::min());
		CONSTDEF(TType, intmax, numeric_limits<int>::max());

		CONSTDEF(TType, _0, 0);	
		CONSTDEF(TType, _1, 1);
		CONSTDEF(TType, _2, 2);
		CONSTDEF(TType, _3, 3);
		CONSTDEF(TType, _4, 4);
		CONSTDEF(TType, _5, 5);
		CONSTDEF(TType, _6, 6);
		CONSTDEF(TType, _7, 7);
		CONSTDEF(TType, _8, 8);
		CONSTDEF(TType, _9, 9);
		CONSTDEF(TType, _10, 10);
		CONSTDEF(TType, _11, 11);
		CONSTDEF(TType, _12, 12);
		CONSTDEF(TType, _13, 13);
		CONSTDEF(TType, _14, 14);
		CONSTDEF(TType, _15, 15);

		CONSTDEF(TType, sign1all0, numeric_limits<int>::min());
		CONSTDEF(TType, sign0all1, numeric_limits<int>::max());
	};	

	template <>
	inline float cfl<float>::ones()
	{
		return numeric_limits<float>::quiet_NaN();
	}

	FEATURE
	struct cfl<_int4>
	{
		CONSTDEF(_int4, _0, _mm_setzero_si128());
		CONSTDEF(_int4, ones, _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128()));
		CONSTDEF(_int4, intmin, -(ones >> 1));
		CONSTDEF(_int4, intmax, ones() >> 1);

		CONSTDEF(_int4, _1, ones() >> 31);
		CONSTDEF(_int4, _2, ones() >> 31 << 1);
		CONSTDEF(_int4, _3, ones() >> 30);
		CONSTDEF(_int4, _4, ones() >> 31 << 2);
		CONSTDEF(_int4, _5, _4() + _1());
		CONSTDEF(_int4, _6, ones() >> 30 << 1);
		CONSTDEF(_int4, _7, ones() >> 29);
		CONSTDEF(_int4, _8, ones() >> 31 << 3);

		CONSTDEF(_int4, _9, _8() + _1());
		CONSTDEF(_int4, _10, _8() + _2());
		CONSTDEF(_int4, _11, _8() + _3());
		CONSTDEF(_int4, _12, _8() + _4());
		CONSTDEF(_int4, _13, _8() + _5());
		CONSTDEF(_int4, _14, _8() + _6());
		CONSTDEF(_int4, _15, ones() >> 28);

		CONSTDEF(_int4, sign1all0, ones() << 31);
		CONSTDEF(_int4, sign0all1, ones() >> 1);
	};

	FEATURE
	struct cfl<_float4>
	{
		CONSTDEF(_float4, _0, cfl<_int4>::_0());
		CONSTDEF(_float4, ones, _mm_castsi128_ps(cfl<_int4>::ones().val));

		CONSTDEF(_float4,  intmin, -(ones() >> 1));
		CONSTDEF(_float4,  intmax, ones() >> 1);

		CONSTDEF(_float4, _1, cfl<_int4>::_1());
		CONSTDEF(_float4, _2, cfl<_int4>::_2());
		CONSTDEF(_float4, _3, cfl<_int4>::_3());
		CONSTDEF(_float4, _4, cfl<_int4>::_4());
		CONSTDEF(_float4, _5, cfl<_int4>::_5());
		CONSTDEF(_float4, _6, cfl<_int4>::_6());
		CONSTDEF(_float4, _7, cfl<_int4>::_7());
		CONSTDEF(_float4, _8, cfl<_int4>::_8());

		CONSTDEF(_float4, _9,  cfl<_int4>::_9());
		CONSTDEF(_float4, _10, cfl<_int4>::_10());
		CONSTDEF(_float4, _11, cfl<_int4>::_11());
		CONSTDEF(_float4, _12, cfl<_int4>::_12());
		CONSTDEF(_float4, _13, cfl<_int4>::_13());
		CONSTDEF(_float4, _14, cfl<_int4>::_14());
		CONSTDEF(_float4, _15, cfl<_int4>::_15());

		CONSTDEF(_float4, sign1all0, _mm_castsi128_ps(cfl<_int4>::sign1all0().val));
		CONSTDEF(_float4, sign0all1, _mm_castsi128_ps(cfl<_int4>::sign0all1().val));
	};

	FEATURE
	struct cfl<_int8>
	{
		CONSTDEF(_int8, _0, _mm256_setzero_si256());
		CONSTDEF(_int8, ones, _mm256_cmpeq_epi32(_mm256_setzero_si256(), _mm256_setzero_si256()));
		CONSTDEF(_int8, intmin, -(ones() >> 1));
		CONSTDEF(_int8, intmax, ones() >> 1);

		CONSTDEF(_int8, _1, ones() >> 31);
		CONSTDEF(_int8, _2, ones() >> 31 << 1);
		CONSTDEF(_int8, _3, ones() >> 30);
		CONSTDEF(_int8, _4, ones() >> 31 << 2);
		CONSTDEF(_int8, _5, _4() + _1());
		CONSTDEF(_int8, _6, ones() >> 30 << 1);
		CONSTDEF(_int8, _7, ones() >> 29);
		CONSTDEF(_int8, _8, ones() >> 31 << 3);

		CONSTDEF(_int8, _9, _8() + _1());
		CONSTDEF(_int8, _10, _8() + _2());
		CONSTDEF(_int8, _11, _8() + _3());
		CONSTDEF(_int8, _12, _8() + _4());
		CONSTDEF(_int8, _13, _8() + _5());
		CONSTDEF(_int8, _14, _8() + _6());
		CONSTDEF(_int8, _15, ones() >> 28);

		CONSTDEF(_int8, sign1all0, ones() << 31);
		CONSTDEF(_int8, sign0all1, ones() >> 1);
	};

	FEATURE
	struct cfl<_int4x2>
	{
		CONSTDEF(_int4x2, _0, _int4x2(_mm_setzero_si128(), _mm_setzero_si128()));
		CONSTDEF(_int4x2, ones, _int4x2(_mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128()), _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128())));
		CONSTDEF(_int4x2, intmin, -(ones() >> 1));
		CONSTDEF(_int4x2, intmax, ones() >> 1);

		CONSTDEF(_int4x2, _1, ones() >> 31);
		CONSTDEF(_int4x2, _2, ones() >> 31 << 1);
		CONSTDEF(_int4x2, _3, ones() >> 30);
		CONSTDEF(_int4x2, _4, ones() >> 31 << 2);
		CONSTDEF(_int4x2, _5, _4() + _1());
		CONSTDEF(_int4x2, _6, ones() >> 30 << 1);
		CONSTDEF(_int4x2, _7, ones() >> 29);
		CONSTDEF(_int4x2, _8, ones() >> 31 << 3);

		CONSTDEF(_int4x2, _9, _8() + _1());
		CONSTDEF(_int4x2, _10, _8() + _2());
		CONSTDEF(_int4x2, _11, _8() + _3());
		CONSTDEF(_int4x2, _12, _8() + _4());
		CONSTDEF(_int4x2, _13, _8() + _5());
		CONSTDEF(_int4x2, _14, _8() + _6());
		CONSTDEF(_int4x2, _15, ones() >> 28);

		CONSTDEF(_int4x2, sign1all0, ones() << 31);
		CONSTDEF(_int4x2, sign0all1, ones() >> 1);
	};

	template<>
	//struct cfl<enable_if_t<_dispatcher::has_avx && _dispatcher::has_avx2, _float8>>
	struct cfl<float8<capability_AVX2>>
	{
		using featuremask = capability_AVX2;

		CONSTDEF(_float8, _0, cfl<_int8>::_0());
		CONSTDEF(_float8, ones, _mm256_castsi256_ps(cfl<_int8>::ones().val));

		CONSTDEF(_float8,  intmin, _mm256_castsi256_ps((-(cfl<_int8>::ones() >> 1)).val));
		CONSTDEF(_float8,  intmax, _mm256_castsi256_ps((cfl<_int8>::ones() >> 1).val));

		CONSTDEF(_float8, _1, cfl<_int8>::_1());
		CONSTDEF(_float8, _2, cfl<_int8>::_2());
		CONSTDEF(_float8, _3, cfl<_int8>::_3());
		CONSTDEF(_float8, _4, cfl<_int8>::_4());
		CONSTDEF(_float8, _5, cfl<_int8>::_5());
		CONSTDEF(_float8, _6, cfl<_int8>::_6());
		CONSTDEF(_float8, _7, cfl<_int8>::_7());
		CONSTDEF(_float8, _8, cfl<_int8>::_8());

		CONSTDEF(_float8, _9, cfl<_int8>::_9());
		CONSTDEF(_float8, _10, cfl<_int8>::_10());
		CONSTDEF(_float8, _11, cfl<_int8>::_11());
		CONSTDEF(_float8, _12, cfl<_int8>::_12());
		CONSTDEF(_float8, _13, cfl<_int8>::_13());
		CONSTDEF(_float8, _14, cfl<_int8>::_14());
		CONSTDEF(_float8, _15, cfl<_int8>::_15());

		CONSTDEF(_float8, sign1all0, _mm256_castsi256_ps(cfl<_int8>::sign1all0().val));
		CONSTDEF(_float8, sign0all1, _mm256_castsi256_ps(cfl<_int8>::sign0all1().val));
	};

	template<>
	//struct cfl<enable_if_t<_dispatcher::has_avx && !_dispatcher::has_avx2, _float8>>
	struct cfl<float8<capability_AVX1>>
	{
		using featuremask = capability_AVX1;

		CONSTDEF(_float8, _0, cfl<_int4x2>::_0());
		CONSTDEF(_float8, ones, _float8(cfl<_int4x2>::ones()));

		CONSTDEF(_float8,  intmin, _float8(-(cfl<_int4x2>::ones() >> 1)));
		CONSTDEF(_float8,  intmax, _float8(cfl<_int4x2>::ones() >> 1));

		CONSTDEF(_float8, _1, cfl<_int4x2>::_1());
		CONSTDEF(_float8, _2, cfl<_int4x2>::_2());
		CONSTDEF(_float8, _3, cfl<_int4x2>::_3());
		CONSTDEF(_float8, _4, cfl<_int4x2>::_4());
		CONSTDEF(_float8, _5, cfl<_int4x2>::_5());
		CONSTDEF(_float8, _6, cfl<_int4x2>::_6());
		CONSTDEF(_float8, _7, cfl<_int4x2>::_7());
		CONSTDEF(_float8, _8, cfl<_int4x2>::_8());

		CONSTDEF(_float8, _9, cfl<_int4x2>::_9());
		CONSTDEF(_float8, _10, cfl<_int4x2>::_10());
		CONSTDEF(_float8, _11, cfl<_int4x2>::_11());
		CONSTDEF(_float8, _12, cfl<_int4x2>::_12());
		CONSTDEF(_float8, _13, cfl<_int4x2>::_13());
		CONSTDEF(_float8, _14, cfl<_int4x2>::_14());
		CONSTDEF(_float8, _15, cfl<_int4x2>::_15());

		CONSTDEF(_float8, sign1all0, _float8(cfl<_int4x2>::sign1all0()));
		CONSTDEF(_float8, sign0all1, _float8(cfl<_int4x2>::sign0all1()));
	};


#define FLR cfl<vreal>
#define FLI cfl<vint>

}}