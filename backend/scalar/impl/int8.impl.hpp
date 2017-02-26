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

#include <x86intrin.h>
#include <type_traits>

#include "../../../util/type_composition.hpp"

#include "../../../common/zval.hpp"
#include "../../../common/common.hpp"
#include "../../../common/type_traits.hpp"
#include "../../../common/traits/common.hpp"

#include "../../../common/traits/construction.hpp"
#include "../../../common/traits/io.hpp"
#include "../../../common/traits/arithmetic.hpp"
#include "../../../common/traits/bitwise.hpp"
#include "../../../common/traits/bitwise_shift.hpp"
#include "../../../common/traits/comparison.hpp"
#include "../../../common/traits/conditional.hpp"

/**
 * @brief int8 implementation for the scalar branch
 * provides unified access to 1 'char' values
 */

namespace zacc { namespace scalar {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates int8
     * @remark scalar
     */
    template<typename composed_t>
    struct int8_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates int8
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {


            /**
             * @brief construction default branch
             * @relates int8
             * @remark scalar - default
             */
            __impl(char value) : base_t(value) {
            }

        };

        /**
         * @brief construction public interface implementation
         * @relates int8
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
     * @relates int8
     * @remark scalar
     */
    template<typename composed_t>
    struct int8_io
    {

        /**
         * @brief io basic interface implementation
         * @relates int8
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates int8
             * @remark scalar - default
             */
            void io_store(typename base_t::extracted_t &target) const {
                target.data()[0] = base_t::_value;
            }


            /**
             * @brief io default branch
             * @relates int8
             * @remark scalar - default
             */
            void io_stream(typename base_t::extracted_t &target) const {
                target.data()[0] = base_t::_value;
            }

        };

        /**
         * @brief io public interface implementation
         * @relates int8
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
     * @relates int8
     * @remark scalar
     */
    template<typename composed_t>
    struct int8_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates int8
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t arithmetic_negate(composed_t one) {
                return -one.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t arithmetic_add(composed_t one, composed_t other) {
                return one.get_value() + other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t arithmetic_sub(composed_t one, composed_t other) {
                return one.get_value() - other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t arithmetic_mul(composed_t one, composed_t other) {
                return one.get_value() * other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t arithmetic_div(composed_t one, composed_t other) {
                return one.get_value() / other.get_value();
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates int8
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
     * @relates int8
     * @remark scalar
     */
    template<typename composed_t>
    struct int8_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates int8
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t bitwise_negate(composed_t one) {
                return ~one.get_value();
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t bitwise_and(composed_t one, composed_t other) {
                return one.get_value() & other.get_value();
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t bitwise_or(composed_t one, composed_t other) {
                return one.get_value() | other.get_value();
            }


            /**
             * @brief bitwise default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t bitwise_xor(composed_t one, composed_t other) {
                return one.get_value() ^ other.get_value();
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates int8
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
     * @relates int8
     * @remark scalar
     */
    template<typename composed_t>
    struct int8_bitwise_shift
    {

        /**
         * @brief bitwise_shift basic interface implementation
         * @relates int8
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief bitwise_shift default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t bitwise_shift_sll(composed_t one, composed_t other) {
                return one.get_value() << other.get_value();
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t bitwise_shift_srl(composed_t one, composed_t other) {
                return one.get_value() >> other.get_value();
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t bitwise_shift_slli(const composed_t one, const size_t other) {
                return one.get_value() << other;
            }


            /**
             * @brief bitwise_shift default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t bitwise_shift_srli(const composed_t one, const size_t other) {
                return one.get_value() >> other;
            }

        };

        /**
         * @brief bitwise_shift public interface implementation
         * @relates int8
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
     * @relates int8
     * @remark scalar
     */
    template<typename composed_t>
    struct int8_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates int8
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t comparison_eq(composed_t one, composed_t other) {
                return one.get_value() == other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t comparison_neq(composed_t one, composed_t other) {
                return one.get_value() != other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t comparison_gt(composed_t one, composed_t other) {
                return one.get_value() > other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t comparison_lt(composed_t one, composed_t other) {
                return one.get_value() < other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t comparison_ge(composed_t one, composed_t other) {
                return one.get_value() >= other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t comparison_le(composed_t one, composed_t other) {
                return one.get_value() <= other.get_value();
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates int8
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
     * @relates int8
     * @remark scalar
     */
    template<typename composed_t>
    struct int8_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates int8
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates int8
             * @remark scalar - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value) {
                return (condition.get_value() != 0 ? if_value : else_value);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates int8
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name int8 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - 'char' as underlying vector type
     * - 'char' as scalar type
     * - '1' as vector size
     * - '8' as alignment
     * @relates int8
     * @remark scalar
     */
    template<uint64_t capability>
    struct __zval_int8
    {
        using zval_t = zval<char, char, 1, 8, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates int8
     * @remark scalar
     */
    template<uint64_t capability>
    struct __zint8
    {
        struct impl;

        using zval_t = typename __zval_int8<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            convertable::impl,
            int8_io<impl>::template impl,
            int8_arithmetic<impl>::template impl,
            int8_bitwise<impl>::template impl,
            int8_bitwise_shift<impl>::template impl,
            int8_comparison<impl>::template impl,
            int8_conditional<impl>::template impl,
            int8_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    using zint8 = typename __zint8<capability>::impl;

    ///@}
}}