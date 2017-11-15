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

#include <type_traits>
#include <cmath>

#include "backend/intrin.hpp"
#include "backend/zval.hpp"

#include "util/type/type_composition.hpp"
#include "util/type/type_traits.hpp"

#include "util/memory.hpp"
#include "util/macros.hpp"

#include "traits/common.hpp"
#include "traits/construction.hpp"
#include "traits/io.hpp"
#include "traits/numeric.hpp"
#include "traits/math.hpp"
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

namespace zacc { namespace backend { namespace avx2 {

    template<uint64_t features>
    struct bint32;

    template<uint64_t features>
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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;



            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            constexpr __impl() : base_t() {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            constexpr __impl(__m256 value) : base_t(_mm256_cvttps_epi32(value)) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(__m256 value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            constexpr __impl(__m256d value) : base_t(_mm256_castsi128_si256(_mm256_cvttpd_epi32(value))) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(__m256d value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            constexpr __impl(__m256i value) : base_t(value) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(__m256i value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            constexpr __impl(int32_t value) : base_t(_mm256_set1_epi32(value)) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(int32_t value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            constexpr __impl(std::array<typename base_t::element_t, base_t::size()> value) : base_t(_mm256_loadu_si256((__m256i*)value.data())) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(std::array<typename base_t::elem..)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark avx2 - default
             */
            constexpr __impl(int32_t arg7, int32_t arg6, int32_t arg5, int32_t arg4, int32_t arg3, int32_t arg2, int32_t arg1, int32_t arg0) : base_t(_mm256_set_epi32(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)) {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "CONS(int32_t arg7, int32_t arg6, int3..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::construction<__impl<base_t>, zint32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int32
             * @remark avx2 - default
             */
            template<typename OutputIt> friend void vstore(OutputIt result, composed_t input)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vstore");

                _mm256_storeu_si256((__m256i*)result, input);
            }


            /**
             * @brief io default branch
             * @relates int32
             * @remark avx2 - default
             */
            template<typename OutputIt> friend void vstream(OutputIt result, composed_t input)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vstream");

                _mm256_stream_si256((__m256i*)result, input);
            }


            /**
             * @brief io default branch
             * @relates int32
             * @remark avx2 - default
             */
            template<typename RandomIt> friend zint32<base_t::features> vgather(RandomIt input, const zint32<base_t::features> &index, composed_t)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vgather");

                return _mm256_i32gather_epi32(input, index, 4);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::io<__impl<base_t>, zint32<base_t::features>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name numeric operations
     */
    ///@{

    /**
     * @brief numeric
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_numeric
    {

        /**
         * @brief numeric basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);

        };

        /**
         * @brief numeric public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::numeric<__impl<base_t>, zint32<base_t::features>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name math operations
     */
    ///@{

    /**
     * @brief math
     * @relates int32
     * @remark avx2
     */
    template<typename composed_t>
    struct int32_math
    {

        /**
         * @brief math basic interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief math default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vabs(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vabs");

                return _mm256_abs_epi32(one);
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vmin(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vmin");

                return _mm256_min_epi32(one, other);
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vmax(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vmax");

                return _mm256_max_epi32(one, other);
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vclamp(composed_t self, composed_t from, composed_t to)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vclamp");

                return vmin(to, vmax(from, self));
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vsqrt(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vsqrt");

                return _mm256_sqrt_ps(_mm256_cvtepi32_ps(one));
            }

        };

        /**
         * @brief math public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::math<__impl<base_t>, zint32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vneg");

                return _mm256_sub_epi32(_mm256_setzero_si256(), one);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vadd");

                return _mm256_add_epi32(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vsub");

                return _mm256_sub_epi32(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vmul");

                return _mm256_mullo_epi32(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vdiv(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vdiv");

                return _mm256_div_ps(_mm256_cvtepi32_ps(one), _mm256_cvtepi32_ps(other));
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vmod(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vmod");

                return vsub(one, vmul(other, vdiv(one, other)));
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::arithmetic<__impl<base_t>, zint32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbneg");

                auto zero = _mm256_setzero_si256();
                auto ones = _mm256_cmpeq_epi32(zero, zero);
                return _mm256_xor_si256(one, ones);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vband");

                return _mm256_and_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbor");

                return _mm256_or_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbxor");

                return _mm256_xor_si256(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend bool is_set(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "is_set");

                return _mm256_testc_si256(one, _mm256_cmpeq_epi32(one,one));
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::bitwise<__impl<base_t>, zint32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vbsll(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbsll");

                return _mm256_sll_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vbsrl(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbsrl");

                return _mm256_srl_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vbslli(const composed_t one, const size_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbslli");

                return _mm256_slli_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vbsrli(const composed_t one, const size_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vbsrli");

                return _mm256_srli_epi32(one, other);
            }

        };

        /**
         * @brief bitwise_shift public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::bitwise_shift<__impl<base_t>, zint32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vlneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vlneg");

                return _mm256_cmpeq_epi32(one, _mm256_setzero_si256());
            }


            /**
             * @brief logical default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vlor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vlor");

                return _mm256_or_si256(one, other) != 0;
            }


            /**
             * @brief logical default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vland(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vland");

                return _mm256_and_si256(one, other) != 0;
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::logical<__impl<base_t>, zint32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "veq");

                return _mm256_cmpeq_epi32(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vneq");

                return !(one == other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vgt");

                return _mm256_cmpgt_epi32(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vlt");

                return _mm256_cmpgt_epi32(other, one);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vge");

                return !(one < other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vle");

                return !(one > other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::comparison<__impl<base_t>, zint32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates int32
             * @remark avx2 - default
             */
            friend zint32<base_t::features> vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("avx2.int32.impl", __LINE__, "zint32(int32_t[8])", "default", "vsel");

                auto mask = _mm256_cmpeq_epi32(_mm256_setzero_si256(), condition);
                return _mm256_blendv_epi8(if_value, else_value, mask);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::conditional<__impl<base_t>, zint32<base_t::features>>;

    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name int32 composition
     */
    ///@{

    //namespace composition {

        /**
         * @brief zval parametrization using
         * - '__m256i' as underlying vector type
         * - 'int32_t' as scalar type
         * - '8' as vector size
         * - '32' as alignment
         * @relates int32
         * @remark avx2
         */
        template<uint64_t features>
        struct __zval_int32
        {
            using zval_t = zval<__m256i, __m256i, int32_t, zval_tag, 8, 32, features>;

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
        template<uint64_t features>
        struct __zint32
        {
            struct impl;

            using zval_t = typename __zval_int32<features>::impl;
            using composition_t = compose
            <
                printable::impl,
                iteratable::impl,
                convertable::impl,
                int32_io<impl>::template impl,
                int32_math<impl>::template impl,
                int32_numeric<impl>::template impl,
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

        template<uint64_t features>
        struct __bint32
        {
            using bval_t = bval<typename __zint32<features>::impl, __m256i>;
            struct impl : public bval_t
            {
                FORWARD2(impl, bval_t);
            };
        };
    //}

    template<uint64_t features>
    struct zint32 : public /*composition::*/__zint32<features>::impl
    {
        FORWARD2(zint32, /*composition::*/__zint32<features>::impl);
    };

    template<uint64_t features>
    struct bint32 : public /*composition::*/__bint32<features>::impl
    {
        FORWARD2(bint32, /*composition::*/__bint32<features>::impl);
    };

    static_assert(is_zval<zint32<0>>::value, "is_zval for zint32 failed.");
    static_assert(is_bval<bint32<0>>::value, "is_bval for bint32 failed.");

    static_assert(!is_floating_point<zint32<0>>::value, "is_floating_point for zint32 failed.");
    static_assert(is_integral<zint32<0>>::value, "is_integral for zint32 failed.");

    static_assert(!is_float<zint32<0>>::value, "is_float for zint32 failed.");
    static_assert(!is_double<zint32<0>>::value, "is_double for zint32 failed.");

    ///@}
}}}