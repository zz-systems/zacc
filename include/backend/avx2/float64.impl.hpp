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
 * @file float64.impl.hpp
 * @brief
 * This file provides defines required components and logic for float64 avx2 target.
 * Provides unified access to 4 'double' values
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
#include "traits/comparable.hpp"
#include "traits/logical.hpp"
#include "traits/conditional.hpp"
#include "traits/numeric.hpp"
#include "traits/math.hpp"
#include "traits/bitwise.hpp"
#include "traits/equatable.hpp"
#include "traits/arithmetic.hpp"
#include "traits/io.hpp"

namespace zacc { namespace backend { namespace avx2
{
    /// @cond
    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct bfloat64;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct zfloat64;
    /// @endcond

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using izfloat64 = ztype<zval_tag, __m256d, double, 4, 32, FeatureMask>;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using ibfloat64 = ztype<bval_tag, __m256d, double, 4, 32, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for float64 [avx2 branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::avx2::izfloat64<T::feature_mask>, T>::value
            || std::is_base_of<backend::avx2::ibfloat64<T::feature_mask>, T>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 4;

        /// capabilities
        static constexpr uint64_t feature_mask = T::feature_mask;

        /// memory alignment
        static constexpr size_t alignment = 32;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// Indicates the last executed operation. Relevant for branch optimization.
        static constexpr last_op last_operation = last_op::undefined;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = __m256d;

        /// scalar type, like int for sse 4x integer vector
        using element_type = double;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = backend::avx2::zfloat64<T::feature_mask>;
        using bval_type = backend::avx2::bfloat64<T::feature_mask>;

        using tag = typename T::tag;
    };
}

namespace zacc { namespace backend { namespace avx2
{
    namespace float64_modules
    {
        /**
         * @brief comparable mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct comparable : traits::comparable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vgt(Composed one, Composed other) 
            {
                return _mm256_cmp_pd(one, other, _CMP_GT_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vlt(Composed one, Composed other) 
            {
                return _mm256_cmp_pd(one, other, _CMP_LT_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vge(Composed one, Composed other) 
            {
                return _mm256_cmp_pd(one, other, _CMP_GE_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vle(Composed one, Composed other) 
            {
                return _mm256_cmp_pd(one, other, _CMP_LE_OQ);
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct logical : traits::logical<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vlneg(Composed one) 
            {
                return _mm256_cmp_pd(one, _mm256_setzero_pd(), _CMP_EQ_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vlor(Composed one, Composed other) 
            {
                return _mm256_or_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vland(Composed one, Composed other) 
            {
                return _mm256_and_pd(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct conditional : traits::conditional<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return _mm256_blendv_pd(else_value, if_value, condition);
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct math : traits::math<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vabs(Composed one) 
            {
                return _mm256_max_pd(one, -one);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vmin(Composed one, Composed other) 
            {
                return _mm256_min_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vmax(Composed one, Composed other) 
            {
                return _mm256_max_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vclamp(Composed self, Composed from, Composed to) 
            {
                return vmin(to, vmax(from, self));
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vrcp(Composed one) 
            {
                return (1 / one);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vtrunc(Composed one) 
            {
                return _mm256_cvtepi32_pd(_mm256_cvttpd_epi32(one));
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vfloor(Composed one) 
            {
                return _mm256_floor_pd(one);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vceil(Composed one) 
            {
                return _mm256_ceil_pd(one);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vround(Composed one) 
            {
                return _mm256_round_pd (one, _MM_FROUND_TO_NEAREST_INT |_MM_FROUND_NO_EXC);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vsqrt(Composed one) 
            {
                return _mm256_sqrt_pd(one);
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct bitwise : traits::bitwise<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vbneg(Composed one) 
            {
                auto zero = _mm256_setzero_pd();
                auto ones = _mm256_cmp_pd(zero, zero, _CMP_EQ_OQ);
                return _mm256_xor_pd(one, ones);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vband(Composed one, Composed other) 
            {
                return _mm256_and_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                return _mm256_or_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                return _mm256_xor_pd(one, other);
            }

            /**
             * @brief  [avx2 branch]
             * @relates float64
             */
            template<typename T = bool>
            friend std::enable_if_t<has_feature_v<Interface, capabilities::AVX2>, T>
            vis_set(Composed one) 
            {
                auto ival =  _mm256_castpd_si256(one);
                return _mm256_testc_si256(ival, _mm256_cmpeq_epi32(ival,ival));
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            template<typename T = bool>
            friend std::enable_if_t<!has_feature_v<Interface, capabilities::AVX2>, T>
            vis_set(Composed one) 
            {
                auto hi = _mm_castpd_si128(_mm256_extractf128_pd(one, 1));
                auto lo = _mm_castpd_si128(_mm256_extractf128_pd(one, 0));
                return _mm_test_all_ones(hi) != 0 && _mm_test_all_ones(lo) != 0;
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct equatable : traits::equatable<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean veq(Composed one, Composed other) 
            {
                return _mm256_cmp_pd(one, other, _CMP_EQ_OQ);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vneq(Composed one, Composed other) 
            {
                return _mm256_cmp_pd(one, other, _CMP_NEQ_OQ);
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct arithmetic : traits::arithmetic<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vneg(Composed one) 
            {
                return _mm256_sub_pd(_mm256_setzero_pd(), one);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return _mm256_add_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return _mm256_sub_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vmul(Composed one, Composed other) 
            {
                return _mm256_mul_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                return _mm256_div_pd(one, other);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vfmadd(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return _mm256_fmadd_pd(multiplicand, multiplier, addendum);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vfmsub(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return _mm256_fmsub_pd(multiplicand, multiplier, addendum);
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation [avx2 branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct io : traits::io<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates float64
             */
            template<typename OutputIt> friend void vstore(OutputIt result, Composed input) 
            {
                _mm256_store_pd(&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                _mm256_stream_pd(&(*result), input);
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            template<typename RandomIt> friend Composed vgather(RandomIt input, const zint32<Interface::feature_mask> &index,  Composed) 
            {
                auto i = _mm256_extractf128_si256(index, 1);
                return _mm256_i32gather_pd(&(*input), i, 8);
            }
        };
    } // end float64_modules

    // =================================================================================================================

    /// public zfloat64 implementation [avx2 branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct zfloat64 : public zval<izfloat64<FeatureMask>>,

        // generic traits
        printable<izfloat64<FeatureMask>, zfloat64<FeatureMask>>,

        // float64 traits
        float64_modules::io<izfloat64<FeatureMask>, zfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::math<izfloat64<FeatureMask>, zfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::numeric<izfloat64<FeatureMask>, zfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::arithmetic<izfloat64<FeatureMask>, zfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::bitwise<izfloat64<FeatureMask>, zfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::comparable<izfloat64<FeatureMask>, zfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::equatable<izfloat64<FeatureMask>, zfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::conditional<izfloat64<FeatureMask>, zfloat64<FeatureMask>, bfloat64<FeatureMask>>
    {
        USING_ZTYPE(zval<izfloat64<FeatureMask>>);
        using zval<izfloat64<FeatureMask>>::zval;


        template<typename T, std::enable_if_t<std::is_same<T, view_t<izfloat64<FeatureMask>>>::value && !is_vector, void**> = nullptr>
        constexpr zfloat64(const T& view) noexcept
                : zfloat64(view[0])
        {}

        template<typename T, typename std::enable_if<is_zval<T>::value, void**>::type = nullptr>
        constexpr zfloat64(const T& other) noexcept
                : zfloat64(other.value())
        {}

        explicit constexpr zfloat64(const bval_t<izfloat64<FeatureMask>>& other) noexcept
            : zfloat64(other.value())
        {}

        /**
         * @brief zfloat64 constructor [avx2 branch]
         * @relates zfloat64
         */
        constexpr zfloat64(__m256 value) noexcept
            : zval<izfloat64<FeatureMask>>(_mm256_cvtps_pd(_mm256_castps256_ps128(value)))
        {
        }

        /**
         * @brief zfloat64 constructor [avx2 branch]
         * @relates zfloat64
         */
        constexpr zfloat64(__m256d value) noexcept
            : zval<izfloat64<FeatureMask>>(value)
        {
        }

        /**
         * @brief zfloat64 constructor [avx2 branch]
         * @relates zfloat64
         */
        constexpr zfloat64(__m256i value) noexcept
            : zval<izfloat64<FeatureMask>>(_mm256_cvtepi32_pd(_mm256_castsi256_si128(value)))
        {
        }

        /**
         * @brief zfloat64 constructor [avx2 branch]
         * @relates zfloat64
         */
        constexpr zfloat64(double value) noexcept
            : zval<izfloat64<FeatureMask>>(_mm256_set1_pd(value))
        {
        }

        /**
         * @brief zfloat64 constructor [avx2 branch]
         * @relates zfloat64
         */
        constexpr zfloat64(extracted_type value) noexcept
            : zval<izfloat64<FeatureMask>>(_mm256_load_pd(value.data()))
        {
        }

        /**
         * @brief zfloat64 constructor [avx2 branch]
         * @relates zfloat64
         */
        constexpr zfloat64(double _3, double _2, double _1, double _0) noexcept
            : zval<izfloat64<FeatureMask>>(_mm256_set_pd(_0, _1, _2, _3))
        {
        }
    };

    // =================================================================================================================

    /// public bfloat64 implementation [avx2 branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct bfloat64 : public zval<ibfloat64<FeatureMask>>,

        // generic traits
        printable<bfloat64<FeatureMask>, bfloat64<FeatureMask>>,

        // float64 traits
        float64_modules::io<ibfloat64<FeatureMask>, bfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::bitwise<ibfloat64<FeatureMask>, bfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::logical<ibfloat64<FeatureMask>, bfloat64<FeatureMask>, bfloat64<FeatureMask>>,
        float64_modules::equatable<ibfloat64<FeatureMask>, bfloat64<FeatureMask>, bfloat64<FeatureMask>>
    {
        USING_ZTYPE(zval<ibfloat64<FeatureMask>>);
        using zval<ibfloat64<FeatureMask>>::zval;

        template<typename T, std::enable_if_t<std::is_same<T, view_t<ibfloat64<FeatureMask>>>::value && !is_vector, void**> = nullptr>
        constexpr bfloat64(const T& view) noexcept
                : bfloat64((view[0]))
        {}

        template<typename T, typename std::enable_if<is_zval<T>::value || is_bval<T>::value, void**>::type = nullptr>
        constexpr bfloat64(const T& other) noexcept
                : bfloat64(other.value())
        {}

        /**
         * @brief bfloat64 constructor [avx2 branch]
         * @relates bfloat64
         */
        constexpr bfloat64(bool value) noexcept
            : zval<ibfloat64<FeatureMask>>((value ? _mm256_cmp_pd(_mm256_setzero_pd(), _mm256_setzero_pd(), _CMP_EQ_OQ) : _mm256_setzero_pd()))
        {
        }
    };

    // Validate zfloat64 ===================================================================================

#define params 0

    static_assert( is_vector_v<izfloat64<params>> == true,    "is_vector_v<izfloat64> != true.");
    static_assert( is_vector_v<ibfloat64<params>> == true,    "is_vector_v<ibfloat64> != true.");

    static_assert( std::is_same<element_t<ibfloat64<params>>, double>::value,    "element_t<ibfloat64> != double.");

    static_assert( std::is_same<element_t<izfloat64<params>>, double>::value,    "element_t<izfloat64> != double.");
    static_assert( std::is_same<element_t<ibfloat64<params>>, double>::value,    "element_t<ibfloat64> != double.");

    static_assert( std::is_same<vector_t<izfloat64<params>>, __m256d>::value,    "vector_t<izfloat64> != __m256d.");
    static_assert( std::is_same<vector_t<ibfloat64<params>>, __m256d>::value,    "vector_t<ibfloat64> != __m256d.");

    static_assert( std::is_same<view_t<izfloat64<params>>, std::array<double, 4>>::value,    "view_t<izfloat64> != std::array<double, 4>.");
    static_assert( std::is_same<view_t<ibfloat64<params>>, std::array<bool, 4>>::value,                        "view_t<ibfloat64> != std::array<bool, 4>.");

//
    static_assert( std::is_base_of<izfloat64<params>, izfloat64<params>>::value, "base_of<izfloat64> != izfloat64.");
    static_assert(!std::is_base_of<ibfloat64<params>, izfloat64<params>>::value, "base_of<izfloat64> == ibfloat64.");

    static_assert( is_zval<izfloat64<params>>::value, "is_zval<izfloat64> == false.");
    static_assert(!is_bval<izfloat64<params>>::value, "is_bval<izfloat64> != false.");

    static_assert( std::is_base_of<izfloat64<params>, zfloat64<params>>::value, "base_of<zfloat64> != izfloat64.");
    static_assert(!std::is_base_of<ibfloat64<params>, zfloat64<params>>::value, "base_of<zfloat64> == ibfloat64.");

    static_assert(zfloat64<params>::size == 4, "zfloat64::size != 4.");
    static_assert(zfloat64<params>::alignment == 32, "zfloat64::alignment != 32.");
    static_assert(zfloat64<params>::is_vector == true, "zfloat64::is_vector != true.");

    static_assert(std::is_same<zfloat64<params>::tag, zval_tag>::value, "zfloat64::tag != zval_tag.");
    static_assert(std::is_same<zfloat64<params>::vector_type, __m256d>::value, "zfloat64::vector_type != __m256d.");
    static_assert(std::is_same<zfloat64<params>::element_type, double>::value, "zfloat64::element_type != double.");
    static_assert(std::is_same<zfloat64<params>::extracted_type, std::array<double, 4>>::value, "zfloat64::extracted_type != std::array<double, 4>.");

    static_assert( is_zval<zfloat64<params>>::value, "is_zval<zfloat64> == false.");
    static_assert(!is_bval<zfloat64<params>>::value, "is_bval<zfloat64> != false.");

    // Validate bfloat64 ===================================================================================

    static_assert( std::is_base_of<ibfloat64<params>, ibfloat64<params>>::value, "base_of<izfloat64> != izfloat64.");
    static_assert(!std::is_base_of<izfloat64<params>, ibfloat64<params>>::value, "base_of<izfloat64> == ibfloat64.");

    static_assert( is_bval<ibfloat64<params>>::value, "is_bval<ibfloat64> == false.");
    static_assert(!is_zval<ibfloat64<params>>::value, "is_zval<ibfloat64> != false.");

    static_assert( std::is_base_of<ibfloat64<params>, bfloat64<params>>::value, "base_of<bfloat64> != ibfloat64.");
    static_assert(!std::is_base_of<izfloat64<params>, bfloat64<params>>::value, "base_of<bfloat64> == izfloat64.");

    static_assert(bfloat64<params>::size == 4, "bfloat64::size != 4.");
    static_assert(bfloat64<params>::alignment == 32, "bfloat64::alignment != 32.");
    static_assert(bfloat64<params>::is_vector == true, "bfloat64::is_vector != true.");

    static_assert(std::is_same<bfloat64<params>::tag, bval_tag>::value, "bfloat64::tag != zval_tag.");
    static_assert(std::is_same<bfloat64<params>::vector_type, __m256d>::value, "bfloat64::vector_type != __m256d.");
    static_assert(std::is_same<bfloat64<params>::element_type, double>::value, "bfloat64::element_type != double.");
    static_assert(std::is_same<bfloat64<params>::extracted_type, std::array<double, 4>>::value, "bfloat64::extracted_type != std::array<double, 4>.");

    static_assert( is_bval<bfloat64<params>>::value, "is_bval<bfloat64> == false.");
    static_assert(!is_zval<bfloat64<params>>::value, "is_zval<bfloat64> != false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<double>::value || is_floating_point < zfloat64<params>>::value, "is_floating_point<zfloat64> == false. [scalar = double]");
    static_assert(!std::is_floating_point<double>::value || !is_integral<zfloat64<params>>::value, "is_integral<zfloat64> != false. [scalar = double]");

    static_assert(!std::is_same<double, float>::value || is_float < zfloat64<params>>::value, "is_float<zfloat64> == false. [scalar = double]");
    static_assert(!std::is_same<double, float>::value || !is_double < zfloat64<params>>::value, "is_double<zfloat64> != false. [scalar = double]");

    static_assert(!std::is_same<double, double>::value || is_double < zfloat64<params>>::value, "is_double<zfloat64> == false. [scalar = double]");
    static_assert(!std::is_same<double, double>::value || !is_float < zfloat64<params>>::value, "is_float<zfloat64> != false. [scalar = double]");

    static_assert(!std::is_integral<double>::value || is_integral<zfloat64<params>>::value,"is_integral<zfloat64> == false. [scalar = double]");
    static_assert(!std::is_integral<double>::value || !is_floating_point < zfloat64<params>>::value, "is_floating_point<zfloat64> != false. [scalar = double]");
}}}