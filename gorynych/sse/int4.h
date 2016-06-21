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
 * @file int4.h
 *
 * @brief SSE __m128i wrapper
 */

#include "../dependencies.h"

namespace zzsystems { namespace gorynych {

	DISPATCHED struct float4;

	/**
	 * @struct int4
	 * @brief SSE vector of 4 int values
	 *
	 * Provides a wrapper around the compiler-specific __m128i type
	 *
	 * @remark SSE2 or SSE3 or SSSE3 or SSE4
	 * @since version 1.0.0
	 */
	DISPATCHED struct alignas(16) int4
	{
		/// compiler-specific vector
		__m128i val;

		/// default constructor
		int4() = default;

		/// constructor for a single int
		int4(const int rhs)			noexcept : val(_mm_set1_epi32(rhs)) {}

		/// constructor for an array
		int4(const int* rhs)		noexcept : val(_mm_load_si128((__m128i*)rhs)) {}

		/// costruct vector from 4 separate ints
		int4(VARGS4(int))			noexcept : val(_mm_set_epi32(VPASS4)) {}
		/// costruct vector from 4 separate floats
		int4(VARGS4(float))			noexcept : val(_mm_cvtps_epi32(_mm_set_ps(VPASS4))) {}


		/// constructor for compiler-specific float vector
		int4(const __m128& rhs)		noexcept : val(_mm_cvtps_epi32(rhs)) {}
		/// constructor for compiler-specific int vector
		int4(const __m128i& rhs)	noexcept : val(rhs) {}
		/// constructor for compiler-specific double vector
		int4(const __m128d& rhs)	noexcept : val(_mm_cvtpd_epi32(rhs)) {}

		/// copy constructor for int vector
		int4(const _int4& rhs) noexcept;

		/// converting constructor for float vector
		int4(const _float4& rhs) noexcept;
		//int4(const double2& rhs);

		/// @brief defines scalar<->vector operators.
		/// @remark Don't forget to extend the macro when you add new operators
		SCALAR_VECTOR_CVT_OP_DEFS(int, _int4)



		/// check if ALL bits are set to 1
//		explicit inline operator bool() const
//		{
//			return _mm_test_all_ones(this->val);
//		}
	};

	DISPATCHED_RET(bool, HAS_SSE) inline is_set(const _int4 a)
	{
		return _mm_test_all_ones(a.val);
	}

	// Arithmetic ======================================================================================================

	/**
	 * @name arithmetic operators
	 */
	///@{

	/**
	 * @brief negation
	 * @relates int4
	 * @remark SSE2
	 */
	DISPATCHED_UN_OP(-, _int4, HAS_SSE)
	{
		BODY(_mm_sub_epi32(_mm_setzero_si128(), a.val));
	}

	/**
	 * @brief add
	 * @relates int4
	 * @remark SSE2
	 */
	DISPATCHED_BIN_OP(+, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_add_epi32);
	}

