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

#include "sse/sse.h"
#include "avx/avx.h"
#include "opencl/opencl.h"
#include "x87/SISD.h"

#include "dependencies.h"

#include "fastload.h"

#ifdef _MSC_VER
// prevent 'decorated name length exceeded, name was truncated'
#pragma warning(disable : 4503)
// prevent 'found Intel(R) Advanced Vector Extensions; consider using / arch:AVX'
#pragma warning(disable : 4752)	
#endif

namespace std
{
	template <class T>
	inline void hash_combine(int& seed, const T& v)
	{
		hash<T> hasher;
		seed ^= hasher(v) + static_cast<int>(0x9e3779b9) + (seed << 6) + (seed >> 2);
	}

	FEATURE
	struct hash<zzsystems::gorynych::_float4>
	{
		typedef zzsystems::gorynych::_float4 argument_type;
		typedef size_t result_type;

		result_type operator()(const argument_type &arg) const
		{
			float *v = zzsystems::gorynych::extract(arg);

			result_type result = 0;

			for (size_t i = 0; i < zzsystems::gorynych::dim<argument_type>(); i++)
				hash_combine<float>(result, v[i]);

			return result;
		}
	};

	FEATURE
	struct hash<zzsystems::gorynych::_float8>
	{
		typedef zzsystems::gorynych::_float8 argument_type;
		typedef size_t result_type;

		result_type operator()(const argument_type &arg) const
		{
			float *v = extract(arg);

			result_type result = 0;

			for (size_t i = 0; i < zzsystems::gorynych::dim<argument_type>(); i++)
				hash_combine<float>(result, v[i]);

			return result;
		}
	};	
}