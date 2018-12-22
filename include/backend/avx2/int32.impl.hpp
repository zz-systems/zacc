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
 * This file provides defines required components and logic for int32 avx2 target.
 * Provides unified access to 8 'int32_t' values
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
#include "traits/numeric.hpp"
#include "traits/bitwise_shift.hpp"
#include "traits/bitwise.hpp"
#include "traits/conditional.hpp"
#include "traits/comparable.hpp"
#include "traits/io.hpp"
#include "traits/equatable.hpp"
#include "traits/arithmetic.hpp"
#include "traits/math.hpp"
#include "traits/logical.hpp"

namespace zacc { namespace backend { namespace avx2
{
    /// @cond
    template<uint64_t features>
    struct bint32;

    template<uint64_t features>
    struct zint32;
    /// @endcond
    
    template<uint64_t FeatureMask>
    using izint32 = ztype<zval_tag, __m256i, __m256i, int32_t, 8, 32, FeatureMask>;

    template<uint64_t FeatureMask>
    using ibint32 = ztype<bval_tag, __m256i, __m256i, int32_t, 8, 32, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for int32 [avx2 branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::avx2::izint32<T::feature_mask>, T>::value
            || std::is_base_of<backend::avx2::ibint32<T::feature_mask>, T>::value>>
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
        using vector_type = __m256i;

        /// scalar type, like int for sse 4x integer vector
        using element_type = int32_t;

        /// mask type for boolean operations
        using mask_vector_type = __m256i;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_t = backend::avx2::zint32<T::feature_mask>;
        using bval_t = backend::avx2::bint32<T::feature_mask>;

        using tag = select_t<
            when<std::is_base_of<backend::avx2::izint32<T::feature_mask>, T>::value, zval_tag>,
            when<std::is_base_of<backend::avx2::ibint32<T::feature_mask>, T>::value, bval_tag>>;
    };
}

namespace zacc { namespace backend { namespace avx2
{
    namespace int32_modules
    {
        /**
         * @brief io mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct io : traits::io<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief io [default branch]
             * @relates int32
             */
            template<typename OutputIt> friend void vstore(OutputIt result, Composed input) 
            {
                _mm256_store_si256((__m256i*)&(*result), input);
            }
            
