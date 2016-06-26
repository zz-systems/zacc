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

/**
 * @file fastload.h
 *
 * @brief constant generation
 *
 * Theoretically constant generation (up to a sane limit) instead of loading from memory is faster.
 * This is yet to be tested / benchmarked.
 */

#include "dependencies.h"
#include "platform/dispatch.h"
#include "gorynych.h"

namespace zzsystems { namespace gorynych
{	
	
/// @def CONSTDEF(type, name, body)
/// @brief shorcut: "constant" declaration
#define CONSTDEF(type, name, body) static inline type name() { return static_cast<type>(body); }

	ANY(TType)
	struct consts
	{
		CONSTDEF(TType, pi,		3.14159265358979323846);
		CONSTDEF(TType, deg2rad, 0.01745329251994329577);
		CONSTDEF(TType, sqrt3,	1.73205080756887729353);
	};


		template<typename type>
		struct ccl
		{
			static inline type zeros() 			{ return 0x0; }
			static inline type ones() 			{ return 0xFFFFFFFF; }
			//static inline type min() 			{ return 0x80000000; }//*/{ return std::numeric_limits<int>::min(); }
			//static inline type max() 			{ return 0x7FFFFFFF; }//*/{ return std::numeric_limits<int>::max(); }

			//static inline type sign1all0() 		{ return 0x80000000; }
			//static inline type sign0all1() 		{ return 0x7FFFFFFF; }
		};

		template<> inline float ccl<float>::ones() 		{ return numeric_limits<float>::quiet_NaN(); }
		//template<> inline float ccl<float>::min() 		{ return -ccl<int>::min(); }

#if defined(COMPILE_SSE2) || defined(COMPILE_SSE3) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE4) || defined(COMPILE_SSE4FMA) || defined(COMPILE_AVX1)

	DISPATCHED
	struct ccl<_int4>
	{
		static inline _int4 zeros()			{ return _mm_setzero_si128();}
		static inline _int4 ones() 			{ return _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128()); }
		//static inline _int4 min() 			{ return ones() << 31; }
		//static inline _int4 max() 			{ return ones() >> 1;}
		//static inline _int4 sign1all0() 	{ return ones() << 31;}
		//static inline _int4 sign0all1() 	{ return ones() >> 1; }
	};

	DISPATCHED
	struct ccl<_float4>
	{
		static inline _float4 zeros()		{ return _mm_setzero_ps();}
		static inline _float4 ones() 		{ return _mm_cmpeq_ps(_mm_setzero_ps(), _mm_setzero_ps()); }// _mm_castsi128_ps(_mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128())); }
		//static inline _float4 min() 		{ return -(ccl<_int4>::min()); }
		//static inline _float4 max() 		{ return (ccl<_int4>::max()); }
		//static inline _float4 sign1all0() 	{ return _mm_castsi128_ps(ccl<_int4>::sign1all0().val);}
		//static inline _float4 sign0all1() 	{ return _mm_castsi128_ps(ccl<_int4>::sign0all1().val); }
	};
#endif
#if defined(COMPILE_AVX2)

	DISPATCHED
	struct ccl<_int8>
	{
		static inline _int8 zeros()			{ return _mm256_setzero_si256();}
		static inline _int8 ones() 			{ return _mm256_cmpeq_epi32(_mm256_setzero_si256(), _mm256_setzero_si256()); }
		//static inline _int8 min() 			{ return ones() << 31; }
		//static inline _int8 max() 			{ return ones() >> 1;}
		//static inline _int8 sign1all0() 	{ return ones() << 31;}
		//static inline _int8 sign0all1() 	{ return ones() >> 1; }
	};

	DISPATCHED
	struct ccl<_float8>
	{
		static inline _float8 zeros()		{ return _mm256_setzero_ps();}
		static inline _float8 ones() 		{ return _mm256_castsi256_ps(_mm256_cmpeq_epi32(_mm256_setzero_si256(), _mm256_setzero_si256())); }
		//static inline _float8 min() 		{ return -(ccl<_int8>::min()); }
		//static inline _float8 max() 		{ return (ccl<_int8>::max()); }
		//static inline _float8 sign1all0() 	{ return _mm256_castsi256_ps(ccl<_int8>::sign1all0().val);}
		//static inline _float8 sign0all1() 	{ return _mm256_castsi256_ps(ccl<_int8>::sign0all1().val); }
	};
#elif defined(COMPILE_AVX1)
	DISPATCHED
	struct ccl<_int4x2>
	{
		static inline _int4x2 zeros()		{ return {_mm_setzero_si128(), _mm_setzero_si128()};}
		static inline _int4x2 ones() 		{ return { _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128()), _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128())}; }
		static inline _int4x2 min() 		{ return ones() << 31; }
		static inline _int4x2 max() 		{ return ones() >> 1;}
		//static inline _int4x2 sign1all0() 	{ return ones() << 31;}
		//static inline _int4x2 sign0all1() 	{ return ones() >> 1; }
	};

	DISPATCHED
	struct ccl<_float8>
	{
		static inline _float8 zeros()		{ return _mm256_setzero_ps();}
		static inline _float8 ones() 		{ return _mm256_cmp_ps(_mm256_setzero_ps(), _mm256_setzero_ps(), _CMP_EQ_OQ); }
		static inline _float8 min() 		{ return -ccl<_int4x2>::min(); }
		static inline _float8 max() 		{ return ccl<_int4x2>::max(); }
		//static inline _float8 sign1all0() 	{ return _mm256_castsi256_ps(_mm256_set_m128i(ccl<_int4>::sign1all0().val, ccl<_int4>::zeros().val));}
		//static inline _float8 sign0all1() 	{ return _mm256_castsi256_ps(_mm256_set_m128i(ccl<_int4>::sign0all1().val, ccl<_int4>::ones().val)); }
	};
