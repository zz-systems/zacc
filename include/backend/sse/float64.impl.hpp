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
#include "traits/numeric.hpp"
#include "traits/math.hpp"
#include "traits/arithmetic.hpp"
#include "traits/bitwise.hpp"
#include "traits/logical.hpp"
#include "traits/comparison.hpp"
#include "traits/conditional.hpp"


/**
 * @brief float64 implementation for the sse branch
 * provides unified access to 2 'double' values
 */

namespace zacc { namespace sse {

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
     * @remark sse
     */
    template<typename composed_t>
    struct float64_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;




            /**
             * @brief construction default branch
             * @relates float64
             * @remark sse - default
             */
            __impl() : base_t() {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark sse - default
             */
            __impl(__m128 value) : base_t(_mm_cvtps_pd(value)) {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "CONS(__m128 value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark sse - default
             */
            __impl(__m128d value) : base_t(value) {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "CONS(__m128d value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark sse - default
             */
            __impl(__m128i value) : base_t(_mm_cvtepi32_pd(_mm_shuffle_epi32(value, _MM_SHUFFLE(0,2,0,0)))) {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "CONS(__m128i value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark sse - default
             */
            __impl(double value) : base_t(_mm_set1_pd(value)) {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "CONS(double value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark sse - default
             */
            __impl(std::array<typename base_t::scalar_t, base_t::dim> value) : base_t(_mm_load_pd(value.data())) {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "CONS(std::array<typename base_t::scal..)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark sse - default
             */
            __impl(double arg1, double arg0) : base_t(_mm_set_pd(arg0, arg1)) {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "CONS(double arg1, double arg0)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float64
         * @remark sse
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
     * @relates float64
     * @remark sse
     */
    template<typename composed_t>
    struct float64_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates float64
             * @remark sse - default
             */
            friend void vstore(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vstore");

                _mm_store_pd(target.data(), source);
            }


            /**
             * @brief io default branch
             * @relates float64
             * @remark sse - default
             */
            friend void vstream(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vstream");

                _mm_stream_pd(target.data(), source);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        using impl = traits::io<__impl<base_t>, composed_t>;
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
     * @remark sse
     */
    template<typename composed_t>
    struct float64_numeric
    {

        /**
         * @brief numeric basic interface implementation
         * @relates float64
         * @remark sse
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
         * @remark sse
         */
        template<typename base_t>
        using impl = traits::numeric<__impl<base_t>, composed_t>;
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
     * @remark sse
     */
    template<typename composed_t>
    struct float64_math
    {

        /**
         * @brief math basic interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief math default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vabs(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vabs");

                return _mm_max_pd(one, -one);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vrcp(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vrcp");

                return (1 / one);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vtrunc(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vtrunc");

                return _mm_cvtepi32_pd(_mm_cvtpd_epi32(one));
            }


            /**
             * @brief math sse4 branch
             * @relates float64
             * @remark sse - sse4
             */
            template<typename T = zfloat64<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> vfloor(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "sse4", "vfloor");

                return _mm_floor_pd(one);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark sse - default
             */
            template<typename T = zfloat64<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> vfloor(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vfloor");

                __m128i junk;
                auto _1  = _mm_srli_epi32(_mm_cmpeq_epi32(junk, junk), 31);
                auto fi = vtrunc(one);
                return vsel(vgt(fi, one), vsub(fi, _1), fi);
            }


            /**
             * @brief math sse4 branch
             * @relates float64
             * @remark sse - sse4
             */
            template<typename T = zfloat64<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> vceil(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "sse4", "vceil");

                return _mm_ceil_pd(one);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark sse - default
             */
            template<typename T = zfloat64<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> vceil(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vceil");

                __m128i junk;
                auto _1  = _mm_srli_epi32(_mm_cmpeq_epi32(junk, junk), 31);
                auto fi = vtrunc(one);
                return vsel(vlt(fi, one), vadd(fi, _1), fi);
            }


            /**
             * @brief math sse4 branch
             * @relates float64
             * @remark sse - sse4
             */
            template<typename T = zfloat64<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> vround(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "sse4", "vround");

                return _mm_round_pd (one, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark sse - default
             */
            template<typename T = zfloat64<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> vround(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vround");

                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi32(zero, zero);
                // generate the highest value < 2;
                auto nearest = _mm_castsi128_pd(_mm_srli_epi64(ones, 2));
                auto tr = vtrunc(one);
                // get remainder;
                auto rmd = one - tr;
                // mul remainder by near 2 will yield the needed offset;
                auto rmd2 = vmul(rmd, nearest);
                // after being truncated of course;
                auto rmd2tr = vtrunc(rmd2);
                return tr + rmd2tr;
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vsqrt(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vsqrt");

                return _mm_sqrt_pd(one);
            }

        };

        /**
         * @brief math public interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        using impl = traits::math<__impl<base_t>, composed_t>;
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
     * @remark sse
     */
    template<typename composed_t>
    struct float64_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vneg");

                return _mm_sub_pd(_mm_setzero_pd(), one);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vadd");

                return _mm_add_pd(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vsub");

                return _mm_sub_pd(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vmul");

                return _mm_mul_pd(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vdiv(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vdiv");

                return _mm_div_pd(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vfmadd(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vfmadd");

                return vadd(vmul(multiplicand, multiplier), addendum);
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vfmsub(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vfmsub");

                return vsub(vmul(multiplicand, multiplier), addendum);
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float64
         * @remark sse
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
     * @relates float64
     * @remark sse
     */
    template<typename composed_t>
    struct float64_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vbneg");

                __m128d junk;
                auto ones = _mm_cmpeq_pd(junk, junk);
                return _mm_xor_pd(one, ones);
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vband");

                return _mm_or_pd(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vbor");

                return _mm_and_pd(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark sse - default
             */
            friend zfloat64<base_t::capability> vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vbxor");

                return _mm_xor_pd(one, other);
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates float64
         * @remark sse
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
     * @relates float64
     * @remark sse
     */
    template<typename composed_t>
    struct float64_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> vlneg(bfloat64<base_t::capability> one)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vlneg");

                return _mm_cmpeq_pd(one, _mm_setzero_pd());
            }


            /**
             * @brief logical default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> vlor(bfloat64<base_t::capability> one, bfloat64<base_t::capability> other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vlor");

                return _mm_or_pd(one, other);
            }


            /**
             * @brief logical default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> vland(bfloat64<base_t::capability> one, bfloat64<base_t::capability> other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vland");

                return _mm_and_pd(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates float64
         * @remark sse
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
     * @relates float64
     * @remark sse
     */
    template<typename composed_t>
    struct float64_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "veq");

                return _mm_cmpeq_pd(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vneq");

                return _mm_cmpneq_pd(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vgt");

                return _mm_cmpgt_pd(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vlt");

                return _mm_cmplt_pd(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vge");

                return _mm_cmpge_pd(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark sse - default
             */
            friend bfloat64<base_t::capability> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vle");

                return _mm_cmple_pd(one, other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float64
         * @remark sse
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
     * @relates float64
     * @remark sse
     */
    template<typename composed_t>
    struct float64_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional sse4 branch
             * @relates float64
             * @remark sse - sse4
             */
            template<typename T = zfloat64<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> vsel(mask_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "sse4", "vsel");

                auto mask = _mm_cmpeq_pd(_mm_setzero_pd(), condition);
                return _mm_blendv_pd(if_value, else_value, mask);
            }


            /**
             * @brief conditional default branch
             * @relates float64
             * @remark sse - default
             */
            template<typename T = zfloat64<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> vsel(mask_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("sse.float64.impl", __LINE__, "zfloat64(double[2])", "default", "vsel");

                auto mask = _mm_cmpeq_pd(_mm_setzero_pd(), condition);
                return _mm_xor_pd(if_value, _mm_and_pd( mask, _mm_xor_pd(else_value, if_value)));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float64
         * @remark sse
         */
        template<typename base_t>
        using impl = traits::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float64 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - '__m128d' as underlying vector type
     * - 'double' as scalar type
     * - '2' as vector size
     * - '16' as alignment
     * @relates float64
     * @remark sse
     */
    template<uint64_t capability>
    struct __zval_float64
    {
        using zval_t = zval<__m128d, __m128d, double, 2, 16, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates float64
     * @remark sse
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
            float64_numeric<impl>::template impl,
            float64_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability>
    struct zfloat64 : public __zfloat64<capability>::impl
    {
        FORWARD2(zfloat64, __zfloat64<capability>::impl);
    };

    template<uint64_t capability>
    struct __bfloat64
    {
        using bval_t = bval<typename __zfloat64<capability>::impl, __m128d>;
        struct impl : public bval_t
        {
            FORWARD2(impl, bval_t);
        };
    };

    template<uint64_t capability>
    struct bfloat64 : public __bfloat64<capability>::impl
    {
        FORWARD2(bfloat64, __bfloat64<capability>::impl);
    };

    static_assert(is_zval<zfloat64<0>>::value, "is_zval for zfloat64 failed.");
    static_assert(is_bval<bfloat64<0>>::value, "is_bval for bfloat64 failed.");

    static_assert(is_floating_point<zfloat64<0>>::value, "is_floating_point for zfloat64 failed.");
    static_assert(!is_integral<zfloat64<0>>::value, "is_integral for zfloat64 failed.");

    static_assert(!is_float<zfloat64<0>>::value, "is_float for zfloat64 failed.");
    static_assert(is_double<zfloat64<0>>::value, "is_double for zfloat64 failed.");

    ///@}
}}