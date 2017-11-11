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

#include <type_traits>
#include <cmath>

#include "backend/intrin.hpp"
#include "backend/zval.hpp"

#include "util/type/type_composition.hpp"
#include "util/type/type_traits.hpp"

#include "util/memory.hpp"
#include "util/macros.hpp"

#include "traits/common.hpp"
#include "traits/construction.hpp"
#include "traits/io.hpp"
#include "traits/numeric.hpp"
#include "traits/math.hpp"
#include "traits/arithmetic.hpp"
#include "traits/bitwise.hpp"
#include "traits/logical.hpp"
#include "traits/comparison.hpp"
#include "traits/conditional.hpp"

/**
 * @brief float32 implementation for the scalar branch
 * provides unified access to 1 'float' values
 */

namespace zacc { namespace backend { namespace scalar {

    template<uint64_t features>
    struct bfloat32;

    template<uint64_t features>
    struct zfloat32;


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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;



            /**
             * @brief construction default branch
             * @relates float32
             * @remark scalar - default
             */
            constexpr __impl() : base_t() {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark scalar - default
             */
            constexpr __impl(float value) : base_t(value) {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "CONS(float value)");

            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark scalar - default
             */
            template <typename T, typename enable = std::enable_if_t<is_zval<T>::value || is_bval<T>::value>> constexpr __impl(const T &value) : base_t(value.value()) {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "CONS(const T &value)");

            }


            /**
             * @brief construction default branch
             * @relates float32
             * @remark scalar - default
             */
            constexpr __impl(std::array<typename base_t::element_t, base_t::size()> value) : base_t(value[0]) {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "CONS(std::array<typename base_t::elem..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::construction<__impl<base_t>, zfloat32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates float32
             * @remark scalar - default
             */
            template<typename OutputIt> friend void vstore(OutputIt result, composed_t input)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vstore");

                result[0] = input.value();
            }


            /**
             * @brief io default branch
             * @relates float32
             * @remark scalar - default
             */
            template<typename OutputIt> friend void vstream(OutputIt result, composed_t input)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vstream");

                result[0] = input.value();
            }


            /**
             * @brief io default branch
             * @relates float32
             * @remark scalar - default
             */
            template<typename RandomIt> friend zfloat32<base_t::features> vgather(RandomIt input, const zint32<base_t::features> &index, composed_t)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vgather");