#endif

//#if defined(COMPILE_SSE2) || defined(COMPILE_SSE3) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE4) || defined(COMPILE_SSE4FMA) || defined(COMPILE_AVX1) || defined(COMPILE_AVX2)

template<typename type, int value>
struct cfl : ccl<type>
{
	static inline type val() { return value; }
};


#define CFL_TYPE(capability) static_dispatcher<capability>::vint
#define CFL_SPECIALIZATION(capability, for_value)\
        template<> inline CFL_TYPE(capability) cfl<CFL_TYPE(capability), for_value>::val()

#define CFL_SPECIALIZATIONS(capability) \
	CFL_SPECIALIZATION(capability, -1) 	{ return ccl<CFL_TYPE(capability)>::ones(); } \
	CFL_SPECIALIZATION(capability, 0) 	{ return ccl<CFL_TYPE(capability)>::zeros(); } \
	/*CFL_SPECIALIZATION(capability, 1) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 31; }*/ \
	/*CFL_SPECIALIZATION(capability, 2) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 31 << 1; } */\
	/*CFL_SPECIALIZATION(capability, 3) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 30; } */\
	/*CFL_SPECIALIZATION(capability, 4) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 31 << 2; } */\
	/*CFL_SPECIALIZATION(capability, 5) 	{ return cfl<CFL_TYPE(capability), 1>::val() + cfl<CFL_TYPE(capability), 4>::val(); } */\
	/*CFL_SPECIALIZATION(capability, 6) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 30 << 1; } */\
	/*CFL_SPECIALIZATION(capability, 7) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 29; } */\
	/*CFL_SPECIALIZATION(capability, 8) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 31 << 3; } */\
	/*CFL_SPECIALIZATION(capability, 9) 	{ return cfl<CFL_TYPE(capability), 8>::val() + cfl<CFL_TYPE(capability), 1>::val(); } */ \
	/*CFL_SPECIALIZATION(capability, 10) 	{ return cfl<CFL_TYPE(capability), 7>::val() + cfl<CFL_TYPE(capability), 3>::val(); } */ \
	/*CFL_SPECIALIZATION(capability, 11) 	{ return cfl<CFL_TYPE(capability), 7>::val() + cfl<CFL_TYPE(capability), 4>::val(); } */\
	/*CFL_SPECIALIZATION(capability, 12) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 30 << 2; } */\
	/*CFL_SPECIALIZATION(capability, 13) 	{ return cfl<CFL_TYPE(capability), 7>::val() + cfl<CFL_TYPE(capability), 6>::val(); } */\
	/*CFL_SPECIALIZATION(capability, 14) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 29 << 1; } */\
	/*CFL_SPECIALIZATION(capability, 15) 	{ return cfl<CFL_TYPE(capability), 7>::val() + cfl<CFL_TYPE(capability), 8>::val(); }*/\
	/*CFL_SPECIALIZATION(capability, 0xFF) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 24; } */\
	/*CFL_SPECIALIZATION(capability, 0x7FFFFFFF) 	{ return ccl<CFL_TYPE(capability)>::ones() >> 1; }*/ \
	template<int value> \
	struct cfl<static_dispatcher<capability>::vreal, value> \
	{ \
		static inline static_dispatcher<capability>::vreal val() 	{ return cfl<static_dispatcher<capability>::vint, value>::val(); } \
	}

#if !defined(COMPILE_FPU)
#define BRANCH_DEF(branch) CFL_SPECIALIZATIONS(capability_##branch);
	STATIC_DISPATCH_ONE_RAW()
#undef BRANCH_DEF
#endif

#define FLR cfl<vreal>
#define FLI cfl<vint>

}}