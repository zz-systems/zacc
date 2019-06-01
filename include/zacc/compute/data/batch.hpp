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

#include <zacc/compute/core/core.hpp>
#include <zacc/compute/transformer/transformer.hpp>
#include <zacc/compute/recorder/recorder.hpp>
#include <zacc/compute/data/container.hpp>
#include <zacc/compute/eval/batch.hpp>

#include <algorithm>
#include <functional>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename T, size_t Size>
    struct batch : term<batch<T, Size>>
    {
        using value_type = T;
        using eval_type = batch_evaluator;

        constexpr static size_t size = Size;
        constexpr static uint64_t mask = 0;
        constexpr static expr_tag expr_tag = expr_tag::scalar;

        constexpr value_type& eval(size_t i)
        {
            return _data[i];
        }

        constexpr value_type const& eval(size_t i) const
        {
            return _data[i];
        }

        constexpr batch() noexcept
        {
            recorder::current() << declare_expr<batch>(*this);
        }

        constexpr batch(batch const&) = default;
        constexpr batch(batch&&) noexcept = default;
        constexpr batch& operator=(batch const&) = delete;
        constexpr batch& operator=(batch&&) = delete;

        constexpr batch(std::initializer_list<T> init_list)
        {
            recorder::current() << declare_expr<batch>(*this);

            std::copy(std::begin(init_list), std::end(init_list), std::begin(_data));
        }

        template<typename Expr>
        constexpr batch(Expr expr) noexcept
        {
            auto d = declare_expr<batch>(*this);
            auto e = assign_expr<batch, Expr>(*this, expr);

            recorder::current() << d << e;
            batch_evaluator::current() << e;
        }

        template<typename Expr>
        constexpr batch& operator=(Expr const& expr) noexcept
        {
            auto e = assign_expr<batch, Expr>(*this, expr);

            recorder::current() << e;
            batch_evaluator::current() << e;

            return *this;
        }

    private:
        alignas(T) typename container<T, Size>::type _data;
    };

    // =================================================================================================================


    // =================================================================================================================

    static_assert(expr_traits<batch<int, 2>>::size == 2, "Size is not 2");
    static_assert(expr_traits<batch<int, 2>>::mask == 0, "Mask is not 0");
    static_assert(expr_traits<batch<int, 2>>::expr_tag == expr_tag::scalar, "Tag is not 'scalar'");

    // =================================================================================================================
}}