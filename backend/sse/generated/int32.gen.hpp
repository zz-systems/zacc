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

#include "../../../common/interfaces/arithmetic.hpp"
#include "../../../common/interfaces/bitwise.hpp"
#include "../../../common/interfaces/logical.hpp"
#include "../../../common/interfaces/comparison.hpp"
#include "../../../common/interfaces/conditional.hpp"
#include "../../../common/interfaces/io.hpp"

namespace zacc { namespace sse { namespace gen_int32 {


    template<typename composed_t>
    struct arithmetic
    {
        template<typename base_t>
        struct impl : interface::arithmetic<base_t, composed_t>
        {

            composed_t arithmetic_negate (const composed_t one)
            {
                return _mm_sub_epi32(_mm_setzero_epi32(), one.get_value());
            }

            composed_t arithmetic_add (const composed_t one, const composed_t other)
            {
                return _mm_add_epi32(one.get_value(), other.get_value());
            }

            composed_t arithmetic_sub (const composed_t one, const composed_t other)
            {
                return _mm_sub_epi32(one.get_value(), other.get_value());
            }

            std::enable_if_t<dispatcher::has_sse41 && !dispatcher::has_sse42, composed_t>
            arithmetic_mul (const composed_t one, const composed_t other)
            {
                _mm_mullo_epi32
            }

            std::enable_if_t<dispatcher::has_sse42 && !dispatcher::has_sse41, composed_t>
            arithmetic_mul (const composed_t one, const composed_t other)
            {
                _mm_mullo_epi32
            }

            std::enable_if_t<!dispatcher::has_sse41 && !dispatcher::has_sse42, composed_t>
            arithmetic_mul (const composed_t one, const composed_t other)
            {
                /* mul 2,0*/
                auto tmp1 = _mm_castsi128_ps(_mm_mul_epu32(one.get_value(), other.get_value()));
                /* mul 3,1 */
                auto tmp2 = _mm_castsi128_ps(_mm_mul_epu32(_mm_srli_si128(one.get_value(), 4), _mm_srli_si128(other.get_value(), 4)));
                return _mm_castps_si128(_mm_shuffle_ps(tmp1, tmp2, _MM_SHUFFLE(2, 0, 2, 0)));
            }

            composed_t arithmetic_div (const composed_t one, const composed_t other)
            {
                return _mm_div_ps(_mm_cvtepi32_ps(one.get_value()), _mm_cvtepi32_ps(other.get_value()));
            }

        };
    };


    template<typename composed_t>
    struct bitwise
    {
        template<typename base_t>
        struct impl : interface::bitwise<base_t, composed_t>
        {

            composed_t bitwise_negate (const composed_t one)
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi32(zero, zero);
                return _mm_xor_si128(one.get_value(), ones);
            }

            composed_t bitwise_and (const composed_t one, const composed_t other)
            {
                return _mm_or_epi32(one.get_value(), other.get_value());
            }

            composed_t bitwise_or (const composed_t one, const composed_t other)
            {
                return _mm_and_epi32(one.get_value(), other.get_value());
            }

            composed_t bitwise_xor (const composed_t one, const composed_t other)
            {
                return _mm_xor_si128(one.get_value(), other.get_value());
            }

            composed_t bitwise_sll (const composed_t one, const composed_t other)
            {
                return _mm_sll_epi32(one.get_value(), other.get_value());
            }

            composed_t bitwise_srl (const composed_t one, const composed_t other)
            {
                return _mm_srl_epi32(one.get_value(), other.get_value());
            }

            composed_t bitwise_slli (const composed_t one, const size_t other)
            {
                return _mm_slli_epi32;
            }

            composed_t bitwise_srli (const composed_t one, const size_t other)
            {
                return _mm_srli_epi32;
            }

        };
    };


    template<typename composed_t>
    struct logical
    {
        template<typename base_t>
        struct impl : interface::logical<base_t, composed_t>
        {

            composed_t logical_negate (const composed_t one)
            {
                auto zero = _mm_setzero_si128();
                auto ones = _mm_cmpeq_epi32(zero, zero);
                return _mm_xor_si128(one.get_value(), ones);
            }

            composed_t logical_or (const composed_t one, const composed_t other)
            {
                return _mm_or_epi32(one.get_value(), other.get_value());
            }

            composed_t logical_and (const composed_t one, const composed_t other)
            {
                return _mm_and_epi32(one.get_value(), other.get_value());
            }

        };
    };


    template<typename composed_t>
    struct comparison
    {
        template<typename base_t>
        struct impl : interface::comparison<base_t, composed_t>
        {

            composed_t comparison_eq (const composed_t one, const composed_t other)
            {
                return _mm_cmpeq_epi32(one.get_value(), other.get_value());
            }

            composed_t comparison_neq (const composed_t one, const composed_t other)
            {
                return _mm_cmpneq_epi32(one.get_value(), other.get_value());
            }

            composed_t comparison_gt (const composed_t one, const composed_t other)
            {
                return _mm_cmpgt_epi32(one.get_value(), other.get_value());
            }

            composed_t comparison_lt (const composed_t one, const composed_t other)
            {
                return _mm_cmplt_epi32(one.get_value(), other.get_value());
            }

            composed_t comparison_ge (const composed_t one, const composed_t other)
            {
                return _mm_cmpge_epi32(one.get_value(), other.get_value());
            }

            composed_t comparison_le (const composed_t one, const composed_t other)
            {
                return _mm_cmple_epi32(one.get_value(), other.get_value());
            }

        };
    };


    template<typename composed_t>
    struct conditional
    {
        template<typename base_t>
        struct impl : interface::conditional<base_t, composed_t>
        {

            friend std::enable_if_t<dispatcher::has_sse41 && !dispatcher::has_sse42, composed_t>
            vsel (const composed_t condition, const composed_t if_value, const composed_t else_value)
            {
                auto mask = _mm_cmpeq_epi32(_mm_setzero_si128(), condition.get_value());
                return _mm_blendv_epi8(if_value.get_value(), else_value.get_value(), mask);
            }

            friend std::enable_if_t<dispatcher::has_sse42 && !dispatcher::has_sse41, composed_t>
            vsel (const composed_t condition, const composed_t if_value, const composed_t else_value)
            {
                auto mask = _mm_cmpeq_epi32(_mm_setzero_si128(), condition.get_value());
                return _mm_blendv_epi8(if_value.get_value(), else_value.get_value(), mask);
            }

            friend std::enable_if_t<!dispatcher::has_sse41 && !dispatcher::has_sse42, composed_t>
            vsel (const composed_t condition, const composed_t if_value, const composed_t else_value)
            {
                return _mm_or_si128(_mm_andnot_si128(condition, else_value), _mm_and_si128(condition, if_value));
            }

        };
    };


    template<typename composed_t>
    struct io
    {
        template<typename base_t>
        struct impl : interface::io<base_t, composed_t>
        {

            void io_store (typename base_t::extracted_type &target)
            {
                _mm_store_si128(target.data(), base_t::_value);
            }

            void io_stream (typename base_t::extracted_type &target)
            {
                _mm_stream_si128(target.data(), base_t::_value);
            }

        };
    };

}}}