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

#include <zacc/expressions/expression.hpp>
#include <zacc/expressions/expression_visitor.hpp>

namespace zacc { namespace expressions {

    struct renderer;

    struct generator
    {
        std::stringstream ss;

        template<typename T>
        generator& operator<<(const T& data)
        {
            ss << data;

            return *this;
        }
    };

    generator& operator<<(generator& g, const generator& data)
    {
        g << data.ss.str();

        return g;
    }

    std::ostream& operator<<(std::ostream& os, const generator& data)
    {
        os << data.ss.str();

        return os;
    }

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

        template<typename T, typename Right>
        generator operator()(const assign_expr<T, Right>& e, generator right)
        {
            generator scope;

            scope << "var_" << std::hex << e._target.id() << " = " << right << ";";

            return scope;
        }

        template<typename UnOp, typename Right>
        generator operator()(const un_expr<UnOp, Right>&, generator right)
        {
            generator scope;

            scope << name_of<UnOp> << right;

            return scope;
        }

        template<typename BinOp, typename Left, typename Right>
        generator operator()(const bin_expr<BinOp, Left, Right>&, generator left, generator right)
        {
            generator scope;

            scope << left << " " << name_of<BinOp> << " " << right;

            return scope;
        }

        template<typename TriOp, typename AExpr, typename BExpr, typename CExpr>
        generator operator()(const tri_expr<TriOp, AExpr, BExpr, CExpr>&, generator a, generator b, generator c)
        {
            generator scope;

            scope << name_of<TriOp> << "(" << a << ", " << b << ", " << c << ")";

            return scope;
        }

        template<typename FuncOp, typename AExpr, typename BExpr, typename CExpr>
        generator operator()(const func_expr<FuncOp, AExpr, BExpr, CExpr>&, generator a, generator b, generator c)
        {
            generator scope;

            scope << name_of<FuncOp> << "(" << a << ", " << b << ", " << c << ")";

            return scope;
        }
    };


    template<typename T>
    generator& operator<<(generator& g, const expr_t<T>& data)
    {
        g << expr_visitor<renderer>::visit(data);

        return g;
    }
}}