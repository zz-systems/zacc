//---------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015-2019 Sergej Zuyev (sergej.zuyev - at - zz-systems.net)
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

namespace zacc::compute
{

    // =================================================================================================================

    struct scalar
    {
    };

    // =================================================================================================================

    template<typename A, typename B, typename C>
    struct select_op<scalar, A, B, C> : operator_base
    {
        constexpr select_op(A a, B b, C c) noexcept
            : a { a }, b { b }, c { c }
        {}

        constexpr auto operator()() const
        {
            return c ? a : b;
        }

        A a;
        B b;
        C c;
    };

    template<typename A, typename B>
    struct call_op<scalar, A, B> : operator_base
    {

    };

    template<typename A, typename B>
    struct init_op<scalar, A, B> : operator_base
    {
        constexpr init_op(A& a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() noexcept
        {
            return a = b;
        }

        A &a;
        B b;
    };

    template<typename A, typename B>
    struct assign_op<scalar, A, B> : operator_base
    {
        constexpr assign_op(A& a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() noexcept
        {
            return a = b;
        }

    private:
        A a;
        B b;
    };

    // =================================================================================================================
    // ARITHMETIC
    // =================================================================================================================

    template<typename A>
    struct identity_op<scalar, A> : arithmetic_op
    {
        constexpr identity_op(A a) noexcept
            : a { a }
        {}

        constexpr auto operator()() const noexcept
        {
            return a;
        }

        A a;
    };

    template<typename A, typename B>
    struct add_op<scalar, A, B> : arithmetic_op
    {
        constexpr add_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a + b;
        }

        A a;
        B b;
    };

    template<typename A>
    struct promote_op<scalar, A> : arithmetic_op
    {
        constexpr promote_op(A a) noexcept
            : a { a }
        {}

        constexpr auto operator()() const noexcept
        {
            return +a;
        }

        A a;
    };

    template<typename A, typename B>
    struct sub_op<scalar, A, B> : arithmetic_op
    {
        constexpr sub_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a - b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct mul_op<scalar, A, B> : arithmetic_op
    {
        constexpr mul_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a * b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct div_op<scalar, A, B> : arithmetic_op
    {
        constexpr div_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a / b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct mod_op<scalar, A, B> : arithmetic_op
    {
        constexpr mod_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a % b;
        }

        A a;
        B b;
    };

    template<typename A>
    struct neg_op<scalar, A> : arithmetic_op
    {
        constexpr neg_op(A a) noexcept
            : a { a }
        {}

        constexpr auto operator()() const noexcept
        {
            return -a;
        }

        A a;
    };

    // =================================================================================================================
    // COMPARISON
    // =================================================================================================================

    template<typename A, typename B>
    struct equal_to_op<scalar, A, B> : comparison_op
    {
        constexpr equal_to_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a == b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct not_equal_to_op<scalar, A, B> : comparison_op
    {
        constexpr not_equal_to_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a != b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct greater_op<scalar, A, B> : comparison_op
    {
        constexpr greater_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a > b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct less_op<scalar, A, B> : comparison_op
    {
        constexpr less_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a < b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct greater_equal_op<scalar, A, B> : comparison_op
    {
        constexpr greater_equal_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a >= b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct less_equal_op<scalar, A, B> : comparison_op
    {
        constexpr less_equal_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a <= b;
        }

        A a;
        B b;
    };

    // =================================================================================================================
    // BOOLEAN
    // =================================================================================================================

    template<typename A, typename B>
    struct bool_and_op<scalar, A, B> : bool_op
    {
        constexpr bool_and_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a && b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct bool_or_op<scalar, A, B> : bool_op
    {
        constexpr bool_or_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a || b;
        }

        A a;
        B b;
    };

    template<typename A>
    struct bool_not_op<scalar, A> : bool_op
    {
        constexpr bool_not_op(A a) noexcept
            : a { a }
        {}

        constexpr auto operator()() const noexcept
        {
            return !a;
        }

        A a;
    };

    // =================================================================================================================
    // BITWISE
    // =================================================================================================================

    template<typename A, typename B>
    struct bit_and_op<scalar, A, B> : bitwise_op
    {
        constexpr bit_and_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a & b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct bit_or_op<scalar, A, B> : bitwise_op
    {
        constexpr bit_or_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a | b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct bit_xor_op<scalar, A, B> : bitwise_op
    {
        constexpr bit_xor_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a ^ b;
        }

        A a;
        B b;
    };

    template<typename A>
    struct bit_not_op<scalar, A> : bitwise_op
    {
        constexpr bit_not_op(A a) noexcept
            : a { a }
        {}

        constexpr auto operator()() const noexcept
        {
            return ~a;
        }

        A a;
    };

    template<typename A, typename B>
    struct bit_shl_op<scalar, A, B> : bitwise_op
    {
        constexpr bit_shl_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a << b;
        }

        A a;
        B b;
    };

    template<typename A, typename B>
    struct bit_shr_op<scalar, A, B> : bitwise_op
    {
        constexpr bit_shr_op(A a, B b) noexcept
            : a { a }, b { b }
        {}

        constexpr auto operator()() const noexcept
        {
            return a >> b;
        }

        A a;
        B b;
    };

    // =================================================================================================================
    // OTHER
    // =================================================================================================================

    template<typename A, typename B, typename C>
    struct fmadd_op<scalar, A, B, C> : operator_base
    {
        constexpr fmadd_op(A a, B b, C c) noexcept
            : a { a }, b { b }, C { c }
        {}

        constexpr auto operator()() const noexcept
        {
            return a * b + c;
        }

        A a;
        B b;
        C c;
    };

    template<typename A, typename B, typename C>
    struct fmsub_op<scalar, A, B, C> : operator_base
    {
        constexpr fmsub_op(A a, B b, C c) noexcept
            : a { a }, b { b }, C { c }
        {}

        constexpr auto operator()() const noexcept
        {
            return a * b - c;
        }

        A a;
        B b;
        C c;
    };

    // =================================================================================================================

}