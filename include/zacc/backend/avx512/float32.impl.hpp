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

#include <zacc/backend/intrin.hpp>
#include <zacc/backend/intrin.ext.hpp>
#include <zacc/backend/zval.hpp>

#include <zacc/util/type/compose.hpp>
#include <zacc/util/type/type_traits.hpp>

#include <zacc/util/memory.hpp>
#include <zacc/util/macros.hpp>

#include <zacc/system/feature.hpp>

#include <zacc/traits/printable.hpp>
#include <zacc/traits/io.hpp>
#include <zacc/traits/math.hpp>
#include <zacc/traits/numeric.hpp>
#include <zacc/traits/bitwise.hpp>
#include <zacc/traits/bitwise_shift.hpp>
#include <zacc/traits/comparable.hpp>
#include <zacc/traits/logical.hpp>
#include <zacc/traits/equatable.hpp>
#include <zacc/traits/conditional.hpp>
#include <zacc/traits/arithmetic.hpp>

/**
 * @brief float32 implementation for the avx512 arch
 * provides unified access to 16 'float' values
 */

namespace zacc { namespace backend { namespace avx512 {

    template<uint64_t arch>
    struct bfloat32;

    template<uint64_t arch>
    struct zfloat32;


    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates float32
     * @remark avx512
     */
    template<typename Composed>
    struct float32_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates float32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;



            /**
             * @brief construction default arch
             * @relates float32
             * @remark avx512 - default
             */
            __impl() : Base() {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "CONS()");

            }


            /**
             * @brief construction default arch
             * @relates float32
             * @remark avx512 - default
             */
            __impl(__m512 value) : Base(value) {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "CONS(__m512 value)");

            }


