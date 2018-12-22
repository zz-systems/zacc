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

/**
 * @file int16.impl.hpp
 * @brief
 * This file provides defines required components and logic for int16 avx2 target.
 * Provides unified access to 16 'int16_t' values
 * @remark
 * This is an autogenerated file. Changes will be lost on regeneration.
 */
#pragma once

#include <type_traits>
#include <cmath>

#include "backend/intrin.hpp"
#include "backend/zval.hpp"

#include "util/type/type_composition.hpp"
#include "util/type/type_traits.hpp"

#include "util/memory.hpp"
#include "util/macros.hpp"

#include "traits/printable.hpp"
#include "traits/bitwise.hpp"
#include "traits/comparable.hpp"
#include "traits/bitwise_shift.hpp"
#include "traits/io.hpp"
#include "traits/logical.hpp"
#include "traits/conditional.hpp"
#include "traits/math.hpp"
#include "traits/equatable.hpp"
#include "traits/arithmetic.hpp"
#include "traits/numeric.hpp"

namespace zacc { namespace backend { namespace avx2
{
    /// @cond
    template<uint64_t features>
    struct bint16;

    template<uint64_t features>
    struct zint16;
    /// @endcond

    template<uint64_t FeatureMask>
    using izint16 = ztype<zval_tag, __m256i, int16_t, 16, 32, FeatureMask>;

    template<uint64_t FeatureMask>
    using ibint16 = ztype<bval_tag, __m256i, int16_t, 16, 32, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for int16 [avx2 branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::avx2::izint16<T::feature_mask>, T>::value
            || std::is_base_of<backend::avx2::ibint16<T::feature_mask>, T>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 16;

        /// capabilities
        static constexpr uint64_t feature_mask = T::feature_mask;

        /// memory alignment
        static constexpr size_t alignment = 32;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = __m256i;

        /// scalar type, like int for sse 4x integer vector
        using element_type = int16_t;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_t = backend::avx2::zint16<T::feature_mask>;
        using bval_t = backend::avx2::bint16<T::feature_mask>;

        using tag = typename T::tag;
    };
}

namespace zacc { namespace backend { namespace avx2
{
    namespace int16_modules
    {
        /**
         * @brief bitwise mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct bitwise : traits::bitwise<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vbneg(Composed one) 
            {
                auto zero = _mm256_setzero_si256();
                auto ones = _mm256_cmpeq_epi16(zero, zero);
                return _mm256_xor_si256(one, ones);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vband(Composed one, Composed other) 
            {
                return _mm256_and_si256(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                return _mm256_or_si256(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                return _mm256_xor_si256(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend bool is_set(Composed one) 
            {
                return _mm256_testc_si256(one, _mm256_cmpeq_epi32(one,one));
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct comparable : traits::comparable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vgt(Composed one, Composed other) 
            {
                return _mm256_cmpgt_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vlt(Composed one, Composed other) 
            {
                return _mm256_cmpgt_epi16(other, one);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vge(Composed one, Composed other) 
            {
                return !(one < other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vle(Composed one, Composed other) 
            {
                return !(one > other);
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise_shift mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct bitwise_shift : traits::bitwise_shift<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vbsll(Composed one, Composed other) 
            {
                return _mm256_sll_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vbsrl(Composed one, Composed other) 
            {
                return _mm256_srl_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vbslli(const Composed one, const size_t other) 
            {
                return _mm256_slli_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vbsrli(const Composed one, const size_t other) 
            {
                return _mm256_srli_epi16(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct io : traits::io<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            template<typename OutputIt> friend void vstore(OutputIt result, Composed input) 
            {
                _mm256_store_si256((__m256i*)&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                _mm256_stream_si256((__m256i*)&(*result), input);
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct logical : traits::logical<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vlneg(Composed one) 
            {
                return _mm256_cmpeq_epi32(one, _mm256_setzero_si256());
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vlor(Composed one, Composed other) 
            {
                return _mm256_or_si256(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vland(Composed one, Composed other) 
            {
                return _mm256_and_si256(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct equatable : traits::equatable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed veq(Composed one, Composed other) 
            {
                return _mm256_cmpeq_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vneq(Composed one, Composed other) 
            {
                return !(one == other);
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct conditional : traits::conditional<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return _mm256_blendv_epi8(else_value, if_value, condition);
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct math : traits::math<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vabs(Composed one) 
            {
                return _mm256_abs_epi16(one);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vmin(Composed one, Composed other) 
            {
                return _mm256_min_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vmax(Composed one, Composed other) 
            {
                return _mm256_max_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vclamp(Composed self, Composed from, Composed to) 
            {
                return vmin(to, vmax(from, self));
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct arithmetic : traits::arithmetic<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vneg(Composed one) 
            {
                return _mm256_sub_epi16(_mm256_setzero_si256(), one);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return _mm256_add_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return _mm256_sub_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vmul(Composed one, Composed other) 
            {
                return _mm256_mullo_epi16(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                auto dividend = one.data();
                auto divisor = other.data();
                typename Composed::extracted_type result;
                for (size_t i = 0; i < Composed::size; i++) { result[i] = dividend[i] / divisor[i]; };
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates int16
             */
            friend Composed vmod(Composed one, Composed other) 
            {
                return vsub(one, vmul(other, vdiv(one, other)));
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [avx2 branch]
         * @relates int16
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };
    } // end int16_modules

