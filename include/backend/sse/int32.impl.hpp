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
#include "traits/bitwise_shift.hpp"
#include "traits/logical.hpp"
#include "traits/comparison.hpp"
#include "traits/conditional.hpp"

/**
 * @brief int32 implementation for the sse branch
 * provides unified access to 4 'int32_t' values
 */

namespace zacc { namespace backend { namespace sse {

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;



            /**
             * @brief construction default branch
             * @relates int32
             * @remark sse - default
             */
            __impl() : base_t() {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark sse - default
             */
            __impl(__m128 value) : base_t(_mm_cvtps_epi32(value)) {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "CONS(__m128 value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark sse - default
             */
            __impl(__m128d value) : base_t(_mm_cvtpd_epi32(value)) {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "CONS(__m128d value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark sse - default
             */
            __impl(__m128i value) : base_t(value) {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "CONS(__m128i value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark sse - default
             */
            __impl(int32_t value) : base_t(_mm_set1_epi32(value)) {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "CONS(int32_t value)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark sse - default
             */
            __impl(std::array<typename base_t::scalar_t, base_t::dim> value) : base_t(_mm_load_si128((__m128i*)value.data())) {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "CONS(std::array<typename base_t::scal..)");

            }


            /**
             * @brief construction default branch
             * @relates int32
             * @remark sse - default
             */
            __impl(int32_t arg3, int32_t arg2, int32_t arg1, int32_t arg0) : base_t(_mm_set_epi32(arg0, arg1, arg2, arg3)) {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "CONS(int32_t arg3, int32_t arg2, int3..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::construction<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::construction<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int32
             * @remark sse - default
             */
            friend void vstore(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vstore");

                _mm_storeu_si128((__m128i*)target.data(), source);
            }


            /**
             * @brief io default branch
             * @relates int32
             * @remark sse - default
             */
            friend void vstream(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vstream");

                _mm_stream_si128((__m128i*)target.data(), source);
            }


            /**
             * @brief io default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vgather(composed_t &target, raw_ptr<const int> source, zint32<base_t::capability> index)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vgather");

                auto i = index.data();
                return _mm_set_epi32(source[i[3]], source[i[2]], source[i[1]], source[i[0]]);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::io<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::io<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_numeric
    {

        /**
         * @brief numeric basic interface implementation
         * @relates int32
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
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::numeric<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::numeric<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_math
    {

        /**
         * @brief math basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief math sse3 branch
             * @relates int32
             * @remark sse - sse3
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE3), T> vabs(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "sse3", "vabs");

                return _mm_abs_epi32(one);
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark sse - default
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE3), T> vabs(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vabs");

                return vmax(one, -one);
            }


            /**
             * @brief math sse4 branch
             * @relates int32
             * @remark sse - sse4
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> vmin(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "sse4", "vmin");

                return _mm_min_epi32(one, other);
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark sse - default
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> vmin(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vmin");

                return vsel(one < other, one, other);
            }


            /**
             * @brief math sse4 branch
             * @relates int32
             * @remark sse - sse4
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> vmax(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "sse4", "vmax");

                return _mm_max_epi32(one, other);
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark sse - default
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> vmax(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vmax");

                return vsel(one < other, one, other);
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vclamp(composed_t self, composed_t from, composed_t to)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vclamp");

                return vmin(to, vmax(from, self));
            }


            /**
             * @brief math default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vsqrt(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vsqrt");

                return _mm_sqrt_ps(_mm_cvtepi32_ps(one));
            }

        };

        /**
         * @brief math public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::math<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::math<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vneg");

                return _mm_sub_epi32(_mm_setzero_si128(), one);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vadd");

                return _mm_add_epi32(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vsub");

                return _mm_sub_epi32(one, other);
            }


            /**
             * @brief arithmetic sse4 branch
             * @relates int32
             * @remark sse - sse4
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "sse4", "vmul");

                return _mm_mullo_epi32(one, other);
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark sse - default
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vmul");

                __m128i tmp1 = _mm_mul_epu32(one,other); /* mul 2,0*/;
                __m128i tmp2 = _mm_mul_epu32( _mm_srli_si128(one,4), _mm_srli_si128(other,4)); /* mul 3,1 */;
                return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE (0,0,2,0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE (0,0,2,0)));
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vdiv(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vdiv");

                return _mm_div_ps(_mm_cvtepi32_ps(one), _mm_cvtepi32_ps(other));
            }


            /**
             * @brief arithmetic default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vmod(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vmod");

                return vsub(one, vmul(other, vdiv(one, other)));
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::arithmetic<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::arithmetic<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vbneg");

                __m128i junk;
                auto ones = _mm_cmpeq_epi32(junk, junk);
                return _mm_xor_si128(one, ones);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vbor");

                return _mm_or_si128(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vband");

                return _mm_and_si128(one, other);
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vbxor");

                return _mm_xor_si128(one, other);
            }


            /**
             * @brief bitwise sse4 branch
             * @relates int32
             * @remark sse - sse4
             */
            template<typename T = bool> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> is_set(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "sse4", "is_set");

                return _mm_test_all_ones(one) != 0;
            }


            /**
             * @brief bitwise default branch
             * @relates int32
             * @remark sse - default
             */
            template<typename T = bool> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> is_set(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "is_set");

                __m128i junk;
                auto ones = _mm_cmpeq_epi32(junk, junk);
                return _mm_movemask_epi8(_mm_cmpeq_epi32(one, ones)) == 0xFFFF;
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::bitwise<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::bitwise<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_bitwise_shift
    {

        /**
         * @brief bitwise_shift basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vbsll(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vbsll");

                return _mm_sll_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vbsrl(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vbsrl");

                return _mm_srl_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vbslli(const composed_t one, const size_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vbslli");

                return _mm_slli_epi32(one, other);
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vbsrli(const composed_t one, const size_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vbsrli");

                return _mm_srli_epi32(one, other);
            }

        };

        /**
         * @brief bitwise_shift public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::bitwise_shift<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::bitwise_shift<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vlneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vlneg");

                return _mm_cmpeq_epi32(one, _mm_setzero_si128());
            }


            /**
             * @brief logical default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vlor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vlor");

                return _mm_or_si128(one, other);
            }


            /**
             * @brief logical default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vland(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vland");

                return _mm_and_si128(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::logical<__impl<base_t>, bint32<base_t::capability>>;

        using impl = traits::logical<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "veq");

                return _mm_cmpeq_epi32(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vneq");

                return !(one == other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vgt");

                return _mm_cmpgt_epi32(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vlt");

                return _mm_cmplt_epi32(one, other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vge");

                return !(one < other);
            }


            /**
             * @brief comparison default branch
             * @relates int32
             * @remark sse - default
             */
            friend zint32<base_t::capability> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vle");

                return !(one > other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::comparison<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::comparison<__impl<base_t>, zint32<base_t::capability>>;

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
     * @remark sse
     */
    template<typename composed_t>
    struct int32_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int32
         * @remark sse
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional sse4 branch
             * @relates int32
             * @remark sse - sse4
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<base_t::dispatcher::is_set(capabilities::SSE41), T> vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "sse4", "vsel");

                auto mask = _mm_cmpeq_epi32(_mm_setzero_si128(), condition);
                return _mm_blendv_epi8(if_value, else_value, mask);
            }


            /**
             * @brief conditional default branch
             * @relates int32
             * @remark sse - default
             */
            template<typename T = zint32<base_t::capability>> friend std::enable_if_t<!base_t::dispatcher::is_set(capabilities::SSE41), T> vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("sse.int32.impl", __LINE__, "zint32(int32_t[4])", "default", "vsel");

                return _mm_or_si128(_mm_andnot_si128(condition, else_value), _mm_and_si128(condition, if_value));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int32
         * @remark sse
         */


        template<typename base_t>
        //using impl = traits::conditional<__impl<base_t>, zint32<base_t::capability>>;

        using impl = traits::conditional<__impl<base_t>, zint32<base_t::capability>>;

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
         * - '__m128i' as underlying vector type
         * - 'int32_t' as scalar type
         * - '4' as vector size
         * - '16' as alignment
         * @relates int32
         * @remark sse
         */
        template<uint64_t capability>
        struct __zval_int32
        {
            using zval_t = zval<__m128i, __m128i, int32_t, 4, 16, capability>;

            struct impl : public zval_t
            {
                FORWARD2(impl, zval_t);
            };
        };
        /**
         * @brief zval composition
         * @relates int32
         * @remark sse
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

        template<uint64_t capability>
        struct __bint32
        {
            using bval_t = bval<typename __zint32<capability>::impl, __m128i>;
            struct impl : public bval_t
            {
                FORWARD2(impl, bval_t);
            };
        };
    //}

    template<uint64_t capability>
    struct zint32 : public /*composition::*/__zint32<capability>::impl
    {
        FORWARD2(zint32, /*composition::*/__zint32<capability>::impl);
    };

    template<uint64_t capability>
    struct bint32 : public /*composition::*/__bint32<capability>::impl
    {
        FORWARD2(bint32, /*composition::*/__bint32<capability>::impl);
    };

    static_assert(is_zval<zint32<0>>::value, "is_zval for zint32 failed.");
    static_assert(is_bval<bint32<0>>::value, "is_bval for bint32 failed.");

    static_assert(!is_floating_point<zint32<0>>::value, "is_floating_point for zint32 failed.");
    static_assert(is_integral<zint32<0>>::value, "is_integral for zint32 failed.");

    static_assert(!is_float<zint32<0>>::value, "is_float for zint32 failed.");
    static_assert(!is_double<zint32<0>>::value, "is_double for zint32 failed.");

    ///@}
}}}