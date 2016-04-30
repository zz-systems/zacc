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


#include "macros.h"
#include <algorithm>

namespace zzsystems { 	
	
	ANY(T) ASSIGN_OP(+=, T) { return a = (a + b); }
	ANY(T) ASSIGN_OP(-=, T) { return a = (a - b); }
	ANY(T) ASSIGN_OP(*=, T) { return a = (a * b); }
	ANY(T) ASSIGN_OP(/=, T) { return a = (a / b); }	

	ANY(T) ASSIGN_OP(&=, T) { return a = (a & b); }
	ANY(T) ASSIGN_OP(|=, T) { return a = (a | b); }
	ANY(T) ASSIGN_OP(^=, T) { return a = (a ^ b); }

	ANY(T) ASSIGN_OP2(>>=, T, int) { return a = a >> b; }
	ANY(T) ASSIGN_OP2(<<=, T, int) { return a = a << b; }

	ANY(T) BIN_OP(>=, T) { return !(a < b); }
	ANY(T) BIN_OP(<=, T) { return !(a > b); }

	namespace gorynych
	{
		// return the vector field count for any given (standard) type
		// e.g sizeof(__m128i) = 128bit = 4 * 32bit => 4
		// e.g sizeof(float)   = 32bit  = 1 * 32bit => 1
		ANY(T)
			constexpr size_t dim() { BODY(sizeof(T) >> 2); }

		// branched select (if - then - else) for boolean condition		
		ANY(TProcess)
			inline TProcess vsel(const bool condition, const TProcess &choice1, const TProcess &choice2)
		{
			return (condition ? choice1 : choice2);
		}

		//// branched select (if - then - else) for any condition
		//ANY2(TCondition, TProcess)
		//	inline TProcess vsel(const TCondition condition, const TProcess &choice1, const TProcess &choice2)
		//{
		//	return (condition ? choice1 : choice2);
		//}

		// Multiply-Add (compatible with specialized fused mul-add implementations)		
		// [y = a * b + c]
		ANY(TType) TRI_FUNC(vfmadd, TType) { BODY(a * b + c); }

		// Multiply-Subtract (compatible with specialized fused mul-sub implementations) 
		// [y = a * b - c]
		ANY(TType) TRI_FUNC(vfmsub, TType) { BODY(a * b - c); }

		// Clamp: min(max(val, minval), maxval)
		ANY(TType) TRI_FUNC(vclamp, TType) { BODY(vmin(vmax(a, b), c)); }

		// Clamp float32 to int32/2 range
		SIMD_ENABLED_F UN_FUNC(clamp_int32, vreal)
		{
			BODY(vclamp<vreal>(a, -1073741824.0, 1073741824.0));
		}

		// absolute value
		UN_FUNC(vabs, double)	{ BODY(std::fabs(a)); }
		UN_FUNC(vabs, float)	{ BODY(std::fabsf(a)); }
		UN_FUNC(vabs, int)		{ BODY(std::abs(a)); }

		// min / max
		ANY(TType) BIN_FUNC(vmin, TType) { BODY(std::min<TType>(a, b)); }
		ANY(TType) BIN_FUNC(vmax, TType) { BODY(std::max<TType>(a, b)); }

		// truncate decimal part (1.5 -> 1.0)
		UN_FUNC(vtrunc, double) { BODY(static_cast<double>(static_cast<int>(a))); }
		UN_FUNC(vtrunc, float)	{ BODY(static_cast<float>(static_cast<int>(a))); }

		// floor
		UN_FUNC(vfloor, double) { BODY(std::floor(a)); }
		UN_FUNC(vfloor, float)	{ BODY(std::floorf(a)); }

		// ceil
		UN_FUNC(vceil, double)	{ BODY(std::ceil(a)); }
		UN_FUNC(vceil, float)	{ BODY(std::ceilf(a)); }

		// round 
		UN_FUNC(vround, double) { BODY(std::round(a)); }
		UN_FUNC(vround, float)	{ BODY(std::roundf(a)); }		

		// square root
		UN_FUNC(vsqrt, double)	{ BODY(std::sqrt(a)); }
		UN_FUNC(vsqrt, float)	{ BODY(std::sqrtf(a)); }
		UN_FUNC(vsqrt, int)		{ BODY(static_cast<int>(::floor(::sqrt(static_cast<double>(a))))); }


		SIMD_ENABLED_F
			bool is_set(vreal value)
		{
			return static_cast<bool>(value);
		}

		template<>
		bool is_set(float value)
		{
			return value != 0;
		}
}}