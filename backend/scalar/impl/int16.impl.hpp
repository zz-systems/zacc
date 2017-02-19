//---------------------------------------------------------------------------------
//
//  This is an autogenerated file. Do not edit!
//
//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2016 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

#pragma once

#include <intrin.h>
#include <type_traits>

#include "../../../common/zval.hpp"
#include "../../../common/common.hpp"
#include "../../../common/compose.hpp"
#include "../../../common/type_traits.hpp"
#include "../../../common/common_traits.hpp"

#include "../../../common/interfaces/construction.hpp"
#include "../../../common/interfaces/io.hpp"
#include "../../../common/interfaces/arithmetic.hpp"
#include "../../../common/interfaces/bitwise.hpp"
#include "../../../common/interfaces/bitwise_shift.hpp"
#include "../../../common/interfaces/comparison.hpp"
#include "../../../common/interfaces/conditional.hpp"

/**
 * @brief int16 implementation for the scalar branch
 * provides unified access to 1 'short' values
 */

namespace zacc { namespace scalar {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates int16
     * @remark scalar
     */
    template<typename composed_t>
    struct int16_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {


            /**
             * @brief construction default branch
             * @relates int16
             * @remark scalar - default
             */
            __impl(short value) : base_t(value) {
            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::construction<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name io operations
     */
    ///@{

    /**
     * @brief io
     * @relates int16
     * @remark scalar
     */
    template<typename composed_t>
    struct int16_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int16
             * @remark scalar - default
             */
            void io_store(typename base_t::extracted_t &target) const {
                target.data()[0] = base_t::_value;
            }


            /**
             * @brief io default branch
             * @relates int16
             * @remark scalar - default
             */
            void io_stream(typename base_t::extracted_t &target) const {
                target.data()[0] = base_t::_value;
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::io<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name arithmetic operations
     */
    ///@{

    /**
     * @brief arithmetic
     * @relates int16
     * @remark scalar
     */
    template<typename composed_t>
    struct int16_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t arithmetic_negate(composed_t one) {
                return -one.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t arithmetic_add(composed_t one, composed_t other) {
                return one.get_value() + other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t arithmetic_sub(composed_t one, composed_t other) {
                return one.get_value() - other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t arithmetic_mul(composed_t one, composed_t other) {
                return one.get_value() * other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t arithmetic_div(composed_t one, composed_t other) {
                return one.get_value() / other.get_value();
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::arithmetic<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name bitwise operations
     */
    ///@{

    /**
     * @brief bitwise
     * @relates int16
     * @remark scalar
     */
    template<typename composed_t>
    struct int16_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t bitwise_negate(composed_t one) {
                return ~one.get_value();
            }


            /**
             * @brief bitwise default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t bitwise_and(composed_t one, composed_t other) {
                return one.get_value() & other.get_value();
            }


            /**
             * @brief bitwise default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t bitwise_or(composed_t one, composed_t other) {
                return one.get_value() | other.get_value();
            }


            /**
             * @brief bitwise default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t bitwise_xor(composed_t one, composed_t other) {
                return one.get_value() ^ other.get_value();
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::bitwise<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name bitwise_shift operations
     */
    ///@{

    /**
     * @brief bitwise_shift
     * @relates int16
     * @remark scalar
     */
    template<typename composed_t>
    struct int16_bitwise_shift
    {

        /**
         * @brief bitwise_shift basic interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief bitwise_shift default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t bitwise_shift_sll(composed_t one, composed_t other) {
                return one.get_value() << other.get_value();
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t bitwise_shift_srl(composed_t one, composed_t other) {
                return one.get_value() >> other.get_value();
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t bitwise_shift_slli(const composed_t one, const size_t other) {
                return one.get_value() << other;
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t bitwise_shift_srli(const composed_t one, const size_t other) {
                return one.get_value() >> other;
            }

        };

        /**
         * @brief bitwise_shift public interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::bitwise_shift<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name comparison operations
     */
    ///@{

    /**
     * @brief comparison
     * @relates int16
     * @remark scalar
     */
    template<typename composed_t>
    struct int16_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t comparison_eq(composed_t one, composed_t other) {
                return one.get_value() == other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t comparison_neq(composed_t one, composed_t other) {
                return one.get_value() != other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t comparison_gt(composed_t one, composed_t other) {
                return one.get_value() > other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t comparison_lt(composed_t one, composed_t other) {
                return one.get_value() < other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t comparison_ge(composed_t one, composed_t other) {
                return one.get_value() >= other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t comparison_le(composed_t one, composed_t other) {
                return one.get_value() <= other.get_value();
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::comparison<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name conditional operations
     */
    ///@{

    /**
     * @brief conditional
     * @relates int16
     * @remark scalar
     */
    template<typename composed_t>
    struct int16_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates int16
             * @remark scalar - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value) {
                return (condition.get_value() != 0 ? if_value : else_value);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int16
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name int16 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - 'short' as underlying vector type
     * - 'short' as scalar type
     * - '1' as vector size
     * - '4' as alignment
     * @relates int16
     * @remark scalar
     */
    template<uint64_t capability>
    struct __zval_int16
    {
        using zval_t = zval<short, short, 1, 4, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates int16
     * @remark scalar
     */
    template<uint64_t capability>
    struct __zint16
    {
        struct impl;

        using zval_t = typename __zval_int16<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            convertable::impl,
            int16_io<impl>::template impl,
            int16_arithmetic<impl>::template impl,
            int16_bitwise<impl>::template impl,
            int16_bitwise_shift<impl>::template impl,
            int16_comparison<impl>::template impl,
            int16_conditional<impl>::template impl,
            int16_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    using zint16 = typename __zint16<capability>::impl;

    ///@}
}}