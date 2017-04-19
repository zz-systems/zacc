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
#include <cmath>

#include "util/type_composition.hpp"

#include "zval.hpp"
#include "common.hpp"
#include "type_traits.hpp"

#include "traits/common.hpp"
#include "traits/construction.hpp"
#include "traits/io.hpp"
#include "traits/numeric.hpp"
#include "traits/math.hpp"
#include "traits/arithmetic.hpp"
#include "traits/comparison.hpp"
#include "traits/conditional.hpp"

/**
 * @brief float32 implementation for the scalar branch
 * provides unified access to 1 'float' values
 */

namespace zacc { namespace scalar {

    // =================================================================================================================
    /**
     * @name construction operations
     */
    ///@{

    /**
     * @brief construction
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_construction
    {

        /**
         * @brief construction basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;



            /**
             * @brief construction default branch
             * @relates float32
             * @remark scalar - default
             */
            __impl() : base_t() {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark scalar - default
             */
            __impl(float value) : base_t(value) {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "CONS(float value)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float32
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
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates float32
             * @remark scalar - default
             */
            friend void vstore(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vstore");

                target.data()[0] = source.get_value();
            }


            /**
             * @brief io default branch
             * @relates float32
             * @remark scalar - default
             */
            friend void vstream(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vstream");

                target.data()[0] = source.get_value();
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::io<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name numeric operations
     */
    ///@{

    /**
     * @brief numeric
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_numeric
    {

        /**
         * @brief numeric basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);

        };

        /**
         * @brief numeric public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::numeric<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name math operations
     */
    ///@{

    /**
     * @brief math
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_math
    {

        /**
         * @brief math basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vabs(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vabs");

                return std::abs(one);
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vrcp(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vrcp");

                return (1 / one);
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vtrunc(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vtrunc");

                return std::trunc(one);
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vfloor(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vfloor");

                return std::floor(one);
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vceil(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vceil");

                return std::ceil(one);
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vround(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vround");

                return std::round(one);
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vsqrt(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vsqrt");

                return std::sqrt(one);
            }

        };

        /**
         * @brief math public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::math<__impl<base_t>, composed_t>;
    };

    ///@}


    // =================================================================================================================
    /**
     * @name arithmetic operations
     */
    ///@{

    /**
     * @brief arithmetic
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_arithmetic
    {

        /**
         * @brief arithmetic basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vneg(composed_t one)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vneg");

                return (-one);
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vadd");

                return (one + other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vsub");

                return (one - other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vmul");

                return (one * other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vdiv(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vdiv");

                return (one / other);
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vfmadd(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vfmadd");

                return std::fma(multiplicand, multiplier, addendum);
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vfmsub(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vfmsub");

                return std::fma(multiplicand, multiplier, -addendum);
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float32
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
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_comparison
    {

        /**
         * @brief comparison basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend mask_t veq(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "veq");

                return (one == other);
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend mask_t vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vneq");

                return (one != other);
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend mask_t vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vgt");

                return (one > other);
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend mask_t vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vlt");

                return (one < other);
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend mask_t vge(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vge");

                return (one >= other);
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend mask_t vle(composed_t one, composed_t other)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vle");

                return (one <= other);
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float32
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
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates float32
             * @remark scalar - default
             */
            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE(std::left << std::setw(32) << "scalar.float32.impl line " STRINGIZE(__LINE__) ":" << std::left << std::setw(24) << " zfloat32(float[1]) " << std::left << std::setw(10) << "default" << "vsel");

                return (condition.get_value() != 0 ? if_value : else_value);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float32 composition
     */
    ///@{

    /**
     * @brief zval parametrization using
     * - 'float' as underlying vector type
     * - 'float' as scalar type
     * - '1' as vector size
     * - '8' as alignment
     * @relates float32
     * @remark scalar
     */
    template<uint64_t capability>
    struct __zval_float32
    {
        using zval_t = zval<float, bool, float, 1, 8, capability>;

        struct impl : public zval_t
        {
            FORWARD2(impl, zval_t);
        };
    };
    /**
     * @brief zval composition
     * @relates float32
     * @remark scalar
     */
    template<uint64_t capability>
    struct __zfloat32
    {
        struct impl;

        using zval_t = typename __zval_float32<capability>::impl;
        using composition_t = compose
        <
            printable::impl,
            iteratable::impl,
            convertable::impl,
            float32_io<impl>::template impl,
            float32_math<impl>::template impl,
            float32_numeric<impl>::template impl,
            float32_arithmetic<impl>::template impl,
            float32_comparison<impl>::template impl,
            float32_conditional<impl>::template impl,
            float32_construction<impl>::template impl,

            composable<zval_t>::template type
        >;

        struct impl : public composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<uint64_t capability = 0xFFFF'FFFF'FFFF'FFFF>
    using zfloat32 = typename __zfloat32<capability>::impl;

    ///@}
}}