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


#include "int4x2.h"
#include "int8.h"
#include "float8.h"
#include "double4.h"
#include "../dependencies.h"



// Traits =========================================================================================================
namespace std {

}
//template<>
//struct std::_Is_floating_point<zzsystems::gorynych::double2>	: std::true_type {	};

namespace zzsystems { namespace gorynych {

	DISPATCHED
	struct is_vint<zzsystems::gorynych::_int8 > : std::true_type {
	};

	DISPATCHED
	struct is_vint<zzsystems::gorynych::_int4x2 > : std::true_type {
	};

	DISPATCHED
	struct is_vreal<zzsystems::gorynych::_float8 > : std::true_type {
	};

	DISPATCHED
	struct scalar_type<_float8> : public __scalar_type<float>
	{};

	DISPATCHED
	struct scalar_type<_int8> : public __scalar_type<int32_t>
	{};
	// Converting constructors ===================================================================================
	DISPATCHED
		_int8::int8(const _float8& rhs) : int8(rhs.val) { }

	DISPATCHED
		_int8::int8(const _int8& rhs) : int8(rhs.val) { }
	//inline int8::int8(const double4& rhs) : int8(rhs.val) { }

	DISPATCHED
		_int4x2::int4x2(const _float8& rhs) : int4x2(_mm256_extractf128_ps(rhs.val, 1), _mm256_extractf128_ps(rhs.val, 0)) { }
	DISPATCHED
		_int4x2::int4x2(const _int4x2& rhs) : int4x2(rhs.hi, rhs.lo) { }
	DISPATCHED
		_int4x2::int4x2(const _int4& rhs_hi, const _int4& rhs_lo) : int4x2(rhs_hi.val, rhs_lo.val) { }

	DISPATCHED
		_float8::float8(const _float8& rhs) : float8(rhs.val) { }
	DISPATCHED
		_float8::float8(const _int8& rhs) : float8(rhs.val) { }
	DISPATCHED
		_float8::float8(const _int4x2& rhs)
		: float8(_mm256_set_m128(_mm_cvtepi32_ps(rhs.hi.val), _mm_cvtepi32_ps(rhs.lo.val)))
	{
		_mm256_zeroupper();
	}
	//inline float8::float8(const double4& rhs) : float8(rhs.val) { }

	/*inline double4::double4(const float8& rhs) : double4(rhs.val) { }
	inline double4::double4(const int8& rhs) : double4(rhs.val) { }
	inline double4::double4(const double4& rhs) : double4(rhs.val) { }*/

//	DISPATCHED void extract(_int8 &src, int32_t* target)
//	{
//		//return src.val.m256i_i32;
//		__m256_store_si256(src.val, target);
//		//for(size_t i = 0; i < dim<_int8>(); i++)
//		//	target[i] = _mm256_extract_epi32(src.val, i);
//	}

	DISPATCHED void extract(const _int8 &src, int32_t* target)
	{
		__mm256_store_si256(src.val, target);
	}

	DISPATCHED void extract(const _int4x2 &src, int32_t* target)
	{
		extract(src.hi, target);
		extract(src.lo, target + 4);
	}

	DISPATCHED void extract(const _float8 &src, float *target)
	{
		_mm256_store_ps(target, src.val);
	}

	DISPATCHED	_int8 vgather(const int* memloc, _int8 index)
	{
		return _mm256_i32gather_epi32(memloc, index.val, sizeof(int));
	}

	DISPATCHED	_int4x2 vgather(const int* memloc, _int4x2 index)
	{
		return{ vgather(memloc, index.hi), vgather(memloc, index.lo) };
	}

	DISPATCHED	_float8 vgather(const float* memloc, _int4x2 index)
	{
		return _mm256_set_m128(vgather(memloc, index.hi).val, vgather(memloc, index.lo).val);
	}

	DISPATCHED _float8 vgather(const float* memloc, _int8 index)
	{
		return _mm256_i32gather_ps(memloc, index.val, sizeof(float));
	}


	// Integer SQRT =============================================================================================	
	DISPATCHED_FUNC(vsqrt, _int8, _dispatcher::has_avx)
		(const _int8 &a)
	{
		BODY(_mm256_sqrt_ps(static_cast<_float8>(a).val));
	}

	DISPATCHED_FUNC(vsqrt, _int4x2, _dispatcher::has_avx)
		(const _int4x2 &a)
	{
		BODY(_mm256_sqrt_ps(static_cast<_float8>(a).val));
	}
	// Integer DIV ==============================================================================================	

	DISPATCHED_BIN_OP(/ , _int8, _dispatcher::has_avx2)
	{
		BODY(_mm256_div_ps(static_cast<_float8>(a).val, static_cast<_float8>(b).val));
	}	

	DISPATCHED_BIN_OP(/ , _int4x2, _dispatcher::has_avx)
	{
		BODY(_mm256_div_ps(static_cast<_float8>(a).val, static_cast<_float8>(b).val));
	}

	DISPATCHED_FUNC(vsel, _int8, _dispatcher::has_avx2)
		(const _float8 &a, const _int8 &b, const _int8 &c)
	{		
		BODY(vsel(c, b, _int8(a)));
	}

	DISPATCHED_FUNC(vsel, _float8, _dispatcher::has_avx2)
		(const _int8 &a, const _float8 &b, const _float8 &c)
	{
		BODY(vsel(c, b, _float8(a)));
	}

	DISPATCHED_FUNC(vsel, _int4x2, _dispatcher::has_avx && !_dispatcher::has_avx2)
		(const _float8 &a, const _int4x2 &b, const _int4x2 &c)
	{
		BODY(vsel(c, b, _int4x2(a.val)));
	}

	DISPATCHED_FUNC(vsel, _float8, _dispatcher::has_avx && !_dispatcher::has_avx2)
		(const _int4x2 &a, const _float8 &b, const _float8 &c)
	{
		BODY(vsel(c, b, _float8(a)));
	}
}}