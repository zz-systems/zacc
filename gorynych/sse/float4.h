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
 * @file float4.h
 *
 * @brief SSE __m128 wrapper
 */

#include "../dependencies.h"

namespace zzsystems { namespace gorynych {

	DISPATCHED struct int4;

	
	//struct double2;

	/**
	 * @struct float4
	 * @brief SSE vector of 4 float values
	 *
	 * Provides a wrapper around the compiler-specific __m128 type
	 *
	 * @since version 1.0.0
	 */
	DISPATCHED struct alignas(16) float4
	{
		/// compiler-specific vector
		__m128 val;

		/// default constructor
		float4() = default;

		/// constructor for a single int
		float4(const int rhs)		noexcept : val(_mm_set1_ps(static_cast<float>(rhs))) {}
		/// constructor for a single float
		float4(const float rhs)		noexcept : val(_mm_set1_ps(rhs)) {}
		/// constructor for a single double
		float4(const double rhs)	noexcept : val(_mm_set1_ps(static_cast<float>(rhs))) {}

		/// constructor for an array
		float4(const float* rhs)	noexcept : val(_mm_load_ps(rhs)) {}

		/// costruct vector from 4 separate ints
		float4(VARGS4(int))			noexcept : val(_mm_cvtepi32_ps(_mm_set_epi32(VPASS4))) {}
		/// costruct vector from 4 separate floats
		float4(VARGS4(float))		noexcept : val(_mm_set_ps(VPASS4)) {}

		/// constructor for compiler-specific float vector
		float4(const __m128& rhs)	noexcept : val(rhs) { }
		/// constructor for compiler-specific int vector
		float4(const __m128i& rhs)	noexcept : val(_mm_cvtepi32_ps(rhs)) {}
		/// constructor for compiler-specific double vector
		float4(const __m128d& rhs)	noexcept : val(_mm_cvtpd_ps(rhs)) {}

		/// copy constructor for float vector
		float4(const _float4& rhs) noexcept;

		/// converting constructor for float vector
		float4(const _int4&	rhs) noexcept;
		//float4(const double2&	rhs);

		/// @brief define scalar<->vector operators.
		/// @remark Don't forget to extend the macro when you add new operators
		SCALAR_VECTOR_CVT_OP_DEFS(float, _float4)


		/// check if ALL bits are set to 1
		/// @ref all_ones()
//		explicit inline operator bool()
//		{
//			return all_ones(*this);
//		}
	};

	DISPATCHED_RET(bool, HAS_SSE) inline is_set(const _float4 a)
	{
		return all_ones(a);
	}
	
	/// @brief check if ALL bits are set to 1
	/// @relates float4
	/// @remark SSE4
	DISPATCHED_RET(bool, HAS_SSE41) inline all_ones(const _float4 a)
	{
		BODY(_mm_test_all_ones(_mm_castps_si128(a.val)) != 0);
	}

	
	/// @brief check if ALL bits are set to 1
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_RET(bool, !HAS_SSE41) inline all_ones(const _float4 a)
	{
		auto zero = _mm_setzero_ps();
		auto ones = _mm_cmpeq_ps(zero, zero);

		BODY(_mm_movemask_ps(_mm_cmpeq_ps(a.val, ones)) == 0xFFFF);
	}

	// Arithmetic =====================================================================================================

	/// @name arithmetic operators / functions
	/// @{
	
