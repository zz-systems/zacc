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

// Code to determine system capabilities at runtime 

#include <algorithm>
#include <iostream>

using namespace std;

namespace zzsystems { namespace gorynych {

	enum capabilities
	{
		CAPABILITY_NONE		= 0,

		CAPABILITY_SSE2		= 1 << 0,
		CAPABILITY_SSE3		= 1 << 1,
		CAPABILITY_SSSE3	= 1 << 2,
		
		CAPABILITY_SSE41	= 1 << 3,
		CAPABILITY_SSE42	= 1 << 4,
		
		CAPABILITY_FMA3		= 1 << 5,
		CAPABILITY_FMA4		= 1 << 6,

		CAPABILITY_AVX1		= 1 << 7,
		CAPABILITY_AVX2		= 1 << 8,
		CAPABILITY_AVX512	= 1 << 9,

		CAPABILITY_FASTFLOAT = 1 << 10,

		CAPABILITY_OPENCL	= 1 << 11,
		CAPABILITY_FPGA		= 1 << 12
	};
		
	struct system_info
	{
		int feature_flags;

		system_info()
			: feature_flags(CAPABILITY_NONE)
		{
			int cpuInfo[4];
			__cpuid(cpuInfo, 1);

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
			__cpuid(cpuInfo, 7);

			feature_flags |= cpuInfo[1] & (1 << 5) ? CAPABILITY_AVX2 : CAPABILITY_NONE;
			feature_flags |= cpuInfo[1] & (1 << 16) ? CAPABILITY_AVX512 : CAPABILITY_NONE;

			//if (use_xrstore && has_avx1)
			//{
			//	// Check if the OS will save the YMM registers
			//	unsigned long long xcrFeatureMask = _xgetbv(_XCR_XFEATURENABLED_MASK);
			//	has_avx1 = (xcrFeatureMask & 0x6) || false;
			//}
		}
		
		bool hasFlag(const capabilities c) const
		{
			return 0 != (this->feature_flags & c);
		}

		void setFlag(const capabilities c, bool enable)
		{
			this->feature_flags = (feature_flags & ~(c)) | ((enable ? 1 : 0) & c);
		}

		bool hasAVX2() const
		{
			return hasFlag(CAPABILITY_AVX1) && hasFlag(CAPABILITY_AVX2);
		}

		bool hasAVX1() const
		{
			return hasFlag(CAPABILITY_AVX1);// && !hasFlag(CAPABILITY_AVX2);
		}
		
		bool hasSSE4() const
		{
			return hasFlag(CAPABILITY_SSE42) || hasFlag(CAPABILITY_SSE41);
		}

		bool hasSSE4FMA() const
		{
			return hasSSE4() && (hasFlag(CAPABILITY_FMA3) || hasFlag(CAPABILITY_FMA4));
		}
		
		bool hasSSSE3() const
		{
			return hasFlag(CAPABILITY_SSSE3) && hasSSE3();
		}

		bool hasSSE3() const
		{
			return hasFlag(CAPABILITY_SSE3) && hasSSE2();
		}

		bool hasSSE2() const
		{
			return hasFlag(CAPABILITY_SSE2);
		}

		static bool hasFPU()
		{
			return true;
		}

		friend ostream& operator<<(ostream& os, const system_info& dt);
	};

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

	// Used to distinguish branch-dependant code at compile-time
	FEATURE
		struct dispatcher
	{
		static constexpr int feature_flags = featuremask();

		static constexpr bool has_sse			= 0 != (featuremask() & CAPABILITY_SSE2) || (featuremask() & CAPABILITY_SSE41);
		static constexpr bool has_fma			= 0 != (featuremask() & CAPABILITY_FMA3) || (featuremask() & CAPABILITY_FMA4);
		static constexpr bool has_sse41			= 0 != (featuremask() & CAPABILITY_SSE41);
		static constexpr bool has_sse42			= 0 != (featuremask() & CAPABILITY_SSE42);
		static constexpr bool has_avx			= 0 != (featuremask() & CAPABILITY_AVX1);
		static constexpr bool has_avx2			= 0 != (featuremask() & CAPABILITY_AVX2);
		static constexpr bool has_avx512		= 0 != (featuremask() & CAPABILITY_AVX512);
		static constexpr bool use_fast_float	= 0 != (featuremask() & CAPABILITY_FASTFLOAT);
	};

	// shortcuts
	#define _dispatcher dispatcher<featuremask>

	#define HAS_SSE _dispatcher::has_sse
	#define HAS_FMA _dispatcher::has_fma
	#define HAS_SSE41 _dispatcher::has_sse41
	#define HAS_SSE42 _dispatcher::has_sse42
	#define HAS_AVX1 _dispatcher::has_avx
	#define HAS_AVX2 _dispatcher::has_avx2
	#define HAS_AVX512 _dispatcher::has_avx512
	#define USE_FAST_FLOAT _dispatcher::use_fast_float

}}