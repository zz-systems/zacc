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
 * @file macros.h
 *
 * @brief This file defines the most important macro and SFINAE black magic
 * used in gorynych and derived projects.
 */

#include <type_traits>

namespace zzsystems { namespace gorynych {


	/// @name traits
	/// @{

	template<typename T>
	struct is_vint : std::false_type {};

	template<typename T>
	struct is_vreal : std::false_type {};

	template<>
	struct is_vint<int> : std::true_type {};

	template<>
	struct is_vreal<float> : std::true_type {};

	template<typename scalar>
	struct __scalar_type
	{
		/// scalar type
		typedef scalar type;
		//scalar value;
		//static_assert(!std::is_same<scalar, void>::value, "not expected");
	};

	template<typename>
	struct scalar_type : public __scalar_type<void>
	{};

	template<>
	struct scalar_type<int> : public __scalar_type<int>
	{};

	template<>
	struct scalar_type<float> : public __scalar_type<float>
	{};

	/// @}

	// Basic stuff =====================================================================================================

	/// @name basic
	/// @{

	/// @deprecated
	#define FORCEINLINE __forceinline

	/// @def SIMD_T
	/// @brief shortcut for vreal, vint
	/// @remark module<vreal, vint> => module<SIMD_T>
	#define SIMD_T vreal, vint

	/// @def ANY(type)
	/// @brief shortcut for one-type template
	#define ANY(type) template<typename type>

	/// @def ANY2(type1, type2)
	/// @brief shortcut for two-type template
	#define ANY2(type1, type2) template<typename type1, typename type2>

	/// @}

	// vectorized type SFINAE stuff ====================================================================================

	/// @name SFINAE helpers
	/// @{

	/// @def VECTORIZED
	/// @brief enables a func, struct, class, whatever to use both float and int vectors
	#define VECTORIZED template<typename vreal, typename vint>

	/// @def VECTORIZED_F
	/// @brief enables a func, struct, class, whatever to use float vectors
	#define VECTORIZED_F template<typename vreal>

	/// @def VECTORIZED_I
	/// @brief enables a func, struct, class, whatever to use int vectors
	#define VECTORIZED_I template<typename vint>

	/// @def VECTORIZED_FUNC_I
	/// @brief shortcut for vectorized integer functions preamble
	#define VECTORIZED_FUNC_I VECTORIZED inline std::enabled_if_t<is_vint<vint>::value && is_vreal<vreal>::value, vint>

	/// @def VECTORIZED_FUNC_F
	/// @brief shortcut for vectorized float functions preamble
	#define VECTORIZED_FUNC_F VECTORIZED inline std::enabled_if_t<is_vint<vint>::value && is_vreal<vreal>::value, vreal>

	/// @def DISPATCHED
	/// @brief Featuremask template. Important for static branch dispatching
	#define DISPATCHED template<typename dispatch_mask>

	/// @def DISPATCHED_RET
	/// @brief shortcut with return type
	#define DISPATCHED_RET(TType, condition) \
		DISPATCHED std::enable_if_t<condition, TType>
	
	/// @}

	// Argument definition, passing ====================================================================================

	/// @name argument helpers
	/// @{

	/// @def UN_ARG
	/// @brief shortcut: unary argument list
	#define UN_ARG (a.val)

	/// @def BIN_ARG
	/// @brief shortcut: binary argument list
	#define BIN_ARG (a.val, b.val)

	/// @def TRI_ARG_OPT
	/// @brief shortcut: ternary argument list (third one is an option value)
	/// @param opt usually a non-vector value
	#define TRI_ARG_OPT(opt) (a.val, b.val, opt)

	/// @def BIN_ARG_DUP
	/// @brief shortcut: binary argument list from duplicated unary argument
	#define BIN_ARG_DUP (a.val, a.val)

	/// @def VARGS4(type)
	/// @brief shortcut: 4 (Constructor) arguments of the same type
	#define VARGS4(type) const type& _3, const type& _2, const type& _1, const type& _0

	/// @def VPASS4
	/// @brief shortcut: Pass 4 (constructor) arguments
	#define VPASS4 _3, _2, _1, _0

	/// @def VPASS4_HI
	/// @brief shortcut: Pass 4 high (constructor) arguments
	#define VPASS4_HI _7, _6, _5, _4

	/// @def VARGS8(type)
	/// @brief shortcut: 8 (Constructor) arguments of the same type
	#define VARGS8(type) const type& _7, const type& _6, const type& _5, const type& _4, \
        				 const type& _3, const type& _2, const type& _1, const type& _0

