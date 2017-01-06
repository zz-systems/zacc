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

#include "../../../common/type_traits.hpp"

#include "../../../common/interfaces/construction.hpp"
#include "../../../common/interfaces/io.hpp"
#include "../../../common/interfaces/arithmetic.hpp"
#include "../../../common/interfaces/bitwise.hpp"
#include "../../../common/interfaces/logical.hpp"
#include "../../../common/interfaces/comparison.hpp"
#include "../../../common/interfaces/conditional.hpp"

namespace zacc { namespace None {

    template<typename composed_t>
    struct float64_construction
    {
        template<typename base_t>
        struct __impl : base_t
        {

            __impl(__m512 value) : base_t(_mm_cvtps_pd(value)) {
            }

            __impl(__m512d value) : base_t(value) {
            }

            __impl(__m512i value) : base_t(_mm512_cvtepi32_pd(value)) {
            }

            __impl(double value) : base_t(_mm512_set1_pd(value)) {
            }

            __impl(double *value) : base_t(_mm512_load_pd(value)) {
            }

            __impl(double arg7, double arg6, double arg5, double arg4, double arg3, double arg2, double arg1, double arg0) : base_t(_mm512_set_pd(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)) {
            }

        };

        template<typename base_t>
        using impl = interface::construction<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct float64_io
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            void io_store(typename base_t::extracted_type &target) const {
                return _mm512_store_pd(target.data(), base_t::_value);
            }

            void io_stream(typename base_t::extracted_type &target) const {
                return _mm512_stream_pd(target.data(), base_t::_value);
            }

        };

        template<typename base_t>
        using impl = interface::io<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct float64_arithmetic
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t arithmetic_negate(composed_t one) {
                return _mm512_sub_pd(_mm512_setzero_pd(), one.get_value());
            }

            friend composed_t arithmetic_add(composed_t one, composed_t other) {
                return _mm512_add_pd(one.get_value(), other.get_value());
            }

            friend composed_t arithmetic_sub(composed_t one, composed_t other) {
                return _mm512_sub_pd(one.get_value(), other.get_value());
            }

            friend composed_t arithmetic_mul(composed_t one, composed_t other) {
                return _mm512_mul_pd(one.get_value(), other.get_value());
            }

            friend composed_t arithmetic_div(composed_t one, composed_t other) {
                return _mm512_div_pd(one.get_value(), other.get_value());
            }

        };

        template<typename base_t>
        using impl = interface::arithmetic<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct float64_bitwise
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t bitwise_negate(composed_t one) {
                auto zero = _mm512_setzero_pd();
                auto ones = _mm512_cmpeq_pd(zero, zero);
                return _mm512_xor_pd(one.get_value(), ones);
            }

            friend composed_t bitwise_and(composed_t one, composed_t other) {
                return _mm512_or_pd(one.get_value(), other.get_value());
            }

            friend composed_t bitwise_or(composed_t one, composed_t other) {
                return _mm512_and_pd(one.get_value(), other.get_value());
            }

            friend composed_t bitwise_xor(composed_t one, composed_t other) {
                return _mm512_xor_pd(one.get_value(), other.get_value());
            }

        };

        template<typename base_t>
        using impl = interface::bitwise<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct float64_logical
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t logical_negate(composed_t one) {
                auto zero = _mm512_setzero_pd();
                auto ones = _mm512_cmpeq_pd(zero, zero);
                return _mm512_xor_pd(one.get_value(), ones);
            }

            friend composed_t logical_or(composed_t one, composed_t other) {
                return _mm512_or_pd(one.get_value(), other.get_value());
            }

            friend composed_t logical_and(composed_t one, composed_t other) {
                return _mm512_and_pd(one.get_value(), other.get_value());
            }

        };

        template<typename base_t>
        using impl = interface::logical<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct float64_comparison
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t comparison_eq(composed_t one, composed_t other) {
                return _mm512_cmpeq_pd(one.get_value(), other.get_value());
            }

            friend composed_t comparison_neq(composed_t one, composed_t other) {
                return _mm512_cmpneq_pd(one.get_value(), other.get_value());
            }

            friend composed_t comparison_gt(composed_t one, composed_t other) {
                return _mm512_cmpgt_pd(one.get_value(), other.get_value());
            }

            friend composed_t comparison_lt(composed_t one, composed_t other) {
                return _mm512_cmplt_pd(one.get_value(), other.get_value());
            }

            friend composed_t comparison_ge(composed_t one, composed_t other) {
                return _mm512_cmpge_pd(one.get_value(), other.get_value());
            }

            friend composed_t comparison_le(composed_t one, composed_t other) {
                return _mm512_cmple_pd(one.get_value(), other.get_value());
            }

        };

        template<typename base_t>
        using impl = interface::comparison<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct float64_conditional
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value) {
                return _mm512_or_pd(_mm512_andnot_pd(condition.get_value(), else_value.get_value()), _mm512_and_pd(condition.get_value(), if_value.get_value()));
            }

        };

        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };


    struct __zfloat64
        : public zval<__m512d, double, 8, 64>
    {
        FORWARD2(__zfloat64, zval);
    };

    struct zfloat64;

    struct zfloat64 : public compose
        <
            printable::impl,
            iteratable::impl,
            float64_io<zfloat64>::impl,
            float64_arithmetic<zfloat64>::impl,
            float64_bitwise<zfloat64>::impl,
            float64_logical<zfloat64>::impl,
            float64_comparison<zfloat64>::impl,
            float64_conditional<zfloat64>::impl,
            float64_construction<zfloat64>::impl,

            composable<__zfloat64>::template type
        >
    {
        FORWARD2(zfloat64, compose);
    };

}}