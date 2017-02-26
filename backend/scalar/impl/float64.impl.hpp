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
#include "../../../common/traits/comparison.hpp"
#include "../../../common/traits/conditional.hpp"

/**
 * @brief float64 implementation for the scalar branch
 * provides unified access to 1 'double' values
 */

namespace zacc { namespace scalar {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {


            /**
             * @brief construction default branch
             * @relates float64
             * @remark scalar - default
             */
            __impl(double value) : base_t(value) {
            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates float64
             * @remark scalar - default
             */
            void io_store(typename base_t::extracted_t &target) const {
                target.data()[0] = base_t::_value;
            }


            /**
             * @brief io default branch
             * @relates float64
             * @remark scalar - default
             */
            void io_stream(typename base_t::extracted_t &target) const {
                target.data()[0] = base_t::_value;
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t arithmetic_negate(composed_t one) {
                return -one.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t arithmetic_add(composed_t one, composed_t other) {
                return one.get_value() + other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t arithmetic_sub(composed_t one, composed_t other) {
                return one.get_value() - other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t arithmetic_mul(composed_t one, composed_t other) {
                return one.get_value() * other.get_value();
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t arithmetic_div(composed_t one, composed_t other) {
                return one.get_value() / other.get_value();
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::arithmetic<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name comparison operations
     */
    ///@{

    /**
     * @brief comparison
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t comparison_eq(composed_t one, composed_t other) {
                return one.get_value() == other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t comparison_neq(composed_t one, composed_t other) {
                return one.get_value() != other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t comparison_gt(composed_t one, composed_t other) {
                return one.get_value() > other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t comparison_lt(composed_t one, composed_t other) {
                return one.get_value() < other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t comparison_ge(composed_t one, composed_t other) {
                return one.get_value() >= other.get_value();
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t comparison_le(composed_t one, composed_t other) {
                return one.get_value() <= other.get_value();
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float64
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
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates float64
             * @remark scalar - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value) {
                return (condition.get_value() != 0 ? if_value : else_value);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float64 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - 'double' as underlying vector type
     * - 'double' as scalar type
     * - '1' as vector size
     * - '8' as alignment
     * @relates float64
     * @remark scalar
     */
    template<uint64_t capability>
    struct __zval_float64
    {
        using zval_t = zval<double, double, 1, 8, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates float64
     * @remark scalar
     */
    template<uint64_t capability>
    struct __zfloat64
    {
        struct impl;

        using zval_t = typename __zval_float64<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            convertable::impl,
            float64_io<impl>::template impl,
            float64_arithmetic<impl>::template impl,
            float64_comparison<impl>::template impl,
            float64_conditional<impl>::template impl,
            float64_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    using zfloat64 = typename __zfloat64<capability>::impl;

    ///@}
}}