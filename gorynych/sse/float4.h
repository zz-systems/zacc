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
	FEATURE
	struct int4;

	
	//struct double2;
#define _float4 float4<featuremask> 
#define _int4 int4<featuremask>

	FEATURE
	struct ALIGN(16) float4 {
		__m128 val;		

		float4() = default;
		
		float4(const int rhs)		: val(_mm_set1_ps(static_cast<float>(rhs))) {}
		float4(const float rhs)		: val(_mm_set1_ps(rhs)) {}
		float4(const double rhs)	: val(_mm_set1_ps(static_cast<float>(rhs))) {}

		float4(const float* rhs)	: val(_mm_load_ps(rhs)) {}

		float4(VARGS4(uint8_t))		: val(_mm_cvtepi32_ps(_mm_set_epi32(VPASS4))) {}
		float4(VARGS4(int32_t))		: val(_mm_cvtepi32_ps(_mm_set_epi32(VPASS4))) {}
		float4(VARGS4(float))		: val(_mm_set_ps(VPASS4)) {}

		float4(const __m128& rhs)	: val(rhs) { }
		float4(const __m128i& rhs)	: val(_mm_cvtepi32_ps(rhs)) {}
		float4(const __m128d& rhs)	: val(_mm_cvtpd_ps(rhs)) {}

		float4(const _float4& rhs);
		float4(const _int4&	rhs);
		//float4(const double2&	rhs);


		BIN_OP_STUB(+, _float4, float)
		BIN_OP_STUB(-, _float4, float)
		BIN_OP_STUB(*, _float4, float)
		BIN_OP_STUB(/ , _float4, float)		

		BIN_OP_STUB(&, _float4, float)
		BIN_OP_STUB(&&, _float4, float)
		BIN_OP_STUB(|, _float4, float)
		BIN_OP_STUB(||, _float4, float)
		BIN_OP_STUB(^, _float4, float)

		BIN_OP_STUB(>, _float4, float)
		BIN_OP_STUB(<, _float4, float)
		BIN_OP_STUB(== , _float4, float)

		//template<enable_if_t<HAS_SSE, bool>>
		explicit inline operator bool()
		{
			return _mm_test_all_ones(_mm_castps_si128(this->val)) != 0;
		}

		static inline auto ones()
		{
			auto t = _mm_setzero_si128();
			return _mm_cmpeq_epi32(t, t);
		}

		static inline auto one()
		{
			return _mm_srli_epi32(ones(), 31);
		}

		static inline auto sign1all0()
		{
			return _mm_slli_epi32(ones(), 31);
		}

		static inline auto sign0all1()
		{
			return _mm_srli_epi32(ones(), 1);
		}
	};
	
	

	// Arithmetic =====================================================================================================
	
	// Add
	FEATURE_BIN_OP(+, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_add_ps);
	}	
	// Sub
	FEATURE_BIN_OP(-, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_sub_ps);
	}
	// Mul
	FEATURE_BIN_OP(*, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_mul_ps);
	}

	// division
	FEATURE_BIN_OP(/, _float4, HAS_SSE && !USE_FAST_FLOAT)
	{
		{ BIN_BODY(_mm_div_ps); }	
	}

	// Fast division (lower precision!)
	FEATURE_BIN_OP(/ , _float4, HAS_SSE && USE_FAST_FLOAT)
	{
		BODY(_mm_mul_ps(a.val, _mm_rcp_ps(b.val)));
	}

	// Negate 
	FEATURE_UN_OP(-, _float4, HAS_SSE)
	{
		BODY(_mm_xor_ps(a.val, _mm_castsi128_ps(_float4::sign1all0())));
	}

	// Comparison =====================================================================================================	
	// Greater than
	FEATURE_BIN_OP(>, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpgt_ps);
	}
	// Less than
	FEATURE_BIN_OP(<, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_cmplt_ps);
	}
	//SIMD_FEATURE(_float4::has_sse)
	FEATURE_BIN_OP(==, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpeq_ps);
	}
	
	// Bitwise ========================================================================================================
	// Bitwise NOT
	FEATURE_UN_OP(~, _float4, HAS_SSE)
	{		
		BODY(_mm_xor_ps(a.val, _mm_castsi128_ps(_float4::ones())));
	}
	
	FEATURE_UN_OP(!, _float4, HAS_SSE)
	{
		BODY(~a);
	}

	// Bitwise AND
	FEATURE_BIN_OP(&, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_and_ps);
	}

	// Bitwise OR
	FEATURE_BIN_OP(|, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_or_ps);
	}

	// Bitwise AND
	FEATURE_BIN_OP(&&, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_and_ps);
	}

	// Bitwise OR
	FEATURE_BIN_OP(|| , _float4, HAS_SSE)
	{
		BIN_BODY(_mm_or_ps);
	}

	// Bitwise XOR
	FEATURE_BIN_OP(^, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_xor_ps);
	}
	
	// Special functions ==============================================================================================
	// SSE > 4.1 Branchless select
	FEATURE_TRI_FUNC(vsel, _float4, HAS_SSE41)
	{
		TRI_BODY_R(_mm_blendv_ps);
	}

	// SSE < 4.1 branchless select
	FEATURE_TRI_FUNC(vsel, _float4, !HAS_SSE41 && HAS_SSE)
	{
		BODY(a /* mask */ & b | ~a & c);
	}

	// Fused multiply-add
	FEATURE_TRI_FUNC(vfmadd, _float4, HAS_FMA)
	{
		TRI_BODY(_mm_fmadd_ps);
	}
	// Fused multipl-subtract
	FEATURE_TRI_FUNC(vfmsub, _float4, HAS_FMA)
	{
		TRI_BODY(_mm_fmsub_ps);
	}

	// Mathematical functions =========================================================================================
	// Absolute value
	FEATURE_UN_FUNC(vabs, _float4, HAS_SSE)
	{
		// According to IEEE 754 standard: sign bit is the first bit => set to 0
		BODY(_mm_and_ps(a.val, _mm_castsi128_ps(_float4::sign0all1())));
	}

	// Minimum value
	FEATURE_BIN_FUNC(vmin, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_min_ps);
	}

	// Maximum
	FEATURE_BIN_FUNC(vmax, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_max_ps);
	}

	// Normal square root
	FEATURE_UN_FUNC(vsqrt, _float4, HAS_SSE && !USE_FAST_FLOAT)
	{
		UN_BODY(_mm_sqrt_ps);
	}

	// Fast square root (lower precision!)
	FEATURE_UN_FUNC(vsqrt, _float4, HAS_SSE && USE_FAST_FLOAT)
	{
		BODY(_mm_mul_ps(a.val, _mm_rsqrt_ps(a.val)));
	}
		
	// Rounding =======================================================================================================

	// Truncate float to *.0
	FEATURE_UN_FUNC(vtrunc, _float4, HAS_SSE)
	{
		BODY(static_cast<_float4>(static_cast<_int4>(a)));
	}

	// Floor value
	FEATURE_UN_FUNC(vfloor, _float4, HAS_SSE41)
	{
		BODY(_mm_round_ps(a.val, _MM_FROUND_FLOOR));
	}

	// Ceil value
	FEATURE_UN_FUNC(vceil, _float4, HAS_SSE41)
	{
		BODY(_mm_round_ps(a.val, _MM_FROUND_CEIL));
	}

	// Round value
	FEATURE_UN_FUNC(vround, _float4, HAS_SSE41)
	{
		BODY(_mm_round_ps(a.val, _MM_FROUND_TO_NEAREST_INT));
	}

	// Floor value
	FEATURE_UN_FUNC(vfloor, _float4, !HAS_SSE41 && HAS_SSE)
	{
		auto fi = vtrunc(a);
		return vsel(fi > a, fi - static_cast<_float4>(_float4::one()), fi);
	}

	// Ceil value
	FEATURE_UN_FUNC(vceil, _float4, !HAS_SSE41 && HAS_SSE)
	{
		auto fi = vtrunc(a);
		return vsel(fi < a, fi + static_cast<_float4>(_float4::one()), fi);
	}

	// Round value
	FEATURE_UN_FUNC(vround, _float4, !HAS_SSE41 && HAS_SSE)
	{		
		//generate the highest value < 2		
		_float4 vNearest2 = _mm_srli_epi32(_float4::ones(), 2);
		auto aTrunc = vtrunc(a);

		auto rmd = a - aTrunc;        // get remainder
		auto rmd2 = rmd * vNearest2;  // mul remainder by near 2 will yield the needed offset

		auto rmd2Trunc = vtrunc(rmd2); // after being truncated of course

		return aTrunc + rmd2Trunc;
	}
}}