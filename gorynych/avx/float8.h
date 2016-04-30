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
	struct int8;
	//struct double4;

#define _float8 float8<featuremask>
#define _int8 int8<featuremask>

	FEATURE
	struct ALIGN(32) float8 {
		__m256 val;

		float8() = default;

		float8(const int rhs)		: val(_mm256_set1_ps(static_cast<float>(rhs))) {}
		float8(const float rhs)		: val(_mm256_set1_ps(rhs)) {}
		float8(const double rhs)	: val(_mm256_set1_ps(static_cast<float>(rhs))) {}

		float8(const float* rhs)	: val(_mm256_load_ps(rhs)) {}

		float8(VARGS8(uint8_t))		: val(_mm256_cvtepi32_ps(_mm256_set_epi32(VPASS8))) {}
		float8(VARGS8(int32_t))		: val(_mm256_cvtepi32_ps(_mm256_set_epi32(VPASS8))) {}
		float8(VARGS8(float))		: val(_mm256_set_ps(VPASS8)) {}

		float8(const __m256& rhs)	: val(rhs) {}
		float8(const __m256i& rhs)	: val(_mm256_cvtepi32_ps(rhs)) {}
		float8(const __m256d& rhs)	: val(_mm256_castps128_ps256(_mm256_cvtpd_ps(rhs))) {}

		float8(const _float8&	rhs);
		float8(const _int8&	rhs);
		float8(const _int4x2& rhs);
		//float8(const double4&	rhs);

		BIN_OP_STUB(+, _float8, float)
		BIN_OP_STUB(-, _float8, float)
		BIN_OP_STUB(*, _float8, float)
		BIN_OP_STUB(/ , _float8, float)

		BIN_OP_STUB(&, _float8, float)
		BIN_OP_STUB(&&, _float8, float)
		BIN_OP_STUB(| , _float8, float)
		BIN_OP_STUB(|| , _float8, float)
		BIN_OP_STUB(^, _float8, float)

		BIN_OP_STUB(> , _float8, float)
		BIN_OP_STUB(< , _float8, float)
		BIN_OP_STUB(== , _float8, float)


		// Return true if all bits are set to 1
		explicit operator bool()
		{
			return _mm256_test_all_ones(_mm256_castps_si256(this->val)) != 0;
		}

		// Generate value with all bits set to 1
		static auto ones()
		{
			auto t = _mm256_setzero_si256();
			return _mm256_cmpeq_epi32(t, t);
		}

		// Generate 1
		static auto one()
		{
			return _mm256_srli_epi32(ones(), 31);
		}

		// Generate sign bit
		static auto sign1all0()
		{
			return _mm256_slli_epi32(ones(), 31);
		}

		// Generate ones mask with sign bit zeroed out
		static auto sign0all1()
		{
			return _mm256_srli_epi32(ones(), 1);
		}
	};	

	// Arithmetic =====================================================================================================
	// Add
	FEATURE_BIN_OP(+, _float8, HAS_AVX1)	
	{
		BIN_BODY(_mm256_add_ps); 
	}

	// Subtract
	FEATURE_BIN_OP(-, _float8, HAS_AVX1)	
	{
		BIN_BODY(_mm256_sub_ps);
	}

	// Multiplication
	FEATURE_BIN_OP(*, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_mul_ps); 
	}

	// Division
	FEATURE_BIN_OP(/, _float8, HAS_AVX1)	
	{
		BIN_BODY(_mm256_div_ps);
	}

	// Arithmetical negation
	FEATURE_UN_OP(-, _float8, HAS_AVX1)
	{
		BODY(_mm256_sub_ps(_mm256_setzero_ps(), a.val)); 
	}

	// Comparison =====================================================================================================
	
	// Greater than
	FEATURE_BIN_OP(>, _float8, HAS_AVX1)	
	{
		TRI_BODY_O(_mm256_cmp_ps, _CMP_GT_OQ); 
	}

	// Less than
	FEATURE_BIN_OP(< , _float8, HAS_AVX1) 
	{
		TRI_BODY_O(_mm256_cmp_ps, _CMP_LT_OQ); 
	}

	// Equal
	FEATURE_BIN_OP(==, _float8, HAS_AVX1)
	{
		TRI_BODY_O(_mm256_cmp_ps, _CMP_EQ_OQ); 
	}

	// Bitwise ========================================================================================================

	// Xor
	FEATURE_BIN_OP(^, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_xor_ps);
	}

	// Bitwise not
	FEATURE_UN_OP(~, _float8, HAS_AVX1)	
	{
		BODY(a ^ _float8(_float8::ones()));
	}

	// Bitwise or
	FEATURE_BIN_OP(|, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_or_ps); 
	}

	// Bitwise and
	FEATURE_BIN_OP(&, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_and_ps);
	}

	// Alias for bitwise not (used with scalar branch)
	FEATURE_UN_OP(!, _float8, HAS_AVX1)
	{
		BODY(~a);
	}

	// Alias for bitwise or (used with scalar branch)
	FEATURE_BIN_OP(|| , _float8, HAS_AVX1)
	{
		BODY(a | b);
	}

	// Alias for bitwise and (used with scalar branch)
	FEATURE_BIN_OP(&&, _float8, HAS_AVX1)
	{
		BODY(a & b);
	}	
	
	// Special functions ==============================================================================================
	// Branchless select
	FEATURE_TRI_FUNC(vsel, _float8, HAS_AVX1) 
	{		
		TRI_BODY_R(_mm256_blendv_ps); 
	}
	// Fused multiply-add
	FEATURE_TRI_FUNC(vfmadd, _float8, HAS_AVX1) 
	{
		TRI_BODY(_mm256_fmadd_ps); 
	}

	// Fused multiply-subtract
	FEATURE_TRI_FUNC(vfmsub, _float8, HAS_AVX1) 
	{
		TRI_BODY(_mm256_fmsub_ps); 
	}

	// Mathematical functions =========================================================================================
	// Absolute value
	FEATURE_UN_FUNC(vabs, _float8, HAS_AVX1)  
	{
		BODY(_mm256_and_ps(a.val, _mm256_castsi256_ps(_float8::sign0all1())));
	}
	
	// Min value
	FEATURE_BIN_FUNC(vmin, _float8, HAS_AVX1)  
	{
		BIN_BODY(_mm256_min_ps); 
	}

	// Max value
	FEATURE_BIN_FUNC(vmax, _float8, HAS_AVX1) 
	{
		BIN_BODY(_mm256_max_ps);
	}

	// Normal square root
	FEATURE_UN_FUNC(vsqrt, _float8, HAS_AVX1 && !USE_FAST_FLOAT)
	{
		UN_BODY(_mm256_sqrt_ps); 
	}

	// Approximated square root (faster)
	FEATURE_UN_FUNC(vsqrt, _float8, HAS_AVX1 && USE_FAST_FLOAT)
	{
		BODY(_mm256_mul_ps(a.val, _mm256_rsqrt_ps(a.val)));
	}

	// Truncate float to *.0
	FEATURE_UN_FUNC(vtrunc, _float8, HAS_AVX1)
	{
		BODY(_mm256_round_ps(a.val, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC));
	}

	// Floor value
	FEATURE_UN_FUNC(vfloor, _float8, HAS_AVX1)
	{
		BODY(_mm256_round_ps(a.val, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));		
	}

	// Ceil value
	FEATURE_UN_FUNC(vceil, _float8, HAS_AVX1)
	{
		BODY(_mm256_round_ps(a.val, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC));
	}

	// Round value
	FEATURE_UN_FUNC(vround, _float8, HAS_AVX1)
	{
		BODY(_mm256_round_ps(a.val, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC));
	}
}}