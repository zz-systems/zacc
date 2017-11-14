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

#include <array>
#include <initializer_list>
#include "traits/arithmetic.hpp"
#include <complex>

namespace zacc { namespace math {

    template<typename T>
    struct zcomplex;

    template<typename zval_t>
    using __cval = zval_base
    <
        std::array<zval_t, 2>, //std::array<typename zval_traits<zval_t>::vector_t, 2>,
        std::array<typename zval_traits<zval_t>::mask_vector_t, 2>,
        zval_t,
        cval_tag,
        2,
        zval_traits<zval_t>::alignment,
        zval_traits<zval_t>::features
    >;

    template<typename T>
    struct __zcomplex_base
    {

        struct impl : __cval<T>
        {
            using base_t = __cval<T>;

            using base_t::size;
            using typename base_t::element_t;
            using typename base_t::vector_t;

            constexpr impl(const vector_t& value)
                    : _value(value)
            {}
            constexpr T real() const
            {
                return _value[0];
            }

            void real(T value) { _value[0] = value; }

            constexpr T imag() const
            {
                return _value[1];
            }
            void imag(T value) { _value[1] = value; }


            T magnitude() { return (real() * real() + imag() * imag()).sqrt(); }
        private:
            //alignas(base_t::alignment) std::array<T, 2> _value;
            alignas(base_t::alignment) vector_t _value;
        };
    };

    /**
     * @brief construction
     */
    template<typename composed_t>
    struct complex_construction
    {
        /**
         * @brief construction basic interface implementation
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using element_t = typename base_t::element_t;
            using vector_t = typename base_t::vector_t;

            //constexpr __impl() : base_t()
            //{}

            //constexpr __impl(const impl& rhs) : _value(rhs._value)
            //{}

    //            template<typename T>
    //            constexpr __impl(const __impl& rhs)
    //                    : base_t(array_cast<element_t>(rhs.value()))
    //            {}

            constexpr __impl(const element_t& re = 0, const element_t& im = 0)
                    : base_t(vector_t{{re, im}})
            {}

            constexpr __impl(const vector_t& value)
                    : base_t(value)
            {}

            //template<typename T = element_t>
            //constexpr __impl(const std::initializer_list<T>& list) : base_t(array_cast<element_t>(list)) {}

        };

        template<typename base_t>
        using impl = traits::construction<__impl<base_t>, zcomplex<typename base_t::element_t>>;
    };

        /**
    * @brief io
    * @relates float32
    * @remark avx
    */
    template<typename composed_t>
    struct complex_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float32
         * @remark avx
         */
        template<typename base_t>
        struct __impl : base_t
        {
            using extracted_t = typename zval_traits<base_t>::extracted_t;

            FORWARD(__impl);

            /**
             * @brief io default branch
             * @relates float32
             * @remark avx - default
             */
            friend void vstore(extracted_t &target, composed_t source)  noexcept {
                //std::copy(source.value().begin(), source.value().end(), target.begin());
                target = source.value();
            }


            /**
             * @brief io default branch
             * @relates float32
             * @remark avx - default
             */
            friend void vstream(extracted_t &target, composed_t source)  noexcept {
                //std::copy(source.value().begin(), source.value().end(), target.begin());
                target = source.value();
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float32
         * @remark avx
         */


        template<typename base_t>
        using impl = traits::io<__impl<base_t>, zcomplex<typename base_t::element_t>>;

    };

    /**
     * @brief provides pretty-print functionality for complex types
     */
    struct complex_printable {
        /**
         * @brief printable trait implementation
         * @tparam base_t base type (e.g previous trait)
         */
        template<typename base_t>
        struct impl : base_t {
            FORWARD(impl);

            /**
             * @brief converts current data to string representation
             * @return string, e.g ( 8, 10i )
             */
            std::string to_string() const {

                auto re = base_t::real().data();
                auto im = base_t::imag().data();

                std::stringstream ss;

                if (base_t::is_vector)
                    ss << "[ ";

                for(auto i = 0; i < base_t::element_t::size(); i++)
                {
                    ss << "( " << re[i] << ", " << im[i] << "i ) ";
                }

                if (base_t::is_vector)
                    ss << "]";

                return ss.str();
            }

