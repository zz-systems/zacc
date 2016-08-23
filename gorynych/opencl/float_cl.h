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
#include <sstream>

#include "../dependencies.h"
#include "../util/uuid.h"

namespace zzsystems { namespace gorynych {

	DISPATCHED struct int_cl;

	DISPATCHED struct float_cl;
	DISPATCHED std::string var(const _float_cl &a);

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
		stringstream expression;
		string name;
		bool is_expression = false;

		/// default constructor
		float_cl()
		{
			name = random_var_name();
			expression << name;
		}

		float_cl(stringstream &builder)
		{
			expression << " " << builder.str();
		}

		float_cl(string &expression)
		{
			this->expression << " " << expression;
		}

		float_cl(const char* expression)
		{
			is_expression = true;
			this->expression << expression;
		}
		/// constructor for a single int
		float_cl(const int rhs, bool immediate = false) : float_cl()
		{
			expression << " = " << rhs << ";" << endl; 
		}
		/// constructor for a single float
		float_cl(const float rhs, bool immediate = false) : float_cl()
		{
			expression << " = " << rhs << ";" << endl;
		}

		/// constructor for a single double
		float_cl(const double rhs, bool immediate = false)	: float_cl()
		{
			expression << " = " << rhs << ";" << endl;
		}				

		/// copy constructor for float vector
		float_cl(const _float_cl&	rhs);
		/// copy constructor for int vector
		float_cl(const _int_cl&	rhs);

		//float_cl(const double4&	rhs);

		/// @brief define scalar<->vector operators.
		/// @remark Don't forget to extend the macro when you add new operators
		//SCALAR_VECTOR_CVT_OP_DEFS(float, float_cl)
		//SCALAR_VECTOR_CVT_OP_DEFS(int, float_cl_imm)
    };

	DISPATCHED struct float_cl_imm
	{	
		stringstream expression;
		string name;
		bool is_expression = false;
	};

	DISPATCHED std::string var(const _float_cl &a) 
	{
		 return a.is_expression ? a.expression.str() : a.name;
	}

	DISPATCHED_RET(bool, HAS_OPENCL) inline is_set(const _float_cl VREF a)
	{
//		builder << function("bool", "is_set", "float value") << function_body("return value != 0");
//		builder << invoke("is_set", var(a));

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
		auto result = _float_cl("");
			result.expression << "( " << "-" << var(a) << " )";
		return result;
	}

	/**
	 * @brief negation operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	// DISPATCHED_RET(_float_cl, HAS_OPENCL) operator-(float a)
	// {
	// 	auto result = _float_cl("");
	// 		result.expression << "( " << "-" << a << " )";
	// 	return result;
	// }

	/**
	 * @brief add operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(+, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << var(a) << " + " << var(b);
		return result;
	}

	/**
	 * @brief add operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_RET(_float_cl, HAS_OPENCL) operator+(const _float_cl &a, float b)
	{
		auto result = _float_cl("");
			result.expression << var(a) << " + " << b;
		return result;
	}

	/**
	 * @brief negation operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_RET(_float_cl, HAS_OPENCL) operator+(float a, const _float_cl &b)
	{
		auto result = _float_cl("");
			result.expression << a << " + " << var(b);
		return result;
	}


	/**
	 * @brief sub operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(-, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << "( " << var(a) << " - " << var(b) << " )";
		return result;
	}

	/**
	 * @brief mul operator
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(*, _float_cl, HAS_OPENCL)
	{
		 auto result = _float_cl("");
			result.expression << "( " << var(a) << " * " << var(b) << " )";
		return result;
	}

	/**
	 * @brief div (precise)
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(/, _float_cl, HAS_OPENCL && !USE_FAST_FLOAT)
	{
		auto result = _float_cl("");
			result.expression << "( " << var(a) << " / " << var(b) << " )";
		return result;
	}

	/**
	 * @brief div operator (faster, lower precision!)
	 * @relates float_cl
	 * @remark OPENCL
	 * @remark FAST_FLOAT
	 */
	DISPATCHED_BIN_OP(/ , _float_cl, HAS_OPENCL && USE_FAST_FLOAT)
	{
		auto result = _float_cl("");
			result.expression << "( " << var(a) << " / " << var(b) << " )";
		return result;
	}

