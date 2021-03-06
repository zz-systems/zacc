//---------------------------------------------------------------------------------
//
//  This is an autogenerated file. Do not edit!
//
//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2018 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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
#include "traits/arithmetic.hpp"
#include "traits/bitwise.hpp"
#include "traits/logical.hpp"
#include "traits/comparable.hpp"
#include "traits/conditional.hpp"

/**
 * @brief float64 implementation for the avx512 arch
 * provides unified access to 8 'double' values
 */

namespace zacc { namespace backend { namespace avx512 {

    template<uint64_t arch>
    struct bfloat64;

    template<uint64_t arch>
    struct zfloat64;


    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates float64
     * @remark avx512
     */
    template<typename Composed>
    struct float64_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates float64
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;



            /**
             * @brief construction default arch
             * @relates float64
             * @remark avx512 - default
             */
            __impl() : Base() {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "CONS()");

            }


            /**
             * @brief construction default arch
             * @relates float64
             * @remark avx512 - default
             */
            __impl(__m512 value) : Base(_mm512_cvtps_pd(value)) {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "CONS(__m512 value)");

            }


            /**
             * @brief construction default arch
             * @relates float64
             * @remark avx512 - default
             */
            __impl(__m512d value) : Base(value) {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "CONS(__m512d value)");

            }


            /**
             * @brief construction default arch
             * @relates float64
             * @remark avx512 - default
             */
            __impl(__m512i value) : Base(_mm512_cvtepi32_pd(value)) {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "CONS(__m512i value)");

            }


            /**
             * @brief construction default arch
             * @relates float64
             * @remark avx512 - default
             */
            __impl(double value) : Base(_mm512_set1_pd(value)) {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "CONS(double value)");

            }


            /**
             * @brief construction default arch
             * @relates float64
             * @remark avx512 - default
             */
            __impl(std::array<typename Base::scalar_t, Base::dim> value) : Base(_mm512_load_pd(value.data())) {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "CONS(std::array<typename Base::scal..)");

            }


            /**
             * @brief construction default arch
             * @relates float64
             * @remark avx512 - default
             */
            __impl(double arg7, double arg6, double arg5, double arg4, double arg3, double arg2, double arg1, double arg0) : Base(_mm512_set_pd(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)) {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "CONS(double arg7, double arg6, double..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float64
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::construction<__impl<Base>, zfloat64<Base::arch>>;

        using impl = traits::construction<__impl<Base>, zfloat64<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float64_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float64
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default arch
             * @relates float64
             * @remark avx512 - default
             */
            void vstore(typename Base::extracted_t &target, Composed source) const noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vstore");

                _mm512_store_pd(target.data(), source);
            }


            /**
             * @brief io default arch
             * @relates float64
             * @remark avx512 - default
             */
            void vstream(typename Base::extracted_t &target, Composed source) const noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vstream");

                _mm512_stream_pd(target.data(), source);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float64
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::io<__impl<Base>, zfloat64<Base::arch>>;

        using impl = traits::io<__impl<Base>, zfloat64<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float64_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates float64
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vneg");

                return _mm512_sub_pd(_mm512_setzero_pd(), one);
            }


            /**
             * @brief arithmetic default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vadd(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vadd");

                return _mm512_add_pd(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vsub(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vsub");

                return _mm512_sub_pd(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vmul(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vmul");

                return _mm512_mul_pd(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vdiv(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vdiv");

                return _mm512_div_pd(one, other);
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float64
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::arithmetic<__impl<Base>, zfloat64<Base::arch>>;

        using impl = traits::arithmetic<__impl<Base>, zfloat64<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float64_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates float64
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vneg");

                auto zero = _mm512_setzero_pd();
                auto ones = _mm512_cmpeq_pd(zero, zero);
                return _mm512_xor_pd(one, ones);
            }


            /**
             * @brief bitwise default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vand(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vand");

                return _mm512_or_pd(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> or(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "or");

                return _mm512_and_pd(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> xor(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "xor");

                return _mm512_xor_pd(one, other);
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates float64
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::bitwise<__impl<Base>, zfloat64<Base::arch>>;

        using impl = traits::bitwise<__impl<Base>, zfloat64<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float64_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates float64
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vneg");

                auto zero = _mm512_setzero_pd();
                auto ones = _mm512_cmpeq_pd(zero, zero);
                return _mm512_xor_pd(one, ones);
            }


            /**
             * @brief logical default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> or(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "or");

                return _mm512_or_pd(one, other);
            }


            /**
             * @brief logical default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vand(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vand");

                return _mm512_and_pd(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates float64
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::logical<__impl<Base>, bfloat64<Base::arch>>;

        using impl = traits::logical<__impl<Base>, zfloat64<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float64_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates float64
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> veq(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "veq");

                return _mm512_cmpeq_pd(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vneq(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vneq");

                return _mm512_cmpneq_pd(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vgt(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vgt");

                return _mm512_cmpgt_pd(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vlt(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vlt");

                return _mm512_cmplt_pd(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vge(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vge");

                return _mm512_cmpge_pd(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vle(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vle");

                return _mm512_cmple_pd(one, other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float64
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::comparable<__impl<Base>, zfloat64<Base::arch>>;

        using impl = traits::comparable<__impl<Base>, zfloat64<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float64_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float64
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default arch
             * @relates float64
             * @remark avx512 - default
             */
            friend zfloat64<Base::arch> vsel(Composed condition, Composed if_value, Composed else_value)  noexcept {

                ZTRACE_BACKEND("avx512.float64.impl", __LINE__, "zfloat64(double[8])", "default", "vsel");

                return _mm512_or_pd(_mm512_andnot_pd(condition, else_value), _mm512_and_pd(condition, if_value));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float64
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::conditional<__impl<Base>, zfloat64<Base::arch>>;

        using impl = traits::conditional<__impl<Base>, zfloat64<Base::arch>>;

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
         * - '__m512d' as underlying vector type
         * - 'double' as scalar type
         * - '8' as vector size
         * - '64' as alignment
         * @relates float64
         * @remark avx512
         */
        template<uint64_t arch>
        struct __zval_float64
        {
            using zval_t = zval<__m512d, __mmask8, double, 8, 64, arch>;

            struct impl : public zval_t
            {
                FORWARD2(impl, zval_t);
            };
        };
        /**
         * @brief zval composition
         * @relates float64
         * @remark avx512
         */
        template<uint64_t arch>
        struct __zfloat64
        {
            struct impl;

            using zval_t = typename __zval_float64<arch>::impl;
            using composition_t = compose
            <
                printable::impl,
                iteratable::impl,
                convertable::impl,
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

        template<uint64_t arch>
        struct __bfloat64
        {
            using bval_t = bval<typename __zfloat64<arch>::impl, __mmask8>;
            struct impl : public bval_t
            {
                FORWARD2(impl, bval_t);
            };
        };
    //}

    template<uint64_t arch>
    struct zfloat64 : public /*composition::*/__zfloat64<arch>::impl
    {
        FORWARD2(zfloat64, /*composition::*/__zfloat64<arch>::impl);
    };

    template<uint64_t arch>
    struct bfloat64 : public /*composition::*/__bfloat64<arch>::impl
    {
        FORWARD2(bfloat64, /*composition::*/__bfloat64<arch>::impl);
    };

    static_assert(is_zval<zfloat64<0>>::value, "is_zval for zfloat64 failed.");
    static_assert(is_bval<bfloat64<0>>::value, "is_bval for bfloat64 failed.");

    static_assert(is_floating_point<zfloat64<0>>::value, "is_floating_point for zfloat64 failed.");
    static_assert(!is_integral<zfloat64<0>>::value, "is_integral for zfloat64 failed.");

    static_assert(!is_float<zfloat64<0>>::value, "is_float for zfloat64 failed.");
    static_assert(is_double<zfloat64<0>>::value, "is_double for zfloat64 failed.");

    ///@}
}}}