            /**
             * @brief io [default branch]
             * @relates int32
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                _mm256_stream_si256((__m256i*)&(*result), input);
            }
            
            /**
             * @brief io [default branch]
             * @relates int32
             */
            template<typename RandomIt> friend zint32<Interface::feature_mask> vgather(RandomIt input, const zint32<Interface::feature_mask> &index,  Composed) 
            {
                return _mm256_i32gather_epi32(&(*input), index, 4);
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct math : traits::math<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief math [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vabs(Composed one) 
            {
                return _mm256_abs_epi32(one);
            }
            
            /**
             * @brief math [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vmin(Composed one, Composed other) 
            {
                return _mm256_min_epi32(one, other);
            }
            
            /**
             * @brief math [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vmax(Composed one, Composed other) 
            {
                return _mm256_max_epi32(one, other);
            }
            
            /**
             * @brief math [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vclamp(Composed self, Composed from, Composed to) 
            {
                return vmin(to, vmax(from, self));
            }
            
            /**
             * @brief math [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vsqrt(Composed one) 
            {
                return _mm256_sqrt_ps(_mm256_cvtepi32_ps(one));
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct numeric : traits::numeric<Interface, Composed, bint32<Interface::feature_mask>>
        {
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct arithmetic : traits::arithmetic<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief arithmetic [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vneg(Composed one) 
            {
                return _mm256_sub_epi32(_mm256_setzero_si256(), one);
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vadd(Composed one, Composed other) 
            {
                return _mm256_add_epi32(one, other);
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vsub(Composed one, Composed other) 
            {
                return _mm256_sub_epi32(one, other);
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vmul(Composed one, Composed other) 
            {
                return _mm256_mullo_epi32(one, other);
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vdiv(Composed one, Composed other) 
            {
                return _mm256_div_ps(_mm256_cvtepi32_ps(one), _mm256_cvtepi32_ps(other));
            }
            
            /**
             * @brief arithmetic [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vmod(Composed one, Composed other) 
            {
                return vsub(one, vmul(other, vdiv(one, other)));
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct bitwise : traits::bitwise<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief bitwise [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vbneg(Composed one) 
            {
                auto zero = _mm256_setzero_si256();
                auto ones = _mm256_cmpeq_epi32(zero, zero);
                return _mm256_xor_si256(one, ones);
            }
            
            /**
             * @brief bitwise [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vband(Composed one, Composed other) 
            {
                return _mm256_and_si256(one, other);
            }
            
            /**
             * @brief bitwise [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vbor(Composed one, Composed other) 
            {
                return _mm256_or_si256(one, other);
            }
            
            /**
             * @brief bitwise [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vbxor(Composed one, Composed other) 
            {
                return _mm256_xor_si256(one, other);
            }
            
            /**
             * @brief bitwise [default branch]
             * @relates int32
             */
            friend bool is_set(Composed one) 
            {
                return _mm256_testc_si256(one, _mm256_cmpeq_epi32(one,one));
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise_shift mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct bitwise_shift : traits::bitwise_shift<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief bitwise_shift [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vbsll(Composed one, Composed other) 
            {
                return _mm256_sll_epi32(one, other);
            }
            
            /**
             * @brief bitwise_shift [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vbsrl(Composed one, Composed other) 
            {
                return _mm256_srl_epi32(one, other);
            }
            
            /**
             * @brief bitwise_shift [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vbslli(const Composed one, const size_t other) 
            {
                return _mm256_slli_epi32(one, other);
            }
            
            /**
             * @brief bitwise_shift [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vbsrli(const Composed one, const size_t other) 
            {
                return _mm256_srli_epi32(one, other);
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct comparable : traits::comparable<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief comparable [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> vgt(Composed one, Composed other) 
            {
                return { _mm256_cmpgt_epi32(one, other), last_operation::comparison };
            }
            
            /**
             * @brief comparable [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> vlt(Composed one, Composed other) 
            {
                return { _mm256_cmpgt_epi32(other, one), last_operation::comparison };
            }
            
            /**
             * @brief comparable [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> vge(Composed one, Composed other) 
            {
                return !(one < other);
            }
            
            /**
             * @brief comparable [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> vle(Composed one, Composed other) 
            {
                return !(one > other);
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct logical : traits::logical<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief logical [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> vlneg(Composed one) 
            {
                return { _mm256_cmpeq_epi32(one, _mm256_setzero_si256()), last_operation::logic };
            }
            
            /**
             * @brief logical [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> vlor(Composed one, Composed other) 
            {
                return { _mm256_or_si256(one, other), last_operation::logic };
            }
            
            /**
             * @brief logical [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> vland(Composed one, Composed other) 
            {
                return { _mm256_and_si256(one, other), last_operation::logic };
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct equatable : traits::equatable<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief equatable [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> veq(Composed one, Composed other) 
            {
                return { _mm256_cmpeq_epi32(one, other), last_operation::comparison };
            }
            
            /**
             * @brief equatable [default branch]
             * @relates int32
             */
            friend bint32<Interface::feature_mask> vneq(Composed one, Composed other) 
            {
                return !(one == other);
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [avx2 branch]
         * @relates int32
         */
        template<typename Interface, typename Composed>
        struct conditional : traits::conditional<Interface, Composed, bint32<Interface::feature_mask>>
        {
            /**
             * @brief conditional [default branch]
             * @relates int32
             */
            friend zint32<Interface::feature_mask> vsel(bint32<Interface::feature_mask> condition, Composed if_value, Composed else_value) 
            {
                return _mm256_blendv_epi8(else_value, if_value, condition);
            }
        };
    } // end int32_modules

    // =================================================================================================================

    /// public zint32 implementation [avx2 branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct zint32 : public zval<izint32<FeatureMask>>,
        // generic traits
        printable<izint32<FeatureMask>, zint32<FeatureMask>>,
        convertable<izint32<FeatureMask>, zint32<FeatureMask>>,
        // int32 traits
        int32_modules::io<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::math<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::numeric<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::arithmetic<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::bitwise<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::bitwise_shift<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::comparable<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::logical<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::equatable<izint32<FeatureMask>, zint32<FeatureMask>>,
        int32_modules::conditional<izint32<FeatureMask>, zint32<FeatureMask>>
    {
        USING_ZTYPE(izint32<FeatureMask>);

        /// complete vector
        using zval_t = zint32<FeatureMask>;

        /// complete boolean vector
        using bval_t = bint32<FeatureMask>;

        /**
         * Copy constructor, forwards to base implementation
         * @tparam T any type convertable to __m256i
         * @param other
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, __m256i>::value>>
        constexpr zint32(const T& other) noexcept
            : zval<izint32<FeatureMask>>(other)
        {}

        /**
         * Move constructor, forwards to base implementation
         * @tparam T any type convertable to __m256i
         * @param other
         */
        template<typename T, typename = std::enable_if_t<(size > 1) && std::is_convertible<T, __m256i>::value>>
        constexpr zint32(T&& other) noexcept
            : zval<izint32<FeatureMask>>(std::forward<T>(other))
        {}

        /**
         * Converting constructor from bint32, forwards to base implementation 
         * @param other
         */
        constexpr zint32(const bint32<FeatureMask>& other) noexcept
            : zval<izint32<FeatureMask>>(other.value())
        {}

        /**
         * @brief zint32 constructor [avx2 branch]
         * @relates zint32
         */
        constexpr zint32(  ) noexcept : zval<izint32<FeatureMask>>()
        {
        }
        /**
         * @brief zint32 constructor [avx2 branch]
         * @relates zint32
         */
        constexpr zint32(__m256 value) noexcept : zval<izint32<FeatureMask>>(_mm256_cvttps_epi32(value))
        {
        }
        /**
         * @brief zint32 constructor [avx2 branch]
         * @relates zint32
         */
        constexpr zint32(__m256d value) noexcept : zval<izint32<FeatureMask>>(_mm256_castsi128_si256(_mm256_cvttpd_epi32(value)))
        {
        }
        /**
         * @brief zint32 constructor [avx2 branch]
         * @relates zint32
         */
        constexpr zint32(__m256i value) noexcept : zval<izint32<FeatureMask>>(value)
        {
        }
        /**
         * @brief zint32 constructor [avx2 branch]
         * @relates zint32
         */
        constexpr zint32(int32_t value) noexcept : zval<izint32<FeatureMask>>(_mm256_set1_epi32(value))
        {
        }
        /**
         * @brief zint32 constructor [avx2 branch]
         * @relates zint32
         */
        constexpr zint32(extracted_type value) noexcept : zval<izint32<FeatureMask>>(_mm256_load_si256((__m256i*)value.data()))
        {
        }
        /**
         * @brief zint32 constructor [avx2 branch]
         * @relates zint32
         */
        constexpr zint32(int32_t _7, int32_t _6, int32_t _5, int32_t _4, int32_t _3, int32_t _2, int32_t _1, int32_t _0) noexcept : zval<izint32<FeatureMask>>(_mm256_set_epi32(_0, _1, _2, _3, _4, _5, _6, _7))
        {
        }
    };

    // =================================================================================================================

    /// public bint32 implementation [avx2 branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct bint32 : public bval<ibint32<FeatureMask>>,
        // generic traits
        printable<bint32<FeatureMask>, bint32<FeatureMask>>,
        convertable<bint32<FeatureMask>, bint32<FeatureMask>>,
        // int32 traits
        int32_modules::io<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::math<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::numeric<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::arithmetic<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::bitwise<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::bitwise_shift<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::comparable<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::logical<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::equatable<ibint32<FeatureMask>, bint32<FeatureMask>>,
        int32_modules::conditional<ibint32<FeatureMask>, bint32<FeatureMask>>
    {
        USING_ZTYPE(ibint32<FeatureMask>);

        /// complete vector
        using zval_t = zint32<FeatureMask>;

        /// complete boolean vector
        using bval_t = bint32<FeatureMask>;

        /// Forwarding constructor
        FORWARD2(bint32, bval<ibint32<FeatureMask>>);

    };

    // Validate zint32 ===================================================================================

    static_assert(std::is_base_of<izint32<0>,
                  izint32<0>>::value,
                  "base_of<izint32> != izint32.");
    static_assert(!std::is_base_of<ibint32<0>,
                  izint32<0>>::value,
                  "base_of<izint32> == ibint32.");

    static_assert(is_zval<izint32<0>>::value,
                  "is_zval<izint32> == false.");
    static_assert(!is_bval<izint32<0>>::value,
                  "is_bval<izint32> != false.");

    static_assert(std::is_base_of<izint32<0>, zint32<0>>::value,
                  "base_of<zint32> != izint32.");
    static_assert(!std::is_base_of<ibint32<0>, zint32<0>>::value,
                  "base_of<zint32> == ibint32.");

    static_assert(zint32<0>::size == 8,
                  "zint32::size != 8.");
    static_assert(zint32<0>::alignment == 32,
                  "zint32::alignment != 32.");
    static_assert(zint32<0>::is_vector == (8 > 1),
    "zint32::is_vector != (8 > 1).");

    static_assert(std::is_same<zint32<0>::tag, zval_tag > ::value,
                  "zint32::tag != zval_tag.");
    static_assert(std::is_same<zint32<0>::vector_type, __m256i > ::value,
                  "zint32::vector_type != __m256i.");
    static_assert(std::is_same<zint32<0>::element_type, int32_t > ::value,
                  "zint32::element_type != int32_t.");
    static_assert(std::is_same<zint32<0>::mask_vector_type, __m256i > ::value,
                  "zint32::mask_vector_type != __m256i.");
    static_assert(std::is_same<zint32<0>::extracted_type,
                  std::array<int32_t, 8>>::value,
                  "zint32::extracted_type != std::array<int32_t, 8>.");


    static_assert(std::is_same<typename ztraits<zint32<0>>::tag, zval_tag > ::value,
                  "zint32::tag != zval_tag.");
    static_assert(std::is_arithmetic<typename ztraits<zint32<0>>::element_type > ::value,
                  "is_arithmetic<zint32::element_type> == false.");
    static_assert(is_zval < zint32<0>>::value,
                  "is_zval<zint32> == false.");
    static_assert(!is_bval < zint32<0>>::value,
                  "is_bval<zint32> != false.");


    // Validate bint32 ===================================================================================


    static_assert(std::is_base_of<ibint32<0>,
                  ibint32<0>>::value,
                  "base_of<izint32> != izint32.");
    static_assert(!std::is_base_of<izint32<0>,
                  ibint32<0>>::value,
                  "base_of<izint32> == ibint32.");

    static_assert(!is_zval<ibint32<0>>::value,
                  "is_zval<ibint32> != false.");
    static_assert(is_bval<ibint32<0>>::value,
                  "is_bval<ibint32> == false.");

    static_assert(std::is_base_of<ibint32<0>, bint32<0>>::value,
                  "base_of<bint32> != ibint32.");
    static_assert(!std::is_base_of<izint32<0>, bint32<0>>::value,
                  "base_of<bint32> == izint32.");

    static_assert(bint32<0>::size == 8,
                  "bint32::size != 8.");
    static_assert(bint32<0>::alignment == 32,
                  "bint32::alignment != 32.");
    static_assert(bint32<0>::is_vector == (8 > 1),
    "bint32::is_vector != (8 > 1).");

    static_assert(std::is_same<bint32<0>::tag, bval_tag > ::value,
                  "bint32::tag != zval_tag.");
    static_assert(std::is_same<bint32<0>::vector_type, __m256i > ::value,
                  "bint32::vector_type != __m256i.");
    static_assert(std::is_same<bint32<0>::element_type, int32_t > ::value,
                  "bint32::element_type != int32_t.");
    static_assert(std::is_same<bint32<0>::mask_vector_type, __m256i > ::value,
                  "bint32::mask_vector_type != __m256i.");
    static_assert(std::is_same<bint32<0>::extracted_type,
                  std::array<int32_t, 8>>::value,
    "bint32::extracted_type != std::array<int32_t, 8>.");

    static_assert(std::is_same<typename ztraits<bint32<0>>::tag, bval_tag > ::value,
                  "bint32::tag != bval_tag.");
    static_assert(std::is_arithmetic<typename ztraits<bint32<0>>::element_type > ::value,
                  "is_arithmetic<bint32::element_type> == false.");
    static_assert(!is_zval < bint32<0>>::value,
                  "is_zval<bint32> != false.");
    static_assert(is_bval < bint32<0>>::value,
                  "is_bval<bint32> == false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<int32_t>::value ||
                  is_floating_point < zint32<0>>::value,
                  "is_floating_point<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_floating_point<int32_t>::value ||
                  !is_integral < zint32<0>>::value,
                  "is_integral<zint32> != false. [scalar = int32_t]");

    static_assert(
            !std::is_same<int32_t, float>::value || is_float < zint32<0>>::value,
            "is_float<zint32> == false. [scalar = int32_t]");
    static_assert(
            !std::is_same<int32_t, float>::value || !is_double < zint32<0>>::value,
            "is_double<zint32> != false. [scalar = int32_t]");

    static_assert(
            !std::is_same<int32_t, double>::value || is_double < zint32<0>>::value,
            "is_double<zint32> == false. [scalar = int32_t]");
    static_assert(
            !std::is_same<int32_t, double>::value || !is_float < zint32<0>>::value,
            "is_float<zint32> != false. [scalar = int32_t]");

    static_assert(
            !std::is_integral<int32_t>::value || is_integral < zint32<0>>::value,
            "is_integral<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_integral<int32_t>::value ||
                  !is_floating_point < zint32<0>>::value,
                  "is_floating_point<zint32> != false. [scalar = int32_t]");
}}}