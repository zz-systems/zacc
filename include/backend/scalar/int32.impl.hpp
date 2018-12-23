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
 * This file provides defines required components and logic for int32 scalar target.
 * Provides unified access to 1 'int32_t' values
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
#include "traits/bitwise_shift.hpp"
#include "traits/math.hpp"
#include "traits/io.hpp"
#include "traits/logical.hpp"
#include "traits/bitwise.hpp"
#include "traits/numeric.hpp"
#include "traits/conditional.hpp"
#include "traits/equatable.hpp"
#include "traits/arithmetic.hpp"
#include "traits/comparable.hpp"

namespace zacc { namespace backend { namespace scalar
{
    /// @cond
    template<uint64_t features>
    struct bint32;

    template<uint64_t features>
    struct zint32;
    /// @endcond

    template<uint64_t FeatureMask>
    using izint32 = ztype<zval_tag, std::array<int32_t, 1>, int32_t, 1, 16, FeatureMask>;

    template<uint64_t FeatureMask>
    using ibint32 = ztype<bval_tag, std::array<int32_t, 1>, int32_t, 1, 16, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for int32 [scalar branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::scalar::izint32<T::feature_mask>, T>::value
            || std::is_base_of<backend::scalar::ibint32<T::feature_mask>, T>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 1;

        /// capabilities
        static constexpr uint64_t feature_mask = T::feature_mask;

        /// memory alignment
        static constexpr size_t alignment = 16;

        /// scalar type? vector type?
        static constexpr bool is_vector = size > 1;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = std::array<int32_t, 1>;

        /// scalar type, like int for sse 4x integer vector
        using element_type = int32_t;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = backend::scalar::zint32<T::feature_mask>;
        using bval_type = backend::scalar::bint32<T::feature_mask>;

        using tag = typename T::tag;
    };
}

namespace zacc { namespace backend { namespace scalar
{
    namespace int32_modules
    {
        /**
         * @brief bitwise_shift mixin implementation [scalar branch]
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
                return (one.value() << other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbsrl(Composed one, Composed other) 
            {
                return (one.value() >> other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbslli(const Composed one, const size_t other) 
            {
                return (one.value() << other);
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbsrli(const Composed one, const size_t other) 
            {
                return (one.value() >> other);
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [scalar branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct math : traits::math<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vabs(Composed one) 
            {
                return std::abs(one.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vmin(Composed one, Composed other) 
            {
                return std::min(one.value(), other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vmax(Composed one, Composed other) 
            {
                return std::max(one.value(), other.value());
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
                return std::sqrt(one.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation [scalar branch]
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
                result[0] = input.value();
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                result[0] = input.value();
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            template<typename RandomIt> friend Composed vgather(RandomIt input, const zint32<Interface::feature_mask> &index,  Composed) 
            {
                return input[index.value()];
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [scalar branch]
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
                return (!one.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vlor(Composed one, Composed other) 
            {
                return (one.value() || other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vland(Composed one, Composed other) 
            {
                return (one.value() && other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [scalar branch]
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
                return (~one.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vband(Composed one, Composed other) 
            {
                return (one.value() & other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbor(Composed one, Composed other) 
            {
                return (one.value() | other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vbxor(Composed one, Composed other) 
            {
                return (one.value() ^ other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend bool vis_set(Composed one) 
            {
                return one.value() != 0;
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [scalar branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct numeric : traits::numeric<Interface, Composed, Boolean>
        {
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [scalar branch]
         * @relates int32
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct conditional : traits::conditional<Interface, Composed, Boolean>
        {
            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vsel(Boolean condition, Composed if_value, Composed else_value) 
            {
                return (condition.value() ? if_value : else_value);
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [scalar branch]
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
                return (one.value() == other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vneq(Composed one, Composed other) 
            {
                return (one.value() != other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [scalar branch]
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
                return (-one.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vadd(Composed one, Composed other) 
            {
                return (one.value() + other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vsub(Composed one, Composed other) 
            {
                return (one.value() - other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vmul(Composed one, Composed other) 
            {
                return (one.value() * other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vdiv(Composed one, Composed other) 
            {
                return (one.value() / other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Composed vmod(Composed one, Composed other) 
            {
                return (one.value() % other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [scalar branch]
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
                return (one.value() > other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vlt(Composed one, Composed other) 
            {
                return (one.value() < other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vge(Composed one, Composed other) 
            {
                return (one.value() >= other.value());
            }

            /**
             * @brief  [default branch]
             * @relates int32
             */
            friend Boolean vle(Composed one, Composed other) 
            {
                return (one.value() <= other.value());
            }
        };
    } // end int32_modules

    // =================================================================================================================

    /// public zint32 implementation [scalar branch]
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
        USING_ZTYPE(izint32<FeatureMask>);

        using zval<izint32<FeatureMask>>::zval;

        template<typename T, typename std::enable_if<is_zval<T>::value, void**>::type = nullptr>
        constexpr zint32(const T& other) noexcept
                : zint32(other.value())
        {}

        explicit constexpr zint32(const bval_t<izint32<FeatureMask>>& other) noexcept
                : zint32(other.value())
        {}

        /**
         * @brief zint32 constructor [scalar branch]
         * @relates zint32
         */
        constexpr zint32(int32_t value) noexcept
            : zval<izint32<FeatureMask>>(std::array<int32_t, 1> {{value}})
        {
        }

        /**
         * @brief zint32 constructor [scalar branch]
         * @relates zint32
         */
        constexpr zint32(extracted_type value) noexcept
            : zval<izint32<FeatureMask>>(value)
        {
        }
    };

