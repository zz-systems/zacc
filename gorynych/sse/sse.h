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
 * @file sse.h
 *
 * @brief Additional SSE wrapper functions and types
 */

#include "../dependencies.h"
#include "int4.h"
#include "float4.h"
#include "double2.h"


namespace zzsystems { namespace gorynych {

	// Type traits =====================================================================================================

	/**
	 * @brief is true type when the supplied type is an int4 vector
	 */
	DISPATCHED struct is_vint<zzsystems::gorynych::_int4>
			: public std::true_type
	{};

	/**
	 * @brief is true type when the supplied type is a float4 vector
	 */
	DISPATCHED struct is_vreal<zzsystems::gorynych::_float4>
			: public std::true_type
	{};


	/**
	 * @brief the underlying type for float4 vector is a float scalar
	 */
	DISPATCHED struct scalar_type<_float4>
			: public __scalar_type<float>
	{};

	/**
	 * @brief the underlying type for int4 vector is an int scalar
	 */
	DISPATCHED struct scalar_type<_int4>
			: public __scalar_type<int>
	{};

	// Converting constructors =========================================================================================

	/// converting constructor for float->int vector conversion
	DISPATCHED inline _int4::int4(const _float4& rhs) noexcept
			: int4(rhs.val) { }

	/// copy constructor for int vector
	DISPATCHED inline _int4::int4(const _int4& rhs) noexcept
			: int4(rhs.val) { }

	/// copy constructor for float vector
	DISPATCHED inline _float4::float4(const _float4& rhs) noexcept
			: float4(rhs.val) { }

	/// converting constructor for int->float vector conversion
	DISPATCHED inline _float4::float4(const _int4& rhs) noexcept
			: float4(rhs.val) { }

	// double support is neither fully implemented nor enabled for now

	//inline int4::int4(const double2& rhs) : int4(rhs.val) { }
	//inline float4::float4(const double2& rhs) : float4(rhs.val) { }

	/*inline double2::double2(const float4& rhs) : double2(rhs.val) { }
	inline double2::double2(const int4& rhs) : double2(rhs.val) { }
	inline double2::double2(const double2& rhs) : double2(rhs.val) { }	*/

	// Memory access: extract, gather, scatter (todo) ==================================================================

	/// extract int vector values to a memory location
	DISPATCHED void extract(const _int4 &src, int* target)
	{
		_mm_store_si128((__m128i*)target, src.val);
	}

	/// extract float vector values to a memory location
	DISPATCHED void extract(const _float4 &src, float *target)
	{
		_mm_store_ps(target, src.val);
	}

	/// gather int vector values from a memory location by an index vector
	DISPATCHED _int4 vgather(const int* source, const _int4 &index)
	{
		ALIGNED int i[dim<_int4>()];

		extract(index, i);

		return _mm_set_epi32(
				source[static_cast<size_t>(i[3])],
				source[static_cast<size_t>(i[2])],
				source[static_cast<size_t>(i[1])],
				source[static_cast<size_t>(i[0])]);
	}

	/// gather float vector values from a memory location by an index vector
	DISPATCHED _float4 vgather(const float* source, const _int4 &index)
	{
		ALIGNED int i[dim<_int4>()];

		extract(index, i);

		return _mm_set_ps(
				source[static_cast<size_t>(i[3])],
				source[static_cast<size_t>(i[2])],
				source[static_cast<size_t>(i[1])],
				source[static_cast<size_t>(i[0])]);
	}

	// Converting selector =============================================================================================

	/// branchless if-then-else with conversion from float->int vector
	DISPATCHED_FUNC(vsel, _int4, HAS_SSE)
		(const _float4 VREF mask, const _int4 VREF b, const _int4 VREF c)
	{
		BODY(vsel(_int4(_mm_castps_si128(mask.val)), b, c));
	}

	/// branchless if-then-else with conversion from int->float vector
	DISPATCHED_FUNC(vsel, _float4, HAS_SSE)
		(const _int4 VREF mask, const _float4 VREF b, const _float4 VREF c)
	{
		BODY(vsel(_float4(_mm_castsi128_ps(mask.val)), b, c));
	}
}}