    // =================================================================================================================

    /// public zint16 implementation [avx2 branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct zint16 : public zval<izint16<FeatureMask>>,

        // generic traits
        printable<izint16<FeatureMask>, zint16<FeatureMask>>,

        // int16 traits
        int16_modules::io<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::math<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::numeric<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::arithmetic<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::bitwise<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::bitwise_shift<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::comparable<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::equatable<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::conditional<izint16<FeatureMask>, zint16<FeatureMask>, bint16<FeatureMask>>
    {
        USING_ZTYPE(izint16<FeatureMask>);

        /// complete vector
        using zval_t = zint16<FeatureMask>;

        /// complete boolean vector
        using bval_t = bint16<FeatureMask>;

        using zval<izint16<FeatureMask>>::zval;

        /**
         * @brief zint16 constructor [avx2 branch]
         * @relates zint16
         */
        constexpr zint16(__m256i value) noexcept
            : zval<izint16<FeatureMask>>(value)
        {
        }

        /**
         * @brief zint16 constructor [avx2 branch]
         * @relates zint16
         */
        constexpr zint16(int16_t value) noexcept
            : zval<izint16<FeatureMask>>(_mm256_set1_epi16(value))
        {
        }

        /**
         * @brief zint16 constructor [avx2 branch]
         * @relates zint16
         */
        constexpr zint16(extracted_type value) noexcept
            : zval<izint16<FeatureMask>>(_mm256_load_si256((__m256i*)value.data()))
        {
        }

        /**
         * @brief zint16 constructor [avx2 branch]
         * @relates zint16
         */
        constexpr zint16(int16_t _15, int16_t _14, int16_t _13, int16_t _12, int16_t _11, int16_t _10, int16_t _9, int16_t _8, int16_t _7, int16_t _6, int16_t _5, int16_t _4, int16_t _3, int16_t _2, int16_t _1, int16_t _0) noexcept
            : zval<izint16<FeatureMask>>(_mm256_set_epi16(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15))
        {
        }
    };

    // =================================================================================================================

    /// public bint16 implementation [avx2 branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct bint16 : public zval<ibint16<FeatureMask>>,

        // generic traits
        printable<bint16<FeatureMask>, bint16<FeatureMask>>,

        // int16 traits
        int16_modules::io<ibint16<FeatureMask>, bint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::bitwise<ibint16<FeatureMask>, bint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::logical<ibint16<FeatureMask>, bint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::equatable<ibint16<FeatureMask>, bint16<FeatureMask>, bint16<FeatureMask>>
    {
        USING_ZTYPE(ibint16<FeatureMask>);

        /// complete vector
        using zval_t = zint16<FeatureMask>;

        /// complete boolean vector
        using bval_t = bint16<FeatureMask>;

        using zval<ibint16<FeatureMask>>::zval;

        /**
         * @brief bint16 constructor [avx2 branch]
         * @relates bint16
         */
        constexpr bint16(bool value) noexcept
            : zval<ibint16<FeatureMask>>((value ? _mm256_cmpeq_epi16(_mm256_setzero_si256(), _mm256_setzero_si256()) : _mm256_setzero_si256()), (last_operation::boolean))
        {
        }
    };

    // Validate zint16 ===================================================================================

    static_assert( std::is_base_of<izint16<0>, izint16<0>>::value, "base_of<izint16> != izint16.");
    static_assert(!std::is_base_of<ibint16<0>, izint16<0>>::value, "base_of<izint16> == ibint16.");

