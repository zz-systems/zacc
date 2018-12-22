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


#pragma once

#include <array>
#include <initializer_list>
#include "traits/arithmetic.hpp"
#include "math/matrix.hpp"
#include <complex>

namespace zacc { namespace math {

    template<typename T>
    struct zcomplex;

    template<typename T>
    struct bcomplex;

    template<typename zval_t>
    using __cval = zval_base
    <
        vec2<zval_t>,
        vec2<typename ztraits<zval_t>::mask_vector_t>,
        zval_t,
        cval_tag,
        2,
        ztraits<zval_t>::alignment,
        ztraits<zval_t>::features
    >;

    /**
         * @brief zval parametrization using
         * - '__m128i' as underlying vector type
         * - 'int32_t' as scalar type
         * - '4' as vector size
         * - '16' as alignment
         * @relates int32
         * @remark sse
         */
    template<typename Zval>
    using czval_base = zval<vec2<Zval>, vec2<typename ztraits<Zval>::mask_vector_t>, Zval, cval_tag, 2, 16, Features>;

    /**
     * @brief bval parametrization using
     * - '__m128i' as underlying vector type
     * - 'int32_t' as scalar type
     * - '4' as vector size
     * - '16' as alignment
     * @relates int32
     * @remark sse
    */
    template<typename Bval>
    using cbval_base = bval<__m128i, __m128i, int32_t, 4, 16, Features>;

    template<typename Element>
    struct __zcomplex_base
    {

        struct impl : __cval<Element>
        {
            using Base = __cval<Element>;

            using Base::size;

            using zval_t = zcomplex<Element>;
            using bval_t = bcomplex<Element>;

            using element_t = typename Base::element_t;
            using vector_t = typename Base::vector_t;

            constexpr impl()
            {}

            template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, vec2<Element>>::value>>
            constexpr impl(const T& other)
                    : _value (other)
            {}

            template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, vec2<Element>>::value>>
            constexpr impl(T&& value)
                    : _value(std::move(value))
            {}

            template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Element>::value>>
            constexpr impl(const vec2<T>& value)
                    : _value(value)
            {}

            template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Element>::value>>
            constexpr impl(vec2<T>&& value)
                    : _value(std::move(value))
            {}


            constexpr impl(const impl& other)
                    : _value (other._value)
            {}

            constexpr impl(impl&& other) noexcept
                : _value(std::move(other._value))
            {}

            template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Element>::value>>
            constexpr impl& operator=(const T& other)
            {
                _value = other;
                return *this;
            }

            template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Element>::value>>
            constexpr impl& operator=(T&& other) noexcept
            {
                _value = std::move(other);
                return *this;
            }

            template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Element>::value>>
            constexpr impl& operator=(const vec2<T>& other)
            {
                _value = other;
                return *this;
            }

            template<typename T, typename enable = std::enable_if_t<std::is_convertible<T, Element>::value>>
            constexpr impl& operator=(vec2<T>&& other) noexcept
            {
                _value = std::move(other);
                return *this;
            }

            constexpr impl& operator=(const impl& other)
            {
                _value = other._value;
                return *this;
            }

            constexpr impl& operator=(impl&& other) noexcept
            {
                _value = std::move(other._value);
                return *this;
            }


            constexpr const Element& real() const
            {
                return _value.x;
            }

            constexpr Element& real()
            {
                return _value.x;
            }

            constexpr const Element& imag() const
            {
                return _value.y;
            }

            constexpr Element& imag()
            {
                return _value.y;
            }

            /**
             * @brief cast to underlying vector type
             * @return raw value
             */
            constexpr vector_t value() const {
                return _value;
            }

            constexpr Element magnitude() const
            {
                return _value.magnitude();
            }

            constexpr Element sqr_magnitude() const
            {
                return _value.sqr_magnitude();
            }

        private:
            alignas(Base::alignment) vector_t _value;
        };
    };

    /**
     * @brief construction
     */
    template<typename Composed>
    struct complex_construction
    {
        /**
         * @brief construction basic interface implementation
         */
        template<typename Base>
        struct __impl : Base
        {

            using zval_t = typename Base::zval_t;
            using bval_t = typename Base::bval_t;

