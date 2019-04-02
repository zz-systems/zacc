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

#include <zacc/expressions/expression.hpp>

namespace zacc { namespace expressions {

    struct evaluator
    {
        template<typename Target>
        pipe<evaluator, declare_expr<Target>> operator<<(declare_expr<Target> expr)
        {
            return { *this, expr };
        }

        template<typename Target, typename Expr>
        evaluator& operator<<(assign_expr<Target, Expr> expr)
        {
            eval(expr);

            return *this; //{ *this, expr };
        }

        template<typename Expr>
        void operator()(Expr expr) const
        {
            eval(expr);
        }

        template<typename Expr>
        void eval(Expr expr) const
        {
//            for(size_t i = 0; i < Expr::size(); ++i)
            for(size_t i = 0; i < 2; ++i)
            {
                expr(i);
            };
        }

        template<typename Func>
        pipe<evaluator, Func> operator<<(Func func)
        {
            return pipe<evaluator, Func>(*this, func);
        }

        static evaluator& current() {
            static evaluator instance;

            return instance;
        }
    };


//    template<typename Expr>
//    std::ostream&
//    operator<<(std::ostream& os, const pipe<evaluator, Expr>& expr)
//    {
//        expr._left.eval(expr._right);
//
//        return os;
//    }

    // =================================================================================================================

}}

namespace zacc
{
//    template<typename Right>
//    struct pipe<expressions::evaluator, Right>
//    {
//        expressions::evaluator _left;
//        Right _right;
//
//        pipe(expressions::evaluator left, Right right)
//            : _left(left), _right(right)
//        {}
//
//        auto operator()() { return _left(_right); }
//
//        template<typename... Args>
//        auto operator()(Args&& ...args) { return _left(_right(std::forward<Args>(args)...)); }
//    };
}