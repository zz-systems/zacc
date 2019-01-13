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
 * This file provides defines required components and logic for float32 scalar target.
 * Provides unified access to 1 'float' values
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
#include "traits/comparable.hpp"
#include "traits/arithmetic.hpp"
#include "traits/equatable.hpp"
#include "traits/bitwise.hpp"
#include "traits/io.hpp"
#include "traits/logical.hpp"
#include "traits/conditional.hpp"
#include "traits/numeric.hpp"
#include "traits/math.hpp"

namespace zacc { namespace backend { namespace scalar
{
    /// @cond
    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct bfloat32;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct zfloat32;
    /// @endcond

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using izfloat32 = ztype<zval_tag, std::array<float, 1>, float, 1, 16, FeatureMask>;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using ibfloat32 = ztype<bval_tag, std::array<float, 1>, float, 1, 16, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for float32 [scalar branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::scalar::izfloat32<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value
            || std::is_base_of<backend::scalar::ibfloat32<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 1;

        /// capabilities
        static constexpr uint64_t feature_mask = std::decay_t<T>::feature_mask;

        /// memory alignment
        static constexpr size_t alignment = 16;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = std::array<float, 1>;

        /// scalar type, like int for sse 4x integer vector
        using element_type = float;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = backend::scalar::zfloat32<std::decay_t<T>::feature_mask>;
        using bval_type = backend::scalar::bfloat32<std::decay_t<T>::feature_mask>;

        using tag = typename std::decay_t<T>::tag;
    };
}

namespace zacc { namespace backend { namespace scalar
{
    namespace float32_modules
    {
        /**
         * @brief comparable mixin implementation [scalar branch]
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
                return (one.value() > other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vlt(Composed one, Composed other) 
            {
                return (one.value() < other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vge(Composed one, Composed other) 
            {
                return (one.value() >= other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vle(Composed one, Composed other) 
            {
                return (one.value() <= other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [scalar branch]
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
                return (-one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return (one.value() + other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return (one.value() - other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmul(Composed one, Composed other) 
            {
                return (one.value() * other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                return (one.value() / other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vfmadd(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return multiplicand.value() * multiplier.value() + addendum.value();
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vfmsub(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return multiplicand.value() * multiplier.value() - addendum.value();
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [scalar branch]
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
                return (one.value() == other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vneq(Composed one, Composed other) 
            {
                return (one.value() != other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [scalar branch]
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
                auto _one = one.value();
                float result;
                bitsof(result) = ~bitsof(_one);
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vband(Composed one, Composed other) 
            {
                auto _one = one.value();
                auto _other = other.value();
                float result;
                bitsof(result) = bitsof(_one) & bitsof(_other);
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                auto _one = one.value();
                auto _other = other.value();
                float result;
                bitsof(result) = bitsof(_one) | bitsof(_other);
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                auto _one = one.value();
                auto _other = other.value();
                float result;
                bitsof(result) = bitsof(_one) ^ bitsof(_other);
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend bool vis_set(Composed one) 
            {
                return one.value() != 0;
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation [scalar branch]
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
                result[0] = input.value();
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                result[0] = input.value();
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            template<typename RandomIt> friend Composed vgather(RandomIt input, const zint32<Interface::feature_mask> &index,  Composed) 
            {
                return input[index.value()];
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [scalar branch]
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
                return !one.value();
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vlor(Composed one, Composed other) 
            {
                return (one.value() || other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Boolean vland(Composed one, Composed other) 
            {
                return (one.value() && other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [scalar branch]
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
                return (condition.value() ? if_value : else_value);
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [scalar branch]
         * @relates float32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [scalar branch]
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
                return std::abs(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmin(Composed one, Composed other) 
            {
                return std::min(one.value(), other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vmax(Composed one, Composed other) 
            {
                return std::max(one.value(), other.value());
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
                return (1 / one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vtrunc(Composed one) 
            {
                return std::trunc(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vfloor(Composed one) 
            {
                return std::floor(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vceil(Composed one) 
            {
                return std::ceil(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vround(Composed one) 
            {
                return std::round(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float32
             */
            friend Composed vsqrt(Composed one) 
            {
                return std::sqrt(one.value());
            }
        };
    } // end float32_modules

    // =================================================================================================================

    /// public zfloat32 implementation [scalar branch]
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
         * @brief zfloat32 constructor [scalar branch]
         * @relates zfloat32
         */
        constexpr zfloat32(float value) noexcept
            : zval<izfloat32<FeatureMask>>(value)
        {
        }
    };

    // =================================================================================================================

    /// public bfloat32 implementation [scalar branch]
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
            //static_assert(size_v<T> == 1, "Dimension mismatch");
        }

        /**
         * @brief bfloat32 constructor [scalar branch]
         * @relates bfloat32
         */
        constexpr bfloat32(bool value) noexcept
            : zval<ibfloat32<FeatureMask>>(value)
        {
        }