	/**
	 * @brief sub
	 * @relates int4
	 * @remark SSE2
	 */
	DISPATCHED_BIN_OP(-, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_sub_epi32);
	}

	/**
	 * @brief mul (native)
	 * @relates int4
	 * @remark SSE4
	 */
	DISPATCHED_BIN_OP(*, _int4, HAS_SSE41)
	{
		BIN_BODY(_mm_mullo_epi32);
	}

	/**
	 * @brief mul (emulated)
	 * @relates int4
	 * @see https://software.intel.com/en-us/forums/intel-c-compiler/topic/288768
	 * @remark SSE2
	 *
	 * For machines without SSE4 another algorithm has to be used
	 */
	DISPATCHED_BIN_OP(*, _int4, !HAS_SSE41 && HAS_SSE)
	{
		/* mul 2,0*/
		auto tmp1 = _mm_castsi128_ps(_mm_mul_epu32(a.val, b.val));
		/* mul 3,1 */
		auto tmp2 = _mm_castsi128_ps(_mm_mul_epu32( _mm_srli_si128(a.val, 4), _mm_srli_si128(b.val, 4)));

		return  _mm_castps_si128(_mm_shuffle_ps(tmp1, tmp2, _MM_SHUFFLE(2,0,2,0)));
	}

	/**
	 * @brief div
	 * @relates int4
	 * @remark SSE2
	 *
	 * operator is implemented using float div and cast back
	 */
	DISPATCHED_BIN_OP(/, _int4, HAS_SSE)
	{
		BODY(_mm_div_ps(_mm_cvtepi32_ps(a.val), _mm_cvtepi32_ps(b.val)));
	}

	///@}

	// Logical =========================================================================================================

	/**
	 * @name logic &comparison operators
	 */
	///@{

	/**
	 * @brief Greater than
	 * @relates int4
	 * @remark SSE2
	 * @returns boolean vector (as int4)
	 */
	DISPATCHED_BIN_OP(>, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpgt_epi32);
	}

	/**
	 * @brief Less than
	 * @relates int4
	 * @remark SSE2
	 * @returns boolean vector (as int4)
 	 */
	DISPATCHED_BIN_OP(<, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_cmplt_epi32);
	}

	/**
	 * @brief Equality
	 * @relates int4
	 * @remark SSE2
	 * @returns boolean vector (as int4)
	 */
	DISPATCHED_BIN_OP(==, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_cmpeq_epi32);
	}

	/**
	 * @brief Non-equality
 	 * @relates int4
	 * @remark SSE2
	 * @returns boolean vector (as int4)
	 */
	DISPATCHED_BIN_OP(!=, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_andnot_si128);
		//BODY(_mm_andnot_si128(_mm_cmpeq_epi32(a.val, b.val), _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128())));
	}

	/**
	 * @brief branchless if-then-else (native)
	 * @relates int4
	 * @param a selector mask
	 * @param b then-branch-value
	 * @param c else-branch-value
	 * @remark SSE4
	 */
	DISPATCHED_TRI_FUNC(vsel, _int4, HAS_SSE41)
	{
		TRI_BODY_R(_mm_blendv_epi8);
	}

	/**
	 * @brief branchless if-then-else (emulated)
	 * @relates int4
	 * @param a selector mask
	 * @param b then-branch-value
	 * @param c else-branch-value
	 * @remark SSE2
	 */
	DISPATCHED_TRI_FUNC(vsel, _int4, HAS_SSE && !HAS_SSE41)
	{
		BODY(a /*mask */ & b | ~a & c);
	}

	///@}

	// Bitwise =========================================================================================================

	/**
	 * @name Bitwise operators
	 *
	 */
	///@{

	/**
	 * @brief not
	 * @relates int4
	 * @remark SSE
	 */
	DISPATCHED_UN_OP(~, _int4, HAS_SSE)
	{
		BODY(_mm_xor_si128(a.val, _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128())));
	}

	/**
	 * @brief or
	 * @relates int4
	 * @remark SSE
	 */
	DISPATCHED_BIN_OP(|, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_or_si128);
	}

	/**
	 * @brief and
	 * @relates int4
	 * @remark SSE
	 */
	DISPATCHED_BIN_OP(&, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_and_si128);
	}

	/**
	 * @brief xor
	 * @relates int4
	 * @remark SSE
	 */
	DISPATCHED_BIN_OP(^, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_xor_si128);
	}

	/**
	 * @brief right shift (logical)
	 * @relates int4
	 * @remark SSE
	 * @param a value
	 * @param sa shift amout
	 */
	DISPATCHED_SHIFT_OP(>>, _int4, HAS_SSE)
	{
		return _mm_srli_epi32		(a.val, sa);
	}

	/**
	 * @brief left shift (logical)
	 * @relates int4
	 * @remark SSE
	 * @param a value
	 * @param sa shift amout
	 */
	DISPATCHED_SHIFT_OP(<<, _int4, HAS_SSE)
	{
		return _mm_slli_epi32(a.val, sa);
	}

	///@}

	// Bitwise aliases (compatibility with scalar logical op's) ========================================================

	/**
	 * @name  Bitwise aliases
	 *
	 * compatibility with scalar logical operators
	 */
	///@{

	/**
	 * @brief Bitwise not (alias)
	 * @relates int4
	 * @ref operator~(const _int4)
	 * @remark SSE
	 *
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 */
	DISPATCHED_UN_OP(!, _int4, HAS_SSE)
	{
		BODY(~a);
	}

	/**
	 * @brief Bitwise or (alias)
	 * @relates int4
	 * @ref operator|(const _int4, const _int4)
	 * @remark SSE
	 *
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 */
	DISPATCHED_BIN_OP(|| , _int4, HAS_SSE)
	{
		BIN_BODY(_mm_or_si128);
	}

	/**
	 * @brief Bitwise and (alias)
	 * @relates int4
	 * @ref operator&(const _int4, const _int4)
	 * @remark SSE
	 *
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 */
	DISPATCHED_BIN_OP(&&, _int4, HAS_SSE)
	{
		BIN_BODY(_mm_and_si128);
	}

	///@}

	// Basic math functions ============================================================================================

	/**
	 * @name Basic math functions
	 */
	///@{

	/**
	 * @brief square root (precise, slower)
	 * @relates int4
	 * @remark SSE
	 *
	 * implemented using float sqrt and cast back to int
	 */
	DISPATCHED_UN_FUNC(vsqrt, _int4, HAS_SSE && !USE_FAST_FLOAT)
	{
		BODY(_mm_sqrt_ps(_mm_cvtepi32_ps(a.val)));
	}

	/**
	 * @brief square root (lower precision, faster)
	 * @relates int4
	 * @remark SSE
	 * @remark FAST_FLOAT
	 *
	 * implemented using float sqrt and cast back to int
	 */
	DISPATCHED_UN_FUNC(vsqrt, _int4, HAS_SSE && USE_FAST_FLOAT)
	{
		auto cvt = _mm_cvtepi32_ps(a.val);

		BODY(_mm_mul_ps(cvt, _mm_rsqrt_ps(cvt)));
	}

	/**
	 * @brief absolute value (emulated)
	 * @relates int4
	 * @remark SSE2
	 * @remark SSE3
	 */
	DISPATCHED_UN_FUNC(vabs, _int4, HAS_SSE && !HAS_SSSE3)
	{
		BODY(vmax(-a, a));
		//BODY(((a >> 31) ^ a) - a);
	}

	/**
	 * @brief absolute value (native)
	 * @relates int4
	 * @remark SSSE3
	 */
	DISPATCHED_UN_FUNC(vabs, _int4, HAS_SSE && HAS_SSSE3)
	{
		UN_BODY(_mm_abs_epi32);
	}

	/**
	 * @brief minumum value (emulated)
	 * @relates int4
	 * @remark SSE2
	 * @remark SSE3
	 * @remark SSSE3
	 */
	DISPATCHED_BIN_FUNC(vmin, _int4, HAS_SSE && !HAS_SSE41)
	{
		BODY(vsel(a < b, a, b));
	}

	/**
	 * @brief minumum value (native)
	 * @relates int4
	 * @remark SSE4
	 */
	DISPATCHED_BIN_FUNC(vmin, _int4, HAS_SSE41)
	{
		BIN_BODY(_mm_min_epi32);
	}

	/**
	 * @brief maximum value (emulated)
	 * @relates int4
	 * @remark SSE2
	 * @remark SSE3
	 * @remark SSSE3
	 */
	DISPATCHED_BIN_FUNC(vmax, _int4, HAS_SSE && !HAS_SSE41)
	{
		BODY(vsel(a > b, a, b));
	}

	/**
	 * @brief maximum value (native)
	 * @relates int4
	 * @remark SSE4
	 */
	DISPATCHED_BIN_FUNC(vmax, _int4, HAS_SSE41)
	{
		BIN_BODY(_mm_max_epi32);
	}

	///@}
}}