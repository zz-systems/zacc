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
#include "util/type/type_traits.hpp"
#include "traits/arithmetic.hpp"
#include "math/matrix.hpp"
#include <complex>

namespace zacc { namespace math
{
    template<typename T>
    struct zcomplex;

    template<typename T>
    using izcomplex = ztype<cval_tag, vec2<T>, T, 2, alignment_v<T>, feature_mask_v<T>>;
}}

namespace zacc
{
    /**
     * @brief ztraits type trait specialization for int32 [avx2 branch]
     * @tparam T
     */
    template<typename T>
    struct ztraits<T, std::enable_if_t<std::is_base_of<math::izcomplex<typename std::decay_t<T>::element_type>, std::decay_t<T>>::value>>
    {
        /// vector size (1 - scalar, 4, 8, 16, ...)
        static constexpr size_t size = 2;

        /// capabilities
        static constexpr uint64_t feature_mask = feature_mask_v<typename std::decay_t<T>::element_type>;

        /// memory alignment
        static constexpr size_t alignment = alignment_v<typename std::decay_t<T>::element_type>;

        /// scalar type? vector type?
        static constexpr bool is_vector = true;

        /// vector type, like __m128i for sse 4x integer vector
        using vector_type = math::vec2<typename std::decay_t<T>::element_type>;

        /// scalar type, like int for sse 4x integer vector
        using element_type = typename std::decay_t<T>::element_type;

        /// extracted std::array of (dim) scalar values
        using extracted_type = std::array<element_type, size>;

        using zval_type = math::zcomplex<typename std::decay_t<T>::element_type>;
        using bval_type = bval_t<typename std::decay_t<T>::element_type>;

        using tag = cval_tag;
    };
}

namespace zacc { namespace math
{
    namespace modules {

        /**
          * @brief printable mixin implementation
          * @relates complex
          */
        template<typename Interface, typename Composed, typename Boolean>
        struct printable
        {
            constexpr auto self()
            {
                return static_cast<Composed*>(this);
            }

            /**
             * @brief converts current data to string representation
             * @return string, e.g [4, 5, 6, 7] for a 4x int vector
             */
            std::string to_string() const {
                std::stringstream ss;

                auto re = self()->real().data();
                auto im = self()->imag().data();

                if (is_vector_v<Interface>)
                    ss << "[ ";

                for(size_t i = 0; i < size_v<Interface>; i++)
                {
                    ss << "( " << re[i] << ", " << im[i] << "i ) ";
                }

                if (is_vector_v<Interface>)
                    ss << "]";

                return ss.str();
            }

            /**
             * @brief prints current value to target stream
             * @param os target stream
             * @param data printable trait
             * @return target stream
             */
            friend std::ostream &operator<<(std::ostream &os, Composed data) {
                os << data.to_string();

                return os;
            }
        };

        // =============================================================================================================

        /**
         * @brief io mixin implementation
         * @relates complex
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct io : traits::io<Interface, Composed, Boolean>
        {
            /**
             * @brief vstore [default branch]
             * @relates complex
             */
            friend void vstore(extracted_t<Interface>& result, Composed input)
            {
                result = input.value();
            }

            /**
             * @brief vstream [default branch]
             * @relates complex
             */
            friend void vstream(extracted_t<Interface>& result, Composed input)
            {
                result = input.value();
            }
        };

        // =============================================================================================================

        /**
         * @brief arithmetic mixin implementation
         * @relates complex
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct arithmetic : traits::arithmetic<Interface, Composed, Boolean>
        {
            /**
             * @brief vneg (conjugate)
             * @relates complex
             */
            friend Composed vneg(Composed one)
            {
                return { one.real(), -one.imag() };
            }

            /**
            * @brief vadd
            * @relates complex
            */
            friend Composed vadd(Composed one, Composed other)
            {
                return one.value() + other.value();
            }

            /**
            * @brief vsub
            * @relates complex
            */
            friend Composed vsub(Composed one, Composed other)
            {
                return one.value() - other.value();
            }

