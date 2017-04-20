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
#include <cmath>

#include "util/type_composition.hpp"

#include "zval.hpp"
#include "common.hpp"
#include "type_traits.hpp"

#include "traits/common.hpp"
#include "traits/construction.hpp"
#include "traits/io.hpp"
#include "traits/arithmetic.hpp"
#include "traits/bitwise.hpp"
#include "traits/bitwise_shift.hpp"
#include "traits/logical.hpp"
#include "traits/comparison.hpp"
#include "traits/conditional.hpp"

/**
 * @brief int16 implementation for the avx2 branch
 * provides unified access to 16 'int16_t' values
 */

namespace zacc { namespace avx2 {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates int16
     * @remark avx2
     */
    template<typename composed_t>
    struct int16_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;



            /**
             * @brief construction default branch
             * @relates int16
             * @remark avx2 - default
             */
            __impl() : base_t() {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates int16
             * @remark avx2 - default
             */
            __impl(__m256i value) : base_t(value) {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "CONS(__m256i value)");

            }


            /**
             * @brief construction default branch
             * @relates int16
             * @remark avx2 - default
             */
            __impl(int16_t value) : base_t(_mm256_set1_epi16(value)) {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "CONS(int16_t value)");

            }


            /**
             * @brief construction default branch
             * @relates int16
             * @remark avx2 - default
             */
            __impl(int16_t *value) : base_t(_mm256_load_si256((__m256i*)value)) {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "CONS(int16_t *value)");

            }


            /**
             * @brief construction default branch
             * @relates int16
             * @remark avx2 - default
             */
            __impl(int16_t arg15, int16_t arg14, int16_t arg13, int16_t arg12, int16_t arg11, int16_t arg10, int16_t arg9, int16_t arg8, int16_t arg7, int16_t arg6, int16_t arg5, int16_t arg4, int16_t arg3, int16_t arg2, int16_t arg1, int16_t arg0) : base_t(_mm256_set_epi16(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)) {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "CONS(int16_t arg15, int16_t arg14, in..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int16
         * @remark avx2
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
     * @relates int16
     * @remark avx2
     */
    template<typename composed_t>
    struct int16_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend void vstore(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vstore");

                _mm256_store_si256((__m256i*)target.data(), source);
            }


            /**
             * @brief io default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend void vstream(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vstream");

                _mm256_stream_si256((__m256i*)target.data(), source);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int16
         * @remark avx2
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
     * @relates int16
     * @remark avx2
     */
    template<typename composed_t>
    struct int16_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vneg");

                return _mm256_sub_epi16(_mm256_setzero_si256(), one);
            }


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vadd");

                return _mm256_add_epi16(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vsub");

                return _mm256_sub_epi16(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vmul");

                return _mm256_mullo_epi16(one, other);
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int16
         * @remark avx2
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
     * @relates int16
     * @remark avx2
     */
    template<typename composed_t>
    struct int16_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vbneg");

                __m256i junk;
                auto ones = _mm256_cmpeq_epi16(junk, junk);
                return _mm256_xor_si256(one, ones);
            }


            /**
             * @brief bitwise default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vband");

                return _mm256_or_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vbor");

                return _mm256_and_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vbxor");

                return _mm256_xor_si256(one, other);
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        using impl = interface::bitwise<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name bitwise_shift operations
     */
    ///@{

    /**
     * @brief bitwise_shift
     * @relates int16
     * @remark avx2
     */
    template<typename composed_t>
    struct int16_bitwise_shift
    {

        /**
         * @brief bitwise_shift basic interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise_shift default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vbsll(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vbsll");

                return _mm256_sll_epi16(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vbsrl(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vbsrl");

                return _mm256_srl_epi16(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vbslli(const composed_t one, const size_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vbslli");

                return _mm256_slli_epi16(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vbsrli(const composed_t one, const size_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vbsrli");

                return _mm256_srli_epi16(one, other);
            }

        };

        /**
         * @brief bitwise_shift public interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        using impl = interface::bitwise_shift<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name logical operations
     */
    ///@{

    /**
     * @brief logical
     * @relates int16
     * @remark avx2
     */
    template<typename composed_t>
    struct int16_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> vlneg(bval<composed_t, mask_t> one)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vlneg");

                return _mm256_cmpeq_epi32(one, _mm256_setzero_si256());
            }


            /**
             * @brief logical default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> vlor(bval<composed_t, mask_t> one, bval<composed_t, mask_t> other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vlor");

                return _mm256_or_si256(one, other);
            }


            /**
             * @brief logical default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> vland(bval<composed_t, mask_t> one, bval<composed_t, mask_t> other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vland");

                return _mm256_and_si256(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates int16
         * @remark avx2
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
     * @relates int16
     * @remark avx2
     */
    template<typename composed_t>
    struct int16_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "veq");

                return _mm256_cmpeq_epi16(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vneq");

                return _mm256_xor_si256(_mm256_cmpeq_epi16(one, other), _mm256_setzero_si256());
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vgt");

                return _mm256_cmpgt_epi16(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vlt");

                return (one != other) && (one <= other);
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vge");

                return (one == other) || _mm256_cmpgt_epi16(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend bval<composed_t, mask_t> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vle");

                return _mm256_xor_si256(_mm256_cmpgt_epi16(one, other), _mm256_setzero_si256());
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int16
         * @remark avx2
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
     * @relates int16
     * @remark avx2
     */
    template<typename composed_t>
    struct int16_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates int16
             * @remark avx2 - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("avx2.int16.impl", __LINE__, "zint16(int16_t[16])", "default", "vsel");

                auto mask = _mm256_cmpeq_epi16(_mm256_setzero_si256(), condition);
                return _mm256_blendv_epi8(if_value, else_value, mask);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int16
         * @remark avx2
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name int16 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - '__m256i' as underlying vector type
     * - 'int16_t' as scalar type
     * - '16' as vector size
     * - '32' as alignment
     * @relates int16
     * @remark avx2
     */
    template<uint64_t capability>
    struct __zval_int16
    {
        using zval_t = zval<__m256i, __m256i, int16_t, 16, 32, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates int16
     * @remark avx2
     */
    template<uint64_t capability>
    struct __zint16
    {
        struct impl;

        using zval_t = typename __zval_int16<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            convertable::impl,
            int16_io<impl>::template impl,
            int16_arithmetic<impl>::template impl,
            int16_bitwise<impl>::template impl,
            int16_bitwise_shift<impl>::template impl,
            int16_logical<impl>::template impl,
            int16_comparison<impl>::template impl,
            int16_conditional<impl>::template impl,
            int16_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    //template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    //using zint16 = typename __zint16<capability>::impl;

    ///@}
}}