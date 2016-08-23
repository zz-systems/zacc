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
 * @file int_cl.h
 *
 * @brief OPENCL int32 wrapper
 */

#include "../dependencies.h"

namespace zzsystems { namespace gorynych {

	//using clstream = std::stringstream;

	DISPATCHED struct float_cl;

    /**
	 * @struct cl_int
	 * @brief OpenCL int32 abstraction
	 *
	 * Provides a wrapper around the OpenCL int32 type
	 *
	 * @remark OpenCL
	 * @since version 1.1.0
	 */
	DISPATCHED struct int_cl
	{
		//clstream stream;
		string name;

		/// default constructor
		int_cl() {};

		/// constructor for a single int
		int_cl(const int rhs)			 {  }
		
		/// converting constructor for float vector
		int_cl(const _float_cl&	rhs) ;
		/// copy constructor for int vector
		int_cl(const _int_cl&	rhs) ;
		//int_cl(const double4&	rhs);

		/// @brief define scalar<->vector operators.
		/// @remark Don't forget to extend the macro when you add new operators
		SCALAR_VECTOR_CVT_OP_DEFS(int, int_cl)

    };

	DISPATCHED_RET(bool, HAS_OPENCL) inline is_set(const _int_cl VREF a)
	{
		return false;
	}

	// Arithmetic ======================================================================================================

	/// @name arithmetic operators / functions
	/// @{
	
	/// @brief negation
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_UN_OP(-, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief add
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_BIN_OP(+, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief sub
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_BIN_OP(-, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief mul
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_BIN_OP(*, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief div is implemented using float div and cast back
	/// @relates int_cl
	/// @remark AVX1, OPENCL
	DISPATCHED_BIN_OP(/, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}

	// Logical =========================================================================================================

	/// @name logical operators
	/// @{

	/// @brief Greater than
	/// @relates int_cl
	/// @remark OPENCL
	/// @returns boolean vector (as int_cl)
	DISPATCHED_BIN_OP(>, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief Less than
	/// @relates int_cl
	/// @remark OPENCL
	/// @returns boolean vector (as int_cl)
	DISPATCHED_BIN_OP(<, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief Equality
	/// @relates int_cl
	/// @remark OPENCL
	/// @returns boolean vector (as int_cl)
	DISPATCHED_BIN_OP(==, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief Non-equality
	/// @relates int_cl
	/// @remark OPENCL
	/// @returns boolean vector (as int_cl)
	DISPATCHED_BIN_OP(!=, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief branchless if-then-else
	/// @relates int_cl
	/// @param a selector mask
	/// @param b then-branch-value
	/// @param c else-branch-value
	/// @remark OPENCL
	DISPATCHED_TRI_FUNC(vsel, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}

	// Bitwise =========================================================================================================

	/// @name bitwise operators
	/// @{

	/// @brief not
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_UN_OP(~, _int_cl, HAS_OPENCL)
	{
		return 0;
	}
	
	/// @brief or
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_BIN_OP(|, _int_cl, HAS_OPENCL)
	{
		return 0;
	}
	
	/// @brief and
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_BIN_OP(&, _int_cl, HAS_OPENCL)
	{
		return 0;
	}
	
	/// @brief xor
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_BIN_OP(^, _int_cl, HAS_OPENCL)
	{
		return 0;
	}
	
	/// @brief right shift (logical)
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_SHIFT_OP(>> , _int_cl, HAS_OPENCL)
	{
		return 0;
	}
	
	/// @brief left shift (logical)
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_SHIFT_OP(<< , _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}

	// Bitwise aliases (compatibility with scalar logical op's) ========================================================

	/// @name bitwise aliases
	/// @{
	
	/// @brief Bitwise not (alias) operator
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int_cl operator~(const _int_cl a)
	/// @remark OPENCL
	DISPATCHED_UN_OP(!, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief Bitwise or (alias) operator
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int_cl operator|(const _int_cl a, const _int_cl b)
	/// @remark OPENCL
	DISPATCHED_BIN_OP(|| , _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	
	/// @brief Bitwise and (alias) operator
	/// @relates int_cl
	/// used in conjuction with logical expressions to stay compatible
	/// to standard scalar operations
	/// @ref _int_cl operator&(const _int_cl a, const _int_cl b)
	/// @remark OPENCL
	DISPATCHED_BIN_OP(&&, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}
		
	// Basic math functions ============================================================================================

	/// @name basic math functions
	/// @{
		
	/// @brief precise square root
	/// @relates int_cl
	/// implemented using float sqrt and cast back
	/// @remark OPENCL
	DISPATCHED_UN_FUNC(vsqrt, _int_cl, HAS_OPENCL && !USE_FAST_FLOAT)
	{
		return 0;
	}
	
	/// @brief fast square root function
	/// @relates int_cl
	/// implemented using float sqrt and cast back
	/// @remark OPENCL, FAST_FLOAT
	DISPATCHED_UN_FUNC(vsqrt, _int_cl, HAS_OPENCL && USE_FAST_FLOAT)
	{
		return 0;		
	}
	
	/// @brief Absolute value
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_UN_FUNC(vabs, _int_cl, HAS_OPENCL)
	{
		return 0;
	}
	
	/// @brief Minumum value
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_BIN_FUNC(vmin, _int_cl, HAS_OPENCL)
	{
		return 0;
	}
	
	/// @brief Maximum value
	/// @relates int_cl
	/// @remark OPENCL
	DISPATCHED_BIN_FUNC(vmax, _int_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}
}}