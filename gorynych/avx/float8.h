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
 * @file float8.h
 *
 * @brief AVX1 __m256 wrapper
 */

#include "../dependencies.h"

namespace zzsystems { namespace gorynych {
	/// forward int8
	DISPATCHED struct int8;
	/// forward int4x2
	DISPATCHED struct int4x2;

	//struct double4;

	/**
	 * @struct float8
	 * @brief AVX vector of 8 float values
	 *
	 * Provides a wrapper around the compiler-specific __m256 type
	 *
	 * @since version 1.0.0
	 */
	DISPATCHED struct alignas(32) float8
	{
		/// compiler-specific vector
		__m256 val;

		/// default constructor
		float8() = default;

		/// constructor for a single int
		float8(const int rhs)		noexcept : val(_mm256_set_ps(DUP8(static_cast<float>(rhs)))) {}
		/// constructor for a single float
		float8(const float rhs)		noexcept : val(_mm256_set_ps(DUP8(rhs))) {}
		/// constructor for a single double
		float8(const double rhs)	noexcept : val(_mm256_set_ps(DUP8(static_cast<float>(rhs)))) {}

		/// constructor for an array
		float8(const float* rhs)	noexcept : val(_mm256_load_ps(rhs)) {}

		/// costruct vector from 8 separate ints
		float8(VARGS8(int))			noexcept : val(_mm256_cvtepi32_ps(_mm256_set_epi32(VPASS8))) {}
		/// costruct vector from 8 separate floats
		float8(VARGS8(float))		noexcept : val(_mm256_set_ps(VPASS8)) {}

		/// constructor for compiler-specific float vector
		float8(const __m256& rhs)	noexcept : val(rhs) {}
		/// constructor for compiler-specific int vector
		float8(const __m256i& rhs)	noexcept : val(_mm256_cvtepi32_ps(rhs)) {}
		/// constructor for compiler-specific double vector
		float8(const __m256d& rhs)	noexcept : val(_mm256_castps128_ps256(_mm256_cvtpd_ps(rhs))) {}

		/// copy constructor for float vector
		float8(const _float8&	rhs) noexcept;
		/// copy constructor for int vector
		float8(const _int8&	rhs) noexcept;
		/// copy constructor for emulated int vector
		float8(const _int4x2& rhs) noexcept;

		//float8(const double4&	rhs);

		/// @brief define scalar<->vector operators.
		/// @remark Don't forget to extend the macro when you add new operators
		SCALAR_VECTOR_CVT_OP_DEFS(float, _float8)

		/// check if ALL bits are set to 1
		/// @ref all_ones()
		explicit operator bool()
		{
			//return _mm256_test_all_ones(_mm256_castps_si256(this->val)) != 0;
			return all_ones(*this);
		}
	};

	/**
	 * @brief check if ALL bits are set to 1
	 * @relates float8
	 * @remark AVX2
	 */
	DISPATCHED_RET(bool, HAS_AVX2) all_ones(const _float8 a)
	{
		BODY(_mm256_test_all_ones(_mm256_castps_si256(a.val)) != 0);
	}

	/**
	 * @brief check if ALL bits are set to 1
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_RET(bool, HAS_AVX1 && !HAS_AVX2) all_ones(const _float8 a)
	{
		auto zero = _mm256_setzero_ps();
		auto ones = _mm256_cmp_ps(zero, zero, _CMP_EQ_OQ);

		BODY(_mm256_movemask_ps(_mm256_cmp_ps(a.val, ones, _CMP_EQ_OQ)) == 0xFFFF);
	}
	// Arithmetic ======================================================================================================
	/// @name arithmetic operators
	/// @{

	/**
	 * @brief negation operator
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_UN_OP(-, _float8, HAS_AVX1)
	{
		BODY(_mm256_sub_ps(_mm256_setzero_ps(), a.val));
	}

	/**
	 * @brief add operator
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_OP(+, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_add_ps); 
	}

	/**
	 * @brief sub operator
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_OP(-, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_sub_ps);
	}

	/**
	 * @brief mul operator
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_OP(*, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_mul_ps); 
	}

	/**
	 * @brief div (precise)
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_OP(/, _float8, HAS_AVX1 && !USE_FAST_FLOAT)
	{
		BIN_BODY(_mm256_div_ps);
	}

	/**
	 * @brief div operator (faster, lower precision!)
	 * @relates float8
	 * @remark AVX1
	 * @remark FAST_FLOAT
	 */
	DISPATCHED_BIN_OP(/ , _float8, HAS_AVX1 && USE_FAST_FLOAT)
	{
		BODY(_mm256_mul_ps(a.val, _mm256_rcp_ps(b.val)));
	}

	/**
	 * @brief fused multiply add
	 * @relates float8
	 * @remark AVX1
	*/
	DISPATCHED_TRI_FUNC(vfmadd, _float8, HAS_AVX1)
	{
		TRI_BODY(_mm256_fmadd_ps);
	}

	/**
	 * @brief fused multiply sub
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_TRI_FUNC(vfmsub, _float8, HAS_AVX1)
	{
		TRI_BODY(_mm256_fmsub_ps);
	}

	///@}
		
	// Logical =========================================================================================================

	/// @name logical & comparison operators
	/// @{

	/**
	 * @brief Greater than 
	 * @relates float8
	 * @remark AVX1
	 * @returns boolean vector (as float8)
	 */
	DISPATCHED_BIN_OP(>, _float8, HAS_AVX1)
	{
		//TRI_BODY_O(_mm256_cmp_ps, _CMP_GT_OQ);
		return _mm256_cmp_ps(a.val, b.val, _CMP_GT_OQ);
	}

