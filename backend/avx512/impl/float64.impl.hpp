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
 * @brief float64 implementation for the None branch
 * provides unified access to 8 'double' values
 */

namespace zacc { namespace None {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates float64
     * @remark None
     */
    template<typename composed_t>
    struct float64_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates float64
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {


            /**
             * @brief construction default branch
             * @relates float64
             * @remark None - default
             */
            __impl(__m512 value) : base_t(_mm_cvtps_pd(value)) {
            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark None - default
             */
            __impl(__m512d value) : base_t(value) {
            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark None - default
             */
            __impl(__m512i value) : base_t(_mm512_cvtepi32_pd(value)) {
            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark None - default
             */
            __impl(double value) : base_t(_mm512_set1_pd(value)) {
            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark None - default
             */
            __impl(double *value) : base_t(_mm512_load_pd(value)) {
            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark None - default
             */
            __impl(double arg7, double arg6, double arg5, double arg4, double arg3, double arg2, double arg1, double arg0) : base_t(_mm512_set_pd(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)) {
            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark None
     */
    template<typename composed_t>
    struct float64_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float64
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates float64
             * @remark None - default
             */
            void io_store(typename base_t::extracted_t &target) const {
                _mm512_store_pd(target.data(), base_t::_value);
            }


            /**
             * @brief io default branch
             * @relates float64
             * @remark None - default
             */
            void io_stream(typename base_t::extracted_t &target) const {
                _mm512_stream_pd(target.data(), base_t::_value);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark None
     */
    template<typename composed_t>
    struct float64_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates float64
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t arithmetic_negate(composed_t one) {
                return _mm512_sub_pd(_mm512_setzero_pd(), one.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t arithmetic_add(composed_t one, composed_t other) {
                return _mm512_add_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t arithmetic_sub(composed_t one, composed_t other) {
                return _mm512_sub_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t arithmetic_mul(composed_t one, composed_t other) {
                return _mm512_mul_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t arithmetic_div(composed_t one, composed_t other) {
                return _mm512_div_pd(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark None
     */
    template<typename composed_t>
    struct float64_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates float64
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t bitwise_negate(composed_t one) {
                auto zero = _mm512_setzero_pd();
                auto ones = _mm512_cmpeq_pd(zero, zero);
                return _mm512_xor_pd(one.get_value(), ones);
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t bitwise_and(composed_t one, composed_t other) {
                return _mm512_or_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t bitwise_or(composed_t one, composed_t other) {
                return _mm512_and_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t bitwise_xor(composed_t one, composed_t other) {
                return _mm512_xor_pd(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark None
     */
    template<typename composed_t>
    struct float64_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates float64
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t logical_negate(composed_t one) {
                auto zero = _mm512_setzero_pd();
                auto ones = _mm512_cmpeq_pd(zero, zero);
                return _mm512_xor_pd(one.get_value(), ones);
            }


            /**
             * @brief logical default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t logical_or(composed_t one, composed_t other) {
                return _mm512_or_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief logical default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t logical_and(composed_t one, composed_t other) {
                return _mm512_and_pd(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark None
     */
    template<typename composed_t>
    struct float64_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates float64
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t comparison_eq(composed_t one, composed_t other) {
                return _mm512_cmpeq_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t comparison_neq(composed_t one, composed_t other) {
                return _mm512_cmpneq_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t comparison_gt(composed_t one, composed_t other) {
                return _mm512_cmpgt_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t comparison_lt(composed_t one, composed_t other) {
                return _mm512_cmplt_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t comparison_ge(composed_t one, composed_t other) {
                return _mm512_cmpge_pd(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t comparison_le(composed_t one, composed_t other) {
                return _mm512_cmple_pd(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark None
     */
    template<typename composed_t>
    struct float64_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float64
         * @remark None
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates float64
             * @remark None - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value) {
                return _mm512_or_pd(_mm512_andnot_pd(condition.get_value(), else_value.get_value()), _mm512_and_pd(condition.get_value(), if_value.get_value()));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float64
         * @remark None
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float64 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - '__m512d' as underlying vector type
     * - 'double' as scalar type
     * - '8' as vector size
     * - '64' as alignment
     * @relates float64
     * @remark None
     */
    template<uint64_t capability>
    struct __zval_float64
    {
        using zval_t = zval<__m512d, double, 8, 64, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates float64
     * @remark None
     */
    template<uint64_t capability>
    struct __zfloat64
    {
        struct impl;

        using zval_t = typename __zval_float64<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            float64_io<impl>::template impl,
            float64_arithmetic<impl>::template impl,
            float64_bitwise<impl>::template impl,
            float64_logical<impl>::template impl,
            float64_comparison<impl>::template impl,
            float64_conditional<impl>::template impl,
            float64_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    using zfloat64 = typename __zfloat64<capability>::impl;

    ///@}
}}