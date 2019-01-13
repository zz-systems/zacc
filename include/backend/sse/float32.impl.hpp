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
 * @file float32.impl.hpp
 * @brief
 * This file provides defines required components and logic for float32 sse target.
 * Provides unified access to 4 'float' values
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
#include "traits/logical.hpp"
#include "traits/arithmetic.hpp"
#include "traits/bitwise.hpp"
#include "traits/comparable.hpp"
#include "traits/math.hpp"
#include "traits/io.hpp"
#include "traits/numeric.hpp"
#include "traits/conditional.hpp"
#include "traits/equatable.hpp"

namespace zacc { namespace backend { namespace sse
{
    /// @cond
    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct bfloat32;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct zfloat32;
    /// @endcond

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using izfloat32 = ztype<zval_tag, __m128, float, 4, 16, FeatureMask>;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using ibfloat32 = ztype<bval_tag, __m128, float, 4, 16, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for float32 [sse branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::sse::izfloat32<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value
            || std::is_base_of<backend::sse::ibfloat32<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value>>
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
        using vector_type = __m128;

        /// scalar type, like int for sse 4x integer vector
        using element_type = float;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = backend::sse::zfloat32<std::decay_t<T>::feature_mask>;
        using bval_type = backend::sse::bfloat32<std::decay_t<T>::feature_mask>;

        using tag = typename std::decay_t<T>::tag;
    };
}

namespace zacc { namespace backend { namespace sse
{
    namespace float32_modules
    {
        /**
         * @brief logical mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct logical : traits::logical<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vlneg(Composed one) 
            {
                return _mm_cmpeq_ps(one, _mm_setzero_ps());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vlor(Composed one, Composed other) 
            {
                return _mm_or_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vland(Composed one, Composed other) 
            {
                return _mm_and_ps(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct arithmetic : traits::arithmetic<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vneg(Composed one) 
            {
                return _mm_sub_ps(_mm_setzero_ps(), one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return _mm_add_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return _mm_sub_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmul(Composed one, Composed other) 
            {
                return _mm_mul_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                return _mm_div_ps(one, other);
            }

            /**
             * @brief  [fma branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::fma3()), T>
            vfmadd(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return _mm_fmadd_ps(multiplicand, multiplier, addendum);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::fma3()), T>
            vfmadd(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return vadd(vmul(multiplicand, multiplier), addendum);
            }

            /**
             * @brief  [fma branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::fma3()), T>
            vfmsub(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return _mm_fmsub_ps(multiplicand, multiplier, addendum);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::fma3()), T>
            vfmsub(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return vsub(vmul(multiplicand, multiplier), addendum);
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct bitwise : traits::bitwise<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vbneg(Composed one) 
            {
                auto zero = _mm_setzero_ps();
                auto ones = _mm_cmpeq_ps(zero, zero);
                return _mm_xor_ps(one, ones);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vband(Composed one, Composed other) 
            {
                return _mm_and_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                return _mm_or_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                return _mm_xor_ps(one, other);
            }

            /**
             * @brief  [sse4 branch]
             * @relates float32
             */
            template<typename T = bool>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vis_set(Composed one) 
            {
                return _mm_test_all_ones(_mm_castps_si128(one)) != 0;
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename T = bool>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vis_set(Composed one) 
            {
                auto zero = _mm_setzero_ps();
                auto ones = _mm_cmpeq_ps(zero, zero);
                return _mm_movemask_ps(_mm_cmpeq_ps(one, ones)) == 0xFFFF;
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct comparable : traits::comparable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vgt(Composed one, Composed other) 
            {
                return _mm_cmpgt_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vlt(Composed one, Composed other) 
            {
                return _mm_cmplt_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vge(Composed one, Composed other) 
            {
                return _mm_cmpge_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vle(Composed one, Composed other) 
            {
                return _mm_cmple_ps(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct math : traits::math<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vabs(Composed one) 
            {
                return _mm_max_ps(one, -one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmin(Composed one, Composed other) 
            {
                return _mm_min_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmax(Composed one, Composed other) 
            {
                return _mm_max_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vclamp(Composed self, Composed from, Composed to) 
            {
                return vmin(to, vmax(from, self));
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vrcp(Composed one) 
            {
                return (1 / one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vtrunc(Composed one) 
            {
                return _mm_cvtepi32_ps(_mm_cvttps_epi32(one));
            }

            /**
             * @brief  [sse4 branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vfloor(Composed one) 
            {
                return _mm_floor_ps(one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vfloor(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto _1  = _mm_srli_epi32(_mm_cmpeq_epi32(zero, zero), 31);
                auto fi = vtrunc(one);
                return vsel(vgt(fi, one), vsub(fi, _1), fi);
            }

            /**
             * @brief  [sse4 branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vceil(Composed one) 
            {
                return _mm_ceil_ps(one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vceil(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto _1  = _mm_srli_epi32(_mm_cmpeq_epi32(zero, zero), 31);
                auto fi = vtrunc(one);
                return vsel(vlt(fi, one), vadd(fi, _1), fi);
            }

            /**
             * @brief  [sse4 branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vround(Composed one) 
            {
                return _mm_round_ps (one, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vround(Composed one) 
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi32(zero, zero);
                // generate the highest value < 2;
                auto nearest = _mm_castsi128_ps(_mm_srli_epi32(ones, 2));
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
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vsqrt(Composed one) 
            {
                return _mm_sqrt_ps(one);
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct io : traits::io<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename OutputIt> friend void vstore(OutputIt result, Composed input) 
            {
                _mm_store_ps(&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                _mm_stream_ps(&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename RandomIt> friend Composed vgather(RandomIt input, const zint32<Interface::feature_mask> &index,  Composed) 
            {
                auto i = index.data();
                return _mm_set_ps(input[i[3]], input[i[2]], input[i[1]], input[i[0]]);
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct conditional : traits::conditional<Interface, Composed, Boolean>
        {
            /**
             * @brief  [sse4 branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<has_feature_v<Interface>(feature::sse41()), T>
            vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return _mm_blendv_ps(else_value, if_value, condition);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename T = Composed>
            friend std::enable_if_t<!has_feature_v<Interface>(feature::sse41()), T>
            vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return _mm_or_ps(_mm_andnot_ps(condition, else_value), _mm_and_ps(condition, if_value));
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [sse branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct equatable : traits::equatable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean veq(Composed one, Composed other) 
            {
                return _mm_cmpeq_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vneq(Composed one, Composed other) 
            {
                return _mm_cmpneq_ps(one, other);
            }
        };
    } // end float32_modules

    // =================================================================================================================

    /// public zfloat32 implementation [sse branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct zfloat32 : public zval<izfloat32<FeatureMask>>,

        // generic traits
        printable<izfloat32<FeatureMask>, zfloat32<FeatureMask>>,

        // float32 traits
        float32_modules::io<izfloat32<FeatureMask>, zfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::math<izfloat32<FeatureMask>, zfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::numeric<izfloat32<FeatureMask>, zfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::arithmetic<izfloat32<FeatureMask>, zfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::bitwise<izfloat32<FeatureMask>, zfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::comparable<izfloat32<FeatureMask>, zfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::equatable<izfloat32<FeatureMask>, zfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::conditional<izfloat32<FeatureMask>, zfloat32<FeatureMask>, bfloat32<FeatureMask>>
    {
        USING_ZTYPE(zval<izfloat32<FeatureMask>>);
        using zval<izfloat32<FeatureMask>>::zval;


        template<typename T, std::enable_if_t<std::is_same<T, view_t<izfloat32<FeatureMask>>>::value && !is_vector, void**> = nullptr>
        constexpr zfloat32(const T& view) noexcept
                : zfloat32(view[0])
        {}

        template<typename T, typename std::enable_if<is_zval<T>::value, void**>::type = nullptr>
        constexpr zfloat32(const T& other) noexcept
                : zfloat32(other.value())
        {}

        explicit constexpr zfloat32(const bval_t<izfloat32<FeatureMask>>& other) noexcept
                : zfloat32(other.value())
        {}

        /**
         * @brief zfloat32 constructor [sse branch]
         * @relates zfloat32
         */
        constexpr zfloat32(__m128 value) noexcept
            : zval<izfloat32<FeatureMask>>(value)
        {
        }

        /**
         * @brief zfloat32 constructor [sse branch]
         * @relates zfloat32
         */
        constexpr zfloat32(__m128d value) noexcept
            : zval<izfloat32<FeatureMask>>(_mm_cvtpd_ps(value))
        {
        }

        /**
         * @brief zfloat32 constructor [sse branch]
         * @relates zfloat32
         */
        constexpr zfloat32(__m128i value) noexcept
            : zval<izfloat32<FeatureMask>>(_mm_cvtepi32_ps(value))
        {
        }

        /**
         * @brief zfloat32 constructor [sse branch]
         * @relates zfloat32
         */
        constexpr zfloat32(float value) noexcept
            : zval<izfloat32<FeatureMask>>(_mm_set1_ps(value))
        {
        }

        /**
         * @brief zfloat32 constructor [sse branch]
         * @relates zfloat32
         */
        constexpr zfloat32(extracted_type value) noexcept
            : zval<izfloat32<FeatureMask>>(_mm_load_ps(value.data()))
        {
        }

        /**
         * @brief zfloat32 constructor [sse branch]
         * @relates zfloat32
         */
        constexpr zfloat32(float _3, float _2, float _1, float _0) noexcept
            : zval<izfloat32<FeatureMask>>(_mm_set_ps(_0, _1, _2, _3))
        {
        }
    };

    // =================================================================================================================

    /// public bfloat32 implementation [sse branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct bfloat32 : public zval<ibfloat32<FeatureMask>>,

        // generic traits
        printable<bfloat32<FeatureMask>, bfloat32<FeatureMask>>,

        // float32 traits
        float32_modules::io<ibfloat32<FeatureMask>, bfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::bitwise<ibfloat32<FeatureMask>, bfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::logical<ibfloat32<FeatureMask>, bfloat32<FeatureMask>, bfloat32<FeatureMask>>,
        float32_modules::equatable<ibfloat32<FeatureMask>, bfloat32<FeatureMask>, bfloat32<FeatureMask>>
    {
        USING_ZTYPE(zval<ibfloat32<FeatureMask>>);
        using zval<ibfloat32<FeatureMask>>::zval;

        template<typename T, std::enable_if_t<std::is_same<T, view_t<ibfloat32<FeatureMask>>>::value && !is_vector, void**> = nullptr>
        constexpr bfloat32(const T& view) noexcept
                : bfloat32((view[0]))
        {}

        template<typename T, typename std::enable_if<is_zval<T>::value || is_bval<T>::value, void**>::type = nullptr>
        constexpr bfloat32(const T& other) noexcept
                : bfloat32(other.value())
        {
            //static_assert(size_v<T> == 4, "Dimension mismatch");
        }

        /**
         * @brief bfloat32 constructor [sse branch]
         * @relates bfloat32
         */
        constexpr bfloat32(__m128 value) noexcept
            : zval<ibfloat32<FeatureMask>>(value)
        {
        }

        /**
         * @brief bfloat32 constructor [sse branch]
         * @relates bfloat32
         */
        constexpr bfloat32(__m128d value) noexcept
            : zval<ibfloat32<FeatureMask>>(_mm_castpd_ps(value))
        {
        }

        /**
         * @brief bfloat32 constructor [sse branch]
         * @relates bfloat32
         */
        constexpr bfloat32(__m128i value) noexcept
            : zval<ibfloat32<FeatureMask>>(_mm_castsi128_pd(value))
        {
        }

        /**
         * @brief bfloat32 constructor [sse branch]
         * @relates bfloat32
         */
        constexpr bfloat32(bool value) noexcept
            : zval<ibfloat32<FeatureMask>>((value ? _mm_cmpeq_pd(_mm_setzero_ps(), _mm_setzero_ps()) : _mm_setzero_ps()))
        {
        }
    };

    // Validate zfloat32 ===================================================================================

#define params 0

    static_assert( is_vector_v<izfloat32<params>> == true,    "is_vector_v<izfloat32> != true.");
    static_assert( is_vector_v<ibfloat32<params>> == true,    "is_vector_v<ibfloat32> != true.");

    static_assert( std::is_same<element_t<ibfloat32<params>>, float>::value,    "element_t<ibfloat32> != float.");

    static_assert( std::is_same<element_t<izfloat32<params>>, float>::value,    "element_t<izfloat32> != float.");
    static_assert( std::is_same<element_t<ibfloat32<params>>, float>::value,    "element_t<ibfloat32> != float.");

    static_assert( std::is_same<vector_t<izfloat32<params>>, __m128>::value,    "vector_t<izfloat32> != __m128.");
    static_assert( std::is_same<vector_t<ibfloat32<params>>, __m128>::value,    "vector_t<ibfloat32> != __m128.");

    static_assert( std::is_same<view_t<izfloat32<params>>, std::array<float, 4>>::value,    "view_t<izfloat32> != std::array<float, 4>.");
    static_assert( std::is_same<view_t<ibfloat32<params>>, std::array<bool, 4>>::value,                        "view_t<ibfloat32> != std::array<bool, 4>.");

//
    static_assert( std::is_base_of<izfloat32<params>, izfloat32<params>>::value, "base_of<izfloat32> != izfloat32.");
    static_assert(!std::is_base_of<ibfloat32<params>, izfloat32<params>>::value, "base_of<izfloat32> == ibfloat32.");

    static_assert( is_zval<izfloat32<params>>::value, "is_zval<izfloat32> == false.");
    static_assert(!is_bval<izfloat32<params>>::value, "is_bval<izfloat32> != false.");

    static_assert( std::is_base_of<izfloat32<params>, zfloat32<params>>::value, "base_of<zfloat32> != izfloat32.");
    static_assert(!std::is_base_of<ibfloat32<params>, zfloat32<params>>::value, "base_of<zfloat32> == ibfloat32.");

    static_assert(zfloat32<params>::size == 4, "zfloat32::size != 4.");
    static_assert(zfloat32<params>::alignment == 16, "zfloat32::alignment != 16.");
    static_assert(zfloat32<params>::is_vector == true, "zfloat32::is_vector != true.");

    static_assert(std::is_same<zfloat32<params>::tag, zval_tag>::value, "zfloat32::tag != zval_tag.");
    static_assert(std::is_same<zfloat32<params>::vector_type, __m128>::value, "zfloat32::vector_type != __m128.");
    static_assert(std::is_same<zfloat32<params>::element_type, float>::value, "zfloat32::element_type != float.");
    static_assert(std::is_same<zfloat32<params>::extracted_type, std::array<float, 4>>::value, "zfloat32::extracted_type != std::array<float, 4>.");

    static_assert( is_zval<zfloat32<params>>::value, "is_zval<zfloat32> == false.");
    static_assert(!is_bval<zfloat32<params>>::value, "is_bval<zfloat32> != false.");

    // Validate bfloat32 ===================================================================================

    static_assert( std::is_base_of<ibfloat32<params>, ibfloat32<params>>::value, "base_of<izfloat32> != izfloat32.");
    static_assert(!std::is_base_of<izfloat32<params>, ibfloat32<params>>::value, "base_of<izfloat32> == ibfloat32.");

    static_assert( is_bval<ibfloat32<params>>::value, "is_bval<ibfloat32> == false.");
    static_assert(!is_zval<ibfloat32<params>>::value, "is_zval<ibfloat32> != false.");

    static_assert( std::is_base_of<ibfloat32<params>, bfloat32<params>>::value, "base_of<bfloat32> != ibfloat32.");
    static_assert(!std::is_base_of<izfloat32<params>, bfloat32<params>>::value, "base_of<bfloat32> == izfloat32.");

    static_assert(bfloat32<params>::size == 4, "bfloat32::size != 4.");
    static_assert(bfloat32<params>::alignment == 16, "bfloat32::alignment != 16.");
    static_assert(bfloat32<params>::is_vector == true, "bfloat32::is_vector != true.");

    static_assert(std::is_same<bfloat32<params>::tag, bval_tag>::value, "bfloat32::tag != zval_tag.");
    static_assert(std::is_same<bfloat32<params>::vector_type, __m128>::value, "bfloat32::vector_type != __m128.");
    static_assert(std::is_same<bfloat32<params>::element_type, float>::value, "bfloat32::element_type != float.");
    static_assert(std::is_same<bfloat32<params>::extracted_type, std::array<float, 4>>::value, "bfloat32::extracted_type != std::array<float, 4>.");

    static_assert( is_bval<bfloat32<params>>::value, "is_bval<bfloat32> == false.");
    static_assert(!is_zval<bfloat32<params>>::value, "is_zval<bfloat32> != false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<float>::value || is_floating_point < zfloat32<params>>::value, "is_floating_point<zfloat32> == false. [scalar = float]");
    static_assert(!std::is_floating_point<float>::value || !is_integral<zfloat32<params>>::value, "is_integral<zfloat32> != false. [scalar = float]");

    static_assert(!std::is_same<float, float>::value || is_float < zfloat32<params>>::value, "is_float<zfloat32> == false. [scalar = float]");
    static_assert(!std::is_same<float, float>::value || !is_double < zfloat32<params>>::value, "is_double<zfloat32> != false. [scalar = float]");

    static_assert(!std::is_same<float, double>::value || is_double < zfloat32<params>>::value, "is_double<zfloat32> == false. [scalar = float]");
    static_assert(!std::is_same<float, double>::value || !is_float < zfloat32<params>>::value, "is_float<zfloat32> != false. [scalar = float]");

    static_assert(!std::is_integral<float>::value || is_integral<zfloat32<params>>::value,"is_integral<zfloat32> == false. [scalar = float]");
    static_assert(!std::is_integral<float>::value || !is_floating_point < zfloat32<params>>::value, "is_floating_point<zfloat32> != false. [scalar = float]");
}}}