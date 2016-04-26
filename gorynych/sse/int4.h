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

#include "../dependencies.h"

namespace zzsystems { namespace gorynych {

	//using namespace std;

	FEATURE
	struct float4;
	//struct double2;
#define _int4 int4<featuremask>
#define _float4 float4<featuremask>

	FEATURE
	struct ALIGN(16) int4 {
		__m128i val;

		int4() = default;
		int4(const int rhs)			: val(_mm_set1_epi32(rhs)) {}

		int4(const __m128& rhs)		: val(_mm_cvtps_epi32(rhs)) {}
		int4(const __m128i& rhs)	: val(rhs) {}
		int4(const __m128d& rhs)	: val(_mm_cvtpd_epi32(rhs)) {}

		int4(const _int4& rhs);
		int4(const _float4& rhs);
		//int4(const double2& rhs);

		BIN_OP_STUB(+, _int4, int)
		BIN_OP_STUB(-, _int4, int)
		BIN_OP_STUB(*, _int4, int)
		BIN_OP_STUB(/, _int4, int)

		BIN_OP_STUB(&, _int4, int)
		BIN_OP_STUB(&&, _int4, int)
		BIN_OP_STUB(|, _int4, int)
		BIN_OP_STUB(||, _int4, int)
		BIN_OP_STUB(^, _int4, int)
		

		BIN_OP_STUB(>, _int4, int)
		BIN_OP_STUB(<, _int4, int)
		BIN_OP_STUB(==, _int4, int)

		explicit inline operator bool()
		{
			return _mm_test_all_ones(this->val);
		}
	};		

	
	
	FEATURE_BIN_OP(+, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_add_epi32);
	}

	FEATURE_BIN_OP(-, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_sub_epi32);
	}

	FEATURE_BIN_OP(*, _int4, HAS_SSE41)
	{
		BIN_BODY(_mm_mullo_epi32);
	}
	
	FEATURE_BIN_OP(*, _int4, !HAS_SSE41 && HAS_SSE)
	{
		__m128i tmp1 = _mm_mul_epu32(a.val, b.val); /* mul 2,0*/
		__m128i tmp2 = _mm_mul_epu32(_mm_srli_si128(a.val, 4), _mm_srli_si128(b.val, 4)); /* mul 3,1 */
		return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE(0, 0, 2, 0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE(0, 0, 2, 0))); /* shuffle results to [63..0] and pack */	
	}

	// yet to implement
	
	
	FEATURE_BIN_OP(>, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpgt_epi32);
	}
	
	FEATURE_BIN_OP(<, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_cmplt_epi32);
	}

	
	FEATURE_BIN_OP(==, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpeq_epi32);
	}

	
	FEATURE_UN_OP(~, _int4, HAS_SSE)
	{
		BODY(_mm_xor_si128(a.val, _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128())));
	}
	FEATURE_UN_OP(!, _int4, HAS_SSE)
	{
		BODY(~a);
	}
	
	FEATURE_UN_OP(-, _int4, HAS_SSE)
	{
		BODY(_mm_sub_epi32(_mm_setzero_si128(), a.val));
	}

	
	FEATURE_BIN_OP(|, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_or_si128);
	}
	
	FEATURE_BIN_OP(&, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_and_si128);
	}

	FEATURE_BIN_OP(|| , _int4, HAS_SSE)
	{
		BIN_BODY(_mm_or_si128);
	}

	FEATURE_BIN_OP(&&, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_and_si128);
	}

	FEATURE_BIN_OP(^, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_xor_si128);
	}
	
	FEATURE_SHIFT_OP(>>, _int4, HAS_SSE)
	{
		return _mm_srli_epi32		(a.val, sa);
	}	
	
	FEATURE_SHIFT_OP(<<, _int4, HAS_SSE)
	{
		return _mm_slli_epi32(a.val, sa);
	}
		
	FEATURE_BIN_FUNC(vmin, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_min_epi32);
	}
	
	FEATURE_BIN_FUNC(vmax, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_max_epi32);
	}
	
	// SSE 4.1 branchless select
	FEATURE_TRI_FUNC(vsel, _int4, HAS_SSE41)
	{		
		TRI_BODY_R(_mm_blendv_epi8);
	}

	FEATURE_TRI_FUNC(vsel, _int4, HAS_SSE && !HAS_SSE41)
	{
		BODY(a /*mask */ & b | ~a & c);
	}
}}