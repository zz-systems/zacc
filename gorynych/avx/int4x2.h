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
 * @file int4x2.h
 *
 * @brief AVX1 int8 emulation wrapper
 *
 * The int8 emulation in case the platform offers only AVX1.
 * This is still a bad implementation - evaluation of correct vzeroupper is necessary.
 */


#include "../dependencies.h"
#include "../sse/int4.h"

namespace zzsystems { namespace gorynych {

	DISPATCHED struct float8;
	//struct double4;

	/**
	 * @struct int4x2
	 * @brief emulated vector of 8 ints
	 * @relates int4
	 *
	 * Provides a wrapper around 2x int4
	 * Provides access to (emulated) int8 vectors on AVX1-only-systems like FX-8350 (Piledriver)
	 * This is a pretty simple and penalized/slow implementation
	 * 		- no appropriate vzeroupper implementation yet.
	 *
	 * Prefer SSE only or AVX2 only implementations for now.
	 *
	 * @remark ( AVX1, SSE or SSE3 or SSSE3 or SSE4) AND AVX1 AND NOT AVX2
	 * @since version 1.0.0
	 */
	DISPATCHED struct alignas(32) int4x2
	{

		_int4 lo, ///< lower vector elements
			  hi; ///< higher vector elements

		/// default constructor
		int4x2() = default;

		/// constructor for a single int
		int4x2(const int32_t rhs)		noexcept: lo(rhs), hi(rhs) {}

		/// constructor for an array
		int4x2(int* rhs)				noexcept: lo(rhs), hi(rhs + 4) {}

		/// costruct vector from 8 separate ints
		int4x2(VARGS8(int))				noexcept: lo(VPASS4), hi(VPASS4_HI) {}
		/// costruct vector from 8 separate floats
		int4x2(VARGS8(float))			noexcept: lo(VPASS4), hi(VPASS4_HI) {}

		/// constructor for compiler-specific float vector
		int4x2(const __m256& rhs)		noexcept: lo(_mm256_extractf128_ps(rhs, 0)),
										  hi(_mm256_extractf128_ps(rhs, 1))	{}
		/// constructor for 2x compiler-specifix int vectors
		int4x2(const __m128i& lo,
			   const __m128i& hi)		noexcept: lo(lo), hi(hi) {}
		/// constructor for compiler-specific double vector
		int4x2(const __m256d& rhs)		noexcept: lo(_mm256_extractf128_pd(rhs, 0)),
										  hi(_mm256_extractf128_pd(rhs, 1)) {}

		/// converting constructor for float vector
		int4x2(const _float8&	rhs) noexcept;
		/// copy constructor for emulated int vector
		int4x2(const _int4x2&	rhs) noexcept;
		/// constructor for 2x int vector
		int4x2(const _int4&	rhs_hi, const _int4& rhs_lo) noexcept;

		//int4x2(const double4&	rhs);

		/// @brief define scalar<->vector operators.
		/// @remark Don't forget to extend the macro when you add new operators
		SCALAR_VECTOR_CVT_OP_DEFS(int, _int4x2)


		/// check if ALL bits are set to 1
//		explicit inline operator bool() const
//		{
//			return static_cast<bool>(hi) && static_cast<bool>(lo);
//		}
	};

	DISPATCHED_RET(bool, HAS_AVX1 && !HAS_AVX2) inline is_set(const _int4x2 a)
	{
		return is_set(a.hi) && is_set(a.lo);
	}

	// Arithmetic ======================================================================================================

	/// @name arithmetic operators / functions
	/// @{

	/// @brief negation
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_UN_OP(-, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { -a.lo, -a.hi };
	}
	
	/// @brief add
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(+, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo + b.lo, a.hi + b.hi };
	}
	
	/// @brief sub
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(-, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo - b.lo, a.hi - b.hi };
	}

	
	/// @brief mul
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(*, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo * b.lo, a.hi * b.hi };
	}

	
	/// @brief div
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(/, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo / b.lo, a.hi / b.hi };
	}

	/// @}

	// Logical =========================================================================================================

	/// @name logical operators / functions
	/// @{

	/// @brief Greater than
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	/// @returns boolean vector (as int4x2)
	DISPATCHED_BIN_OP(>, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo > b.lo, a.hi > b.hi };
	}

    
    /// @brief Less than
	/// @relates int4x2
    /// @remark AVX1
	/// @remark SSE
    /// @returns boolean vector (as int4x2)
	DISPATCHED_BIN_OP(<, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo < b.lo, a.hi < b.hi };
	}

  
	/// @brief Equality
	/// @relates int4x2
	/// @remark AVX1
	/// @returns boolean vector (as int4x2)
	DISPATCHED_BIN_OP(==, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo == b.lo, a.hi == b.hi };
	}

	
	/// @brief Non-equality
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	/// @returns boolean vector (as int4x2)
	DISPATCHED_BIN_OP(!=, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo != b.lo, a.hi != b.hi };
	}

	
	/// @brief branchless if-then-else
	/// @relates int4x2
	/// @param a selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_TRI_FUNC(vsel, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { vsel(a.lo, b.lo, c.lo), vsel(a.hi, b.hi, c.hi) };
	}

	/// @}
	// Bitwise =========================================================================================================

	/// @name bitwise operators
	/// @{

	/// @brief not
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_UN_OP(~, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { ~a.lo, ~a.hi };
	}

	
	/// @brief or
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(|, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo | b.lo, a.hi | b.hi };
	}

	
	/// @brief and
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(&, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo & b.lo, a.hi & b.hi };
	}

	
	/// @brief xor
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(^, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo ^ b.lo, a.hi ^ b.hi };
	}

	
	/// @brief right shift (logical)
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_SHIFT_OP(>> , _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo >> sa, a.hi >> sa };
	}

	
	/// @brief left shift (logical)
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_SHIFT_OP(<< , _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { a.lo << sa, a.hi << sa };
	}

	/// @}

	// Bitwise aliases (compatibility with scalar logical op's) ========================================================

	/// @name logic aliases for bitwise operators
	/// (compatibility with scalar logical operators)
	/// @{

	/// @brief Bitwise not (alias)
	/// @relates int4x2
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int4x2 operator~(const _int4x2 a)
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_UN_OP(!, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		BODY(~a);
	}

	
	/// @brief Bitwise or (alias)
	/// @relates int4x2
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int4x2 operator|(const _int4x2 a, const _int4x2 b)
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(|| , _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		BODY(a | b);
	}

	
	/// @brief Bitwise and (alias)
	/// @relates int4x2
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int4x2 operator&(const _int4x2 a, const _int4x2 b)
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_OP(&&, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		BODY(a & b);
	}

	/// @}

	// Basic math functions ============================================================================================

	/// @name basic math functions
	/// @{

	/// @brief square root
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_UN_FUNC(vsqrt, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		BODY(vsqrt(static_cast<_float8>(a)));
	}

	
	/// @brief Absolute value
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_UN_FUNC(vabs, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { vabs(a.lo), vabs(a.hi) };
	}

	
	/// @brief Minumum value
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_FUNC(vmin, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { vmin(a.lo, b.lo), vmin(a.hi, b.hi) };
	}

	
	/// @brief Maximum value
	/// @relates int4x2
	/// @remark AVX1
	/// @remark SSE
	DISPATCHED_BIN_FUNC(vmax, _int4x2, HAS_AVX1 && !HAS_AVX2)
	{
		return { vmax(a.lo, b.lo), vmax(a.hi, b.hi) };
	}
	/// @}
}}