	/// @def VPASS8
	/// @brief shortcut: Pass 8 (constructor) arguments
	#define VPASS8 _7, _6, _5, _4, _3, _2, _1, _0

	/// @def DUP4(val)
	/// @brief shortcut: replicates @a val 4 times
	#define DUP4(val) val, val, val, val

	/// @def DUP8(val)
	/// @brief shortcut: replicates @a val 8 times
	#define DUP8(i) DUP4(i), DUP4(i)

	/// @}

	// Operator declarations ===========================================================================================

	/// @name operator declaration helpers
	/// @{

	/// @def ASSIGN_OP(op, type)
	/// @brief shortcut: Assignment operator head
	/// @param op operator
	/// @param type return and argument type
	#define ASSIGN_OP(op, type) \
		inline type& operator op(type &a, const type &b)

	/// @def ASSIGN_OP2(op, type1, type2)
	/// @brief shortcut: Converting assignment operator head
	/// @param op operator
	/// @param type1 return and argument a type
	/// @param type2 argument b type
	#define ASSIGN_OP2(op, type1, type2) \
		inline type1& operator op(type1 &a, const type2 &b)

	/// @def UN_OP(op, type)
	/// @brief shortcut: unary operator head
	/// @param op operator
	/// @param type return and argument type
	#define UN_OP(op, type) \
		inline type operator op(const type a)

	/// @def BIN_OP(op, type)
	/// @brief shortcut: binary operator head
	/// @param op operator
	/// @param type return and argument type
	#define BIN_OP(op, type) \
		inline type operator op(const type a, const type b)

	/// @def SHIFT_OP(op, type)
	/// @brief shortcut: shift operator head
	/// @param op operator
	/// @param type return and argument type
	#define SHIFT_OP(op, type) \
		inline type operator op(const type a, const int sa)

	/// @def UN_OP_STUB(op, type, convertable)
	/// @brief shortcut: Converting unary operator
	/// @param op operator
	/// @param type return and argument a type
	/// @param convertable argument b type
	#define UN_OP_STUB(op, type, convertable) \
        /** @fn operator##op##() */ \
		/** @brief unary op operator */ \
		/** Used for scalar<->vector compatibility */ \
		/** @param a scalar */ \
		/** @returns vector value (type) */ \
		inline friend const type operator op(const convertable a)	{ return op static_cast<type>(a); }

	/// @def BIN_OP_STUB_AB(op, type, convertable)
	/// @brief shortcut: Converting binary operator (A <- A op (A)B)
	/// @param op operator
	/// @param type return and argument a type
	/// @param convertable argument b type
	#define BIN_OP_STUB_AB(op, type, convertable) \
        /** @fn operator##op##() */ \
		/** @brief binary op operator */ \
		/** Used for scalar<->vector compatibility */ \
		/** @param a vector */ \
		/** @param b scalar */ \
		/** @returns vector value (type) */ \
		inline friend type operator op(const type &a, const convertable &b) { return a op static_cast<type>(b); }

	/// @def BIN_OP_STUB_BA(op, type, convertable)
	/// @brief shortcut: Converting binary operator (A <- (A)B op A)
	/// @param op operator
	/// @param type return and argument a type
	/// @param convertable argument b type
	#define BIN_OP_STUB_BA(op, type, convertable) \
        /** @fn operator##op##() */ \
		/** @brief binary op operator */ \
		/** Used for scalar<->vector compatibility */ \
		/** @param a scalar */ \
		/** @param b vector */ \
		/** @returns vector value (type) */ \
		inline friend type operator op(const convertable &a, const type &b) { return static_cast<type>(a) op b; }

	/// @def BIN_OP_STUB(op, type, convertable)
	/// @brief shortcut: Permutated pair of converting binary operators
	/// @param op operator
	/// @param type return and argument a type
	/// @param convertable argument b type
	#define BIN_OP_STUB(op, type, convertable) \
		BIN_OP_STUB_AB(op, type, convertable) \
		BIN_OP_STUB_BA(op, type, convertable)

	/// @def BIN_OP_STUB_ANY(op, type)
	/// @brief shortcut: Permutated pair of templated converting binary operators
	/// @param op operator
	/// @param type return and argument a type
	#define BIN_OP_STUB_ANY(op, type) \
		ANY(convertable) BIN_OP_STUB_AB(op, type, convertable) \
		ANY(convertable) BIN_OP_STUB_BA(op, type, convertable)