                return input[index.value()];
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::io<__impl<base_t>, zfloat32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);

        };

        /**
         * @brief numeric public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::numeric<__impl<base_t>, zfloat32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vabs(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vabs");

                return std::abs(one.value());
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vmin(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vmin");

                return std::min(one.value(), other.value());
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vmax(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vmax");

                return std::max(one.value(), other.value());
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vclamp(composed_t self, composed_t from, composed_t to)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vclamp");

                return vmin(to, vmax(from, self));
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vrcp(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vrcp");

                return (1 / one.value());
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vtrunc(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vtrunc");

                return std::trunc(one.value());
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vfloor(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vfloor");

                return std::floor(one.value());
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vceil(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vceil");

                return std::ceil(one.value());
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vround(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vround");

                return std::round(one.value());
            }


            /**
             * @brief math default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vsqrt(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vsqrt");

                return std::sqrt(one.value());
            }

        };

        /**
         * @brief math public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::math<__impl<base_t>, zfloat32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vneg");

                return (-one.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vadd");

                return (one.value() + other.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vsub");

                return (one.value() - other.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vmul");

                return (one.value() * other.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vdiv(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vdiv");

                return (one.value() / other.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vfmadd(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vfmadd");

                return std::fma(multiplicand.value(), multiplier.value(), addendum.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vfmsub(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vfmsub");

                return std::fma(multiplicand.value(), multiplier.value(), -addendum.value());
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::arithmetic<__impl<base_t>, zfloat32<base_t::features>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name bitwise operations
     */
    ///@{

    /**
     * @brief bitwise
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vbneg");

                auto _one = one.value();
                float result;
                bitsof(result) = ~bitsof(_one);
                return result;
            }


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vband");

                auto _one = one.value();
                auto _other = other.value();
                float result;
                bitsof(result) = bitsof(_one) & bitsof(_other);
                return result;
            }


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vbor");

                auto _one = one.value();
                auto _other = other.value();
                float result;
                bitsof(result) = bitsof(_one) | bitsof(_other);
                return result;
            }


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vbxor");

                auto _one = one.value();
                auto _other = other.value();
                float result;
                bitsof(result) = bitsof(_one) ^ bitsof(_other);
                return result;
            }


            /**
             * @brief bitwise default branch
             * @relates float32
             * @remark scalar - default
             */
            friend bool is_set(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "is_set");

                return one.value() != 0;
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::bitwise<__impl<base_t>, zfloat32<base_t::features>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name logical operations
     */
    ///@{

    /**
     * @brief logical
     * @relates float32
     * @remark scalar
     */
    template<typename composed_t>
    struct float32_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vlneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vlneg");

                return !one.value();
            }


            /**
             * @brief logical default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vlor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vlor");

                return (one.value() || other.value());
            }


            /**
             * @brief logical default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vland(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vland");

                return (one.value() && other.value());
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::logical<__impl<base_t>, zfloat32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "veq");

                return (one.value() == other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vneq");

                return (one.value() != other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vgt");

                return (one.value() > other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vlt");

                return (one.value() < other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vge");

                return (one.value() >= other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vle");

                return (one.value() <= other.value());
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::comparison<__impl<base_t>, zfloat32<base_t::features>>;

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
            using vector_t      = typename zval_traits<base_t>::vector_t;
            using element_t     = typename zval_traits<base_t>::element_t;
            using mask_vector_t = typename zval_traits<base_t>::mask_vector_t;
            using extracted_t   = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates float32
             * @remark scalar - default
             */
            friend zfloat32<base_t::features> vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("scalar.float32.impl", __LINE__, "zfloat32(float[1])", "default", "vsel");

                return (condition.value() != 0 ? if_value : else_value);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float32
         * @remark scalar
         */
        template<typename base_t>
        using impl = traits::conditional<__impl<base_t>, zfloat32<base_t::features>>;

    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float32 composition
     */
    ///@{

    //namespace composition {

        /**
         * @brief zval parametrization using
         * - 'float' as underlying vector type
         * - 'float' as scalar type
         * - '1' as vector size
         * - '16' as alignment
         * @relates float32
         * @remark scalar
         */
        template<uint64_t features>
        struct __zval_float32
        {
            using zval_t = zval<float, bool, float, zval_tag, 1, 16, features>;

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
        template<uint64_t features>
        struct __zfloat32
        {
            struct impl;

            using zval_t = typename __zval_float32<features>::impl;
            using composition_t = compose
            <
                printable::impl,
                iteratable::impl,
                convertable::impl,
                float32_io<impl>::template impl,
                float32_math<impl>::template impl,
                float32_numeric<impl>::template impl,
                float32_arithmetic<impl>::template impl,
                float32_bitwise<impl>::template impl,
                float32_logical<impl>::template impl,
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

        template<uint64_t features>
        struct __bfloat32
        {
            using bval_t = bval<typename __zfloat32<features>::impl, bool>;
            struct impl : public bval_t
            {
                FORWARD2(impl, bval_t);
            };
        };
    //}

    template<uint64_t features>
    struct zfloat32 : public /*composition::*/__zfloat32<features>::impl
    {
        FORWARD2(zfloat32, /*composition::*/__zfloat32<features>::impl);
    };

    template<uint64_t features>
    struct bfloat32 : public /*composition::*/__bfloat32<features>::impl
    {
        FORWARD2(bfloat32, /*composition::*/__bfloat32<features>::impl);
    };

    static_assert(is_zval<zfloat32<0>>::value, "is_zval for zfloat32 failed.");
    static_assert(is_bval<bfloat32<0>>::value, "is_bval for bfloat32 failed.");

    static_assert(is_floating_point<zfloat32<0>>::value, "is_floating_point for zfloat32 failed.");
    static_assert(!is_integral<zfloat32<0>>::value, "is_integral for zfloat32 failed.");

    static_assert(is_float<zfloat32<0>>::value, "is_float for zfloat32 failed.");
    static_assert(!is_double<zfloat32<0>>::value, "is_double for zfloat32 failed.");

    ///@}
}}}