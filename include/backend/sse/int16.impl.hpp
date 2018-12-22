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
 * This file provides defines required components and logic for int16 sse target.
 * Provides unified access to 8 'int16_t' values
 * @remark
 * This is an autogenerated file. Changes will be lost on regeneration.
 */
#pragma once

#include <type_traits>
#include <cmath>

#include "backend/intrin.hpp"
#include "backend/zval.hpp"
#include "backend/zval_interface.hpp"

#include "util/type/type_composition.hpp"
#include "util/type/type_traits.hpp"

#include "util/memory.hpp"
#include "util/macros.hpp"

#include "traits/convertable.hpp"
#include "traits/printable.hpp"
#include "traits/arithmetic.hpp"
#include "traits/logical.hpp"
#include "traits/math.hpp"
#include "traits/io.hpp"
#include "traits/bitwise_shift.hpp"
#include "traits/conditional.hpp"
#include "traits/bitwise.hpp"
#include "traits/equatable.hpp"
#include "traits/comparable.hpp"
#include "traits/numeric.hpp"

namespace zacc { namespace backend { namespace sse
{
    /// @cond
    template<uint64_t features>
    struct bint16;

    template<uint64_t features>
    struct zint16;
    /// @endcond
    
    template<uint64_t FeatureMask>
    using izint16 = ztype<zval_tag, __m128i, __m128i, int16_t, 8, 16, FeatureMask>;

    template<uint64_t FeatureMask>
    using ibint16 = ztype<bval_tag, __m128i, __m128i, int16_t, 8, 16, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for int16 [sse branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::sse::izint16<T::feature_mask>, T>::value
            || std::is_base_of<backend::sse::ibint16<T::feature_mask>, T>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 8;

        /// capabilities
        static constexpr uint64_t feature_mask = T::feature_mask;

        /// memory alignment
        static constexpr size_t alignment = 16;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = __m128i;

        /// scalar type, like int for sse 4x integer vector
        using element_type = int16_t;

        /// mask type for boolean operations
        using mask_vector_type = __m128i;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_t = backend::sse::zint16<T::feature_mask>;
        using bval_t = backend::sse::bint16<T::feature_mask>;

        using tag = select_t<
            when<std::is_base_of<backend::sse::izint16<T::feature_mask>, T>::value, zval_tag>,
            when<std::is_base_of<backend::sse::ibint16<T::feature_mask>, T>::value, bval_tag>>;
    };
}

namespace zacc { namespace backend { namespace sse
{
    namespace int16_modules
    {
        /**
         * @brief io mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct io : traits::io<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief io [default branch]
             * @relates int16
             */
            template<typename OutputIt> friend void vstore(OutputIt result, Composed input) 
            {
                _mm_store_si128((__m128i*)&(*result), input);
            }
            
            /**
             * @brief io [default branch]
             * @relates int16
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                _mm_stream_si128((__m128i*)&(*result), input);
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct math : traits::math<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief math [sse4 branch]
             * @relates int16
             */
            template<typename T = zint16<Interface::feature_mask>> friend std::enable_if_t<has_feature_v<Interface, capabilities::SSE3>, T> vabs(Composed one) 
            {
                return _mm_abs_epi16(one);
            }
            
            /**
             * @brief math [default branch]
             * @relates int16
             */
            template<typename T = zint16<Interface::feature_mask>> friend std::enable_if_t<!has_feature_v<Interface, capabilities::SSE3>, T> vabs(Composed one) 
            {
                return vmax(one, -one);
            }
            
            /**
             * @brief math [sse4 branch]
             * @relates int16
             */
            template<typename T = zint16<Interface::feature_mask>> friend std::enable_if_t<has_feature_v<Interface, capabilities::SSE41>, T> vmin(Composed one, Composed other) 
            {
                return _mm_min_epi16(one, other);
            }
            
            /**
             * @brief math [default branch]
             * @relates int16
             */
            template<typename T = zint16<Interface::feature_mask>> friend std::enable_if_t<!has_feature_v<Interface, capabilities::SSE41>, T> vmin(Composed one, Composed other) 
            {
                return vsel(one < other, one, other);
            }
            
