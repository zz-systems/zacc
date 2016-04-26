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

//#pragma once
//#ifndef PARANOISE_INTRINSIC_M128D_H
//#define PARANOISE_INTRINSIC_M128D_H
//
//#include "base.h"
//
//namespace zzsystems { namespace gorynych {
//	struct float4;
//	struct int4;
//
//	ALIGN(16) struct double2 {
//		__m128d val;
//		//double values[2];
//
//		double2() = default;
//		double2(const double& rhs)	{ val = _mm_set1_pd(rhs); }
//
//		double2(const __m128& rhs)	{ val = _mm_cvtps_pd(rhs); }
//		double2(const __m128i& rhs)	{ val = _mm_cvtepi32_pd(rhs); }
//		double2(const __m128d& rhs)	{ val = rhs; }
//
//		double2(const float4& rhs);
//		double2(const int4& rhs);
//		double2(const double2& rhs);
//	};
//
//	inline double2 operator +(const double2& a, const double2& b) { return _mm_add_pd		(a.val, b.val); }
//	inline double2 operator -(const double2& a, const double2& b) { return _mm_sub_pd		(a.val, b.val); }
//	inline double2 operator *(const double2& a, const double2& b) { return _mm_mul_pd		(a.val, b.val); }
//	inline double2 operator /(const double2& a, const double2& b) { return _mm_div_pd		(a.val, b.val); }
//
//	inline double2 operator >(const double2& a, const double2& b) { return _mm_cmpgt_pd	(a.val, b.val); }
//	inline double2 operator <(const double2& a, const double2& b) { return _mm_cmplt_pd	(a.val, b.val); }
//	inline double2 operator==(const double2& a, const double2& b) { return _mm_cmpeq_pd	(a.val, b.val); }
//
//	inline double2 operator &(const double2& a, const double2& b) { return _mm_and_pd		(a.val, b.val); }	
//	inline double2 operator ~(const double2& a)					{ return _mm_andnot_pd	(a.val, a.val); }
//
//	inline double2 abs(const double2& a) {
//		static const __m128d sign_mask = _mm_set1_pd(-0.); // -0. = 1 << 63
//		return _mm_andnot_pd(sign_mask, a.val); // !sign_mask & x
//	}
//
//	inline double2 vmin(const double2& a, const double2& b)		{ return _mm_min_pd		(a.val, b.val);	}
//	inline double2 vmax(const double2& a, const double2& b)		{ return _mm_max_pd		(a.val, b.val);	}	
//
//	inline double2 vsqrt(const double2& a)						{ return _mm_sqrt_pd	(a.val); }
//
//	//inline double2	adjustoToInt32(const double2& a)					 { return _mm_cvtepi32_ps(_mm_cvtps_epi32(a.val)); }
//}}
//
//#endif