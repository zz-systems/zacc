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

#include "intrin.hpp"
#include <type_traits>
#include <cmath>

#include "util/type_composition.hpp"
#include "util/memory.hpp"
#include "zval.hpp"
#include "common.hpp"
#include "type_traits.hpp"

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
 * @brief float64 implementation for the scalar branch
 * provides unified access to 1 'double' values
 */

namespace zacc { namespace backend { namespace scalar {

    template<uint64_t capability>
    struct bfloat64;

    template<uint64_t capability>
    struct zfloat64;


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
            using mask_t = typename base_t::mask_t;



            /**
             * @brief construction default branch
             * @relates float64
             * @remark scalar - default
             */
            __impl() : base_t() {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "CONS()");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark scalar - default
             */
            __impl(double value) : base_t(value) {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "CONS(double value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark scalar - default
             */
            template <typename T, typename enable = std::enable_if_t<is_zval<T>::value || is_bval<T>::value>> __impl(const T &value) : base_t(value.value()) {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "CONS(const T &value)");

            }


            /**
             * @brief construction default branch
             * @relates float64
             * @remark scalar - default
             */
            __impl(std::array<typename base_t::scalar_t, base_t::dim> value) : base_t(value[0]) {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "CONS(std::array<typename base_t::scal..)");

            }

        };

        /**
         * @brief construction public interface implementation
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::construction<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::construction<__impl<base_t>, zfloat64<base_t::capability>>;

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
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief io default branch
             * @relates float64
             * @remark scalar - default
             */
            friend void vstore(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vstore");

                target.data()[0] = source.value();
            }


            /**
             * @brief io default branch
             * @relates float64
             * @remark scalar - default
             */
            friend void vstream(typename base_t::extracted_t &target, composed_t source)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vstream");

