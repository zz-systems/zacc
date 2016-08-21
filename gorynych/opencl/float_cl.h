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
 * @file float_cl.h
 *
 * @brief OPENCL float32 wrapper
 */

#include "../dependencies.h"

namespace zzsystems { namespace gorynych {

	DISPATCHED struct int_cl;

    /**
	 * @struct float_cl
	 * @brief OpenCL float32 abstraction
	 *
	 * Provides a wrapper around the OpenCL float32 type
	 *
	 * @remark OpenCL
	 * @since version 1.1.0
	 */
	DISPATCHED struct float_cl
	{	

		/// default constructor
		float_cl() = default;

		/// constructor for a single int
		float_cl(const int rhs)		noexcept {}
		/// constructor for a single float
		float_cl(const float rhs)		noexcept {}
		/// constructor for a single double
		float_cl(const double rhs)	noexcept {}				

		/// copy constructor for float vector
		float_cl(const _float_cl&	rhs) noexcept;
		/// copy constructor for int vector
		float_cl(const _int_cl&	rhs) noexcept;

		//float_cl(const double4&	rhs);

		/// @brief define scalar<->vector operators.
		/// @remark Don't forget to extend the macro when you add new operators
		SCALAR_VECTOR_CVT_OP_DEFS(float, float_cl)
    };

	DISPATCHED_RET(bool, HAS_OPENCL) inline is_set(const _float_cl VREF a)
	{
		return false;
	}

	// Arithmetic ======================================================================================================
	/// @name arithmetic operators
	/// @{

	/**
	 * @brief negation operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_OP(-, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief add operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(+, _float_cl, HAS_OPENCL)
	{
		 return 0;
	}

	/**
	 * @brief sub operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(-, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief mul operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(*, _float_cl, HAS_OPENCL)
	{
		 return 0;
	}

	/**
	 * @brief div (precise)
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(/, _float_cl, HAS_OPENCL && !USE_FAST_FLOAT)
	{
		return 0;
	}

	/**
	 * @brief div operator (faster, lower precision!)
	 * @relates float_cl
	 * @remark OPENCL
	 * @remark FAST_FLOAT
	 */
	DISPATCHED_BIN_OP(/ , _float_cl, HAS_OPENCL && USE_FAST_FLOAT)
	{
		return 0;
	}

	/**
	 * @brief fused multiply add
	 * @relates float_cl
	 * @remark OPENCL
	*/
	DISPATCHED_TRI_FUNC(vfmadd, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief fused multiply sub
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_TRI_FUNC(vfmsub, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	///@}
		
	// Logical =========================================================================================================

	/// @name logical & comparison operators
	/// @{

	/**
	 * @brief Greater than 
	 * @relates float_cl
	 * @remark OPENCL
	 * @returns boolean vector (as float_cl)
	 */
	DISPATCHED_BIN_OP(>, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief Less than
	 * @relates float_cl
	 * @remark OPENCL
	 * @returns boolean vector (as float_cl)
	 */
	DISPATCHED_BIN_OP(< , _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief Equality
	 * @relates float_cl
	 * @remark OPENCL
	 * @returns boolean vector (as float_cl)
	 */
	DISPATCHED_BIN_OP(==, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief Non-equality
	 * @relates float_cl
	 * @remark OPENCL
	 * @returns boolean vector (as float_cl)
	 */
	DISPATCHED_BIN_OP(!=, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief branchless if-then-else
	 * @relates float_cl
	 * @param a selector mask
	 * @param b then-branch-value
	 * @param c else-branch-value
	 * @remark OPENCL
	 */
	DISPATCHED_TRI_FUNC(vsel, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}

	// Bitwise ========================================================================================================

	/// @name bitwise operators
	/// @{

	/**
	 * @brief not
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_OP(~, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief or
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(|, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief and
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(&, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief xor
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(^, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}
	// Bitwise aliases (compatibility with scalar logical op's) ========================================================

	/**
	 * @name bitwise aliases
	 *
	 * compatibility with scalar logical operators
	 */
	/// @{

	/**
	 * @brief logical not (alias)
	 * @relates float_cl
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 * @ref _float_cl operator~(const _float_cl a)
	 * @remark OPENCL
	 */
	DISPATCHED_UN_OP(!, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief logical or (alias)
	 * @relates float_cl
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 * @ref _float_cl operator|(const _float_cl a, const _float_cl b)
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(|| , _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief logical and (alias)
	 * @relates float_cl	 *
	 * @ref _float_cl operator&(const _float_cl a, const _float_cl b)
	 * @remark OPENCL
	 * used in conjuction with logical expressions to stay compatible
	 * to standard scalar operations
	 */
	DISPATCHED_BIN_OP(&&, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}

	// Basic math functions ============================================================================================

	/// @name basic math functions
	/// @{

	/**
	 * @brief precise square root
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vsqrt, _float_cl, HAS_OPENCL && !USE_FAST_FLOAT)
	{
		return 0;
	}

	/**
	 * @brief fast square root
	 * @relates float_cl
	 * is implemented using float fast sqrt and cast back
	 * @remark OPENCL, FAST_FLOAT
	 */
	DISPATCHED_UN_FUNC(vsqrt, _float_cl, HAS_OPENCL && USE_FAST_FLOAT)
	{
		return 0;
	}

	/**
	 * @brief Absolute value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vabs, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief Minumum value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_FUNC(vmin, _float_cl, HAS_OPENCL)
	{
		 return 0;
	}

	/**
	 * @brief Maximum value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_FUNC(vmax, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}

	// Rounding =======================================================================================================

	/// @name rounding functions
	/// @{

	/**
	 * @brief truncate value to *.0
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vtrunc, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief floor value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vfloor, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief ceil value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vceil, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/**
	 * @brief round value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vround, _float_cl, HAS_OPENCL)
	{
		return 0;
	}

	/// @}
}}