            using element_t = typename Base::element_t;
            using vector_t = typename Base::vector_t;

            //FORWARD(__impl);

            //constexpr __impl() : Base()
            //{}

            //constexpr __impl(const impl& rhs) : _value(rhs._value)
            //{}

    //            template<typename T>
    //            constexpr __impl(const __impl& rhs)
    //                    : Base(array_cast<element_t>(rhs.value()))
    //            {}

//            constexpr __impl(const element_t& re, const element_t& im = 0)
//                    : Base(vector_t{{re, im}})
//            {}

            constexpr __impl()
                    : Base()
            {}


//            template<typename U, typename enable = std::enable_if_t<std::is_convertible<U, element_t>::value>>
//            constexpr __impl(const U& re)
//                    : Base(static_cast<vec2<element_t>>(re))
//            {}
//
//            template<typename U, typename enable = std::enable_if_t<std::is_convertible<U, element_t>::value>>
//            constexpr __impl(const U& re, const U& imag)
//                    : Base(vec2<element_t>(re, imag))
//            {}

            //template<typename U, typename enable = std::enable_if_t<std::is_convertible<U, element_t>::value>>
            constexpr __impl(const element_t& re)
                    : __impl(vec2<element_t>(re, 0))
            {}

            //template<typename U, typename enable = std::enable_if_t<std::is_convertible<U, element_t>::value>>
            constexpr __impl(const element_t& re, const element_t& imag)
                    : __impl(vec2<element_t>(re, imag))
            {}

            template<typename U, typename enable = std::enable_if_t<std::is_same<U, vec2<element_t>>::value>>// || std::is_same<U, zcomplex<element_t>>::value>>
            constexpr __impl(const U& other)
                    : Base(other)
            {}

            template<typename U, typename enable = std::enable_if_t<std::is_same<U, vec2<element_t>>::value>>// || std::is_same<U, zcomplex<element_t>>::value>>
            constexpr __impl(U&& other)
                    : Base(std::forward<U>(other))
            {}

//            template<template<class> class T, typename U, typename enable = std::enable_if_t<std::is_convertible<U, typename ztraits<element_t>::element_t>::value &&  std::is_same<T<U>, vec2<U>>::value>>
//            constexpr __impl(const T<U>& other)
//                    : Base()//vec2<element_t>(other.x, other.y))
//            {}
//
//            template<template<class> class T, typename U, typename enable = std::enable_if_t<std::is_convertible<U, typename ztraits<element_t>::element_t>::value &&  std::is_same<T<U>, vec2<U>>::value>>
//            constexpr __impl(T<U>&& other)
//                    : Base()//vec2<element_t>(std::move(other.x), std::move(other.y)))
//            {}

//            template<typename U, typename enable = std::enable_if_t<std::is_convertible<U, vec2<typename ztraits<element_t>::element_t>>::value>>
//            constexpr __impl(const U& other)
//                    : Base(vec2<element_t>(other.x, other.y))
//            {}

//            template<typename U, typename enable = std::enable_if_t<std::is_convertible<U, vec2<typename ztraits<element_t>::element_t>>::value>>
//            constexpr __impl(U&& other)
//                    : Base(std::forward<U>(other))
//            {}


            /*constexpr __impl(const vector_t& value)
                    : Base(value)
            {}*/
/*
            constexpr __impl(const __impl& value)
                    : Base(vector_t{{value.real(), value.imag()}})
            {}
*/
            //template<typename T = element_t>
            //constexpr __impl(const std::initializer_list<T>& list) : Base(array_cast<element_t>(list)) {}

        };

        template<typename Base>
        using impl = traits::constructable<__impl<Base>, zcomplex<typename Base::element_t>>;
    };

        /**
    * @brief io
    * @relates float32
    * @remark avx
    */
    template<typename Composed>
    struct complex_io
    {

        /**
         * @brief io basic interface implementation
         * @relates float32
         * @remark avx
         */
        template<typename Base>
        struct __impl : Base
        {
            using extracted_t = typename ztraits<Base>::extracted_t;
            using zval_t = typename Base::zval_t;
            using bval_t = typename Base::bval_t;