            /**
             * @brief math [sse4 branch]
             * @relates int16
             */
            template<typename T = zint16<Interface::feature_mask>> friend std::enable_if_t<has_feature_v<Interface, capabilities::SSE41>, T> vmax(Composed one, Composed other) 
            {
                return _mm_max_epi16(one, other);
            }
            
            /**
             * @brief math [default branch]
             * @relates int16
             */
            template<typename T = zint16<Interface::feature_mask>> friend std::enable_if_t<!has_feature_v<Interface, capabilities::SSE41>, T> vmax(Composed one, Composed other) 
            {
                return vsel(one > other, one, other);
            }
            
            /**
             * @brief math [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vclamp(Composed self, Composed from, Composed to) 
            {
                return vmin(to, vmax(from, self));
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct numeric : traits::numeric<Interface, Composed, bint16<Interface::feature_mask>>
        {
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct arithmetic : traits::arithmetic<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief arithmetic [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vneg(Composed one) 
            {
                return _mm_sub_epi16(_mm_setzero_si128(), one);
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vadd(Composed one, Composed other) 
            {
                return _mm_add_epi16(one, other);
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vsub(Composed one, Composed other) 
            {
                return _mm_sub_epi16(one, other);
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vmul(Composed one, Composed other) 
            {
                return _mm_mullo_epi16(one, other);
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vdiv(Composed one, Composed other) 
            {
                auto dividend = one.data();
                auto divisor = other.data();
                typename Composed::extracted_type result;
                for (size_t i = 0; i < Composed::size; i++) { result[i] = dividend[i] / divisor[i]; };
                return result;
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vmod(Composed one, Composed other) 
            {
                return vsub(one, vmul(other, vdiv(one, other)));
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct bitwise : traits::bitwise<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief bitwise [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vbneg(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi16(zero, zero);
                return _mm_xor_si128(one, ones);
            }
            
            /**
             * @brief bitwise [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vbor(Composed one, Composed other) 
            {
                return _mm_or_si128(one, other);
            }
            
            /**
             * @brief bitwise [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vband(Composed one, Composed other) 
            {
                return _mm_and_si128(one, other);
            }
            
            /**
             * @brief bitwise [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vbxor(Composed one, Composed other) 
            {
                return _mm_xor_si128(one, other);
            }
            
            /**
             * @brief bitwise [sse4 branch]
             * @relates int16
             */
            template<typename T = bool> friend std::enable_if_t<has_feature_v<Interface, capabilities::SSE41>, T> is_set(Composed one) 
            {
                return _mm_test_all_ones(one) != 0;
            }
            
