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

#include "intrin.hpp"
#include <type_traits>
#include <cmath>

#include "util/type_composition.hpp"
#include "util/memory.hpp"
#include "zval.hpp"
#include "common.hpp"
#include "type_traits.hpp"

#include "traits/common.hpp"
#include "traits/construction.hpp"
#include "traits/io.hpp"
#include "traits/numeric.hpp"
#include "traits/math.hpp"
#include "traits/arithmetic.hpp"
#include "traits/bitwise.hpp"
#include "traits/logical.hpp"
#include "traits/comparison.hpp"
#include "traits/conditional.hpp"

/**
 * @brief float64 implementation for the avx2 branch
 * provides unified access to 4 'double' values
 */

namespace zacc { namespace avx2 {

    template<uint64_t capability>
    struct bfloat64;

    template<uint64_t capability>
    struct zfloat64;


    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates float64
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;



            /**
             * @brief construction default branch
             * @relates float64
             * @remark avx2 - default
             */
            __impl() : base_t() {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark avx2 - default
             */
            __impl(const __m256 &value) : base_t(_mm256_cvtps_pd(_mm256_castps256_ps128(value))) {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "CONS(const __m256 &value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark avx2 - default
             */
            __impl(const __m256d &value) : base_t(value) {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "CONS(const __m256d &value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark avx2 - default
             */
            __impl(const __m256i &value) : base_t(_mm256_cvtepi32_pd(_mm256_castsi256_si128(value))) {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "CONS(const __m256i &value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark avx2 - default
             */
            __impl(double value) : base_t(_mm256_set1_pd(value)) {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "CONS(double value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark avx2 - default
             */
            __impl(std::array<typename base_t::scalar_t, base_t::dim> value) : base_t(_mm256_load_pd(value.data())) {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "CONS(std::array<typename base_t::scal..)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark avx2 - default
             */
            __impl(double arg3, double arg2, double arg1, double arg0) : base_t(_mm256_set_pd(arg0, arg1, arg2, arg3)) {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "CONS(double arg3, double arg2, double..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::construction<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::construction<__impl<base_t>, zfloat64<base_t::capability>>;

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
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend void vstore(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vstore");

                _mm256_store_pd(target.data(), source);
            }


            /**
             * @brief io default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend void vstream(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vstream");

                _mm256_stream_pd(target.data(), source);
            }


            /**
             * @brief io default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vgather(composed_t &target, raw_ptr<double> source, zint32<base_t::capability> index)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vgather");

                return _mm256_i32gather_pd(source, index, 8);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::io<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::io<__impl<base_t>, zfloat64<base_t::capability>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name numeric operations
     */
    ///@{

    /**
     * @brief numeric
     * @relates float64
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_numeric
    {

        /**
         * @brief numeric basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);

        };

        /**
         * @brief numeric public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::numeric<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::numeric<__impl<base_t>, zfloat64<base_t::capability>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name math operations
     */
    ///@{

    /**
     * @brief math
     * @relates float64
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_math
    {

        /**
         * @brief math basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief math default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vabs(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vabs");

                return _mm256_max_ps(one, -one);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vrcp(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vrcp");

                return _mm256_rcp_ps(one);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vtrunc(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vtrunc");

                return _mm256_cvtepi32_ps(_mm256_cvtps_epi32(one));
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vfloor(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vfloor");

                return _mm256_floor_ps(one);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vceil(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vceil");

                return _mm256_ceil_ps(one);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vround(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vround");

                return _mm256_round_ps (one, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vsqrt(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vsqrt");

                return _mm256_sqrt_ps(one);
            }

        };

        /**
         * @brief math public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::math<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::math<__impl<base_t>, zfloat64<base_t::capability>>;

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
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vneg");

                return _mm256_sub_pd(_mm256_setzero_pd(), one);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vadd");

                return _mm256_add_pd(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vsub");

                return _mm256_sub_pd(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vmul");

                return _mm256_mul_pd(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vdiv(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vdiv");

                return _mm256_div_pd(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vfmadd(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vfmadd");

                return _mm256_fmadd_pd(multiplicand, multiplier, addendum);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vfmsub(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vfmsub");

                return _mm256_fmsub_pd(multiplicand, multiplier, -addendum);
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::arithmetic<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::arithmetic<__impl<base_t>, zfloat64<base_t::capability>>;

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
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vbneg");

                __m256d junk;
                auto ones = _mm256_cmp_pd(junk, junk, _CMP_EQ_OQ);
                return _mm256_xor_pd(one, ones);
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vband");

                return _mm256_or_pd(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vbor");

                return _mm256_and_pd(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vbxor");

                return _mm256_xor_pd(one, other);
            }


            /**
             * @brief bitwise avx2 branch
             * @relates float64
             * @remark avx2 - avx2
             */
            template<typename T = bool> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::AVX2), T> is_set(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "avx2", "is_set");

                auto ival =  _mm256_castpd_si256(one);
                return _mm256_testc_si256(ival, _mm256_cmpeq_epi32(ival,ival));
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark avx2 - default
             */
            template<typename T = bool> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::AVX2), T> is_set(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "is_set");

                auto hi = _mm_castpd_si128(_mm256_extractf128_pd(one, 1));
                auto lo = _mm_castpd_si128(_mm256_extractf128_pd(one, 0));
                return _mm_test_all_ones(hi) != 0 && _mm_test_all_ones(lo) != 0;
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::bitwise<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::bitwise<__impl<base_t>, zfloat64<base_t::capability>>;

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
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vlneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vlneg");

                return _mm256_cmp_pd(one, _mm256_setzero_pd(), _CMP_EQ_OQ);
            }


            /**
             * @brief logical default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vlor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vlor");

                return _mm256_or_pd(one, other);
            }


            /**
             * @brief logical default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vland(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vland");

                return _mm256_and_pd(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::logical<__impl<base_t>, bfloat64<base_t::capability>>;

        using impl = traits::logical<__impl<base_t>, zfloat64<base_t::capability>>;

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
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "veq");

                return _mm256_cmp_pd(one, other, _CMP_EQ_OQ);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vneq");

                return _mm256_cmp_pd(one, other, _CMP_NEQ_OQ);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vgt");

                return _mm256_cmp_pd(one, other, _CMP_GT_OQ);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vlt");

                return _mm256_cmp_pd(one, other, _CMP_LT_OQ);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vge");

                auto result = _mm256_cmp_pd(one, other, _CMP_GE_OQ);
                return result;
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vle");

                return _mm256_cmp_pd(one, other, _CMP_LE_OQ);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::comparison<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::comparison<__impl<base_t>, zfloat64<base_t::capability>>;

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
     * @remark avx2
     */
    template<typename composed_t>
    struct float64_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float64
         * @remark avx2
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates float64
             * @remark avx2 - default
             */
            friend zfloat64<base_t::capability> vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("avx2.float64.impl", __LINE__, "zfloat64(double[4])", "default", "vsel");

                auto mask = _mm256_cmp_pd(_mm256_setzero_pd(), condition, _CMP_EQ_OQ);
                return _mm256_blendv_pd(if_value, else_value, mask);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float64
         * @remark avx2
         */


        template<typename base_t>
        //using impl = traits::conditional<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::conditional<__impl<base_t>, zfloat64<base_t::capability>>;

    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float64 composition
     */
    ///@{

    //namespace composition {

        /**
         * @brief zval parametrization using
         * - '__m256d' as underlying vector type
         * - 'double' as scalar type
         * - '4' as vector size
         * - '32' as alignment
         * @relates float64
         * @remark avx2
         */
        template<uint64_t capability>
        struct __zval_float64
        {
            using zval_t = zval<__m256d, __m256d, double, 4, 32, capability>;

            struct impl : public zval_t
            {
                FORWARD2(impl, zval_t);
            };
        };
        /**
         * @brief zval composition
         * @relates float64
         * @remark avx2
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
                convertable::impl,
                float64_io<impl>::template impl,
                float64_math<impl>::template impl,
                float64_numeric<impl>::template impl,
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

        template<uint64_t capability>
        struct __bfloat64
        {
            using bval_t = bval<typename __zfloat64<capability>::impl, __m256d>;
            struct impl : public bval_t
            {
                FORWARD2(impl, bval_t);
            };
        };
    //}

    template<uint64_t capability>
    struct zfloat64 : public /*composition::*/__zfloat64<capability>::impl
    {
        FORWARD2(zfloat64, /*composition::*/__zfloat64<capability>::impl);
    };

    template<uint64_t capability>
    struct bfloat64 : public /*composition::*/__bfloat64<capability>::impl
    {
        FORWARD2(bfloat64, /*composition::*/__bfloat64<capability>::impl);
    };

    static_assert(is_zval<zfloat64<0>>::value, "is_zval for zfloat64 failed.");
    static_assert(is_bval<bfloat64<0>>::value, "is_bval for bfloat64 failed.");

    static_assert(is_floating_point<zfloat64<0>>::value, "is_floating_point for zfloat64 failed.");
    static_assert(!is_integral<zfloat64<0>>::value, "is_integral for zfloat64 failed.");

    static_assert(!is_float<zfloat64<0>>::value, "is_float for zfloat64 failed.");
    static_assert(is_double<zfloat64<0>>::value, "is_double for zfloat64 failed.");

    ///@}
}}