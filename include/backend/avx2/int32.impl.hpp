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
 * @brief int32 implementation for the avx2 branch
 * provides unified access to 8 'int32_t' values
 */

namespace zacc { namespace avx2 {

    template<uint64_t capability>
    struct bint32;

    template<uint64_t capability>
    struct zint32;


    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;




            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            __impl() : base_t() {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            __impl(__m256 value) : base_t(_mm256_cvtps_epi32(value)) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(__m256 value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            __impl(__m256d value) : base_t(_mm256_cvtpd_epi32(value)) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(__m256d value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            __impl(__m256i value) : base_t(value) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(__m256i value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            __impl(int32_t value) : base_t(_mm256_set1_epi32(value)) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(int32_t value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            __impl(std::array<typename base_t::scalar_t, base_t::dim> value) : base_t(_mm256_load_si256((__m256i*)value.data())) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(std::array<typename base_t::scal..)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            __impl(int32_t arg7, int32_t arg6, int32_t arg5, int32_t arg4, int32_t arg3, int32_t arg2, int32_t arg1, int32_t arg0) : base_t(_mm256_set_epi32(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(int32_t arg7, int32_t arg6, int3..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int32
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
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend void vstore(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vstore");

                _mm256_store_si256((__m256i*)target.data(), source);
            }


            /**
             * @brief io default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend void vstream(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vstream");

                _mm256_stream_si256((__m256i*)target.data(), source);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int32
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
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vneg");

                return _mm256_sub_epi32(_mm256_setzero_si256(), one);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vadd");

                return _mm256_add_epi32(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vsub");

                return _mm256_sub_epi32(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vmul");

                return _mm256_mullo_epi32(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vdiv(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vdiv");

                return _mm256_div_ps(_mm256_cvtepi32_ps(one), _mm256_cvtepi32_ps(other));
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int32
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
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbneg");

                __m256i junk;
                auto ones = _mm256_cmpeq_epi32(junk, junk);
                return _mm256_xor_si256(one, ones);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vband");

                return _mm256_or_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbor");

                return _mm256_and_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbxor");

                return _mm256_xor_si256(one, other);
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int32
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
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_bitwise_shift
    {

        /**
         * @brief bitwise_shift basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vsll(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vsll");

                return _mm256_sll_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vsrl(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vsrl");

                return _mm256_srl_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vslli(const composed_t one, const size_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vslli");

                return _mm256_slli_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vsrli(const composed_t one, const size_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vsrli");

                return _mm256_srli_epi32(one, other);
            }

        };

        /**
         * @brief bitwise_shift public interface implementation
         * @relates int32
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
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> vlneg(bint32<base_t::capability> one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vlneg");

                return _mm256_cmpeq_epi32(one, _mm256_setzero_si256());
            }


            /**
             * @brief logical default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> vlor(bint32<base_t::capability> one, bint32<base_t::capability> other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vlor");

                return _mm256_or_si256(one, other);
            }


            /**
             * @brief logical default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> vland(bint32<base_t::capability> one, bint32<base_t::capability> other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vland");

                return _mm256_and_si256(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates int32
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
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "veq");

                return _mm256_cmpeq_epi32(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vneq");

                return _mm256_xor_si256(_mm256_cmpeq_epi32(one, other), _mm256_setzero_si256());
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vgt");

                return _mm256_cmpgt_epi32(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vlt");

                return (one != other) && (one <= other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vge");

                return (one == other) || _mm256_cmpgt_epi32(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bint32<base_t::capability> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vle");

                return _mm256_xor_si256(_mm256_cmpgt_epi32(one, other), _mm256_setzero_si256());
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int32
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
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::capability> vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vsel");

                return _mm256_blendv_epi8(if_value, else_value, condition);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name int32 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - '__m256i' as underlying vector type
     * - 'int32_t' as scalar type
     * - '8' as vector size
     * - '32' as alignment
     * @relates int32
     * @remark avx2
     */
    template<uint64_t capability>
    struct __zval_int32
    {
        using zval_t = zval<__m256i, __m256i, int32_t, 8, 32, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates int32
     * @remark avx2
     */
    template<uint64_t capability>
    struct __zint32
    {
        struct impl;

        using zval_t = typename __zval_int32<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            convertable::impl,
            int32_io<impl>::template impl,
            int32_arithmetic<impl>::template impl,
            int32_bitwise<impl>::template impl,
            int32_bitwise_shift<impl>::template impl,
            int32_logical<impl>::template impl,
            int32_comparison<impl>::template impl,
            int32_conditional<impl>::template impl,
            int32_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability>
    struct zint32 : public __zint32<capability>::impl
    {
        FORWARD2(zint32, __zint32<capability>::impl);
    };

    template<uint64_t capability>
    struct __bint32
    {
        using bval_t = bval<typename __zint32<capability>::impl, __m256i>;
        struct impl : public bval_t
        {
            FORWARD2(impl, bval_t);
        };
    };

    template<uint64_t capability>
    struct bint32 : public __bint32<capability>::impl
    {
        FORWARD2(bint32, __bint32<capability>::impl);
    };

    static_assert(is_zval<zint32<0>>::value, "is_zval for zint32 failed.");
    static_assert(is_bval<bint32<0>>::value, "is_bval for bint32 failed.");

    static_assert(!is_floating_point<zint32<0>>::value, "is_floating_point for zint32 failed.");
    static_assert(is_integral<zint32<0>>::value, "is_integral for zint32 failed.");

    static_assert(!is_float<zint32<0>>::value, "is_float for zint32 failed.");
    static_assert(!is_double<zint32<0>>::value, "is_double for zint32 failed.");

    ///@}
}}