    static_assert( is_zval<izint16<0>>::value, "is_zval<izint16> == false.");
    static_assert(!is_bval<izint16<0>>::value, "is_bval<izint16> != false.");

    static_assert( std::is_base_of<izint16<0>, zint16<0>>::value, "base_of<zint16> != izint16.");
    static_assert(!std::is_base_of<ibint16<0>, zint16<0>>::value, "base_of<zint16> == ibint16.");

    static_assert(zint16<0>::size == 16, "zint16::size != 16.");
    static_assert(zint16<0>::alignment == 32, "zint16::alignment != 32.");
    static_assert(zint16<0>::is_vector == true, "zint16::is_vector != true.");

    static_assert(std::is_same<zint16<0>::tag, zval_tag>::value, "zint16::tag != zval_tag.");
    static_assert(std::is_same<zint16<0>::vector_type, __m256i>::value, "zint16::vector_type != __m256i.");
    static_assert(std::is_same<zint16<0>::element_type, int16_t>::value, "zint16::element_type != int16_t.");
    static_assert(std::is_same<zint16<0>::extracted_type, std::array<int16_t, 16>>::value, "zint16::extracted_type != std::array<int16_t, 16>.");

    static_assert( is_zval<zint16<0>>::value, "is_zval<zint16> == false.");
    static_assert(!is_bval<zint16<0>>::value, "is_bval<zint16> != false.");

    // Validate bint16 ===================================================================================

    static_assert( std::is_base_of<ibint16<0>, ibint16<0>>::value, "base_of<izint16> != izint16.");
    static_assert(!std::is_base_of<izint16<0>, ibint16<0>>::value, "base_of<izint16> == ibint16.");

    static_assert( is_bval<ibint16<0>>::value, "is_bval<ibint16> == false.");
    static_assert(!is_zval<ibint16<0>>::value, "is_zval<ibint16> != false.");

    static_assert( std::is_base_of<ibint16<0>, bint16<0>>::value, "base_of<bint16> != ibint16.");
    static_assert(!std::is_base_of<izint16<0>, bint16<0>>::value, "base_of<bint16> == izint16.");

    static_assert(bint16<0>::size == 16, "bint16::size != 16.");
    static_assert(bint16<0>::alignment == 32, "bint16::alignment != 32.");
    static_assert(bint16<0>::is_vector == true, "bint16::is_vector != true.");

    static_assert(std::is_same<bint16<0>::tag, bval_tag>::value, "bint16::tag != zval_tag.");
    static_assert(std::is_same<bint16<0>::vector_type, __m256i>::value, "bint16::vector_type != __m256i.");
    static_assert(std::is_same<bint16<0>::element_type, int16_t>::value, "bint16::element_type != int16_t.");
    static_assert(std::is_same<bint16<0>::extracted_type, std::array<int16_t, 16>>::value, "bint16::extracted_type != std::array<int16_t, 16>.");

    static_assert( is_bval<bint16<0>>::value, "is_bval<bint16> == false.");
    static_assert(!is_zval<bint16<0>>::value, "is_zval<bint16> != false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<int16_t>::value || is_floating_point < zint16<0>>::value, "is_floating_point<zint16> == false. [scalar = int16_t]");
    static_assert(!std::is_floating_point<int16_t>::value || !is_integral<zint16<0>>::value, "is_integral<zint16> != false. [scalar = int16_t]");

    static_assert(!std::is_same<int16_t, float>::value || is_float < zint16<0>>::value, "is_float<zint16> == false. [scalar = int16_t]");
    static_assert(!std::is_same<int16_t, float>::value || !is_double < zint16<0>>::value, "is_double<zint16> != false. [scalar = int16_t]");

    static_assert(!std::is_same<int16_t, double>::value || is_double < zint16<0>>::value, "is_double<zint16> == false. [scalar = int16_t]");
    static_assert(!std::is_same<int16_t, double>::value || !is_float < zint16<0>>::value, "is_float<zint16> != false. [scalar = int16_t]");

    static_assert(!std::is_integral<int16_t>::value || is_integral<zint16<0>>::value,"is_integral<zint16> == false. [scalar = int16_t]");
    static_assert(!std::is_integral<int16_t>::value || !is_floating_point < zint16<0>>::value, "is_floating_point<zint16> != false. [scalar = int16_t]");
}}}