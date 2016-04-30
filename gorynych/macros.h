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

// This file defines the most important macro black magic used in gorynych and derived projects. 

namespace zzsystems { namespace gorynych {
	
	// Basic stuff ------------------------------------------------------------------------------------------------------
	
	// memory alignment
	#if _MSC_VER < 1900  
		#define ALIGN(bytes) __declspec(align(bytes))
	#else 
		#define ALIGN(bytes) alignas(bytes)
	#endif

	#define FORCEINLINE __forceinline

	// shortcut (writing that 100000 times sucks)
	#define SIMD_T vreal, vint

	// shortcut (one template type)
	#define ANY(type) template<typename type>

	// shortcut (two template types)
	#define ANY2(type1, type2) template<typename type1, typename type2>
	//-------------------------------------------------------------------------------------------------------------------

	// vectorized type SFINAE stuff -------------------------------------------------------------------------------------
	// define checked floating and integral type to use on SIMD-enabled functions/types. 
	#define SIMD_ENABLE(floatType, intType) \
		template<	typename floatType	= std::enable_if<std::is_floating_point<floatType>::value, floatType>::type, \
					typename intType	= std::enable_if<std::is_integral<intType>::value, intType>::type>

	#define SIMD_ENABLED \
		SIMD_ENABLE(vreal, vint)

	// define checked floating type to use on SIMD-enabled functions/types. 
	#define SIMD_ENABLE_F(floatType) \
		template<typename floatType = std::enable_if<std::is_floating_point<floatType>::value, floatType>::type>
	
	// shortcut(vreal): define checked integral type to use on SIMD-enabled functions/types. 
	#define SIMD_ENABLED_F SIMD_ENABLE_F(vreal)

	// define checked integral type to use on SIMD-enabled functions/types. 
	#define SIMD_ENABLE_I(intType) \
		template<typename intType = std::enable_if<std::is_integral<intType>::value, intType>::type>
	
	// shortcut(vint): define checked integral type to use on SIMD-enabled functions/types. 
	#define SIMD_ENABLED_I SIMD_ENABLE_I(vint)

	// Featuremask template. Important for static branch dispatching
	#define FEATURE template<typename featuremask>

	// shortcut with return type
	#define FEATURE_RET(TType, condition) \
		FEATURE typename std::enable_if<condition, TType>::type 
	//-------------------------------------------------------------------------------------------------------------------
	
	// Argument defintion, passing --------------------------------------------------------------------------------------
	
	// shortcut: unary argument list
	#define UN_ARG  (a.val)
	
	// shortcut: binary argument list
	#define BIN_ARG (a.val, b.val)
	
	// shortcut: ternary argument list (third one is an option value)
	#define TRI_ARG_OPT(opt) (a.val, b.val, opt)
	
	// shortcut: binary argument list from duplicated unary argument
	#define BIN_ARG_DUP (a.val, a.val)

	// Constructor arguments (4-vector)
	#define VARGS4(type) const type& _0, const type& _1, const type& _2, const type& _3
	
	// Pass 4 constructor arguments
	#define VPASS4 _3, _2, _1, _0
	
	// Pass 4 high args
	#define VPASS4_HI _7, _6, _5, _4

	// Constructor arguments (8-vector)
	#define VARGS8(type) const type& _0, const type& _1, const type& _2, const type& _3, const type& _4, const type& _5, const type& _6, const type& _7
	
	// Pass 8 constructor arguments
	#define VPASS8 _7, _6, _5, _4, _3, _2, _1, _0
	//-------------------------------------------------------------------------------------------------------------------

	// Operator declarations --------------------------------------------------------------------------------------------
	
	// Assignment operator
	#define ASSIGN_OP(op, type) \
		inline type& operator op(type &a, const type &b)

	// Converting assignment operator
	#define ASSIGN_OP2(op, type1, type2) \
		inline type1& operator op(type1 &a, const type2 &b)

	// Unary operator
	#define UN_OP(op, type) \
		inline type operator op(const type &a)	

	// Binary operator
	#define BIN_OP(op, type) \
		inline type operator op(const type &a, const type &b)

	// Shift operator 
	#define SHIFT_OP(op, type) \
		inline type operator op(const type &a, const int sa)

	// Converting unary operator
	#define UN_OP_STUB(op, type, convertable) \
		inline friend const type operator op(const convertable &a)	{ return op static_cast<type>(a); }		

