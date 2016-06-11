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
 * @file dependencies.h
 *
 * @brief dependencies for most submodules
 *
 *
 * Here are the dependencies for branch-specific implementations.
 * For example:
 * -- your super duper cpu-extension-specific file --
 * #include "dependencies.h"
 * -- your code
 */


#include <type_traits>
#include "intrin.h"
#include "macros.h"
#include "basic_functions.h"
#include "system_info.h"

///@{
/// alias removing the need to write dispatch_mask

#define _int4 int4<dispatch_mask>
#define _int4x2 int4x2<dispatch_mask>
#define _int8 int8<dispatch_mask>

#define _float4 float4<dispatch_mask>
#define _float8 float8<dispatch_mask>

///@}

