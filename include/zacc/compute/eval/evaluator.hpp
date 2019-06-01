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

#include <zacc/compute/core/expressions.hpp>
#include <zacc/compute/core/pipe.hpp>
#include <zacc/util/crtp_this.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename Impl>
    struct evaluator : expr<evaluator<Impl>>, crtp_this<Impl>
    {
        using crtp_this<Impl>::self;

        template<typename Func>
        pipe<Impl, Func> operator<<(Func const& func) const
        {
            return pipe<Impl, Func>(*self(), func);
        }

        template<typename Target>
        pipe<Impl, declare_expr<Target>> operator<<(declare_expr<Target> const& expr) const
        {
            return { *self(), expr };
        }

        template<typename Target, typename Expr>
        Impl const& operator<<(assign_expr<Target, Expr> const& expr) const
        {
            eval(expr);

            return *self();
        }

        template<typename Target, typename Expr>
        Impl& operator<<(assign_expr<Target, Expr>& expr)
        {
            eval(expr);

            return *self();
        }

        template<typename... Args>
        auto eval(Args&& ...args)
        {
            return self()->eval(std::forward<Args>(args)...);
        }

        template<typename... Args>
        auto eval(Args&& ...args) const
        {
            return self()->eval(std::forward<Args>(args)...);
        }

        static Impl& current() {
            static Impl instance;

            return instance;
        }
    };

    // =================================================================================================================

}}