            /**
            * @brief vmul
            * @relates complex
            */
            friend Composed vmul(Composed one, Composed other)
            {
                return {
                        vfmsub(one.real(), other.real(), one.imag() * other.imag()),
                        vfmadd(one.imag(), other.real(), one.real() * other.imag())
                };
            }

            /**
            * @brief vdiv
            * @relates complex
            */
            friend Composed vdiv(Composed one, Composed other)
            {
                return {
                        vfmadd(one.real(), other.real(), one.imag() * other.imag()) / vfmadd(other.real(), other.real(), other.imag() * other.imag()),
                        vfmsub(one.imag(), other.real(), one.real() * other.imag()) / vfmadd(other.real(), other.real(), other.imag() * other.imag())
                };
            }

            /**
            * @brief vdiv
            * @relates complex
            */
            friend Composed vfmadd(Composed multiplicand, Composed multiplier, Composed addendum) noexcept {
                return vadd(vmul(multiplicand, multiplier), addendum);
            }

            /**
            * @brief vdiv
            * @relates complex
            */
            friend Composed vfmsub(Composed multiplicand, Composed multiplier, Composed addendum) noexcept {
                return vsub(vmul(multiplicand, multiplier), addendum);
            }
        };

        // =============================================================================================================

        /**
         * @brief equatable mixin implementation
         * @relates complex
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct equatable : traits::equatable<Interface, Composed, Boolean>
        {
            /**
             * @brief equatable [default branch]
             * @relates int32
             */
            friend Boolean veq(Composed one, Composed other)
            {
                return one.real() == other.real() && one.imag() == other.imag();
            }

            /**
             * @brief equatable [default branch]
             * @relates int32
             */
            friend Boolean vneq(Composed one, Composed other)
            {
                return !(one == other);
            }
        };

        // =============================================================================================================

        /**
         * @brief conditional mixin implementation
         * @relates complex
         */
        template<typename Interface, typename Composed, typename Boolean>
        struct conditional : traits::conditional<Interface, Composed, Boolean>
        {
            /**
             * @brief vsel
             * @relates complex
             */
            friend Composed vsel(param_t<Boolean> condition, Composed if_value, Composed else_value)
            {
                return {
                    if_value.real().when(condition).otherwise(else_value.real()),
                    if_value.imag().when(condition).otherwise(else_value.imag())
                };
            }
        };
    } // end int32_modules

    // =================================================================================================================

    /// public zcomplex implementation [avx2 branch]
    template<typename T>
     struct zcomplex : public zval<izcomplex<T>>,

            // generic traits
                      modules::printable<izcomplex<T>, zcomplex<T>, bval_t<T>>,

            // zcomplex traits
                      modules::io<izcomplex<T>, zcomplex<T>, bval_t<T>>,
                      modules::arithmetic<izcomplex<T>, zcomplex<T>, bval_t<T>>,
                      modules::equatable<izcomplex<T>, zcomplex<T>, bval_t<T>>,
                      modules::conditional<izcomplex<T>, zcomplex<T>, bval_t<T>>
    {
        USING_ZTYPE(izcomplex<T>);

        using zval<izcomplex<T>>::zval;

         // =============================================================================================================

        template<typename U>
        constexpr zcomplex(const math::vec2<U>& other) noexcept
                : zval<izcomplex<T>>(other)
        {}

        template<typename U, typename std::enable_if<std::is_convertible<U, element_type>::value, void**>::type = nullptr>
        constexpr zcomplex(const U& re) noexcept
            : zval<izcomplex<T>>(vector_type(re, 0))
        {}

        template<typename U, typename std::enable_if<std::is_convertible<U, element_type>::value, void**>::type = nullptr>
        constexpr zcomplex(const U& re, const U& im) noexcept
            : zval<izcomplex<T>>(vector_type(re, im))
        {}

        // =============================================================================================================

        constexpr const element_type& real() const
        {
            return this->value().x();
        }

        constexpr element_type& real()
        {
            return this->value().x();
        }

        constexpr const element_type& imag() const
        {
            return this->value().y();
        }

        constexpr element_type& imag()
        {
            return this->value().y();
        }

        constexpr element_type magnitude() const
        {
            return this->value().magnitude();
        }

        constexpr element_type sqr_magnitude() const
        {
            return this->value().sqr_magnitude();
        }
    };


