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
 * @file system_info.h
 * @brief system capability detection at runtime
 */

#include <algorithm>
#include <iostream>

#ifdef _WIN32

/// MSVC CPUID
#define cpuid(info, x)    __cpuidex(info, x, 0)

#else

//  GCC Intrinsics
#include <cpuid.h>
/// gcc / clang CPUID
#define cpuid(info, x) __cpuid_count(x, 0, info[0], info[1], info[2], info[3])

#endif

using namespace std;

namespace zzsystems { namespace gorynych {

	/// @enum capabilities
	/// @brief relevant system capabilities
	enum capabilities
	{
		CAPABILITY_NONE		= 0, 		///< usuallly fallback to x87 FPU

		CAPABILITY_SSE2		= 1 << 0, 	///< SSE 2 support
		CAPABILITY_SSE3		= 1 << 1,	///< SSE 3 support
		CAPABILITY_SSSE3	= 1 << 2,	///< SSSE 3 support
		
		CAPABILITY_SSE41	= 1 << 3,  	///< SSE 4.1 support
		CAPABILITY_SSE42	= 1 << 4,	///< SSE 4.2 support
		
		CAPABILITY_FMA3		= 1 << 5,	///< FMA 3 support
		CAPABILITY_FMA4		= 1 << 6,	///< FMA 4 support

		CAPABILITY_AVX1		= 1 << 7,	///< AVX support
		CAPABILITY_AVX2		= 1 << 8,	///< AVX 2 support
		CAPABILITY_AVX512	= 1 << 9, 	///< AVX 512 support

		CAPABILITY_FASTFLOAT = 1 << 10, ///< use faster float computations ( lower precision )

		CAPABILITY_OPENCL	= 1 << 11, 	///< OPENCL support
		CAPABILITY_FPGA		= 1 << 12	///< FPGA synthesis support?
	};


#if defined(FASTFLOAT)
#define FASTFLOAT_ENABLED CAPABILITY_FASTFLOAT
#else
#define FASTFLOAT_ENABLED 0
#endif

	using capability_AVX2		= integral_constant<int, FASTFLOAT_ENABLED | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3 | CAPABILITY_SSE41 | CAPABILITY_AVX1 | CAPABILITY_AVX2 >;
	using capability_AVX1		= integral_constant<int, FASTFLOAT_ENABLED | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3 | CAPABILITY_SSE41 | CAPABILITY_AVX1 >;
	using capability_SSE4FMA	= integral_constant<int, FASTFLOAT_ENABLED | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3 | CAPABILITY_SSE41 | CAPABILITY_FMA3>;
	using capability_SSE4		= integral_constant<int, FASTFLOAT_ENABLED | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3 | CAPABILITY_SSE41>;
	using capability_SSSE3		= integral_constant<int, FASTFLOAT_ENABLED | CAPABILITY_SSE2 | CAPABILITY_SSE3 | CAPABILITY_SSSE3>;
	using capability_SSE3		= integral_constant<int, FASTFLOAT_ENABLED | CAPABILITY_SSE2 | CAPABILITY_SSE3>;
	using capability_SSE2		= integral_constant<int, FASTFLOAT_ENABLED | CAPABILITY_SSE2>;
	using capability_FPU		= integral_constant<int, CAPABILITY_NONE>;	

#undef FASTFLOAT_ENABLED

	/// @brief retrieves platform info
	/// which is later used to select an appropriate execution branch
	struct system_info
	{
		/// currently set capabilities
		int feature_flags;

		/// @brief populates the flags with system capabilities
		/// @todo : check xrstore
		/// @todo GPU check
		system_info()
			: feature_flags(CAPABILITY_NONE)
		{
			int cpuInfo[4];
			cpuid(cpuInfo, 1);

			// SSE2:
			feature_flags |= cpuInfo[3] & (1 << 26) ? CAPABILITY_SSE2 : CAPABILITY_NONE;
			
			// SSE3:
			feature_flags |= cpuInfo[2] & (1 << 0) ? CAPABILITY_SSE3 : CAPABILITY_NONE;
			// SSSE3
			feature_flags |= cpuInfo[2] & (1 << 9) ? CAPABILITY_SSSE3 : CAPABILITY_NONE;
			
			// SSE 4.1
			feature_flags |= cpuInfo[2] & (1 << 19) ? CAPABILITY_SSE41 : CAPABILITY_NONE;
			// SSE 4.2
			feature_flags |= cpuInfo[2] & (1 << 20) ? CAPABILITY_SSE42 : CAPABILITY_NONE;

			// FMA3
			feature_flags |= cpuInfo[2] & (1 << 12) ? CAPABILITY_FMA3 : CAPABILITY_NONE;


			bool use_xrstore = cpuInfo[2] & (1 << 27)	|| false;

			feature_flags |= cpuInfo[2] & (1 << 28) ? CAPABILITY_AVX1 : CAPABILITY_NONE;
			
			// Extended CPU info
			cpuid(cpuInfo, 7);

			feature_flags |= cpuInfo[1] & (1 << 5) ? CAPABILITY_AVX2 : CAPABILITY_NONE;
			feature_flags |= cpuInfo[1] & (1 << 16) ? CAPABILITY_AVX512 : CAPABILITY_NONE;

			//if (use_xrstore && has_avx1)
			//{
			//	// Check if the OS will save the YMM registers
			//	unsigned long long xcrFeatureMask = _xgetbv(_XCR_XFEATURENABLED_MASK);
			//	has_avx1 = (xcrFeatureMask & 0x6) || false;
			//}
		}