                target.data()[0] = source.value();
            }


            /**
             * @brief io default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vgather(composed_t &target, raw_ptr<const double> source, zint32<base_t::capability> index)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vgather");

                return source[index.value()];
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::io<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::io<__impl<base_t>, zfloat64<base_t::capability>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name numeric operations
     */
    ///@{

    /**
     * @brief numeric
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_numeric
    {

        /**
         * @brief numeric basic interface implementation
         * @relates float64
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
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::numeric<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::numeric<__impl<base_t>, zfloat64<base_t::capability>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name math operations
     */
    ///@{

    /**
     * @brief math
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_math
    {

        /**
         * @brief math basic interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vabs(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vabs");

                return std::abs(one.value());
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vmin(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vmin");

                return std::min(one.value(), other.value());
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vmax(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vmax");

                return std::max(one.value(), other.value());
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vclamp(composed_t self, composed_t from, composed_t to)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vclamp");

                return vmin(to, vmax(from, self));
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vrcp(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vrcp");

                return (1 / one.value());
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vtrunc(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vtrunc");

                return std::trunc(one.value());
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vfloor(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vfloor");

                return std::floor(one.value());
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vceil(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vceil");

                return std::ceil(one.value());
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vround(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vround");

                return std::round(one.value());
            }


            /**
             * @brief math default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vsqrt(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vsqrt");

                return std::sqrt(one.value());
            }

        };

        /**
         * @brief math public interface implementation
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::math<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::math<__impl<base_t>, zfloat64<base_t::capability>>;

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
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vneg");

                return (-one.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vadd(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vadd");

                return (one.value() + other.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vsub(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vsub");

                return (one.value() - other.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vmul(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vmul");

                return (one.value() * other.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vdiv(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vdiv");

                return (one.value() / other.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vfmadd(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vfmadd");

                return std::fma(multiplicand.value(), multiplier.value(), addendum.value());
            }


            /**
             * @brief arithmetic default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vfmsub(composed_t multiplicand, composed_t multiplier, composed_t addendum)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vfmsub");

                return std::fma(multiplicand.value(), multiplier.value(), -addendum.value());
            }

        };

        /**
         * @brief arithmetic public interface implementation
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::arithmetic<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::arithmetic<__impl<base_t>, zfloat64<base_t::capability>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name bitwise operations
     */
    ///@{

    /**
     * @brief bitwise
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_bitwise
    {

        /**
         * @brief bitwise basic interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vbneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vbneg");

                auto _one = one.value();
                float result;
                reinterpret_cast<uint64_t&>(result) = ~reinterpret_cast<uint64_t&>(_one);
                return result;
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vband(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vband");

                auto _one = one.value();
                auto _other = other.value();
                float result;
                reinterpret_cast<uint64_t&>(result) = reinterpret_cast<uint64_t&>(_one) & reinterpret_cast<uint32_t&>(_other);
                return result;
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vbor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vbor");

                auto _one = one.value();
                auto _other = other.value();
                float result;
                reinterpret_cast<uint64_t&>(result) = reinterpret_cast<uint64_t&>(_one) | reinterpret_cast<uint32_t&>(_other);
                return result;
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vbxor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vbxor");

                auto _one = one.value();
                auto _other = other.value();
                float result;
                reinterpret_cast<uint64_t&>(result) = reinterpret_cast<uint64_t&>(_one) ^ reinterpret_cast<uint32_t&>(_other);
                return result;
            }


            /**
             * @brief bitwise default branch
             * @relates float64
             * @remark scalar - default
             */
            friend bool is_set(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "is_set");

                return one.value() != 0;
            }

        };

        /**
         * @brief bitwise public interface implementation
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::bitwise<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::bitwise<__impl<base_t>, zfloat64<base_t::capability>>;

    };

    ///@}


    // =================================================================================================================
    /**
     * @name logical operations
     */
    ///@{

    /**
     * @brief logical
     * @relates float64
     * @remark scalar
     */
    template<typename composed_t>
    struct float64_logical
    {

        /**
         * @brief logical basic interface implementation
         * @relates float64
         * @remark scalar
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief logical default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vlneg(composed_t one)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vlneg");

                return (!one.value());
            }


            /**
             * @brief logical default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vlor(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vlor");

                return (one.value() || other.value());
            }


            /**
             * @brief logical default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vland(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vland");

                return (one.value() && other.value());
            }

        };

        /**
         * @brief logical public interface implementation
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::logical<__impl<base_t>, bfloat64<base_t::capability>>;

        using impl = traits::logical<__impl<base_t>, zfloat64<base_t::capability>>;

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
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> veq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "veq");

                return (one.value() == other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vneq(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vneq");

                return (one.value() != other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vgt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vgt");

                return (one.value() > other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vlt(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vlt");

                return (one.value() < other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vge(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vge");

                return (one.value() >= other.value());
            }


            /**
             * @brief comparison default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vle(composed_t one, composed_t other)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vle");

                return (one.value() <= other.value());
            }

        };

        /**
         * @brief comparison public interface implementation
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::comparison<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::comparison<__impl<base_t>, zfloat64<base_t::capability>>;

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
            using mask_t = typename base_t::mask_t;

            FORWARD(__impl);


            /**
             * @brief conditional default branch
             * @relates float64
             * @remark scalar - default
             */
            friend zfloat64<base_t::capability> vsel(composed_t condition, composed_t if_value, composed_t else_value)  noexcept {

                ZTRACE_BACKEND("scalar.float64.impl", __LINE__, "zfloat64(double[1])", "default", "vsel");

                return (condition.value() != 0 ? if_value : else_value);
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float64
         * @remark scalar
         */


        template<typename base_t>
        //using impl = traits::conditional<__impl<base_t>, zfloat64<base_t::capability>>;

        using impl = traits::conditional<__impl<base_t>, zfloat64<base_t::capability>>;

    };

    ///@}


    // Type composition ================================================================================================

    /**
     * @name float64 composition
     */
    ///@{

    //namespace composition {

        /**
         * @brief zval parametrization using
         * - 'double' as underlying vector type
         * - 'double' as scalar type
         * - '1' as vector size
         * - '16' as alignment
         * @relates float64
         * @remark scalar
         */
        template<uint64_t capability>
        struct __zval_float64
        {
            using zval_t = zval<double, bool, double, 1, 16, capability>;

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
                float64_math<impl>::template impl,
                float64_numeric<impl>::template impl,
                float64_arithmetic<impl>::template impl,
                float64_bitwise<impl>::template impl,
                float64_logical<impl>::template impl,
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

        template<uint64_t capability>
        struct __bfloat64
        {
            using bval_t = bval<typename __zfloat64<capability>::impl, bool>;
            struct impl : public bval_t
            {
                FORWARD2(impl, bval_t);
            };
        };
    //}

    template<uint64_t capability>
    struct zfloat64 : public /*composition::*/__zfloat64<capability>::impl
    {
        FORWARD2(zfloat64, /*composition::*/__zfloat64<capability>::impl);
    };

    template<uint64_t capability>
    struct bfloat64 : public /*composition::*/__bfloat64<capability>::impl
    {
        FORWARD2(bfloat64, /*composition::*/__bfloat64<capability>::impl);
    };

    static_assert(is_zval<zfloat64<0>>::value, "is_zval for zfloat64 failed.");
    static_assert(is_bval<bfloat64<0>>::value, "is_bval for bfloat64 failed.");

    static_assert(is_floating_point<zfloat64<0>>::value, "is_floating_point for zfloat64 failed.");
    static_assert(!is_integral<zfloat64<0>>::value, "is_integral for zfloat64 failed.");

    static_assert(!is_float<zfloat64<0>>::value, "is_float for zfloat64 failed.");
    static_assert(is_double<zfloat64<0>>::value, "is_double for zfloat64 failed.");

    ///@}
}}}