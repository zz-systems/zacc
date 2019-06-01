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

#include <zacc/compute/core/core.hpp>
#include <zacc/compute/eval/complex.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename T>
    struct complex : term<complex<T>>
    {
        using value_type = T;
        using eval_type = complex_evaluator;

        constexpr static size_t size = 2;
        constexpr static uint64_t mask = 0;
        constexpr static expr_tag expr_tag = expr_tag::complex;

        // =============================================================================================================

        constexpr complex() = default;

        constexpr complex(const complex& other) = default;
        constexpr complex& operator=(complex const& other) = default;

        constexpr complex(complex&& other) noexcept = default;
        constexpr complex& operator=(complex&& other) noexcept = default;

        // =============================================================================================================

        constexpr complex(std::initializer_list<T> init_list)
        {
            recorder::current() << declare_expr<complex>(*this);

            std::copy(std::begin(init_list), std::end(init_list), std::begin(_data));
        }

        template<typename Expr>
        constexpr complex(Expr expr) noexcept
        {
            auto d = declare_expr<complex>(*this);
            auto e = assign_expr<complex, Expr>(*this, expr);

            recorder::current() << d << e;
            eval_type::current() << e;
        }

        template<typename Expr>
        constexpr complex& operator=(Expr const& expr) noexcept
        {
            auto e = assign_expr<complex, Expr>(*this, expr);

            recorder::current() << e;
            eval_type::current() << e;

            return *this;
        }

        // =============================================================================================================

        constexpr auto real() { return _data[0]; }
        constexpr auto real() const { return _data[0]; }

        constexpr auto imag() { return _data[1]; }
        constexpr auto imag() const { return _data[1]; }

        // =============================================================================================================

        constexpr auto begin() { return _data.begin(); }
        constexpr auto begin() const { return _data.begin(); }

        constexpr auto end() { return _data.end(); }
        constexpr auto end() const { return _data.end(); }

        // =============================================================================================================

        constexpr value_type& eval(size_t i)
        {
            return _data[i];
        }

        constexpr value_type const& eval(size_t i) const
        {
            return _data[i];
        }

        // =============================================================================================================

    private:
        alignas(T) typename container<T, size>::type _data;
    };

    // =================================================================================================================

    static_assert(is_complex_expr<complex<float>>::value, "complex<float> should be complex expr");
    static_assert(is_complex_expr<complex<float>, complex<float>>::value, "complex<float> should be complex expr");
}}