            /**
             * @brief construction default arch
             * @relates float32
             * @remark avx512 - default
             */
            __impl(__m512d value) : Base(_mm512_cvtpd_ps(value)) {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "CONS(__m512d value)");

            }


            /**
             * @brief construction default arch
             * @relates float32
             * @remark avx512 - default
             */
            __impl(__m512i value) : Base(_mm512_cvtepi32_ps(value)) {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "CONS(__m512i value)");

            }


            /**
             * @brief construction default arch
             * @relates float32
             * @remark avx512 - default
             */
            __impl(float value) : Base(_mm512_set1_ps(value)) {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "CONS(float value)");

            }


            /**
             * @brief construction default arch
             * @relates float32
             * @remark avx512 - default
             */
            __impl(std::array<typename Base::scalar_t, Base::dim> value) : Base(_mm512_load_ps(value.data())) {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "CONS(std::array<typename Base::scal..)");

            }


            /**
             * @brief construction default arch
             * @relates float32
             * @remark avx512 - default
             */
            __impl(float arg15, float arg14, float arg13, float arg12, float arg11, float arg10, float arg9, float arg8, float arg7, float arg6, float arg5, float arg4, float arg3, float arg2, float arg1, float arg0) : Base(_mm512_set_ps(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)) {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "CONS(float arg15, float arg14, float ..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::construction<__impl<Base>, zfloat32<Base::arch>>;

        using impl = traits::construction<__impl<Base>, zfloat32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float32_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default arch
             * @relates float32
             * @remark avx512 - default
             */
            void vstore(typename Base::extracted_t &target, Composed source) const noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vstore");

                _mm512_store_ps(target.data(), source);
            }


            /**
             * @brief io default arch
             * @relates float32
             * @remark avx512 - default
             */
            void vstream(typename Base::extracted_t &target, Composed source) const noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vstream");

                _mm512_stream_ps(target.data(), source);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::io<__impl<Base>, zfloat32<Base::arch>>;

        using impl = traits::io<__impl<Base>, zfloat32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float32_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates float32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vneg");

                return _mm512_sub_ps(_mm512_setzero_ps(), one);
            }


            /**
             * @brief arithmetic default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vadd(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vadd");

                return _mm512_add_ps(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vsub(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vsub");

                return _mm512_sub_ps(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vmul(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vmul");

                return _mm512_mul_ps(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vdiv(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vdiv");

                return _mm512_div_ps(one, other);
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::arithmetic<__impl<Base>, zfloat32<Base::arch>>;

        using impl = traits::arithmetic<__impl<Base>, zfloat32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float32_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates float32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vneg");

                auto zero = _mm512_setzero_ps();
                auto ones = _mm512_cmpeq_ps(zero, zero);
                return _mm512_xor_ps(one, ones);
            }


            /**
             * @brief bitwise default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vand(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vand");

                return _mm512_or_ps(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> or(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "or");

                return _mm512_and_ps(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> xor(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "xor");

                return _mm512_xor_ps(one, other);
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates float32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::bitwise<__impl<Base>, zfloat32<Base::arch>>;

        using impl = traits::bitwise<__impl<Base>, zfloat32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float32_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates float32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vneg");

                auto zero = _mm512_setzero_ps();
                auto ones = _mm512_cmpeq_ps(zero, zero);
                return _mm512_xor_ps(one, ones);
            }


            /**
             * @brief logical default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> or(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "or");

                return _mm512_or_ps(one, other);
            }


            /**
             * @brief logical default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vand(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vand");

                return _mm512_and_ps(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates float32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::logical<__impl<Base>, bfloat32<Base::arch>>;

        using impl = traits::logical<__impl<Base>, zfloat32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float32_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates float32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> veq(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "veq");

                return _mm512_cmpeq_ps(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vneq(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vneq");

                return _mm512_cmpneq_ps(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vgt(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vgt");

                return _mm512_cmpgt_ps(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vlt(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vlt");

                return _mm512_cmplt_ps(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vge(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vge");

                return _mm512_cmpge_ps(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vle(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vle");

                return _mm512_cmple_ps(one, other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::comparable<__impl<Base>, zfloat32<Base::arch>>;

        using impl = traits::comparable<__impl<Base>, zfloat32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct float32_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default arch
             * @relates float32
             * @remark avx512 - default
             */
            friend zfloat32<Base::arch> vsel(Composed condition, Composed if_value, Composed else_value)  noexcept {

                ZTRACE_BACKEND("avx512.float32.impl", __LINE__, "zfloat32(float[16])", "default", "vsel");

                return _mm512_or_ps(_mm512_andnot_ps(condition, else_value), _mm512_and_ps(condition, if_value));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::conditional<__impl<Base>, zfloat32<Base::arch>>;

        using impl = traits::conditional<__impl<Base>, zfloat32<Base::arch>>;

    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float32 composition
     */
    ///@{

    //namespace composition {

        /**
         * @brief zval parametrization using
         * - '__m512' as underlying vector type
         * - 'float' as scalar type
         * - '16' as vector size
         * - '64' as alignment
         * @relates float32
         * @remark avx512
         */
        template<uint64_t arch>
        struct __zval_float32
        {
            using zval_t = zval<__m512, __mmask16, float, 16, 64, arch>;

            struct impl : public zval_t
            {
                FORWARD2(impl, zval_t);
            };
        };
        /**
         * @brief zval composition
         * @relates float32
         * @remark avx512
         */
        template<uint64_t arch>
        struct __zfloat32
        {
            struct impl;

            using zval_t = typename __zval_float32<arch>::impl;
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

        template<uint64_t arch>
        struct __bfloat32
        {
            using bval_t = bval<typename __zfloat32<arch>::impl, __mmask16>;
            struct impl : public bval_t
            {
                FORWARD2(impl, bval_t);
            };
        };
    //}

    template<uint64_t arch>
    struct zfloat32 : public /*composition::*/__zfloat32<arch>::impl
    {
        FORWARD2(zfloat32, /*composition::*/__zfloat32<arch>::impl);
    };

    template<uint64_t arch>
    struct bfloat32 : public /*composition::*/__bfloat32<arch>::impl
    {
        FORWARD2(bfloat32, /*composition::*/__bfloat32<arch>::impl);
    };

    static_assert(is_zval<zfloat32<0>>::value, "is_zval for zfloat32 failed.");
    static_assert(is_bval<bfloat32<0>>::value, "is_bval for bfloat32 failed.");

    static_assert(is_floating_point<zfloat32<0>>::value, "is_floating_point for zfloat32 failed.");
    static_assert(!is_integral<zfloat32<0>>::value, "is_integral for zfloat32 failed.");

    static_assert(is_float<zfloat32<0>>::value, "is_float for zfloat32 failed.");
    static_assert(!is_double<zfloat32<0>>::value, "is_double for zfloat32 failed.");

    ///@}
}}}