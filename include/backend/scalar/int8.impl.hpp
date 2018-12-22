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
 * This file provides defines required components and logic for int8 scalar target.
 * Provides unified access to 1 'int8_t' values
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

#include "traits/convertable.hpp"
#include "traits/printable.hpp"
#include "traits/logical.hpp"
#include "traits/numeric.hpp"
#include "traits/io.hpp"
#include "traits/equatable.hpp"
#include "traits/math.hpp"
#include "traits/conditional.hpp"
#include "traits/bitwise.hpp"
#include "traits/arithmetic.hpp"
#include "traits/bitwise_shift.hpp"
#include "traits/comparable.hpp"

namespace zacc { namespace backend { namespace scalar
{
    /// @cond
    template<uint64_t features>
    struct bint8;

    template<uint64_t features>
    struct zint8;
    /// @endcond
    
    template<uint64_t FeatureMask>
    using izint8 = ztype<zval_tag, std::array<int8_t, 1>, int8_t, 1, 16, FeatureMask>;

    template<uint64_t FeatureMask>
    using ibint8 = ztype<bval_tag, std::array<int8_t, 1>, int8_t, 1, 16, FeatureMask>;
}}}

namespace zacc {

    /**
     * @brief ztraits type trait specialization for int8 [scalar branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<
            std::is_base_of<backend::scalar::izint8<T::feature_mask>, T>::value
            || std::is_base_of<backend::scalar::ibint8<T::feature_mask>, T>::value>>
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
        using vector_type = std::array<int8_t, 1>;

        /// scalar type, like int for sse 4x integer vector
        using element_type = int8_t;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_t = backend::scalar::zint8<T::feature_mask>;
        using bval_t = backend::scalar::bint8<T::feature_mask>;

        using tag = select_t<
            when<std::is_base_of<backend::scalar::izint8<T::feature_mask>, T>::value, zval_tag>,
            when<std::is_base_of<backend::scalar::ibint8<T::feature_mask>, T>::value, bval_tag>>;
    };
}

namespace zacc { namespace backend { namespace scalar
{
    namespace int8_modules
    {
        /**
         * @brief io mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct io : traits::io<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename OutputIt> friend void vstore(OutputIt result, Composed input) 
            {
                result[0] = input.value();
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            template<typename OutputIt> friend void vstream(OutputIt result, Composed input) 
            {
                result[0] = input.value();
            }
        };

        // =============================================================================================================

        /**
         * @brief math mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct math : traits::math<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vabs(Composed one) 
            {
                return std::abs(one.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vmin(Composed one, Composed other) 
            {
                return std::min(one.value(), other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vmax(Composed one, Composed other) 
            {
                return std::max(one.value(), other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vclamp(Composed self, Composed from, Composed to) 
            {
                return vmin(to, vmax(from, self));
            }
        };

        // =============================================================================================================

        /**
         * @brief numeric mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct numeric : traits::numeric<Interface, Composed, bint8<Interface::feature_mask>>
        {
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct arithmetic : traits::arithmetic<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vneg(Composed one) 
            {
                return (-one.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vadd(Composed one, Composed other) 
            {
                return (one.value() + other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vsub(Composed one, Composed other) 
            {
                return (one.value() - other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vmul(Composed one, Composed other) 
            {
                return (one.value() * other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vdiv(Composed one, Composed other) 
            {
                return (one.value() / other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vmod(Composed one, Composed other) 
            {
                return (one.value() % other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct bitwise : traits::bitwise<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vbneg(Composed one) 
            {
                return (~one.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vband(Composed one, Composed other) 
            {
                return (one.value() & other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vbor(Composed one, Composed other) 
            {
                return (one.value() | other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vbxor(Composed one, Composed other) 
            {
                return (one.value() ^ other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bool is_set(Composed one) 
            {
                return one.value() != 0;
            }
        };

        // =============================================================================================================

        /**
         * @brief bitwise_shift mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct bitwise_shift : traits::bitwise_shift<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vbsll(Composed one, Composed other) 
            {
                return (one.value() << other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vbsrl(Composed one, Composed other) 
            {
                return (one.value() >> other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vbslli(const Composed one, const size_t other) 
            {
                return (one.value() << other);
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vbsrli(const Composed one, const size_t other) 
            {
                return (one.value() >> other);
            }
        };

        // =============================================================================================================

        /**
         * @brief comparable mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct comparable : traits::comparable<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> vgt(Composed one, Composed other) 
            {
                return (one.value() > other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> vlt(Composed one, Composed other) 
            {
                return (one.value() < other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> vge(Composed one, Composed other) 
            {
                return (one.value() >= other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> vle(Composed one, Composed other) 
            {
                return (one.value() <= other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief logical mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct logical : traits::logical<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> vlneg(Composed one) 
            {
                return (!one.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> vlor(Composed one, Composed other) 
            {
                return (one.value() || other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> vland(Composed one, Composed other) 
            {
                return (one.value() && other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct equatable : traits::equatable<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> veq(Composed one, Composed other) 
            {
                return (one.value() == other.value());
            }
            
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend bint8<Interface::feature_mask> vneq(Composed one, Composed other) 
            {
                return (one.value() != other.value());
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation [scalar branch]
         * @relates int8
         */
        template<typename Interface, typename Composed>
        struct conditional : traits::conditional<Interface, Composed, bint8<Interface::feature_mask>>
        {
            /**
             * @brief  [default branch]
             * @relates int8
             */
            friend zint8<Interface::feature_mask> vsel(bint8<Interface::feature_mask> condition, Composed if_value, Composed else_value) 
            {
                return (condition.value() ? if_value : else_value);
            }
        };
    } // end int8_modules

    // =================================================================================================================

    /// public zint8 implementation [scalar branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct zint8 : public zval<izint8<FeatureMask>>,

        // generic traits
        printable<izint8<FeatureMask>, zint8<FeatureMask>>,
        convertable<izint8<FeatureMask>, zint8<FeatureMask>>,

        // int8 traits
        int8_modules::io<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::math<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::numeric<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::arithmetic<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::bitwise<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::bitwise_shift<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::comparable<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::logical<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::equatable<izint8<FeatureMask>, zint8<FeatureMask>>,
        int8_modules::conditional<izint8<FeatureMask>, zint8<FeatureMask>>
    {
        USING_ZTYPE(izint8<FeatureMask>);

        /// complete vector
        using zval_t = zint8<FeatureMask>;

        /// complete boolean vector
        using bval_t = bint8<FeatureMask>;

        /**
         * Copy constructor, forwards to base implementation
         * @tparam T any type convertable to std::array<int8_t, 1>
         * @param other
         */
        template<typename T, typename = std::enable_if_t<std::is_convertible<T, std::array<int8_t, 1>>::value>>
        constexpr zint8(const T& other) noexcept
            : zval<izint8<FeatureMask>>(other)
        {}

        /**
         * Move constructor, forwards to base implementation
         * @tparam T any type convertable to std::array<int8_t, 1>
         * @param other
         */
        template<typename T, typename = std::enable_if_t<(size > 1) && std::is_convertible<T, std::array<int8_t, 1>>::value>>
        constexpr zint8(T&& other) noexcept
            : zval<izint8<FeatureMask>>(std::forward<T>(other))
        {}

        /**
         * Converting constructor from bint8, forwards to base implementation 
         * @param other
         */
        constexpr zint8(const bint8<FeatureMask>& other) noexcept
            : zval<izint8<FeatureMask>>(other.value())
        {}

        /**
         * @brief zint8 constructor [scalar branch]
         * @relates zint8
         */
        constexpr zint8(  ) noexcept
            : zval<izint8<FeatureMask>>()
        {
        }

        /**
         * @brief zint8 constructor [scalar branch]
         * @relates zint8
         */
        constexpr zint8(int8_t value) noexcept
            : zval<izint8<FeatureMask>>(value)
        {
        }

        /**
         * @brief zint8 constructor [scalar branch]
         * @relates zint8
         */
        constexpr zint8(extracted_type value) noexcept
            : zval<izint8<FeatureMask>>(value[0])
        {
        }
    };

    // =================================================================================================================

    /// public bint8 implementation [scalar branch]
    /// @tparam FeatureMask feature mask
    template<uint64_t FeatureMask>
    struct bint8 : public zval<ibint8<FeatureMask>>,

        // generic traits
        printable<bint8<FeatureMask>, bint8<FeatureMask>>,
        convertable<bint8<FeatureMask>, bint8<FeatureMask>>,

        // int8 traits
        int8_modules::io<ibint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::bitwise<ibint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::logical<ibint8<FeatureMask>, bint8<FeatureMask>>,
        int8_modules::equatable<ibint8<FeatureMask>, bint8<FeatureMask>>
    {
        USING_ZTYPE(ibint8<FeatureMask>);

        /// complete vector
        using zval_t = zint8<FeatureMask>;

        /// complete boolean vector
        using bval_t = bint8<FeatureMask>;

        /// Forwarding constructor
        FORWARD2(bint8, zval<ibint8<FeatureMask>>);

    };

    // Validate zint8 ===================================================================================

    static_assert( std::is_base_of<izint8<0>, izint8<0>>::value, "base_of<izint8> != izint8.");
    static_assert(!std::is_base_of<ibint8<0>, izint8<0>>::value, "base_of<izint8> == ibint8.");

    static_assert( is_zval<izint8<0>>::value, "is_zval<izint8> == false.");
    static_assert(!is_bval<izint8<0>>::value, "is_bval<izint8> != false.");

    static_assert( std::is_base_of<izint8<0>, zint8<0>>::value, "base_of<zint8> != izint8.");
    static_assert(!std::is_base_of<ibint8<0>, zint8<0>>::value, "base_of<zint8> == ibint8.");

    static_assert(zint8<0>::size == 1, "zint8::size != 1.");
    static_assert(zint8<0>::alignment == 16, "zint8::alignment != 16.");
    static_assert(zint8<0>::is_vector == false, "zint8::is_vector != false.");

    static_assert(std::is_same<zint8<0>::tag, zval_tag>::value, "zint8::tag != zval_tag.");
    static_assert(std::is_same<zint8<0>::vector_type, std::array<int8_t, 1>>::value, "zint8::vector_type != std::array<int8_t, 1>.");
    static_assert(std::is_same<zint8<0>::element_type, int8_t>::value, "zint8::element_type != int8_t.");
    static_assert(std::is_same<zint8<0>::extracted_type, std::array<int8_t, 1>>::value, "zint8::extracted_type != std::array<int8_t, 1>.");

    static_assert( is_zval<zint8<0>>::value, "is_zval<zint8> == false.");
    static_assert(!is_bval<zint8<0>>::value, "is_bval<zint8> != false.");

    // Validate bint8 ===================================================================================

    static_assert( std::is_base_of<ibint8<0>, ibint8<0>>::value, "base_of<izint8> != izint8.");
    static_assert(!std::is_base_of<izint8<0>, ibint8<0>>::value, "base_of<izint8> == ibint8.");

    static_assert( is_bval<ibint8<0>>::value, "is_bval<ibint8> == false.");
    static_assert(!is_zval<ibint8<0>>::value, "is_zval<ibint8> != false.");

    static_assert( std::is_base_of<ibint8<0>, bint8<0>>::value, "base_of<bint8> != ibint8.");
    static_assert(!std::is_base_of<izint8<0>, bint8<0>>::value, "base_of<bint8> == izint8.");

    static_assert(bint8<0>::size == 1, "bint8::size != 1.");
    static_assert(bint8<0>::alignment == 16, "bint8::alignment != 16.");
    static_assert(bint8<0>::is_vector == false, "bint8::is_vector != false.");

    static_assert(std::is_same<bint8<0>::tag, bval_tag>::value, "bint8::tag != zval_tag.");
    static_assert(std::is_same<bint8<0>::vector_type, std::array<int8_t, 1>>::value, "bint8::vector_type != std::array<int8_t, 1>.");
    static_assert(std::is_same<bint8<0>::element_type, int8_t>::value, "bint8::element_type != int8_t.");
    static_assert(std::is_same<bint8<0>::extracted_type, std::array<int8_t, 1>>::value, "bint8::extracted_type != std::array<int8_t, 1>.");

    static_assert( is_bval<bint8<0>>::value, "is_bval<bint8> == false.");
    static_assert(!is_zval<bint8<0>>::value, "is_zval<bint8> != false.");

    // Validate integral, float, double traits =========================================================================

    static_assert(!std::is_floating_point<int8_t>::value || is_floating_point < zint8<0>>::value, "is_floating_point<zint8> == false. [scalar = int8_t]");
    static_assert(!std::is_floating_point<int8_t>::value || !is_integral<zint8<0>>::value, "is_integral<zint8> != false. [scalar = int8_t]");

    static_assert(!std::is_same<int8_t, float>::value || is_float < zint8<0>>::value, "is_float<zint8> == false. [scalar = int8_t]");
    static_assert(!std::is_same<int8_t, float>::value || !is_double < zint8<0>>::value, "is_double<zint8> != false. [scalar = int8_t]");

    static_assert(!std::is_same<int8_t, double>::value || is_double < zint8<0>>::value, "is_double<zint8> == false. [scalar = int8_t]");
    static_assert(!std::is_same<int8_t, double>::value || !is_float < zint8<0>>::value, "is_float<zint8> != false. [scalar = int8_t]");

    static_assert(!std::is_integral<int8_t>::value || is_integral<zint8<0>>::value,"is_integral<zint8> == false. [scalar = int8_t]");
    static_assert(!std::is_integral<int8_t>::value || !is_floating_point < zint8<0>>::value, "is_floating_point<zint8> != false. [scalar = int8_t]");
}}}