		/// @brief checks if a specific flag is set
		/// @returns true if flag is set
		bool hasFlag(const capabilities c) const
		{
			return 0 != (this->feature_flags & c);
		}

		/// @brief sets or resets feature flag
		/// @param c capability flag to change
		/// @param enable set/reset
		/// useful for deactivation of CPU features
		/// @todo validation: disallow setting features not supported by the system
		void setFlag(const capabilities c, bool enable)
		{
			this->feature_flags = (feature_flags & ~(c)) | ((enable ? 1 : 0) & c);
		}

		/// checks if AVX 2 (and AVX 1) are avaliable
		bool hasAVX2() const
		{
			return hasFlag(CAPABILITY_AVX1) && hasFlag(CAPABILITY_AVX2);
		}

		/// checks if AVX 1 is avaliable
		bool hasAVX1() const
		{
			return hasFlag(CAPABILITY_AVX1);// && !hasFlag(CAPABILITY_AVX2);
		}

		/// checks if SSE 4.1 or SSE 4.1  are avaliable
		bool hasSSE4() const
		{
			return hasFlag(CAPABILITY_SSE42) || hasFlag(CAPABILITY_SSE41);
		}

		/// checks if SSE 4 and FMA3/4 are avaliable
		bool hasSSE4FMA() const
		{
			return hasSSE4() && (hasFlag(CAPABILITY_FMA3) || hasFlag(CAPABILITY_FMA4));
		}

		/// checks if SSSE3 and SSE3 are avaliable
		bool hasSSSE3() const
		{
			return hasFlag(CAPABILITY_SSSE3) && hasSSE3();
		}

		/// checks if SSE3 is avaliable
		bool hasSSE3() const
		{
			return hasFlag(CAPABILITY_SSE3) && hasSSE2();
		}

		/// checks if SSE2 is avaliable
		bool hasSSE2() const
		{
			return hasFlag(CAPABILITY_SSE2);
		}

		/// checks if x87 FPU is avaliable :O
		static bool hasFPU()
		{
			return true;
		}

		/// pretty-prints the currently supperted features
		friend ostream& operator<<(ostream& os, const system_info& dt);

		static constexpr const char* getName(const capabilities c)
		{
			switch(c)
			{
				case CAPABILITY_SSE2: 	return "SSE2";
				case CAPABILITY_SSE3: 	return "SSE3";
				case CAPABILITY_SSSE3: 	return "SSSE3";
				case CAPABILITY_SSE41: 	return "SSE4.1";
				case CAPABILITY_SSE42: 	return "SSE4.2";
				case CAPABILITY_FMA3: 	return "SSE4+FMA3";
				case CAPABILITY_FMA4: 	return "SSE4+FMA4";
				case CAPABILITY_AVX1: 	return "AVX1";
				case CAPABILITY_AVX2: 	return "AVX2";
				case CAPABILITY_AVX512: return "AVX512";
				case CAPABILITY_OPENCL: return "OpenCL";
				case CAPABILITY_FPGA: 	return "FPGA";

				default: 
					return "FPU";				
			}
		}
	};

	/// pretty-prints the currently supperted features
	inline ostream& operator<<(ostream& os, const system_info& cap)
	{
		os << "Has SSE2:	"	<< boolalpha << cap.hasFlag(CAPABILITY_SSE2) << endl;
		os << "Has SSE3:	"	<< boolalpha << cap.hasFlag(CAPABILITY_SSE3)  << endl;
		os << "Has SSSE3:	"	<< boolalpha << cap.hasFlag(CAPABILITY_SSSE3) << endl;

		os << "Has SSE4.1:	"	<< boolalpha << cap.hasFlag(CAPABILITY_SSE41) << endl;
		os << "Has SSE4.2:	"	<< boolalpha << cap.hasFlag(CAPABILITY_SSE42) << endl;

		os << "Has FMA3:	"	<< boolalpha << cap.hasFlag(CAPABILITY_FMA3) << endl;

		//os << "Uses XRSTORE: "	<< cap.use_xrstore << endl;

		os << "Has AVX1:	"	<< boolalpha << cap.hasFlag(CAPABILITY_AVX1) << endl;
		os << "Has AVX2:	"	<< boolalpha << cap.hasFlag(CAPABILITY_AVX2) << endl;
		os << "Has AVX512:	"	<< boolalpha << cap.hasFlag(CAPABILITY_AVX512) << endl;

		return os;
	}