    // =================================================================================================================

    /// public bint32 implementation [scalar branch]
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
        USING_ZTYPE(ibint32<FeatureMask>);

        using zval<ibint32<FeatureMask>>::zval;

        template<typename T, typename std::enable_if<is_zval<T>::value, void**>::type = nullptr>
        constexpr bint32(const T& other) noexcept
                : bint32(other.value())
        {}

        template<typename T, typename std::enable_if<is_bval<T>::value, void**>::type = nullptr>
        constexpr bint32(const T& other) noexcept
                : bint32(other.raw_value())
        {}


        /**
         * @brief bint32 constructor [scalar branch]
         * @relates bint32
         */
        constexpr bint32(bool value) noexcept
            : zval<ibint32<FeatureMask>>(std::array<bool, 1> {{ value }})
        {
        }

        /**
         * @brief bint32 constructor [scalar branch]
         * @relates bint32
         */
        constexpr bint32(zint32<FeatureMask> value) noexcept
            : zval<ibint32<FeatureMask>>(std::array<bool, 1> {{ value.value() != 0 }})
        {
        }
    };

    // Validate zint32 ===================================================================================

    static_assert( std::is_base_of<izint32<0>, izint32<0>>::value, "base_of<izint32> != izint32.");
    static_assert(!std::is_base_of<ibint32<0>, izint32<0>>::value, "base_of<izint32> == ibint32.");

    static_assert( is_zval<izint32<0>>::value, "is_zval<izint32> == false.");
    static_assert(!is_bval<izint32<0>>::value, "is_bval<izint32> != false.");

    static_assert( std::is_base_of<izint32<0>, zint32<0>>::value, "base_of<zint32> != izint32.");
    static_assert(!std::is_base_of<ibint32<0>, zint32<0>>::value, "base_of<zint32> == ibint32.");

    static_assert(zint32<0>::size == 1, "zint32::size != 1.");
    static_assert(zint32<0>::alignment == 16, "zint32::alignment != 16.");
    static_assert(zint32<0>::is_vector == false, "zint32::is_vector != false.");

    static_assert(std::is_same<zint32<0>::tag, zval_tag>::value, "zint32::tag != zval_tag.");
    static_assert(std::is_same<zint32<0>::vector_type, std::array<int32_t, 1>>::value, "zint32::vector_type != std::array<int32_t, 1>.");
    static_assert(std::is_same<zint32<0>::element_type, int32_t>::value, "zint32::element_type != int32_t.");
    static_assert(std::is_same<zint32<0>::extracted_type, std::array<int32_t, 1>>::value, "zint32::extracted_type != std::array<int32_t, 1>.");

    static_assert( is_zval<zint32<0>>::value, "is_zval<zint32> == false.");
    static_assert(!is_bval<zint32<0>>::value, "is_bval<zint32> != false.");

    // Validate bint32 ===================================================================================

    static_assert( std::is_base_of<ibint32<0>, ibint32<0>>::value, "base_of<izint32> != izint32.");
    static_assert(!std::is_base_of<izint32<0>, ibint32<0>>::value, "base_of<izint32> == ibint32.");

    static_assert( is_bval<ibint32<0>>::value, "is_bval<ibint32> == false.");
    static_assert(!is_zval<ibint32<0>>::value, "is_zval<ibint32> != false.");

    static_assert( std::is_base_of<ibint32<0>, bint32<0>>::value, "base_of<bint32> != ibint32.");
    static_assert(!std::is_base_of<izint32<0>, bint32<0>>::value, "base_of<bint32> == izint32.");

    static_assert(bint32<0>::size == 1, "bint32::size != 1.");
    static_assert(bint32<0>::alignment == 16, "bint32::alignment != 16.");
    static_assert(bint32<0>::is_vector == false, "bint32::is_vector != false.");

    static_assert(std::is_same<bint32<0>::tag, bval_tag>::value, "bint32::tag != zval_tag.");
    static_assert(std::is_same<bint32<0>::vector_type, std::array<int32_t, 1>>::value, "bint32::vector_type != std::array<int32_t, 1>.");
    static_assert(std::is_same<bint32<0>::element_type, int32_t>::value, "bint32::element_type != int32_t.");
    static_assert(std::is_same<bint32<0>::extracted_type, std::array<int32_t, 1>>::value, "bint32::extracted_type != std::array<int32_t, 1>.");

    static_assert( is_bval<bint32<0>>::value, "is_bval<bint32> == false.");
    static_assert(!is_zval<bint32<0>>::value, "is_zval<bint32> != false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<int32_t>::value || is_floating_point < zint32<0>>::value, "is_floating_point<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_floating_point<int32_t>::value || !is_integral<zint32<0>>::value, "is_integral<zint32> != false. [scalar = int32_t]");

    static_assert(!std::is_same<int32_t, float>::value || is_float < zint32<0>>::value, "is_float<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_same<int32_t, float>::value || !is_double < zint32<0>>::value, "is_double<zint32> != false. [scalar = int32_t]");

    static_assert(!std::is_same<int32_t, double>::value || is_double < zint32<0>>::value, "is_double<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_same<int32_t, double>::value || !is_float < zint32<0>>::value, "is_float<zint32> != false. [scalar = int32_t]");

    static_assert(!std::is_integral<int32_t>::value || is_integral<zint32<0>>::value,"is_integral<zint32> == false. [scalar = int32_t]");
    static_assert(!std::is_integral<int32_t>::value || !is_floating_point < zint32<0>>::value, "is_floating_point<zint32> != false. [scalar = int32_t]");
}}}