	/// @brief negation operator
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_UN_OP(-, _float4, HAS_SSE)
	{
		BODY(_mm_sub_ps(_mm_setzero_ps(), a.val));
		//BODY(_mm_xor_ps(a.val, _mm_castsi128_ps(_float4::sign1all0())));
	}

	
	/// @brief add operator
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_OP(+, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_add_ps);
	}

	
	/// @brief sub operator
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_OP(-, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_sub_ps);
	}

	
	/// @brief mul operator
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_OP(*, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_mul_ps);
	}

	
	/// @brief div operator (precise)
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_OP(/, _float4, HAS_SSE && !USE_FAST_FLOAT)
	{
		BIN_BODY(_mm_div_ps);
	}

	
	/// @brief div operator (faster, lower precision!)
	/// @relates float4
	/// @remark SSE2, FAST_FLOAT
	DISPATCHED_BIN_OP(/ , _float4, HAS_SSE && USE_FAST_FLOAT)
	{
		BODY(_mm_mul_ps(a.val, _mm_rcp_ps(b.val)));
	}


	/// @brief fused multiply add
	/// @relates float4
	/// @remark FMA
	DISPATCHED_TRI_FUNC(vfmadd, _float4, HAS_FMA)
	{
		TRI_BODY(_mm_fmadd_ps);
	}


	/// @brief fused multiply sub
	/// @relates float4
	/// @remark FMA
	DISPATCHED_TRI_FUNC(vfmsub, _float4, HAS_FMA)
	{
		TRI_BODY(_mm_fmsub_ps);
	}


	/// @}

	// Logical =========================================================================================================	

	/// @name logical / comparison operators
	/// @{

	/// @brief Greater than operator
	/// @relates float4
	/// @remark SSE2
	/// @returns boolean vector (as float4)	
	DISPATCHED_BIN_OP(>, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpgt_ps);
	}

	
	/// @brief Less than operator
	/// @relates float4
	/// @remark SSE2
	/// @returns boolean vector (as float4)
	DISPATCHED_BIN_OP(<, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_cmplt_ps);
	}

	
	/// @brief Equality operator
	/// @relates float4
	/// @remark SSE2
	/// @returns boolean vector (as float4)
	DISPATCHED_BIN_OP(==, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpeq_ps);
	}

	
	/// @brief Non-equality operator
	/// @relates float4
	/// @remark SSE2
	/// @returns boolean vector (as float4)
	DISPATCHED_BIN_OP(!=, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpneq_ps);
	}

	
	/// @brief branchless if-then-else
	/// @relates float4
	/// @param a selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	/// @remark SSE4
	DISPATCHED_TRI_FUNC(vsel, _float4, HAS_SSE41)
	{
		TRI_BODY_R(_mm_blendv_ps);
	}

	
	/// @brief branchless if-then-else
	/// @relates float4
	/// @param a selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	/// @remark SSE2
	DISPATCHED_TRI_FUNC(vsel, _float4, !HAS_SSE41 && HAS_SSE)
	{
		BODY((a /* mask */ & b) | (~a & c));
	}

	/// @}

	// Bitwise ========================================================================================================

	/// @name bitwise operators
	/// @{
	
	/// @brief not
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_UN_OP(~, _float4, HAS_SSE)
	{
		auto zero = _mm_setzero_ps();
		auto ones = _mm_cmpeq_ps(zero, zero);

		BODY(_mm_xor_ps(a.val, ones));
	}

	
	/// @brief or
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_OP(|, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_or_ps);
	}

	
	/// @brief and
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_OP(&, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_and_ps);
	}

	
	/// @brief xor
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_OP(^, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_xor_ps);
	}

	/// @}

	// Bitwise aliases (compatibility with scalar logical op's) ========================================================

	/// @name bitwise aliases
	/// compatibility with scalar logical operatorss
	/// @{

	/// @brief not (alias)
	/// @relates float4
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref operator~()
	/// @remark SSE2
	DISPATCHED_UN_OP(!, _float4, HAS_SSE)
	{
		BODY(~a);
	}
	
	/// @brief or (alias)
	/// @relates float4
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref operator|()
	/// @remark SSE2
	DISPATCHED_BIN_OP(|| , _float4, HAS_SSE)
	{
		BODY(a | b);
	}

	
	/// @brief and (alias)
	/// @relates float4
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref operator&()
	/// @remark SSE2
	DISPATCHED_BIN_OP(&&, _float4, HAS_SSE)
	{
		BODY(a & b);
	}

	/// @}

	// Basic math functions ============================================================================================

	/// @name basic math functions
	/// @{

	/// @brief precise square root
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_UN_FUNC(vsqrt, _float4, HAS_SSE && !USE_FAST_FLOAT)
	{
		UN_BODY(_mm_sqrt_ps);
	}

	
	/// @brief fast square root
	/// @relates float4
	/// @remark SSE2,
	/// @remark FAST_FLOAT
	DISPATCHED_UN_FUNC(vsqrt, _float4, HAS_SSE && USE_FAST_FLOAT)
	{
		BODY(_mm_mul_ps(a.val, _mm_rsqrt_ps(a.val)));
	}

	
	/// @brief Absolute value
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_UN_FUNC(vabs, _float4, HAS_SSE)
	{
		// According to IEEE 754 standard: sign bit is the first bit => set to 0
		//BODY(_mm_and_ps(a.val, _mm_castsi128_ps(_float4::sign0all1())));
		BODY(vmax(a, -a));
	}

	
	/// @brief Minumum value
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_FUNC(vmin, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_min_ps);
	}

	
	/// @brief Maximum value
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_BIN_FUNC(vmax, _float4, HAS_SSE)
	{
		BIN_BODY(_mm_max_ps);
	}

	/// @}
	// Rounding =======================================================================================================

	/// @name rounding
	/// @{
	
	/// @brief truncate value to *.0
	/// @relates float4
	/// @remark SSE2
	DISPATCHED_UN_FUNC(vtrunc, _float4, HAS_SSE)
	{
		BODY(static_cast<_float4>(static_cast<_int4>(a)));
	}

	
	/// @brief floor value
	/// @relates float4
	/// @remark SSE4
	DISPATCHED_UN_FUNC(vfloor, _float4, HAS_SSE41)
	{
		BODY(_mm_round_ps(a.val, _MM_FROUND_FLOOR));
	}

	
	/// @brief ceil value
	/// @relates float4
	/// @remark SSE4
	DISPATCHED_UN_FUNC(vceil, _float4, HAS_SSE41)
	{
		BODY(_mm_round_ps(a.val, _MM_FROUND_CEIL));
	}

	
	/// @brief round value
	/// @relates float4
	/// @remark SSE4
	DISPATCHED_UN_FUNC(vround, _float4, HAS_SSE41)
	{
		BODY(_mm_round_ps(a.val, _MM_FROUND_TO_NEAREST_INT));
	}

	
	/// @brief floor value
	/// @relates float4
	/// @remark SSE2
	/// @remark SSE3
	/// @see http://dss.stephanierct.com/DevBlog/?p=8
	DISPATCHED_UN_FUNC(vfloor, _float4, !HAS_SSE41 && HAS_SSE)
	{
		auto zero = _mm_setzero_si128();
		auto one  = _mm_srli_epi32(_mm_cmpeq_epi32(zero, zero), 31);

		auto fi = vtrunc(a);
		return vsel(fi > a, fi - _float4(one), fi);
	}

	
	/// @brief ceil value
	/// @relates float4
	/// @remark SSE2
	/// @remark SSE3
	/// @see http://dss.stephanierct.com/DevBlog/?p=8
	DISPATCHED_UN_FUNC(vceil, _float4, !HAS_SSE41 && HAS_SSE)
	{
		auto zero = _mm_setzero_si128();
		auto one  = _mm_srli_epi32(_mm_cmpeq_epi32(zero, zero), 31);

		auto fi = vtrunc(a);
		return vsel(fi < a, fi + _float4(one), fi);
	}

	
	/// @brief round value
	/// @relates float4
	/// @remark SSE2
	/// @remark SSE3
	/// @see http://dss.stephanierct.com/DevBlog/?p=8
	DISPATCHED_UN_FUNC(vround, _float4, !HAS_SSE41 && HAS_SSE)
	{
		auto zero = _mm_setzero_si128();
		auto ones = _mm_cmpeq_epi32(zero, zero);

		//generate the highest value < 2		
		_float4 vNearest2 = _mm_castsi128_ps(_mm_srli_epi32(ones, 2));
		auto aTrunc = vtrunc(a);

		auto rmd = a - aTrunc;        // get remainder
		auto rmd2 = rmd * vNearest2;  // mul remainder by near 2 will yield the needed offset

		auto rmd2Trunc = vtrunc(rmd2); // after being truncated of course

		return aTrunc + rmd2Trunc;
	}

	/// @}
}}