//    constexpr zcomplex<zdouble> operator""_i(unsigned long long d)
//    {
//        return { 0.0, d };
//    }
//    constexpr zcomplex<zdouble> operator""_i(long double d)
//    {
//        return { 0.0, d };
//    }
//
//    constexpr zcomplex<zfloat> operator""_if(unsigned long long d)
//    {
//        return { 0.0, d };
//    }
//    constexpr zcomplex<zfloat> operator""_if(long double d)
//    {
//        return { 0.0, d };
//    }

    static_assert( std::is_base_of<izcomplex<zfloat>, izcomplex<zfloat>>::value, "base_of<izcomplex> != izcomplex.");

    static_assert( is_cval<izcomplex<zfloat>>::value, "is_cval<izcomplex> == false.");

    static_assert( std::is_base_of<izcomplex<zfloat>, zcomplex<zfloat>>::value, "base_of<zcomplex> != izcomplex.");

//    static_assert(zcomplex<zfloat>::size == 2, "zint32::size != 8.");
//    static_assert(zcomplex<zfloat>::alignment == 32, "zint32::alignment != 32.");
//    static_assert(zcomplex<zfloat>::is_vector == true, "zint32::is_vector != true.");

    static_assert(std::is_same<zcomplex<zfloat>::tag, cval_tag>::value, "izcomplex::tag != cval_tag.");
    static_assert(std::is_same<zcomplex<zfloat>::vector_type, vec2<zfloat>>::value, "zcomplex::vector_type != vec2<zfloat>.");
    static_assert(std::is_same<zcomplex<zfloat>::element_type, zfloat>::value, "zcomplex::element_type != zfloat.");
    static_assert(std::is_same<zcomplex<zfloat>::extracted_type, std::array<zfloat, 2>>::value, "zfloat::extracted_type != std::array<zfloat, 2>.");



    // Validate bint32 ===================================================================================

//    static_assert( std::is_base_of<ibcomplex<zfloat>, ibcomplex<zfloat>>::value, "base_of<izint32> != izint32.");
//    static_assert(!std::is_base_of<izcomplex<zfloat>, ibcomplex<zfloat>>::value, "base_of<izint32> == ibint32.");
//
//    static_assert( is_bval<ibcomplex<zfloat>>::value, "is_bval<ibint32> == false.");
//    static_assert(!is_zval<ibcomplex<zfloat>>::value, "is_zval<ibint32> != false.");
//
//    static_assert( std::is_base_of<ibcomplex<zfloat>, bcomplex<zfloat>>::value, "base_of<bint32> != ibint32.");
//    static_assert(!std::is_base_of<izcomplex<zfloat>, bcomplex<zfloat>>::value, "base_of<bint32> == izint32.");
//
//    static_assert(bcomplex<zfloat>::size == 8, "bint32::size != 8.");
//    static_assert(bcomplex<zfloat>::alignment == 32, "bint32::alignment != 32.");
//    static_assert(bcomplex<zfloat>::is_vector == true, "bint32::is_vector != true.");
//
//    static_assert(std::is_same<bcomplex<zfloat>::tag, bval_tag>::value, "bint32::tag != zval_tag.");
//    static_assert(std::is_same<bcomplex<zfloat>::vector_type, __m256i>::value, "bint32::vector_type != __m256i.");
//    static_assert(std::is_same<bcomplex<zfloat>::element_type, int32_t>::value, "bint32::element_type != int32_t.");
//    static_assert(std::is_same<bcomplex<zfloat>::extracted_type, std::array<int32_t, 8>>::value, "bint32::extracted_type != std::array<int32_t, 8>.");
//
//    static_assert( is_bval<bcomplex<zfloat>>::value, "is_bval<bint32> == false.");
//    static_assert(!is_zval<bcomplex<zfloat>>::value, "is_zval<bint32> != false.");
}}