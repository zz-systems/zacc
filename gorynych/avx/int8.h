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
 * @file int8.h
 *
 * @brief AVX2 __m256i wrapper
 */

#include "../dependencies.h"

namespace zzsystems { namespace gorynych {

	DISPATCHED struct float8;
	//struct double4;

	/**
	 * @struct int8
	 * @brief AVX2 vector of 8 int values
	 *
	 * Provides a wrapper around the compiler-specific __m128i type
	 *
	 * @remark AVX2
	 * @since version 1.0.0
	 */
	DISPATCHED struct alignas(32) int8
	{
		/// compiler-specific vector
		__m256i val;

		/// default constructor
		int8() = default;

		/// constructor for a single int
		int8(const int rhs)			noexcept : val(_mm256_set_epi32(DUP8(rhs))) {}

		/// constructor for an array
		int8(const int* rhs)		noexcept : val(_mm256_load_si256((__m256i*)rhs)) {}

		/// costruct vector from 8 separate ints
		int8(VARGS8(int))			noexcept : val(_mm256_set_epi32(VPASS8)) {}
		/// costruct vector from 8 separate floats
		int8(VARGS8(float))			noexcept : val(_mm256_cvtps_epi32(_mm256_set_ps(VPASS8))) {}

		/// constructor for compiler-specific float vector
		int8(const __m256& rhs)		noexcept : val(_mm256_cvtps_epi32(rhs)) {}
		/// constructor for compiler-specific int vector
		int8(const __m256i& rhs)	noexcept : val(rhs) {}
		/// constructor for compiler-specific double vector
		int8(const __m256d& rhs)	noexcept : val(_mm256_castsi128_si256(_mm256_cvtpd_epi32(rhs))) {}

		/// converting constructor for float vector
		int8(const _float8&	rhs) noexcept;
		/// copy constructor for int vector
		int8(const _int8&	rhs) noexcept;
		//int8(const double4&	rhs);

		/// @brief define scalar<->vector operators.
		/// @remark Don't forget to extend the macro when you add new operators
		SCALAR_VECTOR_CVT_OP_DEFS(int, _int8)



		/// check if ALL bits are set to 1
//		explicit inline operator bool()
//		{
//			return _mm256_test_all_ones(this->val);
//		}
	};

	DISPATCHED_RET(bool, HAS_AVX2) inline is_set(const _int8 VREF a)
	{
		return _mm256_test_all_ones(a.val);
	}

	// Arithmetic ======================================================================================================

	/// @name arithmetic operators / functions
	/// @{
	
