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
 * @file basic_functions.h
 *
 * @brief Generic base functions and conventions
 */

#include "macros.h"
#include <algorithm>
#include <cstdlib>
#include <cmath>
//class type;

namespace std
{
#ifndef WIN32
    //float fabs(float val) { return std::abs(val); }
	//float floorf(float val) { return std::floor(val); }
	//float ceilf(float val) { return std::ceil(val); }
	//float sqrtf(float val) { return std::sqrt(val); }
#endif
}

namespace zzsystems {

	// Generic operators ===============================================================================================

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
		/// @fn dim
		/// @brief vector dimensions
		/// @returns the vector field count for any given (standard) type
		/// @remark dim<int4>  => sizeof(__m128i) = 128bit = 4 * 32bit => 4
		/// @remark dim<float> => sizeof(float)   = 32bit  = 1 * 32bit => 1
		ANY(T) constexpr size_t dim()
		{
			BODY(sizeof(T) >> 2);
		}

		/// @fn vsel()
		/// @brief branched if-then-else
		/// @param a boolean selector mask
		/// @param b then-branch-value
		/// @param c else-branch-value
		ANY(TProcess)inline TProcess vsel
				(const bool condition, const TProcess &choice1, const TProcess &choice2)
		{
			return (condition ? choice1 : choice2);
		}

		// Special functions ===========================================================================================

		/// @fn vfmadd()
		/// @brief generic multiply-add
		/// Multiply-Add (compatible with specialized fused mul-add implementations)
		/// [y = a * b + c]
		ANY(TType) TRI_FUNC(vfmadd, TType)
		{
			BODY(a * b + c);
		}

		/// @fn vfmadd()
		/// @brief generic multiply-sub
		/// Multiply-Subtract (compatible with specialized fused mul-sub implementations)
		/// [y = a * b - c]
		ANY(TType) TRI_FUNC(vfmsub, TType)
		{
			BODY(a * b - c);
		}

		/// @fn is_set()
		/// @brief generic check if value is not 0
		VECTORIZED_F bool is_set(vreal value)
		{
			return static_cast<bool>(value);
		}

		/// @fn is_set()
		/// @brief check if value is not 0 (float)
		template<>
		inline bool is_set(float value)
		{
			return value != 0;
		}

		// Basic math functions ========================================================================================

		/// @fn vsqrt()
		/// @brief precise square root function (double)
		UN_FUNC(vsqrt, double)
		{
			BODY(std::sqrt(a));
		}

		/// @fn vsqrt()
		/// @brief precise square root function (int)
		UN_FUNC(vsqrt, float)
		{
			BODY(std::sqrt(a));
		}

		/// @fn vsqrt()
		/// @brief precise square root function (int)
		/// is implemented using float sqrt and cast back
		UN_FUNC(vsqrt, int)
		{
			BODY(static_cast<int>(::floor(::sqrt(static_cast<double>(a)))));
		}

		/// @fn vabs()
		/// @brief generic absolute value (float)
		UN_FUNC(vabs, float)
		{
			BODY(std::abs(a));
		}

		/// @fn vabs()
		/// @brief generic absolute value (int)
		UN_FUNC(vabs, int)
		{
			BODY(std::abs(a));
		}

		/// @fn vmin()
		/// @brief generic minumum value
		ANY(TType) BIN_FUNC(vmin, TType)
		{
			BODY(std::min<TType>(a, b));
		}

		/// @fn vmin()
		/// @brief generic maximum value
		ANY(TType) BIN_FUNC(vmax, TType)
		{
			BODY(std::max<TType>(a, b));
		}

		/// @fn vclamp()
		/// @brief generic clamp
		/// min(max(val, minval), maxval)
		ANY(TType) TRI_FUNC(vclamp, TType)
		{
			BODY(vmin(vmax(a, b), c));
		}

		/// @fn clamp_int32()
		/// @brief generic clamp to int 32 range
		// Clamp float32 to int32/2 range
		VECTORIZED_F UN_FUNC(clamp_int32, vreal)
		{
			BODY(vclamp<vreal>(a, -1073741824.0, 1073741824.0));
		}

		// Rounding ====================================================================================================

		/// @fn vtrunc()
		/// @brief truncate value to *.0 (double)
		UN_FUNC(vtrunc, double)
		{
			BODY(static_cast<double>(static_cast<int>(a)));
		}

		/// @fn vtrunc()
		/// @brief truncate value to *.0 (float)
		UN_FUNC(vtrunc, float)
		{
			BODY(static_cast<float>(static_cast<int>(a)));
		}

		/// @fn vfloor()
		/// @brief floor value (double)
		UN_FUNC(vfloor, double)
		{
			BODY(std::floor(a));
		}

		/// @fn vfloor()
		/// @brief floor value (float)
		UN_FUNC(vfloor, float)
		{
			BODY(std::floor(a));
		}

		/// @fn vceil()
		/// @brief ceil value (double)
		UN_FUNC(vceil, double)
		{
			BODY(std::ceil(a));
		}

		/// @fn vceil()
		/// @brief ceil value (float)
		UN_FUNC(vceil, float)
		{
			BODY(std::ceil(a));
		}

		/// @fn vround()
		/// @brief round value (double)
		UN_FUNC(vround, double)
		{
			BODY(std::round(a));
		}

		/// @fn vround()
		/// @brief round value (float)
		UN_FUNC(vround, float)
		{
			BODY(std::round(a));
		}
}}