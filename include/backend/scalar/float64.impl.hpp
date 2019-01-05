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
 * This file provides defines required components and logic for float64 scalar target.
 * Provides unified access to 1 'double' values
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
#include "traits/io.hpp"
#include "traits/conditional.hpp"
#include "traits/bitwise.hpp"
#include "traits/equatable.hpp"
#include "traits/arithmetic.hpp"
#include "traits/comparable.hpp"
#include "traits/math.hpp"
#include "traits/logical.hpp"
#include "traits/numeric.hpp"

namespace zacc { namespace backend { namespace scalar
{
    /// @cond
    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct bfloat64;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    struct zfloat64;
    /// @endcond

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using izfloat64 = ztype<zval_tag, std::array<double, 1>, double, 1, 16, FeatureMask>;

    template<uint64_t FeatureMask>// = last_operation::undefined>
    using ibfloat64 = ztype<bval_tag, std::array<double, 1>, double, 1, 16, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for float64 [scalar branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::scalar::izfloat64<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value
            || std::is_base_of<backend::scalar::ibfloat64<std::decay_t<T>::feature_mask>, std::decay_t<T>>::value>>
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
        using vector_type = std::array<double, 1>;

        /// scalar type, like int for sse 4x integer vector
        using element_type = double;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = backend::scalar::zfloat64<std::decay_t<T>::feature_mask>;
        using bval_type = backend::scalar::bfloat64<std::decay_t<T>::feature_mask>;

        using tag = typename std::decay_t<T>::tag;
    };
}

namespace zacc { namespace backend { namespace scalar
{
    namespace float64_modules
    {
        /**
         * @brief io mixin implementation [scalar branch]
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
                result[0] = input.value();
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                result[0] = input.value();
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            template<typename RandomIt> friend Composed vgather(RandomIt input, const zint32<Interface::feature_mask> &index,  Composed) 
            {
                return input[index.value()];
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [scalar branch]
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
                return (condition.value() ? if_value : else_value);
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [scalar branch]
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
                auto _one = one.value();
                double result;
                bitsof(result) = ~bitsof(_one);
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vband(Composed one, Composed other) 
            {
                auto _one = one.value();
                auto _other = other.value();
                double result;
                bitsof(result) = bitsof(_one) & bitsof(_other);
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                auto _one = one.value();
                auto _other = other.value();
                double result;
                bitsof(result) = bitsof(_one) | bitsof(_other);
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                auto _one = one.value();
                auto _other = other.value();
                double result;
                bitsof(result) = bitsof(_one) ^ bitsof(_other);
                return result;
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend bool vis_set(Composed one) 
            {
                return one.value() != 0;
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [scalar branch]
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
                return (one.value() == other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vneq(Composed one, Composed other) 
            {
                return (one.value() != other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [scalar branch]
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
                return (-one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return (one.value() + other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return (one.value() - other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vmul(Composed one, Composed other) 
            {
                return (one.value() * other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                return (one.value() / other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vfmadd(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return multiplicand.value() * multiplier.value() + addendum.value();
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vfmsub(Composed multiplicand, Composed multiplier, Composed addendum) 
            {
                return multiplicand.value() * multiplier.value() - addendum.value();
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [scalar branch]
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
                return std::abs(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vmin(Composed one, Composed other) 
            {
                return std::min(one.value(), other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vmax(Composed one, Composed other) 
            {
                return std::max(one.value(), other.value());
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
                return (1 / one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vtrunc(Composed one) 
            {
                return std::trunc(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vfloor(Composed one) 
            {
                return std::floor(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vceil(Composed one) 
            {
                return std::ceil(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vround(Composed one) 
            {
                return std::round(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Composed vsqrt(Composed one) 
            {
                return std::sqrt(one.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [scalar branch]
         * @relates float64
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [scalar branch]
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
                return (one.value() > other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vlt(Composed one, Composed other) 
            {
                return (one.value() < other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vge(Composed one, Composed other) 
            {
                return (one.value() >= other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vle(Composed one, Composed other) 
            {
                return (one.value() <= other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [scalar branch]
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
                return (!one.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vlor(Composed one, Composed other) 
            {
                return (one.value() || other.value());
            }

            /**
             * @brief  [default branch]
             * @relates float64
             */
            friend Boolean vland(Composed one, Composed other) 
            {
                return (one.value() && other.value());
            }
        };
    } // end float64_modules

    // =================================================================================================================

    /// public zfloat64 implementation [scalar branch]
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
         * @brief zfloat64 constructor [scalar branch]
         * @relates zfloat64
         */
        constexpr zfloat64(double value) noexcept
            : zval<izfloat64<FeatureMask>>(value)
        {
        }
    };

    // =================================================================================================================

    /// public bfloat64 implementation [scalar branch]
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
        {
            //static_assert(size_v<T> == 1, "Dimension mismatch");
        }

        /**
         * @brief bfloat64 constructor [scalar branch]
         * @relates bfloat64
         */
        constexpr bfloat64(bool value) noexcept
            : zval<ibfloat64<FeatureMask>>(value)
        {
        }

