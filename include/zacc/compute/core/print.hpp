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

#include <stack>
#include <list>
#include <map>
#include <string>

namespace zacc::compute
{
    template<typename Expression>
    constexpr auto make_print_expr(Expression&& expression);

    template<typename Expression>
    class print_expr
    {
    public:
        constexpr explicit print_expr(Expression&& expression)
            : _expression { std::forward<Expression>(expression) }
        {}

        constexpr explicit print_expr(Expression const& expression)
            : _expression { expression }
        {}
    private:

        Expression _expression;

        struct bla
        {
            std::stack<std::string> stack;
            std::map<size_t, std::tuple<std::string, std::string, std::string>> vars;

            template<typename E>
            void visit(E&& expr)
            {
                if constexpr(std::is_base_of_v<expression<>, std::decay_t<E>>)
                {
                    using op = typename std::decay_t<E>::operator_type;

                    if constexpr(std::is_same_v<op, assign_op<>>)
                    {
                        visit(expr.second());
                        stack.push(" = ");
                        visit(expr.first());
                    }
                    if constexpr(std::is_same_v<op, init_op<>>)
                    {
                        visit(expr.second());
                        stack.push(" = ");
                        visit(expr.first());
                    }
                    if constexpr(std::is_same_v<op, fmadd_op<>>)
                    {
                        stack.push(")");
                        visit(expr.template operand<2>());
                        stack.push(", ");
                        visit(expr.template operand<1>());
                        stack.push(", ");
                        visit(expr.template operand<0>());
                        stack.push("(");
                        stack.push("fma");
                    }
                    else if constexpr(std::is_same_v<op, select_op<>>)
                    {
                        visit(expr.template operand<2>());
                        stack.push("\t: ");
                        stack.push("\n");
                        visit(expr.template operand<1>());
                        stack.push("\t? ");
                        stack.push("\n");
                        visit(expr.template operand<0>());
                    }
                    else
                    {
                        stack.push(")");
                        visit(expr.second());
                        if constexpr(std::is_same_v<op, add_op<>>)
                        {
                            stack.push(" + ");
                        }
                        else if constexpr(std::is_same_v<op, sub_op<>>)
                        {
                            stack.push(" - ");
                        }
                        else if constexpr(std::is_same_v<op, mul_op<>>)
                        {
                            stack.push(" * ");
                        }
                        else if constexpr(std::is_same_v<op, fmadd_op<>>)
                        {
                            stack.push("fma");
                        }
                        visit(expr.first());
                        stack.push("(");
                    }
                }
                else if constexpr(std::is_base_of_v<var<>, std::decay_t<E>>)
                {
                    using vt = typename std::decay_t<E>::value_type;

                    auto id = expr.handle();
                    std::string type;
                    std::string suffix;

                    if constexpr(std::is_same_v<vt, int8_t>)
                    {
                        type = "int8_t";
                        suffix = "i8";
                    }
                    else if constexpr(std::is_same_v<vt, int16_t>)
                    {
                        type = "int16_t";
                        suffix = "i16";
                    }
                    else if constexpr(std::is_same_v<vt, int32_t>)
                    {
                        type = "int32_t";
                        suffix = "i32";
                    }
                    else if constexpr(std::is_same_v<vt, float>)
                    {
                        type = "float";
                        suffix = "f";
                    }
                    else if constexpr(std::is_same_v<vt, double>)
                    {
                        type = "double";
                        suffix = "d";
                    }

                    std::string name = "var" + std::to_string(id) + "_" + suffix;

                    stack.push(name);

                    if (!vars.count(id))
                    {
                        vars.emplace(id, std::make_tuple(type, name, std::to_string(0/*expr()*/)));
                    }
                }
                else
                {
                    stack.push(std::to_string(expr));
                }
            };
        };

        template <class charT, class Traits>
        friend std::basic_ostream<charT, Traits>& operator<<(std::basic_ostream<charT, Traits>& os, print_expr const& self)
        {
            bla b;

            b.visit(self._expression);

            os << "{" << std::endl;
            for(auto [k, v] : b.vars)
            {
                auto [t, n, i] = v;
                os << t << " " << n << " = " << i << ";" << std::endl;
            }

            while(!b.stack.empty())
            {
                os << b.stack.top();
                b.stack.pop();
            }

            os << ";" << std::endl;

            os << "}" << std::endl;

            return os;
        }
    };

    template<typename>
    class builder;

    template<typename Expression>
    void print(Expression&& expr)
    {
        auto b = builder(expr);
        auto e = b.build(scalar{});
        std::cout << e() << std::endl;
    }
}