	// Converting binary operator (A <- A op (A)B)
	#define BIN_OP_STUB_AB(op, type, convertable) \
		inline friend type operator op(const type &a, const convertable &b) { return a op static_cast<type>(b); }

	// Converting binary operator (A <- (A)B op A)
	#define BIN_OP_STUB_BA(op, type, convertable) \
		inline friend type operator op(const convertable &a, const type &b) { return static_cast<type>(a) op b; }

	// Permutated pair of converting binary operators
	#define BIN_OP_STUB(op, type, convertable) \
		BIN_OP_STUB_AB(op, type, convertable) \
		BIN_OP_STUB_BA(op, type, convertable)

	// Permutated pair of templated converting binary operators
	#define BIN_OP_STUB_ANY(op, type) \
		ANY(convertable) BIN_OP_STUB_AB(op, type, convertable) \
		ANY(convertable) BIN_OP_STUB_BA(op, type, convertable)

	// shortcut: operator declaration
	#define FEATURE_OP(op, TType, condition) \
		FEATURE_RET(TType, condition) inline operator op

	// shortcut: unary operator declaration
	#define FEATURE_UN_OP(op, TType, condition) \
		FEATURE_OP(op, TType, condition) (const TType &a)	

	// shortcut: binary operator declaration
	#define FEATURE_BIN_OP(op, TType, condition) \
		FEATURE_OP(op, TType, condition) (const TType &a, const TType &b)

	// shortcut: shift operator declaration
	#define FEATURE_SHIFT_OP(op, TType, condition) \
		FEATURE_OP(op, TType, condition) (const TType &a, const int sa)
	//-------------------------------------------------------------------------------------------------------------------

	// Function declarations --------------------------------------------------------------------------------------------

	// Shortcut for function declaration
	#define FUNC(name, type) inline type name()

	// unary function 
	#define UN_FUNC(name, type) inline type name(const type &a)

	// binary function
	#define BIN_FUNC(name, type) inline type name(const type &a, const type &b)

	// ternary function
	#define TRI_FUNC(name, type) inline type name(const type &a, const type &b, const type &c)	

	// shortcut: function declaration
	#define FEATURE_FUNC(name, TType, condition) \
		FEATURE_RET(TType, condition) inline name

	// shortcut: unary function declaration
	#define FEATURE_UN_FUNC(name, TType, condition) \
	FEATURE_RET(TType, condition) name(const TType &a)

	// shortcut: binary function declaration
	#define FEATURE_BIN_FUNC(name, TType, condition) \
	FEATURE_RET(TType, condition) name(const TType &a, const TType &b)

	// shortcut: ternary function declaration
	#define FEATURE_TRI_FUNC(name, TType, condition) \
	FEATURE_RET(TType, condition) name(const TType &a, const TType &b, const TType &c)

	//-------------------------------------------------------------------------------------------------------------------

	// Function/Operator bodies -----------------------------------------------------------------------------------------
	
	// Information about selected branch on a per-function/operator basis
	#if defined(ENABLE_DEBUG_FUNC_INSTANCE) //&& defined(__DEBUG)
		#define DEBUG_FUNC_INSTANCE(name) cout << "for " << static_dispatcher<featuremask>::unit_name() << " using: " << name << endl
	#else 
		#define DEBUG_FUNC_INSTANCE {}
	#endif

	// cosmetic...
	#define BODY(expr) return expr

	// body for 1 argument
	#define UN_BODY(intrin) return intrin UN_ARG
	// body for 1 argument, duplicated
	#define UN_BODY_D(intrin) return intrin BIN_ARG_DUP

	// body for 2 arguments
	#define BIN_BODY(intrin) return intrin BIN_ARG
	// body for 2 arguments in reversed order
	#define BIN_BODY_R(intrin) return intrin BIN_ARG

	// body for 3 arguments
	#define TRI_BODY(intrin) return intrin (a.val, b.val, c.val)
	// body for 3 arguments in reversed order
	#define TRI_BODY_R(intrin) return intrin (c.val, b.val, a.val)

	// body for 2 standard and one special argument
	#define TRI_BODY_O(intrin, opt) return intrin TRI_ARG_OPT(opt)

	//-------------------------------------------------------------------------------------------------------------------
}}