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
 * @file int32.impl.hpp
 * @brief
 * This file provides defines required components and logic for int32 sse target.
 * Provides unified access to 4 'int32_t' values
 * @remark
 * This is an autogenerated file. Changes will be lost on regeneration.
 */
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

namespace zacc { namespace backend { namespace sse
{
    /// @cond
    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct bint32;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct zint32;
    /// @endcond

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using izint32 = ztype<zval_tag, __m128i, int32_t, 4, 16, FeatureMask>;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using ibint32 = ztype<bval_tag, __m128i, int32_t, 4, 16, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for int32 [sse branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::sse::izint32<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value
            || std::is_base_of<backend::sse::ibint32<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 4;

        /// capabilities
        static constexpr uint64_t feature_mask = std::decay_t<T>::feature_mask;

        /// memory alignment
        static constexpr size_t alignment = 16;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = __m128i;

        /// scalar type, like int for sse 4x integer vector
        using element_type = int32_t;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = backend::sse::zint32<std::decay_t<T>::feature_mask>;
        using bval_type = backend::sse::bint32<std::decay_t<T>::feature_mask>;

        using tag = typename std::decay_t<T>::tag;
    };
}

namespace zacc { namespace backend { namespace sse
{
    namespace int32_modules
    {
        /**
         * @brief bitwise mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct bitwise : traits::bitwise<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbneg(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi32(zero, zero);
                return _mm_xor_si128(one, ones);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                return _mm_or_si128(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vband(Composed one, Composed other) 
            {
                return _mm_and_si128(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                return _mm_xor_si128(one, other);
            }

            /**
             * @brief  [sse4 branch]
             * @relates int32
             */
            template<typename T = bool>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vis_set(Composed one) 
            {
                return _mm_test_all_ones(one) != 0;
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename T = bool>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vis_set(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi32(zero, zero);
                return _mm_movemask_epi8(_mm_cmpeq_epi32(one, ones)) == 0xFFFF;
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct arithmetic : traits::arithmetic<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vneg(Composed one) 
            {
                return _mm_sub_epi32(_mm_setzero_si128(), one);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return _mm_add_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return _mm_sub_epi32(one, other);
            }

            /**
             * @brief  [sse4 branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vmul(Composed one, Composed other) 
            {
                return _mm_mullo_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vmul(Composed one, Composed other) 
            {
                __m128i tmp1 = _mm_mul_epu32(one,other); /* mul 2,0*/;
                __m128i tmp2 = _mm_mul_epu32( _mm_srli_si128(one,4), _mm_srli_si128(other,4)); /* mul 3,1 */;
                return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE (0,0,2,0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE (0,0,2,0)));
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                return _mm_div_ps(_mm_cvtepi32_ps(one), _mm_cvtepi32_ps(other));
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vmod(Composed one, Composed other) 
            {
                return vsub(one, vmul(other, vdiv(one, other)));
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct comparable : traits::comparable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vgt(Composed one, Composed other) 
            {
                return _mm_cmpgt_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vlt(Composed one, Composed other) 
            {
                return _mm_cmplt_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vge(Composed one, Composed other) 
            {
                return !(one < other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vle(Composed one, Composed other) 
            {
                return !(one > other);
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };

        // =============================================================================================================

        /**
         * @brief bitwise_shift mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct bitwise_shift : traits::bitwise_shift<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbsll(Composed one, Composed other) 
            {
                return _mm_sll_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbsrl(Composed one, Composed other) 
            {
                return _mm_srl_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbslli(const Composed one, const size_t other) 
            {
                return _mm_slli_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbsrli(const Composed one, const size_t other) 
            {
                return _mm_srli_epi32(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct equatable : traits::equatable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean veq(Composed one, Composed other) 
            {
                return _mm_cmpeq_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vneq(Composed one, Composed other) 
            {
                return !(one == other);
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct conditional : traits::conditional<Interface, Composed, Boolean>
        {
            /**
             * @brief  [sse4 branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return _mm_blendv_epi8(else_value, if_value, condition);
            }

            /**
             * @brief  [default branch]
             * @relates int32
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
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct logical : traits::logical<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vlneg(Composed one) 
            {
                return _mm_cmpeq_epi32(one, _mm_setzero_si128());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vlor(Composed one, Composed other) 
            {
                return _mm_or_si128(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vland(Composed one, Composed other) 
            {
                return _mm_and_si128(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct io : traits::io<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename OutputIt> friend void vstore(OutputIt result, Composed input) 
            {
                _mm_store_si128((__m128i*)&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                _mm_stream_si128((__m128i*)&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename RandomIt> friend Composed vgather(RandomIt input, const zint32<Interface::feature_mask> &index, Composed) 
            {
                auto i = index.data();
                return _mm_set_epi32(input[i[3]], input[i[2]], input[i[1]], input[i[0]]);
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [sse branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct math : traits::math<Interface, Composed, Boolean>
        {
            /**
             * @brief  [sse3 branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse3()), T>
            vabs(Composed one) 
            {
                return _mm_abs_epi32(one);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse3()), T>
            vabs(Composed one) 
            {
                return vmax(one, -one);
            }

            /**
             * @brief  [sse4 branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vmin(Composed one, Composed other) 
            {
                return _mm_min_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vmin(Composed one, Composed other) 
            {
                return vsel(one < other, one, other);
            }

            /**
             * @brief  [sse4 branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vmax(Composed one, Composed other) 
            {
                return _mm_max_epi32(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vmax(Composed one, Composed other) 
            {
                return vsel(one > other, one, other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vclamp(Composed self, Composed from, Composed to) 
            {
                return vmin(to, vmax(from, self));
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vsqrt(Composed one) 
            {
                return _mm_sqrt_ps(_mm_cvtepi32_ps(one));
            }
        };
    } // end int32_modules

    // =================================================================================================================

    /// public zint32 implementation [sse branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct zint32 : public zval<izint32<FeatureMask>>,

        // generic traits
        printable<izint32<FeatureMask>, zint32<FeatureMask>>,

        // int32 traits
        int32_modules::io<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::math<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::numeric<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::arithmetic<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::bitwise<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::bitwise_shift<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::comparable<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::equatable<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::conditional<izint32<FeatureMask>, zint32<FeatureMask>, bint32<FeatureMask>>
    {
        USING_ZTYPE(zval<izint32<FeatureMask>>);
        using zval<izint32<FeatureMask>>::zval;

        constexpr zint32() = default;

        // =============================================================================================================

        template<typename T, std::enable_if_t<std::is_same<T, view_t<izint32<FeatureMask>>>::value && !is_vector, void**> = nullptr>
        constexpr zint32(const T& view) noexcept
                : zint32(view[0])
        {}

        template<typename T, typename std::enable_if<is_zval<T>::value, void**>::type = nullptr>
        constexpr zint32(const T& other) noexcept
                : zint32(other.value())
        {}

        explicit constexpr zint32(const bval_t<izint32<FeatureMask>>& other) noexcept
                : zint32(other.value())
        {}

        /**
         * @brief zint32 constructor [sse branch]
         * @relates zint32
         */
        constexpr zint32(__m128 value) noexcept
            : zval<izint32<FeatureMask>>(_mm_cvttps_epi32(value))
        {
        }

        /**
         * @brief zint32 constructor [sse branch]
         * @relates zint32
         */
        constexpr zint32(__m128d value) noexcept
            : zval<izint32<FeatureMask>>(_mm_cvttpd_epi32(value))
        {
        }

        /**
         * @brief zint32 constructor [sse branch]
         * @relates zint32
         */
        constexpr zint32(int32_t value) noexcept
            : zval<izint32<FeatureMask>>(_mm_set1_epi32(value))
        {
        }

        /**
         * @brief zint32 constructor [sse branch]
         * @relates zint32
         */
        constexpr zint32(extracted_type value) noexcept
            : zval<izint32<FeatureMask>>(_mm_load_si128((__m128i*)value.data()))
        {
        }

        /**
         * @brief zint32 constructor [sse branch]
         * @relates zint32
         */
        constexpr zint32(int32_t _3, int32_t _2, int32_t _1, int32_t _0) noexcept
            : zval<izint32<FeatureMask>>(_mm_set_epi32(_0, _1, _2, _3))
        {
        }
    };

    // =================================================================================================================

    /// public bint32 implementation [sse branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct bint32 : public zval<ibint32<FeatureMask>>,

        // generic traits
        printable<bint32<FeatureMask>, bint32<FeatureMask>>,

        // int32 traits
        int32_modules::io<ibint32<FeatureMask>, bint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::bitwise<ibint32<FeatureMask>, bint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::logical<ibint32<FeatureMask>, bint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::equatable<ibint32<FeatureMask>, bint32<FeatureMask>, bint32<FeatureMask>>
    {
        USING_ZTYPE(zval<ibint32<FeatureMask>>);
        using zval<ibint32<FeatureMask>>::zval;

        constexpr bint32() = default;

        // =============================================================================================================

        template<typename T, std::enable_if_t<std::is_same<T, view_t<ibint32<FeatureMask>>>::value && !is_vector, void**> = nullptr>
        constexpr bint32(const T& view) noexcept
                : bint32((view[0]))
        {}

        template<typename T, typename std::enable_if<is_zval<T>::value || is_bval<T>::value, void**>::type = nullptr>
        constexpr bint32(const T& other) noexcept
                : bint32(other.value())
        {
            //static_assert(size_v<T> == 4, "Dimension mismatch");
        }

        /**
         * @brief bint32 constructor [sse branch]
         * @relates bint32
         */
        constexpr bint32(__m128 value) noexcept
            : zval<ibint32<FeatureMask>>(_mm_castps_si128(value))
        {
        }

        /**
         * @brief bint32 constructor [sse branch]
         * @relates bint32
         */
        constexpr bint32(__m128d value) noexcept
            : zval<ibint32<FeatureMask>>(_mm_castpd_si128(value))
        {
        }

        /**
         * @brief bint32 constructor [sse branch]
         * @relates bint32
         */
        constexpr bint32(bool value) noexcept
            : zval<ibint32<FeatureMask>>((value ? _mm_cmpeq_epi32(_mm_setzero_si128(), _mm_setzero_si128()) : _mm_setzero_si128()))
        {
        }
    };

    // Validate zint32 ===================================================================================

#define params 0

    static_assert( is_vector_v<izint32<params>> == true,    "is_vector_v<izint32> != true.");
    static_assert( is_vector_v<ibint32<params>> == true,    "is_vector_v<ibint32> != true.");

    static_assert( std::is_same<element_t<ibint32<params>>, int32_t>::value,    "element_t<ibint32> != int32_t.");

    static_assert( std::is_same<element_t<izint32<params>>, int32_t>::value,    "element_t<izint32> != int32_t.");
    static_assert( std::is_same<element_t<ibint32<params>>, int32_t>::value,    "element_t<ibint32> != int32_t.");

    static_assert( std::is_same<vector_t<izint32<params>>, __m128i>::value,    "vector_t<izint32> != __m128i.");
    static_assert( std::is_same<vector_t<ibint32<params>>, __m128i>::value,    "vector_t<ibint32> != __m128i.");

    static_assert( std::is_same<view_t<izint32<params>>, std::array<int32_t, 4>>::value,    "view_t<izint32> != std::array<int32_t, 4>.");
    static_assert( std::is_same<view_t<ibint32<params>>, std::array<bool, 4>>::value,                        "view_t<ibint32> != std::array<bool, 4>.");

//
    static_assert( std::is_base_of<izint32<params>, izint32<params>>::value, "base_of<izint32> != izint32.");
    static_assert(!std::is_base_of<ibint32<params>, izint32<params>>::value, "base_of<izint32> == ibint32.");

    static_assert( is_zval<izint32<params>>::value, "is_zval<izint32> == false.");
    static_assert(!is_bval<izint32<params>>::value, "is_bval<izint32> != false.");

    static_assert( std::is_base_of<izint32<params>, zint32<params>>::value, "base_of<zint32> != izint32.");
    static_assert(!std::is_base_of<ibint32<params>, zint32<params>>::value, "base_of<zint32> == ibint32.");

    static_assert(zint32<params>::size == 4, "zint32::size != 4.");
    static_assert(zint32<params>::alignment == 16, "zint32::alignment != 16.");
    static_assert(zint32<params>::is_vector == true, "zint32::is_vector != true.");

    static_assert(std::is_same<zint32<params>::tag, zval_tag>::value, "zint32::tag != zval_tag.");
    static_assert(std::is_same<zint32<params>::vector_type, __m128i>::value, "zint32::vector_type != __m128i.");
    static_assert(std::is_same<zint32<params>::element_type, int32_t>::value, "zint32::element_type != int32_t.");
    static_assert(std::is_same<zint32<params>::extracted_type, std::array<int32_t, 4>>::value, "zint32::extracted_type != std::array<int32_t, 4>.");

    static_assert( is_zval<zint32<params>>::value, "is_zval<zint32> == false.");
    static_assert(!is_bval<zint32<params>>::value, "is_bval<zint32> != false.");

    // Validate bint32 ===================================================================================

    static_assert( std::is_base_of<ibint32<params>, ibint32<params>>::value, "base_of<izint32> != izint32.");
    static_assert(!std::is_base_of<izint32<params>, ibint32<params>>::value, "base_of<izint32> == ibint32.");

    static_assert( is_bval<ibint32<params>>::value, "is_bval<ibint32> == false.");
    static_assert(!is_zval<ibint32<params>>::value, "is_zval<ibint32> != false.");

    static_assert( std::is_base_of<ibint32<params>, bint32<params>>::value, "base_of<bint32> != ibint32.");
    static_assert(!std::is_base_of<izint32<params>, bint32<params>>::value, "base_of<bint32> == izint32.");

    static_assert(bint32<params>::size == 4, "bint32::size != 4.");
    static_assert(bint32<params>::alignment == 16, "bint32::alignment != 16.");
    static_assert(bint32<params>::is_vector == true, "bint32::is_vector != true.");

    static_assert(std::is_same<bint32<params>::tag, bval_tag>::value, "bint32::tag != zval_tag.");
    static_assert(std::is_same<bint32<params>::vector_type, __m128i>::value, "bint32::vector_type != __m128i.");
    static_assert(std::is_same<bint32<params>::element_type, int32_t>::value, "bint32::element_type != int32_t.");
    static_assert(std::is_same<bint32<params>::extracted_type, std::array<int32_t, 4>>::value, "bint32::extracted_type != std::array<int32_t, 4>.");

    static_assert( is_bval<bint32<params>>::value, "is_bval<bint32> == false.");
    static_assert(!is_zval<bint32<params>>::value, "is_zval<bint32> != false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<int32_t>::value || is_floating_point < zint32<params>>::value, "is_floating_point<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_floating_point<int32_t>::value || !is_integral<zint32<params>>::value, "is_integral<zint32> != false. [scalar = int32_t]");

    static_assert(!std::is_same<int32_t, float>::value || is_float < zint32<params>>::value, "is_float<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_same<int32_t, float>::value || !is_double < zint32<params>>::value, "is_double<zint32> != false. [scalar = int32_t]");

    static_assert(!std::is_same<int32_t, double>::value || is_double < zint32<params>>::value, "is_double<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_same<int32_t, double>::value || !is_float < zint32<params>>::value, "is_float<zint32> != false. [scalar = int32_t]");

    static_assert(!std::is_integral<int32_t>::value || is_integral<zint32<params>>::value,"is_integral<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_integral<int32_t>::value || !is_floating_point < zint32<params>>::value, "is_floating_point<zint32> != false. [scalar = int32_t]");
}}}