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

#include <zacc/compute/core/core.hpp>
#include <zacc/compute/renderer/generator.hpp>

namespace zacc { namespace compute {

    // =================================================================================================================

    struct renderer
    {
        template<typename T>
        generator operator()(const lit<T>& t)
        {
            generator scope;
            scope << t._val;

            return scope;
        }

        template<typename T>
        generator operator()(const term<T>& t)
        {
            generator scope;
            scope << "var_" << std::hex << t.id();

            return scope;
        }

        template<typename T>
        generator operator()(const declare_expr<T>& e)
        {
            generator scope;

            scope << type_of<T>::full_name() << " " << "var_" << std::hex << e._target.id() << ";";

            return scope;
        }

        template<typename T, typename Expr>
        generator operator()(const assign_expr<T, Expr>& e, generator right)
        {
            generator scope;

            scope << "var_" << std::hex << e._target.id() << " = " << right << ";";

            return scope;
        }

        template<typename UnOp, typename Expr>
        generator operator()(const un_expr<UnOp, Expr>&, generator right)
        {
            generator scope;

            scope << name_of<apply_t<UnOp, Expr>> << right;

            return scope;
        }

        template<typename BinOp, typename LExpr, typename RExpr>
        generator operator()(const bin_expr<BinOp, LExpr, RExpr>&, generator left, generator right)
        {
            generator scope;

            scope << left << " " << name_of<apply_t<BinOp, LExpr, RExpr>> << " " << right;

            return scope;
        }

        template<typename TriOp, typename AExpr, typename BExpr, typename CExpr>
        generator operator()(const tri_expr<TriOp, AExpr, BExpr, CExpr>&, generator a, generator b, generator c)
        {
            generator scope;

            scope << name_of<apply_t<TriOp, AExpr, BExpr, CExpr>> << "(" << a << ", " << b << ", " << c << ")";

            return scope;
        }

        template<typename FuncOp, typename AExpr, typename BExpr, typename CExpr>
        generator operator()(const func_expr<FuncOp, AExpr, BExpr, CExpr>&, generator a, generator b, generator c)
        {
            generator scope;

            scope << name_of<apply_t<FuncOp, AExpr, BExpr, CExpr>> << "(" << a << ", " << b << ", " << c << ")";

            return scope;
        }
    };

    // =================================================================================================================

    template<typename T>
    generator& operator<<(generator& g, const expr_t<T>& data)
    {
        g << expr_visitor<renderer>::visit(data);

        return g;
    }

    // =================================================================================================================
}}