	/// @brief negation
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_UN_OP(-, _int8, HAS_AVX2)
	{
		BODY(_mm256_sub_epi32(_mm256_setzero_si256(), a.val));
	}

	
	/// @brief add
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_BIN_OP(+, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_add_epi32);
	}

	
	/// @brief sub
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_BIN_OP(-, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_sub_epi32);
	}

	
	/// @brief mul
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_BIN_OP(*, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_mullo_epi32);
	}

	
	/// @brief div is implemented using float div and cast back
	/// @relates int8
	/// @remark AVX1, AVX2
	DISPATCHED_BIN_OP(/, _int8, HAS_AVX1 && HAS_AVX2)
	{
		BODY(_mm256_div_ps(_mm256_cvtepi32_ps(a.val), _mm256_cvtepi32_ps(b.val)));
	}

	/// @}

	// Logical =========================================================================================================

	/// @name logical operators
	/// @{

	/// @brief Greater than
	/// @relates int8
	/// @remark AVX2
	/// @returns boolean vector (as int8)
	DISPATCHED_BIN_OP(>, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_cmpgt_epi32);
	}

	
	/// @brief Less than
	/// @relates int8
	/// @remark AVX2
	/// @returns boolean vector (as int8)
	DISPATCHED_BIN_OP(<, _int8, HAS_AVX2)
	{
		BIN_BODY_R(_mm256_cmpgt_epi32);
	}

	
	/// @brief Equality
	/// @relates int8
	/// @remark AVX2
	/// @returns boolean vector (as int8)
	DISPATCHED_BIN_OP(==, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_cmpeq_epi32);
	}

	
	/// @brief Non-equality
	/// @relates int8
	/// @remark AVX2
	/// @returns boolean vector (as int8)
	DISPATCHED_BIN_OP(!=, _int8, HAS_AVX2)
	{

		BODY(_mm256_xor_si256((_mm256_cmpeq_epi32 BIN_ARG), _mm256_cmpeq_epi32(_mm256_setzero_si256(), _mm256_setzero_si256())));

		//BODY((_mm256_cmpeq_epi32 BIN_ARG));
	}

	
	/// @brief branchless if-then-else
	/// @relates int8
	/// @param a selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	/// @remark AVX2
	DISPATCHED_TRI_FUNC(vsel, _int8, HAS_AVX2)
	{
		TRI_BODY_R(_mm256_blendv_epi8);
	}

	/// @}

	// Bitwise =========================================================================================================

	/// @name bitwise operators
	/// @{

	/// @brief not
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_UN_OP(~, _int8, HAS_AVX2)
	{
		BODY(_mm256_xor_si256(a.val, _mm256_cmpeq_epi32(_mm256_setzero_si256(), _mm256_setzero_si256())));
	}
	
	/// @brief or
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_BIN_OP(|, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_or_si256);
	}
	
	/// @brief and
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_BIN_OP(&, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_and_si256);
	}
	
	/// @brief xor
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_BIN_OP(^, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_xor_si256);
	}
	
	/// @brief right shift (logical)
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_SHIFT_OP(>> , _int8, HAS_AVX2)
	{
		return _mm256_srli_epi32(a.val, sa);
	}
	
	/// @brief left shift (logical)
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_SHIFT_OP(<< , _int8, HAS_AVX2)
	{
		return _mm256_slli_epi32(a.val, sa);
	}

	/// @}

	// Bitwise aliases (compatibility with scalar logical op's) ========================================================

	/// @name bitwise aliases
	/// @{
	
	/// @brief Bitwise not (alias) operator
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int8 operator~(const _int8 a)
	/// @remark AVX2
	DISPATCHED_UN_OP(!, _int8, HAS_AVX2)
	{
		BODY(~a);
	}

	
	/// @brief Bitwise or (alias) operator
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int8 operator|(const _int8 a, const _int8 b)
	/// @remark AVX2
	DISPATCHED_BIN_OP(|| , _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_or_si256);
	}

	
	/// @brief Bitwise and (alias) operator
	/// @relates int8
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int8 operator&(const _int8 a, const _int8 b)
	/// @remark AVX2
	DISPATCHED_BIN_OP(&&, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_and_si256);
	}

	/// @}
		
	// Basic math functions ============================================================================================

	/// @name basic math functions
	/// @{
		
	/// @brief precise square root
	/// @relates int8
	/// implemented using float sqrt and cast back
	/// @remark AVX2
	DISPATCHED_UN_FUNC(vsqrt, _int8, HAS_AVX2 && !USE_FAST_FLOAT)
	{
		BODY(_mm256_sqrt_ps(_mm256_cvtepi32_ps(a.val)));
	}
	
	/// @brief fast square root function
	/// @relates int8
	/// implemented using float sqrt and cast back
	/// @remark AVX2, FAST_FLOAT
	DISPATCHED_UN_FUNC(vsqrt, _int8, HAS_AVX2 && USE_FAST_FLOAT)
	{
		auto cvt = _mm256_cvtepi32_ps(a.val);

		BODY(_mm256_mul_ps(cvt, _mm256_rsqrt_ps(cvt)));
	}
	
	/// @brief Absolute value
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_UN_FUNC(vabs, _int8, HAS_AVX2)
	{
		UN_BODY(_mm256_abs_epi32);
	}
	
	/// @brief Minumum value
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_BIN_FUNC(vmin, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_min_epi32);
	}
	
	/// @brief Maximum value
	/// @relates int8
	/// @remark AVX2
	DISPATCHED_BIN_FUNC(vmax, _int8, HAS_AVX2)
	{
		BIN_BODY(_mm256_max_epi32);
	}

	/// @}
}}