	/// Used to distinguish branch-dependant code at compile-time
	/// @ref VECTORIZED
	/// @ref DISPATCHED
	/// @todo GPU check
	DISPATCHED
		struct dispatcher
	{
		/// current capabilities
		static constexpr int feature_flags = capability();

		/// sse 2 available?
		static constexpr bool has_sse2			= 0 != (capability() & CAPABILITY_SSE2);
		/// sse 3 available?
		static constexpr bool has_sse3			= 0 != (capability() & CAPABILITY_SSE3);
		/// ssse 3 available?
		static constexpr bool has_ssse3			= 0 != (capability() & CAPABILITY_SSSE3);

		// fma4 available?
		static constexpr bool has_fma3			= 0 != (capability() & CAPABILITY_FMA3);
		/// fma4 available?
		static constexpr bool has_fma4			= 0 != (capability() & CAPABILITY_FMA4);
		/// fma available?
		static constexpr bool has_fma			= has_fma3 || has_fma4;

		/// sse 4.1 available?
		static constexpr bool has_sse41			= 0 != (capability() & CAPABILITY_SSE41);
		/// sse 4.2 available?
		static constexpr bool has_sse42			= 0 != (capability() & CAPABILITY_SSE42);
		/// sse 4 available?
		static constexpr bool has_sse4			= has_sse41 || has_sse42;

		/// avx 1 available?
		static constexpr bool has_avx			= 0 != (capability() & CAPABILITY_AVX1);
		/// avx 2 available?
		static constexpr bool has_avx2			= 0 != (capability() & CAPABILITY_AVX2);
		/// avx 512 available?
		static constexpr bool has_avx512		= 0 != (capability() & CAPABILITY_AVX512);
		/// fast (lower precision) float enabled?
		static constexpr bool use_fast_float	= 0 != (capability() & CAPABILITY_FASTFLOAT);
	};

	/// @name dispatcher shortcuts
	/// @{

	/// dispatcher alias
	#define _dispatcher dispatcher<capability>

	/// @def HAS_SSE
	/// @brief shortcut: check if SSE 2 is available
	#define HAS_SSE _dispatcher::has_sse2

	/// @def HAS_SSE3
	/// @brief shortcut: check if SSE 3 is available
	#define HAS_SSE3 _dispatcher::has_sse3

	/// @def HAS_SSSE3
	/// @brief shortcut: check if SSSE 3 is available
	#define HAS_SSSE3 _dispatcher::has_ssse3

	/// @def HAS_FMA3
	/// @brief shortcut: check if FMA 3 is available
	#define HAS_FMA3 _dispatcher::has_fma3

	/// @def HAS_FMA4
	/// @brief shortcut: check if FMA 4 is available
	#define HAS_FMA4 _dispatcher::has_fma4

	/// @def HAS_FMA
	/// @brief shortcut: check if FMA 3/4 is available
	#define HAS_FMA _dispatcher::has_fma

	/// @def HAS_SSE41
	/// @brief shortcut: check if SSE 4.1 is available
	#define HAS_SSE41 _dispatcher::has_sse41

	/// @def HAS_SSE42
	/// @brief shortcut: check if SSE 4.2 is available
	#define HAS_SSE42 _dispatcher::has_sse42

	/// @def HAS_SSE4
	/// @brief shortcut: check if SSE 4.1/4.2 is available
	#define HAS_SSE4 _dispatcher::has_sse4

	/// @def HAS_AVX1
	/// @brief shortcut: check if AVX is available
	#define HAS_AVX1 _dispatcher::has_avx

	/// @def HAS_AVX2
	/// @brief shortcut: check if AVX 2 is available
	#define HAS_AVX2 _dispatcher::has_avx2

	/// @def HAS_AVX512
	/// @brief shortcut: check if AVX 512 is available
	#define HAS_AVX512 _dispatcher::has_avx512

	/// @def USE_FAST_FLOAT
	/// @brief shortcut: check if fast float is active
	#define USE_FAST_FLOAT _dispatcher::use_fast_float

	/// @}

}}