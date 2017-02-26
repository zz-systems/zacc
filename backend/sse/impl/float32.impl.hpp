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

#include <x86intrin.h>
#include <type_traits>

#include "../../../util/type_composition.hpp"

#include "../../../common/zval.hpp"
#include "../../../common/common.hpp"
#include "../../../common/type_traits.hpp"
#include "../../../common/traits/common.hpp"

#include "../../../common/traits/construction.hpp"
#include "../../../common/traits/io.hpp"
#include "../../../common/traits/arithmetic.hpp"
#include "../../../common/traits/bitwise.hpp"
#include "../../../common/traits/logical.hpp"
#include "../../../common/traits/comparison.hpp"
#include "../../../common/traits/conditional.hpp"

/**
 * @brief float32 implementation for the sse branch
 * provides unified access to 4 'float' values
 */

namespace zacc { namespace sse {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates float32
     * @remark sse
     */
    template<typename composed_t>
    struct float32_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates float32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {


            /**
             * @brief construction default branch
             * @relates float32
             * @remark sse - default
             */
            __impl(__m128 value) : base_t(value) {
            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark sse - default
             */
            __impl(__m128d value) : base_t(_mm_cvtpd_ps(value)) {
            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark sse - default
             */
            __impl(__m128i value) : base_t(_mm_cvtepi32_ps(value)) {
            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark sse - default
             */
            __impl(float value) : base_t(_mm_set1_ps(value)) {
            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark sse - default
             */
            __impl(float *value) : base_t(_mm_load_ps(value)) {
            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark sse - default
             */
            __impl(float arg3, float arg2, float arg1, float arg0) : base_t(_mm_set_ps(arg0, arg1, arg2, arg3)) {
            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float32
         * @remark sse
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
     * @relates float32
     * @remark sse
     */
    template<typename composed_t>
    struct float32_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates float32
             * @remark sse - default
             */
            void io_store(typename base_t::extracted_t &target) const {
                _mm_store_ps(target.data(), base_t::_value);
            }


            /**
             * @brief io default branch
             * @relates float32
             * @remark sse - default
             */
            void io_stream(typename base_t::extracted_t &target) const {
                _mm_stream_ps(target.data(), base_t::_value);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float32
         * @remark sse
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
     * @relates float32
     * @remark sse
     */
    template<typename composed_t>
    struct float32_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates float32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t arithmetic_negate(composed_t one) {
                return _mm_sub_ps(_mm_setzero_ps(), one.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t arithmetic_add(composed_t one, composed_t other) {
                return _mm_add_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t arithmetic_sub(composed_t one, composed_t other) {
                return _mm_sub_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t arithmetic_mul(composed_t one, composed_t other) {
                return _mm_mul_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t arithmetic_div(composed_t one, composed_t other) {
                return _mm_div_ps(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float32
         * @remark sse
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
     * @relates float32
     * @remark sse
     */
    template<typename composed_t>
    struct float32_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates float32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t bitwise_negate(composed_t one) {
                __m128 junk;
                auto ones = _mm_cmpeq_ps(junk, junk);
                return _mm_xor_ps(one.get_value(), ones);
            }


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t bitwise_and(composed_t one, composed_t other) {
                return _mm_or_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t bitwise_or(composed_t one, composed_t other) {
                return _mm_and_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t bitwise_xor(composed_t one, composed_t other) {
                return _mm_xor_ps(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates float32
         * @remark sse
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
     * @relates float32
     * @remark sse
     */
    template<typename composed_t>
    struct float32_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates float32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t logical_negate(composed_t one) {
                return _mm_cmpeq_ps(one.get_value(), _mm_setzero_ps());
            }


            /**
             * @brief logical default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t logical_or(composed_t one, composed_t other) {
                return _mm_or_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief logical default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t logical_and(composed_t one, composed_t other) {
                return _mm_and_ps(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates float32
         * @remark sse
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
     * @relates float32
     * @remark sse
     */
    template<typename composed_t>
    struct float32_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates float32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t comparison_eq(composed_t one, composed_t other) {
                return _mm_cmpeq_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t comparison_neq(composed_t one, composed_t other) {
                return _mm_cmpneq_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t comparison_gt(composed_t one, composed_t other) {
                return _mm_cmpgt_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t comparison_lt(composed_t one, composed_t other) {
                return _mm_cmplt_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t comparison_ge(composed_t one, composed_t other) {
                return _mm_cmpge_ps(one.get_value(), other.get_value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t comparison_le(composed_t one, composed_t other) {
                return _mm_cmple_ps(one.get_value(), other.get_value());
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float32
         * @remark sse
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
     * @relates float32
     * @remark sse
     */
    template<typename composed_t>
    struct float32_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates float32
             * @remark sse - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value) {
                return _mm_or_ps(_mm_andnot_ps(condition.get_value(), else_value.get_value()), _mm_and_ps(condition.get_value(), if_value.get_value()));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float32
         * @remark sse
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float32 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - '__m128' as underlying vector type
     * - 'float' as scalar type
     * - '4' as vector size
     * - '16' as alignment
     * @relates float32
     * @remark sse
     */
    template<uint64_t capability>
    struct __zval_float32
    {
        using zval_t = zval<__m128, float, 4, 16, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates float32
     * @remark sse
     */
    template<uint64_t capability>
    struct __zfloat32
    {
        struct impl;

        using zval_t = typename __zval_float32<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            convertable::impl,
            float32_io<impl>::template impl,
            float32_arithmetic<impl>::template impl,
            float32_bitwise<impl>::template impl,
            float32_logical<impl>::template impl,
            float32_comparison<impl>::template impl,
            float32_conditional<impl>::template impl,
            float32_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    using zfloat32 = typename __zfloat32<capability>::impl;

    ///@}
}}