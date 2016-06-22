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
 * @file avx.h
 *
 * @brief Additional SSE wrapper functions and types
 */

#include "int4x2.h"
#include "int8.h"
#include "float8.h"
#include "double4.h"
#include "../dependencies.h"

namespace zzsystems { namespace gorynych {

	// Type traits =====================================================================================================

	/// @name traits

	/**
	 * @brief is true type when the supplied type is an int8 vector
	 */
	DISPATCHED struct is_vint<zzsystems::gorynych::_int8 >
			: public std::true_type
	{};

	/**
	 * @brief is true type when the supplied type is an int4x2 vector
	 */
	DISPATCHED struct is_vint<zzsystems::gorynych::_int4x2 >
			: public std::true_type
	{};

	/**
	 * @brief is true type when the supplied type is a float8 vector
	 */
	DISPATCHED struct is_vreal<zzsystems::gorynych::_float8 >
			: public std::true_type
	{};

	/**
	 * @brief the underlying type for int8 vector is an int scalar
	 */
	DISPATCHED struct scalar_type<_int8>
			: public __scalar_type<int>
	{};

	/**
	 * @brief the underlying type for int4x2 vector is an int scalar
	 */
	DISPATCHED struct scalar_type<_int4x2>
			: public __scalar_type<int>
	{};

	/**
	* @brief the underlying type for float8 vector is a float scalar
	*/
	DISPATCHED struct scalar_type<_float8>
			: public __scalar_type<float>
	{};

	/// @}

	// Converting constructors =========================================================================================

	/// @name converting constructors
	/// @{

	/// converting constructor for float->int vector conversion
	DISPATCHED inline _int8::int8(const _float8& rhs) noexcept
			: int8(rhs.val) { }

	/// copy constructor for int vector
	DISPATCHED inline _int8::int8(const _int8& rhs) noexcept
			: int8(rhs.val) { }
	//inline int8::int8(const double4& rhs) : int8(rhs.val) { }

	/// converting constructor for float->int vector conversion
	DISPATCHED inline _int4x2::int4x2(const _float8& rhs) noexcept
			: int4x2(rhs.val) { }

	/// copy constructor for int vector
	DISPATCHED inline _int4x2::int4x2(const _int4x2& rhs) noexcept
			: int4x2(rhs.lo, rhs.hi) { }

	/// copy constructor for emulated int vector components
	DISPATCHED inline _int4x2::int4x2(const _int4& lo, const _int4& hi) noexcept
			: int4x2(lo.val, hi.val) { }

	/// copy constructor for float vector
	DISPATCHED inline _float8::float8(const _float8& rhs) noexcept
			: float8(rhs.val) { }

	/// converting constructor for int->float vector conversion
	DISPATCHED inline _float8::float8(const _int8& rhs) noexcept
			: float8(rhs.val) { }

	/// converting constructor for int->float vector conversion
	DISPATCHED inline _float8::float8(const _int4x2& rhs) noexcept
		: float8(_mm256_set_m128(_mm_cvtepi32_ps(rhs.lo.val), _mm_cvtepi32_ps(rhs.hi.val)))
	{
		//_mm256_zeroupper();
	}

	/// @}

	// Memory access: extract, gather, scatter (todo) ==================================================================

	/// @name memory access
	/// extract, gather, scatter (todo)
	/// @{

	/// @brief extract int vector values to a memory location
	/// @param[in] src source vector
	/// @param[out] target aligned storage
	/// @remark target must be aligned
	DISPATCHED void extract(const _int8 &src, int* target)
	{
		_mm256_store_si256((__m256i*)target, src.val);
	}

	/// @brief extract int vector values to a memory location
	/// @param[in] src source vector
	/// @param[out] target aligned storage
	/// @remark target must be aligned
	DISPATCHED void extract(const _int4x2 &src, int* target)
	{
		extract(src.lo, target);
		extract(src.hi, target + 4);
	}

	/// @brief extract float vector values to a memory location
	/// @param[in] src source vector
	/// @param[out] target aligned storage
	/// @remark target must be aligned
	DISPATCHED void extract(const _float8 &src, float *target)
	{
		_mm256_store_ps(target, src.val);
	}

	/// @brief gather float vector values
	/// (a = b[c[i]])
	/// from a memory location by an index vector
	/// @param [in] memloc source
	/// @param index index vector
	DISPATCHED	_int8 vgather(const int* memloc, const _int8 &index)
	{
		return _mm256_i32gather_epi32(memloc, index.val, sizeof(int));
	}

	/// @brief gather float vector values
	/// (a = b[c[i]])
	/// from a memory location by an index vector
	/// @param [in] memloc source
	/// @param index index vector
	DISPATCHED	_int4x2 vgather(const int* memloc, const _int4x2 &index)
	{
		return{ vgather(memloc, index.hi), vgather(memloc, index.lo) };
	}

	/// @brief gather float vector values
	/// (a = b[c[i]])
	/// from a memory location by an index vector
	/// @param [in] memloc source
	/// @param index index vector
	DISPATCHED	_float8 vgather(const float* memloc, const _int4x2 &index)
	{
		return _mm256_set_m128(vgather(memloc, index.hi).val, vgather(memloc, index.lo).val);
	}

	/// @brief gather float vector values
	/// (a = b[c[i]])
	/// from a memory location by an index vector
	/// @param [in] memloc source
	/// @param index index vector
	DISPATCHED _float8 vgather(const float* memloc, const _int8 &index)
	{
		return _mm256_i32gather_ps(memloc, index.val, sizeof(float));
	}

	/// @}

	// Converting selector =============================================================================================

	/// @name converting selectors
	/// @{

	/// @brief branchless if-then-else
	/// with conversion from float->int vector
	/// @param mask selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	DISPATCHED_FUNC(vsel, _int8, HAS_AVX2)
		(const _float8 &mask, const _int8 &b, const _int8 &c)
	{
		BODY(vsel(_int8(_mm256_castps_si256(mask.val)), b, c));
	}

	/// @brief branchless if-then-else
	/// with conversion from int->float vector
	/// @param mask selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	DISPATCHED_FUNC(vsel, _float8, HAS_AVX2)
		(const _int8 &mask, const _float8 &b, const _float8 &c)
	{
		BODY(vsel(_float8(_mm256_castsi256_ps(mask.val)), b, c));
	}

	/// @brief branchless if-then-else
	/// with conversion from float->int vector
	/// @param mask selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	DISPATCHED_FUNC(vsel, _int4x2, HAS_AVX1 && !HAS_AVX2)
		(const _float8 &mask, const _int4x2 &b, const _int4x2 &c)
	{
		_int4x2 a = {
				_int4(_mm_castps_si128(_mm256_extractf128_ps(mask.val, 0))),
				_int4(_mm_castps_si128(_mm256_extractf128_ps(mask.val, 1)))
		};

		BODY(vsel(a, b, c));
	}

	/// @brief branchless if-then-else
	/// with conversion from int->float vector
	/// @param mask selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	DISPATCHED_FUNC(vsel, _float8, HAS_AVX1 && !HAS_AVX2)
		(const _int4x2 &mask, const _float8 &b, const _float8 &c)
	{
		auto a = _mm256_set_m128(_mm_castsi128_ps(mask.lo.val), _mm_castsi128_ps(mask.hi.val));
		BODY(vsel(_float8(a), b, c));
	}

	/// @}
}}