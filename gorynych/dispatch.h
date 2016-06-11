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
 * @file dispatch.h
 *
 * @brief static and dynamic (@ runtime) branch dispatching
 */

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

	/**
	 * @struct static_dispatcher
	 * @brief "fallback" (erroneous) type dispatcher
	 */
	template<typename dispatch_mask, typename enable = void>
	struct static_dispatcher
	{
		static_assert(!is_same<enable, void>::value, "not expected");

		typedef int		vint;  ///< scalar int
		typedef float	vreal; ///< scalar float

		/// @brief execution unit this dispatcher targets (x87 FPU fallback)
		/// @returns string with the unit name
		static constexpr const char* unit_name() { return "default FPU"; }
	};

	/**
	 * @struct static_dispatcher
	 * @brief x87 FPU type dispatcher
	 */
	DISPATCHED struct static_dispatcher<dispatch_mask,
		typename enable_if<!HAS_SSE && !HAS_AVX1 && !HAS_AVX2>::type>
	{
		typedef int		vint;  ///< scalar int
		typedef float	vreal; ///< scalar float

		/// @brief execution unit this dispatcher targets (x87 FPU)
		/// @returns string with the unit name
		static constexpr const char* unit_name() { return "FPU"; }
	};

#if defined(COMPILE_SSE2) || defined(COMPILE_SSE3) || defined(COMPILE_SSSE3) || defined(COMPILE_SSE4) || defined(COMPILE_SSE4FMA)

	/**
	 * @struct static_dispatcher
	 * @brief SSE type dispatcher
	 */
	DISPATCHED struct static_dispatcher<dispatch_mask,
		typename enable_if<HAS_SSE && !HAS_AVX1 && !HAS_AVX2>::type>
	{
		typedef _int4 vint; 	///< vector int x4
		typedef _float4 vreal;  ///< vector float x4

		/// execution unit this dispatcher targets (SSE)
		/// @returns string with the unit name
		static constexpr const char* unit_name() { return "SSE"; }
	};

#endif

#if defined(COMPILE_AVX1)
	/**
	 * @struct static_dispatcher
	 * @brief AVX1 type dispatcher
	 */
	DISPATCHED struct static_dispatcher<dispatch_mask,
		typename enable_if<HAS_AVX1 && !HAS_AVX2>::type>
	{
		typedef _int4x2 vint;  ///< emulated vector int x8
		typedef _float8 vreal; ///< native vector float x8

		/// execution unit this dispatcher targets (AVX1)
		/// @returns string with the unit name
		static constexpr const char* unit_name() { return "AVX1"; }
	};
#endif
#if defined(COMPILE_AVX2)
	/**
	* @struct static_dispatcher
	* @brief AVX2 type dispatcher
	*/
	DISPATCHED struct static_dispatcher<dispatch_mask,
		typename enable_if<HAS_AVX1 && HAS_AVX2>::type>
	{
		typedef _int8 vint; 	///< native vector int x8
		typedef _float8 vreal; 	///< native vector float x8

		/// execution unit this dispatcher targets (AVX2)
		/// @returns string with the unit name
		static constexpr const char* unit_name() { return "AVX2"; }
	};
#endif

/// @def BRANCH(branch_name, body)
/// @brief branch template
/// Evaluates the capabilites, defines the
/// appropriate types for the current branch
/// @param body expression
/// @param branch_name branch name
#define BRANCH(branch_name, body)\
	{ \
		using capability = capability_##branch_name; \
		using vreal = static_dispatcher<capability>::vreal; \
		using vint	= static_dispatcher<capability>::vint; \
		body; \
	}

/// @def CBRANCH(sysinfo, body, branch_name)
/// @brief conditional branch template
/// @param sysinfo system_info object
/// @param body expression
/// @param branch_name branch name
#define CBRANCH(sysinfo, body, branch_name) \
	if (sysinfo.has##branch_name()) \
	{ \
		BRANCH(branch_name, body);\
	}

/// @def SIMD_DISPATCH(sysinfo, body)
/// @brief Dynamic dispatch
/// select one branch at runtime
/// @param sysinfo system_info object
/// @param body expression
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


/// @def SIMD_BUILD(sysinfo, body)
/// @brief Dynamic dispatch
/// select muliple valid branch at runtime
/// @param sysinfo system_info object
/// @param body expression
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