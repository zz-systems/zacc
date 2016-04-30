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

// static and dynamic (@ runtime) branch dispatching

#include "dependencies.h"
#include "system_info.h"
#include "avx/avx.h"
#include "sse/sse.h"
#include "x87/SISD.h"
#include "opencl/opencl.h"

namespace zzsystems { namespace gorynych {
	using namespace std;

	// "fallback" (erroneous) dispatcher
	template<typename featuremask, typename enable = void>
	struct static_dispatcher
		//: dispatcher<featuremask>
	{
		static_assert(!is_same<enable, void>::value, "not expected");

		typedef int		vint;
		typedef float	vreal;
		static constexpr const char* unit_name() { return "default FPU"; }
	};

	// x87 dispatcher
	FEATURE
	struct static_dispatcher<featuremask,
		typename enable_if<!HAS_SSE && !HAS_AVX1 && !HAS_AVX2>::type>
		//: dispatcher<featuremask>
	{
		typedef int		vint;
		typedef float	vreal;
		static constexpr const char* unit_name() { return "FPU"; }
	};

	// Dispatcher for all SSE kinds
	FEATURE
		struct static_dispatcher<featuremask,
		typename enable_if<HAS_SSE && !HAS_AVX1 && !HAS_AVX2>::type>
		//: dispatcher<featuremask>
	{
		typedef _int4 vint;
		typedef _float4 vreal;
		static constexpr const char* unit_name() { return "SSE"; }
	};

	// AVX1 dispatcher
	FEATURE
		struct static_dispatcher<featuremask,
		typename enable_if<HAS_AVX1 && !HAS_AVX2>::type>
		//: dispatcher<featuremask>
	{
		typedef _int4x2 vint;
		typedef _float8 vreal;
		static constexpr const char* unit_name() { return "AVX1"; }
	};

	// AVX2 dispatcher
	FEATURE
		struct static_dispatcher<featuremask,
		typename enable_if<HAS_AVX1 && HAS_AVX2>::type>
		//: dispatcher<featuremask>
	{
		typedef _int8 vint;
		typedef _float8 vreal;
		static constexpr const char* unit_name() { return "AVX2"; }
	};	
	
	// capability-constants - used for compile-time branch deduction. 
	// fast float approximation is used by default. 
	using capability_AVX2		= integral_constant<int, CAPABILITY_FASTFLOAT | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3 | CAPABILITY_SSE41 | CAPABILITY_AVX1 | CAPABILITY_AVX2 >;
	using capability_AVX1		= integral_constant<int, CAPABILITY_FASTFLOAT | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3 | CAPABILITY_SSE41 | CAPABILITY_AVX1 >;
	using capability_SSE4FMA	= integral_constant<int, CAPABILITY_FASTFLOAT | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3 | CAPABILITY_SSE41 | CAPABILITY_FMA3>;
	using capability_SSE4		= integral_constant<int, CAPABILITY_FASTFLOAT | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3 | CAPABILITY_SSE41>;
	using capability_SSSE3		= integral_constant<int, CAPABILITY_FASTFLOAT | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3>;
	using capability_SSE3		= integral_constant<int, CAPABILITY_FASTFLOAT | CAPABILITY_SSE2 | CAPABILITY_SSE3>;
	using capability_SSE2		= integral_constant<int, CAPABILITY_FASTFLOAT | CAPABILITY_SSE2>;
	using capability_FPU		= integral_constant<int, CAPABILITY_NONE>;

	// single branch
#define BRANCH(sysinfo, body, branch_name) \
	if (sysinfo.has##branch_name()) \
	{ \
		using capability = capability_##branch_name; \
		using vreal = static_dispatcher<capability>::vreal; \
		using vint	= static_dispatcher<capability>::vint; \
		body; \
	}

	// Dynamic dispatch: Select branch to run
#define SIMD_DISPATCH(sysinfo, body) \
	do { \
		BRANCH(sysinfo, body, AVX2) \
		else BRANCH(sysinfo, body, AVX1) \
		else BRANCH(sysinfo, body, SSE4FMA) \
		else BRANCH(sysinfo, body, SSE4) \
		else BRANCH(sysinfo, body, SSSE3) \
		else BRANCH(sysinfo, body, SSE3) \
		else BRANCH(sysinfo, body, SSE2) \
		else BRANCH(sysinfo, body, FPU) \
	} while(false)

	// Dynamic dispatch: (Pre)build branches	
#define SIMD_BUILD(sysinfo, body) \
	do { \
		BRANCH(sysinfo, body, AVX2) \
		BRANCH(sysinfo, body, AVX1) \
		BRANCH(sysinfo, body, SSE4FMA) \
		BRANCH(sysinfo, body, SSE4) \
		BRANCH(sysinfo, body, SSSE3) \
		BRANCH(sysinfo, body, SSE3) \
		BRANCH(sysinfo, body, SSE2) \
		BRANCH(sysinfo, body, FPU) \
	} while(false)

}}