	/**
	 * @brief fused multiply add
	 * @relates float_cl
	 * @remark OPENCL
	*/
	DISPATCHED_TRI_FUNC(vfmadd, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << invoke("fma", var(a), var(b), var(c));
		return result;
	}

	/**
	 * @brief fused multiply sub
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_TRI_FUNC(vfmsub, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << invoke("fma", var(a), var(b), var(-c));
		return result;
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
		auto result = _float_cl("");
			result.expression << var(a) << " > " << var(b);
		return result;
	}

	/**
	 * @brief Less than
	 * @relates float_cl
	 * @remark OPENCL
	 * @returns boolean vector (as float_cl)
	 */
	DISPATCHED_BIN_OP(< , _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << var(a) << " < " << var(b);
		return result;
	}

	/**
	 * @brief Equality
	 * @relates float_cl
	 * @remark OPENCL
	 * @returns boolean vector (as float_cl)
	 */
	DISPATCHED_BIN_OP(==, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << var(a) << " == " << var(b);
		return result;
	}

	/**
	 * @brief Non-equality
	 * @relates float_cl
	 * @remark OPENCL
	 * @returns boolean vector (as float_cl)
	 */
	DISPATCHED_BIN_OP(!=, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << var(a) << " != " << var(b);
		return result;
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
		auto result = _float_cl("");
			result.expression << var(a) << " ? " << var(b) << " : " << var(c);
		return result;
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
		auto result = _float_cl("");
			result.expression << " ~" << var(a);
		return result;
	}

	/**
	 * @brief or
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(|, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << var(a) << " | " << var(b);
		return result;
	}

	/**
	 * @brief and
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(&, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << var(a) << " & " << var(b);
		return result;
	}

	/**
	 * @brief xor
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_OP(^, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << var(a) << " ^ " << var(b);
		return result;
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
		return ~a;
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
		return a | b;
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
		return a & b;
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
		auto result = _float_cl("");
			result.expression << invoke("sqrt", var(a));
		return result;
	}

	/**
	 * @brief fast square root
	 * @relates float_cl
	 * is implemented using float fast sqrt and cast back
	 * @remark OPENCL, FAST_FLOAT
	 */
	DISPATCHED_UN_FUNC(vsqrt, _float_cl, HAS_OPENCL && USE_FAST_FLOAT)
	{
		auto result = _float_cl("");
			result.expression << invoke("sqrt", var(a));
		return result;
	}

	/**
	 * @brief Absolute value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vabs, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << invoke("abs", var(a));
		return result;
	}

	/**
	 * @brief Minumum value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_FUNC(vmin, _float_cl, HAS_OPENCL)
	{
		 auto result = _float_cl("");
			result.expression << invoke("min", var(a), var(b));
		return result;
	}

	/**
	 * @brief Maximum value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_BIN_FUNC(vmax, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << invoke("max", var(a), var(b));
		return result;
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
		auto result = _float_cl("");
			result.expression << invoke("trunc", var(a));
		return result;
	}

	/**
	 * @brief floor value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vfloor, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << invoke("floor", var(a));
		return result;
	}

	/**
	 * @brief ceil value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vceil, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << invoke("ceil", var(a));
		return result;
	}

	/**
	 * @brief round value
	 * @relates float_cl
	 * @remark OPENCL
	 */
	DISPATCHED_UN_FUNC(vround, _float_cl, HAS_OPENCL)
	{
		auto result = _float_cl("");
			result.expression << invoke("round", var(a));
		return result;
	}

	/// @}
}}