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
#include <sstream>

#include <zacc/compute/core/expressions.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    template<typename Visitor>
    struct expr_visitor
    {
        template<typename T>
        static auto visit(const lit<T>& node, Visitor visitor = Visitor())
        {
            return visitor(node);
        }

        template<typename T>
        static auto visit(const term<T>& node, Visitor visitor = Visitor())
        {
            return visitor(node);
        }

        template<typename T>
        static auto visit(const declare_expr<T>& node, Visitor visitor = Visitor())
        {
            return visitor(node);
        }

        template<typename T, typename Right>
        static auto visit(const assign_expr<T, Right>& node, Visitor visitor = Visitor())
        {
            return visitor(node, expr_visitor<Visitor>::visit(node._expr));
        }

        template<typename UnOp, typename Right>
        static auto visit(const un_expr<UnOp, Right>& node, Visitor visitor = Visitor())
        {
            return visitor(node, expr_visitor<Visitor>::visit(node._expr));
        }

        template<typename BinOp, typename Left, typename Right>
        static auto visit(const bin_expr<BinOp, Left, Right>& node, Visitor visitor = Visitor())
        {
            return visitor(node, expr_visitor<Visitor>::visit(node._left), expr_visitor<Visitor>::visit(node._right));
        }

        template<typename TriOp, typename AExpr, typename BExpr, typename CExpr>
        static auto visit(const tri_expr<TriOp, AExpr, BExpr, CExpr>& node, Visitor visitor = Visitor())
        {
            return visitor(node, expr_visitor<Visitor>::visit(node._a), expr_visitor<Visitor>::visit(node._b), expr_visitor<Visitor>::visit(node._c));
        }

        template<typename FuncOp, typename AExpr, typename BExpr, typename CExpr>
        static auto visit(const func_expr<FuncOp, AExpr, BExpr, CExpr>& node, Visitor visitor = Visitor())
        {
            return visitor(node, expr_visitor<Visitor>::visit(node._a), expr_visitor<Visitor>::visit(node._b), expr_visitor<Visitor>::visit(node._c));
        }
    };

    // =================================================================================================================

//    template<typename Impl>
//    struct expr_visitor
//    {
//        void operator()(__expr& expr)
//        {
//            static_cast<Impl *const>(this)->ap1ply(expr);
//        }
//    };
//
//
//    struct lit_visitor : expr_visitor<lit_visitor>
//    {
//        template<typename T>
//        void apply(lit<T> const& expr)
//        {
//
//        }
//    };

    // =================================================================================================================

}}