            /**
             * @brief bitwise [default branch]
             * @relates int16
             */
            template<typename T = bool> friend std::enable_if_t<!has_feature_v<Interface, capabilities::SSE41>, T> is_set(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi32(zero, zero);
                return _mm_movemask_epi8(_mm_cmpeq_epi16(one, ones)) == 0xFFFF;
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise_shift mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct bitwise_shift : traits::bitwise_shift<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief bitwise_shift [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vbsll(Composed one, Composed other) 
            {
                return _mm_sll_epi16(one, other);
            }
            
            /**
             * @brief bitwise_shift [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vbsrl(Composed one, Composed other) 
            {
                return _mm_srl_epi16(one, other);
            }
            
            /**
             * @brief bitwise_shift [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vbslli(const Composed one, const size_t other) 
            {
                return _mm_slli_epi16(one, other);
            }
            
            /**
             * @brief bitwise_shift [default branch]
             * @relates int16
             */
            friend zint16<Interface::feature_mask> vbsrli(const Composed one, const size_t other) 
            {
                return _mm_srli_epi16(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct comparable : traits::comparable<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief comparable [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> vgt(Composed one, Composed other) 
            {
                return _mm_cmpgt_epi16(one, other);
            }
            
            /**
             * @brief comparable [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> vlt(Composed one, Composed other) 
            {
                return _mm_cmplt_epi16(one, other);
            }
            
            /**
             * @brief comparable [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> vge(Composed one, Composed other) 
            {
                return !(one < other);
            }
            
            /**
             * @brief comparable [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> vle(Composed one, Composed other) 
            {
                return !(one > other);
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct logical : traits::logical<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief logical [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> vlneg(Composed one) 
            {
                return _mm_cmpeq_epi16(one, _mm_setzero_si128());
            }
            
            /**
             * @brief logical [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> vlor(Composed one, Composed other) 
            {
                return _mm_or_si128(one, other);
            }
            
            /**
             * @brief logical [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> vland(Composed one, Composed other) 
            {
                return _mm_and_si128(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct equatable : traits::equatable<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief equatable [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> veq(Composed one, Composed other) 
            {
                return _mm_cmpeq_epi16(one, other);
            }
            
            /**
             * @brief equatable [default branch]
             * @relates int16
             */
            friend bint16<Interface::feature_mask> vneq(Composed one, Composed other) 
            {
                return !(one == other);
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [sse branch]
         * @relates int16
         */
        template<typename Interface, typename Composed>
        struct conditional : traits::conditional<Interface, Composed, bint16<Interface::feature_mask>>
        {
            /**
             * @brief conditional [sse4 branch]
             * @relates int16
             */
            template<typename T = zint16<Interface::feature_mask>> friend std::enable_if_t<has_feature_v<Interface, capabilities::SSE41>, T> vsel(bint16<Interface::feature_mask> condition, Composed if_value, Composed else_value) 
            {
                return _mm_blendv_epi8(else_value, if_value, condition);
            }
            
            /**
             * @brief conditional [default branch]
             * @relates int16
             */
            template<typename T = zint16<Interface::feature_mask>> friend std::enable_if_t<!has_feature_v<Interface, capabilities::SSE41>, T> vsel(bint16<Interface::feature_mask> condition, Composed if_value, Composed else_value) 
            {
                return _mm_or_si128(_mm_andnot_si128(condition, else_value), _mm_and_si128(condition, if_value));
            }
        };
    } // end int16_modules

    // =================================================================================================================

    /// public zint16 implementation [sse branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct zint16 : public zval<izint16<FeatureMask>>,
        // generic traits
        printable<izint16<FeatureMask>, zint16<FeatureMask>>,
        convertable<izint16<FeatureMask>, zint16<FeatureMask>>,
        // int16 traits
        int16_modules::io<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::math<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::numeric<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::arithmetic<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::bitwise<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::bitwise_shift<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::comparable<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::logical<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::equatable<izint16<FeatureMask>, zint16<FeatureMask>>,
        int16_modules::conditional<izint16<FeatureMask>, zint16<FeatureMask>>
    {
        USING_ZTYPE(izint16<FeatureMask>);

        /// complete vector
        using zval_t = zint16<FeatureMask>;

        /// complete boolean vector
        using bval_t = bint16<FeatureMask>;

        /**
         * Copy constructor, forwards to base implementation
         * @tparam T any type convertable to __m128i
         * @param other
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, __m128i>::value>>
        constexpr zint16(const T& other) noexcept
            : zval<izint16<FeatureMask>>(other)
        {}

        /**
         * Move constructor, forwards to base implementation
         * @tparam T any type convertable to __m128i
         * @param other
         */
        template<typename T, typename = std::enable_if_t<(size > 1) && std::is_convertible<T, __m128i>::value>>
        constexpr zint16(T&& other) noexcept
            : zval<izint16<FeatureMask>>(std::forward<T>(other))
        {}

        /**
         * Converting constructor from bint16, forwards to base implementation 
         * @param other
         */
        constexpr zint16(const bint16<FeatureMask>& other) noexcept
            : zval<izint16<FeatureMask>>(other.value())
        {}

        /**
         * @brief zint16 constructor [sse branch]
         * @relates zint16
         */
        constexpr zint16(  ) noexcept : zval<izint16<FeatureMask>>()
        {
        }
        /**
         * @brief zint16 constructor [sse branch]
         * @relates zint16
         */
        constexpr zint16(__m128i value) noexcept : zval<izint16<FeatureMask>>(value)
        {
        }
        /**
         * @brief zint16 constructor [sse branch]
         * @relates zint16
         */
        constexpr zint16(short value) noexcept : zval<izint16<FeatureMask>>(_mm_set1_epi16(value))
        {
        }
        /**
         * @brief zint16 constructor [sse branch]
         * @relates zint16
         */
        constexpr zint16(const extracted_type &value) noexcept : zval<izint16<FeatureMask>>(_mm_load_si128((__m128i *) value.data()))
        {
        }
        /**
         * @brief zint16 constructor [sse branch]
         * @relates zint16
         */
        constexpr zint16(int16_t _7, int16_t _6, int16_t _5, int16_t _4, int16_t _3, int16_t _2, int16_t _1, int16_t _0) noexcept : zval<izint16<FeatureMask>>(_mm_set_epi16(_0, _1, _2, _3, _4, _5, _6, _7))
        {
        }
    };

    // =================================================================================================================

    /// public bint16 implementation [sse branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct bint16 : public bval<ibint16<FeatureMask>>,
        // generic traits
        printable<bint16<FeatureMask>, bint16<FeatureMask>>,
        convertable<bint16<FeatureMask>, bint16<FeatureMask>>,
        // int16 traits
        int16_modules::io<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::math<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::numeric<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::arithmetic<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::bitwise<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::bitwise_shift<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::comparable<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::logical<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::equatable<ibint16<FeatureMask>, bint16<FeatureMask>>,
        int16_modules::conditional<ibint16<FeatureMask>, bint16<FeatureMask>>
    {
        USING_ZTYPE(ibint16<FeatureMask>);

        /// complete vector
        using zval_t = zint16<FeatureMask>;

        /// complete boolean vector
        using bval_t = bint16<FeatureMask>;

        /// Forwarding constructor
        FORWARD2(bint16, bval<ibint16<FeatureMask>>);

    };

    // Validate zint16 ===================================================================================

    static_assert(std::is_base_of<izint16<0>,
                  izint16<0>>::value,
                  "base_of<izint16> != izint16.");
    static_assert(!std::is_base_of<ibint16<0>,
                  izint16<0>>::value,
                  "base_of<izint16> == ibint16.");

    static_assert(is_zval<izint16<0>>::value,
                  "is_zval<izint16> == false.");
    static_assert(!is_bval<izint16<0>>::value,
                  "is_bval<izint16> != false.");

    static_assert(std::is_base_of<izint16<0>, zint16<0>>::value,
                  "base_of<zint16> != izint16.");
    static_assert(!std::is_base_of<ibint16<0>, zint16<0>>::value,
                  "base_of<zint16> == ibint16.");

    static_assert(zint16<0>::size == 8,
                  "zint16::size != 8.");
    static_assert(zint16<0>::alignment == 16,
                  "zint16::alignment != 16.");
    static_assert(zint16<0>::is_vector == (8 > 1),
    "zint16::is_vector != (8 > 1).");

    static_assert(std::is_same<zint16<0>::tag, zval_tag > ::value,
                  "zint16::tag != zval_tag.");
    static_assert(std::is_same<zint16<0>::vector_type, __m128i > ::value,
                  "zint16::vector_type != __m128i.");
    static_assert(std::is_same<zint16<0>::element_type, int16_t > ::value,
                  "zint16::element_type != int16_t.");
    static_assert(std::is_same<zint16<0>::mask_vector_type, __m128i > ::value,
                  "zint16::mask_vector_type != __m128i.");
    static_assert(std::is_same<zint16<0>::extracted_type,
                  std::array<int16_t, 8>>::value,
                  "zint16::extracted_type != std::array<int16_t, 8>.");


    static_assert(std::is_same<typename ztraits<zint16<0>>::tag, zval_tag > ::value,
                  "zint16::tag != zval_tag.");
    static_assert(std::is_arithmetic<typename ztraits<zint16<0>>::element_type > ::value,
                  "is_arithmetic<zint16::element_type> == false.");
    static_assert(is_zval < zint16<0>>::value,
                  "is_zval<zint16> == false.");
    static_assert(!is_bval < zint16<0>>::value,
                  "is_bval<zint16> != false.");


    // Validate bint16 ===================================================================================


    static_assert(std::is_base_of<ibint16<0>,
                  ibint16<0>>::value,
                  "base_of<izint16> != izint16.");
    static_assert(!std::is_base_of<izint16<0>,
                  ibint16<0>>::value,
                  "base_of<izint16> == ibint16.");

    static_assert(!is_zval<ibint16<0>>::value,
                  "is_zval<ibint16> != false.");
    static_assert(is_bval<ibint16<0>>::value,
                  "is_bval<ibint16> == false.");

    static_assert(std::is_base_of<ibint16<0>, bint16<0>>::value,
                  "base_of<bint16> != ibint16.");
    static_assert(!std::is_base_of<izint16<0>, bint16<0>>::value,
                  "base_of<bint16> == izint16.");

    static_assert(bint16<0>::size == 8,
                  "bint16::size != 8.");
    static_assert(bint16<0>::alignment == 16,
                  "bint16::alignment != 16.");
    static_assert(bint16<0>::is_vector == (8 > 1),
    "bint16::is_vector != (8 > 1).");

    static_assert(std::is_same<bint16<0>::tag, bval_tag > ::value,
                  "bint16::tag != zval_tag.");
    static_assert(std::is_same<bint16<0>::vector_type, __m128i > ::value,
                  "bint16::vector_type != __m128i.");
    static_assert(std::is_same<bint16<0>::element_type, int16_t > ::value,
                  "bint16::element_type != int16_t.");
    static_assert(std::is_same<bint16<0>::mask_vector_type, __m128i > ::value,
                  "bint16::mask_vector_type != __m128i.");
    static_assert(std::is_same<bint16<0>::extracted_type,
                  std::array<int16_t, 8>>::value,
    "bint16::extracted_type != std::array<int16_t, 8>.");

    static_assert(std::is_same<typename ztraits<bint16<0>>::tag, bval_tag > ::value,
                  "bint16::tag != bval_tag.");
    static_assert(std::is_arithmetic<typename ztraits<bint16<0>>::element_type > ::value,
                  "is_arithmetic<bint16::element_type> == false.");
    static_assert(!is_zval < bint16<0>>::value,
                  "is_zval<bint16> != false.");
    static_assert(is_bval < bint16<0>>::value,
                  "is_bval<bint16> == false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<int16_t>::value ||
                  is_floating_point < zint16<0>>::value,
                  "is_floating_point<zint16> == false. [scalar = int16_t]");
    static_assert(!std::is_floating_point<int16_t>::value ||
                  !is_integral < zint16<0>>::value,
                  "is_integral<zint16> != false. [scalar = int16_t]");

    static_assert(
            !std::is_same<int16_t, float>::value || is_float < zint16<0>>::value,
            "is_float<zint16> == false. [scalar = int16_t]");
    static_assert(
            !std::is_same<int16_t, float>::value || !is_double < zint16<0>>::value,
            "is_double<zint16> != false. [scalar = int16_t]");

    static_assert(
            !std::is_same<int16_t, double>::value || is_double < zint16<0>>::value,
            "is_double<zint16> == false. [scalar = int16_t]");
    static_assert(
            !std::is_same<int16_t, double>::value || !is_float < zint16<0>>::value,
            "is_float<zint16> != false. [scalar = int16_t]");

    static_assert(
            !std::is_integral<int16_t>::value || is_integral < zint16<0>>::value,
            "is_integral<zint16> == false. [scalar = int16_t]");
    static_assert(!std::is_integral<int16_t>::value ||
                  !is_floating_point < zint16<0>>::value,
                  "is_floating_point<zint16> != false. [scalar = int16_t]");
}}}