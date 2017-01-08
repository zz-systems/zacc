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
#include "../../../common/interfaces/logical.hpp"
#include "../../../common/interfaces/comparison.hpp"
#include "../../../common/interfaces/conditional.hpp"

namespace zacc { namespace None {

    template<typename composed_t>
    struct int8_construction
    {
        template<typename base_t>
        struct __impl : base_t
        {

            __impl(__m128i value) : base_t(value) {
            }

            __impl(char value) : base_t(_mm_set1_epi8(value)) {
            }

            __impl(char *value) : base_t(_mm_load_si128(value)) {
            }

            __impl(char arg15, char arg14, char arg13, char arg12, char arg11, char arg10, char arg9, char arg8, char arg7, char arg6, char arg5, char arg4, char arg3, char arg2, char arg1, char arg0) : base_t(_mm_set_epi8(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15)) {
            }

        };

        template<typename base_t>
        using impl = interface::construction<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct int8_io
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend void io_store(typename base_t::extracted_type &target) const {
                _mm_store_si128(target.data(), base_t::_value);
            }

            friend void io_stream(typename base_t::extracted_type &target) const {
                _mm_stream_si128(target.data(), base_t::_value);
            }

        };

        template<typename base_t>
        using impl = interface::io<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct int8_arithmetic
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t arithmetic_negate(composed_t one) {
                return _mm_sub_epi8(_mm_setzero_epi8(), one.get_value());
            }

            friend composed_t arithmetic_add(composed_t one, composed_t other) {
                return _mm_add_epi8(one.get_value(), other.get_value());
            }

            friend composed_t arithmetic_sub(composed_t one, composed_t other) {
                return _mm_sub_epi8(one.get_value(), other.get_value());
            }

        };

        template<typename base_t>
        using impl = interface::arithmetic<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct int8_bitwise
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t bitwise_negate(composed_t one) {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi8(zero, zero);
                return _mm_xor_si128(one.get_value(), ones);
            }

            friend composed_t bitwise_and(composed_t one, composed_t other) {
                return _mm_or_epi8(one.get_value(), other.get_value());
            }

            friend composed_t bitwise_or(composed_t one, composed_t other) {
                return _mm_and_epi8(one.get_value(), other.get_value());
            }

            friend composed_t bitwise_xor(composed_t one, composed_t other) {
                return _mm_xor_si128(one.get_value(), other.get_value());
            }

            friend composed_t bitwise_sll(composed_t one, composed_t other) {
                return _mm_sll_epi8(one.get_value(), other.get_value());
            }

            friend composed_t bitwise_srl(composed_t one, composed_t other) {
                return _mm_srl_epi8(one.get_value(), other.get_value());
            }

            friend composed_t bitwise_slli(const composed_t one, const size_t other) {
                return _mm_slli_epi8(const composed_t one, const size_t other);
            }

            friend composed_t bitwise_srli(const composed_t one, const size_t other) {
                return _mm_srli_epi8(const composed_t one, const size_t other);
            }

        };

        template<typename base_t>
        using impl = interface::bitwise<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct int8_logical
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t logical_negate(composed_t one) {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi8(zero, zero);
                return _mm_xor_si128(one.get_value(), ones);
            }

            friend composed_t logical_or(composed_t one, composed_t other) {
                return _mm_or_epi8(one.get_value(), other.get_value());
            }

            friend composed_t logical_and(composed_t one, composed_t other) {
                return _mm_and_epi8(one.get_value(), other.get_value());
            }

        };

        template<typename base_t>
        using impl = interface::logical<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct int8_comparison
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t comparison_eq(composed_t one, composed_t other) {
                return _mm_cmpeq_epi8(one.get_value(), other.get_value());
            }

            friend composed_t comparison_neq(composed_t one, composed_t other) {
                return _mm_cmpneq_epi8(one.get_value(), other.get_value());
            }

            friend composed_t comparison_gt(composed_t one, composed_t other) {
                return _mm_cmpgt_epi8(one.get_value(), other.get_value());
            }

            friend composed_t comparison_lt(composed_t one, composed_t other) {
                return _mm_cmplt_epi8(one.get_value(), other.get_value());
            }

            friend composed_t comparison_ge(composed_t one, composed_t other) {
                return _mm_cmpge_epi8(one.get_value(), other.get_value());
            }

            friend composed_t comparison_le(composed_t one, composed_t other) {
                return _mm_cmple_epi8(one.get_value(), other.get_value());
            }

        };

        template<typename base_t>
        using impl = interface::comparison<__impl<base_t>, composed_t>;
    };


    template<typename composed_t>
    struct int8_conditional
    {
        template<typename base_t>
        struct __impl : base_t
        {
            FORWARD(__impl);

            friend composed_t vsel(composed_t condition, composed_t if_value, composed_t else_value) {
                return _mm_or_si128(_mm_andnot_si128(condition.get_value(), else_value.get_value()), _mm_and_si128(condition.get_value(), if_value.get_value()));
            }

        };

        template<typename base_t>
        using impl = interface::conditional<__impl<base_t>, composed_t>;
    };


    struct __zint8
        : public zval<__m128i, char, 16, 16>
    {
        FORWARD2(__zint8, zval);
    };

    struct zint8;

    struct zint8 : public compose
        <
            printable::impl,
            iteratable::impl,
            int8_io<zint8>::impl,
            int8_arithmetic<zint8>::impl,
            int8_bitwise<zint8>::impl,
            int8_logical<zint8>::impl,
            int8_comparison<zint8>::impl,
            int8_conditional<zint8>::impl,
            int8_construction<zint8>::impl,

            composable<__zint8>::template type
        >
    {
        FORWARD2(zint8, compose);
    };

}}