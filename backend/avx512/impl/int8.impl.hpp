//---------------------------------------------------------------------------------
//
//  This is an autogenerated file. Do not edit!
//
//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#include <intrin.h>
#include <type_traits>

#include "../../../common/zval.hpp"
#include "../../../common/common.hpp"
#include "../../../common/compose.hpp"
#include "../../../common/type_traits.hpp"
#include "../../../common/common_traits.hpp"

#include "../../../common/interfaces/construction.hpp"
#include "../../../common/interfaces/io.hpp"
#include "../../../common/interfaces/arithmetic.hpp"
#include "../../../common/interfaces/bitwise.hpp"
#include "../../../common/interfaces/logical.hpp"
#include "../../../common/interfaces/comparison.hpp"
#include "../../../common/interfaces/conditional.hpp"

/**
 * @brief int8 implementation for the None branch
 * provides unified access to 64 'char' values
 */

namespace zacc { namespace None {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates int8
     * @remark None
     */
    template<typename composed_t>
    struct int8_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {


            /**
             * @brief construction default branch
             * @relates int8
             * @remark None - default
             */
            __impl(__m512i value) : base_t(value) {
            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark None - default
             */
            __impl(char value) : base_t(_mm512_set1_epi8(value)) {
            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark None - default
             */
            __impl(char *value) : base_t(_mm512_load_si128(value)) {
            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark None - default
             */
            __impl(char arg63, char arg62, char arg61, char arg60, char arg59, char arg58, char arg57, char arg56, char arg55, char arg54, char arg53, char arg52, char arg51, char arg50, char arg49, char arg48, char arg47, char arg46, char arg45, char arg44, char arg43, char arg42, char arg41, char arg40, char arg39, char arg38, char arg37, char arg36, char arg35, char arg34, char arg33, char arg32, char arg31, char arg30, char arg29, char arg28, char arg27, char arg26, char arg25, char arg24, char arg23, char arg22, char arg21, char arg20, char arg19, char arg18, char arg17, char arg16, char arg15, char arg14, char arg13, char arg12, char arg11, char arg10, char arg9, char arg8, char arg7, char arg6, char arg5, char arg4, char arg3, char arg2, char arg1, char arg0) : base_t(_mm512_set_epi8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20, arg21, arg22, arg23, arg24, arg25, arg26, arg27, arg28, arg29, arg30, arg31, arg32, arg33, arg34, arg35, arg36, arg37, arg38, arg39, arg40, arg41, arg42, arg43, arg44, arg45, arg46, arg47, arg48, arg49, arg50, arg51, arg52, arg53, arg54, arg55, arg56, arg57, arg58, arg59, arg60, arg61, arg62, arg63)) {
            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        using impl = interface::construction<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name io operations
     */
    ///@{

    /**
     * @brief io
     * @relates int8
     * @remark None
     */
    template<typename composed_t>
    struct int8_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int8
             * @remark None - default
             */
            friend void io_store(typename base_t::extracted_t &target) const {
                _mm512_store_si512(target.data(), base_t::_value);
            }


            /**
             * @brief io default branch
             * @relates int8
             * @remark None - default
             */
            friend void io_stream(typename base_t::extracted_t &target) const {
                _mm512_stream_si512(target.data(), base_t::_value);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        using impl = interface::io<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name arithmetic operations
     */
    ///@{

    /**
     * @brief arithmetic
     * @relates int8
     * @remark None
     */
    template<typename composed_t>
    struct int8_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t arithmetic_negate(composed_t one) {
                return _mm512_sub_epi8(_mm512_setzero_epi8(), one.get_value());
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        using impl = interface::arithmetic<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name bitwise operations
     */
    ///@{

    /**
     * @brief bitwise
     * @relates int8
     * @remark None
     */
    template<typename composed_t>
    struct int8_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t bitwise_negate(composed_t one) {
                auto zero = _mm512_setzero_si128();
                auto ones = _mm512_cmpeq_epi8(zero, zero);
                return _mm512_xor_si128(one.get_value(), ones);
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t bitwise_and(composed_t one, composed_t other) {
                return _mm512_or_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t bitwise_or(composed_t one, composed_t other) {
                return _mm512_and_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t bitwise_xor(composed_t one, composed_t other) {
                return _mm512_xor_si128(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t bitwise_sll(composed_t one, composed_t other) {
                return _mm512_sll_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t bitwise_srl(composed_t one, composed_t other) {
                return _mm512_srl_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t bitwise_slli(const composed_t one, const size_t other) {
                return _mm512_slli_epi8(const composed_t one, const size_t other);
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t bitwise_srli(const composed_t one, const size_t other) {
                return _mm512_srli_epi8(const composed_t one, const size_t other);
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        using impl = interface::bitwise<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name logical operations
     */
    ///@{

    /**
     * @brief logical
     * @relates int8
     * @remark None
     */
    template<typename composed_t>
    struct int8_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t logical_negate(composed_t one) {
                auto zero = _mm512_setzero_si128();
                auto ones = _mm512_cmpeq_epi8(zero, zero);
                return _mm512_xor_si128(one.get_value(), ones);
            }


            /**
             * @brief logical default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t logical_or(composed_t one, composed_t other) {
                return _mm512_or_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief logical default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t logical_and(composed_t one, composed_t other) {
                return _mm512_and_epi8(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        using impl = interface::logical<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name comparison operations
     */
    ///@{

    /**
     * @brief comparison
     * @relates int8
     * @remark None
     */
    template<typename composed_t>
    struct int8_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t comparison_eq(composed_t one, composed_t other) {
                return _mm512_cmpeq_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t comparison_neq(composed_t one, composed_t other) {
                return _mm512_cmpneq_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t comparison_gt(composed_t one, composed_t other) {
                return _mm512_cmpgt_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t comparison_lt(composed_t one, composed_t other) {
                return _mm512_cmplt_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t comparison_ge(composed_t one, composed_t other) {
                return _mm512_cmpge_epi8(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t comparison_le(composed_t one, composed_t other) {
                return _mm512_cmple_epi8(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        using impl = interface::comparison<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name conditional operations
     */
    ///@{

    /**
     * @brief conditional
     * @relates int8
     * @remark None
     */
    template<typename composed_t>
    struct int8_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates int8
             * @remark None - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value) {
                return _mm512_or_si128(_mm512_andnot_si128(condition.get_value(), else_value.get_value()), _mm512_and_si128(condition.get_value(), if_value.get_value()));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int8
         * @remark None
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name int8 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - '__m512i' as underlying vector type
     * - 'char' as scalar type
     * - '64' as vector size
     * - '64' as alignment
     * @relates int8
     * @remark None
     */
    template<uint64_t capability>
    struct __zval_int8
    {
        using zval_t = zval<__m512i, char, 64, 64, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates int8
     * @remark None
     */
    template<uint64_t capability>
    struct __zint8
    {
        struct impl;

        using zval_t = typename __zval_int8<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            int8_io<impl>::template impl,
            int8_arithmetic<impl>::template impl,
            int8_bitwise<impl>::template impl,
            int8_logical<impl>::template impl,
            int8_comparison<impl>::template impl,
            int8_conditional<impl>::template impl,
            int8_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    using zint8 = typename __zint8<capability>::impl;

    ///@}
}}