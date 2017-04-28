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
#include "traits/logical.hpp"
#include "traits/comparison.hpp"
#include "traits/conditional.hpp"


/**
 * @brief int8 implementation for the avx2 branch
 * provides unified access to 32 'int8_t' values
 */

namespace zacc { namespace avx2 {

    template<uint64_t capability>
    struct bint8;

    template<uint64_t capability>
    struct zint8;


    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates int8
     * @remark avx2
     */
    template<typename composed_t>
    struct int8_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;




            /**
             * @brief construction default branch
             * @relates int8
             * @remark avx2 - default
             */
            __impl() : base_t() {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark avx2 - default
             */
            __impl(__m256i value) : base_t(value) {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "CONS(__m256i value)");

            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark avx2 - default
             */
            __impl(int8_t value) : base_t(_mm256_set1_epi8(value)) {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "CONS(int8_t value)");

            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark avx2 - default
             */
            __impl(std::array<typename base_t::scalar_t, base_t::dim> value) : base_t(_mm256_load_si256((__m256i*)value.data())) {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "CONS(std::array<typename base_t::scal..)");

            }


            /**
             * @brief construction default branch
             * @relates int8
             * @remark avx2 - default
             */
            __impl(int8_t arg31, int8_t arg30, int8_t arg29, int8_t arg28, int8_t arg27, int8_t arg26, int8_t arg25, int8_t arg24, int8_t arg23, int8_t arg22, int8_t arg21, int8_t arg20, int8_t arg19, int8_t arg18, int8_t arg17, int8_t arg16, int8_t arg15, int8_t arg14, int8_t arg13, int8_t arg12, int8_t arg11, int8_t arg10, int8_t arg9, int8_t arg8, int8_t arg7, int8_t arg6, int8_t arg5, int8_t arg4, int8_t arg3, int8_t arg2, int8_t arg1, int8_t arg0) : base_t(_mm256_set_epi8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16, arg17, arg18, arg19, arg20, arg21, arg22, arg23, arg24, arg25, arg26, arg27, arg28, arg29, arg30, arg31)) {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "CONS(int8_t arg31, int8_t arg30, int8..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::construction<__impl<base_t>, composed_t>;
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
     * @remark avx2
     */
    template<typename composed_t>
    struct int8_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend void vstore(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vstore");

                _mm256_store_si256((__m256i*)target.data(), source);
            }


            /**
             * @brief io default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend void vstream(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vstream");

                _mm256_stream_si256((__m256i*)target.data(), source);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::io<__impl<base_t>, composed_t>;
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
     * @remark avx2
     */
    template<typename composed_t>
    struct int8_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend zint8<base_t::capability> vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vneg");

                return _mm256_sub_epi8(_mm256_setzero_si256(), one);
            }


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend zint8<base_t::capability> vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vadd");

                return _mm256_add_epi8(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend zint8<base_t::capability> vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vsub");

                return _mm256_sub_epi8(one, other);
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::arithmetic<__impl<base_t>, composed_t>;
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
     * @remark avx2
     */
    template<typename composed_t>
    struct int8_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend zint8<base_t::capability> vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vbneg");

                __m256i junk;
                auto ones = _mm256_cmpeq_epi8(junk, junk);
                return _mm256_xor_si256(one, ones);
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend zint8<base_t::capability> vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vband");

                return _mm256_or_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend zint8<base_t::capability> vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vbor");

                return _mm256_and_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend zint8<base_t::capability> vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vbxor");

                return _mm256_xor_si256(one, other);
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::bitwise<__impl<base_t>, composed_t>;
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
     * @remark avx2
     */
    template<typename composed_t>
    struct int8_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> vlneg(bint8<base_t::capability> one)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vlneg");

                return _mm256_cmpeq_epi32(one, _mm256_setzero_si256());
            }


            /**
             * @brief logical default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> vlor(bint8<base_t::capability> one, bint8<base_t::capability> other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vlor");

                return _mm256_or_si256(one, other);
            }


            /**
             * @brief logical default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> vland(bint8<base_t::capability> one, bint8<base_t::capability> other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vland");

                return _mm256_and_si256(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::logical<__impl<base_t>, composed_t>;
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
     * @remark avx2
     */
    template<typename composed_t>
    struct int8_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "veq");

                return _mm256_cmpeq_epi8(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vneq");

                return _mm256_xor_si256(_mm256_cmpeq_epi8(one, other), _mm256_setzero_si256());
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vgt");

                return _mm256_cmpgt_epi8(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vlt");

                // reversed args;
                return _mm256_cmpgt_epi8(other, one);
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vge");

                return (one == other) || _mm256_cmpgt_epi8(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend bint8<base_t::capability> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vle");

                return (one == other) || _mm256_cmpgt_epi8(one, other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::comparison<__impl<base_t>, composed_t>;
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
     * @remark avx2
     */
    template<typename composed_t>
    struct int8_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates int8
             * @remark avx2 - default
             */
            friend zint8<base_t::capability> vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("avx2.int8.impl", __LINE__, "zint8(int8_t[32])", "default", "vsel");

                auto mask = _mm256_cmpeq_epi8(_mm256_setzero_si256(), condition);
                return _mm256_blendv_epi8(if_value, else_value, mask);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int8
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name int8 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - '__m256i' as underlying vector type
     * - 'int8_t' as scalar type
     * - '32' as vector size
     * - '32' as alignment
     * @relates int8
     * @remark avx2
     */
    template<uint64_t capability>
    struct __zval_int8
    {
        using zval_t = zval<__m256i, __m256i, int8_t, 32, 32, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates int8
     * @remark avx2
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
            convertable::impl,
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

    template<uint64_t capability>
    struct zint8 : public __zint8<capability>::impl
    {
        FORWARD2(zint8, __zint8<capability>::impl);
    };

    template<uint64_t capability>
    struct __bint8
    {
        using bval_t = bval<typename __zint8<capability>::impl, __m256i>;
        struct impl : public bval_t
        {
            FORWARD2(impl, bval_t);
        };
    };

    template<uint64_t capability>
    struct bint8 : public __bint8<capability>::impl
    {
        FORWARD2(bint8, __bint8<capability>::impl);
    };

    static_assert(is_zval<zint8<0>>::value, "is_zval for zint8 failed.");
    static_assert(is_bval<bint8<0>>::value, "is_bval for bint8 failed.");

    static_assert(!is_floating_point<zint8<0>>::value, "is_floating_point for zint8 failed.");
    static_assert(is_integral<zint8<0>>::value, "is_integral for zint8 failed.");

    static_assert(!is_float<zint8<0>>::value, "is_float for zint8 failed.");
    static_assert(!is_double<zint8<0>>::value, "is_double for zint8 failed.");

    ///@}
}}