            FORWARD(__impl);

            /**
             * @brief io default arch
             * @relates float32
             * @remark avx - default
             */
            friend void vstore(extracted_t &target, Composed source)  noexcept {
                //std::copy(source.value().begin(), source.value().end(), target.begin());
                target = source.value();
            }


            /**
             * @brief io default arch
             * @relates float32
             * @remark avx - default
             */
            friend void vstream(extracted_t &target, Composed source)  noexcept {
                //std::copy(source.value().begin(), source.value().end(), target.begin());
                target = source.value();
            }

        };

        /**
         * @brief io public interface implementation
         * @relates float32
         * @remark avx
         */


        template<typename Base>
        using impl = traits::io<__impl<Base>, zcomplex<typename Base::element_t>>;

    };

    /**
     * @brief provides pretty-print functionality for complex types
     */
    struct complex_printable {
        /**
         * @brief printable trait implementation
         * @tparam Base base type (e.g previous trait)
         */
        template<typename Base>
        struct impl : Base {

            using zval_t = typename Base::zval_t;
            using bval_t = typename Base::bval_t;

            FORWARD(impl);

            /**
             * @brief converts current data to string representation
             * @return string, e.g ( 8, 10i )
             */
            std::string to_string() const {

                auto re = Base::real().data();
                auto im = Base::imag().data();

                std::stringstream ss;

                if (Base::is_vector)
                    ss << "[ ";

                for(size_t i = 0; i < Base::element_t::size(); i++)
                {
                    ss << "( " << re[i] << ", " << im[i] << "i ) ";
                }

                if (Base::is_vector)
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
    template<typename Composed>
    struct complex_arithmetic
    {
        /**
         * @brief arithmetic basic interface implementation
         */
        template<typename Base>
        struct __impl : Base
        {
            FORWARD(__impl);

            using zval_t = typename Base::zval_t;
            using bval_t = typename Base::bval_t;

            using element_t = typename Base::element_t;

            /**
             *
             * @param a
             * @param b
             * @return
             */
            friend zcomplex<element_t> vadd(const zcomplex<element_t> &a, const zcomplex<element_t> &b) noexcept {
                return a.value() + b.value();
            }

            /**
             *
             * @param a
             * @param b
             * @return
             */
            friend zcomplex<element_t> vsub(const zcomplex<element_t> &a, const zcomplex<element_t> &b) noexcept {
                return a.value() - b.value();
            }

          /**
            *
            * @param a
            * @param b
            * @return
            */

            friend zcomplex<element_t> vmul(const zcomplex<element_t> &a, const zcomplex<element_t> &b) noexcept {
                return {
                        vfmsub(a.real(), b.real(), a.imag() * b.imag()),
                        vfmadd(a.imag(), b.real(), a.real() * b.imag())
                };
            }

            /**
             *
             * @param a
             * @param b
             * @return
             */

            friend zcomplex<element_t> vdiv(const zcomplex<element_t> &a, const zcomplex<element_t> &b) noexcept {

                return {
                        vfmadd(a.real(), b.real(), a.imag() * b.imag()) / vfmadd(b.real(), b.real(), b.imag() * b.imag()),
                        vfmsub(a.imag(), b.real(), a.real() * b.imag()) / vfmadd(b.real(), b.real(), b.imag() * b.imag())
                };
            }

//            /**
//             *
//             * @param a
//             * @param b
//             * @return
//             */
//
//            friend zcomplex<element_t> vmul(const zcomplex<element_t> &a, const zcomplex<element_t> &b) noexcept {
//                return {
//                        (a.real() * b.real() - a.imag() * b.imag()),
//                        (a.imag() * b.real() + a.real() * b.imag())
//                };
//            }
//
//            /**
//             *
//             * @param a
//             * @param b
//             * @return
//             */
//            friend zcomplex<element_t> vdiv(const zcomplex<element_t> &a, const zcomplex<element_t> &b) noexcept {
//                return {
//                        ((a.real() * b.real() + a.imag() * b.imag()) / (b.real() * b.real() + b.imag() * b.imag())),
//                        ((a.imag() * b.real() - a.real() * b.imag()) / (b.real() * b.real() + b.imag() * b.imag()))
//                };
//            }

            /**
             *
             * @param multiplicand
             * @param multiplier
             * @param addendum
             * @return
             */
            friend zcomplex<element_t> vfmadd(zcomplex<element_t> multiplicand, zcomplex<element_t> multiplier, zcomplex<element_t> addendum) noexcept{
                return vadd(vmul(multiplicand, multiplier), addendum);
            }

            /**
             *
             * @param multiplicand
             * @param multiplier
             * @param addendum
             * @return
             */
            friend zcomplex<element_t> vfmsub(zcomplex<element_t> multiplicand, zcomplex<element_t> multiplier, zcomplex<element_t> addendum) noexcept{
                return vsub(vmul(multiplicand, multiplier), addendum);
            }
        };

        template<typename Base>
        using impl = traits::arithmetic<__impl<Base>, zcomplex<typename Base::element_t>>;
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
    template<typename Composed>
    struct complex_conditional
    {

        /**
         * @brief conditional basic interface implementation
         * @relates float32
         * @remark avx2
         */
        template<typename Base>
        struct __impl : Base
        {
            using zval_t = typename Base::zval_t;
            using bval_t = typename Base::bval_t;

            using vector_t      = typename ztraits<Base>::vector_t;
            using element_t     = typename ztraits<Base>::element_t;
            using mask_vector_t = typename ztraits<Base>::mask_vector_t;
            using extracted_t   = typename ztraits<Base>::extracted_t;

            FORWARD(__impl);


            /**
             * @brief conditional default arch
             * @relates float32
             * @remark avx2 - default
             */
            friend Composed vsel(bval_t condition, Composed if_value, Composed else_value) noexcept {

                return
                {
                        if_value.real().when(condition.real()).otherwise(else_value.real()),
                        if_value.imag().when(condition.imag()).otherwise(else_value.imag())
                };
            }

//            /**
//             * @brief conditional default arch
//             * @relates float32
//             * @remark avx2 - default
//             */
//            friend bval_t vsel(bval_t condition, Composed if_value, Composed else_value) noexcept {
//
//                return
//                        {
//                                if_value.real().when(condition.real()).otherwise(else_value.real()),
//                                if_value.imag().when(condition.imag()).otherwise(else_value.imag())
//                        };
//            }
        };

        /**
         * @brief conditional public interface implementation
         * @relates float32
         * @remark avx2
         */
        template<typename Base>
        using impl = traits::conditional<__impl<Base>, zcomplex<typename Base::element_t>>;

    };

    ///@}

    template<typename T>
    struct __zcomplex
    {
        struct impl;

        using zval_base_t = typename __zcomplex_base<T>::impl;
        using bval_base_t = typename __zcomplex_base<typename T::bval_t>::impl;

        using composition_t = compose
        <
            complex_printable::impl,

            complex_io<impl>::template impl,
            complex_arithmetic<impl>::template impl,
            complex_conditional<impl>::template impl,
            complex_construction<impl>::template impl,

            composable<zval_base_t>::template type
        >;

        struct impl : public composition_t
        {
            using zval_t = zcomplex<T>;
            using bval_t = bcomplex<T>;

            FORWARD2(impl, composition_t);
        };
    };

    template<typename T>
    struct zcomplex : public __zcomplex<T>::impl
    {
        using zval_t = zcomplex<T>;
        using bval_t = bcomplex<T>;

        FORWARD2(zcomplex, __zcomplex<T>::impl);


        static_assert(!is_zval<zcomplex<T>>::value, "is_zval for zcomplex<int> failed.");
        static_assert(!is_bval<zcomplex<T>>::value, "is_bval for zcomplex<int> failed.");
        static_assert(is_cval<zcomplex<T>>::value,  "is_cval for zcomplex<int> failed.");
    };

    template<typename T>
    struct __bcomplex
    {
        struct impl;

        using zval_base_t = typename __zcomplex_base<T>::impl;
        using bval_base_t = typename __zcomplex_base<typename T::bval_t>::impl;

        using composition_t = compose
        <
            complex_printable::impl,

            complex_conditional<impl>::template impl,
            complex_construction<impl>::template impl,

            composable<bval_base_t>::template type
        >;

        struct impl : public composition_t
        {
            using zval_t = zcomplex<T>;
            using bval_t = bcomplex<T>;

            FORWARD2(impl, composition_t);
        };
    };

    template<typename T>
    struct bcomplex : public __bcomplex<T>::impl
    {
        using zval_t = zcomplex<T>;
        using bval_t = bcomplex<T>;


        constexpr bcomplex(const zcomplex<typename ztraits<T>::zval_t>& other)
                : __bcomplex<T>::impl (make_bval<T>(other.real(), last_operation::undefined),
                                       make_bval<T>(other.imag(), last_operation::undefined))
        {
        }

        constexpr bcomplex(const zcomplex<typename ztraits<T>::zval_t>& other, last_operation last_op)
                : __bcomplex<T>::impl (make_bval<T>(other.real(), last_op),
                                       make_bval<T>(other.imag(), last_op))
        {
        }

        constexpr bcomplex(zcomplex<typename ztraits<T>::zval_t>&& other)
                : __bcomplex<T>::impl (make_bval<T>(other.real(), last_operation::undefined),
                                       make_bval<T>(other.imag(), last_operation::undefined))
        {
        }

        constexpr bcomplex(zcomplex<typename ztraits<T>::zval_t>&& other, last_operation last_op)
                : __bcomplex<T>::impl (make_bval<T>(other.real(), last_op),
                                       make_bval<T>(other.imag(), last_op))
        {
        }

        constexpr bcomplex(const bcomplex& other)
                : __bcomplex<T>::impl (make_bval<T>(other.real(), other.real().last_op()),
                                       make_bval<T>(other.imag(), other.imag().last_op()))
        {
        }

        constexpr bcomplex(bcomplex&& other)
                : __bcomplex<T>::impl (make_bval<T>(other.real(), other.real().last_op()),
                                       make_bval<T>(other.imag(), other.imag().last_op()))
        {
        }

        constexpr bcomplex(const bcomplex& other, last_operation last_op)
                : __bcomplex<T>::impl (make_bval<T>(other.real(), last_op),
                                       make_bval<T>(other.imag(), last_op))
        {
        }

        constexpr bcomplex(bcomplex&& other, last_operation last_op)
                : __bcomplex<T>::impl (make_bval<T>(other.real(), last_op),
                                       make_bval<T>(other.imag(), last_op))
        {
        }


        template<typename U, typename enable = std::enable_if_t<is_zval<U>::value || is_bval<U>::value>>
        constexpr bcomplex(const U &one)
                : __bcomplex<T>::impl (make_bval<T>(one),
                                       make_bval<T>(one))
        {
        }

        template<typename U, typename enable = std::enable_if_t<is_zval<U>::value || is_bval<U>::value>>
        constexpr bcomplex(U &&one)
                : __bcomplex<T>::impl (make_bval<T>(one),
                                       make_bval<T>(one))
        {
        }

        constexpr bcomplex(const T& one, const T& other)
                : __bcomplex<T>::impl (make_bval<T>(one),
                                       make_bval<T>(other))
        {
        }

        constexpr bcomplex(T&& one, T&& other)
                : __bcomplex<T>::impl (make_bval<T>(one),
                                       make_bval<T>(other))
        {
        }

        constexpr last_operation last_op() const { return last_operation::undefined; }
        bcomplex(bool one) = delete;


        static_assert(!is_zval<bcomplex<T>>::value,     "is_zval for bcomplex<int> failed.");
        static_assert(is_bval<bcomplex<T>>::value,      "is_bval for bcomplex<int> failed.");
        static_assert(is_cval<bcomplex<T>>::value,      "is_cval for bcomplex<int> failed.");

    };
    constexpr zcomplex<zdouble> operator""_i(unsigned long long d)
    {
        return { 0.0, d };
    }
    constexpr zcomplex<zdouble> operator""_i(long double d)
    {
        return { 0.0, d };
    }

    constexpr zcomplex<zfloat> operator""_if(unsigned long long d)
    {
        return { 0.0, d };
    }
    constexpr zcomplex<zfloat> operator""_if(long double d)
    {
        return { 0.0, d };
    }

}}