	/// @def DISPATCHED_OP(op, type, condition)
	/// @brief shortcut: Dispatched operator header (without args)
	/// @param op operator
	/// @param type return and argument type
	/// @param condition SFINAE enable_if condition
	#define DISPATCHED_OP(op, type, condition) \
		DISPATCHED_RET(type, condition) inline operator op

	/// @def DISPATCHED_UN_OP(op, type, condition)
	/// @brief shortcut: Dispatched unary operator header
	/// @param op operator
	/// @param type return and argument type
	/// @param condition SFINAE enable_if condition
	#define DISPATCHED_UN_OP(op, type, condition) \
		DISPATCHED_OP(op, type, condition) (const type a)

	/// @def DISPATCHED_BIN_OP(op, type, condition)
	/// @brief shortcut: Dispatched binary operator header
	/// @param op operator
	/// @param type return and argument type
	/// @param condition SFINAE enable_if condition
	#define DISPATCHED_BIN_OP(op, type, condition) \
		DISPATCHED_OP(op, type, condition) (const type a, const type b)

	/// @def DISPATCHED_SHIFT_OP(op, type, condition)
	/// @brief shortcut: Dispatched shift operator header
	/// @param op operator
	/// @param type return and argument type
	/// @param condition SFINAE enable_if condition
	#define DISPATCHED_SHIFT_OP(op, type, condition) \
		DISPATCHED_OP(op, type, condition) (const type a, const int sa)

	/// @}

	// Function declarations ===========================================================================================

	/// @name function declaration helpers
	/// @{

	/// @def FUNC(name, type)
	/// @brief shortcut: function header (empty args)
	/// @param name function name
	/// @param type return type
	#define FUNC(name, type) inline type name()

	/// @def UN_FUNC(name, type)
	/// @brief shortcut: unary function header
	/// @param name function name
	/// @param type return and argument type
	#define UN_FUNC(name, type) inline type name(const type &a)

	/// @def BIN_FUNC(name, type)
	/// @brief shortcut: binary function header
	/// @param name function name
	/// @param type return and argument type
	#define BIN_FUNC(name, type) inline type name(const type &a, const type &b)

	/// @def TRI_FUNC(name, type)
	/// @brief shortcut: ternary function header
	/// @param name function name
	/// @param type return and argument type
	#define TRI_FUNC(name, type) inline type name(const type &a, const type &b, const type &c)	

	/// @def DISPATCHED_FUNC(name, type, condition)
	/// @brief shortcut: Dispatched function header (without args)
	/// @param name function name
	/// @param type return type
	/// @param condition SFINAE enable_if condition
	#define DISPATCHED_FUNC(name, type, condition) \
		DISPATCHED_RET(type, condition) inline name

	/// @def DISPATCHED_UN_FUNC(name, type, condition)
	/// @brief shortcut: Dispatched unary function header
	/// @param name function name
	/// @param type return and argument type
	/// @param condition SFINAE enable_if condition
	#define DISPATCHED_UN_FUNC(name, type, condition) \
		DISPATCHED_RET(type, condition) name(const type a)

	/// @def DISPATCHED_BIN_FUNC(name, type, condition)
	/// @brief shortcut: Dispatched binary function header
	/// @param name function name
	/// @param type return and argument type
	/// @param condition SFINAE enable_if condition
	#define DISPATCHED_BIN_FUNC(name, type, condition) \
		DISPATCHED_RET(type, condition) name(const type a, const type b)

	/// @def DISPATCHED_TRI_FUNC(name, type, condition)
	/// @brief shortcut: Dispatched ternary function header
	/// @param name function name
	/// @param type return and argument type
	/// @param condition SFINAE enable_if condition
	#define DISPATCHED_TRI_FUNC(name, type, condition) \
		DISPATCHED_RET(type, condition) name(const type a, const type b, const type c)

	/// @}
	// Function/Operator bodies ========================================================================================

	/// @name function / operator bodies
	/// @{

	/// @def DEBUG_FUNC_INSTANCE(name)
	/// @brief: Information about selected branch on a per-function/operator basis
	#if defined(ENABLE_DEBUG_FUNC_INSTANCE) //&& defined(__DEBUG)
		#define DEBUG_FUNC_INSTANCE(name) cout << "for " << static_dispatcher<dispatch_mask>::unit_name() << " using: " << name << endl
	#else 
		#define DEBUG_FUNC_INSTANCE {}
	#endif