	/**
	 * @brief Less than
	 * @relates float8
	 * @remark AVX1
	 * @returns boolean vector (as float8)
	 */
	DISPATCHED_BIN_OP(< , _float8, HAS_AVX1)
	{
		//TRI_BODY_O(_mm256_cmp_ps, _CMP_LT_OQ);
		return _mm256_cmp_ps(a.val, b.val, _CMP_LT_OQ);
	}

	/**
	 * @brief Equality
	 * @relates float8
	 * @remark AVX1
	 * @returns boolean vector (as float8)
	 */
	DISPATCHED_BIN_OP(==, _float8, HAS_AVX1)
	{
		//TRI_BODY_O(_mm256_cmp_ps, _CMP_EQ_OQ);
		return _mm256_cmp_ps(a.val, b.val, _CMP_EQ_OQ);
	}

	/**
	 * @brief Non-equality
	 * @relates float8
	 * @remark AVX1
	 * @returns boolean vector (as float8)
	 */
	DISPATCHED_BIN_OP(!=, _float8, HAS_AVX1)
	{
		//TRI_BODY_O(_mm256_cmp_ps, _CMP_EQ_OQ);
		return _mm256_cmp_ps(a.val, b.val, _CMP_NEQ_OQ);
	}

	/**
	 * @brief branchless if-then-else
	 * @relates float8
	 * @param a selector mask
	 * @param b then-branch-value
	 * @param c else-branch-value
	 * @remark AVX1
	 */
	DISPATCHED_TRI_FUNC(vsel, _float8, HAS_AVX1)
	{
		TRI_BODY_R(_mm256_blendv_ps);
	}

	/// @}

	// Bitwise ========================================================================================================

	/// @name bitwise operators
	/// @{

	/**
	 * @brief not
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_UN_OP(~, _float8, HAS_AVX1)
	{
		auto zero = _mm256_setzero_ps();
		auto ones = _mm256_cmp_ps(zero, zero, _CMP_EQ_OQ);

		BODY(_mm256_xor_ps(a.val, ones));
	}

	/**
	 * @brief or
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_OP(|, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_or_ps);
	}

	/**
	 * @brief and
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_OP(&, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_and_ps);
	}

	/**
	 * @brief xor
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_OP(^, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_xor_ps);
	}

	/// @}
	// Bitwise aliases (compatibility with scalar logical op's) ========================================================

	/**
	 * @name bitwise aliases
	 *
	 * compatibility with scalar logical operators
	 */
	/// @{

	/**
	 * @brief logical not (alias)
	 * @relates float8
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 * @ref _float8 operator~(const _float8 a)
	 * @remark AVX1
	 */
	DISPATCHED_UN_OP(!, _float8, HAS_AVX1)
	{
		BODY(~a);
	}

	/**
	 * @brief logical or (alias)
	 * @relates float8
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 * @ref _float8 operator|(const _float8 a, const _float8 b)
	 * @remark AVX1
	 */
	DISPATCHED_BIN_OP(|| , _float8, HAS_AVX1)
	{
		BODY(a | b);
	}

	/**
	 * @brief logical and (alias)
	 * @relates float8	 *
	 * @ref _float8 operator&(const _float8 a, const _float8 b)
	 * @remark AVX1
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 */
	DISPATCHED_BIN_OP(&&, _float8, HAS_AVX1)
	{
		BODY(a & b);
	}

	/// @}

	// Basic math functions ============================================================================================

	/// @name basic math functions
	/// @{

	/**
	 * @brief precise square root
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_UN_FUNC(vsqrt, _float8, HAS_AVX1 && !USE_FAST_FLOAT)
	{
		UN_BODY(_mm256_sqrt_ps);
	}

	/**
	 * @brief fast square root
	 * @relates float8
	 * is implemented using float fast sqrt and cast back
	 * @remark AVX1, FAST_FLOAT
	 */
	DISPATCHED_UN_FUNC(vsqrt, _float8, HAS_AVX1 && USE_FAST_FLOAT)
	{
		BODY(_mm256_mul_ps(a.val, _mm256_rsqrt_ps(a.val)));
	}

	/**
	 * @brief Absolute value
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_UN_FUNC(vabs, _float8, HAS_AVX1)
	{
		//BODY(_mm256_and_ps(a.val, _mm256_castsi256_ps(_float8::sign0all1())));
		BODY(vmax(a, -a));
	}

	/**
	 * @brief Minumum value
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_FUNC(vmin, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_min_ps); 
	}

	/**
	 * @brief Maximum value
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_BIN_FUNC(vmax, _float8, HAS_AVX1)
	{
		BIN_BODY(_mm256_max_ps);
	}

	/// @}

	// Rounding =======================================================================================================

	/// @name rounding functions
	/// @{

	/**
	 * @brief truncate value to *.0
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_UN_FUNC(vtrunc, _float8, HAS_AVX1)
	{
		BODY(_mm256_round_ps(a.val, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC));
	}

	/**
	 * @brief floor value
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_UN_FUNC(vfloor, _float8, HAS_AVX1)
	{
		BODY(_mm256_round_ps(a.val, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC));		
	}

	/**
	 * @brief ceil value
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_UN_FUNC(vceil, _float8, HAS_AVX1)
	{
		BODY(_mm256_round_ps(a.val, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC));
	}

	/**
	 * @brief round value
	 * @relates float8
	 * @remark AVX1
	 */
	DISPATCHED_UN_FUNC(vround, _float8, HAS_AVX1)
	{
		BODY(_mm256_round_ps(a.val, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC));
	}

	/// @}
}}