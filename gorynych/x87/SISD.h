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
 * @file SISD.h
 *
 * @brief Additional x87 wrapper functions and types
 */

#include "../dependencies.h"

namespace zzsystems { namespace gorynych {


	// Memory access: extract, gather, scatter (todo) ==================================================================

	/// extract int scalar value to a memory location
	inline void extract(const int& src, int* target)	{ target[0] = src; }

	/// extract float scalar value to a memory location
	inline void extract(const float& src, float *target)		{ target[0] = src; }

	/// gather int scalar value from a memory location by an index scalar
	inline int vgather(const int* memloc, size_t index)
	{
		return memloc[index];
	}

	/// gather float scalar value from a memory location by an index scalar
	inline float vgather(const float* memloc, size_t index)
	{
		return memloc[index];
	}
}} 