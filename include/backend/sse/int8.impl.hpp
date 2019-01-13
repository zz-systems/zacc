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
 * @file int8.impl.hpp
 * @brief
 * This file provides defines required components and logic for int8 sse target.
 * Provides unified access to 16 'int8_t' values
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

#include "system/features.hpp"

#include "traits/printable.hpp"
#include "traits/numeric.hpp"
#include "traits/equatable.hpp"
#include "traits/comparable.hpp"
#include "traits/math.hpp"
#include "traits/bitwise.hpp"
#include "traits/conditional.hpp"
#include "traits/logical.hpp"
#include "traits/arithmetic.hpp"
#include "traits/io.hpp"

namespace zacc { namespace backend { namespace sse
{
    /// @cond
    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct bint8;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct zint8;
    /// @endcond

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using izint8 = ztype<zval_tag, __m128i, int8_t, 16, 16, FeatureMask>;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using ibint8 = ztype<bval_tag, __m128i, int8_t, 16, 16, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for int8 [sse branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::sse::izint8<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value
            || std::is_base_of<backend::sse::ibint8<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 16;

        /// capabilities
        static constexpr uint64_t feature_mask = std::decay_t<T>::feature_mask;

        /// memory alignment
        static constexpr size_t alignment = 16;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = __m128i;

        /// scalar type, like int for sse 4x integer vector
        using element_type = int8_t;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = backend::sse::zint8<std::decay_t<T>::feature_mask>;
        using bval_type = backend::sse::bint8<std::decay_t<T>::feature_mask>;

        using tag = typename std::decay_t<T>::tag;
    };
}

namespace zacc { namespace backend { namespace sse
{
    namespace int8_modules
    {
        /**
         * @brief numeric mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct equatable : traits::equatable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean veq(Composed one, Composed other) 
            {
                return _mm_cmpeq_epi8(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean vneq(Composed one, Composed other) 
            {
                return !(one == other);
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct comparable : traits::comparable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean vgt(Composed one, Composed other) 
            {
                return _mm_cmpgt_epi8(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean vlt(Composed one, Composed other) 
            {
                return _mm_cmplt_epi8(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean vge(Composed one, Composed other) 
            {
                return !(one < other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean vle(Composed one, Composed other) 
            {
                return !(one > other);
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct math : traits::math<Interface, Composed, Boolean>
        {
            /**
             * @brief  [sse4 branch]
             * @relates int8
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse3()), T>
            vabs(Composed one) 
            {
                return _mm_abs_epi8(one);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse3()), T>
            vabs(Composed one) 
            {
                return vmax(one, -one);
            }

            /**
             * @brief  [sse4 branch]
             * @relates int8
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vmin(Composed one, Composed other) 
            {
                return _mm_min_epi8(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vmin(Composed one, Composed other) 
            {
                return vsel(one < other, one, other);
            }

            /**
             * @brief  [sse4 branch]
             * @relates int8
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vmax(Composed one, Composed other) 
            {
                return _mm_max_epi8(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vmax(Composed one, Composed other) 
            {
                return vsel(one > other, one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vclamp(Composed self, Composed from, Composed to) 
            {
                return vmin(to, vmax(from, self));
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct bitwise : traits::bitwise<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vbneg(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi8(zero, zero);
                return _mm_xor_si128(one, ones);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                return _mm_or_si128(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vband(Composed one, Composed other) 
            {
                return _mm_and_si128(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                return _mm_xor_si128(one, other);
            }

            /**
             * @brief  [sse4 branch]
             * @relates int8
             */
            template<typename T = bool>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vis_set(Composed one) 
            {
                return _mm_test_all_ones(one) != 0;
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename T = bool>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vis_set(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi32(zero, zero);
                return _mm_movemask_epi8(_mm_cmpeq_epi8(one, ones)) == 0xFFFF;
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct conditional : traits::conditional<Interface, Composed, Boolean>
        {
            /**
             * @brief  [sse4 branch]
             * @relates int8
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return _mm_blendv_epi8(else_value, if_value, condition);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return _mm_or_si128(_mm_andnot_si128(condition, else_value), _mm_and_si128(condition, if_value));
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct logical : traits::logical<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean vlneg(Composed one) 
            {
                return _mm_cmpeq_epi8(one, _mm_setzero_si128());
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean vlor(Composed one, Composed other) 
            {
                return _mm_or_si128(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Boolean vland(Composed one, Composed other) 
            {
                return _mm_and_si128(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct arithmetic : traits::arithmetic<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vneg(Composed one) 
            {
                return _mm_sub_epi8(_mm_setzero_si128(), one);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return _mm_add_epi8(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return _mm_sub_epi8(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vmul(Composed one, Composed other) 
            {
                /// @see http://stackoverflow.com/a/29155682/1261537;
                auto even = _mm_mullo_epi16(one, other);
                auto odd  = _mm_mullo_epi16(_mm_srli_epi16(one, 8),_mm_srli_epi16(other, 8));
                return _mm_or_si128(_mm_slli_epi16(odd, 8), _mm_and_si128(even, _mm_set1_epi16(0xFF)));
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                auto dividend = one.data();
                auto divisor = other.data();
                alignas(Composed::alignment) typename Composed::extracted_type result;
                for (size_t i = 0; i < Composed::size; i++) { result[i] = dividend[i] / divisor[i]; };
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend Composed vmod(Composed one, Composed other) 
            {
                return vsub(one, vmul(other, vdiv(one, other)));
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation [sse branch]
         * @relates int8
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct io : traits::io<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename OutputIt> friend void vstore(OutputIt result, Composed input) 
            {
                _mm_store_si128((__m128i*)&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                _mm_stream_si128((__m128i*)&(*result), input);
            }
        };
    } // end int8_modules

    // =================================================================================================================

    /// public zint8 implementation [sse branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct zint8 : public zval<izint8<FeatureMask>>,

        // generic traits
        printable<izint8<FeatureMask>, zint8<FeatureMask>>,

        // int8 traits
        int8_modules::io<izint8<FeatureMask>, zint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::math<izint8<FeatureMask>, zint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::numeric<izint8<FeatureMask>, zint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::arithmetic<izint8<FeatureMask>, zint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::bitwise<izint8<FeatureMask>, zint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::comparable<izint8<FeatureMask>, zint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::equatable<izint8<FeatureMask>, zint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::conditional<izint8<FeatureMask>, zint8<FeatureMask>, bint8<FeatureMask>>
    {
        USING_ZTYPE(zval<izint8<FeatureMask>>);
        using zval<izint8<FeatureMask>>::zval;


        template<typename T, std::enable_if_t<std::is_same<T, view_t<izint8<FeatureMask>>>::value && !is_vector, void**> = nullptr>
        constexpr zint8(const T& view) noexcept
                : zint8(view[0])
        {}

        template<typename T, typename std::enable_if<is_zval<T>::value, void**>::type = nullptr>
        constexpr zint8(const T& other) noexcept
                : zint8(other.value())
        {}

        explicit constexpr zint8(const bval_t<izint8<FeatureMask>>& other) noexcept
                : zint8(other.value())
        {}

        /**
         * @brief zint8 constructor [sse branch]
         * @relates zint8
         */
        constexpr zint8(__m128i value) noexcept
            : zval<izint8<FeatureMask>>(value)
        {
        }

        /**
         * @brief zint8 constructor [sse branch]
         * @relates zint8
         */
        constexpr zint8(int8_t value) noexcept
            : zval<izint8<FeatureMask>>(_mm_set1_epi8(value))
        {
        }

        /**
         * @brief zint8 constructor [sse branch]
         * @relates zint8
         */
        constexpr zint8(const extracted_type &value) noexcept
            : zval<izint8<FeatureMask>>(_mm_load_si128((__m128i*)value.data()))
        {
        }

        /**
         * @brief zint8 constructor [sse branch]
         * @relates zint8
         */
        constexpr zint8(int8_t _15, int8_t _14, int8_t _13, int8_t _12, int8_t _11, int8_t _10, int8_t _9, int8_t _8, int8_t _7, int8_t _6, int8_t _5, int8_t _4, int8_t _3, int8_t _2, int8_t _1, int8_t _0) noexcept
            : zval<izint8<FeatureMask>>(_mm_set_epi8(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15))
        {
        }
    };

    // =================================================================================================================

    /// public bint8 implementation [sse branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct bint8 : public zval<ibint8<FeatureMask>>,

        // generic traits
        printable<bint8<FeatureMask>, bint8<FeatureMask>>,

        // int8 traits
        int8_modules::io<ibint8<FeatureMask>, bint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::bitwise<ibint8<FeatureMask>, bint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::logical<ibint8<FeatureMask>, bint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::equatable<ibint8<FeatureMask>, bint8<FeatureMask>, bint8<FeatureMask>>
    {
        USING_ZTYPE(zval<ibint8<FeatureMask>>);
        using zval<ibint8<FeatureMask>>::zval;

        template<typename T, std::enable_if_t<std::is_same<T, view_t<ibint8<FeatureMask>>>::value && !is_vector, void**> = nullptr>
        constexpr bint8(const T& view) noexcept
                : bint8((view[0]))
        {}

        template<typename T, typename std::enable_if<is_zval<T>::value || is_bval<T>::value, void**>::type = nullptr>
        constexpr bint8(const T& other) noexcept
                : bint8(other.value())
        {
            //static_assert(size_v<T> == 16, "Dimension mismatch");
        }

        /**
         * @brief bint8 constructor [sse branch]
         * @relates bint8
         */
        constexpr bint8(bool value) noexcept
            : zval<ibint8<FeatureMask>>((value ? _mm_cmpeq_epi8(_mm_setzero_si128(), _mm_setzero_si128()) : _mm_setzero_si128()))
        {
        }
    };

    // Validate zint8 ===================================================================================

#define params 0

    static_assert( is_vector_v<izint8<params>> == true,    "is_vector_v<izint8> != true.");
    static_assert( is_vector_v<ibint8<params>> == true,    "is_vector_v<ibint8> != true.");

    static_assert( std::is_same<element_t<ibint8<params>>, int8_t>::value,    "element_t<ibint8> != int8_t.");

    static_assert( std::is_same<element_t<izint8<params>>, int8_t>::value,    "element_t<izint8> != int8_t.");
    static_assert( std::is_same<element_t<ibint8<params>>, int8_t>::value,    "element_t<ibint8> != int8_t.");

    static_assert( std::is_same<vector_t<izint8<params>>, __m128i>::value,    "vector_t<izint8> != __m128i.");
    static_assert( std::is_same<vector_t<ibint8<params>>, __m128i>::value,    "vector_t<ibint8> != __m128i.");

    static_assert( std::is_same<view_t<izint8<params>>, std::array<int8_t, 16>>::value,    "view_t<izint8> != std::array<int8_t, 16>.");
    static_assert( std::is_same<view_t<ibint8<params>>, std::array<bool, 16>>::value,                        "view_t<ibint8> != std::array<bool, 16>.");

//
    static_assert( std::is_base_of<izint8<params>, izint8<params>>::value, "base_of<izint8> != izint8.");
    static_assert(!std::is_base_of<ibint8<params>, izint8<params>>::value, "base_of<izint8> == ibint8.");

    static_assert( is_zval<izint8<params>>::value, "is_zval<izint8> == false.");
    static_assert(!is_bval<izint8<params>>::value, "is_bval<izint8> != false.");

    static_assert( std::is_base_of<izint8<params>, zint8<params>>::value, "base_of<zint8> != izint8.");
    static_assert(!std::is_base_of<ibint8<params>, zint8<params>>::value, "base_of<zint8> == ibint8.");

    static_assert(zint8<params>::size == 16, "zint8::size != 16.");
    static_assert(zint8<params>::alignment == 16, "zint8::alignment != 16.");
    static_assert(zint8<params>::is_vector == true, "zint8::is_vector != true.");

    static_assert(std::is_same<zint8<params>::tag, zval_tag>::value, "zint8::tag != zval_tag.");
    static_assert(std::is_same<zint8<params>::vector_type, __m128i>::value, "zint8::vector_type != __m128i.");
    static_assert(std::is_same<zint8<params>::element_type, int8_t>::value, "zint8::element_type != int8_t.");
    static_assert(std::is_same<zint8<params>::extracted_type, std::array<int8_t, 16>>::value, "zint8::extracted_type != std::array<int8_t, 16>.");

    static_assert( is_zval<zint8<params>>::value, "is_zval<zint8> == false.");
    static_assert(!is_bval<zint8<params>>::value, "is_bval<zint8> != false.");

    // Validate bint8 ===================================================================================

    static_assert( std::is_base_of<ibint8<params>, ibint8<params>>::value, "base_of<izint8> != izint8.");
    static_assert(!std::is_base_of<izint8<params>, ibint8<params>>::value, "base_of<izint8> == ibint8.");

    static_assert( is_bval<ibint8<params>>::value, "is_bval<ibint8> == false.");
    static_assert(!is_zval<ibint8<params>>::value, "is_zval<ibint8> != false.");

    static_assert( std::is_base_of<ibint8<params>, bint8<params>>::value, "base_of<bint8> != ibint8.");
    static_assert(!std::is_base_of<izint8<params>, bint8<params>>::value, "base_of<bint8> == izint8.");

    static_assert(bint8<params>::size == 16, "bint8::size != 16.");
    static_assert(bint8<params>::alignment == 16, "bint8::alignment != 16.");
    static_assert(bint8<params>::is_vector == true, "bint8::is_vector != true.");

    static_assert(std::is_same<bint8<params>::tag, bval_tag>::value, "bint8::tag != zval_tag.");
    static_assert(std::is_same<bint8<params>::vector_type, __m128i>::value, "bint8::vector_type != __m128i.");
    static_assert(std::is_same<bint8<params>::element_type, int8_t>::value, "bint8::element_type != int8_t.");
    static_assert(std::is_same<bint8<params>::extracted_type, std::array<int8_t, 16>>::value, "bint8::extracted_type != std::array<int8_t, 16>.");

    static_assert( is_bval<bint8<params>>::value, "is_bval<bint8> == false.");
    static_assert(!is_zval<bint8<params>>::value, "is_zval<bint8> != false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<int8_t>::value || is_floating_point < zint8<params>>::value, "is_floating_point<zint8> == false. [scalar = int8_t]");
    static_assert(!std::is_floating_point<int8_t>::value || !is_integral<zint8<params>>::value, "is_integral<zint8> != false. [scalar = int8_t]");

    static_assert(!std::is_same<int8_t, float>::value || is_float < zint8<params>>::value, "is_float<zint8> == false. [scalar = int8_t]");
    static_assert(!std::is_same<int8_t, float>::value || !is_double < zint8<params>>::value, "is_double<zint8> != false. [scalar = int8_t]");

    static_assert(!std::is_same<int8_t, double>::value || is_double < zint8<params>>::value, "is_double<zint8> == false. [scalar = int8_t]");
    static_assert(!std::is_same<int8_t, double>::value || !is_float < zint8<params>>::value, "is_float<zint8> != false. [scalar = int8_t]");

    static_assert(!std::is_integral<int8_t>::value || is_integral<zint8<params>>::value,"is_integral<zint8> == false. [scalar = int8_t]");
    static_assert(!std::is_integral<int8_t>::value || !is_floating_point < zint8<params>>::value, "is_floating_point<zint8> != false. [scalar = int8_t]");
}}}