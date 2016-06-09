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

#if defined(COMPILE_SSE2) || defined(COMPILE_SSE3) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE4) || defined(COMPILE_SSE4FMA) || defined(COMPILE_AVX1)
#include "sse/sse.h"
#endif

#if defined(COMPILE_AVX1) || defined(COMPILE_AVX2)
#include "avx/avx.h"
#endif

#include "x87/SISD.h"
#include "opencl/opencl.h"

namespace zzsystems { namespace gorynych {
	using namespace std;

	// "fallback" (erroneous) dispatcher
	template<typename dispatch_mask, typename enable = void>
	struct static_dispatcher
		//: dispatcher<dispatch_mask>
	{
		static_assert(!is_same<enable, void>::value, "not expected");

		typedef int		vint;
		typedef float	vreal;
		static constexpr const char* unit_name() { return "default FPU"; }
	};

	// x87 dispatcher
	DISPATCHED
	struct static_dispatcher<dispatch_mask,
		typename enable_if<!HAS_SSE && !HAS_AVX1 && !HAS_AVX2>::type>
		//: dispatcher<dispatch_mask>
	{
		typedef int		vint;
		typedef float	vreal;
		static constexpr const char* unit_name() { return "FPU"; }
	};

#if defined(COMPILE_SSE2) || defined(COMPILE_SSE3) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE4) || defined(COMPILE_SSE4FMA)
	// Dispatcher for all SSE kinds
	DISPATCHED
		struct static_dispatcher<dispatch_mask,
		typename enable_if<HAS_SSE && !HAS_AVX1 && !HAS_AVX2>::type>
		//: dispatcher<dispatch_mask>
	{
		typedef _int4 vint;
		typedef _float4 vreal;
		static constexpr const char* unit_name() { return "SSE"; }
	};
#endif

#if defined(COMPILE_AVX1)
	// AVX1 dispatcher
	DISPATCHED
		struct static_dispatcher<dispatch_mask,
		typename enable_if<HAS_AVX1 && !HAS_AVX2>::type>
		//: dispatcher<dispatch_mask>
	{
		typedef _int4x2 vint;
		typedef _float8 vreal;
		static constexpr const char* unit_name() { return "AVX1"; }
	};
#endif
#if defined(COMPILE_AVX2)
	// AVX2 dispatcher
	DISPATCHED
		struct static_dispatcher<dispatch_mask,
		typename enable_if<HAS_AVX1 && HAS_AVX2>::type>
		//: dispatcher<dispatch_mask>
	{
		typedef _int8 vint;
		typedef _float8 vreal;
		static constexpr const char* unit_name() { return "AVX2"; }
	};	
#endif
	// capability-constants - used for compile-time branch deduction. 
	// fast float approximation is used by default.



#define BRANCH(branch_name, body)\
	{ \
		using capability = capability_##branch_name; \
		using vreal = static_dispatcher<capability>::vreal; \
		using vint	= static_dispatcher<capability>::vint; \
		body; \
	}


	// single branch
#define CBRANCH(sysinfo, body, branch_name) \
	if (sysinfo.has##branch_name()) \
	{ \
		BRANCH(branch_name, body);\
	}

	// Dynamic dispatch: Select branch to run
#define SIMD_DISPATCH(sysinfo, body) \
	do { \
		CBRANCH(sysinfo, body, AVX2) \
		else CBRANCH(sysinfo, body, AVX1) \
		else CBRANCH(sysinfo, body, SSE4FMA)\
		else CBRANCH(sysinfo, body, SSE4) \
		else CBRANCH(sysinfo, body, SSSE3) \
		else CBRANCH(sysinfo, body, SSE3) \
		else CBRANCH(sysinfo, body, SSE2) \
		else CBRANCH(sysinfo, body, FPU) \
	} while(false)


	// Dynamic dispatch: (Pre)build branches	
#define SIMD_BUILD(sysinfo, body) \
	do { \
		CBRANCH(sysinfo, body, AVX2) \
		CBRANCH(sysinfo, body, AVX1) \
		CBRANCH(sysinfo, body, SSE4FMA) \
		CBRANCH(sysinfo, body, SSE4) \
		CBRANCH(sysinfo, body, SSSE3) \
		CBRANCH(sysinfo, body, SSE3) \
		CBRANCH(sysinfo, body, SSE2) \
		CBRANCH(sysinfo, body, FPU) \
	} while(false)


}}