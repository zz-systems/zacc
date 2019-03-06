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
 * @brief int32 implementation for the avx512 arch
 * provides unified access to 16 'int32_t' values
 */

namespace zacc { namespace backend { namespace avx512 {

    template<uint64_t arch>
    struct bint32;

    template<uint64_t arch>
    struct zint32;


    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates int32
     * @remark avx512
     */
    template<typename Composed>
    struct int32_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;



            /**
             * @brief construction default arch
             * @relates int32
             * @remark avx512 - default
             */
            __impl() : Base() {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "CONS()");

            }


            /**
             * @brief construction default arch
             * @relates int32
             * @remark avx512 - default
             */
            __impl(__m512i value) : Base(value) {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "CONS(__m512i value)");

            }


            /**
             * @brief construction default arch
             * @relates int32
             * @remark avx512 - default
             */
            __impl(int32_t value) : Base(_mm512_set1_epi8(value)) {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "CONS(int32_t value)");

            }


            /**
             * @brief construction default arch
             * @relates int32
             * @remark avx512 - default
             */
            __impl(std::array<typename Base::scalar_t, Base::dim> value) : Base(_mm512_load_si512(value.data())) {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "CONS(std::array<typename Base::scal..)");

            }


            /**
             * @brief construction default arch
             * @relates int32
             * @remark avx512 - default
             */
            __impl(int32_t arg15, int32_t arg14, int32_t arg13, int32_t arg12, int32_t arg11, int32_t arg10, int32_t arg9, int32_t arg8, int32_t arg7, int32_t arg6, int32_t arg5, int32_t arg4, int32_t arg3, int32_t arg2, int32_t arg1, int32_t arg0) : Base(_mm512_set_epi8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)) {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "CONS(int32_t arg15, int32_t arg14, in..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::construction<__impl<Base>, zint32<Base::arch>>;

        using impl = traits::construction<__impl<Base>, zint32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct int32_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend void vstore(typename Base::extracted_t &target, Composed source) const noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vstore");

                _mm512_store_si512(target.data(), source);
            }


            /**
             * @brief io default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend void vstream(typename Base::extracted_t &target, Composed source) const noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vstream");

                _mm512_stream_si512(target.data(), source);
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::io<__impl<Base>, zint32<Base::arch>>;

        using impl = traits::io<__impl<Base>, zint32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct int32_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vneg");

                return _mm512_sub_epi32(_mm512_setzero_epi32(), one);
            }


            /**
             * @brief arithmetic default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vadd(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vadd");

                return _mm512_add_epi32(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vsub(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vsub");

                return _mm512_sub_epi32(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vmul(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vmul");

                return _mm512_mullo_epi32(one, other);
            }


            /**
             * @brief arithmetic default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vdiv(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vdiv");

                return _mm512_div_ps(_mm512_cvtepi32_ps(one), _mm512_cvtepi32_ps(other));
            }


            /**
             * @brief arithmetic default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vmod(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vmod");

                return vsub(one, vmul(other, vdiv(one, other)));
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::arithmetic<__impl<Base>, zint32<Base::arch>>;

        using impl = traits::arithmetic<__impl<Base>, zint32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct int32_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vneg");

                auto zero = _mm512_setzero_si128();
                auto ones = _mm512_cmpeq_epi32(zero, zero);
                return _mm512_xor_si128(one, ones);
            }


            /**
             * @brief bitwise default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vand(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vand");

                return _mm512_or_epi32(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> or(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "or");

                return _mm512_and_epi32(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> xor(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "xor");

                return _mm512_xor_si128(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vsll(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vsll");

                return _mm512_sll_epi32(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vsrl(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vsrl");

                return _mm512_srl_epi32(one, other);
            }


            /**
             * @brief bitwise default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vslli(const Composed one, const size_t other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vslli");

                return _mm512_slli_epi32(const Composed one, const size_t other);
            }


            /**
             * @brief bitwise default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vsrli(const Composed one, const size_t other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vsrli");

                return _mm512_srli_epi32(const Composed one, const size_t other);
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::bitwise<__impl<Base>, zint32<Base::arch>>;

        using impl = traits::bitwise<__impl<Base>, zint32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct int32_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates int32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vneg(Composed one)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vneg");

                auto zero = _mm512_setzero_si128();
                auto ones = _mm512_cmpeq_epi32(zero, zero);
                return _mm512_xor_si128(one, ones);
            }


            /**
             * @brief logical default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> or(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "or");

                return _mm512_or_epi32(one, other);
            }


            /**
             * @brief logical default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vand(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vand");

                return _mm512_and_epi32(one, other);
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates int32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::logical<__impl<Base>, bint32<Base::arch>>;

        using impl = traits::logical<__impl<Base>, zint32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct int32_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> veq(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "veq");

                return _mm512_cmpeq_epi32(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vneq(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vneq");

                return _mm512_cmpneq_epi32(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vgt(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vgt");

                return _mm512_cmpgt_epi32(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vlt(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vlt");

                return _mm512_cmplt_epi32(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vge(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vge");

                return _mm512_cmpge_epi32(one, other);
            }


            /**
             * @brief comparison default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vle(Composed one, Composed other)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vle");

                return _mm512_cmple_epi32(one, other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::comparable<__impl<Base>, zint32<Base::arch>>;

        using impl = traits::comparable<__impl<Base>, zint32<Base::arch>>;

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
     * @remark avx512
     */
    template<typename Composed>
    struct int32_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int32
         * @remark avx512
         */
        template<typename Base>
        struct __impl : Base
        {
            using mask_t = typename Base::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default arch
             * @relates int32
             * @remark avx512 - default
             */
            friend zint32<Base::arch> vsel(Composed condition, Composed if_value, Composed else_value)  noexcept {

                ZTRACE_BACKEND("avx512.int32.impl", __LINE__, "zint32(int32_t[16])", "default", "vsel");

                return _mm512_or_si128(_mm512_andnot_si128(condition, else_value), _mm512_and_si128(condition, if_value));
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int32
         * @remark avx512
         */


        template<typename Base>
        //using impl = traits::conditional<__impl<Base>, zint32<Base::arch>>;

        using impl = traits::conditional<__impl<Base>, zint32<Base::arch>>;

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
         * - '__m512i' as underlying vector type
         * - 'int32_t' as scalar type
         * - '16' as vector size
         * - '64' as alignment
         * @relates int32
         * @remark avx512
         */
        template<uint64_t arch>
        struct __zval_int32
        {
            using zval_t = zval<__m512i, __mmask16, int32_t, 16, 64, arch>;

            struct impl : public zval_t
            {
                FORWARD2(impl, zval_t);
            };
        };
        /**
         * @brief zval composition
         * @relates int32
         * @remark avx512
         */
        template<uint64_t arch>
        struct __zint32
        {
            struct impl;

            using zval_t = typename __zval_int32<arch>::impl;
            using composition_t = compose
            <
                printable::impl,
                iteratable::impl,
                convertable::impl,
                int32_io<impl>::template impl,
                int32_arithmetic<impl>::template impl,
                int32_bitwise<impl>::template impl,
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

        template<uint64_t arch>
        struct __bint32
        {
            using bval_t = bval<typename __zint32<arch>::impl, __mmask16>;
            struct impl : public bval_t
            {
                FORWARD2(impl, bval_t);
            };
        };
    //}

    template<uint64_t arch>
    struct zint32 : public /*composition::*/__zint32<arch>::impl
    {
        FORWARD2(zint32, /*composition::*/__zint32<arch>::impl);
    };

    template<uint64_t arch>
    struct bint32 : public /*composition::*/__bint32<arch>::impl
    {
        FORWARD2(bint32, /*composition::*/__bint32<arch>::impl);
    };

    static_assert(is_zval<zint32<0>>::value, "is_zval for zint32 failed.");
    static_assert(is_bval<bint32<0>>::value, "is_bval for bint32 failed.");

    static_assert(!is_floating_point<zint32<0>>::value, "is_floating_point for zint32 failed.");
    static_assert(is_integral<zint32<0>>::value, "is_integral for zint32 failed.");

    static_assert(!is_float<zint32<0>>::value, "is_float for zint32 failed.");
    static_assert(!is_double<zint32<0>>::value, "is_double for zint32 failed.");

    ///@}
}}}