	/// @def BODY(expr)
	/// @brief Returns the supplied expression.
	/// Expression may be intercepted in the future for debug purposes,
	/// For now it's only cosmetic
	/// @returns supplied expression
	#define BODY(expr) return expr

	/// @def UN_BODY(func)
	/// @brief shortcut: function / operator call with 1 argument
	#define UN_BODY(func) BODY((func UN_ARG))

	/// @def UN_BODY_D(func)
	/// @brief shortcut: function / operator call with 2 arguments (1 duplicated)
	#define UN_BODY_D(func) BODY((func BIN_ARG_DUP))

	/// @def BIN_BODY(func)
	/// @brief shortcut: function / operator call with 2 arguments
	#define BIN_BODY(func) BODY((func BIN_ARG))

	/// @def BIN_BODY_R(func)
	/// @brief shortcut: function / operator call with 2 arguments (reversed)
	#define BIN_BODY_R(func) BODY((func (b.val, a.val)))

	/// @def TRI_BODY(func)
	/// @brief shortcut: function / operator call with 3 arguments
	#define TRI_BODY(func) BODY((func (a.val, b.val, c.val)))

	/// @def TRI_BODY_R(func)
	/// @brief shortcut: function / operator call with 3 arguments (reversed)
	#define TRI_BODY_R(func) BODY((func (c.val, b.val, a.val)))

	/// @def TRI_BODY_O(func)
	/// @brief shortcut: function / operator call with 2 standard and 1 special arguments
	/// @param opt special argument type
	#define TRI_BODY_O(func, opt) BODY((func TRI_ARG_OPT(opt)))

	/// @}
	// Converting operators ============================================================================================

	#define DEFINE_ARITHMETIC_CVT_OPS_ANY(target_type) \
        /** @name arithmetic converting operators */\
		/**@{*/\
		BIN_OP_STUB_ANY(+, target_type) \
		BIN_OP_STUB_ANY(-, target_type) \
		BIN_OP_STUB_ANY(*, target_type) \
		BIN_OP_STUB_ANY(/ , target_type) \
		/** @} */

	#define DEFINE_BITWISE_CVT_OPS_ANY(target_type) \
        /** @name arithmetic converting operators */\
		/**@{*/\
		BIN_OP_STUB_ANY(^, target_type) \
		BIN_OP_STUB_ANY(|, target_type) \
		BIN_OP_STUB_ANY(&, target_type) \
		/** @} */

	#define DEFINE_LOGIC_CVT_OPS_ANY(target_type) \
        /** @name arithmetic converting operators */\
		/**@{*/\
		BIN_OP_STUB_ANY(>,  target_type) \
		BIN_OP_STUB_ANY(>=, target_type) \
		BIN_OP_STUB_ANY(<,  target_type) \
		BIN_OP_STUB_ANY(<=,  target_type) \
		BIN_OP_STUB_ANY(==, target_type) \
		BIN_OP_STUB_ANY(!=, target_type) \
		BIN_OP_STUB_ANY(||,  target_type) \
		BIN_OP_STUB_ANY(&&,  target_type) \
		/** @} */


		/// @def SCALAR_VECTOR_CVT_OP_DEFS(scalar_type, vector_type)
		/// @brief shortcut: collection of converting operators for a single vector and a single scalar
		/// @param scalar_type scalar type
		/// @param vector_type vector type
#define SCALAR_VECTOR_CVT_OP_DEFS(scalar_type, vector_type) \
        /** @name converting operators */\
		/**@{*/\
		BIN_OP_STUB(+, vector_type, scalar_type) \
		BIN_OP_STUB(-, vector_type, scalar_type) \
		BIN_OP_STUB(*, vector_type, scalar_type) \
		BIN_OP_STUB(/ , vector_type, scalar_type) \
		\
		BIN_OP_STUB(&, vector_type, scalar_type) \
		BIN_OP_STUB(&&, vector_type, scalar_type) \
		BIN_OP_STUB(|, vector_type, scalar_type) \
		BIN_OP_STUB(||, vector_type, scalar_type) \
		BIN_OP_STUB(^, vector_type, scalar_type) \
		\
		BIN_OP_STUB(>, vector_type, scalar_type) \
		BIN_OP_STUB(<, vector_type, scalar_type) \
		BIN_OP_STUB(== , vector_type, scalar_type) \
		BIN_OP_STUB(!= , vector_type, scalar_type) \
		/**@}*/\


}}