            /**
             * @brief prints current value to target stream
             * @param os target stream
             * @param data printable trait
             * @return target stream
             */
            friend std::ostream &operator<<(std::ostream &os, const impl data) {
                os << data.to_string();

                return os;
            }
        };
    };
    /**
     * @brief arithmetic
     */
    template<typename composed_t>
    struct complex_arithmetic
    {
        /**
         * @brief arithmetic basic interface implementation
         */
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            using element_t = typename base_t::element_t;

            /**
             *
             * @param a
             * @param b
             * @return
             */
            friend zcomplex<element_t> vadd(const composed_t &a, const composed_t &b) noexcept{
                zcomplex<element_t> result = {
                           a.real() + b.real(),
                           a.imag() + b.imag()
                       };

                return result;
            }

            /**
             *
             * @param a
             * @param b
             * @return
             */
            friend zcomplex<element_t> vsub(const composed_t &a, const composed_t &b) noexcept {
                zcomplex<element_t> result = {
                           a.real() - b.real(),
                           a.imag() - b.imag()
                       };

                return result;
            }

            /**
             *
             * @param a
             * @param b
             * @return
             */
            friend zcomplex<element_t> vmul(const composed_t &a, const composed_t &b) noexcept {
                return {
                           (a.real() * b.real() - a.imag() * b.imag()),
                           (a.imag() * b.real() + a.real() * b.imag())
                       };
            }

            /**
             *
             * @param a
             * @param b
             * @return
             */
            friend zcomplex<element_t> vdiv(const composed_t &a, const composed_t &b) noexcept {
                return {
                           ((a.real() * b.real() + a.imag() * b.imag()) / (b.real() * b.real() + b.imag() * b.imag())),
                           ((a.imag() * b.real() - a.real() * b.imag()) / (b.real() * b.real() + b.imag() * b.imag()))
                       };
            }

            /**
             *
             * @param multiplicand
             * @param multiplier
             * @param addendum
             * @return
             */
            friend zcomplex<element_t> vfmadd(composed_t multiplicand, composed_t multiplier, composed_t addendum) noexcept{
                return vadd(vmul(multiplicand, multiplier), addendum);
            }

            /**
             *
             * @param multiplicand
             * @param multiplier
             * @param addendum
             * @return
             */
            friend zcomplex<element_t> vfmsub(composed_t multiplicand, composed_t multiplier, composed_t addendum) noexcept{
                return vsub(vmul(multiplicand, multiplier), addendum);
            }
        };

        template<typename base_t>
        using impl = traits::arithmetic<__impl<base_t>, zcomplex<typename base_t::element_t>>;
    };

    // =================================================================================================================
    /**
     * @name conditional operations
     */
    ///@{

    /**
     * @brief conditional
     * @relates float32
     * @remark avx2
     */
    template<typename composed_t>
    struct complex_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float32
         * @remark avx2
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
             * @remark avx2 - default
             */
            friend zcomplex<element_t> vsel(composed_t condition, composed_t if_value, composed_t else_value) noexcept {

                return
                {
                        if_value.real().when(condition.real()).otherwise(else_value.real()),
                        if_value.imag().when(condition.imag()).otherwise(else_value.imag())
                };
            }

        };

        /**
         * @brief conditional public interface implementation
         * @relates float32
         * @remark avx2
         */
        template<typename base_t>
        using impl = traits::conditional<__impl<base_t>, zcomplex<typename base_t::element_t>>;

    };

    ///@}

    template<typename T>
    struct __zcomplex
    {
        struct impl;

        using zcomplex_t = typename __zcomplex_base<T>::impl;
        using composition_t = compose
        <
            complex_printable::impl,
            iteratable::impl,

            complex_io<impl>::template impl,
            complex_arithmetic<impl>::template impl,
            complex_construction<impl>::template impl,
            complex_conditional<impl>::template impl,

            composable<zcomplex_t>::template type
        >;

        struct impl : composition_t
        {
            FORWARD2(impl, composition_t);
        };
    };

    template<typename T>
    struct zcomplex : __zcomplex<T>::impl
    {
        FORWARD2(zcomplex, __zcomplex<T>::impl);
    };


    constexpr zcomplex<zdouble> operator""i(unsigned long long d)
    {
        return { 0.0, d };
    }
    constexpr zcomplex<zdouble> operator""i(long double d)
    {
        return { 0.0, d };
    }

    constexpr zcomplex<zfloat> operator""if(unsigned long long d)
    {
        return { 0.0, d };
    }
    constexpr zcomplex<zfloat> operator""if(long double d)
    {
        return { 0.0, d };
    }
}}