        /**
         * @brief bfloat32 constructor [scalar branch]
         * @relates bfloat32
         */
        constexpr bfloat32(zfloat32<FeatureMask> value) noexcept
            : zval<ibfloat32<FeatureMask>>(value.value() != 0)
        {
        }
    };

    // Validate zfloat32 ===================================================================================

#define params 0

    static_assert( is_vector_v<izfloat32<params>> == false,    "is_vector_v<izfloat32> != false.");
    static_assert( is_vector_v<ibfloat32<params>> == false,    "is_vector_v<ibfloat32> != false.");

    static_assert( std::is_same<element_t<ibfloat32<params>>, float>::value,    "element_t<ibfloat32> != float.");

    static_assert( std::is_same<element_t<izfloat32<params>>, float>::value,    "element_t<izfloat32> != float.");
    static_assert( std::is_same<element_t<ibfloat32<params>>, float>::value,    "element_t<ibfloat32> != float.");

    static_assert( std::is_same<vector_t<izfloat32<params>>, std::array<float, 1>>::value,    "vector_t<izfloat32> != std::array<float, 1>.");
    static_assert( std::is_same<vector_t<ibfloat32<params>>, std::array<float, 1>>::value,    "vector_t<ibfloat32> != std::array<float, 1>.");

    static_assert( std::is_same<view_t<izfloat32<params>>, std::array<float, 1>>::value,    "view_t<izfloat32> != std::array<float, 1>.");
    static_assert( std::is_same<view_t<ibfloat32<params>>, std::array<bool, 1>>::value,                        "view_t<ibfloat32> != std::array<bool, 1>.");

//
    static_assert( std::is_base_of<izfloat32<params>, izfloat32<params>>::value, "base_of<izfloat32> != izfloat32.");
    static_assert(!std::is_base_of<ibfloat32<params>, izfloat32<params>>::value, "base_of<izfloat32> == ibfloat32.");

    static_assert( is_zval<izfloat32<params>>::value, "is_zval<izfloat32> == false.");
    static_assert(!is_bval<izfloat32<params>>::value, "is_bval<izfloat32> != false.");

    static_assert( std::is_base_of<izfloat32<params>, zfloat32<params>>::value, "base_of<zfloat32> != izfloat32.");
    static_assert(!std::is_base_of<ibfloat32<params>, zfloat32<params>>::value, "base_of<zfloat32> == ibfloat32.");

    static_assert(zfloat32<params>::size == 1, "zfloat32::size != 1.");
    static_assert(zfloat32<params>::alignment == 16, "zfloat32::alignment != 16.");
    static_assert(zfloat32<params>::is_vector == false, "zfloat32::is_vector != false.");

    static_assert(std::is_same<zfloat32<params>::tag, zval_tag>::value, "zfloat32::tag != zval_tag.");
    static_assert(std::is_same<zfloat32<params>::vector_type, std::array<float, 1>>::value, "zfloat32::vector_type != std::array<float, 1>.");
    static_assert(std::is_same<zfloat32<params>::element_type, float>::value, "zfloat32::element_type != float.");
    static_assert(std::is_same<zfloat32<params>::extracted_type, std::array<float, 1>>::value, "zfloat32::extracted_type != std::array<float, 1>.");

    static_assert( is_zval<zfloat32<params>>::value, "is_zval<zfloat32> == false.");
    static_assert(!is_bval<zfloat32<params>>::value, "is_bval<zfloat32> != false.");

    // Validate bfloat32 ===================================================================================

    static_assert( std::is_base_of<ibfloat32<params>, ibfloat32<params>>::value, "base_of<izfloat32> != izfloat32.");
    static_assert(!std::is_base_of<izfloat32<params>, ibfloat32<params>>::value, "base_of<izfloat32> == ibfloat32.");

    static_assert( is_bval<ibfloat32<params>>::value, "is_bval<ibfloat32> == false.");
    static_assert(!is_zval<ibfloat32<params>>::value, "is_zval<ibfloat32> != false.");

    static_assert( std::is_base_of<ibfloat32<params>, bfloat32<params>>::value, "base_of<bfloat32> != ibfloat32.");
    static_assert(!std::is_base_of<izfloat32<params>, bfloat32<params>>::value, "base_of<bfloat32> == izfloat32.");

    static_assert(bfloat32<params>::size == 1, "bfloat32::size != 1.");
    static_assert(bfloat32<params>::alignment == 16, "bfloat32::alignment != 16.");
    static_assert(bfloat32<params>::is_vector == false, "bfloat32::is_vector != false.");

    static_assert(std::is_same<bfloat32<params>::tag, bval_tag>::value, "bfloat32::tag != zval_tag.");
    static_assert(std::is_same<bfloat32<params>::vector_type, std::array<float, 1>>::value, "bfloat32::vector_type != std::array<float, 1>.");
    static_assert(std::is_same<bfloat32<params>::element_type, float>::value, "bfloat32::element_type != float.");
    static_assert(std::is_same<bfloat32<params>::extracted_type, std::array<float, 1>>::value, "bfloat32::extracted_type != std::array<float, 1>.");

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