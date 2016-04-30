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
#include "int4.h"
#include "float4.h"
#include "double2.h"

// Traits =========================================================================================================
FEATURE
struct std::_Is_integral<zzsystems::gorynych::_int4>	: std::true_type {	};

FEATURE
struct std::_Is_floating_point<zzsystems::gorynych::_float4>	: std::true_type {	};

//template<>
//struct std::_Is_floating_point<zzsystems::gorynych::double2>	: std::true_type {	};

namespace zzsystems { namespace gorynych {

	// Converting constructors ===================================================================================
	FEATURE
	inline _int4::int4(const _float4& rhs) : int4(rhs.val) { }
	FEATURE
	inline _int4::int4(const _int4& rhs) : int4(rhs.val) { }
	//inline int4::int4(const double2& rhs) : int4(rhs.val) { }
	FEATURE
	inline _float4::float4(const _float4& rhs) : float4(rhs.val) { }
	FEATURE
	inline _float4::float4(const _int4& rhs) : float4(rhs.val) { }
	//inline float4::float4(const double2& rhs) : float4(rhs.val) { }

	/*inline double2::double2(const float4& rhs) : double2(rhs.val) { }
	inline double2::double2(const int4& rhs) : double2(rhs.val) { }
	inline double2::double2(const double2& rhs) : double2(rhs.val) { }	*/

	FEATURE
	int32_t* extract(_int4 &src)
	{
		return src.val.m128i_i32;
	}

	FEATURE
	const int32_t* extract(const _int4 &src)
	{
		return src.val.m128i_i32;
	}

	FEATURE
	const float* extract(const _float4 &src)
	{		
		return src.val.m128_f32;		
	}
	
	FEATURE
	_int4 vgather(const int* memloc, _int4 index)
	{
		int* i = extract(index);
		return _mm_set_epi32(
			memloc[static_cast<size_t>(i[3])], 
			memloc[static_cast<size_t>(i[2])],
			memloc[static_cast<size_t>(i[1])], 
			memloc[static_cast<size_t>(i[0])]);
	}

	FEATURE
		_float4 vgather(const float* memloc, _int4 index)
	{
		int* i = extract(index);
		return _mm_set_ps(
			memloc[static_cast<size_t>(i[3])], 
			memloc[static_cast<size_t>(i[2])], 
			memloc[static_cast<size_t>(i[1])], 
			memloc[static_cast<size_t>(i[0])]);
	}

	// Integer SQRT =============================================================================================	
	FEATURE_FUNC(vsqrt, _int4, HAS_SSE)
		(const _int4 &a)
	{
		BODY(_mm_sqrt_ps(static_cast<_float4>(a).val));
	}	

	// Integer DIV ==============================================================================================	
		
	FEATURE_BIN_OP(/, _int4, HAS_SSE)
	{
		BODY(_mm_div_ps(static_cast<_float4>(a).val, static_cast<_float4>(b).val));
	}

	FEATURE_FUNC(vsel, _int4, !HAS_SSE41 && HAS_SSE)
		(const _float4 &a, const _int4 &b, const _int4 &c)
	{
		_int4 mask(a.val);
		return (mask & b) | (~mask & c);
	}

	FEATURE_FUNC(vsel, _float4, !HAS_SSE41 && HAS_SSE)
		(const _int4 &a, const _float4 &b, const _float4 &c)
	{
		_float4 mask = _mm_castsi128_ps(a.val);
		return mask & b | ~mask & c;
	}

	FEATURE_FUNC(vsel, _int4, HAS_SSE41 && HAS_SSE)
		(const _float4 &a, const _int4 &b, const _int4 &c)
	{
		BODY(_mm_blendv_epi8(c.val, b.val, _mm_castps_si128(a.val)));
	}

	FEATURE_FUNC(vsel, _float4, HAS_SSE41 && HAS_SSE)
		(const _int4 &a, const _float4 &b, const _float4 &c)
	{
		BODY(_mm_blendv_ps(c.val, b.val, _mm_castsi128_ps(a.val)));
	}	
}}