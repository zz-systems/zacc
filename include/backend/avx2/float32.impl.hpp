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
 * This file provides defines required components and logic for float32 avx2 target.
 * Provides unified access to 8 'float' values
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
#include "traits/numeric.hpp"
#include "traits/comparable.hpp"
#include "traits/io.hpp"
#include "traits/bitwise.hpp"
#include "traits/arithmetic.hpp"
#include "traits/math.hpp"
#include "traits/conditional.hpp"
#include "traits/logical.hpp"
#include "traits/equatable.hpp"

namespace zacc { namespace backend { namespace avx2
{
    /// @cond
    template<uint64_t features>
    struct bfloat32;

    template<uint64_t features>
    struct zfloat32;
    /// @endcond

    template<uint64_t FeatureMask>
    using izfloat32 = ztype<zval_tag, __m256, float, 8, 32, FeatureMask>;

    template<uint64_t FeatureMask>
    using ibfloat32 = ztype<bval_tag, __m256, float, 8, 32, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for float32 [avx2 branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::avx2::izfloat32<T::feature_mask>, T>::value
            || std::is_base_of<backend::avx2::ibfloat32<T::feature_mask>, T>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 8;

        /// capabilities
        static constexpr uint64_t feature_mask = T::feature_mask;

        /// memory alignment
        static constexpr size_t alignment = 32;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = __m256;

        /// scalar type, like int for sse 4x integer vector
        using element_type = float;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = backend::avx2::zfloat32<T::feature_mask>;
        using bval_type = backend::avx2::bfloat32<T::feature_mask>;

        using tag = typename T::tag;
    };
}

namespace zacc { namespace backend { namespace avx2
{
    namespace float32_modules
    {
        /**
         * @brief equatable mixin implementation [avx2 branch]
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
                return _mm256_cmp_ps(one, other, _CMP_EQ_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vneq(Composed one, Composed other) 
            {
                return _mm256_cmp_ps(one, other, _CMP_NEQ_OQ);
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [avx2 branch]
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
                return _mm256_cmp_ps(one, other, _CMP_GT_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vlt(Composed one, Composed other) 
            {
                return _mm256_cmp_ps(one, other, _CMP_LT_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vge(Composed one, Composed other) 
            {
                return _mm256_cmp_ps(one, other, _CMP_GE_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vle(Composed one, Composed other) 
            {
                return _mm256_cmp_ps(one, other, _CMP_LE_OQ);
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation [avx2 branch]
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
                _mm256_store_ps(&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                _mm256_stream_ps(&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename RandomIt> friend Composed vgather(RandomIt input, const zint32<Interface::feature_mask> &index,  Composed) 
            {
                return _mm256_i32gather_ps(&(*input), index, 4);
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [avx2 branch]
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
                auto zero = _mm256_setzero_ps();
                auto ones = _mm256_cmp_ps(zero, zero, _CMP_EQ_OQ);
                return _mm256_xor_ps(one, ones);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vband(Composed one, Composed other) 
            {
                return _mm256_and_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                return _mm256_or_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                return _mm256_xor_ps(one, other);
            }

            /**
             * @brief  [avx2 branch]
             * @relates float32
             */
            template<typename T = bool>
            friend std::enable_if_t<has_feature_v<Interface, capabilities::AVX2>, T>
            vis_set(Composed one) 
            {
                auto ival =  _mm256_castps_si256(one);
                return _mm256_testc_si256(ival, _mm256_cmpeq_epi32(ival,ival));
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename T = bool>
            friend std::enable_if_t<!has_feature_v<Interface, capabilities::AVX2>, T>
            vis_set(Composed one) 
            {
                auto hi = _mm_castps_si128(_mm256_extractf128_ps(one, 1));
                auto lo = _mm_castps_si128(_mm256_extractf128_ps(one, 0));
                return _mm_test_all_ones(hi) != 0 && _mm_test_all_ones(lo) != 0;
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [avx2 branch]
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
                return _mm256_cmp_ps(one, _mm256_setzero_ps(), _CMP_EQ_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vlor(Composed one, Composed other) 
            {
                return _mm256_or_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vland(Composed one, Composed other) 
            {
                return _mm256_and_ps(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [avx2 branch]
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
                return _mm256_sub_ps(_mm256_setzero_ps(), one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return _mm256_add_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return _mm256_sub_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmul(Composed one, Composed other) 
            {
                return _mm256_mul_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                return _mm256_div_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vfmadd(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return _mm256_fmadd_ps (multiplicand, multiplier, addendum);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vfmsub(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return _mm256_fmsub_ps(multiplicand, multiplier, addendum);
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [avx2 branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct conditional : traits::conditional<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return _mm256_blendv_ps(else_value, if_value, condition);
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [avx2 branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [avx2 branch]
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
                return _mm256_max_ps(one, _mm256_sub_ps(_mm256_setzero_ps(), one));
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmin(Composed one, Composed other) 
            {
                return _mm256_min_ps(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmax(Composed one, Composed other) 
            {
                return _mm256_max_ps(one, other);
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
                return (1/one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vtrunc(Composed one) 
            {
                return _mm256_cvtepi32_ps(_mm256_cvttps_epi32(one));
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vfloor(Composed one) 
            {
                return _mm256_floor_ps(one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vceil(Composed one) 
            {
                return _mm256_ceil_ps(one);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vround(Composed one) 
            {
                return _mm256_round_ps (one, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vsqrt(Composed one) 
            {
                return _mm256_sqrt_ps(one);
            }
        };
    } // end float32_modules

    // =================================================================================================================

    /// public zfloat32 implementation [avx2 branch]
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
        USING_ZTYPE(izfloat32<FeatureMask>);

        using zval<izfloat32<FeatureMask>>::zval;

        template<typename T, typename std::enable_if<is_zval<T>::value, void**>::type = nullptr>
        constexpr zfloat32(const T& other) noexcept
                : zfloat32(other.value())
        {}

        explicit constexpr zfloat32(const bval_t<izfloat32<FeatureMask>>& other) noexcept
                : zfloat32(other.value())
        {}

        /**
         * @brief zfloat32 constructor [avx2 branch]
         * @relates zfloat32
         */
        constexpr zfloat32(__m256 value) noexcept
            : zval<izfloat32<FeatureMask>>(value)
        {
        }

        /**
         * @brief zfloat32 constructor [avx2 branch]
         * @relates zfloat32
         */
        constexpr zfloat32(__m256d value) noexcept
            : zval<izfloat32<FeatureMask>>(_mm256_castps128_ps256(_mm256_cvtpd_ps(value)))
        {
        }

        /**
         * @brief zfloat32 constructor [avx2 branch]
         * @relates zfloat32
         */
        constexpr zfloat32(__m256i value) noexcept
            : zval<izfloat32<FeatureMask>>(_mm256_cvtepi32_ps(value))
        {
        }

        /**
         * @brief zfloat32 constructor [avx2 branch]
         * @relates zfloat32
         */
        constexpr zfloat32(float value) noexcept
            : zval<izfloat32<FeatureMask>>(_mm256_set1_ps(value))
        {
        }

        /**
         * @brief zfloat32 constructor [avx2 branch]
         * @relates zfloat32
         */
        constexpr zfloat32(extracted_type value) noexcept
            : zval<izfloat32<FeatureMask>>(_mm256_load_ps(value.data()))
        {
        }

        /**
         * @brief zfloat32 constructor [avx2 branch]
         * @relates zfloat32
         */
        constexpr zfloat32(float _7, float _6, float _5, float _4, float _3, float _2, float _1, float _0) noexcept
            : zval<izfloat32<FeatureMask>>(_mm256_set_ps(_0, _1, _2, _3, _4, _5, _6, _7))
        {
        }
    };

    // =================================================================================================================

    /// public bfloat32 implementation [avx2 branch]
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
        USING_ZTYPE(ibfloat32<FeatureMask>);

        using zval<ibfloat32<FeatureMask>>::zval;

        template<typename T, typename std::enable_if<is_zval<T>::value, void**>::type = nullptr>
        constexpr bfloat32(const T& other) noexcept
                : bfloat32(other.value())
        {}

//        constexpr bfloat32(const zval_t<ibfloat32<FeatureMask>>& other) noexcept
//                : bfloat32(other.value())
//        {}

        /**
         * @brief bfloat32 constructor [avx2 branch]
         * @relates bfloat32
         */
        constexpr bfloat32(bool value) noexcept
            : zval<ibfloat32<FeatureMask>>((value ? _mm256_cmp_ps(_mm256_setzero_ps(), _mm256_setzero_ps(), _CMP_EQ_OQ) : _mm256_setzero_ps()), (last_operation::boolean))
        {
        }
    };

    // Validate zfloat32 ===================================================================================

    static_assert( std::is_base_of<izfloat32<0>, izfloat32<0>>::value, "base_of<izfloat32> != izfloat32.");
    static_assert(!std::is_base_of<ibfloat32<0>, izfloat32<0>>::value, "base_of<izfloat32> == ibfloat32.");

    static_assert( is_zval<izfloat32<0>>::value, "is_zval<izfloat32> == false.");
    static_assert(!is_bval<izfloat32<0>>::value, "is_bval<izfloat32> != false.");

    static_assert( std::is_base_of<izfloat32<0>, zfloat32<0>>::value, "base_of<zfloat32> != izfloat32.");
    static_assert(!std::is_base_of<ibfloat32<0>, zfloat32<0>>::value, "base_of<zfloat32> == ibfloat32.");

    static_assert(zfloat32<0>::size == 8, "zfloat32::size != 8.");
    static_assert(zfloat32<0>::alignment == 32, "zfloat32::alignment != 32.");
    static_assert(zfloat32<0>::is_vector == true, "zfloat32::is_vector != true.");

    static_assert(std::is_same<zfloat32<0>::tag, zval_tag>::value, "zfloat32::tag != zval_tag.");
    static_assert(std::is_same<zfloat32<0>::vector_type, __m256>::value, "zfloat32::vector_type != __m256.");
    static_assert(std::is_same<zfloat32<0>::element_type, float>::value, "zfloat32::element_type != float.");
    static_assert(std::is_same<zfloat32<0>::extracted_type, std::array<float, 8>>::value, "zfloat32::extracted_type != std::array<float, 8>.");

    static_assert( is_zval<zfloat32<0>>::value, "is_zval<zfloat32> == false.");
    static_assert(!is_bval<zfloat32<0>>::value, "is_bval<zfloat32> != false.");

    // Validate bfloat32 ===================================================================================

    static_assert( std::is_base_of<ibfloat32<0>, ibfloat32<0>>::value, "base_of<izfloat32> != izfloat32.");
    static_assert(!std::is_base_of<izfloat32<0>, ibfloat32<0>>::value, "base_of<izfloat32> == ibfloat32.");

    static_assert( is_bval<ibfloat32<0>>::value, "is_bval<ibfloat32> == false.");
    static_assert(!is_zval<ibfloat32<0>>::value, "is_zval<ibfloat32> != false.");

    static_assert( std::is_base_of<ibfloat32<0>, bfloat32<0>>::value, "base_of<bfloat32> != ibfloat32.");
    static_assert(!std::is_base_of<izfloat32<0>, bfloat32<0>>::value, "base_of<bfloat32> == izfloat32.");

    static_assert(bfloat32<0>::size == 8, "bfloat32::size != 8.");
    static_assert(bfloat32<0>::alignment == 32, "bfloat32::alignment != 32.");
    static_assert(bfloat32<0>::is_vector == true, "bfloat32::is_vector != true.");

    static_assert(std::is_same<bfloat32<0>::tag, bval_tag>::value, "bfloat32::tag != zval_tag.");
    static_assert(std::is_same<bfloat32<0>::vector_type, __m256>::value, "bfloat32::vector_type != __m256.");
    static_assert(std::is_same<bfloat32<0>::element_type, float>::value, "bfloat32::element_type != float.");
    static_assert(std::is_same<bfloat32<0>::extracted_type, std::array<float, 8>>::value, "bfloat32::extracted_type != std::array<float, 8>.");

    static_assert( is_bval<bfloat32<0>>::value, "is_bval<bfloat32> == false.");
    static_assert(!is_zval<bfloat32<0>>::value, "is_zval<bfloat32> != false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<float>::value || is_floating_point < zfloat32<0>>::value, "is_floating_point<zfloat32> == false. [scalar = float]");
    static_assert(!std::is_floating_point<float>::value || !is_integral<zfloat32<0>>::value, "is_integral<zfloat32> != false. [scalar = float]");

    static_assert(!std::is_same<float, float>::value || is_float < zfloat32<0>>::value, "is_float<zfloat32> == false. [scalar = float]");
    static_assert(!std::is_same<float, float>::value || !is_double < zfloat32<0>>::value, "is_double<zfloat32> != false. [scalar = float]");

    static_assert(!std::is_same<float, double>::value || is_double < zfloat32<0>>::value, "is_double<zfloat32> == false. [scalar = float]");
    static_assert(!std::is_same<float, double>::value || !is_float < zfloat32<0>>::value, "is_float<zfloat32> != false. [scalar = float]");

    static_assert(!std::is_integral<float>::value || is_integral<zfloat32<0>>::value,"is_integral<zfloat32> == false. [scalar = float]");
    static_assert(!std::is_integral<float>::value || !is_floating_point < zfloat32<0>>::value, "is_floating_point<zfloat32> != false. [scalar = float]");
}}}