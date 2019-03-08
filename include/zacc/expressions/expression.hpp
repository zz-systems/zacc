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

namespace zacc {

    template<typename Expr>
    struct expr
    {
        //auto operator()() { return static_cast<const Expr*>(this)->operator(); }
    };

    template<typename T>
    struct arg : expr<arg<T>>
    {
        T operator() (T val)
        {
            return val;
        }
    };

    template<typename T>
    struct lit : expr<lit<T>>
    {
        T _val;

        lit(T val) : _val(val)
        {}

        T operator()()
        {
            return _val;
        }
    };

    template<typename BinOp, typename Left, typename Right>
    struct bin_expr : expr<bin_expr<BinOp, Left, Right>>
    {
        Left _left;
        Right _right;

        bin_expr(Left left, Right right)
            : _left(left), _right(right)
        {}

        auto operator()() { return BinOp()(_left(), _right()); }
    };

    template<typename UnOp, typename Expr>
    struct un_expr : expr<un_expr<UnOp, Expr>>
    {
        Expr _expr;

        un_expr(Expr expr)
            : _expr(expr)
        {}

        auto operator()() { return UnOp()(_expr()); }
    };
}