        /**
         * @brief bfloat64 constructor [scalar branch]
         * @relates bfloat64
         */
        constexpr bfloat64(zfloat64<FeatureMask> value) noexcept
            : zval<ibfloat64<FeatureMask>>(value.value() != 0)
        {
        }
    };

    // Validate zfloat64 ===================================================================================

#define params 0

    static_assert( is_vector_v<izfloat64<params>> == false,    "is_vector_v<izfloat64> != false.");
    static_assert( is_vector_v<ibfloat64<params>> == false,    "is_vector_v<ibfloat64> != false.");

    static_assert( std::is_same<element_t<ibfloat64<params>>, double>::value,    "element_t<ibfloat64> != double.");

    static_assert( std::is_same<element_t<izfloat64<params>>, double>::value,    "element_t<izfloat64> != double.");
    static_assert( std::is_same<element_t<ibfloat64<params>>, double>::value,    "element_t<ibfloat64> != double.");

    static_assert( std::is_same<vector_t<izfloat64<params>>, std::array<double, 1>>::value,    "vector_t<izfloat64> != std::array<double, 1>.");
    static_assert( std::is_same<vector_t<ibfloat64<params>>, std::array<double, 1>>::value,    "vector_t<ibfloat64> != std::array<double, 1>.");

    static_assert( std::is_same<view_t<izfloat64<params>>, std::array<double, 1>>::value,    "view_t<izfloat64> != std::array<double, 1>.");
    static_assert( std::is_same<view_t<ibfloat64<params>>, std::array<bool, 1>>::value,                        "view_t<ibfloat64> != std::array<bool, 1>.");

//
    static_assert( std::is_base_of<izfloat64<params>, izfloat64<params>>::value, "base_of<izfloat64> != izfloat64.");
    static_assert(!std::is_base_of<ibfloat64<params>, izfloat64<params>>::value, "base_of<izfloat64> == ibfloat64.");

    static_assert( is_zval<izfloat64<params>>::value, "is_zval<izfloat64> == false.");
    static_assert(!is_bval<izfloat64<params>>::value, "is_bval<izfloat64> != false.");

    static_assert( std::is_base_of<izfloat64<params>, zfloat64<params>>::value, "base_of<zfloat64> != izfloat64.");
    static_assert(!std::is_base_of<ibfloat64<params>, zfloat64<params>>::value, "base_of<zfloat64> == ibfloat64.");

    static_assert(zfloat64<params>::size == 1, "zfloat64::size != 1.");
    static_assert(zfloat64<params>::alignment == 16, "zfloat64::alignment != 16.");
    static_assert(zfloat64<params>::is_vector == false, "zfloat64::is_vector != false.");

    static_assert(std::is_same<zfloat64<params>::tag, zval_tag>::value, "zfloat64::tag != zval_tag.");
    static_assert(std::is_same<zfloat64<params>::vector_type, std::array<double, 1>>::value, "zfloat64::vector_type != std::array<double, 1>.");
    static_assert(std::is_same<zfloat64<params>::element_type, double>::value, "zfloat64::element_type != double.");
    static_assert(std::is_same<zfloat64<params>::extracted_type, std::array<double, 1>>::value, "zfloat64::extracted_type != std::array<double, 1>.");

    static_assert( is_zval<zfloat64<params>>::value, "is_zval<zfloat64> == false.");
    static_assert(!is_bval<zfloat64<params>>::value, "is_bval<zfloat64> != false.");

    // Validate bfloat64 ===================================================================================

    static_assert( std::is_base_of<ibfloat64<params>, ibfloat64<params>>::value, "base_of<izfloat64> != izfloat64.");
    static_assert(!std::is_base_of<izfloat64<params>, ibfloat64<params>>::value, "base_of<izfloat64> == ibfloat64.");

    static_assert( is_bval<ibfloat64<params>>::value, "is_bval<ibfloat64> == false.");
    static_assert(!is_zval<ibfloat64<params>>::value, "is_zval<ibfloat64> != false.");

    static_assert( std::is_base_of<ibfloat64<params>, bfloat64<params>>::value, "base_of<bfloat64> != ibfloat64.");
    static_assert(!std::is_base_of<izfloat64<params>, bfloat64<params>>::value, "base_of<bfloat64> == izfloat64.");

    static_assert(bfloat64<params>::size == 1, "bfloat64::size != 1.");
    static_assert(bfloat64<params>::alignment == 16, "bfloat64::alignment != 16.");
    static_assert(bfloat64<params>::is_vector == false, "bfloat64::is_vector != false.");

    static_assert(std::is_same<bfloat64<params>::tag, bval_tag>::value, "bfloat64::tag != zval_tag.");
    static_assert(std::is_same<bfloat64<params>::vector_type, std::array<double, 1>>::value, "bfloat64::vector_type != std::array<double, 1>.");
    static_assert(std::is_same<bfloat64<params>::element_type, double>::value, "bfloat64::element_type != double.");
    static_assert(std::is_same<bfloat64<params>::extracted_type, std::array<double, 1>>::value, "bfloat64::extracted_type != std::array<double, 1>.");

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